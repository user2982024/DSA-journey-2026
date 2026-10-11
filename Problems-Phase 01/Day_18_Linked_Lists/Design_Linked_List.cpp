/*
===============================================================================
DSA JOURNEY — LINKED LISTS
===============================================================================

PROBLEM: 707. Design Linked List
PLATFORM: LeetCode
DIFFICULTY: Medium
LANGUAGE: C++

===============================================================================
1. PROBLEM STATEMENT
===============================================================================

Design your own linked list implementation.

The linked list must support the following operations:

1. MyLinkedList()
   Initializes an empty linked list.

2. int get(int index)
   Returns the value of the node at the given index.
   Returns -1 if the index is invalid.

3. void addAtHead(int val)
   Inserts a new node containing val at the beginning.

4. void addAtTail(int val)
   Inserts a new node containing val at the end.

5. void addAtIndex(int index, int val)
   Inserts a new node before the node currently at index.
   If index equals the current list length, insert at the tail.
   If index is greater than the current list length, do nothing.

6. void deleteAtIndex(int index)
   Deletes the node at the given index if it exists.

In this implementation, negative indices are handled safely:
- get() returns -1.
- addAtIndex() and deleteAtIndex() do nothing.

===============================================================================
2. OUR APPROACH: DOUBLY LINKED LIST
===============================================================================

We implement a doubly linked list rather than an array or singly linked list.

Each node contains three pieces of information:

    val  -> Stores the node's value.
    prev -> Points to the previous node.
    next -> Points to the next node.

Example:

    nullptr <- 10 <-> 20 <-> 30 -> nullptr
                ^             ^
               head          tail

HEAD:
- Points to the first node.
- head->prev must always be nullptr when the list is nonempty.

TAIL:
- Points to the last node.
- tail->next must always be nullptr when the list is nonempty.

SIZE:
- Stores the total number of nodes.
- An empty list has size == 0.
- A nonempty list has size >= 1.

EMPTY LIST:

    head = nullptr
    tail = nullptr
    size = 0

SINGLE-NODE LIST:

    head ----+
             |
             v
           [10]
             ^
             |
    tail ----+

    head == tail
    head->prev == nullptr
    head->next == nullptr
    size == 1

===============================================================================
3. WHY DID WE CHOOSE A DOUBLY LINKED LIST?
===============================================================================

A singly linked list stores only a next pointer.

A doubly linked list stores both prev and next pointers.

Advantages:
- We can move forward and backward.
- Deleting a known node is straightforward because its predecessor
  is directly accessible through prev.
- Insertion before a known node is straightforward.
- Head and tail operations can be performed in O(1) time.

Trade-off:
- Each node requires additional memory for its prev pointer.
- Every insertion or deletion must maintain both directions correctly.

===============================================================================
4. POINTER CONNECTION RULES
===============================================================================

When inserting a node between A and B:

    A <-> B

The new structure should become:

    A <-> NEW <-> B

The four essential pointer updates are:

    NEW->prev = A;
    NEW->next = B;
    A->next = NEW;
    B->prev = NEW;

When deleting NEW:

    A <-> NEW <-> B

Reconnect the remaining nodes:

    A->next = B;
    B->prev = A;

After reconnecting the list, release NEW's allocated memory with delete.

IMPORTANT:
Updating connections and freeing memory are different operations.
Correct pointer connections do not automatically free a node.

===============================================================================
5. IMPLEMENTATION
===============================================================================
*/

class MyLinkedList {
private:

    /*
    ---------------------------------------------------------------------------
    NODE STRUCTURE
    ---------------------------------------------------------------------------

    Each node stores:
    - val: The integer value.
    - prev: Pointer to the previous node.
    - next: Pointer to the next node.

    The constructor initializes both pointers to nullptr.
    This prevents uninitialized pointers from containing arbitrary addresses.
    */

    struct Node {
        int val;
        Node* prev;
        Node* next;

        Node(int data) {
            val = data;
            prev = nullptr;
            next = nullptr;
        }
    };

    /*
    ---------------------------------------------------------------------------
    PRIVATE DATA MEMBERS
    ---------------------------------------------------------------------------

    head:
        First node in the list.

    tail:
        Last node in the list.

    size:
        Number of nodes currently stored.

    These members are private because outside code should manipulate the list
    through the public methods rather than directly modifying its pointers.
    */

    Node* head;
    Node* tail;
    int size;

public:

    /*
    ===========================================================================
    CONSTRUCTOR: MyLinkedList()
    ===========================================================================

    PURPOSE:
        Initialize an empty linked list.

    INITIAL STATE:
        head = nullptr
        tail = nullptr
        size = 0

    TIME COMPLEXITY: O(1)
    AUXILIARY SPACE: O(1)
    */

    MyLinkedList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    /*
    ===========================================================================
    DESTRUCTOR: ~MyLinkedList()
    ===========================================================================

    PURPOSE:
        Release the memory occupied by all remaining nodes when the linked
        list object is destroyed.

    WHY IS THIS NECESSARY?

    We allocate nodes dynamically using:

        new Node(val);

    Removing a node from the list does not automatically free its memory.
    Similarly, destroying the list object does not automatically free
    dynamically allocated nodes.

    Therefore, we traverse the list and delete each node.

    TIME COMPLEXITY: O(n)
    AUXILIARY SPACE: O(1)

    NOTE:
        Copying this raw-pointer-owning class would require proper copy
        semantics. Copying is disabled below to prevent shallow-copy errors.
    */

    ~MyLinkedList() {
        Node* current = head;

        while (current != nullptr) {
            Node* nextNode = current->next;

            delete current;

            current = nextNode;
        }

        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    /*
    Disable copying because this class owns dynamically allocated nodes.

    A compiler-generated copy would copy the pointer addresses rather than
    independently copy the nodes. That could lead to double deletion and
    dangling pointers.
    */

    MyLinkedList(const MyLinkedList&) = delete;

    MyLinkedList& operator=(const MyLinkedList&) = delete;

    /*
    ===========================================================================
    FUNCTION 1: get(index)
    ===========================================================================

    PURPOSE:
        Return the value stored at the requested index.

    APPROACH:
        1. Check whether the index is valid.
        2. Start traversal from head.
        3. Move forward until the requested index is reached.
        4. Return the node's value.
        5. Return -1 if the index is invalid.

    WHY DO WE CHECK index >= size?

        Valid indices range from 0 through size - 1.

        For example, if size == 3:
            Valid indices: 0, 1, 2
            Invalid index: 3 or greater

    TIME COMPLEXITY:
        O(index), bounded by O(n).

    AUXILIARY SPACE:
        O(1).
    */

    int get(int index) {
        // Reject negative indices and indices outside the list.
        if (index < 0 || index >= size) {
            return -1;
        }

        // Begin at the first node.
        Node* current = head;

        // Traverse until the requested index is reached.
        for (int count = 0; count < index; count++) {
            current = current->next;
        }

        // current points to the node at the requested index.
        return current->val;
    }

    /*
    ===========================================================================
    FUNCTION 2: addAtHead(val)
    ===========================================================================

    PURPOSE:
        Insert a new node at the beginning of the list.

    CASE 1: THE LIST IS EMPTY

        Before:
            head = nullptr
            tail = nullptr

        After:
            head ----+
                     v
                   [NEW]
                     ^
            tail ----+

        Both head and tail must point to the new node.

    CASE 2: THE LIST IS NONEMPTY

        Before:
            head -> A <-> B

        After:
            head -> NEW <-> A <-> B

        Required pointer updates:

            newNode->next = head;
            head->prev = newNode;
            head = newNode;

        The new head's prev pointer must be nullptr.

    TIME COMPLEXITY: O(1)
    AUXILIARY SPACE: O(1) per insertion.
    The newly allocated node itself requires O(1) space.
    */

    void addAtHead(int val) {
        // Dynamically allocate the new node.
        Node* newNode = new Node(val);

        // Case 1: The list is empty.
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }

        // Case 2: The list already contains nodes.
        else {
            newNode->next = head;
            head->prev = newNode;

            head = newNode;
        }

        // The new head must not have a previous node.
        head->prev = nullptr;

        // Maintain the node count.
        size++;
    }

    /*
    ===========================================================================
    FUNCTION 3: addAtTail(val)
    ===========================================================================

    PURPOSE:
        Insert a new node at the end of the list.

    CASE 1: THE LIST IS EMPTY

        Both head and tail point to the new node.

    CASE 2: THE LIST IS NONEMPTY

        Before:
            A <-> B <- tail

        After:
            A <-> B <-> NEW <- tail

        Required pointer updates:

            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;

    Because we maintain a tail pointer, we do not need to traverse the list
    to locate its final node.

    TIME COMPLEXITY: O(1)
    AUXILIARY SPACE: O(1) per insertion.
    */

    void addAtTail(int val) {
        // Create the node to insert.
        Node* newNode = new Node(val);

        // Case 1: The list is empty.
        if (tail == nullptr) {
            head = newNode;
            tail = newNode;
        }

        // Case 2: The list already contains nodes.
        else {
            tail->next = newNode;
            newNode->prev = tail;

            tail = newNode;
        }

        // The new tail must not have a next node.
        tail->next = nullptr;

        // Maintain the node count.
        size++;
    }

    /*
    ===========================================================================
    FUNCTION 4: addAtIndex(index, val)
    ===========================================================================

    PURPOSE:
        Insert a new node before the node currently at index.

    IMPORTANT INDEX RULES:

        index < 0:
            Do nothing in this implementation.

        index == 0:
            Insert at the head.

        index == size:
            Insert at the tail.

        index > size:
            Do nothing.

        Otherwise:
            Insert before the existing node at index.

    EXAMPLE:

        List:
            10 <-> 20 <-> 30

        addAtIndex(1, 15)

        Result:
            10 <-> 15 <-> 20 <-> 30

    APPROACH:

        1. Reject invalid indices.
        2. Use addAtHead for index 0.
        3. Use addAtTail when index == size.
        4. Otherwise, traverse to the existing node at index.
        5. Insert the new node immediately before it.
        6. Update both forward and backward connections.
        7. Increment size exactly once.

    WHY DO WE HANDLE HEAD AND TAIL SEPARATELY?

        Inserting at either boundary changes a boundary pointer.
        Separating these cases avoids dereferencing nonexistent neighbors.

    TIME COMPLEXITY:
        O(index), bounded by O(n).
        Boundary insertions are O(1).

    AUXILIARY SPACE:
        O(1) per insertion.
    */

    void addAtIndex(int index, int val) {
        // Reject invalid indices.
        if (index < 0 || index > size) {
            return;
        }

        // Insertion at the beginning.
        if (index == 0) {
            addAtHead(val);
            return;
        }

        // Insertion at the end.
        if (index == size) {
            addAtTail(val);
            return;
        }

        /*
        We are inserting in the middle.

        Because index is greater than 0 and less than size,
        the node currently at index exists.
        */

        Node* current = head;

        // Find the existing node that should follow the new node.
        for (int count = 0; count < index; count++) {
            current = current->next;
        }

        /*
        Before insertion:

            current->prev <-> current

        After insertion:

            current->prev <-> newNode <-> current
        */

        Node* newNode = new Node(val);

        // Establish the new node's connections.
        newNode->prev = current->prev;
        newNode->next = current;

        // Connect the previous node to the new node.
        current->prev->next = newNode;

        // Connect the current node back to the new node.
        current->prev = newNode;

        // Maintain the node count.
        size++;
    }

    /*
    ===========================================================================
    FUNCTION 5: deleteAtIndex(index)
    ===========================================================================

    PURPOSE:
        Delete the node at the requested index if it exists.

    IMPORTANT LESSON FROM OUR DEBUGGING SESSION:

        Updating pointers is not the same as deleting a node from memory.

        We must:
            1. Locate the target node.
            2. Reconnect its neighbors.
            3. Delete the target node.
            4. Decrease size exactly once.

    APPROACH:

        1. Reject invalid indices.
        2. Traverse to the target node.
        3. If a previous node exists, connect it to the target's next node.
           Otherwise, update head.
        4. If a next node exists, connect it back to the target's previous node.
           Otherwise, update tail.
        5. Delete the target node.
        6. Decrement size.

    THIS SINGLE APPROACH HANDLES ALL THREE CASES:

        A. Deleting the head.
        B. Deleting a middle node.
        C. Deleting the tail.

    It also correctly handles a single-node list.

    EXAMPLE 1: DELETE A MIDDLE NODE

        Before:
            10 <-> 20 <-> 30

        Delete index 1.

        After:
            10 <-> 30

    EXAMPLE 2: DELETE THE HEAD

        Before:
            10 <-> 20 <-> 30

        Delete index 0.

        After:
            20 <-> 30

        The new head's prev pointer must be nullptr.

    EXAMPLE 3: DELETE THE TAIL

        Before:
            10 <-> 20 <-> 30

        Delete index 2.

        After:
            10 <-> 20

        The new tail's next pointer must be nullptr.

    EXAMPLE 4: DELETE THE ONLY NODE

        Before:
            head -> [10] <- tail

        After:
            head = nullptr
            tail = nullptr
            size = 0

    TIME COMPLEXITY:
        O(index), bounded by O(n).
        Locating the target is the potentially expensive operation.
        Reconnecting and deleting the node takes O(1) time.

    AUXILIARY SPACE:
        O(1).
    */

    void deleteAtIndex(int index) {
        // Reject negative indices and indices outside the list.
        if (index < 0 || index >= size) {
            return;
        }

        // Locate the node that must be deleted.
        Node* target = head;

        for (int count = 0; count < index; count++) {
            target = target->next;
        }

        /*
        Reconnect the previous node, if one exists.

        If target is the head, there is no previous node.
        In that case, update head to the next node.
        */

        if (target->prev != nullptr) {
            target->prev->next = target->next;
        }
        else {
            head = target->next;
        }

        /*
        Reconnect the next node, if one exists.

        If target is the tail, there is no next node.
        In that case, update tail to the previous node.
        */

        if (target->next != nullptr) {
            target->next->prev = target->prev;
        }
        else {
            tail = target->prev;
        }

        /*
        IMPORTANT MEMORY-MANAGEMENT STEP:

        We have already reconnected the remaining nodes.
        The target node is no longer part of the list, so release its memory.
        */

        delete target;

        // Maintain the node count.
        size--;
    }
};

/*
===============================================================================
6. COMPLEXITY ANALYSIS
===============================================================================

Let n be the current number of nodes in the linked list.

+----------------+-------------------+------------------------+
| Operation      | Time Complexity   | Auxiliary Space        |
+----------------+-------------------+------------------------+
| Constructor    | O(1)              | O(1)                   |
| get(index)     | O(index), O(n)    | O(1)                   |
| addAtHead      | O(1)              | O(1) per new node      |
| addAtTail      | O(1)              | O(1) per new node      |
| addAtIndex     | O(index), O(n)    | O(1) per new node      |
| deleteAtIndex  | O(index), O(n)    | O(1)                   |
| Destructor     | O(n)              | O(1)                   |
+----------------+-------------------+------------------------+

EXPLANATION:

1. get(index):
   We may need to traverse index nodes to reach the requested position.

2. addAtHead():
   We already have head, so insertion requires a constant number of pointer
   updates.

3. addAtTail():
   We maintain tail, so locating the final node does not require traversal.

4. addAtIndex():
   Insertion may require traversing to the target position. Once there,
   pointer updates take constant time.

5. deleteAtIndex():
   Finding the target may take O(n) time. Reconnecting its neighbors takes
   O(1) time.

6. Destructor:
   Every remaining node is deleted exactly once, so total time is O(n).

SPACE COMPLEXITY OF THE STORED LIST:

    O(n)

Each node requires memory for its value and two pointers.

The additional working space used by individual operations is O(1).

===============================================================================
7. ISSUES WE FACED AND HOW WE LEARNED FROM THEM
===============================================================================

ISSUE 1: FORGETTING THE BACKWARD CONNECTION

Problem:
    Updating only next can leave prev pointing to the wrong node.

Lesson:
    Every insertion or deletion must maintain both directions.

ISSUE 2: HANDLING THE EMPTY LIST

Problem:
    Inserting into an empty list cannot rely on an existing head or tail.

Lesson:
    When the first node is inserted, both head and tail must point to it.

ISSUE 3: HANDLING A SINGLE NODE

Problem:
    Deleting the only node must not leave head or tail pointing to deleted
    memory.

Lesson:
    The generic deletion logic updates head and tail correctly when either
    neighbor is absent.

ISSUE 4: INVALID INDEXES

Problem:
    Traversing an invalid index can cause a null-pointer dereference.

Lesson:
    Validate the index before traversal.

ISSUE 5: UPDATING POINTERS IN THE WRONG ORDER

Problem:
    Overwriting a pointer too early can lose access to the node that must
    be reconnected.

Lesson:
    Preserve the target node and its neighboring relationships while
    performing pointer updates.

ISSUE 6: MEMORY LEAKS

Problem:
    Removing a node from the chain without calling delete leaves its
    dynamically allocated memory unreleased.

Lesson:
    Reconnect the remaining list, then delete the removed node.

ISSUE 7: SIZE INCONSISTENCY

Problem:
    Decrementing size on an invalid deletion or incrementing it more than
    once makes later index checks incorrect.

Lesson:
    Change size only after a successful insertion or deletion.

===============================================================================
8. IMPORTANT POINTER INVARIANTS
===============================================================================

After every public operation, these properties should remain true:

1. size == 0 if and only if head == nullptr and tail == nullptr.

2. If size > 0:
       head != nullptr
       tail != nullptr

3. If the list is nonempty:
       head->prev == nullptr
       tail->next == nullptr

4. If node A's next pointer points to node B:
       B->prev must point to A.

5. If node B's prev pointer points to node A:
       A->next must point to B.

6. Traversing from head through next must visit exactly size nodes.

7. After any successful insertion:
       size increases by exactly one.

8. After any successful deletion:
       size decreases by exactly one.

9. Invalid operations must not modify the list.

These invariants are useful when debugging linked-list implementations.

===============================================================================
9. MANUAL TEST CASES
===============================================================================

TEST 1: EMPTY LIST

    MyLinkedList list;

    list.get(0);              // -1
    list.deleteAtIndex(0);    // No operation

Expected:
    head == nullptr
    tail == nullptr
    size == 0

TEST 2: INSERT AT HEAD

    list.addAtHead(10);
    list.addAtHead(20);

Expected:
    20 <-> 10

TEST 3: INSERT AT TAIL

    list.addAtTail(30);

Expected:
    20 <-> 10 <-> 30

TEST 4: INSERT AT INDEX

    list.addAtIndex(1, 15);

Expected:
    20 <-> 15 <-> 10 <-> 30

TEST 5: GET VALID AND INVALID INDEXES

    list.get(0);    // 20
    list.get(1);    // 15
    list.get(4);    // -1
    list.get(-1);   // -1

TEST 6: DELETE A MIDDLE NODE

    list.deleteAtIndex(1);

Expected:
    20 <-> 10 <-> 30

TEST 7: DELETE THE HEAD

    list.deleteAtIndex(0);

Expected:
    10 <-> 30

TEST 8: DELETE THE TAIL

    list.deleteAtIndex(1);

Expected:
    10

TEST 9: DELETE THE LAST NODE

    list.deleteAtIndex(0);

Expected:
    head == nullptr
    tail == nullptr
    size == 0

TEST 10: INVALID INSERTION

    list.addAtIndex(5, 100);

Expected:
    The list remains unchanged when index > size.

TEST 11: SINGLE-NODE HEAD AND TAIL

    list.addAtHead(42);

Expected:
    head == tail
    head->prev == nullptr
    head->next == nullptr
    size == 1

===============================================================================
10. FINAL TAKEAWAYS
===============================================================================

This problem combines several fundamental C++ and DSA concepts:

- Classes and encapsulation.
- Constructors and destructors.
- Structures and pointers.
- Dynamic memory allocation using new.
- Memory deallocation using delete.
- Doubly linked list traversal.
- Head and tail management.
- Insertion and deletion at boundaries and middle positions.
- Index validation.
- Maintaining data-structure invariants.
- Time and space complexity analysis.

The most important lesson from this problem is that a linked list is not merely
a sequence of values. It is a network of nodes connected through pointers.

Correctness depends on preserving the connections, maintaining head and tail,
keeping size accurate, and managing allocated memory.

A solution that passes test cases is a milestone. Understanding why the pointer
updates work is what prepares you to solve unfamiliar linked-list problems.

===============================================================================
END OF STUDY NOTES
===============================================================================
*/