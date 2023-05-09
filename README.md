# Push And Pop

**Introduction**

This project provides two implementations of a thread-safe push and pop data structure, called QuickPush and QuickPop. Both implementations are derived from an abstract class PushAndPop, which provides basic functionality for push and pop operations.

The two implementations:
1. QuickPush O(1) & RegularPop O(n)
2. QuickPop O(1) & RegularPush O(n)


**Prerequisites**

This project requires a compiler that supports the C++20 standard.


**Usage**

Clone the repository: git clone https://github.com/avivshalom1/Una.git
Navigate to the project directory: cd push_and_pop

To use the push and pop data structure, include the appropriate header file:
#include "push_and_pop.hpp" 

To create an instance of the data structure, simply call the constructor. 
You may optionally provide a comparison function for sorting the data (default is std::less<T>()):

QuickPush<int> myPush;             // create instance of QuickPush with int data
QuickPop<std::string> myPop([](const std::string& lhs, const std::string& rhs) 
                              { return lhs.size() < rhs.size(); });  // create instance of QuickPop with std::string data, sorted by string length
  
To push data onto the data structure, use the Push function:                                                                                     myPush.Push(42);           // push 42 onto the QuickPush data structure
myPop.Push("hello world"); // push "hello world" onto the QuickPop data structure
                          
To pop data from the data structure, use the Pop function:
int myInt = myPush.Pop();           // pop data from QuickPush data structure into myInt
std::string myString = myPop.Pop(); // pop data from QuickPop data structure into myString
                                                               
  
                                                               
**Implementation Details**

Both implementations are thread-safe and use a doubly-linked list for storing the data. QuickPush sorts the data in ascending order, while QuickPop returns the maximum value in the data structure.

The PushAndPop abstract class provides basic functionality for push and pop operations. It defines a nested Node class, which represents a node in the doubly-linked list. The PushAndPop class also provides a counting semaphore for synchronizing push and pop operations.

The QuickPush and QuickPop classes derive from the PushAndPop class and implement the push and pop operations. QuickPush sorts the data in the list by inserting new nodes in the correct order. QuickPop finds the maximum value in the list and removes it.
