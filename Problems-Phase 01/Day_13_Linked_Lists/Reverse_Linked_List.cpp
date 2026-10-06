/*
    ============================================================
    Problem: Reverse Linked List
    Platform: LeetCode
    Problem Number: 206
    Difficulty: Easy

    Link:
    https://leetcode.com/problems/reverse-linked-list/

    ============================================================
    Problem Statement:

    Given the head of a singly linked list, reverse the list
    and return the reversed list.

    Example:

    Input:
        1 → 2 → 3 → 4 → 5 → nullptr

    Output:
        5 → 4 → 3 → 2 → 1 → nullptr

    ============================================================
    APPROACH:

    We reverse the linked list by changing the direction of
    every node's next pointer.

    We use three pointers:

        previous
        current
        next

    Initially:

        previous = nullptr
        current  = head
        next     = current->next

    At every iteration:

        1. Save the next node.
        2. Reverse current's next pointer.
        3. Move previous forward.
        4. Move current forward.

    The important order is:

        next = current->next;
        current->next = previous;
        previous = current;
        current = next;

    Why do we need 'next'?

    Once we execute:

        current->next = previous;

    the original connection from current to the next node
    is lost. Therefore, we must save the next node before
    changing the link.

    ============================================================
    POINTER MOVEMENT:

    Example:

        1 → 2 → 3 → 4 → nullptr

    Initially:

        previous = nullptr
        current  = 1
        next     = 2

    After processing 1:

        nullptr ← 1    2 → 3 → 4

        previous = 1
        current  = 2

    After processing 2:

        nullptr ← 1 ← 2    3 → 4

        previous = 2
        current  = 3

    After processing 3:

        nullptr ← 1 ← 2 ← 3    4

        previous = 3
        current  = 4

    After processing 4:

        nullptr ← 1 ← 2 ← 3 ← 4

        previous = 4
        current  = nullptr

    At this point, previous points to the new head.

    Therefore:

        return previous;

    ============================================================
    EDGE CASES:

    1. Empty linked list

        Input:
            nullptr

        There is nothing to reverse.

        Return:
            nullptr

        Handled by:

            if (head == nullptr)
                return head;

    ------------------------------------------------------------

    2. Single-node linked list

        Input:
            1 → nullptr

        A single node is already reversed.

        Return:
            1 → nullptr

        Handled by:

            if (head->next == nullptr)
                return head;

    ------------------------------------------------------------

    3. Two-node linked list

        Input:
            1 → 2 → nullptr

        Output:
            2 → 1 → nullptr

        The three-pointer algorithm handles this naturally.

    ------------------------------------------------------------

    4. Multiple-node linked list

        Input:
            1 → 2 → 3 → 4 → 5

        Output:
            5 → 4 → 3 → 2 → 1

        Every link is reversed one by one.

    ============================================================
    IMPORTANT ISSUE ENCOUNTERED DURING SOLVING:

    Initially, there was a mistake in updating the 'next'
    pointer.

    Incorrect idea:

        next = next->next;

    This is dangerous because 'next' should represent the
    original next node of 'current'.

    Correct:

        next = current->next;

    Why?

    Suppose:

        1 → 2 → 3 → nullptr

    If current = 1:

        next must become 2.

    Then we reverse:

        current->next = previous;

    After that, current can safely move to the saved node:

        current = next;

    Using:

        next = next->next;

    can skip nodes and can eventually lose access to part
    of the linked list.

    ============================================================
    ANOTHER IMPORTANT REALIZATION:

    The new head of the reversed list is NOT the original
    head.

    Example:

        Original:
            1 → 2 → 3 → nullptr

        Reversed:
            3 → 2 → 1 → nullptr

    After the loop:

        current  = nullptr
        previous = 3

    Therefore:

        return previous;

    'previous' is pointing to the node that became the new
    head.

    ============================================================
    WHY WE DON'T NEED SPECIAL HANDLING INSIDE THE LOOP:

    The loop:

        while (current != nullptr)

    naturally handles:

        0 nodes
        1 node
        2 nodes
        multiple nodes

    The explicit edge-case checks for nullptr and a single
    node are therefore optional from a correctness perspective,
    but they make the intention clear.

    ============================================================
    DRY RUN:

    Input:

        1 → 2 → 3 → nullptr

    Initial:

        previous = nullptr
        current  = 1

    ------------------------------------------------------------

    Iteration 1:

        next = 2
        1->next = nullptr
        previous = 1
        current = 2

        List:

        nullptr ← 1    2 → 3

    ------------------------------------------------------------

    Iteration 2:

        next = 3
        2->next = 1
        previous = 2
        current = 3

        List:

        nullptr ← 1 ← 2    3

    ------------------------------------------------------------

    Iteration 3:

        next = nullptr
        3->next = 2
        previous = 3
        current = nullptr

        List:

        nullptr ← 1 ← 2 ← 3

    ------------------------------------------------------------

    Loop ends because:

        current == nullptr

    Return:

        previous

    Final list:

        3 → 2 → 1 → nullptr

    ============================================================
    ALGORITHM:

        1. Set previous = nullptr.
        2. Set current = head.
        3. While current is not nullptr:
             a. Save current->next in next.
             b. Reverse current->next to previous.
             c. Move previous to current.
             d. Move current to next.
        4. Return previous.

    ============================================================
    COMPLEXITY ANALYSIS:

    Let n be the number of nodes.

    Time Complexity:
        O(n)

    Every node is visited exactly once.

    Space Complexity:
        O(1)

    Only three pointer variables are used.
    No additional data structure is required.

    ============================================================
    FINAL CODE:
*/

class Solution {
public:
    ListNode* reverseList(ListNode* head) {

        // Edge case: empty list
        if (head == nullptr) {
            return head;
        }

        // Edge case: single-node list
        if (head->next == nullptr) {
            return head;
        }

        ListNode* previous = nullptr;
        ListNode* current = head;
        ListNode* next = current->next;

        while (current != nullptr) {

            // Save the next node before changing the link
            next = current->next;

            // Reverse the current node's pointer
            current->next = previous;

            // Move previous forward
            previous = current;

            // Move current forward
            current = next;
        }

        // previous is now the new head
        return previous;
    }
};

/*
    ============================================================
    KEY TAKEAWAY:

    The core pattern for iterative linked-list reversal is:

        next = current->next;
        current->next = previous;
        previous = current;
        current = next;

    Memorizing this pattern is less important than understanding
    WHY the order matters.

    The most important rule:

        SAVE THE NEXT NODE BEFORE BREAKING THE CURRENT LINK.

    ============================================================
*/