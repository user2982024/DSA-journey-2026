/*
    ========================================================================
    LeetCode 21 — Merge Two Sorted Lists
    DSA Day 14 — Linked Lists
    ========================================================================

    Problem:
    Given the heads of two sorted singly linked lists, merge the two
    lists into one sorted linked list and return the head of the
    merged list.

    The original nodes should be reused rather than creating a new
    list of nodes.

    Example:

        list1:
        1 -> 3 -> 5 -> nullptr

        list2:
        2 -> 4 -> 6 -> nullptr

        Merged:
        1 -> 2 -> 3 -> 4 -> 5 -> 6 -> nullptr


    ========================================================================
    APPROACH
    ========================================================================

    We use a two-pointer approach.

    We maintain four pointers:

        current1
            Points to the current unmerged node of list1.

        current2
            Points to the current unmerged node of list2.

        head
            Points to the first node of the merged list.
            Once assigned, head never changes.

        tail
            Points to the last node currently present in the merged
            list. It moves forward whenever a new node is attached.

    Important invariant:

        Everything from head through tail is already correctly
        merged and sorted.

        current1 and current2 always point to the first unmerged
        nodes of their respective lists.


    ========================================================================
    WHY DO WE NEED current1 AND current2?
    ========================================================================

    At every step, we compare:

        current1->val
        current2->val

    The smaller value should be the next node in the merged list.

    If:

        current1->val <= current2->val

    we attach current1.

    Otherwise:

        current2->val < current1->val

    so we attach current2.


    ========================================================================
    EDGE CASES
    ========================================================================

    Before doing the main merging logic, we handle empty lists.

    CASE 1:
    list1 is empty.

        list1 == nullptr

    Then there is nothing to merge from list1, so we simply return
    list2.

        return list2;


    CASE 2:
    list2 is empty.

        list2 == nullptr

    Return list1.

        return list1;


    CASE 3:
    Both lists are empty.

        list1 == nullptr
        list2 == nullptr

    The first condition already returns list2, which is nullptr.

    Therefore, no separate condition is required for both lists being
    empty.


    ========================================================================
    INITIALIZATION
    ========================================================================

        ListNode* current1 = list1;
        ListNode* current2 = list2;

        ListNode* head = nullptr;
        ListNode* tail = nullptr;

    Initially, the merged list does not contain any node.

    Therefore:

        head = nullptr
        tail = nullptr


    ========================================================================
    MAIN LOOP
    ========================================================================

        while (current1 != nullptr && current2 != nullptr)

    We continue comparing nodes while BOTH lists still contain an
    unmerged node.

    This condition is also important for safety.

    Because inside the loop we access:

        current1->val
        current2->val

    we must know that both pointers are not nullptr.


    ========================================================================
    SELECTING THE NEXT NODE
    ========================================================================

    We compare:

        current1->val <= current2->val

    If true, current1 is selected.

    Otherwise, current2 is selected.

    We use <= instead of < so that if both values are equal, we
    simply choose the node from list1.

    Either choice would be correct when the values are equal.


    ========================================================================
    IMPORTANT ISSUE #1 — HANDLING THE FIRST NODE
    ========================================================================

    One of the main difficulties in this problem was deciding how
    to initialize the merged list.

    Initially:

        head = nullptr
        tail = nullptr

    When we select the FIRST node, there is no existing tail to
    attach it to.

    Therefore, when:

        head == nullptr

    we know that the merged list is empty.

    We set:

        head = selected node;
        tail = selected node;

    This establishes the first node of the merged list.

    Both head and tail point to the same node initially.


    ========================================================================
    IMPORTANT ISSUE #2 — WHY DOES head NOT MOVE?
    ========================================================================

    After the first node is selected:

        head
         |
         v
        1

    Suppose we later add:

        2
        3
        4

    We want:

        head
         |
         v
        1 -> 2 -> 3 -> 4
                       ^
                       |
                      tail

    head must always remain at node 1.

    Therefore:

        head = ...

    should only happen once.

    tail is the pointer that moves.

    This gives us:

        head -> first node
        tail -> last node


    ========================================================================
    IMPORTANT ISSUE #3 — WHY DO WE UPDATE tail?
    ========================================================================

    Suppose the merged list is:

        1 -> 3

    and tail points to 3.

    We want to attach 5.

    We do:

        tail->next = current1;

    Now:

        1 -> 3 -> 5

    Then tail must move to the newly added node:

        tail = tail->next;

    So:

        tail
          |
          v
        5

    This allows us to continue building the list.


    ========================================================================
    IMPORTANT ISSUE #4 — HOW DO WE MOVE THROUGH A LINKED LIST?
    ========================================================================

    In an array, we commonly use:

        i++

    But linked lists do not work like arrays.

    To move to the next node, we use:

        current1 = current1->next;

    or:

        current2 = current2->next;

    This follows the actual pointer stored inside the node.


    ========================================================================
    IMPORTANT ISSUE #5 — DO NOT ATTACH A NODE BEFORE COMPARING
    ========================================================================

    We must first determine which node is smaller.

    Only after selecting the node do we attach it to the merged list.

    Therefore, each iteration follows this sequence:

        1. Compare current1 and current2.
        2. Select the smaller node.
        3. Attach that node.
        4. Move tail.
        5. Advance the pointer of the list from which the node
           was selected.


    ========================================================================
    FIRST-NODE LOGIC
    ========================================================================

    If current1 is selected:

        if (head == nullptr) {
            head = current1;
            tail = current1;
        }

    Otherwise:

        tail->next = current1;
        tail = tail->next;

    The exact same logic is required when current2 is selected.

    This symmetry is important.

    A common mistake would be to handle the first node correctly
    when selecting from list1 but forget the same situation when
    selecting from list2.


    ========================================================================
    WHY DO WE ADVANCE ONLY ONE CURRENT POINTER?
    ========================================================================

    Suppose:

        current1->val <= current2->val

    Then current1 is selected.

    Therefore, after attaching current1, we move:

        current1 = current1->next;

    We do NOT move current2.

    Why?

    Because current2 has not been used yet.

    It still needs to be compared against the next node from list1.

    Similarly, if current2 is selected, only current2 advances.


    ========================================================================
    MAIN MERGING PROCESS
    ========================================================================

    Example:

        list1:
        1 -> 4 -> 7

        list2:
        2 -> 3 -> 8

    Initial:

        current1 = 1
        current2 = 2

    Compare:

        1 <= 2

    Select 1.

        merged:
        1

        current1 -> 4


    Compare:

        4 > 2

    Select 2.

        merged:
        1 -> 2

        current2 -> 3


    Compare:

        4 > 3

    Select 3.

        merged:
        1 -> 2 -> 3

        current2 -> 8


    Compare:

        4 <= 8

    Select 4.

        merged:
        1 -> 2 -> 3 -> 4

        current1 -> 7


    Compare:

        7 <= 8

    Select 7.

        merged:
        1 -> 2 -> 3 -> 4 -> 7

        current1 -> nullptr


    Now the main loop stops because:

        current1 == nullptr


    ========================================================================
    ATTACHING THE REMAINING NODES
    ========================================================================

    At this point, one list is exhausted.

    However, the other list may still contain nodes.

    Example:

        merged:
        1 -> 2 -> 3 -> 4 -> 7

        remaining list2:
        8

    Since list2 is already sorted, there is no need to compare
    anything anymore.

    We can directly attach the remaining nodes.

    Therefore:

        while (current1 != nullptr) {
            ...
        }

    attaches any remaining nodes from list1.

    And:

        while (current2 != nullptr) {
            ...
        }

    attaches any remaining nodes from list2.


    ========================================================================
    WHY CAN WE DIRECTLY ATTACH THE REMAINING LIST?
    ========================================================================

    Suppose the main loop stopped because:

        current1 == nullptr

    That means all nodes from list1 have already been merged.

    current2 still contains the remaining nodes of list2.

    Because list2 was originally sorted, its remaining nodes are
    already sorted.

    Also, the last node already placed in the merged list is smaller
    than or equal to the remaining nodes.

    Therefore, we can attach the remaining portion directly.


    ========================================================================
    DRY RUN 1 — BOTH LISTS HAVE MULTIPLE NODES
    ========================================================================

        list1:
        1 -> 3 -> 5

        list2:
        2 -> 4 -> 6


    Initial:

        current1 = 1
        current2 = 2
        head = nullptr
        tail = nullptr


    Step 1:

        1 <= 2

    Select 1.

        head = 1
        tail = 1

        current1 = 3


    Merged:

        1


    Step 2:

        3 > 2

    Select 2.

        tail->next = 2
        tail = 2

        current2 = 4


    Merged:

        1 -> 2


    Step 3:

        3 <= 4

    Select 3.

        current1 = 5

    Merged:

        1 -> 2 -> 3


    Step 4:

        5 > 4

    Select 4.

        current2 = 6

    Merged:

        1 -> 2 -> 3 -> 4


    Step 5:

        5 <= 6

    Select 5.

        current1 = nullptr

    Merged:

        1 -> 2 -> 3 -> 4 -> 5


    Main loop ends.

    Remaining:

        current2 = 6

    Attach remaining node:

        1 -> 2 -> 3 -> 4 -> 5 -> 6


    Return:

        head


    ========================================================================
    DRY RUN 2 — FIRST NODE COMES FROM LIST2
    ========================================================================

        list1:
        5 -> 7

        list2:
        1 -> 3


    Initial:

        current1 = 5
        current2 = 1
        head = nullptr
        tail = nullptr


    Compare:

        5 > 1

    Therefore, current2 is selected.

    Since:

        head == nullptr

    we set:

        head = current2
        tail = current2


    Now:

        merged:
        1


    Advance:

        current2 = 3


    Continue:

        5 > 3

    Select 3.

    Result:

        1 -> 3


    Then:

        current2 == nullptr

    The main loop ends.

    Remaining list1:

        5 -> 7

    Attach the remaining nodes:

        1 -> 3 -> 5 -> 7


    This dry run is important because it verifies that the
    first-node logic works symmetrically for both lists.


    ========================================================================
    DRY RUN 3 — ONE LIST IS EMPTY
    ========================================================================

        list1:
        nullptr

        list2:
        1 -> 2 -> 3


    First condition:

        if (list1 == nullptr)

    is true.

    Therefore:

        return list2;


    Result:

        1 -> 2 -> 3


    No merging is necessary.


    ========================================================================
    DRY RUN 4 — BOTH LISTS ARE EMPTY
    ========================================================================

        list1 = nullptr
        list2 = nullptr


    First condition:

        if (list1 == nullptr)

    is true.

    Therefore:

        return list2;

    Since list2 is also nullptr:

        return nullptr;


    Correct.


    ========================================================================
    IMPORTANT CONCEPT — WE ARE NOT CREATING A THIRD LIST
    ========================================================================

    It may feel like we are creating a third list because we have:

        head
        tail

    However, we are NOT allocating new nodes.

    We are reusing the existing nodes from list1 and list2 and
    changing their next pointers.

    For example:

        list1:
        1 -> 3

        list2:
        2 -> 4

    We rearrange the existing nodes to form:

        1 -> 2 -> 3 -> 4

    No new ListNode objects are created.

    Therefore, the solution uses O(1) auxiliary space.


    ========================================================================
    CORRECTNESS
    ========================================================================

    At every iteration:

        current1 and current2 point to the first unmerged nodes.

    Because both input lists are sorted, the smaller of those two
    nodes must be the smallest node that can be safely added next.

    We attach that node to tail and advance only the pointer from
    the list that supplied the node.

    Therefore, after every iteration:

        head -> tail

    contains a correctly sorted merged sequence.

    When one list becomes empty, all remaining nodes of the other
    list are already sorted, so they can be attached directly.

    Thus, the final linked list is sorted and contains every node
    from both input lists exactly once.


    ========================================================================
    FINAL CODE
    ========================================================================
*/

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {

        // If list1 is empty, the merged list is simply list2.
        if (list1 == nullptr) {
            return list2;
        }

        // If list2 is empty, the merged list is simply list1.
        if (list2 == nullptr) {
            return list1;
        }

        // Pointers to the current unmerged nodes.
        ListNode* current1 = list1;
        ListNode* current2 = list2;

        // head points to the first node of the merged list.
        // tail points to the last node of the merged list.
        ListNode* head = nullptr;
        ListNode* tail = nullptr;

        // Continue while both lists still have nodes to compare.
        while (current1 != nullptr && current2 != nullptr) {

            // Select the smaller node from the two lists.
            if (current1->val <= current2->val) {

                // Handle the first node of the merged list.
                if (head == nullptr) {
                    head = current1;
                    tail = current1;
                }

                // Attach current1 after the current tail.
                else {
                    tail->next = current1;
                    tail = tail->next;
                }

                // Move current1 to the next unmerged node.
                current1 = current1->next;
            }

            else {

                // Handle the first node of the merged list.
                if (head == nullptr) {
                    head = current2;
                    tail = current2;
                }

                // Attach current2 after the current tail.
                else {
                    tail->next = current2;
                    tail = tail->next;
                }

                // Move current2 to the next unmerged node.
                current2 = current2->next;
            }
        }

        // If list1 still has nodes, attach the remaining nodes.
        while (current1 != nullptr) {
            tail->next = current1;
            tail = tail->next;
            current1 = current1->next;
        }

        // If list2 still has nodes, attach the remaining nodes.
        while (current2 != nullptr) {
            tail->next = current2;
            tail = tail->next;
            current2 = current2->next;
        }

        // head always points to the first node of the merged list.
        return head;
    }
};


/*
    ========================================================================
    COMPLEXITY ANALYSIS
    ========================================================================

    Let:

        M = number of nodes in list1
        N = number of nodes in list2

    Time Complexity:

        O(M + N)

    Every node from both lists is processed at most once.

    Therefore:

        Total time = O(M + N)


    Space Complexity:

        O(1)

    We only use a constant number of pointers:

        current1
        current2
        head
        tail

    We do not create any new nodes or auxiliary data structures.


    ========================================================================
    KEY TAKEAWAYS
    ========================================================================

    1. Use two pointers to track the current unmerged node of each
       sorted linked list.

    2. Use head to permanently remember the first node of the
       merged list.

    3. Use tail to track the last node so new nodes can be attached.

    4. The first node requires special handling because there is no
       previous tail yet.

    5. After the first node:

           tail->next = selectedNode;
           tail = tail->next;

    6. Only advance the current pointer from the list whose node was
       selected.

    7. Once one list becomes empty, directly attach the remaining
       nodes from the other sorted list.

    8. We reuse existing nodes instead of creating new ones.

    9. Time complexity:

           O(M + N)

    10. Space complexity:

           O(1)


    ========================================================================
    PATTERN RECOGNITION
    ========================================================================

    This problem teaches an important linked-list pattern:

        MERGING TWO SORTED LINKED LISTS

    The key idea is:

        Compare -> Select -> Attach -> Advance

    This pattern becomes useful in more advanced problems such as:

        - Merge Sort on Linked Lists
        - Merge K Sorted Lists
        - Merging multiple sorted sequences


    ========================================================================
    REFLECTION FROM THIS PROBLEM
    ========================================================================

    This problem was particularly useful for understanding how
    linked lists are manipulated through pointers.

    The important concepts were not just the final code.

    We learned:

        head = first node
        tail = last node

    We learned that head should remain fixed while tail moves.

    We learned that linked-list traversal is done using:

        current = current->next

    rather than array-style indexing or incrementing.

    We also learned how to maintain an invariant:

        Everything from head through tail is already correctly
        sorted and merged.

    Once this invariant is maintained, every iteration becomes much
    easier to reason about.

    ========================================================================
    END
    ========================================================================
*/