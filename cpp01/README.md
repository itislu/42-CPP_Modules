# CPP01 - Table of Contents

| Exercise     | Name          | Learnings                                                                         |
| ------------ | ------------- | --------------------------------------------------------------------------------- |
| [ex00](ex00) | 🧟 Zombie     | - Constructor & Deconstructor                                                     |
| [ex01](ex01) | 🧟 Horde      | - Array allocation on heap                                                        |
| [ex02](ex02) | 🧠 Brain      | - References and their memory address                                             |
| [ex03](ex03) | 🪓 Weapon     | - References in a class                                                           |
| [ex04](ex04) | 📄 sed        | - `string` methods, <br> - `string` performance optimization, <br> - File streams |
| [ex05](ex05) | 😡 Harl       |                                                                                   |
| [ex06](ex06) | 🤬 HarlFilter | - `switch` statement                                                              |

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
    // delete (array - 1);

    /* No segmentation fault (pure free, no destructor call) */
    // operator delete(array - 1);
}
```
