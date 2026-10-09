/*
===============================================================================
                    LEETCODE 143 — REORDER LIST
===============================================================================

Difficulty : Medium
Topics    : Linked List, Two Pointers, Fast/Slow Pointers,
            Linked-List Reversal, In-Place Merging

-------------------------------------------------------------------------------
1. PROBLEM STATEMENT
-------------------------------------------------------------------------------

Given the head of a singly linked list:

    L0 -> L1 -> L2 -> ... -> Ln-1 -> Ln

Reorder the list into the following sequence:

    L0 -> Ln -> L1 -> Ln-1 -> L2 -> Ln-2 -> ...

The existing nodes must be reordered in place. Do not change their values
and do not create a separate list of copied nodes.

The function returns void, so the original list must be modified directly.

Examples
--------

Example 1:
    Input:  1 -> 2 -> 3 -> 4
    Output: 1 -> 4 -> 2 -> 3

Example 2:
    Input:  1 -> 2 -> 3 -> 4 -> 5
    Output: 1 -> 5 -> 2 -> 4 -> 3

Example 3:
    Input:  1 -> 2
    Output: 1 -> 2

-------------------------------------------------------------------------------
2. CORE IDEA
-------------------------------------------------------------------------------

The algorithm has three main phases:

    1. Find the middle of the linked list using slow and fast pointers.
    2. Reverse the second part of the linked list.
    3. Merge both parts alternately, taking one node from each part.

Example:

    Original:
        1 -> 2 -> 3 -> 4 -> 5

    After splitting:
        First part:  1 -> 2 -> 3
        Second part: 4 -> 5

    After reversing the second part:
        First part:            1 -> 2 -> 3
        Reversed second part:  5 -> 4

    After merging:
        1 -> 5 -> 2 -> 4 -> 3

All operations are performed in place. No additional list nodes are created.

-------------------------------------------------------------------------------
3. PHASE ONE — HANDLE SMALL LISTS
-------------------------------------------------------------------------------

The first two checks return early for lists containing one or two nodes.

    if (head->next == nullptr)
        return;

    if (head->next->next == nullptr)
        return;

One node:
    1 -> nullptr

There is nothing to reorder.

Two nodes:
    1 -> 2 -> nullptr

The list is already in the required order.

LeetCode 143 guarantees a non-empty list, so these checks are safe under the
problem constraints. They are optional for this algorithm.

For a more general implementation that may receive an empty list, the initial
guard could be:

    if (head == nullptr || head->next == nullptr)
        return;

-------------------------------------------------------------------------------
4. PHASE TWO — FIND THE MIDDLE
-------------------------------------------------------------------------------

    ListNode* slow = head;
    ListNode* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

Pointer roles:
    slow : Moves one node per iteration.
    fast : Moves two nodes per iteration.

Because fast moves twice as quickly, slow reaches the middle when fast reaches
the end or becomes nullptr.

Dry run: Five nodes
-------------------

    List: 1 -> 2 -> 3 -> 4 -> 5

    Iteration       slow        fast
    ---------------------------------
    Initial           1           1
    1                 2           3
    2                 3           5
    Stop              3           5

The loop stops because fast->next is nullptr. The slow pointer is at node 3,
and the second part begins at slow->next, which is node 4.

Dry run: Four nodes
-------------------

    List: 1 -> 2 -> 3 -> 4

    Iteration       slow        fast
    ---------------------------------
    Initial           1           1
    1                 2           3
    2                 3      nullptr
    Stop              3      nullptr

For an even-length list, slow points to the second middle node. Here, that is
node 3, and the second part begins at node 4.

With slow and fast both initialized to head:
    - Odd length: slow reaches the actual middle node.
    - Even length: slow reaches the second middle node.

-------------------------------------------------------------------------------
5. PHASE THREE — IDENTIFY AND SPLIT THE SECOND PART
-------------------------------------------------------------------------------

    ListNode* sec = nullptr;

    if (slow != nullptr) {
        sec = slow->next;
    }
    else {
        sec = slow;
    }

    slow->next = nullptr;

The sec pointer identifies the beginning of the second part.

Under the problem constraints, slow cannot be nullptr, so the if/else check is
redundant. The same operation can be simplified to:

    ListNode* sec = slow->next;
    slow->next = nullptr;

Why set slow->next to nullptr?
--------------------------------

Before splitting:

    1 -> 2 -> 3 -> 4 -> 5
              ^
             slow
                  ^
                 sec (node 4)

After setting slow->next to nullptr:

    First part:  1 -> 2 -> 3 -> nullptr
    Second part: 4 -> 5 -> nullptr

This disconnects the two parts so that the second part can be reversed
independently.

For an odd-length list, the middle node remains in the first part:

    First part:  1 -> 2 -> 3
    Second part: 4 -> 5

The first part therefore contains one more node than the second part.

-------------------------------------------------------------------------------
6. PHASE FOUR — REVERSE THE SECOND PART
-------------------------------------------------------------------------------

    ListNode* previous = nullptr;
    ListNode* current1 = sec;
    ListNode* next1 = nullptr;

    while (current1 != nullptr) {
        next1 = current1->next;
        current1->next = previous;
        previous = current1;
        current1 = next1;
    }

Pointer roles:
    previous : The already-reversed portion.
    current1 : The node currently being processed.
    next1    : Saves the next node before the link is changed.

Why save next1 first?
---------------------

Consider:

    4 -> 5 -> nullptr

Initially:
    previous = nullptr
    current1 = node 4

First, save the next node:

    next1 = current1->next;

Now next1 points to node 5.

Then reverse the link:

    current1->next = previous;

Node 4 now points to nullptr.

Advance the pointers:

    previous = current1;
    current1 = next1;

Now previous points to node 4, and current1 points to node 5. The next
iteration links node 5 back to node 4.

Result:

    5 -> 4 -> nullptr

Reversal trace:
    Step                 previous     current1       Reversed part
    ----------------------------------------------------------------
    Initial              nullptr         4           Empty
    After iteration 1       4             5           4 -> nullptr
    After iteration 2       5          nullptr        5 -> 4 -> nullptr

When the loop ends, previous points to the head of the reversed second part.
That is why the merge phase initializes current3 with previous.

-------------------------------------------------------------------------------
7. PHASE FIVE — MERGE BOTH PARTS
-------------------------------------------------------------------------------

After splitting and reversing the example list:

    First part:            1 -> 2 -> 3 -> nullptr
    Reversed second part:  5 -> 4 -> nullptr

The goal is to alternate nodes:
    - Take one node from the first part.
    - Take one node from the second part.
    - Repeat until the second part is exhausted.

Initialize the merge pointers:

    ListNode* current2 = head;
    ListNode* current3 = previous;
    ListNode* next2 = current2->next;
    ListNode* next3 = current3->next;

Pointer roles:
    current2 : Current node in the first part.
    current3 : Current node in the reversed second part.
    next2    : Next unprocessed node in the first part.
    next3    : Next unprocessed node in the second part.

Initially, for the five-node example:

    current2 -> 1
    current3 -> 5
    next2    -> 2
    next3    -> 4

The initial next2 and next3 assignments are not necessary because both are
reassigned at the beginning of each merge iteration. They are harmless.

The merging loop:

    while (current3 != nullptr) {
        next2 = current2->next;
        next3 = current3->next;

        current2->next = current3;
        current3->next = next2;

        current2 = next2;
        current3 = next3;
    }

First link update:
    current2->next = current3;

Connect the current first-part node to the current second-part node.

    1 -> 5

Second link update:
    current3->next = next2;

Connect that second-part node to the next unprocessed node in the first part.

    1 -> 5 -> 2 -> 3

The next iteration processes nodes 2 and 4.

Why save next2 and next3 before changing links?
------------------------------------------------

Changing a node's next pointer can destroy the original route to the next
unprocessed node. Save both next pointers before overwriting either link:

    next2 = current2->next;
    next3 = current3->next;

Then rewire the links and advance the pointers.

IMPORTANT PRINCIPLE:
    Preserve the next node before overwriting a link.

-------------------------------------------------------------------------------
8. COMPLETE DRY RUN — 1 -> 2 -> 3 -> 4 -> 5
-------------------------------------------------------------------------------

Step 1: Find the middle
    slow points to node 3.
    sec points to node 4.

Step 2: Split the list
    First part:  1 -> 2 -> 3 -> nullptr
    Second part: 4 -> 5 -> nullptr

Step 3: Reverse the second part
    First part:            1 -> 2 -> 3 -> nullptr
    Reversed second part:  5 -> 4 -> nullptr

Step 4: Merge the first pair
    current2 = 1
    current3 = 5
    next2    = 2
    next3    = 4

After rewiring:
    1 -> 5 -> 2 -> 3

Advance:
    current2 = 2
    current3 = 4

Step 5: Merge the second pair
    next2 = 3
    next3 = nullptr

After rewiring:
    1 -> 5 -> 2 -> 4 -> 3

Advance:
    current2 = 3
    current3 = nullptr

The loop ends because current3 is nullptr.

Final result:
    1 -> 5 -> 2 -> 4 -> 3 -> nullptr

-------------------------------------------------------------------------------
9. WHY DOES THE MERGE LOOP USE current3 != nullptr?
-------------------------------------------------------------------------------

    while (current3 != nullptr)

The first part has at least as many nodes as the second part because of where
the list is split.

    - Odd length: the first part contains the middle node and is one node longer.
    - Even length: this implementation also leaves the first part one node longer.

Therefore, the second part is never longer than the first part.

When current3 becomes nullptr, all nodes from the reversed second part have
been merged. Any remaining node in the first part is already correctly placed
at the end.

Example final node:
    1 -> 5 -> 2 -> 4 -> 3

Node 3 remains at the end after the second part is exhausted.

-------------------------------------------------------------------------------
10. COMMON MISTAKES
-------------------------------------------------------------------------------

Mistake 1: Forgetting to split the list
    slow->next = nullptr;

Without this disconnection, the parts remain connected, making reversal and
merging harder to manage and potentially causing incorrect links or cycles.

Mistake 2: Reversing before saving the next node

Incorrect:
    current1->next = previous;
    next1 = current1->next;

After the first statement, the original next node is no longer accessible
through current1->next.

Correct:
    next1 = current1->next;
    current1->next = previous;

Mistake 3: Overwriting merge links before saving both next pointers

Correct order:
    next2 = current2->next;
    next3 = current3->next;

Mistake 4: Advancing pointers too early

First reconnect both nodes:
    current2->next = current3;
    current3->next = next2;

Then advance:
    current2 = next2;
    current3 = next3;

Mistake 5: Using the wrong merge condition

    while (current3 != nullptr)

The second part determines the number of merge iterations because it is never
longer than the first part in this implementation.

-------------------------------------------------------------------------------
11. TIME AND SPACE COMPLEXITY
-------------------------------------------------------------------------------

Time Complexity: O(n)

The algorithm makes a constant number of linear passes:
    1. Find the middle: O(n).
    2. Reverse the second part: O(n).
    3. Merge both parts: O(n).

Total:
    O(n) + O(n) + O(n) = O(n)

Auxiliary Space Complexity: O(1)

The algorithm uses a fixed number of pointer variables. Their number does not
increase with the input size. No additional array, stack, or copied list is
created.

-------------------------------------------------------------------------------
12. WHY THIS IS AN IN-PLACE ALGORITHM
-------------------------------------------------------------------------------

The algorithm rearranges links between existing nodes instead of creating
new list nodes.

It uses:
    - Two-pointer traversal to find the middle.
    - Pointer reversal to reverse the second part.
    - Pointer rewiring to merge the two parts.

This is an example of solving a linked-list problem by changing links instead
of storing node values elsewhere.

-------------------------------------------------------------------------------
13. POSSIBLE CODE SIMPLIFICATIONS
-------------------------------------------------------------------------------

The accepted solution is correct under LeetCode 143's constraints. These are
optional cleanup opportunities, not correctness fixes.

A. More general early return

Instead of two separate checks, a version that also handles an empty list can
start with:

    if (head == nullptr || head->next == nullptr) {
        return;
    }

B. Simplify second-part initialization

Because slow is guaranteed to be non-null under the problem constraints:

    ListNode* sec = slow->next;
    slow->next = nullptr;

The if/else check around slow is redundant.

C. Simplify merge pointer initialization

These initial values:

    ListNode* next2 = current2->next;
    ListNode* next3 = current3->next;

can be replaced with:

    ListNode* next2 = nullptr;
    ListNode* next3 = nullptr;

Both variables are assigned at the start of each merge iteration before use.

-------------------------------------------------------------------------------
14. KEY TAKEAWAYS
-------------------------------------------------------------------------------

- Slow and fast pointers find the middle in O(n) time and O(1) auxiliary space.
- A list can be split by setting a node's next pointer to nullptr.
- During reversal, save the next node before changing the current link.
- During merging, save the next unprocessed node from both parts before rewiring.
- The second part is never longer than the first part in this implementation.
- The list can be reordered without creating additional list nodes.

-------------------------------------------------------------------------------
FINAL COMPLEXITY SUMMARY
-------------------------------------------------------------------------------

    Time Complexity:             O(n)
    Auxiliary Space Complexity:  O(1)
    In-place:                    Yes
    Additional list nodes:       None

Result:
    An in-place solution to LeetCode 143 — Reorder List using slow and fast
    pointers, linked-list reversal, and alternating merge.

===============================================================================
                         ACCEPTED SOLUTION BELOW
===============================================================================
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
public:
    void reorderList(ListNode* head) {
        if (head->next == nullptr) {
            return;
        }

        if (head->next->next == nullptr) {
            return;
        }

        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode* sec = nullptr;

        if (slow != nullptr) {
            sec = slow->next;
        }
        else {
            sec = slow;
        }

        slow->next = nullptr;

        ListNode* previous = nullptr;
        ListNode* current1 = sec;
        ListNode* next1 = nullptr;

        while (current1 != nullptr) {
            next1 = current1->next;
            current1->next = previous;
            previous = current1;
            current1 = next1;
        }

        ListNode* current2 = head;
        ListNode* current3 = previous;
        ListNode* next2 = current2->next;
        ListNode* next3 = current3->next;

        while (current3 != nullptr) {
            next2 = current2->next;
            next3 = current3->next;

            current2->next = current3;
            current3->next = next2;

            current2 = next2;
            current3 = next3;
        }

        return;
    }
};