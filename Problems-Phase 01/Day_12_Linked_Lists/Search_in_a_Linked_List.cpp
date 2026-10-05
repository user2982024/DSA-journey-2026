/*
===============================================================================
Problem: Search in Linked List
Platform: GeeksforGeeks
Topic: Singly Linked List
Difficulty: Easy

Problem Statement
-----------------
Given the head of a singly linked list and an integer key, determine whether
the key exists in the linked list.

Return:
    true  -> if the key is present
    false -> if the key is not present

Example 1:
    Linked List: 10 -> 20 -> 30 -> nullptr
    key = 20
    Output: true

Example 2:
    Linked List: 10 -> 20 -> 30 -> nullptr
    key = 50
    Output: false

===============================================================================
1. CORE IDEA
===============================================================================

A singly linked list does not provide direct/random access like an array.

For example:

    head
      |
      v
    10 -> 20 -> 30 -> nullptr

To search for a value, we start at the head and visit each node one by one.

At every node:

    1. Check whether current->data == key.
    2. If yes, return true immediately.
    3. Otherwise move current to current->next.
    4. If current becomes nullptr, the entire list has been searched and
       the key does not exist, so return false.

This is called LINKED-LIST TRAVERSAL.

===============================================================================
2. WHY WE USE A SEPARATE POINTER 'current'
===============================================================================

We should not move 'head' while searching because head represents the
beginning of the linked list.

Instead:

    Node* current = head;

Now:

    head     -> remains at the first node
    current  -> moves through the list

Example:

    head
      |
      v
    10 -> 20 -> 30 -> nullptr

Initially:

    current -> 10

After one iteration:

    current -> 20

After another:

    current -> 30

Finally:

    current -> nullptr

The original head remains unchanged.

===============================================================================
3. STEP-BY-STEP DRY RUN
===============================================================================

Consider:

    10 -> 20 -> 30 -> 40 -> nullptr

Search for:

    key = 30

Initial state:

    current -> 10

Iteration 1:
    current->data = 10
    10 == 30 ? No

    Move:
        current = current->next

Now:

    current -> 20

Iteration 2:
    current->data = 20
    20 == 30 ? No

    Move:
        current = current->next

Now:

    current -> 30

Iteration 3:
    current->data = 30
    30 == 30 ? Yes

Therefore:

    return true;

We stop immediately. There is no reason to continue searching.

===============================================================================
4. CASE WHERE THE KEY DOES NOT EXIST
===============================================================================

List:

    10 -> 20 -> 30 -> nullptr

key:

    50

Traversal:

    current -> 10    (10 != 50)
    current -> 20    (20 != 50)
    current -> 30    (30 != 50)
    current -> nullptr

Now:

    current == nullptr

This means there are no more nodes.

Therefore:

    return false;

===============================================================================
5. EDGE CASES
===============================================================================

Edge Case 1: Empty Linked List
--------------------------------

    head = nullptr

There are no nodes to search.

The loop:

    while (current != nullptr)

will not execute, and the function returns false.

Note:
The current GFG constraints may guarantee a non-empty list, but handling
nullptr makes the function robust and safe.

Edge Case 2: One Node
---------------------

    10 -> nullptr

key = 10

    10 == 10

Return true.

key = 50

    10 != 50
    current becomes nullptr

Return false.

Edge Case 3: Key is at the First Node
--------------------------------------

    20 -> 30 -> 40 -> nullptr

key = 20

The first comparison succeeds, so we immediately return true.

Edge Case 4: Key is at the Last Node
-------------------------------------

    20 -> 30 -> 40 -> nullptr

key = 40

We traverse through 20 and 30, then find 40 and return true.

Edge Case 5: Duplicate Values
------------------------------

    10 -> 20 -> 20 -> 30 -> nullptr

key = 20

We only need to know whether the key exists.

Therefore, as soon as the first 20 is found, return true.

We do NOT need to find every occurrence.

Edge Case 6: Negative Values
----------------------------

The algorithm does not depend on values being positive.

For example:

    -10 -> -5 -> 0 -> 8 -> nullptr

key = -5

The normal comparison works correctly.

===============================================================================
6. WHERE THE MAIN THINKING HAPPENS
===============================================================================

The problem is simple, but it teaches an important linked-list pattern:

    current = head

    while (current != nullptr) {
        check current
        move current forward
    }

This pattern will appear repeatedly in linked-list problems.

The most important thing is understanding:

    current = current->next;

This does NOT move the node itself.

It moves the pointer 'current' to the next node.

For example:

    10 -> 20 -> 30

If:

    current -> 10

then after:

    current = current->next;

we have:

    current -> 20

The linked list itself has not changed.

===============================================================================
7. COMMON MISTAKES
===============================================================================

Mistake 1: Forgetting to move current
--------------------------------------

Incorrect:

    while (current != nullptr) {
        if (current->data == key) {
            return true;
        }
    }

If the key is not found, current never changes, so the loop becomes infinite.

Correct idea:

    current = current->next;

Mistake 2: Accessing current->data after current becomes nullptr
----------------------------------------------------------------

You must make sure current is not nullptr before accessing:

    current->data

The condition:

    while (current != nullptr)

provides this safety.

Mistake 3: Moving head instead of current
------------------------------------------

Avoid doing:

    head = head->next;

for a search operation.

That changes the head pointer and loses the original starting point.

Use:

    Node* current = head;

and move current instead.

Mistake 4: Continuing after finding the key
-------------------------------------------

Once the key is found:

    return true;

There is no reason to continue traversing the list.

===============================================================================
8. SOLUTION
===============================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
Structure of a singly linked list node.

Each node contains:
    data -> the value stored in the node
    next -> pointer to the next node
*/
class Node {
public:
    int data;
    Node* next;

    Node(int x) {
        data = x;
        next = nullptr;
    }
};

class Solution {
public:

    /*
    Function: searchKey

    Purpose:
        Search for 'key' in the linked list.

    Parameters:
        head -> pointer to the first node
        key  -> value we want to find

    Return:
        true  -> key exists
        false -> key does not exist
    */
    bool searchKey(Node* head, int key) {

        // Start traversal from the first node.
        Node* current = head;

        // Continue until we reach the end of the linked list.
        while (current != nullptr) {

            // Check the current node's value.
            if (current->data == key) {
                return true;
            }

            // Move to the next node.
            current = current->next;
        }

        // We reached the end without finding the key.
        return false;
    }
};

/*
===============================================================================
9. COMPLEXITY ANALYSIS
===============================================================================

Time Complexity: O(n)

Why?

In the worst case, the key:
    - is at the last node, or
    - does not exist.

Then we may visit all n nodes.

Best case:
    O(1)

If the key is present in the first node, we return immediately.

Worst case:
    O(n)

Average case:
    O(n)

Therefore, the overall time complexity is:

    O(n)

Auxiliary Space Complexity: O(1)

Why?

We only use one extra pointer:

    Node* current

No array, vector, hash map, recursion stack, or other data structure grows
with the size of the linked list.

Therefore:

    Auxiliary Space = O(1)

===============================================================================
10. IMPORTANT LINKED-LIST PATTERN LEARNED
===============================================================================

For simple traversal problems, remember this template:

    Node* current = head;

    while (current != nullptr) {

        // Work with current

        current = current->next;
    }

This is one of the most fundamental patterns in singly linked lists.

===============================================================================
11. FINAL TAKEAWAY
===============================================================================

The complete thought process is:

    Start at head
        |
        v
    Check current node
        |
        +---- key found? ---- Yes ---> return true
        |
        No
        |
        v
    Move to current->next
        |
        v
    current == nullptr?
        |
        Yes
        |
        v
    return false

The problem is fundamentally a traversal problem.

The most important concept is not the code itself, but understanding that
a singly linked list must generally be traversed node by node because it
does not support direct indexing like an array.

===============================================================================
12. GITHUB NOTE
===============================================================================

Suggested filename:

    Search_in_Linked_List.cpp

Suggested GitHub commit message:

    Solve Search in Linked List using traversal

Suggested short commit description:

    Implemented linear traversal solution for searching a key in a singly
    linked list. Added edge-case handling and O(n) time / O(1) auxiliary
    space analysis.

===============================================================================
END
===============================================================================
*/

int main() {

    /*
    Optional local testing.

    This main() is NOT required by GeeksforGeeks because GFG provides its
    own driver code. It is included only so the file can also be compiled
    and tested locally.

    You can remove main() before submitting to GFG if necessary.
    */

    Node* head = new Node(10);
    head->next = new Node(20);
    head->next->next = new Node(30);
    head->next->next->next = new Node(40);

    Solution solution;

    cout << boolalpha;

    cout << "Search 30: "
         << solution.searchKey(head, 30) << '\n';

    cout << "Search 50: "
         << solution.searchKey(head, 50) << '\n';

    // Optional cleanup for local testing.
    Node* current = head;

    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }

    return 0;
}