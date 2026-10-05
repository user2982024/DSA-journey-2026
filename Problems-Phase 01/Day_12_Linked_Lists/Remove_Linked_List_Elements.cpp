/*
===============================================================================
Problem: Remove Linked List Elements
Platform: LeetCode
Problem Number: 203
Topic: Singly Linked List
Difficulty: Easy

===============================================================================
PROBLEM STATEMENT
===============================================================================

Given the head of a singly linked list and an integer 'val', remove all the
nodes of the linked list whose value is equal to 'val'.

Return the head of the modified linked list.

Example 1:
    Input:
        head = [1,2,6,3,4,5,6]
        val = 6

    Output:
        [1,2,3,4,5]

Example 2:
    Input:
        head = [7,7,7,7]
        val = 7

    Output:
        []

Example 3:
    Input:
        head = [1,2,3]
        val = 4

    Output:
        [1,2,3]

===============================================================================
1. CORE IDEA
===============================================================================

The main challenge in this problem is understanding that there are two
different types of nodes we may need to remove:

    1. The node that 'current' is pointing to.
    2. The node that comes immediately after 'current'.

This distinction is extremely important in a singly linked list.

A singly linked list only allows us to move forward.

For example:

    1 -> 2 -> 6 -> 3 -> nullptr
         ^
       current

If we want to remove 6, we cannot move backwards from 6 to 2 because there
is no previous pointer.

Therefore, we need to remain at 2 and change:

    2 -> 6 -> 3

into:

    2 -> 3

This is done using:

    current->next = current->next->next;

===============================================================================
2. IMPORTANT OBSERVATION: DIVIDE THE PROBLEM INTO CASES
===============================================================================

Initially, this problem can look like one large problem.

A much easier way to solve it is to divide it into three cases.

CASE 1:
    The node to remove is at the beginning of the linked list.

CASE 2:
    The node to remove is somewhere after the current node.

CASE 3:
    The node to remove is the final node.

Once these cases are separated, the pointer manipulation becomes much easier
to understand.

===============================================================================
3. CASE 1: REMOVE NODES FROM THE BEGINNING
===============================================================================

Consider:

    7 -> 7 -> 8 -> 1 -> nullptr

and:

    val = 7

The first two nodes must be removed.

Initially:

    head
     |
     v
    7 -> 7 -> 8 -> 1 -> nullptr
    ^
 current

Since:

    current->val == val

the current node must be removed.

We move head forward:

    head = head->next;

After removing the first 7 conceptually:

    head
     |
     v
    7 -> 8 -> 1 -> nullptr

There is still another 7 at the beginning.

Therefore, we must continue removing matching nodes from the beginning.

This is why we use another loop:

    while (current != nullptr && current->val == val)

Inside it:

    head = head->next;
    current = current->next;

Eventually:

    head
     |
     v
    8 -> 1 -> nullptr

Now the first node is a value that should remain.

===============================================================================
4. ENTIRE LIST CONTAINS THE VALUE
===============================================================================

Consider:

    7 -> 7 -> 7 -> 7 -> nullptr

and:

    val = 7

Every node needs to be removed.

We repeatedly move:

    head = head->next;

and:

    current = current->next;

Eventually:

    head = nullptr
    current = nullptr

The loop stops safely.

The function returns:

    nullptr

Therefore, the algorithm correctly handles an entire list that needs to be
removed.

===============================================================================
5. CASE 2: REMOVE A NODE FROM THE MIDDLE
===============================================================================

Consider:

    1 -> 2 -> 6 -> 3 -> nullptr

and:

    val = 6

We cannot remove 6 directly using 'current' if current is pointing to 6,
because we need the previous node to reconnect the list.

There is no previous pointer in a singly linked list.

Therefore, we stop at the node BEFORE the node that we want to remove:

    1 -> 2 -> 6 -> 3
         ^
       current

Now:

    current->next

points to 6.

We check:

    current->next->val == val

Since:

    6 == 6

the node must be removed.

We bypass it:

    current->next = current->next->next;

Before:

    2 -> 6 -> 3

After:

    2 -> 3

The complete list becomes:

    1 -> 2 -> 3 -> nullptr

===============================================================================
6. VERY IMPORTANT: WHY CURRENT DOES NOT MOVE AFTER DELETION
===============================================================================

This is one of the most important lessons from this problem.

Consider:

    1 -> 2 -> 6 -> 6 -> 6 -> 3
         ^
       current

Suppose:

    val = 6

We remove current->next:

    current->next = current->next->next;

Now:

    1 -> 2 -> 6 -> 6 -> 3
         ^
       current

Notice that 'current' is STILL pointing to 2.

This is intentional.

Why?

Because the NEW current->next is another 6.

If we immediately moved current forward, we could skip a node that also needs
to be removed.

Therefore:

    If current->next is removed:
        DO NOT move current.

Instead, check current->next again.

This allows us to handle consecutive matching nodes.

Example:

    1 -> 2 -> 6 -> 6 -> 6 -> 3

After first deletion:

    1 -> 2 -> 6 -> 6 -> 3

After second deletion:

    1 -> 2 -> 6 -> 3

After third deletion:

    1 -> 2 -> 3

Throughout these deletions, current stays at 2.

===============================================================================
7. WHEN SHOULD CURRENT MOVE?
===============================================================================

There are two situations.

Situation 1:
    A node was deleted.

Then:

    current stays where it is.

Why?

Because the new current->next may also need to be deleted.

Situation 2:
    No deletion occurred.

Then:

    current = current->next;

Why?

Because the current node and its next node are both acceptable, so we can
move forward.

This gives us the fundamental rule:

    DELETION HAPPENED
        -> stay at current

    NO DELETION
        -> move current forward

===============================================================================
8. CASE 3: REMOVE THE LAST NODE
===============================================================================

Consider:

    1 -> 2 -> 3 -> 4 -> 6 -> nullptr

and:

    val = 6

Eventually:

    current
       |
       v
    4 -> 6 -> nullptr

We check:

    current->next->val == val

This is true.

Then:

    current->next = current->next->next;

Since:

    6->next == nullptr

we get:

    4 -> nullptr

Therefore:

    1 -> 2 -> 3 -> 4 -> nullptr

The last node has been removed.

===============================================================================
9. POINTER SAFETY: CURRENT VS CURRENT->NEXT
===============================================================================

One of the most important lessons from this problem was understanding that:

    current != nullptr

does NOT guarantee:

    current->next != nullptr

For example:

    1 -> 2 -> 3 -> nullptr
             ^
           current

Here:

    current != nullptr

is true.

But:

    current->next == nullptr

Therefore, this would be dangerous:

    current->next->val

because it would attempt to access:

    nullptr->val

That causes undefined behavior / runtime error.

Therefore, before accessing:

    current->next->val

we must first ensure:

    current->next != nullptr

The safe condition is:

    current->next != nullptr && current->next->val == val

The order is important because C++ uses short-circuit evaluation.

First:

    current->next != nullptr

is checked.

Only if it is true do we evaluate:

    current->next->val == val

===============================================================================
10. WHY THE ORDER OF CONDITIONS MATTERS
===============================================================================

This is unsafe:

    current->next->val == val && current->next != nullptr

because current->next->val is accessed BEFORE checking whether current->next
exists.

This is safe:

    current->next != nullptr && current->next->val == val

because the first condition protects the second condition.

This is an important general C++ pointer-safety concept.

===============================================================================
11. EMPTY LIST
===============================================================================

If:

    head == nullptr

there is nothing to remove.

Therefore:

    if (head == nullptr) {
        return head;
    }

This immediately returns nullptr.

===============================================================================
12. CONSECUTIVE MATCHING NODES AT THE BEGINNING
===============================================================================

Consider:

    7 -> 7 -> 7 -> 8 -> 9

and:

    val = 7

The first three nodes must be removed.

We cannot simply move head once.

Instead:

    while (current != nullptr && current->val == val)

we repeatedly move:

    head = head->next;
    current = current->next;

Eventually:

    head
     |
     v
    8 -> 9 -> nullptr

This is why the inner loop is necessary.

===============================================================================
13. WHY THE INNER LOOP DOES NOT MAKE THE ALGORITHM O(n^2)
===============================================================================

At first, it may seem that having an inner while loop means:

    O(n^2)

But that is not true here.

Each node is processed only a constant number of times.

When a node at the beginning is removed, we move past it permanently.

We do not go back and traverse it again.

Similarly, when a node after current is removed, current stays in place, but
the removed node disappears from the list and is never processed again.

Therefore, across the entire algorithm, the total amount of traversal is
linear.

So:

    Time Complexity = O(n)

not:

    O(n^2)

===============================================================================
14. COMPLETE ALGORITHM
===============================================================================

Step 1:
    If the list is empty, return head.

Step 2:
    Create current and point it to head.

Step 3:
    Traverse the list while current exists.

Step 4:
    If current itself contains val:

        Repeatedly move head and current forward while the current node
        contains val.

Step 5:
    Otherwise, check whether current->next exists and contains val.

Step 6:
    If current->next contains val:

        Bypass it using:

            current->next = current->next->next;

        Do NOT move current.

Step 7:
    Otherwise:

        current = current->next;

Step 8:
    Continue until current becomes nullptr.

Step 9:
    Return head.

===============================================================================
15. FINAL SOLUTION
===============================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
LeetCode provides the ListNode structure automatically.

The following is the structure used by LeetCode:

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
*/

class Solution {
public:

    ListNode* removeElements(ListNode* head, int val) {

        // Edge case:
        // If the linked list is empty, there is nothing to remove.
        if (head == nullptr) {
            return head;
        }

        // Pointer used to traverse the linked list.
        ListNode* current = head;

        /*
        Traverse the complete linked list.

        We only require current != nullptr here because current itself
        may be the last node and we still need to process it.
        */
        while (current != nullptr) {

            /*
            CASE 1:
            The current node itself needs to be removed.

            This mainly handles nodes at the beginning of the list.
            It also handles multiple consecutive matching nodes at the head.
            */
            if (current->val == val) {

                /*
                Remove consecutive matching nodes from the beginning.

                We move both head and current forward.

                The condition order is important:
                    current != nullptr
                is checked before:
                    current->val == val

                This prevents accessing current->val when current is nullptr.
                */
                while (current != nullptr && current->val == val) {

                    head = head->next;
                    current = current->next;
                }
            }

            /*
            CASE 2:
            The next node needs to be removed.

            Before accessing current->next->val, we must verify that
            current->next is not nullptr.
            */
            else if (current->next != nullptr &&
                     current->next->val == val) {

                /*
                Bypass the node that needs to be removed.

                Example:

                    current
                       |
                       v
                    2 -> 6 -> 3

                becomes:

                    2 -> 3
                */
                current->next = current->next->next;

                /*
                IMPORTANT:

                Do NOT move current here.

                The new current->next might also contain val.

                Example:

                    2 -> 6 -> 6 -> 3

                After removing the first 6:

                    2 -> 6 -> 3

                current must remain at 2 so that the second 6 can also
                be checked.
                */
            }

            /*
            CASE 3:
            Neither current nor current->next needs to be removed.

            Therefore, it is safe to move current forward.
            */
            else {
                current = current->next;
            }
        }

        // Return the new head of the linked list.
        return head;
    }
};

/*
===============================================================================
16. DRY RUN
===============================================================================

Input:

    head = 1 -> 2 -> 6 -> 3 -> 4 -> 5 -> 6 -> nullptr
    val = 6

Initial:

    current = 1
    head = 1

--------------------------------------------------
Iteration 1
--------------------------------------------------

current->val = 1

1 == 6 ?
No.

current->next->val = 2

2 == 6 ?
No.

Therefore:

    current = current->next

Now:

    current = 2

--------------------------------------------------
Iteration 2
--------------------------------------------------

current->val = 2

2 == 6 ?
No.

current->next->val = 6

6 == 6 ?
Yes.

Remove:

    current->next = current->next->next;

List becomes:

    1 -> 2 -> 3 -> 4 -> 5 -> 6 -> nullptr

current remains:

    current = 2

--------------------------------------------------
Iteration 3
--------------------------------------------------

current->val = 2

2 == 6 ?
No.

current->next->val = 3

3 == 6 ?
No.

Move:

    current = 3

--------------------------------------------------
Iteration 4
--------------------------------------------------

current = 3

3 != 6

current->next = 4

4 != 6

Move:

    current = 4

--------------------------------------------------
Iteration 5
--------------------------------------------------

current = 4

4 != 6

current->next = 5

5 != 6

Move:

    current = 5

--------------------------------------------------
Iteration 6
--------------------------------------------------

current = 5

5 != 6

current->next = 6

6 == 6

Remove:

    current->next = current->next->next;

The last 6 points to nullptr.

Therefore:

    5 -> nullptr

Final list:

    1 -> 2 -> 3 -> 4 -> 5 -> nullptr

current is still 5.

Next iteration:

    current->next == nullptr

Therefore the second condition fails.

Then:

    current = current->next;

So:

    current = nullptr

The loop ends.

Return:

    head

Final answer:

    1 -> 2 -> 3 -> 4 -> 5 -> nullptr

===============================================================================
17. COMPLEXITY ANALYSIS
===============================================================================

Time Complexity:
    O(n)

Why?

Every node is processed a constant number of times.

The inner loop that handles matching nodes at the beginning does not cause
O(n^2) complexity because once a node is removed, it is never traversed again.

Similarly, when current->next is removed, current stays in place, but the
removed node is permanently skipped.

Therefore:

    Time = O(n)

Best Case:
    O(1)

If the relevant structure allows the answer to be determined immediately,
very little traversal may be required.

Worst Case:
    O(n)

We may need to inspect the entire linked list.

Auxiliary Space:
    O(1)

We only use a constant number of pointers:

    head
    current

No additional data structure proportional to n is used.

Therefore:

    Auxiliary Space = O(1)

===============================================================================
18. IMPORTANT LESSONS LEARNED
===============================================================================

Lesson 1:
    Divide a difficult-looking problem into smaller cases.

Instead of thinking:

    "Remove all unwanted nodes."

Think:

    Case 1 -> current itself must be removed.
    Case 2 -> current->next must be removed.
    Case 3 -> nothing needs to be removed.

This makes the problem much easier.

--------------------------------------------------

Lesson 2:
    Always verify pointers before dereferencing them.

Before:

    current->next->val

make sure:

    current->next != nullptr

--------------------------------------------------

Lesson 3:
    The order of conditions matters.

Safe:

    current->next != nullptr &&
    current->next->val == val

Unsafe:

    current->next->val == val &&
    current->next != nullptr

--------------------------------------------------

Lesson 4:
    After deleting current->next, do not automatically move current.

Why?

Because current->next has changed and the new node might also need to
be removed.

--------------------------------------------------

Lesson 5:
    Multiple loops do not automatically mean O(n^2).

What matters is how many times each element is actually processed.

Here, every node is processed only a constant number of times.

Therefore:

    O(n)

--------------------------------------------------

Lesson 6:
    A singly linked list cannot move backwards.

There is no previous pointer.

Therefore, when deleting a node from the middle, we normally keep a pointer
to the node immediately before it.

===============================================================================
19. COMMON MISTAKES
===============================================================================

Mistake 1:
    Using:

        while (current->next != nullptr)

as the main loop condition.

Problem:

    The last node would never be processed.

Correct idea:

    while (current != nullptr)

--------------------------------------------------

Mistake 2:
    Accessing:

        current->next->val

without checking:

        current->next != nullptr

This can cause:

    Runtime Error:
    member access within null pointer

--------------------------------------------------

Mistake 3:
    Moving current after deleting current->next.

Example:

    1 -> 2 -> 6 -> 6 -> 3

After deleting the first 6:

    1 -> 2 -> 6 -> 3

If current immediately moves forward, the second 6 can be skipped.

--------------------------------------------------

Mistake 4:
    Handling only middle/end nodes and forgetting the head.

Example:

    7 -> 7 -> 8 -> 1

The head itself contains the value that needs to be removed.

Therefore, head handling is necessary.

===============================================================================
20. FINAL MENTAL MODEL
===============================================================================

When solving linked-list deletion problems, think:

                    current
                       |
                       v
    previous/current -> target -> next

If target must be removed:

    previous/current -> next

This means:

    current->next = current->next->next;

If the current node itself must be removed from the beginning:

    head = head->next;

The most important question to ask is:

    "Which node am I currently standing on,
     and which node am I trying to remove?"

Once that becomes clear, linked-list deletion becomes much easier.

===============================================================================
21. FINAL SUMMARY
===============================================================================

Problem:
    Remove all nodes whose value equals val.

Main technique:
    Singly linked list traversal + pointer manipulation.

Key operations:

    Remove current head:
        head = head->next;

    Remove current->next:
        current->next = current->next->next;

Important rule:

    If a node was deleted:
        stay at current.

    If no node was deleted:
        move current forward.

Complexity:

    Time:
        O(n)

    Auxiliary Space:
        O(1)

This problem was particularly useful because it teaches pointer safety,
case decomposition, consecutive-node deletion, and the correct movement of
a traversal pointer.

===============================================================================
END
===============================================================================
*/