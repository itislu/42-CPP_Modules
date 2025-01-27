# CPP04 - Table of Contents

| Exercise     | Name       | Learnings                                                                                                                                                                                                                                                  |
| ------------ | ---------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| [ex00](ex00) | 🐾 Animal  | - Subtype polymorphism                                                                                                                                                                                                                                     |
| [ex01](ex01) | 🧠 Animal  | - Deep copy vs. shallow copy                                                                                                                                                                                                                               |
| [ex02](ex02) | 💭 Animal  | - Abstract classes                                                                                                                                                                                                                                         |
| [ex03](ex03) | 🔮 Materia | - Interfaces, <br> - Value-initialization of arrays, <br> - Copy-and-swap idiom, <br> - Move semantics, <br> - Templates and template specialization, <br> - Overloading `new` and `delete`, <br> - Dynamic dispatch, vTable and vPtr, <br> - Dynamic cast |

# Resources

### Copy-and-Swap Idiom

The main benefit of the copy-and-swap idiom is that it provides strong exception guarantee.
In the copy assignment operator, this means that all operations which could throw an exception (the copying) are made before the object being assigned to gets changed.

It also helps to reuse code because assignment essentially boils down to deletion of the original value and copying over the new value.
This idiom allows us to reuse the copy constructor and the destructor because of that fact.

It works by:
1. Taking the argument by value (which creates a copy using the copy constructor).
2. Swapping the contents of *this with the parameter (which mustn't throw).
3. Letting the destructor clean up the old data when the parameter goes out of scope.

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
