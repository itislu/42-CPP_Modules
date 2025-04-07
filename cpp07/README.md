# CPP07 - Table of Contents

"Only after overload resolution has chosen a function template will any explicit specializations be considered." - High Integrity C++ Coding Standard 2013

ADL (argument-dependent lookup) - "ADL is the reason behind the established idiom for swapping two objects in generic code:using std::swap; swap(obj1, obj2); because calling std::swap(obj1, obj2) directly would not consider the user-defined swap() functions that could be defined in the same namespace as the types of obj1 or obj2, and just calling the unqualified swap(obj1, obj2) would call nothing if no user-defined overload was provided. In particular, std::iter_swap and all other standard library algorithms use this approach when dealing with Swappable types." - https://en.cppreference.com/w/cpp/language/adl

https://youtu.be/nfIX8yWlByY - C++ Function Templates: How Do They Really Work? - Walter E. Brown [C++ on Sea 2019]

http://www.gotw.ca/publications/mill17.htm - Why Not Specialize Function Templates?

Tag Dispatch vs SFINAE
