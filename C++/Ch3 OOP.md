# Chapter 3: OOP

## 3.1: Arrays and `std::vector`

These tutorials haven't covered arrays until now because the intention was to provide an understanding of how arrays are actually structured in system RAM so as better to contrast them with how dynamic structures like `std::vector` differ. That said, Chapter 2 was all about memory, so we are now equipped to discuss them.

Arrays have a self-explanatory name; they are data structures that contain a "list" of data of the same type. For example, one could create an array of integers, or an array of doubles, or an array of `std::string`s, et cetera. The catch with arrays is that they cannot be expanded or contracted once instantiated, meaning that the size defined at instantiation sticks with the array for the entirety of its life cycle. (*until deleted*) 

### Arrays in RAM

Arrays are stored in system RAM as a contiguous block, long enough to store the desired number of elements. For example, bringing back the hypothetical 8-bit computer from last chapter, this is what a hypothetical 4-element long integer array could look like in RAM.

|                         Address | Data     |
| ------------------------------: | :------- |
|                        00000000 | 10001100 |
|                        00000001 | 01010010 |
| Element 1: (*index 0*) 00000010 | 01000100 |
| Element 2: (*index 1*) 00000011 | 01101000 |
| Element 3: (*index 2*) 00000100 | 00100100 |
| Element 4: (*index 3*) 00000101 | 00010000 |
|                        00000110 | 01111010 |
|                        00000111 | 00011110 |

Figure 3.1.1: Depiction of system RAM structure with an integer array

It is for the reason that arrays must occupy contiguous memory spaces that arrays have a fixed size once defined.

### Classic C-style Arrays

C++ inherits native support for arrays from it's predecessor, C. C-style arrays can be instantiated like so:

```C++
int nums[10];
// OR
double doubles[] = {1.2, 3.14, 6.28};
// etc.
```

The first example just creates an empty array of integers 10 elements in length, and the second example initializes an array of doubles three elements in length, initially filled with the numbers 1.2, 3.14, and 6.28. Once initialized, elements can be accessed like so:

```C++
// Continuation of previous sample...
nums[0] = 10;
nums[3] = 400;
nums[2] = 404;

doubles[0] = 3.14159;
std::cout << doubles[1] << std::endl;
```

Note that array indices begin at zero, meaning that the last the last element in the array is located at index length - 1. Square brackets, `[]`, are used to specify which index data should be read from or written to. Getting the length of a C-style array is a [surprisingly difficult endeavor](https://stackoverflow.com/q/4108313/3339274), involving the following syntax:

```C++
// Continuation of previous sample...
std::cout << "Size of doubles array: " << sizeof(doubles)/sizeof(doubles[0]) << std::endl;
```

`sizeof` is syntax directly inherited from ancient C, with which C++ was intentionally designed to be forwards compatible with. For this reason, (*and a few others*) most programmers now [recommend using `std::array` instead, which has a far more usable API, for applications that don't require the multi-dimensional capabilities of C-style arrays](https://stackoverflow.com/q/6111565/3339274). For that reason, we'll be returning to these types of arrays when we discuss multi-dimensional data structures.

### `std::array`

The same basic principles of C-style arrays apply to the implementation of `std::array`, introduced as a part of C++11. Here are the same examples from above, slightly modified to work with `std::array`. Note that the [`array`](https://en.cppreference.com/w/cpp/container/array) header must be included to use these.

```C++
std::array<int, 10> nums;
std::array<double, 3> doubles = {1.2, 3.14, 6.28};

nums[0] = 10;
nums[3] = 400;
nums[2] = 404;
doubles[0] = 3.14159;

std::cout << doubles[1] << std::endl;
std::cout << "Size of doubles array: " << doubles.size() << std::endl;
```

Much cleaner! Note that `std::array` makes use of two template, (*which we covered last chapter*) one for the type that the array will hold and another (*this time a template parameter, not type*) which defines the length of the array.

A new type of `for` loop called the for-each loop is available for iterating through the elements in the array:

```C++
for(double val : doubles) {
  std::cout << val << std::endl;
}
```

as opposed to the other, more traditional, manner for iterating through an array:

```C++
for(int i = 0; i < doubles.size(); i++) {
  std::cout << doubles[i] << std::endl;
}
```

which is just generally less concise and clean. However, as hinted at by the syntax, the for-each loop cannot be used to modify the contents of the array, as the newly created object is distinct and not linked with its respective element in the array.

The primary limitation of arrays, C-style or `std::array`, still remains though; the size of the array cannot be changed, increased or decreased. That is, unless you use a `std::vector`...

### `std::vector`

`std::vector` works in a hyper-similar manner to `std::array`, with the primary upgrade being that the size of the list isn't fixed. Like `std::array`, `std::vector` requires an extra header to be included, in this case, [`vector`](https://en.cppreference.com/w/cpp/container/array). However, the exact syntax used does differ somewhat.

```C++
std::vector<int> nums;
std::vector<double> doubles = {1.2, 3.14, 6.28};

nums.push_back(10);
nums.push_back(400);
nums.push_back(404);
doubles[0] = 3.14159;

std::cout << doubles[1] << std::endl;
std::cout << "Size of doubles array: " << doubles.size() << std::endl;

std::cout << "Elements in doubles array" << std::endl;
for(double val : doubles) {
  std::cout << val << std::endl;
}
```

More functions are available to be called of a vector class, which can be found by visiting the [cppreference.com page for `std::vector`](https://en.cppreference.com/w/cpp/container/vector), like `.clear`, `.erase`, `.insert` and more.

### Multidimensional Arrays

As promised, we're going to be revisiting ye' old C-style arrays for the purposes of learning about multidimensional arrays. These aren't all too common in C++, hence the less than stellar framework of C++ styled implementations like those that exist for single-dimension arrays. In fact, most of the time, when dealing with multi-dimensional data, it is preferred to use a specialized vector and matrix library like [Armadillo](http://arma.sourceforge.net/), [blaze](https://bitbucket.org/blaze-lib/blaze) or the vastly more popular [eigen](https://github.com/eigenteam/eigen-git-mirror). However, it is sometimes useful to be able to use native multidimensional arrays, so here we go.

```C++
// Defining multidimensional arrays
int nums[3][3][3];
double nums2[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

nums[0][1][2] = 10;
nums[1][2][3] = 999;
nums[3][2][1] = 314;

std::cout << nums2[1][0];
// etc.
```

Each dimension of the array is specified in its own set of square brackets, for as many dimensions as desired, although the syntax becomes more and more cumbersome with each additional dimension. Note that the size of the array MUST be provided within the square brackets at initialization, even in the case of immediate specification of data like in the case of `nums2`. Again, these aren't a very common occurrence in day-to-day C++ programming, so dealing with the specifics of syntax and usage when the application comes isn't a bad solution.

## 3.2: Delving deeper into Classes

In the previous chapter, we briefly discussed the constructor and destructor member functions, but only made use of the destructor to free the memory associated with the linked list when the `SinglyLinkedList` was destroyed. We're going to talk about them, as well as some more fun class-related information now.

### Constructors and Destructors

As alluded to before, both the constructor and destructor have the same name as the parent class and no return type. *i.e.*

```C++
class Test {
 public:
  // Test Class Constructor
  Test(int num) {
    number = num;
  }
  
  // Test Class Destructor
  ~Test() {
    // Nothing really to do here, no heap objects to free
  }
 private:
  int number;
};
```

As used in the previous chapter, the sole purpose of destructors is to clean up member objects that wouldn't normally be freed in a regular destruction, usually only heap objects. The role of constructors is to set up the class to be used before any other methods are called. The constructor is automatically called when instantiating a class. For example:

```C++
Test test = Test(7);
//OR
Test test2(5);
```

The parameters to the class instantiation are passed onto the constructor, which does its thing to set up the class, usually stuff along the lines of initializing member objects, before other member functions can be called.

### Constructor Member Initializer Lists

Say we wanted to create a class with a member instance of the `Test` class we just defined. However, the `Test` constructor requires a parameter, so we need to feed it one when the instance is created. We might start by trying to write this:

```C++
class MyClass {
 public:
  MyClass(int num) {
    test(num);
  }
 private:
  Test test;
};
```

but this code results in two errors, one when the constructor parameter isn't provided for `Test test` and another when `test(num)` is run because the constructor cannot be called after the class is instantiated. This is because the code above roughly translates into this:

```C++
Test test;
test(num);
```

We can address this with something called a constructor member initializer list. They allow us to instantiate classes and provide definitions to member objects before they are created. Here is an example:

```C++
class MyClass {
 public:
  MyClass(int num) : test(num) {}
 private:
  Test test;
};
```

In the code above, the colon represents the start of the constructor member initializer list, and here we can call the `Test` class constructor. This results in the test object being instantiated with the value `num` passed in.

These are also very handy when dealing with constants. Like classes, `const` variables can only be set once, at definition. This means that:

```C++
const int thing;	// Compiler Error: no value provided
thing = 10;			  // Compiler Error: const variables cannot be modified after definition
```

but, now we have a way of resolving this issue in classes with a constructor member initializer list:

```C++
class MyClass {
 public:
  MyClass(int num) : test(num), constant(num) {}
 private:
  Test test;
  const int constant;
};
```

### Function Overloading and Default Parameters

Function Overloading is a fun and useful feature that allows us to define multiple functions with the same name but with different parameters. Normally, if two functions with the same name exist in the same scope, the compiler throws a fit:

```C++
void thing() {
  //...
}

void thing() { // Compiler Error: function redefinition isn't allowed
  //...
}
```

However, if they have different parameters...

```C++
void thing() {
  //...
}

void thing(int num) {
  //...
}
```

then there isn't any issue. This practice is called function overloading. It is useful for when there is a need for two different versions of a function that would do the exact same thing, just with slightly different outputs. When the function is called, the compiler will look for the best fit function of the bunch to call based on the parameters passed in. There is no practical limit to how many times a function can be overloaded.

Default parameters are very similar to function overloading. In this, parameters are given a default value that they will be set to if a value isn't provided. For example:

```C++
void thing(int num = 404) {
  //...
}
```

In this case, if `thing()` is called, then the function will proceed assuming that `num` equals 404. Otherwise, `num` takes on the value passed in. In the case where multiple parameters are required to a function call, the default parameters must come last:

```C++
void thing(double decimal, int integer, int num = 0) {
  //...
}
```

The reason why becomes apparent considering the above scenario. If the `integer` and `num` parameters were switched, and `thing(3.14, 10)` was called, how would the compiler be able to decide which the programmer meant?

- `thing(decimal = 3.14, N/A, integer = 10)`
- `thing(decimal = 3.14, num = 10, ??)`

The first option seems okay, but the second should result in a syntax error, and both would likely result in wildly different results.

### Special  loop  syntax

Another important but small bit of information to be had regards the `break` and `continue` keywords. These are applicable in loops, like the `for` and `while`, as well as in a couple other situations.

#### `break`

Break is applicable in loops as well as the `switch` block. Let's look at its use in loops first.

```C++
for(int i = 0; i < 10; i++) {
  std::cout << i << std::endl;
  if(i == 4) break;
}
```

Running this block of code would print out the numbers 0-4 each on separate lines. The loop could iterate until i == 10, but the loop is cut short when i == 4 because the `break` command is issued, breaking out of the loop right there. This is useful when a loop needs to be exited, but the `return` keyword shouldn't be issued.

The other use of `break` is in a `switch` block. These are like an extended if-else if-else if-else block all smooshed into one, but it is only applicable for equal boolean expressions. (*==*) What this means is that the condition, if written into an if statement must have an equal comparison as the only logical operation. For example:

```C++
int value = 4;
switch(value) {
	case 0:
		// Do thing 1
		break;
	case 1:
		// Do thing 2
		break;
	case 2:
		// Do thing 3
		break;
	case 5:
		// Do thing 4
		break;
	default:
		// Do thing 5
		break;
}
```

which is equivalent to

```C++
if(value == 0) {
  // Do thing 1
} else if(value == 1) {
  // Do thing 2
} else if(value == 2) {
  // Do thing 3
} else if(value == 5) {
  // Do thing 4
} else {
  // Do thing 5
}
```

Much more concise, amirite? In the `switch` block,, the `break` statement serves to break execution out of the switch block after the code associated with the proper case is complete. If the `break` wasn't there, every case afterward would also be executed. For example, if case 2 was run, case 5 and the default case would also run, usually an undesirable behavior.

#### `continue`

The `continue` statement is pretty much only useful in `for` loops. Consider the following example:

```C++
for(int i = 0; i <= 10; i++) {
  if(i % 2 == 0) continue;
  else std::cout << i << std::endl;
}
```

The above code would output the following:

```shell
$ g++ test.cc && ./a.out
1
3
5
7
9
$ 
```

Any guesses as to what the `continue` statement does? Vote now! 

Time's up! The correct answer is: the `continue` statement skips the rest of the code in the for loop and re-evaluates the condition. In laymen's terms, the `continue` statement jumps back to the top of the loop.

This is useful if certain iterations in a loop shouldn't be run, but the loop needs to continue running.

### Access Specifiers

Notice that we've been putting the keywords `public:` and `private:` into our classes to delineate which member functions and objects can be accessed from where. Well, there's a third access specifier in C++, called `protected:`. Here's what they all do:

- `public:` Accessible from anywhere: inside the class, in derived  classes, from the outside
- `private:` Only accessible from inside the class
- `protected:` Hybrid of the above two: accessible from inside the class and in derived classes

Child classes have to do with class and struct inheritance, a fun topic in its own right.

### Class Inheritance

A principal feature of OOP is what's called [polymorphism](https://en.wikipedia.org/wiki/Polymorphism_(computer_science)), which includes the ability for objects to inherit properties from others. Classes and structs are the posterchildren of this feature. For example, say I have a rectangle class:

```C++
class Rectangle {
 public:
  Rectangle(int length, int width) {
    length_ = length;
    width_ = width;
  }
  
  int getArea() {
    return length * width;
  }
 private:
  int length_;
  int width_;
};
```

and I want to make a square class. One could write all of this from scratch, or one could also just do this:

```C++
class Square : public Rectangle {
 public:
  Square(int length) : Rectangle(length, length) {}
};
```

and be able to use the `Rectangle` class's `getArea()` member function. The `: public Rectangle` is the part that claims inheritance from the `Rectangle` class, with the `public` being the maximum access specifier that member functions and objects in the base class can have in the child class; `protected` and `private` are also acceptable access specifiers here. Next up, we see that the rectangle class's constructor is called in a member initializer list. This piece is responsible for the instantiation of the rectangle class.

[This cplusplus.com tutorial](http://www.cplusplus.com/doc/tutorial/inheritance/) goes over inheritance in a far greater depth.

### Interfaces

An interface is a special type of class that creates a blueprint for other classes to be based upon. It creates a set of "virtual" functions that should (*and sometimes must*) be implemented by derived classes, for these virtual functions don't contain a full implementation or any code at all. For example:

```C++
class Quadrilateral {
 public:
  Quadrilateral(int side1, int side2) {
    side1_ = side1;
    side2_ = side2;
  }
  
  virtual int getArea() {
    return side1_ * side2_;
  }
 private:
  int side1_;
  int side2_;
};
```

is an example of an interface, Note how `getArea()` is defined as virtual, a hint to programmers inheriting from this class that they might need to reimplement the function. However, the derived class doesn't need to override the `getArea()` function unless this is written:

```C++
class Quadrilateral {
 public:
  Quadrilateral(int side1, int side2) {
    side1_ = side1;
    side2_ = side2;
  }
  
  virtual int getArea() = 0;
 private:
  int side1_;
  int side2_;
};
```

because now, `getArea()` is defined as being pure virtual, meaning that the function actually doesn't exist until the derived class implements the function. As soon as a class or struct has at least one pure virtual function in it, it is then called an abstract class or struct. In fact, abstract classes and structs are barred from ever being instantiated by themselves, since their functionality is seriously hampered by the pure virtual functions

Again, [this cplusplus.com tutorial](http://www.cplusplus.com/doc/tutorial/polymorphism/) goes into far greater depths into interfaces and abstract classes.

## 3.3:  Enumerations

While not being a super crucial type in C++, when enumerations are applicable, they make what they do SO damn easy and easy to read. For that reason alone, they are worth knowing about.

Fundamentally, enumerations are just an integer variable, but the façade they put up on the front end makes dealing with states so much easier. Say we wanted a class to keep track of what state it was in . (*e.g. processing data, saving data to a file, reading data from a file, et. cetera*) We could just create an integer member variable and assign meaning to each number, (*e.g. -1 means an error occurred, 0 means doing nothing, 1 means reading, 2 means writing, et. cetera*) but that would get clunky over time, and it wouldn't be immediately obvious just from reading the code that that is what is happening.

Instead, we could declare an enumeration and use it instead. For example:

```C++
enum class State {WORKING, STOPPED, ERROR};
State state = State::ERROR;
```

creates an enumerated class that has possible states `State::WORKING`, `State::STOPPED`, and `State::ERROR`. The `enum class` line creates the class, the blueprint for the enumeration, and the `State state` line creates the object `state` that can be set and read.

Performing a comparison against the state of an enumeration is easy:

```C++
if(state == State::Stopped) { /*...*/ }
```

## 3.4: Lambdas and Function Pointers

Function pointers are another very interesting feature in C++ that allows functions to be passed around as objects. This is especially useful for systems like timers where the program might want the timer to run a bit of code when the timer expires, or other systems where so called "callback" functions are applicable. Function pointers are handled by the `std::function<TYPE(PARAMS...)>` object, contained in the header `functional`. A function pointer can be created from a properly defined function like so:

```C++
void doSomething(int num) {
  //...
}

std::function<void(int)> callback = doSomething;
```

Note that the template type must match the return type and parameter type list of the function it stores. Then, the function can be called like so:

```C++
callback(1234);
```

However, another method for creating function pointers exists: anonymous functions. Also called lambdas, these are a [common concept in many object-oriented languages](https://en.wikipedia.org/wiki/Anonymous_function), allowing functions to be declared without a given name for s specific use. Here's an example of lambda syntax:

```C++
[CAPTURE](PARAMS) {/* CODE */}
```

The parameters and code areas are pretty self explanatory, but what's a capture? Well, captures allow for certain aspects of the current scope to be, well, captured into the lambda. For example, if an object in the surrounding scope is imperative to the operation of the lambda, then that object can be captured in the lambda. An example of a lambda with a capture is as follows:

```C++
int state = 4;
std::function<void()> callback = [state]() {
  if(state > 2) std::cout << "yay, the state is greater than two!" << std::endl;
  else std::cout << "Oh no, the system broke..." << std::endl;
}

// Much later...
callback();
```

Now, there are a couple different methods that can be used for lambda captures:

- Capture by value: *The value of the captured object is recorded and used at the point in time when the lambda is **defined***
- Capture by reference: *The value of the captured object is recorded and used at the point in time when the lambda is **executed***

An excellent demonstration of this behavior can be found on [crascit.com](https://crascit.com/2015/03/01/lambdas-for-lunch/):

```C++
int x = 5;

auto copyLambda = [x](){ return x; };		// Capture by value
auto refLambda  = [&x](){ return x; };  // Capture by reference

std::cout << copyLambda() << std::endl;
std::cout << refLambda()  << std::endl;
x = 7;
std::cout << copyLambda() << std::endl;
std::cout << refLambda()  << std::endl;
```

The above code produces the following output:

```shell
$ g++ ./test.cc && ./a.out
5
5
5
7
$
```

As you can see, the value captured by the reference capture lambda changed by the time it was executed for a second time, while the value capture lambda didn't.

### `this` capture and capture defaults

Lambda captures can contain more than just object names. There are three special capture tools to help make capture syntax more readable:

- `this`: Capture everything in the current class (*therefore only applicable form within a class*) by value (*not allowed to capture `this` by reference*)
- `=`: Capture all objects in the current scope by value
- `&`: Capture all objects in the current scope by reference

Once again, [crascit.com](https://crascit.com/2015/03/01/lambdas-for-lunch/) has a very nice example code block to demonstrate this:

```C++
class Foo {
  int x;
 public:
  Foo() : x(10) {}

  void bar() {
    // Increment x every time we are called
    auto lam = [this](){ return ++x; };
    std::cout << lam() << std::endl;
  }
};

Foo foo;
foo.bar(); // Outputs 11
foo.bar(); // Outputs 12

int x = 10;
int y = 14;
auto lam1 = []()       { return 24; };  // OK: capture nothing
auto lam2 = [=]()      { return x+y; }; // OK: copy x, copy y
auto lam3 = [&]()      { return x+y; }; // OK: reference x, reference y
auto lam4 = [=, &x]()   { return x+y; }; // OK: reference x, copy y
auto lam5 = [&, x]()    { return x+y; }; // OK: copy x, reference y
auto lam6 = [&x, =]()   { return x+y; }; // Error: default must be first
auto lam7 = [=, x]()    { return x+y; }; // Error: both specify copy x
auto lam8 = [=, this]() { return x+y; }; // Error: both specify copy this
auto lam9 = [&, &x]()   { return x+y; }; // Error: both specify reference x
```

The `auto` keyword used here is another useful tool that allows the programmer to have the compiler decide what type the object needs to have, a capability best used sparingly because of the ambiguity it creates in the code for other humans. As demonstrated in the above sample, a multiplicity of captures can be utilized to specify exactly what should be captured and how.

Many programmers make the argument that such "catch all" captures should be used sparingly, an not without necessity because of how they often result in unnecessary objects being captured, wasting memory space and processor cycles, a highly undesirable effect on systems with a speed or memory space crunch. But frankly, with the speed of modern computers, it really doesn't smatter in most cases.

## 3.5: Threading

Every program, application, script, etc. on a computer when executed launches one (*or more*) "thread"s of execution. Each thread operates pseudo-independently from one another, only sharing resources when explicitly told how and without complete knowledge of each other. Threading is responsible for the multitasking paradigm that we rely on so heavily with modern computers, enabling us to have more complex programs and open multiple programs concurrently, a capability completely essential to our use of technology in the present day. Launching a new thread, also called a process, is useful incredibly useful when trying to make two things happen at the same time, such as waiting for user input from a GUI (*graphical user interface*) and doing calculations in the background simultaneously.

### Theory

At a low-level, threads operate wildly differently based on which operating system is being programmed for, but the basic idea is the same. I really like the [explanation given by @Leos313 on this Stack Overflow question](https://stackoverflow.com/a/38145183/3339274), so I'll briefly paraphrase it here. The main thread (*initial program launched by the user*) can at any point create a new thread to run aside it, giving it a routine to perform after which it will exit and cease to exist. The main thread can check up on the threads it launches, (*"worker threads"*) checking to see if they are complete, but it can't do much more without some fancy footwork. If the main thread ends before the worker threads, the workers will also exit, generating an error:

```
terminate called without an active exception
```

to signify that they were interrupted before they could finish.

### Before  we start using threads...

Threading is a special feature, as the operating system needs to specifically support multithreading (*the act of having more than one thread running at a time*) For this reason, the C++ standard doesn't outright include full support for threading so that it remains compatible with operating systems that don't support multithreading; it contains function definitions, but will fail to link (*a part of the compilation process*) without something extra to provide the method for interacting with the multithreading features of the particular platform.

Without providing the required materials, the C++ linker will produce [an error like this when trying to compile the program](https://stackoverflow.com/q/21211980/3339274):

```shell
Linux/MacOS

tmp/cc8sIoP4.o: In function `std::thread::thread<void (Test::*)(), Test*>(void (Test::*&&)(), Test*&&)':
test2.cc:(.text._ZNSt6threadC2IM4TestFvvEJPS1_EEEOT_DpOT0_[_ZNSt6threadC5IM4TestFvvEJPS1_EEEOT_DpOT0_]+0x33): undefined reference to `pthread_create'
collect2: error: ld returned 1 exit status

Windows:

./test.cc:8:3: error: ‘thread’ is not a member of ‘std’
```

Setting up such implementations of C++ multithreading differs between operating systems.

#### Unix-based platforms: *Linux and MacOS*

Most operating systems based on [Unix, a highly foundational OS built by Bell Labs in 1969](https://en.wikipedia.org/wiki/Unix), such as all Linux distributions and MacOS derive their threading capabilities from implementations of the [NPTL (*Native POSIX Thread Library*)](https://en.wikipedia.org/wiki/Native_POSIX_Thread_Library) or similar APIs based on the POSIX Thread spec, often shortened to `pthread`, a term you might recognize from the above error message.

Using `pthread` is simple, requiring it to be "linked" into the compilation process. In `g++`, just add the `-pthread` or `lpthread` flag. (*the `l` stands for link*)

```shell
$ g++ test.cc -pthread
OR
$ g++ test.cc -lpthread
```

#### Windows

Windows users (*again*) have a harder experience, as the MinGW package that must be installed for `g++` to be used must be installed with an implementation of POSIX `pthread`s to be able to compile the C++ `thread` header.

Such resources as [this Stack Overflow post](https://stackoverflow.com/q/15718904/3339274) and the linked-to [MinGW build](https://sourceforge.net/projects/mingwbuilds/files/host-windows/releases/4.8.0/32-bit/threads-posix/sjlj/) exist for those who are willing to weather the storm of potential hurdles present here, however this is another example of a way in which the newly-introduced [Windows Subsystem for Linux (*WSL*)](https://en.wikipedia.org/wiki/Windows_Subsystem_for_Linux) for Windows 10 briefly discussed in Chapter 1 takes the cake in terms of simplicity. As its name describes, because it runs a modified Linux (*specifically Ubuntu*) OS on top of Windows, it is able to make full use of the standard `pthread` implementations that ordinary Linux OSes can.

### Implementation

Due to the relatively simple API inherent to threading due to the limited ability of the main thread to interact with the worker threads, the actual API of the C++ `thread` header is pretty simple.

```C++
#include <thread>
#intlude <iostream>

void function() {
  std::cout << "This is the worker thread" << std::endl; 
}

int main() {
  std::thread worker; // No new thread is created yet, as there is nothing for it to do...
  worker = std::thread(function); // A new thread is created, and the function "function" runs
  std::cout << "This is the main thread" << std::endl;
  
  // If the worker thread is still running, we need to make sure that it terminates before the main thread to avoid the "terminate called without an active exception" message.
  if(worker.joinable()) { // Check to see if the worker thread is still running
    worker.join(); // If it is, wait for it to terminate on its own
  }
  return 0;
}
```

Possible output:

```shell
$ g++ test.cc -pthread && ./a.out
This is the worker thread
This is the main thread
$
```

Note that this only one of the possible outputs generatable by the above example. Because a new thread is spawned, there is really no defined behavior as to which of the threads will execute which commands in order. Depending on the circumstances, it may very well be possible that the main thread prints its line before the worker thread.

Threads can also be spawned from functions that require parameters:

```c++
void function(int a, int b, int c, /*...*/) {
	//...
}

//...

std::thread worker(function, 1, 2, 3, /*...*/);
```

The return type of the function, however, should be void, as all other return types are promptly ignored by the new thread. Since there is no simple way for the worker thread to communicate back with the main thread, there is no way for the C++ compiler to get the returned value back to the caller.

## 3.6: Event Loop Example

An [event loop](https://en.wikipedia.org/wiki/Event_loop) is a construct that is central to the vast majority of computer programs, helping them manage sequences of events and tasks in an orderly fashion. Different parts of the program schedule events with the event loop, such as "let me know in 10 minutes", "let me know when the internet comes back", etc. with the expectation that the event loop is on top of what is going on and will "wake up" the program that asked to be notified.

There are almost an infinite number of variations and permutations possible to an event loop and surrounding infrastructure, but we're going to create a rather simple event loop that sequences events given to it, i.e. executes events one after another. To do this, we're going to enlist concepts from this chapter, including `std::vector`, lambdas, and more.

Like we did last chapter, let's think about this project in terms of the required API, which this time is pretty simple:

- `addTask(std::function<void()>)`: adds the given function to the list of tasks to execute
- `run()`: start processing the events already in the list
- `stop()`: interrupt the actions of `run()`
- `clearAll()`: get rid of any tasks already added

The list of tasks inside the class will take the form of an `std::vector` so that we can dynamically add more tasks as they come in.

### Let's get started writing!

```c++
#include <functional>
#include <thread>
#include <vector>

class EventLoop {
 public:
  EventLoop() { stopWork_ = false; }

  // Push a new task onto the end of the queue
  void addTask(std::function<void()> task) { tasks_.push_back(task); }

  void run() {
    // Reset the stopWork_ flag so that the worker doesn't immediately stop
    stopWork_ = false;
    // Only start a new worker thread if it isn't already running 
    if(!worker_.joinable()) worker_ = std::thread(&EventLoop::processList, this);
  }

  // Stop executing tasks
  void stop() { stopWork_ = true; }

  // Clear the queue
  void clearAll() {
    // Make sure that the thread isn't running before we modify the queue
  	stop();
    tasks_.clear();
  }

  // Wait for the worker thread to exit before letting the class destroy itself
  ~EventLoop() {
    if(worker_.joinable()) worker_.join();
  }

 private:
  // Function to be run by the worker thread
  void processList() {
    //...
  }

  // Task queue to be processed by the worker thread
  std::vector<std::function<void()>> tasks_;
  // Worker thread
  std::thread worker_;
  // Communicates to the worker thread that it should stop working when set to true
  bool stopWork_;
};

int main() {
  //...
  return 0;
}
```

In this initial C++ code stub for the program we're writing, the basic foundation of the `EventLoop` class is put forward. The only new syntax here is present when we set up the worker thread:

`std::thread(&EventLoop::processList, this);`

`worker_` gets its code from the `processList()` member function, and [special syntax is required for passing a member function into the `std::thread` constructor](https://stackoverflow.com/q/11057800/3339274). The Stack Overflow post [linked to](https://stackoverflow.com/questions/11057800/passing-member-functions-to-stdthread) contains a technical answer for why this syntax is required, but it basically boils down to the following. Because there is a possibility that the member function modifies or makes use of other member objects in the class, which does happen to be the case for us, we need to specify which instance of the `EventLoop` class the `processList` function we want to be calling is in.

Thus, we take the pointer (*`&`*) to the `processList` function contained in the `EventLoop` class, for which the namespace operator (*`::`*) is used.

The `this` parameter ensures the worker thread access to the member objects it needs to run, namely `tasks_` and `stopWork_` by passing in a pointer to the current class. It also serves the purpose of identifying which instance  of the `EventLoop` class we want to be using.

### Filling in the gaps

Next, let's fill in the empty space we left for the `processList` function.

```c++
void processList() {
  // Loop while there are elements in the vector and we aren't supposed to stop
  while (tasks_.size() != 0 && !stopWork_) {
    // Call the first task in the vector
    tasks_[0]();
    // Erase the first task in the vector (.begin() points to the first element of the vector)
    tasks_.erase(tasks_.begin());
  }
}
```

This is a pretty simple function. It loops through every item in the `tasks_` vector (*by erasing the first element each iteration, thus removing already processed tasks from the queue*)

And finally, let's write the `main()` function. Here, let's write a simple test of the `EventLoop` class, testing every function.

```C++
// Add this on top:
#include <chrono>
#include <iostream>

int main() {
  EventLoop el;
  
  // Add 5 elements to the queue
  for (int i = 0; i < 5; i++) {
    el.addTask([i]() { std::cout << i << std::endl; });
  }
  // Clear the elements we just added
  el.clearAll();
  
  // Add 5 more elements to the queue
  for (int i = 5; i < 10; i++) {
    el.addTask([i]() { std::cout << i << std::endl; });
  }

  // Run the event loop
  el.run();
  
  // Wait for a bit before stopping the event loop
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(100ms);
  el.stop();

  return 0;
}
```

This too is a pretty simple function, just calling each of the functions in the class to test their functionality. The only new part is the code to wait for 100 milliseconds.

```C++
using namespace std::chrono_literals;
std::this_thread::sleep_for(100ms);
```

`std::this_thread`, provided by the `thread` header, gives us a way to pause execution (*called blocking*) of the current thread for the given duration, in this case, 100 milliseconds. 

The `using namespace std::chrono_literals` line allows us to write 100 milliseconds as `100ms` instead of what it stands for: `std::chrono::milliseconds(100)`. This is because [the `std::chrono_literals` namespace defines `[INTEGER]ms` to be equivalent to `std::chrono::milliseconds(100)`](https://en.cppreference.com/w/cpp/header/chrono). This handy shortcut is really nice, especially considering that other literals like it are made available in the same namespace. (*`us` (microsecond), `ns` (nanosecond), `s`, `min`, `h`*)

### Possible output

```shell
$ g++ test.cc -pthread
5
6
7
8
9
$
```

Again, note that this is only one of the many possible outputs. Depending on many other uncontrollable factors on the computer while the program is running, some of the outputs may be omitted because they weren't able to be run by the worker thread in the 100ms that the main thread allowed before stopping the event loop.

And thus, our example is completed!