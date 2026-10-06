/*
======================================================================
                    REVERSE LINKED LIST II
======================================================================

Problem:
    Reverse a linked list from position `left` to position `right`
    and return the modified list.

Platform:
    LeetCode

Problem Number:
    92

Difficulty:
    Medium

Link:
    https://leetcode.com/problems/reverse-linked-list-ii/

----------------------------------------------------------------------
PROBLEM DESCRIPTION
----------------------------------------------------------------------

Given the head of a singly linked list and two integers `left` and
`right`, reverse the nodes of the list from position `left` to
position `right`, and return the resulting list.

The reversal must be performed by changing the links between nodes.

Example:

    Input:
        1 → 2 → 3 → 4 → 5

        left = 2
        right = 4

    Output:
        1 → 4 → 3 → 2 → 5


Another example:

    Input:
        1 → 2 → 3 → 4 → 5

        left = 1
        right = 4

    Output:
        4 → 3 → 2 → 1 → 5


======================================================================
CORE IDEA
======================================================================

The main idea is to divide the problem into three parts:

    1. Position the boundary pointers.
    2. Reverse only the required portion.
    3. Reconnect the reversed portion with the rest of the list.

The algorithm is based on the same three-pointer reversal technique
used in LeetCode 206 (Reverse Linked List):

    previous
    current
    next

The major additional difficulty in this problem is that we are NOT
reversing the entire list.

We must carefully identify:

    - the node before `left`
    - the node after `right`
    - the first node inside the reversal range
    - the first node that should NOT be reversed

======================================================================
POINTERS USED
======================================================================

We use:

    previous
    current
    next

For positioning the reversal range, we use:

    leftPart
    rightPart

And two counters:

    l
    r


----------------------------------------------------------------------
MEANING OF leftPart
----------------------------------------------------------------------

`leftPart` represents the node immediately BEFORE the reversal
range.

Example:

    1 → 2 → 3 → 4 → 5

    left = 3

Then:

    leftPart = 2

because node 2 is immediately before node 3.


Special case:

    left = 1

There is no node before the reversal range.

In our implementation, `leftPart` remains equal to `head`.

Example:

    1 → 2 → 3 → 4 → 5
    ↑
    leftPart

Here:

    leftPart = 1

This requires special handling during reconnection and return.


----------------------------------------------------------------------
MEANING OF rightPart
----------------------------------------------------------------------

The most important invariant in this implementation is:

    rightPart represents the node immediately AFTER the reversal
    range.

Example:

    1 → 2 → 3 → 4 → 5 → 6

    left = 2
    right = 4

Then:

    leftPart  = 1
    rightPart = 5

The nodes to reverse are:

    2 → 3 → 4

And node 5 must NOT be reversed.

Therefore, node 5 acts as the stopping boundary.

Our reversal loop can then be:

    while (current != rightPart)


----------------------------------------------------------------------
SPECIAL CASE: RIGHT IS THE LAST NODE
----------------------------------------------------------------------

This is the most important boundary issue encountered while solving
the problem.

Example:

    1 → 2 → 3 → 4 → 5

    left = 2
    right = 5

There is no node after position 5.

Therefore, there is no actual node that can serve as `rightPart`.

So we use:

    rightPart = nullptr

Then the reversal condition becomes effectively:

    while (current != nullptr)

This allows the final node to be reversed.

The implementation detects this situation during positioning:

    if (rightPart->next != nullptr) {
        rightPart = rightPart->next;
    }
    else {
        rightPart = nullptr;
        r++;
        break;
    }

The `break` is important because the linked list has ended.


======================================================================
POSITIONING THE BOUNDARIES
======================================================================

We start with:

    leftPart  = head
    rightPart = head

and:

    l = 1
    r = 1

The positioning loop is:

    while (r != right + 1)

Inside the loop:

    if (l != left - 1 && left > 1) {
        leftPart = leftPart->next;
        l++;
    }

This moves `leftPart` until it reaches:

    position left - 1


For example:

    1 → 2 → 3 → 4 → 5

    left = 3

We need:

    leftPart = 2

because position 2 is immediately before position 3.


For `left = 1`, the condition:

    left > 1

is false.

Therefore:

    leftPart = head

which is exactly what we need.


----------------------------------------------------------------------
RIGHT-SIDE POSITIONING
----------------------------------------------------------------------

The right pointer is moved using:

    if (rightPart->next != nullptr) {
        rightPart = rightPart->next;
    }

This attempts to move `rightPart` to the node after the reversal.

If there is no next node:

    rightPart->next == nullptr

then `rightPart` becomes:

    nullptr

and the loop ends using:

    break;

This handles the case where `right` is the final node.


======================================================================
INITIALIZING THE REVERSAL
======================================================================

After positioning:

If:

    left == 1

then:

    previous = leftPart;

because `leftPart` is actually the first node.

Otherwise:

    previous = leftPart->next;

because the node after `leftPart` is the first node of the
reversal range.

Then:

    current = previous->next;

and:

    next = current->next;


Example:

    1 → 2 → 3 → 4 → 5

    left = 2
    right = 4

We have:

    leftPart = 1

Therefore:

    previous = 2
    current  = 3
    next     = 4


For:

    left = 1
    right = 4

We have:

    leftPart = 1

Therefore:

    previous = 1
    current  = 2
    next     = 3


======================================================================
REVERSAL LOGIC
======================================================================

The actual reversal uses the standard three-pointer technique:

    while (current != rightPart) {

        next = current->next;

        current->next = previous;

        previous = current;

        current = next;
    }


The order is extremely important.

First:

    next = current->next;

We save the next node before modifying the current node.

Then:

    current->next = previous;

This reverses the current link.

Then:

    previous = current;

Move `previous` forward.

Then:

    current = next;

Move `current` forward using the saved pointer.


======================================================================
WHY next MUST BE SAVED FIRST
======================================================================

Suppose:

    2 → 3 → 4

and:

    current = 3

If we immediately do:

    current->next = previous;

then node 3 no longer points toward 4.

Therefore, we MUST first save:

    next = current->next;

so that we don't lose the remaining list.


======================================================================
RECONNECTION
======================================================================

After reversal, we must reconnect the reversed section to the
unchanged parts of the list.


----------------------------------------------------------------------
CASE 1: left == 1
----------------------------------------------------------------------

Example:

    1 → 2 → 3 → 4 → 5

    left = 1
    right = 4

After reversal:

    4 → 3 → 2 → 1

The old first node (1) must connect to node 5.

Therefore:

    leftPart->next = current;


Since:

    leftPart = 1
    current  = 5

we get:

    1 → 5

The new head is `previous`.

Therefore:

    return previous;


Final result:

    4 → 3 → 2 → 1 → 5


----------------------------------------------------------------------
CASE 2: left > 1
----------------------------------------------------------------------

Example:

    1 → 2 → 3 → 4 → 5

    left = 2
    right = 4

After reversal:

    4 → 3 → 2

The old first node of the reversed section is node 2.

Node 2 must connect to node 5.

And node 1 must connect to the new beginning of the reversed
section, node 4.

Therefore:

    leftPart->next->next = current;

and:

    leftPart->next = previous;


Before reconnection:

    leftPart = 1
    leftPart->next = 2

After reversal:

    previous = 4
    current = 5


First:

    leftPart->next->next = current;

means:

    2 → 5


Then:

    leftPart->next = previous;

means:

    1 → 4


Final result:

    1 → 4 → 3 → 2 → 5


The original head remains unchanged, so:

    return head;


======================================================================
EDGE CASES
======================================================================

1. SINGLE NODE

    Input:

        1

    left = 1
    right = 1

    No reversal is needed.

    Handled by:

        if (head->next == nullptr)
            return head;


----------------------------------------------------------------------
2. left == right

Example:

    1 → 2 → 3 → 4 → 5

    left = 3
    right = 3

Only one node is selected.

Reversing one node changes nothing.

Handled by:

    if (left == right)
        return head;


----------------------------------------------------------------------
3. REVERSAL STARTS AT HEAD

Example:

    1 → 2 → 3 → 4 → 5

    left = 1
    right = 4

Result:

    4 → 3 → 2 → 1 → 5

This requires special handling because there is no node before
the reversal range.


----------------------------------------------------------------------
4. REVERSAL ENDS AT TAIL

Example:

    1 → 2 → 3 → 4 → 5

    left = 2
    right = 5

Result:

    1 → 5 → 4 → 3 → 2

In this situation:

    rightPart = nullptr

and the reversal continues until:

    current == nullptr


----------------------------------------------------------------------
5. ENTIRE LIST

Example:

    1 → 2 → 3 → 4 → 5

    left = 1
    right = 5

Result:

    5 → 4 → 3 → 2 → 1

This combines both major boundary cases:

    left == 1
    right is the final node


----------------------------------------------------------------------
6. TWO-NODE REVERSAL

Example:

    1 → 2 → 3 → 4 → 5

    left = 3
    right = 4

Result:

    1 → 2 → 4 → 3 → 5

The same pointer logic handles this normally.


======================================================================
IMPORTANT DEBUGGING JOURNEY
======================================================================

This problem required careful pointer reasoning.

Several issues were encountered while developing the algorithm.


----------------------------------------------------------------------
ISSUE 1: Handling left == 1
----------------------------------------------------------------------

Initially, the normal initialization was based on:

    previous = leftPart->next;

But when:

    left == 1

there is no node before the reversal.

This would skip the first node.

The solution was to create a separate case:

    if (left == 1) {
        previous = leftPart;
    }
    else {
        previous = leftPart->next;
    }


----------------------------------------------------------------------
ISSUE 2: Incorrect right boundary
----------------------------------------------------------------------

Initially, the reversal condition was:

    while (current != rightPart)

but `rightPart` was sometimes pointing to the node at `right`
rather than the node after `right`.

This caused the node at the `right` position to remain unreversed.

The positioning logic was then refined so that `rightPart`
represents the node immediately after the reversal.


----------------------------------------------------------------------
ISSUE 3: right IS THE LAST NODE
----------------------------------------------------------------------

Suppose:

    1 → 2 → 3 → 4 → 5

    left = 2
    right = 5

There is no node after position 5.

Therefore, `rightPart` cannot point to a real node.

The solution was:

    rightPart = nullptr;

and then:

    break;

from the positioning loop.

This allows:

    while (current != rightPart)

to become effectively:

    while (current != nullptr)


----------------------------------------------------------------------
ISSUE 4: Accidentally Reversing One Extra Node
----------------------------------------------------------------------

At one point, the loop was changed to:

    while (previous != rightPart)

This caused an extra node to be processed in cases where
`rightPart` represented the node after the reversal.

The correct interpretation is:

    rightPart = boundary AFTER the reversal

Therefore the correct condition is:

    while (current != rightPart)


----------------------------------------------------------------------
ISSUE 5: Confusion Between rightPart and rightPart->next
----------------------------------------------------------------------

An important pointer concept discovered during debugging:

If:

    rightPart → 60 → nullptr

then:

    rightPart != nullptr

but:

    rightPart->next == nullptr

These are NOT the same thing.

A pointer pointing to the final node does NOT automatically become
nullptr just because that node's next pointer is nullptr.

We explicitly set:

    rightPart = nullptr

only when there is no node after the reversal range.


======================================================================
DETAILED DRY RUN
======================================================================

Example:

    1 → 2 → 3 → 4 → 5

    left = 2
    right = 4


POSITIONING:

    leftPart  = 1
    rightPart = 5


INITIALIZATION:

    previous = 2
    current  = 3
    next     = 4


REVERSAL:

Iteration 1:

    next = 4
    3->next = 2
    previous = 3
    current = 4


List portion:

    3 → 2

    4 → 5


Iteration 2:

    next = 5
    4->next = 3
    previous = 4
    current = 5


Now:

    previous = 4
    current = 5
    rightPart = 5

Therefore:

    current == rightPart

The loop stops.


RECONNECTION:

    leftPart = 1
    previous = 4
    current = 5

First:

    leftPart->next->next = current

This gives:

    2 → 5


Then:

    leftPart->next = previous

This gives:

    1 → 4


Final list:

    1 → 4 → 3 → 2 → 5


======================================================================
DRY RUN: left == 1
======================================================================

Example:

    1 → 2 → 3 → 4 → 5

    left = 1
    right = 4


POSITIONING:

    leftPart = 1
    rightPart = 5


INITIALIZATION:

    previous = 1
    current = 2


REVERSAL:

    2 → 1
    3 → 2 → 1
    4 → 3 → 2 → 1

At the end:

    previous = 4
    current = 5


RECONNECTION:

    leftPart->next = current

Therefore:

    1 → 5


And:

    previous = 4

is the new head.


Final:

    4 → 3 → 2 → 1 → 5


======================================================================
DRY RUN: right IS THE LAST NODE
======================================================================

Example:

    1 → 2 → 3 → 4 → 5

    left = 2
    right = 5


POSITIONING:

    leftPart = 1

When rightPart reaches node 5:

    rightPart->next == nullptr

Therefore:

    rightPart = nullptr

and:

    break;


Now:

    previous = 2
    current = 3


Reversal continues while:

    current != nullptr


Nodes 3, 4, and 5 are reversed.


At the end:

    previous = 5
    current = nullptr


Reconnect:

    1 → 5 → 4 → 3 → 2


======================================================================
WHY THE ALGORITHM WORKS
======================================================================

The algorithm maintains the following invariants:

1. `leftPart` always identifies the node before the reversal
   section, unless `left == 1`.

2. `rightPart` identifies the first node that must NOT be
   reversed.

3. `previous` identifies the beginning of the reversed portion
   during reversal.

4. `current` identifies the next node that still needs to be
   processed.

5. `next` temporarily saves the original forward direction
   before it is changed.

These invariants allow the same reversal mechanism to work for
different positions of `left` and `right`.


======================================================================
ALGORITHM SUMMARY
======================================================================

1. Handle trivial cases:
       - single node
       - left == right

2. Initialize:
       previous
       current
       next
       leftPart
       rightPart
       l
       r

3. Position `leftPart` at the node before `left`.

4. Position `rightPart` at the node after `right`.

5. If `right` is the final node:
       rightPart = nullptr
       break

6. Initialize `previous` and `current`.

7. Reverse the required section using:
       next
       current
       previous

8. Reconnect the reversed section.

9. If `left == 1`:
       return previous

10. Otherwise:
       return head


======================================================================
TIME COMPLEXITY
======================================================================

Let:

    n = number of nodes in the linked list.

The list is traversed a constant number of times:

    - positioning the boundaries
    - reversing the selected section

Therefore:

    Time Complexity = O(n)


======================================================================
SPACE COMPLEXITY
======================================================================

Only a constant number of pointer and integer variables are used.

No array, vector, map, recursion, or additional linked list is
created.

Therefore:

    Space Complexity = O(1)


======================================================================
FINAL SOLUTION
======================================================================
*/

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {

        // Edge case:
        // A single-node list is already reversed.
        if (head->next == nullptr) {
            return head;
        }

        // Edge case:
        // Reversing one position changes nothing.
        if (left == right) {
            return head;
        }

        // Pointers used during reversal.
        ListNode* previous = nullptr;
        ListNode* current = nullptr;
        ListNode* next = nullptr;

        // Boundary pointers.
        ListNode* leftPart = head;
        ListNode* rightPart = head;

        // Position counters.
        int l = 1;
        int r = 1;

        /*
            Position leftPart at the node immediately before `left`.

            Position rightPart at the node immediately after `right`.

            If there is no node after `right`, rightPart becomes
            nullptr.
        */
        while (r != right + 1) {

            if (l != left - 1 && left > 1) {
                leftPart = leftPart->next;
                l++;
            }

            if (rightPart->next != nullptr) {
                rightPart = rightPart->next;
            }
            else {
                // `right` is the final node.
                rightPart = nullptr;
                r++;
                break;
            }

            r++;
        }

        /*
            Initialize the reversal.

            If left == 1, the reversal begins at the original head,
            so previous starts at leftPart.

            Otherwise, previous starts at the first node inside
            the reversal range.
        */
        if (left == 1) {
            previous = leftPart;
        }
        else {
            previous = leftPart->next;
        }

        current = previous->next;
        next = current->next;

        /*
            Reverse the selected portion.

            `rightPart` represents the first node that should NOT
            be reversed.

            If right is the last node, rightPart is nullptr.
        */
        while (current != rightPart) {

            // Save the next node before changing the link.
            next = current->next;

            // Reverse the current link.
            current->next = previous;

            // Move previous forward.
            previous = current;

            // Move current forward.
            current = next;
        }

        /*
            Reconnect the reversed section.
        */

        if (left == 1) {

            // The old first node is now the end of the reversed
            // section and must connect to the remaining list.
            leftPart->next = current;
        }
        else {

            // Connect the old beginning of the reversed section
            // to the node after the reversed section.
            leftPart->next->next = current;

            // Connect the node before the reversed section to the
            // new beginning of the reversed section.
            leftPart->next = previous;
        }

        /*
            If reversal started at the head, `previous` is the new
            head.

            Otherwise, the original head is still the head.
        */
        if (left == 1) {
            return previous;
        }
        else {
            return head;
        }
    }
};


/*
======================================================================
FINAL TAKEAWAY
======================================================================

The most important lesson from this problem is not the code itself.

The important lesson is defining pointer invariants.

For this implementation:

    leftPart
        =
    node before the reversal section

and:

    rightPart
        =
    node after the reversal section

If the node after `right` does not exist:

    rightPart = nullptr


Once these meanings are fixed, the reversal becomes the familiar
three-pointer technique:

    next = current->next;
    current->next = previous;
    previous = current;
    current = next;


The most important pointer rule:

    ALWAYS SAVE `current->next` BEFORE CHANGING `current->next`.

This problem also demonstrates an important interview skill:

    Do not immediately abandon an algorithm when it fails.

Instead:

    1. Define what every pointer represents.
    2. Construct a small counterexample.
    3. Dry-run every pointer.
    4. Identify the violated invariant.
    5. Fix the invariant.
    6. Test boundary cases.
    7. Only then consider changing the entire approach.

This solution was developed from the standard full-list reversal
technique and adapted to a partial linked-list reversal using
explicit boundary pointers.

======================================================================
*/