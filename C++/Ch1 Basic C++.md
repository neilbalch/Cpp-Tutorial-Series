# Chapter 1: Basic C++

## 1.0: Guide to the Universe

Complete C++ documentation can be found at the sites [en.cppreference.com/w](http://en.cppreference.com/w/) and [cplusplus.com](http://www.cplusplus.com/). The search tools on these sites work well when you know what you are looking for, so searching on Google and then clicking links to these sites is the option most likely to return a positive result. However, to a newer C++ programmer, the site can seem quite daunting, so we will try to provide a basic understanding here. In addition to this, the YouTube channel [TheCherno has an excellent playlist on fundamental to advanced C++ topics](youtube.com/watch?v=18c3MTX0PK0&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb) that we highly recommend for anyone who wants to learn more about tricky topics explained in an understandable manner.

If you don’t want to set up a code environment on the terminal yet, you can always practice C++ with [cpp.sh](www.cpp.sh) or a similar web based C++ compiler. The only caveat to this approach is that there is no easy way to link multiple files together, and your programs would need to be in one file.

### Style Guides

When programming in a team setting, (*or even individually*) it is best practice to follow a set of common formatting guidelines to ensure a consistent look and feel, called a style guide. By far, the most common for C++ is the the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html). This document describes how to properly format and write easily comprehensible code in a way that is consistent, used internally by Google in their source code and externally by many many other organisations and teams. It does appear to be a very scary and long document; I mean just take a look at how small the scroll nubbin gets when viewing!

But really, it isn’t *that* scary in actuality. Most of the rules will become second nature to you once you begin to write code for the team and get comments on it. In general, a good rule of thumb is to make your code look like the code that surrounds it. For the most part, unless you love reading endless quantities of rules, just know it exists and that many programmers follow the rules in it.

## 1.1: What is C++?

Well, according to Wikipedia, [“*C++ is a general-purpose programming language*”](https://en.wikipedia.org/wiki/General-purpose_programming_language). If that satisfies you, then you can stop reading, but if not, the rest of this section will address that in more detail. C++ is an [object-oriented language](https://en.wikipedia.org/wiki/Object-oriented_programming), meaning that most all of the things one uses when writing a program in C++ are objects. These usually take the form of *classes and structs*, which organise code into easily reusable blocks, which in of themselves encapsulate more specific functions that do stuff, and variables that store data.

In addition, C++ (*its parent language, C, and derivative langiages such as C#*) are highly low-level languages, meaning that writing in C++ sometimes requires more advanced knoledge regarding how a computer functions internally, such as how memory storage works. However, this also means that unlike more abstracted languages, such as Java, Python, JavaScrpt, etc., C++ is incredibly responsive and is nearly always used in applications where quick and responsive programs are a requirement. Such applications include AAA games, robotics, control systems and much more.

In fact, many other languages compile down to C++ code when run because of its inherently quicker operations. Many compilers for other languages (*namely [Java](https://stackoverflow.com/questions/1220914/in-which-language-are-the-java-compiler-and-jvm-written) and [Python](https://softwareengineering.stackexchange.com/questions/20988/why-is-python-written-in-c-and-not-in-c)*) are also written in C or C++ for the same reasons.

C++ source files will most often take the form of `.cpp`, `.cc` and `.h` files. The first two, `.cpp` and `.cc` are source files, which contain the code that actually performs actions, and `.h` (*header*) files containing a list of functions and classes that will be implemented in the `.cc` file of the same name.

## 1.2: Hello World!

### Hello World!

When beginning to program in any language, it is traditional to start by writing a “Hello World!” program that simply prints text to the screen. Here, we will continue that tradition. Try to follow along as best as you can, writing this code in a text file with a `.cc` extension. (*i.e. `HelloWorld.cc`*)

```C++
#include <iostream>

int main() {
  std::cout << "Hello World!" << std::endl;
}
```

The first line, `#include <iostream>`, includes the default I/O (*Input/Output*) library, which enables us to use `std::cout` to print to the screen.

The second line, `int main() {`, defines the function that the C++ compiler will tell the computer to run. By default, the function returns `0`, which means that there were no errors, hence the return type of `int` (*integer*) at the beginning of the line.

The third line calls the `std::cout` function, which prints the text Hello World! to the screen. The words Hello World are inside quotation marks here because that tells the compiler that it should treat the text inside the `“”` marks as a string of characters. The `<<` syntax is a bit odd, but for now we can equate its function to feeding the content on the open end of the arrow to the command on the closed side of the arrow, feeding the string Hello World into the command `std::cout`. The `std::endl` command shoves a newline command on the end so that if more text needs to be printed it will end up on the next line. Without the `std::endl`, the output would look like this in your shell:

```shell
$ ./HelloWorld
Hello World$
```

The fact that the prompt is now on the same line as the text we printed is not good, and when we add the std::endl, the output looks like this:

```shell
$ ./HelloWorld
Hello World
$
```

Much better! Finally, a semicolon is added on the end of the line to tell the compiler that the command is over. The last line closes the `main()` function with a curly brace.

### Compiling and Running the Program

Great, now we have written our program, but how do we run it? Well, as long as you are using a bash terminal (*Mac, Linux, or WSL on Windows*) you can use `g++` as a compiler. If you are on Windows and would prefer not to install WSL (*Windows Subsystem for Linux*), you can install and configure [MinGW](http://mingw.org/), but you're kinda on your own here because I don't want to explain it and all of its nuances. (*and the instructions for compilation and running the program are going to differ slightly*)

[This video on the YouTube channel Frame of Essence](https://www.youtube.com/watch?v=QXjU9qTsYCc) does a good job at describing what a compiler does. It is a good watch if you don’t already know what one does. (*It even uses C++ as an example!*)

Figure out how to install `g++` on your terminal. (*Doing a google search for “How to install g++ on [Your OS Here]” is a good start*) Once you have it, you can run your program by typing:

``` shell
g++ -g [FILEPATH] && ./a.out
```

into your terminal to compile and run the program. With luck, you should see something like the example output above, provided that there are no syntax errors in your code.

### Let’s Have Some Fun

Why don’t we add a bit more to this program? Let’s make it now take input from the terminal, asking for the user’s name and then print it back out for them. The flow of the program should now resemble this: Ask the user for their name and store it in a container, then print the value of the container. Containers like these are called variables. In C++, variables can store virtually any kind of data you want, from integers and floating point numbers to strings of characters. Since we are taking in a name, we will use a string variable. Now, modify your program file to look like this:

```C++
#include <iostream>
#include <string>

int main() {
  std::cout << "Hello World! What is your name? ";

  std::string name = "";
  std::cin >> name;

  std::cout << "Hello, " << name << "!" << std::endl;
}
```

The first line we added, `#include <string>`, includes the standard library that allows us to use string variables. In the main function, we first print out the question to the user, declare a string variable called name, take the input the user gave and save it into the name variable, and then print the name variable out to the screen.
If you compile and run this program again (*with this command: `g++ -g [FILEPATH]; ./a.out`*), you should see output that looks like this:

```shell
$ ./a.out
Hello World! What is your name? Neil
Hello, Neil!
$
```

### Because We Can

Awesome, the program worked! Now, say that we really like people with the name Trevor, and we want to treat them extra special. We can modify this program to also say something nice to users that put in the name Trevor. The `if` statement in C++ can help us do that. The basic structure of an if statement looks like this:

```C++
if (condition) {
  // Do something
} else {
  // Do something else
}
```

The program will stop when it gets to an if statement, check to see if the condition (*which must evaluate to a boolean value, i.e. true or false*) is true, and if it is, it will run the code inside the `// Do something` section, and if it isn’t true (*false*) it will run the code in the `// Do something else` section. When you see a `//` in C++, it means that the rest of the line is a comment, which tells the compiler not to run that line. We can implement this in our program to decide if we should congratulate the user for being a Trevor. Modify your program to look like this:

```C++
#include <iostream>
#include <string>

int main() {
  std::cout << "Hello World! What is your name? " << std::endl;

  std::string name = "";
  std::cin >> name;

  if (name == "Trevor" || name == "trevor") {
    // We want to say hi
    std::cout << "Hey! I really like your name, " << name << "!";
  } else {
    // We don’t care
    std::cout << "Hello, " << name << "!";
  }
}
```

The condition to the if statement that we just added checks to see if the name variable is either trevor or Trevor, in which case we would want to do something special. The `||` operator means or, so the condition would read in English: *"if name equals Trevor or if name equals trevor”*. If that is true, then we print, *“Hey! I really like your name, Trevor! (or trevor!)”* and if it isn’t, then we print *“Hello, [Name]!”*.

If you run this version of the program, the output should look like this:

```shell
$ ./a.out
Hello World! What is your name? Neil
Hello, Neil!
$
```

***OR***

```shell
$ ./a.out
Hello World! What is your name? Trevor
Hey! I really like your name, Trevor!
$
```

depending on whether or not you type in “trevor” or “Trevor” as your name.

## 1.3: Problem 1

### The Problem

Our next coding challenge comes from [the first problem](https://projecteuler.net/problem=1) on [projecteuler.net](https://projecteuler.net). The problem reads:

> If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.
Find the sum of all the multiples of 3 or 5 below 1000.

Alright, so this is asking us to print out the sum of all of the integer numbers less than 1000 that are evenly divisible by either 3 or 5. Before we start writing code to solve this problem, we need to think through what we want the program to do. In English words, we want the program to run through all of the integers between 0 and 1000, checking to see if the number is evenly divisible by 3 or 5 and if it is, we want it to add that number to a running sum. Then, after it finishes looping through 1000 times, stop and print the sum to the screen.

### Looping Looping Looping Looping

Let’s first look at how we can make a loop that steps through the integer numbers 1 to 1000. There are two main ways of writing a loop in C++: the `while` loop and the `for` loop. The syntax for a while loop is as follows:

```C++
while (condition) {
  // Do stuff here as long as the condition is true
}
```

The `while` loop will run the code inside itself for as long as the condition evaluates to true. If it starts out evaluating to false, then the code will be skipped entirely. A while loop that runs through the numbers 1 to 1000 would look like this:

```C++
int counter = 0;
while (counter < 1000) {
  // Do stuff here
  counter++; // Increment the counter by +1
}
```

First, we initialize a counter variable at 0. Then, we have a while loop with the condition that evaluates to true as long as counter is less than 1000. Then, inside the loop, we run the code we want to run, and then we increment the counter by 1. (*The `counter++` syntax is shorthand for (evaluates to) counter = counter + 1 in this case*)

Another possible way to loop through the integer numbers 1 to 1000 is by using a `for` loop. The syntax for a `for` loop is as follows:

```C++
for (int i = 0; i < 1000; i++) {
  // Do stuff here
}
```

This is a very compact syntax, as it essentially squishes the three lines of context for the while loop into one line. First, the code initializes a loop variable `i` that starts at 0. Then it runs the code inside the for loop, assuming that the condition evaluates to true. Then, it increments the loop variable (*`i`*) by 1 and then checks to see if the condition still evaluates to true. If it does, then it runs the code inside the loop again. And so on and so forth until the condition evaluates to false, in which case the loop exits.

Alright, now that we know how to write a loop, we can write a skeleton for our new program.

```C++
#include <iostream>

int main() {
  // Running sum
  int sum = 0;

  // Loop
  for (int i = 0; i < 1000; i++) {
    // Do the logic here
  }

  // After all is done, print the result.
  std::cout << "Final Sum: " << sum << std::endl;
}
```

### Modulo and Fun

Now we need to work out the logic that would add to the running sum if the loop variable is evenly divisible by either 3 or 5. In C++, the modulo operator (`%`) calculates the remainder of a division. For example, 5 % 3 would equal 2, as the remainder of 5/3 is 2. We can use this to find if the loop variable is divisible by 3 or 5, as if it is, the output of a modulo operation on such a number would be 0. We can write a series of two if statements to check if the loop variable is evenly divisible by either 3 or 5. Add this inside your for loop:

```C++
if (i % 3 == 0) {
  sum += i;
}

if (i % 5 == 0) {
  sum += i;
}
```

### Oh Noes!

When you program, always think of edge cases, possible ways your code could break and not provide the proper result. (*aka corner cases*) One such edge case is a number that is both evenly divisible by 3 and 5. What happens if we set i = 15? Well, the first if statement condition would evaluate to true, as `15 % 3 == 0`, and the second if statement condition would also evaluate to true, as `15 % 5 == 0` as well. This would result in 15 being added to the sum twice, not once like we want it to be. We can fix this by adding the else keyword to the second if statement:

```C++
if (i % 3 == 0) {
  sum += i;
} else if (i % 5 == 0) {
  sum += i;
}
```

With this updated code, the second condition will only be evaluated if the first condition evaluates to false. Let’s reanalyse the same edge case again where i = 15. The first condition evaluates to true, so the value of i is added to the sum, and then since the first condition evaluated to true, the second condition is ignored. What do you know? The edge case passes now!

Note that the two blocks can be merged together by tweaking the condition slightly. This code:

```C++
if (i % 3 == 0 || i % 5 == 0) {
  sum += i;
}
```

still does the same thing as the code above. Combining the two conditions with two pipes (*Typed with `Shift+\` on standard keyboards*) performs an OR operation so that if either of the parts to the left or right of the two pipes evaluates to true, the entire condition evaluates to true. Neither method is better than the other, and in fact there are often many acceptable methods to use to solve a problem.

### Taking on The Final Form

At this point, your code for this program should look like this:

```C++
int main() {
  // Running sum
  int sum = 0;

  // Loop
  for (int i = 0; i < 1000; i++) {
    if (i % 3 == 0) {
      sum += i;
    } else if (i % 5 == 0) {
      sum += i;
    }
  }

  // After all is done, print the result.
  std::cout << "Final Sum: " << sum << std::endl;
}
```

Compile and run the code now. You should get the correct answer printed on the terminal:

```shell
Final Sum: 233168
```

## 1.4: Object Oriented Programming in C++

The concept of an object in Object Oriented Programming (*OOP*) can represent almost any kind of thing, from a variable that stores data, a function that performs a specific action, to a class that may contain many other variables and functions that each serve purposes that are related to one another.

The epitome of OOP is scope, which is the range in which an object is visible. In general, a good rule of thumb for scopes is that an object is only visible to code within the same set of curly braces (`{}`) as it is inside.

### Variables

We have used variable before in previous sections. These objects can contain only one dataset at a time, but their value can be modified as long as they are not declared as a constant, in which case attempting to modify their contents will result in a syntax error. Variable names cannot have spaces in them. A variable is declared like so:

`type variable_name = initial_value`;

**For example**:

- `int sum = 0;`
- `std::string myString = "Hello World!";`
- `double pi = 3.14159;`
- `const double intakeHardstop = 0.0153;`

It is good to note that while this particular guide hasn’t covered the topic, the last example here with the `const` keyword in front makes the variable a constant value. Once a value is set into it, the value can no longer be changed. There are many other variants of the `const` keyword, like `constexpr`, but those are for a later day. (*Unless the annoyance of not knowing results in a Google search*)

### Functions

A function is a set of lines of code that performs a specific action. Functions are defined like so:

```C++
return_type function_name(arguments) {
  // Do stuff here
  return something_of_the_same_type_as_the_return_type;
}
```

The return type of a function is what type of output the function will spit out after it is done executing. It can be anything really, as long as it is a valid type. (*For example: `int`, `double`, `std::string`, or `void`*) The `void` return type is special, as it means that the function doesn’t return anything, and therefore, the return statement, which actually specifies what should be spit out of the function, is not used. The function name can also be anything, but it cannot include spaces nor numbers as the first character.

The arguments are variables that must be provided by the user of the function for use inside the function. Depending on the function’s intended purpose, there can also be no arguments required. Arguments are declared like normal variables, but normally don’t have an assignment on the end. For example, an argument to a function could look like int num_iterations. Notice how the variable isn’t assigned an initial value. Arguments are separated by commas in the function declaration.

Functions can be used once they are defined like so:

`return_type my_variable = function_name(arguments);`

or if the function has a return type of void:

`function_name(arguments);`

**For Example**:

```C++
double add(double num1, double num2) {
  return num1 + num2;
}

double output = add(3.14159, 6.28318);
```

### Classes and Structs

In C++, there is no major difference between classes and structs. As mentioned before, both are used to group functions and variables that are related to one another together. Member functions and variables (*contained inside a class or struct*) have an access specifier that dictates which areas of the program (*scopes*) can see and access them. In classes by default, members are assigned the private access specifier, which means that only other members can see and access them. In structs, the opposite is true; by default, members are assigned the public access specifier, meaning that any part of the program can access them. Here is an example class definition:

```C++
class Rectangle {
 public:
  Rectangle(double length, double width) {
    length_ = length;
    width_ = width;
  }
  double area() {
    return length_ * width_;
  }

  double perimeter() {
    return (2 * length_) + (2 * width_);
  }
 private:
  double length_;
  double width_;
};
```

This class groups together functions that deal with rectangle shapes. The use of the `public:`
keyword means that every declaration after that line will have the access specifier of public. This results in the `area()` and `perimeter()` member functions being declared as public. Next, the `private:` keyword changes the access specifier again, making the following member variables private. The member variables are named with an underscore in front of their names to indicate that they are member variables, a common convention in C++.

The first member function defined in this example doesn’t have a type because it is the constructor. This optional function is called when an instance of the class is created. Classes and structs are only blueprints, as on their own they are incapable of doing anything. For them to be of any use, you need to create an instance of the class or struct, which can be likened to building the structure on said blueprint. An instance of the rectangle class above can be made like so:

`Rectangle my_rectangle(5.0, 10.0);`

That creates a new instance of the `Rectangle` class called `my_rectangle`. As used in this case, the constructor is called (*and passed the values 5.0 and 10.0*) to set up the known circumstances of the rectangle, indicating that it has a length of 5 units and a width of 10 units. Whenever a new instance of a class or struct is created, the constructor is called (*assuming the class or struct defines a constructor*) and passed the parameters given in between the parentheses. Constructors are always defined to have the same name as the class or struct they are in, which makes the `Rectangle` function the constructor in our example. Now that we created an instance of the rectangle class, we can now call its member functions.

`std::cout << "Area of the rectangle: " << my_rectangle.area() << std::endl;`

This line prints out the area of a rectangle with a length of 5 units and a width of 10 units by calling the `my_rectangle`’s area function. The `.` operator is used to access an object inside a class or struct. In the example above, the `.` operator is used to call the `area()` function in the `my_rectangle` class.

**Note**: This class could also be defined as a struct, as long as you tweak the access specifiers a bit:

```C++
struct Rectangle {
  Rectangle(double length, double width) {
    length_ = length;
    width_ = width;
  }
  double area() {
    return length_ * width_;
  }

  double perimeter() {
    return (2 * length_) + (2 * width_);
  }
 private:
  double length_;
  double width_;
};
```

The `public:` access specifier is not required, as the default access specifier for structs is already public.

### Class and Struct Inheritance

Classes and structs can inherit from one another in C++, allowing for less code to be retyped. Say we wanted to create a new class to handle squares. We could create an entirely new class, but why would we when we can just inherit from the rectangle class that already has all of the features we need. A square class that inherits from the rectangle class would look like this:

```C++
class Square : public Rectangle {
 public:
  Square(double length) : Rectangle(length, length) {};
};
```

The first line dictates that the class `Square` inherits from the class `Rectangle`. That means that the Square derived class takes on all of the member variables and functions of the Rectangle base class. Some objects that are not inherited from the base class are constructors and private members. If you need objects from the base class to be visible in the derived class but not outside both of them, use the protected access modifier instead of the private access modifier. The only difference between the two is that protected allows access to inherited classes and private doesn’t.

### Namespaces

Namespaces are a way to group objects together into sub-scopes. These are not like classes and structs in the sense that they don’t need to be instantiated, but rather more like chapter markers that mark large swaths of code. Namespaces are created like so:

```C++
namespace myNamespace {
  // Code goes in here, i.e.
  int a = 10;
  double something = 3.14159;
}
```

To access the objects inside the namespace, you would type `[Namespace Name]::[Object Name]`. For example:
`std::cout << myNamespace::a << std::endl`;
would print `“10”` to the screen and:
`std::cout << myNamespace::something << std::endl;`
would print `“3.14159”` to the screen. Notice something interesting here? In fact, the very same `std::cout` command we have been using since the beginning of time calls the `cout` function in the namespace `std`! Wow, namespaces are everywhere!

### Include all da codes!
At the beginning of all of our programs so far, we have been typing the line `#include <iostream>`, which imports the `iostream` library. This is a subset of the greater `std` namespace, and is one of the many standard libraries that can be included to add functionality to your code. Another such standard library we have been using, `#include <string>`, helps us with strings of text, like `“Hello World!”`. You can find a full list of all available standard libraries [here](http://en.cppreference.com/w/cpp/header). Any of the above mentioned standard libraries can be included following the same syntax we used before:

`#include <[Name of Standard Library]>`

Files you make yourself can also be included, but they follow a different syntax:

`#include "[File Path]"`

in order to signify that the compiler needs to look for the file in the working directory.
