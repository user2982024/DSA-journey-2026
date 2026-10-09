/*
===============================================================================
PROBLEM: Remove Nth Node From End of List
PLATFORM: LeetCode
PROBLEM NUMBER: 19
DIFFICULTY: Medium
TOPIC: Linked Lists, Pointer Manipulation, Two-Pass Traversal
LANGUAGE: C++

AUTHOR'S APPROACH:
Two-pass linked-list traversal using a node count and a pointer to the
node immediately preceding the target node.

TIME COMPLEXITY: O(n)
AUXILIARY SPACE COMPLEXITY: O(1)

===============================================================================
1. PROBLEM DESCRIPTION
===============================================================================

Given the head of a singly linked list, remove the nth node from the end of
the list and return the head of the modified list.

A singly linked list consists of nodes where each node contains:
    1. A value.
    2. A pointer to the next node.

Each node points only forward. Therefore, we cannot directly move backward
from the last node to the previous node.

The challenge is to identify the node that must be removed and correctly
update the links so that the remaining list stays connected.

-------------------------------------------------------------------------------
2. EXAMPLES
-------------------------------------------------------------------------------

Example 1:

Input:
    head = [1, 2, 3, 4, 5]
    n = 2

Explanation:

    Original list:

    1 -> 2 -> 3 -> 4 -> 5 -> nullptr

    Counting from the end:

    5 is the 1st node from the end.
    4 is the 2nd node from the end.

    Therefore, node 4 must be removed.

Output:
    [1, 2, 3, 5]


Example 2:

Input:
    head = [1]
    n = 1

Explanation:

    The list contains only one node.

    Removing the 1st node from the end removes the only node.

Output:
    []


Example 3:

Input:
    head = [1, 2]
    n = 1

Explanation:

    The last node, containing 2, must be removed.

Output:
    [1]


Example 4:

Input:
    head = [1, 2]
    n = 2

Explanation:

    The 2nd node from the end is the head node, containing 1.

    Removing the head leaves only node 2.

Output:
    [2]


===============================================================================
3. UNDERSTANDING THE PROBLEM
===============================================================================

The phrase "nth node from the end" means that counting starts from the
last node and moves backward conceptually.

For example:

    10 -> 20 -> 30 -> 40 -> 50 -> nullptr

If n = 1, remove node 50.
If n = 2, remove node 40.
If n = 3, remove node 30.
If n = 4, remove node 20.
If n = 5, remove node 10.

However, because this is a SINGLY linked list, we cannot traverse backward.

We must find another way to determine the target node.

The key observation is:

    If the list contains L nodes, the nth node from the end is located at
    position (L - n + 1) when counting from the beginning.

For deletion, we generally need to reach the node immediately BEFORE the
target node so that its next pointer can skip the target.

There is one special situation:

    If L - n == 0, the target is the head itself.

In that situation, we must update the head pointer.


===============================================================================
4. APPROACH: TWO-PASS TRAVERSAL
===============================================================================

We solve the problem using two traversals of the linked list.

PASS 1: COUNT THE NODES
----------------------

Initialize a pointer named current1 at the head.

Traverse the complete linked list and increment a counter for each node.

After this traversal, the counter contains the total number of nodes.

Let this count be L.

PASS 2: FIND THE NODE BEFORE THE TARGET
---------------------------------------

The zero-based distance from the beginning to the target node is:

    L - n

There are two cases.

CASE 1: L - n == 0
------------------

The target is the head node.

Update the head:

    head = head->next;

Return the updated head.

CASE 2: L - n > 0
-----------------

The target is not the head.

Initialize a second pointer, current2, at the head.

Use an iterator initialized to 1.

Move current2 forward while:

    iterator < L - n

After the traversal, current2 points to the node immediately before the
target node.

Remove the target by bypassing it:

    current2->next = current2->next->next;

Finally, return head.


===============================================================================
5. COMPLETE C++ SOLUTION
===============================================================================
*/

#include <iostream>
using namespace std;

/*
LeetCode provides the ListNode definition and the testing environment.

The following definition is included here only to make the explanation
self-contained. When submitting to LeetCode, use its provided definition
instead of declaring ListNode a second time.

struct ListNode {
    int val;
    ListNode* next;

    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};
*/

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {

        // Pointer for the first traversal.
        ListNode* current1 = head;

        // Pointer for the second traversal.
        ListNode* current2 = head;

        // Stores the total number of nodes.
        int size = 0;

        // Tracks the position during the second traversal.
        int iterator = 1;

        /*
        -------------------------------------------------------------------
        PASS 1: COUNT THE TOTAL NUMBER OF NODES
        -------------------------------------------------------------------

        Move current1 through the complete list.

        Increment size once for every node.

        At the end:
            current1 == nullptr
            size == total number of nodes
        */

        while (current1 != nullptr) {
            current1 = current1->next;
            size++;
        }

        /*
        -------------------------------------------------------------------
        CASE 1: REMOVE THE HEAD NODE
        -------------------------------------------------------------------

        If size - n == 0, the target is the head.

        For example:

            1 -> 2 -> 3 -> nullptr
            n = 3

        size - n = 3 - 3 = 0

        The head must be removed.

        Move head to the second node and return the new head.
        */

        if (size - n == 0) {
            head = head->next;
            return head;
        }

        /*
        -------------------------------------------------------------------
        CASE 2: REMOVE A NODE OTHER THAN THE HEAD
        -------------------------------------------------------------------

        Move current2 until it points to the node immediately before
        the target node.

        The target's zero-based position is size - n.

        Because iterator starts at 1, we stop when iterator reaches
        size - n.
        */

        else {
            while (iterator < size - n) {
                current2 = current2->next;
                iterator++;
            }

            /*
            Bypass the target node.

            If the list is:

                1 -> 2 -> 3 -> 4 -> 5 -> nullptr

            And current2 points to node 3, then:

                current2->next = current2->next->next;

            changes:

                3 -> 4 -> 5

            into:

                3 ------> 5

            Node 4 is no longer part of the linked list.
            */

            current2->next = current2->next->next;
        }

        // The original head remains valid in this case.
        return head;
    }
};


/*
===============================================================================
6. DRY RUN: EXAMPLE 1
===============================================================================

Input:

    List: 1 -> 2 -> 3 -> 4 -> 5 -> nullptr
    n = 2

PASS 1: COUNT NODES
-------------------

Initially:

    current1 = head
    size = 0

Iteration 1:
    current1 points to 1
    Move to 2
    size = 1

Iteration 2:
    Move to 3
    size = 2

Iteration 3:
    Move to 4
    size = 3

Iteration 4:
    Move to 5
    size = 4

Iteration 5:
    Move to nullptr
    size = 5

The loop stops.

Now:

    size = 5
    n = 2

Calculate:

    size - n = 5 - 2 = 3

Since the result is not zero, the target is not the head.


PASS 2: FIND THE PREVIOUS NODE
------------------------------

Initially:

    current2 = head       // Node 1
    iterator = 1

The loop condition is:

    iterator < size - n

    iterator < 3

Iteration 1:
    current2 moves from node 1 to node 2.
    iterator becomes 2.

Iteration 2:
    current2 moves from node 2 to node 3.
    iterator becomes 3.

Now iterator < 3 is false.

Therefore:

    current2 points to node 3.

The target is current2->next, which is node 4.


REMOVE THE TARGET
-----------------

Execute:

    current2->next = current2->next->next;

Before:

    3 -> 4 -> 5

After:

    3 ------> 5

The final list is:

    1 -> 2 -> 3 -> 5 -> nullptr

Output:

    [1, 2, 3, 5]


===============================================================================
7. DRY RUN: REMOVING THE HEAD
===============================================================================

Input:

    List: 1 -> 2 -> 3 -> nullptr
    n = 3

First traversal:

    size = 3

Calculate:

    size - n = 3 - 3 = 0

The condition is true:

    if (size - n == 0)

Execute:

    head = head->next;

Now head points to node 2.

The resulting list is:

    2 -> 3 -> nullptr

Return head.

Output:

    [2, 3]


===============================================================================
8. EDGE CASES
===============================================================================

EDGE CASE 1: A SINGLE NODE
--------------------------

Input:
    [1], n = 1

Node count:
    size = 1

Calculation:
    size - n = 0

The head moves to head->next, which is nullptr.

Output:
    []


EDGE CASE 2: REMOVE THE LAST NODE
---------------------------------

Input:
    [1, 2, 3, 4, 5], n = 1

Calculation:
    size - n = 5 - 1 = 4

current2 stops at node 4.

The link is updated to:

    4->next = 4->next->next

Since node 5 is the last node, its next pointer is nullptr.

The result is:

    1 -> 2 -> 3 -> 4 -> nullptr


EDGE CASE 3: REMOVE THE HEAD
----------------------------

Input:
    [1, 2, 3], n = 3

Calculation:
    size - n = 0

Update the head to the next node.

Output:
    [2, 3]


EDGE CASE 4: TWO NODES, REMOVE THE LAST
---------------------------------------

Input:
    [1, 2], n = 1

Calculation:
    size - n = 2 - 1 = 1

current2 remains at node 1 because iterator starts at 1.

Update:

    current2->next = current2->next->next;

The result is:

    1 -> nullptr


EDGE CASE 5: TWO NODES, REMOVE THE HEAD
---------------------------------------

Input:
    [1, 2], n = 2

Calculation:
    size - n = 0

Update head to node 2.

Output:
    [2]


===============================================================================
9. IMPORTANT POINTER CONCEPTS
===============================================================================

CONCEPT 1: WHY DO WE NEED TWO POINTERS?
---------------------------------------

current1 is used to count the nodes.

After the first traversal, current1 reaches nullptr. We cannot use it to
traverse the list again because it no longer points to the head.

current2 independently starts at head and is used to locate the node
before the target.

The two pointers have different responsibilities.


CONCEPT 2: WHY DO WE COUNT THE NODES FIRST?
-------------------------------------------

In a singly linked list, there is no direct backward traversal.

Counting the nodes gives us the total length L.

Once L is known, the position of the target can be calculated using:

    L - n

This transforms a problem stated from the end into a forward traversal
from the beginning.


CONCEPT 3: WHY DO WE HANDLE THE HEAD SEPARATELY?
------------------------------------------------

For nodes other than the head, we can change the previous node's next
pointer to bypass the target.

But the head has no previous node.

Therefore, removing the head requires changing the head pointer itself:

    head = head->next;


CONCEPT 4: WHY DOES current2 STOP BEFORE THE TARGET?
----------------------------------------------------

We need to modify the next pointer of the node before the target.

For example:

    1 -> 2 -> 3 -> 4 -> nullptr

To remove node 3, we need access to node 2.

We update:

    node2->next = node2->next->next;

The resulting list is:

    1 -> 2 -> 4 -> nullptr

If current2 were positioned at node 3 instead, we would not have the
previous node needed for this deletion operation.


CONCEPT 5: WHAT DOES nullptr MEAN HERE?
---------------------------------------

nullptr indicates that a pointer does not point to a valid object.

In this problem, nullptr marks the end of the linked list.

A valid operation:

    current2->next = current2->next->next;

requires current2 and current2->next to point to valid nodes.

The problem constraints guarantee 1 <= n <= size, and the algorithm
ensures that current2 reaches the node immediately before the target
in the non-head case.

Never dereference a null pointer.


===============================================================================
10. COMMON MISTAKES TO AVOID
===============================================================================

MISTAKE 1: FORGETTING THE HEAD CASE
----------------------------------

If the target is the head, there is no previous node to modify.

Always handle this situation separately or use a dummy-node technique.


MISTAKE 2: OFF-BY-ONE ERRORS
----------------------------

The target's zero-based position is:

    size - n

The previous node is at one-based position:

    size - n

when size - n > 0.

The loop condition in this implementation is:

    iterator < size - n

because iterator starts at 1 and current2 initially points to the first
node.

Changing the initial value of iterator may require changing the loop
condition too.


MISTAKE 3: USING current1 AFTER THE FIRST TRAVERSAL
--------------------------------------------------

After counting the nodes, current1 is nullptr.

Do not attempt to use current1 to find the target unless you reset it
to head.


MISTAKE 4: DEREFERENCING nullptr
--------------------------------

Expressions such as:

    current2->next

are only safe when current2 points to a valid node.

Pointer checks must match the operations performed inside the loop.


MISTAKE 5: CONFUSING THE TARGET WITH ITS PREVIOUS NODE
-----------------------------------------------------

To delete a non-head node, current2 must point to the node immediately
before the target.

The target itself is:

    current2->next

The link update skips that target.


===============================================================================
11. CORRECTNESS EXPLANATION
===============================================================================

Let L be the total number of nodes and n the requested position from
the end.

After the first traversal, size equals L.

CASE 1: L - n == 0
------------------

This means n == L, so the target is the first node.

Updating head to head->next removes the target and correctly returns
the modified list.

CASE 2: L - n > 0
-----------------

The second traversal advances current2 to the node at position L - n
when counting from 1.

This is the node immediately before the target, which is at position
L - n + 1.

The assignment:

    current2->next = current2->next->next;

bypasses the target and connects the preceding node to the target's
successor.

All other nodes retain their relative order.

Therefore, the algorithm removes exactly the nth node from the end
and returns the correct head of the modified list.


===============================================================================
12. COMPLEXITY ANALYSIS
===============================================================================

TIME COMPLEXITY: O(n)
---------------------

Let n denote the total number of nodes in this complexity section.

The first traversal visits all nodes:

    O(n)

The second traversal visits at most n - 1 nodes:

    O(n)

The total is:

    O(n) + O(n) = O(2n) = O(n)

We ignore constant factors in Big-O notation.

A list with twice as many nodes requires work proportional to twice
the length, up to constant factors.


AUXILIARY SPACE COMPLEXITY: O(1)
--------------------------------

The algorithm uses a fixed number of pointers and integer variables:

    current1
    current2
    size
    iterator

The number of variables does not grow with the input size.

No additional array or data structure proportional to the list length
is created.

Therefore:

    Auxiliary space = O(1)


===============================================================================
13. ALTERNATIVE APPROACH: TWO POINTERS WITH A GAP
===============================================================================

Another common solution uses a dummy node and two pointers.

The idea is to advance one pointer n nodes ahead of the other. Then move
both pointers together until the leading pointer reaches the end.

The trailing pointer will then be immediately before the target.

A dummy node placed before head simplifies deleting the head because
the head also has a preceding node: the dummy node.

This approach still takes:

    Time: O(n)
    Auxiliary space: O(1)

The two-pass approach implemented above is easier to derive initially
because it first counts the nodes and then calculates the target position.

The gap-based approach is a useful follow-up exercise.


===============================================================================
14. KEY TAKEAWAYS
===============================================================================

1. A singly linked list supports forward traversal, not direct backward
   traversal.

2. Counting nodes allows us to convert a position from the end into
   a position from the beginning.

3. Removing a non-head node requires access to its previous node.

4. Removing the head requires updating the head pointer itself.

5. Pointer assignments must preserve the correct links.

6. Off-by-one errors are common in linked-list traversal, so trace the
   pointer position carefully.

7. Multiple linear traversals still result in O(n) time complexity.

8. A fixed number of pointers means O(1) auxiliary space.

9. The dummy-node and two-pointer-gap approach is an important alternative
   worth learning after understanding the two-pass solution.


===============================================================================
15. FINAL SUMMARY
===============================================================================

Problem:
    Remove the nth node from the end of a singly linked list.

Chosen strategy:
    Count nodes, calculate the target position, traverse to its previous
    node, and bypass the target.

Special case:
    If size - n == 0, remove the head.

Time complexity:
    O(n)

Auxiliary space complexity:
    O(1)

Result:
    Accepted on LeetCode.

The main lesson is that understanding pointer positions and carefully
updating links is more important than writing the code quickly.

===============================================================================
END OF FILE
===============================================================================
