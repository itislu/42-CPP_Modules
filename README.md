# Table of Contents

- [**📚 Resources**](#-resources)
- [**⚙️ Automatic labels of your commits for CPP modules monorepo**](#%EF%B8%8F-automatic-labels-of-your-commits-for-cpp-modules-monorepo)

---

# 📚 Resources

| Description                                                                                                                                                                            | Type                          | Link                                                                                                                                   |
| -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ----------------------------- | -------------------------------------------------------------------------------------------------------------------------------------- |
| **Learn C++** <br> A site with well structured lessons for absolute beginners. Goes over all concepts.                                                                                 | ~300 short Lessons            | [learncpp.com](https://www.learncpp.com)                                                                                               |
| **C++ Overview using the C++98 Standard** <br> One of the few tutorials using the C++98 standard.                                                                                      | ~ 25 medium length Articles   | [cplusplus.com](https://cplusplus.com/doc/oldtutorial/)                                                                                |
| **C++ Super-FAQ** <br> A great FAQ about C++ ranging from newbie questions, learning C++ when coming from C, basic and advanced features of C++, coding standards to language updates. | FAQ (100s of questions)       | [isocpp.org](https://isocpp.org/faq)                                                                                                   |
| **C++ Core Guidelines written by Bjarne Stroustrup himself** <br> Very useful to read about certain features of the language and for best practices, dos and don'ts.                   | Knowledge Base (~25 sections) | [isocpp.github.io](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)                                                       |
| **42 Intra eLearning Videos** <br> Teaches the concepts needed for all modules. One video for each concept.                                                                            | ~40 Videos                    | [elearning.intra.42.fr](https://elearning.intra.42.fr/tags/38/notions)                                                                 |
| **Harvard C++ Quick Overview over New Features compared to C** <br> Concise introduction to C++ concepts with really clear code examples.                                              | 1 Article                     | [read.seas.harvard.edu](https://read.seas.harvard.edu/cs161/2021/doc/cplusplus/)                                                       |
| **C++ tutorial for C users** <br> A tutorial for C programmers who wish to learn C++, showing basic principles of C++. Lots of small code snippets.                                    | 1 Article                     | [ericbrasseur.org](http://www.ericbrasseur.org/cppcen.html)                                                                            |
| **C++ for C Programmers - University of California, Santa Cruz** <br> A university professor goes over the benefits of C++ compared to C in a slow and easy to understand way.         | Video (8h 44min)              | [youtube.com](https://www.youtube.com/watch?v=Mkg2fpKD1KI)                                                                             |
| **C++ Programming Wikibook** <br> Easy to read, Wikipedia-style book. Great start when researching a new concept or feature.                                                           | Online-Book <br> (~650 pages) | [wikibooks.org](https://en.wikibooks.org/wiki/C%2B%2B_Programming)                                                                     |
| **A Tour of C++ - Book** <br> A short book that serves as an overview of all of standard C++, written by Bjarne Stroustrup.                                                            | Book <br> (~200 pages)        | [PDF](https://github.com/Kikou1998/textbook/blob/master/A%20Tour%20of%20C%2B%2B%20(2nd%20Edition)%20(C%2B%2B%20In-Depth%20Series).pdf) |
| **C++ Primer (5th Edition) - Book** <br> In-depth tutorial and reference book.                                                                                                         | Book <br> (~900 pages)        | [PDF](https://github.com/yanshengjia/cpp-playground/blob/master/cpp-primer/resource/C%2B%2B%20Primer%20(5th%20Edition).pdf)            |
| **The C++ Programming Language - Book** <br> Hardcore reference book written by Bjarne Stroustrup.																					 | Book <br> (~1300 pages)       | [PDF](https://chenweixiang.github.io/docs/The_C++_Programming_Language_4th_Edition_Bjarne_Stroustrup.pdf)				              |
| **C++ Weekly With Jason Turner** <br> Weekly videos about C++ (and Computer Science in general).                                                                                       | 400+ short-form Videos        | [youtube.com](https://www.youtube.com/@cppweekly)                                                                                      |

---

# ⚙️ Automatic labels of your commits for CPP modules monorepo

This alias automatically puts the numbers of the current CPP module and the current exercise at the very front as the scope of the commit. The numbers are extracted from the current directory.

**Example:**<br>
You are in the directory `cpp00/ex00` -> the scope would be `00/00`.

The alias also conveniently formats your commit messages according to the [Conventional Commits](https://www.conventionalcommits.org/) - first a keyword, then the message.<br>
It puts the first argument as the type of the commit, everything else as the message. The type is usually one of the following: `feat`, `fix`, `refactor`, `style`, `test`, `docs`, `chore`. The message is a short description of the commit.

### Usage

This is how you can use the alias:

```bash
git cmm feat Convert program arguments to uppercase
```

**Result:**

```
[00/00] feat: Convert program arguments to uppercase
```

### Setup

To set this alias up just for your CPP repository (so not globally across all repositories), run the following command:

```bash
git config alias.cmm '!f() {
    local exercise_path=$(echo "$GIT_PREFIX" | sed '"'"'s/^..\///'"'"' | grep -oE '"'"'.*(/|^)ex[0-9]{2}(/|$)'"'"');
    local module=$(dirname "$exercise_path" | xargs basename | sed '"'"'s/^\.$//'"'"');
    local exercise=$(basename "$exercise_path");
    if [ -z "$module" ] && [ -z "$exercise" ]; then
        module=$(basename "$GIT_PREFIX");
    fi;
    local module_num=$(echo "$module" | grep -oE '"'"'[0-9]+'"'"');
    local exercise_num=$(echo "$exercise" | grep -oE '"'"'[0-9]{2}'"'"');
    local type=$1;
    shift;
    local message="$@";
    local scope="";
    if [ -n "$module_num" ] && [ -n "$exercise_num" ]; then
        scope="[$module_num/$exercise_num] ";
    elif [ -n "$module" ]; then
        scope="[$module] ";
    elif [ -n "$exercise" ]; then
        scope="[$exercise] ";
    fi;
    git commit -m "$scope$type: $message";
}; f'
```

## Pre-populate the scope in the commit message file

If you prefer to use `git commit` to edit your commit messages in your editor, you can use a git hook to automatically pre-populate the scope in the commit message file.

This means when you `git commit`, the file that opens already has the scope of your commit in the first line.

### Setup

1. **Make sure you are in the root of your repository.**

2. Run the following command:
   ```bash
   cat << 'EOF' >> .git/hooks/prepare-commit-msg
   #!/bin/sh

   COMMIT_MSG_FILE=$1
   COMMIT_SOURCE=$2
   SHA1=$3

   # Remove the "# Please enter the commit message..." help message.
   /usr/bin/perl -i.bak -ne 'print unless(m/^. Please enter the commit message/..m/^#$/)' "$COMMIT_MSG_FILE"

   # Only use if it's a regular commit without -m or -F
   case "$2,$3" in
   	,|template,)
   		# Prepend the scope to the commit message file
   		exercise_path=$(echo "$GIT_PREFIX" | sed 's/^..\///' | grep -oE '.*(/|^)ex[0-9]{2}(/|$)')
   		module=$(dirname "$exercise_path" | xargs basename | sed 's/^\.$//')
   		exercise=$(basename "$exercise_path")
   		if [ -z "$module" ] && [ -z "$exercise" ]; then
   			module=$(basename "$GIT_PREFIX")
   		fi
   		module_num=$(echo "$module" | grep -oE '[0-9]+')
   		exercise_num=$(echo "$exercise" | grep -oE '[0-9]{2}')
   		scope=""
   		if [ -n "$module_num" ] && [ -n "$exercise_num" ]; then
   			scope="[$module_num/$exercise_num] "
   		elif [ -n "$module" ]; then
   			scope="[$module] "
   		elif [ -n "$exercise" ]; then
   			scope="[$exercise] "
   		fi
   		sed -i "1i$scope" "$COMMIT_MSG_FILE"
   		;;
   	*) ;;
   esac
   EOF
   chmod +x .git/hooks/prepare-commit-msg
   ```
