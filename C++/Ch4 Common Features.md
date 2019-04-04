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
file.open("test.txt", ios::in | ios::out | ios::app); // Opens the file "./test.txt" for reading and writing. Lines written to the file will be appended to the end isntead of replacing what is already there.
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
  } catch(const char* error) { // Catch an exception in the form of a const char* (analagous to a String type)
    std::cout << "Error! " << error << std::endl;
  }
}
```

But even still, be aware that usage and implementation of exception throwing is highly frowned upon in many contexts and organizations. Beware.

### 4.3 Why Does This Exist`?`

All hail the immense and total power of the inline `if` statement! The `?` operator functions as a sort of inline `if` statement. Let's see if it's usage is apparent from an example:

```C++
int number = 10;
std::cout << number > 5 ? "BIG!" : "small" << std::endl;
```

The code above would print the word "BIG" to the terminal. Do you see what just happened? Let's generalize the `?` operator's usage.

`[CONDITION] ? [VAL IF TRUE] :[VAL IF FALSE]`

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