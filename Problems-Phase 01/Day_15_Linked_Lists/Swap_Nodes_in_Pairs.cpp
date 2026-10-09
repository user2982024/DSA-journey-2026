/*
================================================================================
DSA JOURNEY — LINKED LISTS
Problem: Swap Nodes in Pairs
Platform: LeetCode
Problem Number: 24
Topic: Linked List / Pointer Manipulation
Difficulty: Medium
================================================================================

PROBLEM STATEMENT
-----------------
Given the head of a singly linked list, swap every two adjacent nodes and
return its head.

Important:
- We must swap the NODES themselves, not just their values.
- If the list has an odd number of nodes, the final node remains unchanged.
- We should solve the problem in O(n) time and O(1) extra space.

Example:

Input:
1 -> 2 -> 3 -> 4 -> NULL

Output:
2 -> 1 -> 4 -> 3 -> NULL


================================================================================
OUR APPROACH
================================================================================

The goal is to process the linked list two nodes at a time.

For every pair:

    previous -> current -> next

we want:

    current -> previous -> next

For example:

Before:
    1 -> 2 -> 3 -> 4 -> NULL

After swapping the first pair:
    2 -> 1 -> 3 -> 4 -> NULL

Then we need to swap the next pair:
    4 -> 3

giving:

    2 -> 1 -> 4 -> 3 -> NULL


================================================================================
FIRST IDEA / INITIAL POINTERS
================================================================================

We initially reasoned using three main pointers:

    previous
    current
    next

Their roles were:

    previous = first node of the current pair
    current  = second node of the current pair
    next     = node immediately after the current pair

For:

    1 -> 2 -> 3 -> 4

we initially have:

    previous -> 1
    current  -> 2
    next     -> 3

The swap itself is:

    current->next = previous;
    previous->next = next;

which gives:

    2 -> 1 -> 3 -> 4

However, this alone was NOT enough to correctly connect the already
processed portion with the newly swapped pair.


================================================================================
IMPORTANT BUG WE FOUND
================================================================================

Our first three-pointer implementation worked for the first pair but failed
when there were more pairs.

Example:

    1 -> 2 -> 3 -> 4 -> NULL

After swapping the first pair:

    2 -> 1 -> 3 -> 4

When swapping the second pair, we could correctly create:

    4 -> 3

BUT node 1 was still connected to node 3:

    2 -> 1 -> 3

Therefore the newly created:

    4 -> 3

could become disconnected from the processed portion.

The problem was NOT simply pointer safety.

The deeper problem was:

    STRUCTURAL CONNECTIVITY

We had to remember the last node of the already-processed portion so that
it could be connected to the newly swapped pair.

This led to the introduction of another pointer:

    left


================================================================================
FINAL POINTER ROLES
================================================================================

We ended up using five pointers:

    left
    previous
    current
    next
    newHead

Their roles are:

1. left
   ----
   The last node of the already processed/swapped portion.

2. previous
   ---------
   The first node of the current pair.

3. current
   -------
   The second node of the current pair.

4. next
   ----
   The node immediately after the current pair.

5. newHead
   --------
   The new head of the entire list.

   Since the first pair is:

       head -> head->next

   after swapping, the second node becomes the new head:

       newHead = head->next;


================================================================================
EDGE CASES
================================================================================

CASE 1: Empty list

    head = NULL

There is nothing to swap.

Return head immediately.


CASE 2: One-node list

    1 -> NULL

There is no pair to swap.

Return head immediately.


CASE 3: Two nodes

    1 -> 2 -> NULL

After swapping:

    2 -> 1 -> NULL


CASE 4: Odd number of nodes

    1 -> 2 -> 3 -> NULL

After swapping:

    2 -> 1 -> 3 -> NULL

The last unpaired node remains unchanged.


================================================================================
STEP-BY-STEP ALGORITHM
================================================================================

Initial list:

    1 -> 2 -> 3 -> 4 -> NULL

Initial pointers:

    left     = NULL
    previous = 1
    current  = 2
    next     = 3
    newHead  = 2


STEP 1: Swap the first pair
----------------------------

    current->next = previous;

Gives:

    2 -> 1

Then:

    previous->next = next;

Gives:

    1 -> 3

Current structure:

    2 -> 1 -> 3 -> 4 -> NULL


STEP 2: Connect the processed portion
--------------------------------------

There is no processed portion yet because:

    left == NULL


STEP 3: Move the processed-pair pointer
----------------------------------------

    left = previous;

Now:

    left -> 1


STEP 4: Move to the next pair
-----------------------------

    previous = next;

So:

    previous -> 3

Then:

    current = previous->next;

So:

    current -> 4

Then:

    next = current->next;

Therefore:

    next = NULL


STEP 5: Swap the second pair
----------------------------

    current->next = previous;

Gives:

    4 -> 3

Then:

    previous->next = next;

Gives:

    3 -> NULL


STEP 6: Connect the previous portion
-------------------------------------

Now:

    left != NULL

Therefore:

    left->next = current;

Since:

    left = 1
    current = 4

we get:

    2 -> 1 -> 4 -> 3 -> NULL


================================================================================
WHY 'left' WAS NECESSARY
================================================================================

This was the most important debugging insight.

Swapping a pair locally is not enough.

Suppose we have:

    2 -> 1        4 -> 3

Both pairs are individually correct, but the two sections are disconnected.

We need:

    2 -> 1 -> 4 -> 3

The node 1 is the last node of the already processed portion.

Therefore:

    left = 1

and:

    left->next = 4;

connects the processed portion to the newly swapped pair.

The major lesson:

    In linked-list problems, always think about BOTH:

        1. Pointer safety
        2. Structural connectivity


================================================================================
WHY WE USED 'newHead'
================================================================================

The original head is:

    1

After swapping the first pair:

    2 -> 1

Therefore the original head is no longer the head of the list.

We save:

    newHead = head->next;

before changing the structure.

At the end:

    return newHead;


================================================================================
FINAL CODE
================================================================================
*/

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {

        // Edge case 1:
        // Empty linked list.
        if (head == nullptr) {
            return head;
        }

        // Edge case 2:
        // Only one node exists, so there is nothing to swap.
        if (head->next == nullptr) {
            return head;
        }

        /*
        Pointer roles:

        left:
            Last node of the already processed/swapped portion.

        previous:
            First node of the current pair.

        current:
            Second node of the current pair.

        next:
            Node after the current pair.

        newHead:
            New head after swapping the first pair.
        */

        ListNode* left = nullptr;
        ListNode* previous = head;
        ListNode* current = head->next;
        ListNode* next = current->next;

        // After swapping the first pair, the second node becomes the head.
        ListNode* newHead = head->next;

        while (previous != nullptr && current != nullptr) {

            /*
            Swap the current pair.

            Before:
                previous -> current -> next

            After:
                current -> previous -> next
            */

            current->next = previous;
            previous->next = next;

            /*
            If there is already a processed portion, connect its last node
            to the newly swapped pair.

            Example:

                2 -> 1    4 -> 3

            left points to 1 and current points to 4.

            Therefore:

                left->next = current;

            gives:

                2 -> 1 -> 4 -> 3
            */
            if (left != nullptr) {
                left->next = current;
            }

            // The first node of the current pair is now the tail of the
            // processed portion.
            left = previous;

            // Move to the next pair.
            previous = next;

            // If there is no next pair, stop.
            if (previous == nullptr) {
                break;
            }

            // The second node of the next pair.
            current = previous->next;

            // If only one node remains, it cannot form a pair.
            if (current == nullptr) {
                break;
            }

            // Node after the next pair.
            next = current->next;
        }

        return newHead;
    }
};


/*
================================================================================
COMPLEXITY ANALYSIS
================================================================================

TIME COMPLEXITY: O(n)

Every node is visited a constant number of times.

Therefore:

    Time = O(n)

where n is the number of nodes.


SPACE COMPLEXITY: O(1)

We use only a constant number of pointer variables:

    left
    previous
    current
    next
    newHead

No data structure proportional to n is created.

Therefore:

    Auxiliary Space = O(1)


================================================================================
INTERVIEW EXPLANATION
================================================================================

A concise interview explanation:

"I process the linked list two nodes at a time. For each pair, I keep
pointers to the first node, second node, and the node after the pair. I
reverse the two nodes by changing their next pointers.

I also maintain a pointer called 'left', which represents the tail of the
already processed portion. This allows me to connect the previously swapped
portion to the newly swapped pair.

I save the new head before performing the first swap because the second node
of the first pair becomes the new head.

The algorithm visits every node once, so it takes O(n) time and O(1)
auxiliary space."


================================================================================
KEY LESSONS LEARNED
================================================================================

1. Swap linked-list nodes by changing LINKS, not values.

2. A locally correct pointer operation may still produce a globally
   incorrect linked-list structure.

3. Always consider:
       - pointer safety
       - structural connectivity

4. When processing multiple pairs/groups, maintain a pointer to the end of
   the already processed portion when necessary.

5. Preserve important connections before modifying links.

6. The head of a linked list may change after rearranging nodes, so explicitly
   preserve the new head.

7. Dry-running pointer problems node-by-node is extremely useful while
   building the mental model.

8. With repetition, detailed pointer tracing gradually becomes pattern
   recognition, making future linked-list problems much faster.


================================================================================
PERSONAL DSA JOURNEY NOTE
================================================================================

This problem was solved through independent reasoning rather than copying
a tutorial solution.

The important achievement was not simply getting Accepted.

The important part was:

    brainstorming
        ↓
    implementation
        ↓
    failed attempt
        ↓
    dry run
        ↓
    identify structural bug
        ↓
    introduce 'left'
        ↓
    retest
        ↓
    accepted solution

The final solution demonstrates understanding of linked-list pointer
manipulation rather than memorization of a standard template.

================================================================================
END
================================================================================