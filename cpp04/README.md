# CPP04 - Table of Contents

| Exercise     | Name       | Learnings                                                                                                                                                                                                                                                                             |
| ------------ | ---------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| [ex00](ex00) | 🐾 Animal  | - Subtype polymorphism                                                                                                                                                                                                                                                                |
| [ex01](ex01) | 🧠 Animal  | - Deep copy vs. shallow copy                                                                                                                                                                                                                                                          |
| [ex02](ex02) | 💭 Animal  | - Abstract classes                                                                                                                                                                                                                                                                    |
| [ex03](ex03) | 🔮 Materia | - Interfaces, <br> - Value-initialization of arrays, <br> - Copy-and-swap idiom, <br> - Move semantics, <br> - Templates and template specialization, <br> - Reference counting, <br> - Overloading `new` and `delete`, <br> - Dynamic dispatch, vTable and vPtr, <br> - Dynamic cast |

# Resources

### Copy-and-Swap Idiom

The copy-and-swap idiom elegantly assists the copy assignment operator in achieving two things: avoiding code duplication, and providing a strong exception guarantee.

```c++
Class operator=(Class other);
```

  1. Take the argument by value (which creates a copy using the copy constructor).
  2. Swap the contents of `*this` with the parameter (which mustn't throw).
  3. Let the destructor clean up the old data when the parameter goes out of scope.

The main benefit of the copy-and-swap idiom is that it provides strong exception guarantee.<br>
In the copy assignment operator, this means that all operations, which could throw an exception (the copying), are made before the object being assigned to gets changed.

It also helps to reuse code between the copy constructor and copy assignment operator.<br>
Since assignment essentially boils down to deletion of the original value and copying over the new value, this idiom allows us to reuse the copy constructor and the destructor.

- [What is the copy-and-swap idiom?](https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom)

- [Want Speed? Pass by Value.](https://web.archive.org/web/20140113221447/http://cpp-next.com/archive/2009/08/want-speed-pass-by-value/)

- [Conditions for copy elision?](https://stackoverflow.com/questions/6383639/conditions-for-copy-elision)

- [Exception-Safety in Generic Components](https://www.boost.org/community/exception_safety.html)

- [Mention on cppreference.com](https://en.cppreference.com/w/cpp/language/operators#Assignment_operator)

- [Example of resource reuse](https://en.cppreference.com/w/cpp/language/copy_assignment#Example)

- [Move constructors and move assignment](https://www.learncpp.com/cpp-tutorial/move-constructors-and-move-assignment/)

- [What is move semantics?](https://stackoverflow.com/questions/3106110/what-is-move-semantics)

### Templates

- [C++ Template implementation file extension convention?](https://stackoverflow.com/a/77060142/24880406)

### Virtual Functions, vTable and vPtr

- [The virtual table](https://www.learncpp.com/cpp-tutorial/the-virtual-table/)

- [Pure virtual functions, abstract base classes, and interface classes](https://www.learncpp.com/cpp-tutorial/pure-virtual-functions-abstract-base-classes-and-interface-classes/)

- [How are virtual functions and vtable implemented?](https://stackoverflow.com/questions/99297/how-are-virtual-functions-and-vtable-implemented)

- [Does the vptr change during destruction?](https://stackoverflow.com/questions/7916833/does-the-vptr-change-during-destruction)

- [When `__cxa_pure_virtual` is just a different flavor of SEGFAULT](https://uvdn7.github.io/pure_virtual/)

- [V-table pseudo-code](https://isocpp.org/wiki/faq/virtual-functions#dyn-binding2)

- [When should my destructor be virtual?](https://isocpp.org/wiki/faq/virtual-functions#virtual-dtors)

### Reference Counting

- [How do I do simple reference counting?](https://isocpp.org/wiki/faq/freestore-mgmt#ref-count-simple)

### Overloading `new` and `delete`

- [What are the two steps that happen when I say delete p?](https://isocpp.org/wiki/faq/freestore-mgmt#two-steps-of-delete)

- [What are the steps of new?](https://isocpp.org/wiki/faq/freestore-mgmt#new-doesnt-leak-if-ctor-throws)

---

# Ever wondered why there is `delete` AND `delete[]`?

First, let's have a class `A` which prints something in the constructor, and something in the destructor.<br>
When we `new A[42]`, we see the constructor print 42 times. So far so normal.

But how is it that when we pass that memory address around and eventually `delete[]` it, the program knows at runtime **how many destructors have to be called**?

## Most modern compilers do a secret trick when we `new[N]`

They not only allocate memory for `N` objects, but also for 1 extra `size_t`.<br>
That `size_t` stores the amount of objects that follow, and is stored at the very beginning of the block of memory that gets allocated.<br>
And with that `size_t` the program knows how many destructors to call.

## But why does it crash when we `delete` a pointer that was `new[]`ed?

The pointer that `new[]` returns though starts from the first actual object, so not including the `size_t`. That's important so we can do `array[0]` to access the first element.

But let's keep in mind that the start of the actually allocated memory block starts 1 `size_t` before the pointer that we got!<br>
That is why we have the `delete[]`.<br>
The main difference between `delete[]` and `delete` is that `delete[]` frees the memory 1 `size_t` before the address that we give it, while `delete` frees exactly the address we give it.

That explains why we get an invalid free when we pass a pointer that was `new[]`ed to `delete` instead of `delete[]`.<br>
`delete[]` assumes the actual memory address to free is at an offset, while `delete` does not.

It is exactly the same thing as doing this in C:
```c
char *ptr = malloc(10);
ptr++;
free(ptr);
```

> [!NOTE]
> This is called "over-allocation", and it is a common technique to implement all sorts of memory tracking mechanisms, like reference-counting.

Source:
[How do compilers use “over-allocation” to remember the number of elements in an allocated array?](https://isocpp.org/wiki/faq/compiler-dependencies#num-elems-in-new-array-overalloc)

## Short example

```c++
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <new>
#include <sstream>

class A {
public:
    A() : _ptr(new char[42]) {}
    ~A() { delete[] _ptr; }

private:
    char* _ptr;
};

int main(int argc, char* argv[])
{
    int amount = 0;
    if (argc > 1) {
        std::istringstream(argv[1]) >> amount;
    }

    A* array = new A[amount];

    std::cout << "newed size: " << *(reinterpret_cast<size_t*>(array) - 1)
              << '\n';

    /* Correct */
    delete[] array;

    /* Invalid free */
    // delete array;

    /* Segmentation fault (no object with destructor at that address) */
    // delete (reinterpret_cast<size_t*>(array) - 1);

    /* No segmentation fault (pure free, no destructor call) */
    // operator delete(reinterpret_cast<size_t*>(array) - 1);
}
```
