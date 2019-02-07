# Chapter 2: Memory

## 2.1: Operations of System RAM

This section is going to be somewhat complex in theory, a fact that is unfortunately unavoidable when discussing computer memory. Complete understanding of this system isn't necessary, but a general understanding is highly recommended. *It is also recommended to have a grip on what binary is and what it looks like before reading this section.*

System memory, often referred to by its proper name Random Access Memory (*RAM*), is an integral part of a computer's operations. It stores the data that the CPU (*Central Processing Unit*) is currently working on in and is accessible via a high-speed and low latency connection to the CPU. It is considerably faster than the conventional storage of the system, whether it be a hard drive or and SSD, and is therefore unsurprisingly considerably more expensive per unit.

Later on in the journey through C++, we'll learn about the CPU's own super high speed memory which is even faster still, (*and again more expensive per unit*) called the CPU cache, which is used in somewhat similar manner to the RAM, but that's literally a topic for another day.

### RAM model

It is convenient (*and mostly correct*) to think of the RAM as being a list of binary (*0 or 1*) digits in byte groups, each entry organized by a corresponding address, used for reading and writing data to the right places.

|  Address | Data     |
| -------: | :------- |
| 00000000 | 10001100 |
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

## 2.3: Smart Pointers

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

## 2.4: Linked List example

Our programming application of memory in this chapter is going to be creating a singly-linked list class.

Linked lists are a fundamental concept in programming, no matter what language. Their concept is rather simple, but detailed and nuanced in the implementation. They store lists of data.

### Theory

Linked lists are made up of nodes, each one storing on object and a pointer to the next node. (*in double-linked lists, the node also stores the pointer to the previous node*) If you think about how that paradigm works, it is actually a pretty stable way to store a large amount of information that changes in length, which would make it unsuitable for storing in an array. (*which must maintain a fixed size*) So... in a more graphical form:

Singly linked list:

- Node 1:
  - Object
  - Pointer: Node 2
- Node 2:
  - Object
  - Pointer: Node 3
- Node 3:
  - Object
  - Pointer: nullptr

Figure 2.4.1: Graphical representation of a singly-linked list

The last node points to `nullptr`, as a sort of termination pointer to signal to the program that there are no more nodes past Node 3.

We're going to make the linked list work first with integer data types, and then make use of C++ templates to generalize the code to work with all data types.

First up, we need to imagine the API (*Application Programming Interface*) of this singly-linked list class, or what functions the users of our class can call. Let's make a list:

- `SinglyLinkedList`
  - `void push_front(object)`
  - `void push_back(object)`
  - `void pop_front()`
  - `void pop_back()`
  - `void list_nodes()`

The names of these functions should be fairly self-explanatory, after all, that is the point of an API. `push_front` will push a new node onto the front of the list (*i.e. before Node 1*), `push_back` will push a new node onto the back of the list (*i.e. after the last node*), and `pop_front` and `pop_back` will remove the node at the front or back of the list respectively.

### Beginnings

The first task is to create a code representation of our node object, which can be easily done with a `struct`:

```C++
struct Item {
  int value;
  Item* next = nullptr;
}
```

This is a simple struct containing a value variable to store the integer and a pointer to the next item in the list, which is initially set to nullptr.

Next, let's make a function to automate the instantiation and creation of an `Item` object.

```C++
Item* make_node(int value) {
  // Create a new Item on the heap
  Item* node = new Item();

  // Give the new node the proper value
  node->value = value;

  return node;
}
```

First, we use a pointer and the `new` keyword to create a new `Item` object on the heap. Then, we use the [syntactic sugar](https://en.wikipedia.org/wiki/Syntactic_sugar) (*shortcut or macro*) "`->`" to dereference `node` and assign the `value` attribute. The same line could be rearranged to a more familiar syntax:

```C++
(*node).value = value;
```

but the `->` is shorter and easier to type, plus it is harder to mess up by forgetting the parentheses. Finally, we return a raw pointer the completed node object.

We are now ready to begin creating the linked list class. Here is a template with which we will start:

```C++
#include <iostream>

class SinglyLinkedList {
 public:
  // Functions will go here
 private:
  // Item template for the singly linked list
  struct Item {
    int value;
    Item* next = nullptr;
  };

  // Helper for making a node item from a value
  Item* make_node(int value) {
    // Make a new node
    Item* node = new Item();
    // Assign the new node the given value
    node->value = value;

    return node;
  }

  // HEAD of the singly linked list
  Item* head = nullptr;
};
```

The new addition, the private `Item*` called `head`, is incredibly important, because it will contain a pointer to the first, or head, item of the list. Without it, the program will have no way of keeping track of which item is at the top. It'll start out pointing to `nullptr` for now. The `iostream` header is included to provide support for `std::cout`, a function that we'll later use.

### Core Functionality

Next, let's write and implement the four functions we need for the API, starting with the simplest, `push_front`. First, let's decide on how this function will operate.

The behavior we need from it is to create a new node, and then put it on the front of the list. We can do this by setting it's `next` attribute to the current `head` pointer and then setting the  `head` pointer equal to the new node. Thus, we will have "shifted" the previous head node down by one, the desired behavior.

```C++
void push_front(int value) {
  // Create a new node
  Item* node = make_node(value);
  // Set the next item of the new node to the current head node
  node->next = head;
  // Set the new node to be the head node
  head = node;
}
```

Next, let's work on the `pop_front` function, which works on a very similar principle. We need to get rid of the first item in the list. We can do this by setting the `head` pointer to the `next` attribute of the current `head` item. But, in order for us to be good memory stewards, we need to clean up the "popped" item first, which we can do by temporarily storing the next item temporarily. Whew! Let's see if this makes more sense in code:

```C++
void pop_front() {
  if(head == nullptr) {
    // Return early, there isn't anything to pop
    return;
  }
  // Temporarily store the pointer to the next item in the list
  Item* temp_head = head->next;
  // Clean up the current head element
  delete head;
  // Reset head
  head = temp_head;
}
```

Pushing to and popping from the back of the list is more complicated because we first need to locate the end of the list. This can be done with a while loop that keeps iterating through the list until the next attribute is equal to `nullptr`, the terminating state. Let's write `push_back` first.

What we need to do is create a new node, then find the last node in the list and set its `next`attribute to be the newly created node. Let's see how this works in code:

```C++
void push_back(int value) {
  // Create a new node
  Item* node = make_node(value);

  // If the list is empty, this is really easy
  if(head == nullptr) {
    head = node;
  } else {
    // Make a copy of the head pointer that we can modify
    Item* temp_head = head;
    // Iterate through the list until we reach the end
    while(temp_head->next != nullptr) {
      temp_head = temp_head->next;
    }

    // Make the last item in the list point to the new node
    temp_head->next = node;

    // Clean up the temp_head pointer
    temp_head = nullptr;
    delete temp_head;
  }
}
```

In this instance, we aren't able to clean up the `temp_head` like we usually pointer because it is in a unique position.  By the end of its usable life, `temp_head` points to the last item in the list, so if we call `delete` on it to remove it, it will take the end item with it, thus removing the node we just added AND wrecking the linked list by getting rid of the `nullptr` marker that allows the rest of the program to tell when it is at the end of the list. Doubly bad. Instead, we first make the `temp_head` pointer point to nothing, and then delete it.

Now let's finish up the operational functions by creating `pop_back`. For this to work, we need to again find the end of the list and get rid of the last item. Then we can delete the the last item. Let's see this in code:

``` C++
void pop_back() {
  if(head == nullptr) {
    // Return early, there isn't anything to pop
    return;
  }
  // Iterate through the list until the next node is the end
  if(head->next == nullptr) {
    // The list only has one item, just delete it
    delete head;
    // Reset the head pointer
    head = nullptr;
  } else {
    // The list has multiple items, locate the 2nd to last item
    // Make a copy of the head pointer that we can modify
    Item* temp_head = head;
    while(temp_head->next->next != nullptr) {
      temp_head = temp_head->next;
    }

    // Delete the last item
    delete temp_head->next;
    // Reset the next attribute of the new last item
    temp_head->next = nullptr;

    // Clean up the temp_head pointer
    temp_head = nullptr;
    delete temp_head;
  }
}
```

In order for us to see what the list looks like, we need to create the `list_nodes` function to print them all out. There isn't any new theory here, just a different application:

```C++
void list_nodes() {
  std::cout << "\nListing all nodes:" << std::endl;
  // Make a copy of the head pointer that we can modify
  Item* temp_head = head;
  // Iterate though the entire list
  while(temp_head != nullptr) {
    // Print out the current item
    std::cout << temp_head->value << std::endl;
    // Move along the pointer
    temp_head = temp_head->next;
  }

  // Clean up the temp_head pointer
  temp_head = nullptr;
  delete temp_head;
}
```

And finally, we need to create a destructor that will free the memory of all of the list items when the `SinglyLinkedList` class is deleted. We'll cover constructors and destructors later, but for now, just know that the destructor is called automatically whenever the class is deleted. Destructors are denoted by having the same name as their parent classes, just with a tilde in front and don't have any return type.

```C++
~SinglyLinkedList() {
  while(head != nullptr) {
    pop_back();
  }
  delete head;
}
```

### Putting it all together

And now, we're done with the `SinglyLinkedList` class! All put together, the class should look like this:

```C++
#include <iostream>

class SinglyLinkedList {
 public:
  void push_front(int value) {
    // Create a new node
    Item* node = make_node(value);
    // Set the next item of the new node to the current head node
    node->next = head;
    // Set the new node to be the head node
    head = node;
  }

  void pop_front() {
    if(head == nullptr) {
     // Return early, there isn't anything to pop
      return;
    }
    // Temporarily store the pointer to the next item in the list
    Item* temp_head = head->next;
    // Clean up the current head element
    delete head;
    // Reset head
    head = temp_head;
  }

  void push_back(int value) {
    // Create a new node
    Item* node = make_node(value);

    // If the list is empty, this is really easy
    if(head == nullptr) {
      head = node;
    } else {
      // Make a copy of the head pointer that we can modify
      Item* temp_head = head;
      // Iterate through the list until we reach the end
      while(temp_head->next != nullptr) {
        temp_head = temp_head->next;
      }

      // Make the last item in the list point to the new node
      temp_head->next = node;

      // Clean up the temp_head pointer
      temp_head = nullptr;
      delete temp_head;
    }
  }

  void pop_back() {
    if(head == nullptr) {
      // Return early, there isn't anything to pop
      return;
    }
    // Iterate through the list until the next node is the end
    if(head->next == nullptr) {
      // The list only has one item, just delete it
      delete head;
      // Reset the head pointer
      head = nullptr;
    } else {
      // The list has multiple items, locate the 2nd to last item
      // Make a copy of the head pointer that we can modify
      Item* temp_head = head;
      while(temp_head->next->next != nullptr) {
        temp_head = temp_head->next;
      }

      // Delete the last item
      delete temp_head->next;
      // Reset the next attribute of the new last item
      temp_head->next = nullptr;

      // Clean up the temp_head pointer
      temp_head = nullptr;
      delete temp_head;
    }
  }

  void list_nodes() {
    std::cout << "\nListing all nodes:" << std::endl;
    // Make a copy of the head pointer that we can modify
    Item* temp_head = head;
    // Iterate though the entire list
    while(temp_head != nullptr) {
      // Print out the current item
      std::cout << temp_head->value << std::endl;
      // Move along the pointer
      temp_head = temp_head->next;
    }

    // Clean up the temp_head pointer
    temp_head = nullptr;
    delete temp_head;
  }

  ~SinglyLinkedList() {
    while(head != nullptr) {
      pop_back();
    }
    delete head;
  }

 private:
  // Item template for the singly linked list
  struct Item {
    int value;
    Item* next = nullptr;
  };

  // Helper for making a node item from a value
  Item* make_node(int value) {
    // Make a new node
    Item* node = new Item();
    // Assign the new node the given value
    node->value = value;

    return node;
  }

  // HEAD of the singly linked list
  Item* head = nullptr;
};
```

Now, to actually use this class, we need a main function and some code. Feel free to stop here and try to write it on your own before looking at the solution below.

```C++
int main() {
  SinglyLinkedList newlist;
  newlist.push_front(10);
  newlist.push_front(3);
  newlist.push_back(10000);
  newlist.push_back(60);
  newlist.list_nodes();
  newlist.pop_front();
  newlist.list_nodes();
  newlist.pop_back();
  newlist.list_nodes();
}
```

### Running the program

Put these two together in the same file and run. With luck there won't be any syntax errors and the output should mirror:

```shell
$ g++ test.cc && ./a.out

Listing all nodes:
3
10
10000
60

Listing all nodes:
10
10000
60

Listing all nodes:
10
10000
$
```

### Generalizing the SinglyLinkedList with C++ template types

Excellent! Now, as a finishing touch (*and extra lesson*), let's make this class more useful by extending its support to beyond just integers. We can easily do this with templates. Simply put, templates enable code to support many different types of objects and treat them the same. The syntax for creating a basic template type is as follows:

```C++
template <class T>
```

Realistically, you could call the template type whatever you want, but calling it T is a common convention used by many C++ programmers. This line is to be placed before the highest level scope that makes use of it, in this case, the `SinglyLinkedList` class.

```C++
#include <iostream>

template <class T>
class SinglyLinkedList {
 ...
```

Next, we'll replace every instance of the `int` type in the class with `T`, which will become the type stored in the `value` attribute of the `Item` class.

```C++
#include <iostream>

template <class T>
class SinglyLinkedList {
 public:
  void push_front(T value) {
    // Create a new node
    Item* node = make_node(value);
    // Set the next item of the new node to the current head node
    node->next = head;
    // Set the new node to be the head node
    head = node;
  }

  void pop_front() {
    if(head == nullptr) {
     // Return early, there isn't anything to pop
      return;
    }
    // Temporarily store the pointer to the next item in the list
    Item* temp_head = head->next;
    // Clean up the current head element
    delete head;
    // Reset head
    head = temp_head;
  }

  void push_back(T value) {
    // Create a new node
    Item* node = make_node(value);

    // If the list is empty, this is really easy
    if(head == nullptr) {
      head = node;
    } else {
      // Make a copy of the head pointer that we can modify
      Item* temp_head = head;
      // Iterate through the list until we reach the end
      while(temp_head->next != nullptr) {
        temp_head = temp_head->next;
      }

      // Make the last item in the list point to the new node
      temp_head->next = node;

      // Clean up the temp_head pointer
      temp_head = nullptr;
      delete temp_head;
    }
  }

  void pop_back() {
    if(head == nullptr) {
      // Return early, there isn't anything to pop
      return;
    }
    // Iterate through the list until the next node is the end
    if(head->next == nullptr) {
      // The list only has one item, just delete it
      delete head;
      // Reset the head pointer
      head = nullptr;
    } else {
      // The list has multiple items, locate the 2nd to last item
      // Make a copy of the head pointer that we can modify
      Item* temp_head = head;
      while(temp_head->next->next != nullptr) {
        temp_head = temp_head->next;
      }

      // Delete the last item
      delete temp_head->next;
      // Reset the next attribute of the new last item
      temp_head->next = nullptr;

      // Clean up the temp_head pointer
      temp_head = nullptr;
      delete temp_head;
    }
  }

  void list_nodes() {
    std::cout << "\nListing all nodes:" << std::endl;
    // Make a copy of the head pointer that we can modify
    Item* temp_head = head;
    // Iterate though the entire list
    while(temp_head != nullptr) {
      // Print out the current item
      std::cout << temp_head->value << std::endl;
      // Move along the pointer
      temp_head = temp_head->next;
    }

    // Clean up the temp_head pointer
    temp_head = nullptr;
    delete temp_head;
  }

  ~SinglyLinkedList() {
    while(head != nullptr) {
      pop_back();
    }
    delete head;
  }

 private:
  // Item template for the singly linked list
  struct Item {
    T value;
    Item* next = nullptr;
  };

  // Helper for making a node item from a value
  Item* make_node(T value) {
    // Make a new node
    Item* node = new Item();
    // Assign the new node the given value
    node->value = value;

    return node;
  }

  // HEAD of the singly linked list
  Item* head = nullptr;
};
```

We'll also need to refactor the main function a bit to deal with this. For the sake of it, we'll test two different data types.

```C++
int main() {
  // Demo with a double list
  {
    SinglyLinkedList<double> newlist;
    newlist.push_front(10.0);
    newlist.push_front(3.14159);
    newlist.push_back(10000.0);
    newlist.push_back(60.64334583);
    newlist.list_nodes();
    newlist.pop_front();
    newlist.list_nodes();
    newlist.pop_back();
    newlist.list_nodes();
  }
  // Demo with a std::string list
  {
    SinglyLinkedList<std::string> list;
    list.push_back("Hello this is text.");
    list.list_nodes();
    list.pop_front();
    list.push_front("What is this?");
    list.list_nodes();
  }
}
```

Notice that the newly added syntax when instantiating the `SinglyLinkedList` class for defining what the template type will be (*the bit within the angle brackets <>*).

The added curly brackets around each of the examples without a control structure like `if`, `else`, `while`, `for`, etc. around it is called an empty scope. Empty scopes do exactly what their name implies; they create an artificial scope, deleting any object instantiated within them after they are completed. These aren't necessary here, but they help to group the code and are incredibly useful in certain instances where the life cycle of an object needs to be controlled more precisely. For that reason, it is a good idea to be able to recognize them and when they are useful.

And thus, our example is completed!