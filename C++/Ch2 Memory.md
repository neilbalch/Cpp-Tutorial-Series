# Memory

## 2.1: Operations of System RAM

This section is going to be somewhat complex in theory, a fact that is unfortunately unavoidable when discussing computer memory. Complete understanding of this system isn't necessary, but a general understanding is highly recommended. *It is also recommended to have a grip on what binary is and what it looks like before reading this section.*

System memory, often referred to by its proper name Random Access Memory (*RAM*), is an integral part of a computer's operations. It stores the data that the CPU (*Central Processing Unit*) is currently working on in and is accessible via a high-speed and low latency connection to the CPU. It is considerably faster than the conventional storage of the system, whether it be a hard drive or and SSD, and is therefore unsurprisingly considerably more expensive per unit.

Later on in the journey through C++, we'll learn about the CPU's own super high speed memory which is even faster still, (*and again more expensive per unit*) called the CPU cache, which is used in somewhat similar manner to the RAM, but that's literally a topic for another day.

### RAM model

It is convenient (*and mostly correct*) to think of the RAM as being a list of binary (*0 or 1*) digits in byte groups, each entry organized by a corresponding address, used for reading and writing data to the right places.

| Address  |   Data   |
|---------:|:---------|
| 00000000 | 10001r00 |
| 00000001 | 01010010 |
| 00000010 | 01000100 |
| 00000011 | 01101000 |
| 00000100 | 00100100 |
| 00000101 | 00010000 |
| 00000110 | 01111010 |
| 00000111 | 00011110 |

Figure 2.1.1: Depiction of system RAM structure

The exact length of the addresses and corresponding data are dependent on the bus width of the processor. (*64 bits long for 64 bit processors, such as the one in the computer you're probably using to read this right now*) For the sake of simplicity, we'll model the memory as it would for an 8-bit processor.

Programs are allowed to read and write data to RAM in locations where they are allowed to by the operating system. The process of requesting more data space in RAM is called allocation, a term that will become very important for future C++ learning. If a program tries to write data to a location it isn't allowed to, usually by accident, the operating system will interrupt the program execution with a segmentation fault. (*I promise that you'll get a lot of these*)

### C++ Memory Allocation

In C++, and other low-level languages, there are two main locations where data can be written to in RAM: the stack and the heap.

The stack is a comparatively small section of RAM allocated by default to every process (*specific term for a single running instance of a program*) at the outset, and generally can't be expanded by very much. It is a HIGHLY managed part of RAM, frequently cleansed of unnecessary stuff and organized very tightly (*data is packed together as close as possible in RAM to maximize capacity*). When the capacity of the stack is met or exceeded, the operating system will terminate the process on the grounds of a stack overflow. (*deliberately the same name as [the popular programming Q/A forum](https://stackoverflow.com/)*) For these reasons, it is generally relegated to data that is relevant to the program at the current moment. Data that needs to be preserved for longer periods of time (*or is just simply very large*) is stored on the heap.

Making use of the stack is incredibly easy; we've been doing it since the first chapter.

```C++
int i = 1001; // Declares an integer variable called 'i' located on the stack
double pi = 3.14159; // Declares a double precision floating point number (decimal number) called 'pi' located on the stack
```

The heap, as its name suggests, is a less heavily regulated portion of system RAM that has a practically unlimited size (*up to the total system RAM size of course*) that can be used for less time-sensitive, longer term and larger size data storage. The primary caveat to its use is that it requires active management of the data that is put there, as if it is never explicitly removed it will stay there permanently, even after the process is killed or ends. This is called a memory leak, and is a highly elusive mistake to try and catch in large programs.

Making use of the heap is a more intricate task, and one that can't be properly introduced without first discussing pointers. So...

## 2.2: Pointers

The basic concept of a pointer is very simple, and the name itself is self-explanatory: it is a data type that points to another location in system memory. For example, in our hypothetical 8-bit system, a pointer's data could contain this: `01001110`, which points to the address of the same number.

In C++, pointers are declared like so:

```C++
int var = 31;
int *var_ptr = &var;
```

In this example, `var_ptr` is the pointer. Note that in addition to the asterisk (*\**) declaring that the variable is a pointer, the type of object that the pointer points to must also be declared. The ampersand (*&*) character was used to get the address of the `var` variable. If the pointer was printed to the terminal, an experiment I urge you to complete, it would spit out a hexadecimal value that represents the binary address in memory that it points to.

Pointers also have another useful property, dereferencing, which allows the data at the location the pointer points to to be obtained.

```C++
int a = 31415;
int *a_ptr = &a;

int b = *a;
```

This introduces one of the stereotypical confusions when learning C++; the asterisk and ampersand characters change meaning based on the context.

| Character |   Usage Location    |        Meaning        |
|----------:|:-------------------:|:----------------------|
|    *      | left of expression  | pointer declaration   |
|    *      | right of expression | dereferencing         |
|    &      | left of expression  | reference declaration |
|    &      | right of expression | get pointer to        |

Figure 2.2.1: Asterisk and ampersand definition table.

We'll get to what a reference is in a bit. They're a whole different set of crazy, and best left alone until required. Generally, they're considered to be improper to use unless necessary because they syntactically appear to be just like normal variables, but behave in a similar way to pointers sometimes, ending up confusing everyone!

### `nullptr`

No talk of pointers is complete without the classic `nullptr`. `nullptr`, as some can probably deduce, is a keyword that represents absolutely nothing, hence the name that begins with null. Well, that isn't exactly true; it is a pointer that resolves (*points*) to the 0th location in memory (*`00000000` in our 8-bit computer example*). The 0th location in memory is special, no matter what system, because it is most often a protected location, meaning that no program (*not even the OS*) is allowed to write to it. Therefore, it represents absolutely nothing, since no one is allowed to put anything there.

If the program tries to dereference a pointer pointing to `nullptr`, the program will terminate with a segmentation fault.

`nullptr` isn't used as a value, but it is used when a pointer needs to communicate that it is empty and pointing to nothing. It is often used to represent an exception state, where some piece of information that is supposed to exist doesn't. (*if not immediately filled at declaration, pointers initially point to `nullptr`*)

### Heap Allocation

Back to heap allocation! Now that we know what pointers are, this explanation should be fairly straightforward.

```C++
int *my_heap_int = new int(5);
```

Instantiating an object on the heap is as simple as creating an empty pointer and assigning it the value of a new object of the same type. The `new` keyword is the operative term here, allocating enough space in heap memory for an integer variable. The value of the object stored at `my_heap_int` can be accessed via dereferencing.

In order to not cause memory leaks, it is necessary to clean up heap objects when they are not needed anymore. This is done by deleting them.

```C++
// Continued from the previous example...
delete my_heap_int;
```

All sorts of fun operations can be applied to pointers, such as addition/subtraction and more, allowing for more advanced concepts like type punning, which will be covered later.

## 2.3 Smart Pointers

Pointers like those discussed in section 2.2 are actually more accurately called raw pointers because of their relation to smart pointers. They will henceforth be referred to as such. (*be warned. :)* )

Because heap memory isn't managed in the same rigorous way as stack memory, leading to possible memory leaks and other adverse problems, C++11 (*the extension to the C++ standard released in 2011*) added a new and exciting feature called smart pointers. These objects attempt to mitigate the chances of generating a memory leak or using excessive RAM by providing a sort of wrapper around raw pointers that controls when they are created and deleted.

Smart pointers are made available via the `<memory>` header file. (*look back at the end of chapter 1 for instructions on how to import a library*)

There are three distinct types of [smart pointers](http://www.umich.edu/~eecs381/handouts/C++11_smart_ptrs.pdf):

- `std::unique_ptr<TYPE>`
- `std::shared_ptr<TYPE>`
- `std::weak_ptr<TYPE>`

The `TYPE` within angle brackets in the above lines refers to the type of object that will be stored. (*Remember that pointers need to know what type of object they will point to when defined? The smart pointer needs to know too.*)

The angle brackets, when used in a type expression, (*like how they are used above*) represent what's called a template. They are another advanced topic that we'll cover later, but for now, just think of them as telling the object you're defining what kind of object it is going to deal with.

The two most common types of smart pointers are `std::unique_ptr` and `std::shared_ptr`, in that order. `std::shared_ptr` is used when attempting to share the same memory between different processes, ensuring that neither can delete the raw pointer without the permission of the other. For that reason, we won't be talking about `std::shared_ptr` until we talk about multithreading. We also won't discuss `std::weak_ptr` here, as it's a lot more niche in its uses.

### [`std::unique_ptr<TYPE>`](https://en.wikipedia.org/wiki/Smart_pointer#unique_ptr)

`std::unique_ptr` is special because of its limitations, of which it has quite a few. It manages a raw pointer which it "owns". This is accomplished by not allowing the raw pointer to be duplicated and assigned to another raw pointer, in essence protecting the ability to make another pointer just like it. (*hence the name unique*)

Such objects are incredibly useful because of how they put up an extra block against other bits of code tampering with the memory location and automatically delete their inner raw pointer when they aren't needed anymore. (*because they are defined as stack objects*)

A `std::unique_ptr` can be defined like so:

```C++
// Given that "#include <memory>" is put at the top of the file,
std::unique_ptr<int> ptr(new int(1000);
//OR
double num = 3.14159;
std::unique_ptr<double> ptr2(*num);
```

Note that the syntax for instantiating a `std::unique_ptr` requires a raw pointer, either created inline or the pointer to another object that is already defined.

Ownership of the raw pointer can be "transferred" to another `std::unique_ptr` with the `std::move` function. For example:

```C++
// Continuation of above example...
std::unique_ptr<int> a = ptr; // COMPILER ERROR
std::unique_ptr<int> b = std::move(ptr); // Works
```

## 2.4 Linked List example

TODO(Neil): Make this from this: https://github.com/neilbalch/FRC971-Cpp/blob/master/LinkedList/linked_list.cc