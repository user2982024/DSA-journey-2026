/*
    ================================================================
    LeetCode 142 — Linked List Cycle II
    DSA Day 14 — Linked Lists
    ================================================================

    Problem:
    Given the head of a linked list, return the node where the cycle
    begins.

    If there is no cycle, return nullptr.

    IMPORTANT:
    We are not only checking whether a cycle exists.

    We need to find the EXACT NODE where the cycle starts.

    Example:

        1 -> 2 -> 3 -> 4 -> 5
                  ^         |
                  |_________|

        Cycle begins at node 3.

        Answer: node 3


    ================================================================
    APPROACH
    ================================================================

    We use Floyd's Cycle Detection Algorithm with two phases.

    PHASE 1:
        Detect whether a cycle exists and find any point where the
        slow and fast pointers meet inside the cycle.

    PHASE 2:
        Find the exact node where the cycle begins.

    We use two pointers:

        slow -> moves one step
        fast -> moves two steps

    Initially:

        slow = head
        fast = head


    ================================================================
    PHASE 1 — FIND A MEETING POINT
    ================================================================

    We move:

        slow = slow->next;
        fast = fast->next->next;

    If:

        slow == fast

    then a cycle exists.

    We do NOT immediately return the meeting node because the
    meeting point is not necessarily the beginning of the cycle.

    It is only some point inside the cycle.

    Example:

        1 -> 2 -> 3 -> 4 -> 5
                  ^         |
                  |_________|

    The pointers might meet at node 4.

    But the cycle actually begins at node 3.

    Therefore, we need PHASE 2.


    ================================================================
    IMPORTANT SAFETY CONDITION
    ================================================================

        while (fast != nullptr && fast->next != nullptr)

    This condition is necessary because fast moves two nodes:

        fast = fast->next->next;

    Before accessing fast->next->next, we must make sure:

        fast != nullptr
        fast->next != nullptr

    Otherwise, dereferencing nullptr could cause a segmentation
    fault.


    ================================================================
    PHASE 1 CODE
    ================================================================

        while (fast != nullptr && fast->next != nullptr) {

            slow = slow->next;
            fast = fast->next->next;

            if (fast == slow) {
                break;
            }
        }

    Notice that we use break instead of immediately returning.

    Why?

    Because if a cycle exists, we need to continue with PHASE 2
    after finding the meeting point.

    Therefore, break exits the loop while preserving the positions
    of slow and fast.


    ================================================================
    CHECK WHETHER A CYCLE ACTUALLY EXISTS
    ================================================================

    After PHASE 1, there are two possibilities.

    CASE 1:
    A cycle exists.

    Then slow and fast have met inside the cycle.

    CASE 2:
    No cycle exists.

    In that situation, fast reaches nullptr or fast->next reaches
    nullptr.

    Therefore:

        if (fast == nullptr || fast->next == nullptr)
            return nullptr;

    This check is extremely important.

    Without it, we could incorrectly enter PHASE 2 even though
    there is no cycle.


    ================================================================
    PHASE 2 — FIND THE CYCLE ENTRANCE
    ================================================================

    Once slow and fast meet inside the cycle:

        slow = head;

    We reset slow to the beginning of the linked list.

    Fast remains at the meeting point.

    Then both pointers move ONE step at a time:

        slow = slow->next;
        fast = fast->next;

    They will meet exactly at the beginning of the cycle.

    Therefore:

        return slow;


    ================================================================
    WHY DOES RESETTING SLOW TO HEAD WORK?
    ================================================================

    This is the most important concept in this problem.

    Let:

        A = distance from head to the cycle entrance

        B = distance from cycle entrance to the meeting point

        L = length of the entire cycle

    At the meeting point:

        slow has traveled:

            A + B

        fast has traveled:

            A + B + kL

    where k is some positive integer representing complete
    rotations around the cycle.

    Since fast moves twice as fast as slow:

        2(A + B) = A + B + kL

    Simplifying:

        A + B = kL

    Therefore:

        A = kL - B

    This means that the distance from:

        head -> cycle entrance

    is equivalent to the distance from:

        meeting point -> cycle entrance

    when moving around the cycle.

    Therefore, if we:

        1. Put slow back at head.
        2. Keep fast at the meeting point.
        3. Move both one step at a time.

    They will meet exactly at the cycle entrance.


    ================================================================
    INTUITIVE EXPLANATION
    ================================================================

    Imagine the linked list as:

        HEAD
          |
          v
        A -> B -> C -> D -> E
                  ^         |
                  |_________|

    Suppose the pointers meet somewhere inside the cycle.

    At that meeting point, the distance remaining around the cycle
    back to the entrance is related exactly to the distance from
    the head to the entrance.

    So we create two starting points:

        slow -> head

        fast -> meeting point

    Now both move at the same speed.

    Because their remaining distances to the cycle entrance are
    aligned, they meet at the entrance.

    This is why PHASE 2 works.


    ================================================================
    ISSUE WE FACED #1 — MEETING POINT IS NOT THE ANSWER
    ================================================================

    A common mistake is:

        if (slow == fast)
            return slow;

    This is incorrect for LeetCode 142.

    The meeting point only proves that a cycle exists.

    It does NOT necessarily represent the beginning of the cycle.

    Therefore:

        PHASE 1 -> find any meeting point
        PHASE 2 -> find the exact cycle entrance


    ================================================================
    ISSUE WE FACED #2 — WHAT IF THERE IS NO CYCLE?
    ================================================================

    We initially needed to make sure that PHASE 2 is only executed
    when a cycle actually exists.

    Consider:

        1 -> 2 -> 3 -> nullptr

    Eventually:

        fast == nullptr

    or:

        fast->next == nullptr

    Therefore we must write:

        if (fast == nullptr || fast->next == nullptr) {
            return nullptr;
        }

    Only after this check do we begin PHASE 2.


    ================================================================
    ISSUE WE FACED #3 — WHY NO ELSE IS REQUIRED
    ================================================================

    After:

        return nullptr;

    the function immediately terminates.

    Therefore, if execution reaches the next line:

        slow = head;

    we already know that a cycle exists.

    There is no need to write:

        else {
            ...
        }

    The return statement already separates the two cases.


    ================================================================
    ISSUE WE FACED #4 — WHY CAN WE RETURN slow?
    ================================================================

    After PHASE 2:

        while (slow != fast)

    terminates, we know:

        slow == fast

    Both pointers are at the cycle entrance.

    Therefore, either pointer could technically be returned:

        return slow;

    or:

        return fast;

    Both are correct.

    We conventionally return slow.


    ================================================================
    DRY RUN 1 — CYCLE EXISTS
    ================================================================

    Consider:

        1 -> 2 -> 3 -> 4 -> 5
                  ^         |
                  |_________|

    Cycle entrance = 3

    PHASE 1:

    Initial:

        slow = 1
        fast = 1

    Iteration 1:

        slow = 2
        fast = 3

    Iteration 2:

        slow = 3
        fast = 5

    Iteration 3:

        slow = 4
        fast = 4

    Meeting point:

        slow = 4
        fast = 4

    We break out of the loop.


    PHASE 1 RESULT:

        A cycle exists.

    Now:

        slow = head

    Therefore:

        slow = 1
        fast = 4


    PHASE 2:

    Iteration 1:

        slow = 2
        fast = 5

    Iteration 2:

        slow = 3
        fast = 3

    They meet at node 3.

    Therefore:

        return slow;

    Answer:

        node 3


    ================================================================
    DRY RUN 2 — NO CYCLE
    ================================================================

        1 -> 2 -> 3 -> 4 -> nullptr

    Initial:

        slow = 1
        fast = 1

    Iteration 1:

        slow = 2
        fast = 3

    Iteration 2:

        slow = 3
        fast = nullptr

    Loop terminates.

    Now:

        fast == nullptr

    Therefore:

        return nullptr;

    PHASE 2 is never executed.


    ================================================================
    DRY RUN 3 — ONE NODE WITHOUT A CYCLE
    ================================================================

        1 -> nullptr

    Initial:

        slow = 1
        fast = 1

    Loop condition:

        fast != nullptr
            -> true

        fast->next != nullptr
            -> false

    Loop does not execute.

    Therefore:

        return nullptr;


    ================================================================
    DRY RUN 4 — ONE NODE WITH A SELF-CYCLE
    ================================================================

        1
        |
        └----> 1

    Initial:

        slow = 1
        fast = 1

    First iteration:

        slow = 1
        fast = 1

    They meet immediately.

    PHASE 1:

        cycle exists.

    Reset:

        slow = head = 1
        fast = 1

    PHASE 2 condition:

        slow != fast

    is false.

    Therefore, PHASE 2 does not execute.

    Return:

        node 1

    This is correct because the only node is the cycle entrance.


    ================================================================
    FINAL CODE
    ================================================================
*/

class Solution {
public:
    ListNode* detectCycle(ListNode* head) {

        // Phase 1:
        // Use Floyd's algorithm to find a meeting point
        // inside the cycle, if one exists.
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != nullptr && fast->next != nullptr) {

            slow = slow->next;
            fast = fast->next->next;

            // A meeting proves that a cycle exists.
            if (fast == slow) {
                break;
            }
        }

        // If fast reached the end, there is no cycle.
        if (fast == nullptr || fast->next == nullptr) {
            return nullptr;
        }

        // Phase 2:
        // Move slow back to the head.
        slow = head;

        // Move both pointers one step at a time.
        // Their meeting point is the cycle entrance.
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }

        return slow;
    }
};

/*
    ================================================================
    COMPLEXITY ANALYSIS
    ================================================================

    Time Complexity:
        O(n)

    PHASE 1 takes O(n) time in the worst case.

    PHASE 2 also takes O(n) time in the worst case.

    Therefore:

        O(n) + O(n) = O(n)

    Overall:

        O(n)


    Space Complexity:
        O(1)

    We only use two pointers:

        slow
        fast

    No hash set, array, vector, or other data structure is used.

    Therefore, the extra space is constant.


    ================================================================
    KEY TAKEAWAYS
    ================================================================

    1. This problem is an extension of LeetCode 141.

    2. PHASE 1:
       Detect whether a cycle exists.

    3. The meeting point is NOT necessarily the cycle entrance.

    4. PHASE 2:
       Reset slow to head.

    5. Keep fast at the meeting point.

    6. Move both one step at a time.

    7. Their next meeting point is the cycle entrance.

    8. If fast reaches nullptr, return nullptr.

    9. No extra data structure is required.

    10. Complexity:
            Time  -> O(n)
            Space -> O(1)


    ================================================================
    PATTERN RECOGNITION
    ================================================================

    The main pattern is:

        FAST + SLOW POINTERS

    This is one of the most important linked-list techniques.

    It can be used for:

        - Detecting a cycle
        - Finding the cycle entrance
        - Finding the middle node
        - Detecting palindromes
        - Reordering linked lists

    LeetCode 141 and 142 should therefore be remembered together:

        LC 141:
            "Does a cycle exist?"

        LC 142:
            "Where does the cycle begin?"


    ================================================================
    FINAL LESSON
    ================================================================

    The most important thing learned from this problem is not simply
    memorizing:

        slow = head;

    followed by:

        while (slow != fast)

    The important understanding is WHY this works.

    The meeting point from PHASE 1 gives us a mathematical
    relationship between:

        distance from head to cycle entrance

    and:

        distance from meeting point to cycle entrance.

    Therefore, resetting one pointer to head and moving both at the
    same speed makes them meet exactly at the cycle entrance.

    This turns Floyd's algorithm from a memorized trick into a
    reusable algorithmic pattern.

    ================================================================
    END
    ================================================================
*/