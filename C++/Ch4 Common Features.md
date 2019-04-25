# Chapter 4: Common Features

## 4.1: File IO

C++ has three objects defined in the STL (*Standard Template Library*) to help with accessing (*reading and writing to and from*) files in the file system. The following objects are made available in the `fstream` header.

- `fstream`: The most generic of the three objects, capable of performing both file read and file write operations, however lacks some specific features implemented only by the other objects.
- `ofstream`: Exclusively usable for file *write* and *creation* operations only.
- `ifstream`: Exclusively usable for file *read* operations.

Theoretically the workflow for interacting with files on the filesystem is as follows, no matter the platform or language used: `Open File --> Do stuff to the file --> Close File`.

The act of "*opening*" a file does two things: it initializes the file stream object (*one of the ones introduced above*) and sets a flag that prohibits other applications from making severe changes to the file, e.g. removing it. This flag is set until the file is "*closed*", which results in the changes being dumped back into the file, the un-initialization of the file stream object, and the aforementioned resetting of the file change flag. Along with this, other processes are set in motion, such as a notification sent to all processes listening for the file to be modified, but that is a more advanced topic to be discussed at a later date.

All three file stream objects implement the open/close process in nearly the same manner. That said;

### File Stream `.open()`

The fingerprint of the `.open()` function implemented for all of the file stream objects is as follows:

```C++
void open(const string& filename, ios_base::openmode mode = ios_base::in | ios_base::out);
```

Whew, let's unpack this! First is the easy part; `const string& filename`, despite how it looks, is just a simple path to the file desired to be opened. This is usually relative to the directory that the C++ file that calls this is in. The second part gets... fun.

There, we have an `ios_base::openmode` object as a parameter, but this is actually more simple than it seems. We can see that if no parameter is provided, it will default to an OR combination of the `in` and `out` type. Let's look at our options here:

| Member Constant | Stands For   | Access                                                       |
| --------------- | ------------ | ------------------------------------------------------------ |
| `in`            | **in**put    | File open for reading: the *internal stream buffer* supports input operations. |
| `out`           | **out**put   | File open for writing: the *internal stream buffer* supports output operations. |
| `binary`        | **binary**   | Operations are performed in binary mode rather than text.    |
| `ate`           | **at e**nd   | The *output position* starts at the end of the file.         |
| `app`           | **app**end   | All output operations happen at the end of the file, appending to its existing contents. |
| `trunc`         | **trunc**ate | Any contents that existed in the file before it is open are discarded. |

Figure 4.1.1: Truth table for `openmode` choices (*pulled straight from [cplusplus.com](http://www.cplusplus.com/reference/fstream/fstream/open/)*)

A couple of these are somewhat redundant, namely the `in` and `out` constants, which are implicitly taken when using the `ifstream` and `ofstream` objects respectively. Nevertheless, they all exist to be used should the desire come.

As we have already seen, these constants can be combined with the use of an OR operation (*single pipe for bitwise or: `|`. Double pipe, `||`, should also work, but that is normally used for logical operations with boolean values.*)

For example:

```C++
#include <fstream>

fstream file;
file.open("test.txt", ios::in | ios::out | ios::app); // Opens the file "./test.txt" for reading and writing. Lines written to the file will be appended to the end instead of replacing what is already there.
```

### File Stream Operations

Remember how we have used `std::cout` before? Something like: `std::cout << "This is printed to the terminal" << std::endl;`. Well, as it turns out, [the header we get that function from, `iostream`, inherits from the same base classes as the `fstream` classes](https://en.cppreference.com/w/cpp/io). What this means for us is that `fstream`s will function in a hyper-similar manner to how `std::cout` worked. For example:

```C++
//...
// Reading from `file`
std::cout << file << std::endl; // Prints the contents of the file to the terminal directly.
char data[100]; // Initialize a character array of size 100.
file >> data; // Fill `data` with the contents of the file.
std::cout << data << std::endl; // Prints the contents of the data array. (First 100 characters of the file object)

// Writing to `file`
file >> "\nThis is going on a new line.\n"; // Write a new line to the `file` object. `\n` is the escape character for a new line.
```

### File Stream `close()`

After the program has done all that it wants to do with the file stream, it then needs to release the file system resource by calling `.close()`. In comparison to the other functionality that we've looked at yet, this is pretty simple. Just call the function when done; it takes no parameters and returns nothing. For example:

```C++
//...
file.close();
```

### When to Use Which Class

As we've seen, the `fstream` object is perfectly capable of doing most tasks one would need to perform, both for writing and for reading to and from a file. However, this should only be done when it is conceivable that the program will need to do both. Most of the time, the program will only be reading from or writing to a file, in which case there are a couple of good reasons to use the more specific `ifstream` or `ofstream` objects.

1. It makes it more clear what the expected behavior of functions using the file stream object are, preventing stupid mistakes where the wrong operations are made to a file.
2. There are some more specific abilities that would require the usage of the correct object due to the fact that the `ifstream` and `ofstream` classes have more specific code and helper functions better suited to their respective roles.

## 4.2: Please `try` to Like This Part

In all honesty, the `try` block is traditionally a very useful piece of kit when there is a possibility of a segment of code producing an exception or runtime error. Many other languages have this feature, including Java, Python, JavaScript, and more. In general, despite the fact that C++ has a rather solid framework for throwing and catching exceptions, it isn't all that common to run across a behavior like this in many code bases.

People consider it messy to start throwing exceptions, especially in applications that need to continue running even if an exception is generated, due to how any uncaught exceptions will terminate the program instantly. To that effect, it is actually really difficult to create a situation where a runtime error will be thrown just by using the C++ STL. Like, really difficult.

However, throwing your own exceptions is a piece of cake. Here is an example of a `try` block in action.

```C++
#include <iostream>

double divide(double a, double b) {
  if(b == 0) throw "Cannot divide by zero."; // If the divisor is 0, we have a problem.
  else return a/b; // Else, just run the calculation.
}

int main() {
  try {
    std::cout << divide(5.0, 2.0) << std::endl; // Fine, no tripping the exception
    std::cout << divide(5.0, 2.0) << std::endl; // Error, trips the exception
  } catch(const char* error) { // Catch an exception in the form of a const char* (analogous to a String type)
    std::cout << "Error! " << error << std::endl;
  }
}
```

But even still, be aware that usage and implementation of exception throwing is highly frowned upon in many contexts and organizations. Beware.

## 4.3: Why Does This Exist`?`

All hail the immense and total power of the inline `if` statement! The `?` operator functions as a sort of inline `if` statement. Let's see if it's usage is apparent from an example:

```C++
int number = 10;
std::cout << number > 5 ? "BIG!" : "small" << std::endl;
```

The code above would print the word "BIG" to the terminal. Do you see what just happened? Let's generalize the `?` operator's usage.

`[CONDITION] ? [VAL IF TRUE] : [VAL IF FALSE]`

If the condition evaluates to true, then the result will be whatever is contained between the `?` and the `:`. Otherwise, the result will be what comes after the `:`.

This is a really powerful piece of syntax because of how it enables code to be collapsed *dramatically*. Just have a look at these two equivalent blocks of code:

```C++
int number = 10;
if(number > 5) {
  std::cout << "BIG!" << std::endl;
} else {
  std::cout << "small" << std::endl;
}

// OR
int number = 10;
std::cout << number > 5 ? "BIG!" : "small" << std::endl;
```

Which would you rather write? The latter is *significantly* shorter and more concise, resulting in faster writing of code and, arguably, easier comprehension of what will happen in the end for someone who is reading quickly. Keep this trick in mind. It's not for use everywhere, but when used appropriately, it is a GOD tool. Good places to use it are in situations like the one depicted above and in object instantiations.

## 4.4:  Fitting Square Pegs in Round Holes

Like it does in other aspects, C++ has two different methods by which to change objects between types, one of which it inherited from C and one that it established itself.

### C-Style Casting

These conversions are pretty self-explanatory:

```C++
double a = 3.14159;
int b = 123456;

double c = (double)b;
int d = (int)a;
```

In the cases depicted above, the casting occurs when an alternate type is declared within the parentheses. In the case of converting a `double` to an `int`, where there is a loss of precision due to the inability of an integer variable to hold decimal places, the double is truncated (*cut short*) at the decimal place, effectively rounding down, to make the value fit properly.

#### The Dark Side of C-Style Casts

However, nothing in life is perfect. There are [caveats to performing casts with the syntax described above](https://stackoverflow.com/a/1609185/3339274).

1. It's really hard to search for instances of a C-style cast in a code base
2. It's sometimes difficult to understand exactly what the author intended to have the cast do, especially in more advanced and obscure situations
3. C-style casts aren't checked very well by the compiler, sometimes allowing undefined behaviors to crop up, especially when casting between more complicated objects

However, these objections don't really matter for simple data types like those shown in the example above. Only caution against using C-style casts for more interesting and complicated conversions, such as those involving pointers, classes, and other objects like those.

That said...

### C++ Casting

C++ introduces four different types of casts, each for [slightly different purposes](https://stackoverflow.com/a/332086/3339274). Ordered in ascending levels of rarity and niche nature:

- `static_cast<>`
- `const_cast<>`
- `dynamic_cast<>`
- `reinterpret_cast<>`

The template parameter that these casts take (*inside the `<>`*) is the desired target type, or what would have been put within the parentheses of a C-style cast. The following explanations are paraphrased from [this Stack Overflow post](https://stackoverflow.com/a/332086/3339274), which does an excellent job explaining all of the nuances of each type of cast.

#### `static_cast<>`

`static_cast<>` is by far the most commonly used of them all. It is essentially a direct implementation of the same functionality traditionally found in a C-style cast, just without the caveats. In fact, it is so common that a lot of the time, situations where a `static_cast<>` would be appropriate are automatically handled by implicit conversions, a topic that will be covered in a bit.

It can also be used to convert classes and structs up the inheritance hierarchy, i.e. from the base class to the child class. Conversions down the ranks, i.e. from the child class to the parent class, are handled automatically, without the necessity to use a `static_cast<>`. However, since the cast is performed at compile time, only objects that are directly related through a parent-child relationship are able to be processed in this manner. Otherwise, use `dynamic_cast<>`.

#### `const_cast<>`

`const_cast<>` is arguably the simplest and most niche of them all. It's sole purpose is to remove the "constancy" (*if you will*) from an object, allowing one to be used in a non-const expression. Simple as that, for most intents and purposes.

#### `dynamic_cast<>`

The uses of this type of cast, and `reinterpret_cast<>` for that matter, are very specific and highly limited. Thus, explanation of the nuances is difficult.

The most useful ways in which to use `dynamic_cast<>` is with pointers to polymorphic objects, which is to say classes or structs that make use of inheritance (**possibly also virtual functions*) at the same time.

Take this example program: (*slightly adapted from [learncpp.com](https://www.learncpp.com/cpp-tutorial/12-9-dynamic-casting/)*)

```C++
#include <iostream>
#include <string>

class Base {
 protected:
  int m_value;

 public:
  Base(int value) : m_value(value) {}
  virtual ~Base() {}
};

class Derived : public Base {
 protected:
  std::string m_name;

 public:
  Derived(int value, std::string name) : Base(value), m_name(name) {}
  const std::string& getName() { return m_name; }
};

Base* getObject(bool bReturnDerived) {
  if (bReturnDerived)
    return new Derived(1, "Apple");
  else
    return new Base(2);
}

int main() {
  Base *b = getObject(true);

  Derived *d = dynamic_cast<Derived*>(b); // use dynamic cast to convert Base pointer into Derived pointer

  std::cout << "The name of the Derived is: " << d->getName() << '\n';
  delete b;
  return 0;
}
```

In this admittedly contrived situation, we have a `Derived` class that inherits from the `Base` class. We also have a `getObject()` function that returns a `Base*` that has the ability to point either to a `Base` object or a `Derived` object disguised as a `Base` object.

In the `main()` function, we instantiate a `Base` pointer, and then want to call the `getName()` member function implemented by the `Derived` class. Believe it or not, we have two options: both `static_cast<>` and `dynamic_cast<>` could work here. However, as it is evaluated at compile time, `static_cast<>` in this situation wouldn't provide any checks to make sure that the conversion would make sense or produce a meaningful result. This is where `dynamic_cast<>` comes in as a conversion processed at runtime, offering the opportunity to address what `static_cast<>` doesn't.

Thus, we perform a `dynamic_cast<>` to `Derived*` so we can then call the `getName()` member function. However, there's a problem with this code; with one line change to how `*b` is instantiated, the `dynamic_cast<>` will fail spectacularly, and we will end up with trying to dereference `nullptr`, a cardinal sin and runtime error generator.

If `getObject(true)` is changed to `getObject(false)`, the `Base*` that gets returned no longer actually points to an instance of a `Derived` class. That means that the `dynamic_cast<>` will fail (*by returning `nullptr`*) because it has no way of converting the `Base*` to a `Derived*`. Think about it: if you were to try to perform the conversion, how would you do it? There isn't any way to account for the fact that you'd be missing important data, namely `m_name`.

To protect against this, we change the `main()` function like so:

```C++
int main() {
  Base *b = getObject(true);

  Derived *d = dynamic_cast<Derived*>(b); // use dynamic cast to convert Base pointer into Derived pointer

  if(d != nullptr) std::cout << "The name of the Derived is: " << d->getName() << '\n';
  delete b;
  return 0;
}
```

This way, if the `dynamic_cast<>` fails, we will know about it and not try to dereference `nullptr`  when printing out the name of the `Derived` class. This check is absolutely necessary whenever using `dynamic_cast<>` to avoid dereferencing `nullptr`.

#### `reinterpret_cast<>`

To quote [a Stack Overflow post](https://stackoverflow.com/a/332086/3339274):

> `reinterpret_cast` is the most dangerous cast, and should be used very sparingly. It turns one type directly into another — such as casting the value from one pointer to another, or storing a pointer in an `int`, or all sorts of other nasty things.

This is the case because of what the `reinterpret_cast<>` actually does behind the scenes. Somewhat literally, it just acts as if the type of the original object *was* the type it's converting to, just replacing the label. As an even greater scare, this is what [another Stack Overflow user says](https://stackoverflow.com/a/43273907/3339274):

> If you don't know what `reinterpret_cast` stands for, don't use it. If you will need it in the future, you will know.

For this reason, we're not going to go into depth into this one. Heed the advice of your elders, kids.

### Implicit Conversions

Believe it or not, we have been making use of the C++ feature of implicit conversion before. It is a feature that acts in the background to help us. Like C-style casting, this behavior was inherited from C, where it was first introduced. Here's an example:

```C++
void doSomething(double value) { /* ... Do work ... */ }

doWork(5);
```

See what's happening here? The `doSomething` function wants to take in a `double` parameter, but it was passed an `int` type. The compiler then implicitly converted the `int` type to a `double` type.

If instead the syntax was trying to go the other way, say from a `double` to an `int`, the conversion would work the same, this time with the compiler truncating the `double` at the decimal point, effectively rounding down to the nearest whole number.

There are far more instances in C++ where implicit conversions appear, but this is the most common mode of operation in general.

## 4.5: Just... split the difference

This section is perhaps the most important in the entire chapter. Nearly all C++ code bases out there make use of this practice: splitting code between `.h` header files and `.cc` source files, both of the same name. (*except for the obvious difference in file extension*)

Also sometimes formatted to be `.hpp` and `.cpp` files due to how the `.h` and `.c` files are normally associated with the C language, these files each have a separate but distinct role:

- `.h` (*also `.hpp`*) files are responsible for object definitions, without the implementing code.
- `.cc` (*also `.cpp`*) files are responsible for object implementations, defined in the corresponding `.h` or `.hpp` file.

The reasons for doing this are twofold: it helps us humans read the code more easily (*which will hopefully become apparent soon once we look at how this works*) and it helps the compiler check the code for idiosyncrasies that would cause errors. [This article](http://cse230.artifice.cc/lecture/splitting-code.html) goes into depth on how this works and does a good job explaining why this is common practice in C++.

### Example file set

Here we have a simple example: (*modified a bit from the above article*)

`rectangle.h`:

```C++
#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
 public:
  double width;
  double height;

  double area();
};

#endif
```

`rectangle.cc`:

```C++
#include "rectangle.h"

double Rectangle::area() {
  return width * height;
}
```

Okey, what's going on here? Let's analyze the `rectangle.h` file more closely first.

#### Header File

The first two lines and last line, the ones with the hash symbols (*`#`*) in front, are a formality that helps the compiler deal with the possibility that the same code may be included multiple times in a code base.

For example, if instead of a rectangle class this was a math class, it is forseeable that many parts of the code may want to include this capability. Due to how the `#include` preprocessor directive (*part of the compiler*) works, it is just a straight copy and paste operation. This means that the code from the included file will just be placed verbatim in place of the `#include` call.

If unprotected from redefinition, it is possible to have multiple locations include the same file and end up with a situation where there are object redefinitions, serious errors that can screw up a code base dramatically.

So, how does it work? Any line with a hash symbol (*`#`*) in front is a preprocessor directive. These calls are processed before the compiler really gets started, hence the name *pre*processor.

`#ifndef` (*and the matching `#ifdef`*) check to see if a specific symbol is defined yet. It's the preprocessor's version of an `if` statement. Symbols are any object type or preprocessor definition. (*`#define`*)

Luckily for us in the case of this example, the preprocessor definition hasn't occurred yet. (*HINT: it's defined in the next line!*) Thus, our condition which essentially evaluates to "does `RECTANGLE_H` exist yet?" becomes true and the lines between the `#ifndef` and `#endif` lines are kept in the file. If the condition wvaluated to false, the lines in between would be omitted.

The next line with the `#define` makes sure that future includes of this file won't duplicate the code by defining the symbol used in the previous line. By convention, the symbol name is the file path relative to the root directory of the project with the slashes and periods converted to underscores and all of the characters in upper case. For example:

- `BIN_COMMON_TIME_H` for `./bin/common/time.h`
- `SRC_RX_PPMSUMD_H` for `./src/rx/ppmsumd.h`

The class definition in `rectangle.h` shouldn't be anything new with the exception of the `double area();` line. Here, the function is defined but not implemented. This is what makes this feature special, it enables the compact definition to be laid out in the header file with the implementation decided later. As it stands `area()` is un-callable because the compiler has no idea what to do with a call to the `area()` function.

#### Source File

This, however, is resolved in `rectangle.cc`. The first line is very necessary, telling the compiler that it is related to the `rectangle.h` header and implements the objects defined there.

Next comes the definition of the `Rectangle` class's `area()` function. Note the usage of the scope operator (*`::`*) that we last saw in relation to namespaces. Other than that quirk, the function definition remains the same.

### More on why

Imagine that instead of being short, the `Rectangle` class was longer. Soon, with the function definitions encapsulated in a separate file, it becomes far easier to read and understand what the class does just by reading the header file. This is one of the most important reasons why this practice is so universal.

## 3.6: Build Systems

Up until this point, we've been using [`g++`, a part of the GCC (*GNU Compiler Collection*)](https://gcc.gnu.org/) to compile and run our C++ code. However, there are several other options, namely [`clang`](http://clang.llvm.org/) which despite the odd sounding name (*literally abbreviated for C-language*) is very powerful.

There also exist more complicated build systems that automate much of the tedious work that is necessary when working with `g++` or `clang` on their own, which for the most part require each piece of the code base to be compiled separately.

Arguably, the most popular C++ build systems in the wild are [CMake](https://cmake.org/), [Ninja](https://ninja-build.org/) and [Bazel](https://bazel.build/) in ascending order of complexity. Many of such build systems are also compatible with other mainstream programming languages. For example, Bazel is compatible with Java, C++, Android, iOS, Go and many more development tools.

This section will introduce both CMake and Bazel.

### The humble build file

Both CMake and Bazel, as well as many other build systems, make use of so called "build files" to tell the compiler what it needs to do in order to successfully assemble the project. These "build files" are placed one per directory of the project. CMake uses `CMakeLists.txt` files, while Bazel uses `BUILD` files. Both have different methods of formatting, but they both accomplish the same task.

Within build systems, there are two types of compilable objects (*called targets*) that can be declared in build files: executables and libraries. Executables are runnable outputs, the same idea as the outputs we've been generating with `g++`, compiled into binaries. Libraries are a more complicated topic, but these are compilable outputs that need to be implemented within an executable to be used.

Technically, the difference between executables and libraries is that executables have an entry point and libraries don't. Entry points are where the program begins to run, which in C++ is the `main()` function. Only executable targets with an entry point (*and only one*) may be run directly.

Executables are the most common kind of output to generate in C++, so we're only going to discuss those. Feel free to look up how to compile dynamic libraries with CMake and Bazel on your own prerogative.

### CMake

CMake, an open source build system from Kitware, is where we will start.

First, like with `g++`, we must first acquire and install CMake from the internet. Fortunately, [CMake's download page](https://cmake.org/download/) provides installers for most operating systems. On Linux, CMake can be obtained via the package manager, usually accessible by the name `cmake`.

An excellent getting started tutorial for CMake already exists on [riptutorial.com](https://riptutorial.com/cmake). The following example will be paraphrased from there.

The first step is to make a simple project to build. (*DUH!*) Let's practice multi-file projects.

`main.cc`:

```C++
#include "foo.h"

int main() {
  foo();
  return 0;
}
```

`foo.h`:

```C++
#ifndef FOO_H
#define FOO_H

void foo();
#endif
```

`foo.cc`:

```C++
#include <iostream>
#include "foo.h"

void foo() {
  std::cout << "Hello World!" << std::endl;
}
```

Alright, that was pretty simple. Now let's looks at the associated `CMakeLists.txt`.

`CMakeLists.txt`:

```CMake
cmake_minimum_required(VERSION 2.4)

project(hello_world)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(app main.cc foo.cc)
```

So, here we go... The first line just sets the minimum version of `cmake` that must be installed to run this build script. No fancy stuff here, just some configuration details.

The second line is where things start to matter. `project(hello_world)` declares a new CMake project called "hello_world". For the most part, this name doesn't matter. Just make it understandable and reasonable.

The third line then sets and include directory. This is where the compiler will look for the header files requested in the C++ files. For now, the only include directory is the root of the project, which is accessible in the build file with the `$(PROJECT_SOURCE_DIR)` variable.

And finally, the last line, sets up the executable that will be output at the end of compilation. The first parameter, `app`, sets the name of the output binary and the secondary parameters, `main.cc` and `foo.cc` set up the C++ source files that must be compiled to create the binary. Note that there must be one and only one `main()` function in all of the source files included in this list. A separate executable must be instantiated to support another entry point.

Now, to use this build file and compile the project, let's use the `cmake` command. There's actually a few required steps:

```shell
$ mkdir build                   # Create a new directory for intermediate build files, only do this once
$ cmake -E chdir build cmake .. # Tell CMake to generate the build environment, only run this after changing "CMakeList.txt" files
$ cmake --build build           # Tell CMake to compile the project
$
```

After running the last command, a binary file will be available to run in the `./build` directory. The name of the executable will be the same as the one set in the `CMakeList.txt` file, in our case, `app`. So...

```shell
$ # Continue from the previous section
$ ./build/app
Hello World!
$
```