/*
    ================================================================
    LeetCode 141 — Linked List Cycle
    DSA Day 14 — Linked Lists
    ================================================================

    Problem:
    Given the head of a linked list, determine whether the linked
    list contains a cycle.

    A cycle exists when a node's next pointer points back to a
    previous node in the linked list. Because of this, traversing
    the list will never reach nullptr.

    Example:

        No Cycle:
        1 -> 2 -> 3 -> 4 -> nullptr

        Cycle:
        1 -> 2 -> 3 -> 4
             ^         |
             |_________|

    ================================================================
    APPROACH
    ================================================================

    We use Floyd's Cycle Detection Algorithm, also known as the
    Slow and Fast Pointer technique.

    We maintain two pointers:

        slow -> moves one node at a time
        fast -> moves two nodes at a time

    Both pointers start from head.

    If there is NO cycle:
        - slow and fast will eventually reach nullptr.
        - Therefore, we return false.

    If there IS a cycle:
        - Once both pointers enter the cycle, the fast pointer keeps
          gaining on the slow pointer.
        - Eventually, fast catches slow.
        - Therefore, if slow == fast, a cycle exists.

    ================================================================
    WHY DOES THE FAST POINTER CATCH THE SLOW POINTER?
    ================================================================

    Imagine two runners running around a circular track.

        Runner 1 (slow) -> moves 1 step
        Runner 2 (fast) -> moves 2 steps

    The faster runner gains one step on the slower runner during
    every iteration.

    Since the track is circular, the fast runner must eventually
    catch the slow runner.

    The same idea applies to a cyclic linked list.

    ================================================================
    INITIALIZATION
    ================================================================

        ListNode* slow = head;
        ListNode* fast = head;

    Both pointers start at the same node.

    IMPORTANT:
    We do NOT check slow == fast immediately after initialization.

    If we did:

        if (slow == fast)
            return true;

    the condition would always be true because both pointers start
    at head.

    Instead, we first move the pointers and then compare them.

    ================================================================
    MAIN LOOP
    ================================================================

        while (fast != nullptr && fast->next != nullptr)

    This condition is extremely important.

    We move fast by two nodes:

        fast = fast->next->next;

    Therefore, before accessing fast->next->next, we must make sure:

        1. fast is not nullptr
        2. fast->next is not nullptr

    Otherwise, we could dereference a nullptr and cause a
    segmentation fault.

    Inside the loop:

        slow = slow->next;
        fast = fast->next->next;

    Then:

        if (slow == fast)
            return true;

    ================================================================
    IMPORTANT ISSUES WE FACED
    ================================================================

    1. Checking slow == fast before moving

       Initially, both pointers are:

           slow = head
           fast = head

       Therefore:

           slow == fast

       would immediately be true even when the linked list has
       NO cycle.

       FIX:
       Move the pointers first and then compare them.

    ---------------------------------------------------------------

    2. Understanding the while-loop condition

       We cannot simply write:

           while (fast != nullptr)

       because fast moves two steps:

           fast = fast->next->next;

       If fast->next is nullptr, accessing:

           fast->next->next

       would be invalid.

       FIX:

           while (fast != nullptr && fast->next != nullptr)

       This safely allows the fast pointer to move two nodes.

    ---------------------------------------------------------------

    3. One-node linked list

       A list containing only one node does NOT automatically mean
       there is no cycle.

       Example:

           1
           ^ \
           |  |
           |__|

       This is a cycle if:

           node->next = node;

       Floyd's algorithm handles this case naturally.

       After the first movement:

           slow -> node
           fast -> node

       They meet, so we correctly return true.

       If the one node points to nullptr:

           1 -> nullptr

       the loop condition fails and we return false.

    ================================================================
    DRY RUN 1 — NO CYCLE
    ================================================================

    Linked list:

        1 -> 2 -> 3 -> 4 -> nullptr

    Initial:

        slow = 1
        fast = 1

    Iteration 1:

        slow = 2
        fast = 3

        slow != fast

    Iteration 2:

        slow = 3
        fast = nullptr

        Loop stops.

    Result:

        return false

    Therefore, there is no cycle.

    ================================================================
    DRY RUN 2 — CYCLE EXISTS
    ================================================================

    Linked list:

        1 -> 2 -> 3 -> 4
                  ^    |
                  |____|

    The cycle is:

        3 -> 4 -> 3 -> 4 -> ...

    Initial:

        slow = 1
        fast = 1

    Iteration 1:

        slow = 2
        fast = 3

        slow != fast

    Iteration 2:

        slow = 3
        fast = 3

        slow == fast

    Therefore:

        return true

    ================================================================
    DRY RUN 3 — ONE NODE WITH A SELF-CYCLE
    ================================================================

        1
        |
        └----> 1

    Initial:

        slow = 1
        fast = 1

    Move:

        slow = 1
        fast = 1

    They meet:

        slow == fast

    Therefore:

        return true

    ================================================================
    DRY RUN 4 — ONE NODE WITHOUT A CYCLE
    ================================================================

        1 -> nullptr

    Initial:

        slow = 1
        fast = 1

    Check:

        fast != nullptr          -> true
        fast->next != nullptr    -> false

    Therefore, the loop does not execute.

    Result:

        return false

    ================================================================
    CORRECTNESS / WHY THE ALGORITHM WORKS
    ================================================================

    There are two possible situations.

    CASE 1: No cycle

    The linked list eventually reaches nullptr.

    Since fast moves twice as quickly as slow, fast will reach the
    end of the list. The loop terminates and we return false.

    CASE 2: A cycle exists

    Once both pointers enter the cycle, fast moves two positions for
    every one position moved by slow.

    Therefore, fast gains one position on slow during every
    iteration.

    Because the cycle has a finite number of nodes, fast must
    eventually catch slow.

    When:

        slow == fast

    a cycle definitely exists, so we return true.

    ================================================================
    FINAL CODE
    ================================================================
*/

class Solution {
public:
    bool hasCycle(ListNode* head) {

        // Slow moves one step at a time.
        ListNode* slow = head;

        // Fast moves two steps at a time.
        ListNode* fast = head;

        // We need both fast and fast->next to exist because
        // fast moves two nodes at a time.
        while (fast != nullptr && fast->next != nullptr) {

            slow = slow->next;
            fast = fast->next->next;

            // If both pointers meet, a cycle exists.
            if (fast == slow) {
                return true;
            }
        }

        // Fast reached the end, so there is no cycle.
        return false;
    }
};

/*
    ================================================================
    COMPLEXITY ANALYSIS
    ================================================================

    Time Complexity:
        O(n)

    In the worst case, the pointers traverse the linked list/cycle
    a constant number of times before either reaching nullptr or
    meeting.

    Space Complexity:
        O(1)

    We only use two additional pointers:

        slow
        fast

    No extra data structure such as a hash set is required.

    ================================================================
    KEY TAKEAWAYS
    ================================================================

    1. Floyd's Cycle Detection uses two pointers:
           slow -> 1 step
           fast -> 2 steps

    2. Initialize both pointers at head.

    3. Move first, then compare.
       Do NOT compare slow and fast immediately after initialization.

    4. Always protect:
           fast->next->next

       with:

           fast != nullptr && fast->next != nullptr

    5. A one-node list can still contain a cycle if:
           node->next == node

    6. If slow and fast meet:
           cycle exists

    7. If fast reaches nullptr:
           no cycle

    8. The algorithm uses:
           O(n) time
           O(1) extra space

    ================================================================
    PATTERN RECOGNITION
    ================================================================

    This problem introduces an extremely important linked-list
    pattern:

        FAST & SLOW POINTERS

    This pattern will appear in several other linked-list problems,
    including:

        - Finding the middle of a linked list
        - Detecting the start of a cycle
        - Finding a palindrome
        - Reordering a linked list

    The important lesson is not only memorizing Floyd's algorithm.

    The real lesson is recognizing when two pointers moving at
    different speeds can reveal structural information about a
    linked list.

    ================================================================
    LESSON FROM THIS PROBLEM
    ================================================================

    The biggest improvement in this problem was not simply writing
    the final code.

    It was understanding WHY each condition and pointer movement
    exists.

    The final algorithm is short:

        slow = slow->next;
        fast = fast->next->next;

    But the important reasoning is:

        Why two pointers?
        Why different speeds?
        Why start together?
        Why move before comparing?
        Why check fast and fast->next?
        Why does meeting prove a cycle?

    Understanding these questions makes the pattern reusable instead
    of making the solution something that has to be memorized.

    ================================================================
    END
    ================================================================
*/