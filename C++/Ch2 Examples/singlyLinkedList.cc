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