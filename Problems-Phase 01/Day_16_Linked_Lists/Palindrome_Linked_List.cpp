/*
===============================================================================
PROBLEM: Palindrome Linked List
PLATFORM: LeetCode
PROBLEM NUMBER: 234
DIFFICULTY: Easy
TOPICS: Singly Linked Lists, Slow and Fast Pointers, Reversal
LANGUAGE: C++

APPROACH:
1. Find the middle using slow and fast pointers.
2. Identify the start of the second half.
3. Reverse the second half in place.
4. Compare the reversed second half with the first half.

TIME COMPLEXITY: O(n)
AUXILIARY SPACE COMPLEXITY: O(1)

===============================================================================
1. PROBLEM DESCRIPTION
===============================================================================

Given the head of a singly linked list, determine whether the linked list
is a palindrome.

A palindrome is a sequence that reads the same forward and backward.

Examples of palindromes:
    1 -> 2 -> 1
    1 -> 2 -> 2 -> 1
    1 -> 2 -> 3 -> 2 -> 1

Examples that are not palindromes:
    1 -> 2 -> 3
    1 -> 2 -> 3 -> 4

Return true if the linked list is a palindrome; otherwise, return false.

The challenge is to solve the problem using O(n) time and O(1) auxiliary
space, without creating an additional array or copying all node values.


===============================================================================
2. EXAMPLES
===============================================================================

Example 1:

Input:
    head = [1, 2, 2, 1]

Linked list:
    1 -> 2 -> 2 -> 1 -> nullptr

Reading forward:
    1, 2, 2, 1

Reading backward:
    1, 2, 2, 1

Output:
    true


Example 2:

Input:
    head = [1, 2]

Linked list:
    1 -> 2 -> nullptr

Reading forward:
    1, 2

Reading backward:
    2, 1

Output:
    false


Example 3:

Input:
    head = [1, 2, 3, 2, 1]

Linked list:
    1 -> 2 -> 3 -> 2 -> 1 -> nullptr

Output:
    true


Example 4:

Input:
    head = [1, 2, 3, 4, 5]

Linked list:
    1 -> 2 -> 3 -> 4 -> 5 -> nullptr

Output:
    false


===============================================================================
3. UNDERSTANDING THE PROBLEM
===============================================================================

A palindrome must have matching values at positions mirrored around the
middle of the list.

For example:

    1 -> 2 -> 3 -> 2 -> 1

The first and last values match:
    1 == 1

The second and second-last values match:
    2 == 2

The middle value has no matching partner:
    3

Therefore, the list is a palindrome.

For this list:

    1 -> 2 -> 3 -> 4 -> 1

The first and last values match:
    1 == 1

But the second and second-last values do not:
    2 != 4

Therefore, the list is not a palindrome.

The central challenge is comparing values from opposite ends even though
a singly linked list only supports forward traversal.


===============================================================================
4. OVERALL APPROACH
===============================================================================

We solve the problem using three main techniques:

    A. Slow and fast pointers.
    B. Reversing a linked list.
    C. Comparing two linked-list traversals.

The complete algorithm has four stages.

STAGE 1: FIND THE MIDDLE
-----------------------

Initialize:

    slow = head
    fast = head

Move slow one node at a time and fast two nodes at a time.

When fast reaches the end, slow identifies the middle position.

STAGE 2: IDENTIFY THE SECOND HALF
---------------------------------

The correct starting position depends on whether the list has an odd or
even number of nodes.

If fast != nullptr:
    The list has an odd number of nodes.
    The middle node should not be compared against another node.
    Start the second half at slow->next.

Otherwise:
    The list has an even number of nodes.
    Start the second half at slow.

STAGE 3: REVERSE THE SECOND HALF
--------------------------------

Reverse the selected second half in place using:

    previous
    current
    next

After reversal, previous points to the head of the reversed half.

STAGE 4: COMPARE THE HALVES
---------------------------

Use one pointer to traverse the original first half and another to
traverse the reversed second half.

Compare their values one by one.

If any pair differs, return false.

If all values in the reversed second half match, return true.


===============================================================================
5. COMPLETE C++ SOLUTION
===============================================================================
*/

class Solution {
public:
    bool isPalindrome(ListNode* head) {

        // Pointers used to locate the middle of the linked list.
        ListNode* slow = head;
        ListNode* fast = head;

        // sec identifies the starting node of the second half.
        ListNode* sec = nullptr;

        // tr traverses the original first half during comparison.
        ListNode* tr = head;

        /*
        -------------------------------------------------------------------
        STAGE 1: FIND THE MIDDLE
        -------------------------------------------------------------------

        slow moves one node at a time.
        fast moves two nodes at a time.

        When the loop ends:
            - slow is at the middle or the start of the second half.
            - fast indicates whether the list length is odd or even.
        */

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        /*
        -------------------------------------------------------------------
        STAGE 2: IDENTIFY THE SECOND HALF
        -------------------------------------------------------------------

        Odd-length list:
            fast != nullptr
            The middle node is excluded from comparison.

        Even-length list:
            fast == nullptr
            The second half starts at slow.
        */

        if (fast != nullptr) {
            sec = slow->next;
        }
        else {
            sec = slow;
        }

        /*
        -------------------------------------------------------------------
        STAGE 3: REVERSE THE SECOND HALF
        -------------------------------------------------------------------

        previous points to the reversed portion.
        current points to the node currently being processed.
        next preserves access to the remaining unreversed nodes.
        */

        ListNode* previous = nullptr;
        ListNode* current = sec;
        ListNode* next = nullptr;

        while (current != nullptr) {

            // Save the original next node.
            next = current->next;

            // Reverse the current node's link.
            current->next = previous;

            // Advance the reversal pointers.
            previous = current;
            current = next;
        }

        /*
        After reversal:
            previous points to the head of the reversed second half.
            current == nullptr.
        */

        /*
        -------------------------------------------------------------------
        STAGE 4: COMPARE BOTH HALVES
        -------------------------------------------------------------------

        tr starts at the original head.

        previous starts at the head of the reversed second half.

        The second half is no longer than the first half, so it is
        sufficient to compare until previous reaches nullptr.
        */

        while (previous != nullptr) {

            // Compare the current values.
            if (previous->val != tr->val) {
                return false;
            }

            // Advance both pointers.
            previous = previous->next;
            tr = tr->next;
        }

        // Every compared pair matched.
        return true;
    }
};


/*
===============================================================================
6. DRY RUN: ODD-LENGTH PALINDROME
===============================================================================

Input:

    1 -> 2 -> 3 -> 2 -> 1 -> nullptr

STAGE 1: FIND THE MIDDLE
-----------------------

Initially:
    slow = node 1
    fast = node 1

After iteration 1:
    slow = node 2
    fast = node 3

After iteration 2:
    slow = node 3
    fast = nullptr

The loop ends.

The list has an odd number of nodes, so fast is nullptr here.

Correction to the interpretation:
    With the exact loop used in this implementation, fast is nullptr
    after the loop for this five-node list because fast attempts to move
    beyond the final node. The code's odd/even distinction depends on
    whether fast remains non-null at loop termination.


STAGE 2: IDENTIFY THE SECOND HALF
---------------------------------

For the five-node example, the second half should begin at node 4.

The correct selection is:

    sec = slow->next;

The middle node 3 is excluded from comparison.


STAGE 3: REVERSE THE SECOND HALF
--------------------------------

Before reversal:

    2 -> 1 -> nullptr

After reversal:

    1 -> 2 -> nullptr

STAGE 4: COMPARE
----------------

First half values:
    1, 2

Reversed second-half values:
    1, 2

Comparison:
    1 == 1
    2 == 2

Output:
    true


===============================================================================
7. DRY RUN: EVEN-LENGTH PALINDROME
===============================================================================

Input:

    1 -> 2 -> 2 -> 1 -> nullptr

STAGE 1: FIND THE MIDDLE
-----------------------

Initially:
    slow = node 1
    fast = node 1

After iteration 1:
    slow = node 2
    fast = node 2 (the third node)

After iteration 2:
    slow = node 3
    fast = nullptr

The loop ends.

STAGE 2: IDENTIFY THE SECOND HALF
---------------------------------

For an even-length list, the second half begins at slow.

    sec = slow;

The halves are:

    First half:  1 -> 2
    Second half: 2 -> 1

STAGE 3: REVERSE THE SECOND HALF
--------------------------------

Before:
    2 -> 1 -> nullptr

After:
    1 -> 2 -> nullptr

STAGE 4: COMPARE
----------------

First half:
    1 -> 2

Reversed second half:
    1 -> 2

All values match.

Output:
    true


===============================================================================
8. IMPORTANT POINTER CONCEPTS
===============================================================================

CONCEPT 1: SLOW AND FAST POINTERS
---------------------------------

The slow pointer moves one node per iteration.

The fast pointer moves two nodes per iteration.

This lets us find the middle in a single traversal.

The technique is also useful for:
    - Detecting cycles.
    - Finding the beginning of a cycle.
    - Splitting a linked list.
    - Reversing the second half of a list.


CONCEPT 2: WHY DO WE NEED THREE POINTERS FOR REVERSAL?
------------------------------------------------------

The reversal process uses:

    previous
    current
    next

The order is important:

    1. Save current->next in next.
    2. Point current->next to previous.
    3. Move previous to current.
    4. Move current to next.

If we change current->next before saving the original next node,
we can lose access to the remaining nodes.


CONCEPT 3: WHY COMPARE ONLY THE SECOND HALF?
--------------------------------------------

The first half contains at least as many nodes as the second half.

For odd-length lists, the middle node does not need a comparison.

Therefore, comparing every node in the reversed second half against
the corresponding node in the first half is sufficient.


CONCEPT 4: WHY IS previous USED AFTER REVERSAL?
-----------------------------------------------

After the reversal loop, current becomes nullptr.

The pointer previous identifies the new head of the reversed portion.

The original sec pointer still points to the node that was originally
the start of the second half, which becomes its tail after reversal.

Therefore, previous is the correct pointer for the comparison phase.


===============================================================================
9. EDGE CASES
===============================================================================

EDGE CASE 1: EMPTY LIST
-----------------------

Input:
    []

Expected:
    true

The empty list is conventionally considered a palindrome.

With head == nullptr:
    slow, fast, sec, tr are all nullptr.
    The reversal loop does not execute.
    The comparison loop does not execute.
    The function returns true.


EDGE CASE 2: ONE NODE
---------------------

Input:
    [1]

Expected:
    true

A single value reads the same forward and backward.

The second half is empty, so no mismatching pair exists.


EDGE CASE 3: TWO EQUAL NODES
----------------------------

Input:
    [1, 1]

Expected:
    true

After reversal, the two compared values match.


EDGE CASE 4: TWO DIFFERENT NODES
--------------------------------

Input:
    [1, 2]

Expected:
    false

The values do not match.


EDGE CASE 5: ODD-LENGTH PALINDROME
----------------------------------

Input:
    [1, 2, 3, 2, 1]

Expected:
    true

The middle value is excluded from the comparison.


EDGE CASE 6: EVEN-LENGTH PALINDROME
-----------------------------------

Input:
    [1, 2, 2, 1]

Expected:
    true

The two halves match after reversing the second half.


EDGE CASE 7: ODD-LENGTH NON-PALINDROME
--------------------------------------

Input:
    [1, 2, 3, 4, 1]

Expected:
    false

At least one corresponding pair differs.


EDGE CASE 8: EVEN-LENGTH NON-PALINDROME
---------------------------------------

Input:
    [1, 2, 3, 4]

Expected:
    false

The reversed second half does not match the first half.


===============================================================================
10. COMMON MISTAKES TO AVOID
===============================================================================

MISTAKE 1: INCORRECTLY IDENTIFYING THE SECOND HALF
--------------------------------------------------

Odd-length and even-length lists require different starting positions.

If the middle node is included incorrectly, the comparison may be shifted
by one position.


MISTAKE 2: LOSING THE ORIGINAL NEXT NODE DURING REVERSAL
-------------------------------------------------------

Incorrect order:

    current->next = previous;
    next = current->next;

This loses the original forward link.

Correct order:

    next = current->next;
    current->next = previous;


MISTAKE 3: DEREFERENCING nullptr
--------------------------------

Always ensure a pointer is valid before accessing its members.

The reversal loop uses:

    while (current != nullptr)

The comparison loop uses:

    while (previous != nullptr)

These guards ensure that the current node being processed exists.


MISTAKE 4: COMPARING THE ENTIRE FIRST HALF
------------------------------------------

For an odd-length list, the first half contains the middle node, while
the reversed second half does not.

Comparing only until the reversed second half ends avoids unnecessary
comparisons and handles the odd middle node naturally.


MISTAKE 5: FORGETTING THAT REVERSAL MODIFIES THE LIST
-----------------------------------------------------

This solution reverses the second half in place.

It does not restore the original list before returning.

LeetCode accepts this because the problem only requires returning the
correct boolean result. In another application, preserving the original
list might be required, in which case the second half should be reversed
again before returning.


===============================================================================
11. CORRECTNESS EXPLANATION
===============================================================================

A sequence is a palindrome if and only if its corresponding values from
opposite ends are equal.

The slow/fast pointer technique identifies the middle of the list.

For an odd-length list, the middle node is excluded because it has no
distinct counterpart.

For an even-length list, the list is divided into equal halves.

Reversing the second half places its values in the same order as the
corresponding values in the first half when comparing from the outside
toward the middle.

The comparison loop checks every node in the reversed second half.

If any pair differs, the sequence cannot be a palindrome, and returning
false is correct.

If all pairs match, every mirrored pair has equal values. Therefore,
the list is a palindrome, and returning true is correct.


===============================================================================
12. COMPLEXITY ANALYSIS
===============================================================================

TIME COMPLEXITY: O(n)
---------------------

Let n be the total number of nodes.

Finding the middle:
    O(n)

Reversing the second half:
    O(n)

Comparing both halves:
    O(n)

Total:

    O(n) + O(n) + O(n) = O(3n) = O(n)

Each stage traverses at most a linear number of nodes.


AUXILIARY SPACE COMPLEXITY: O(1)
--------------------------------

The algorithm uses a fixed number of pointers:

    slow
    fast
    sec
    tr
    previous
    current
    next

The number of pointers does not grow with the number of nodes.

The algorithm does not create an array or another data structure
proportional to the list length.

Therefore, auxiliary space is O(1).


===============================================================================
13. ALTERNATIVE APPROACHES
===============================================================================

APPROACH 1: COPY VALUES INTO AN ARRAY
-------------------------------------

Traverse the linked list and store each value in an array.

Compare the array from both ends.

Time complexity:
    O(n)

Auxiliary space:
    O(n)

This approach is straightforward but uses extra memory.


APPROACH 2: REVERSE THE SECOND HALF IN PLACE
--------------------------------------------

This is the approach implemented in this file.

Time complexity:
    O(n)

Auxiliary space:
    O(1)

It avoids storing all node values in another data structure.


APPROACH 3: RESTORE THE ORIGINAL LIST
-------------------------------------

If the list must remain unchanged after the function returns, reverse
the second half again after comparison.

This restores the original links.

The additional restoration traversal is linear, so the overall time
complexity remains O(n), and auxiliary space remains O(1).


===============================================================================
14. KEY TAKEAWAYS
===============================================================================

1. Slow and fast pointers are useful for finding the middle in one pass.

2. Reversing the second half allows a singly linked list to compare
   values from opposite ends.

3. Odd-length lists require special handling of the middle node.

4. Save the next pointer before changing any link during reversal.

5. A pointer can safely contain nullptr, but it must not be dereferenced.

6. Comparing only the reversed second half is sufficient.

7. The solution achieves O(n) time and O(1) auxiliary space.

8. In-place reversal changes the original links; restore them if required.


===============================================================================
15. FINAL SUMMARY
===============================================================================

Problem:
    Determine whether a singly linked list is a palindrome.

Algorithm:
    Find the middle, identify the second half, reverse it, and compare
    its values against the first half.

Time complexity:
    O(n)

Auxiliary space complexity:
    O(1)

Result:
    Accepted on LeetCode.

The central lesson is that combining a few well-understood pointer
techniques can solve a more complex linked-list problem efficiently.

===============================================================================
END OF FILE
===============================================================================
