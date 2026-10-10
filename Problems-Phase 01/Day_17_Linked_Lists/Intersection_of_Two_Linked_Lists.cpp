
/*
===============================================================================
PROBLEM: INTERSECTION OF TWO LINKED LISTS
PLATFORM: LeetCode
PROBLEM NUMBER: 160
DIFFICULTY: EASY
TOPIC: SINGLY LINKED LIST
APPROACH: LENGTH COUNTING AND POINTER ALIGNMENT
STATUS: ACCEPTED
===============================================================================

1. PROBLEM STATEMENT
--------------------

Given the heads of two singly linked lists, headA and headB, return the node
at which the two linked lists intersect.

If the two linked lists do not intersect, return nullptr.

IMPORTANT:
- The lists may have different lengths.
- Either list may be empty.
- The lists may intersect or may have no intersection.
- An intersection means both lists share the SAME NODE in memory.
- Two different nodes containing the same value do NOT constitute an
  intersection.
- The original linked lists must not be modified.
- The returned node must be the actual shared node, not a newly created node.

The problem asks us to find the first shared node, if one exists.


===============================================================================
2. UNDERSTANDING WHAT INTERSECTION MEANS
===============================================================================

Consider two linked lists:

List A:
    4 -> 1 -> 8 -> 4 -> 5

List B:
    5 -> 6 -> 1 -> 8 -> 4 -> 5

If both lists share the exact same node containing 8, they intersect at that
node.

Conceptually:

    List A:  4 -> 1 --+
                     |
                     v
                     8 -> 4 -> 5 -> nullptr
                     ^
                     |
    List B:  5 -> 6 -> 1 --+

The important point is that after the intersection, both lists follow the
same next-pointer chain.

The prefix nodes before the intersection can be different, but the shared
suffix consists of the same node objects.

If both lists contain a node with value 7, that alone does not mean they
intersect. The nodes could occupy different memory addresses.


===============================================================================
3. WHY NODE IDENTITY MATTERS
===============================================================================

Suppose:

    List A contains a node with value 7 at address 0x100.
    List B contains another node with value 7 at address 0x500.

These are different nodes even though their values are equal.

Comparison by value:

    nodeA->val == nodeB->val

This checks whether their stored values are equal.

Comparison by pointer:

    nodeA == nodeB

This checks whether both pointers refer to the exact same node.

For this problem, we must compare node pointers, not node values.

The correct intersection test is:

    if (t1 == t2)

NOT:

    if (t1->val == t2->val)


===============================================================================
4. INITIAL BRUTE-FORCE IDEA
===============================================================================

The initial idea was to take every node in List A and compare it with every
node in List B.

For every node in List A:
    Traverse List B.
    If both pointers refer to the same node, return that node.

This approach is logically correct, but inefficient.

If List A has M nodes and List B has N nodes, the worst-case time complexity
is:

    O(M * N)

The goal was to find a more efficient approach without using additional
collections such as arrays, vectors, or hash maps.

The final solution uses the lengths of both lists to align their pointers.


===============================================================================
5. CORE IDEA: LENGTH ALIGNMENT
===============================================================================

Let:

    M = number of nodes in List A
    N = number of nodes in List B

If the lists have different lengths, their head pointers are not equally
far from the end of their respective lists.

For example:

    List A:  A1 -> A2 -> A3 -> C1 -> C2 -> nullptr
    List B:  B1 -> C1 -> C2 -> nullptr

List A has five nodes.
List B has three nodes.

The length difference is:

    diff = 5 - 3 = 2

If we advance the pointer in List A by two nodes:

    t1 starts at A3
    t2 starts at B1

Both pointers now have the same number of nodes remaining.

This is the essential insight:

    Advance the pointer of the longer list by the difference in lengths.

After alignment, move both pointers forward together.

If an intersection exists, both pointers will reach the shared node at the
same time.

If no intersection exists, both pointers will eventually reach nullptr.


===============================================================================
6. VARIABLES AND POINTERS USED
===============================================================================

current1:
    Traverses List A while counting its nodes.

current2:
    Traverses List B while counting its nodes.

count1:
    Stores the length of List A.

count2:
    Stores the length of List B.

diff:
    Stores the absolute difference between the two list lengths.

t1:
    Starts at headA and is advanced when List A is longer.

t2:
    Starts at headB and is advanced when List B is longer.

iterator:
    Counts how many steps have been taken while aligning the pointers.


===============================================================================
7. STEP 1: COUNT THE LENGTH OF LIST A
===============================================================================

Initially:

    current1 = headA
    count1 = 0

While current1 is not nullptr:

    Increment count1.
    Move current1 to current1->next.

When current1 becomes nullptr, count1 contains the number of nodes in List A.

The counting operation takes:

    O(M) time


===============================================================================
8. STEP 2: COUNT THE LENGTH OF LIST B
===============================================================================

Similarly:

    current2 = headB
    count2 = 0

While current2 is not nullptr:

    Increment count2.
    Move current2 to current2->next.

When current2 becomes nullptr, count2 contains the number of nodes in List B.

The counting operation takes:

    O(N) time

IMPORTANT:
After counting, current1 and current2 both point to nullptr.

We therefore initialize new traversal pointers from headA and headB before
starting the alignment process.


===============================================================================
9. STEP 3: CALCULATE THE LENGTH DIFFERENCE
===============================================================================

The implementation calculates:

    diff = max(count1, count2) - min(count1, count2)

This gives the non-negative difference between the lengths.

Examples:

    count1 = 5, count2 = 3
    diff = 5 - 3 = 2

    count1 = 3, count2 = 5
    diff = 5 - 3 = 2

    count1 = 4, count2 = 4
    diff = 4 - 4 = 0

The difference tells us how many nodes the pointer in the longer list must
skip before both pointers can traverse equal-length remaining portions.


===============================================================================
10. STEP 4: ALIGN THE POINTERS
===============================================================================

Initialize:

    t1 = headA
    t2 = headB
    iterator = 0

CASE A: List A is longer.

If:

    count1 > count2

Advance t1 by diff nodes.

CASE B: List B is longer.

If:

    count1 < count2

Advance t2 by diff nodes.

CASE C: Both lists have equal lengths.

If:

    count1 == count2

Neither pointer needs to move during alignment.

The diff is zero, so the alignment loops are skipped.

After this stage, both pointers have the same number of nodes remaining.


===============================================================================
11. STEP 5: FIND THE INTERSECTION
===============================================================================

Once the pointers are aligned, traverse both lists simultaneously.

At each step:

    1. Compare t1 and t2.
    2. If t1 == t2, return t1.
    3. Otherwise, advance both pointers by one node.

The loop condition in the submitted implementation is:

    while (t1 != nullptr)

Because the lists have been aligned, the two pointers have equal numbers of
nodes remaining. Therefore, if there is no intersection, they reach nullptr
together.

If no shared node is found, return nullptr.

This approach correctly handles both intersecting and non-intersecting lists.


===============================================================================
12. STEP-BY-STEP DRY RUN: INTERSECTION EXISTS
===============================================================================

Consider:

    List A:
    4 -> 1 -> 8 -> 4 -> 5 -> nullptr

    List B:
    5 -> 6 -> 1 -> 8 -> 4 -> 5 -> nullptr

Assume both lists share the same node containing 8.

For this example:

    count1 = 5
    count2 = 6

Length difference:

    diff = 6 - 5 = 1

List B is longer, so advance t2 by one node.

After alignment:

    t1 points to the first node of List A.
    t2 points to the second node of List B.

Both pointers now have five nodes remaining.

SIMULTANEOUS TRAVERSAL
----------------------

Comparison 1:
    t1 points to value 4.
    t2 points to value 6.
    Different node addresses.

Comparison 2:
    t1 points to value 1.
    t2 points to value 1.
    Equal values do not prove intersection.
    The pointers must still be compared directly.

Comparison 3:
    The pointers continue advancing together.

When both pointers reach the actual shared node containing 8:

    t1 == t2

The function returns that shared node.

IMPORTANT:
The numerical values in this illustrative list are not sufficient to
determine intersection. The example assumes that the suffix beginning at 8
is shared by both lists.


===============================================================================
13. STEP-BY-STEP DRY RUN: NO INTERSECTION
===============================================================================

Consider two completely separate lists:

    List A:
    1 -> 2 -> 3 -> nullptr

    List B:
    4 -> 5 -> nullptr

Lengths:

    count1 = 3
    count2 = 2

Difference:

    diff = 1

List A is longer, so advance t1 by one node.

Now:

    t1 points to node 2.
    t2 points to node 4.

Move both pointers together:

    t1: node 2 -> node 3 -> nullptr
    t2: node 4 -> node 5 -> nullptr

No pair of pointers identifies the same node.

Both eventually become nullptr.

The loop terminates, and the function returns:

    nullptr


===============================================================================
14. EQUAL-LENGTH LISTS
===============================================================================

Equal-length lists are a valid case.

For example:

    List A: 1 -> 2 -> 3 -> nullptr
    List B: 4 -> 5 -> 6 -> nullptr

Here:

    count1 = 3
    count2 = 3
    diff = 0

Neither pointer is advanced during alignment.

The simultaneous traversal checks the node addresses.

If the lists do not share any nodes, the function returns nullptr.

If the lists share a suffix, the pointers eventually reach the same node and
return it.

Equal lengths do NOT automatically imply that the lists intersect.


===============================================================================
15. PROBLEMS ENCOUNTERED DURING REASONING
===============================================================================

A. BRUTE-FORCE COMPLEXITY

The first idea was to compare each node of one list with every node of the
other list.

This would work, but it has O(M * N) worst-case time complexity.

The improvement was to count both list lengths and align the pointers.

B. REMEMBERING TO RESET THE POINTERS

The pointers used to count the lengths finish at nullptr.

We must create fresh pointers:

    t1 = headA
    t2 = headB

Otherwise, the alignment stage would not begin at the list heads.

C. HANDLING EQUAL LENGTHS

It is not necessary to add a special alignment operation for equal lengths.

Both comparisons:

    count1 > count2
    count1 < count2

are false when the lengths are equal.

Therefore, neither pointer advances during alignment.

D. COMPARING VALUES INSTEAD OF POINTERS

Nodes can have identical values but different memory addresses.

The correct condition is:

    t1 == t2

E. REMEMBERING TO ADVANCE BOTH POINTERS

If the pointers are different, both must move forward by one node.

Otherwise, the traversal may become stuck or compare incorrect positions.

F. RETURNING nullptr WHEN NO INTERSECTION EXISTS

If no shared node is found, the function must return nullptr.

This handles the case where the lists are entirely separate.


===============================================================================
16. DEBUGGING AND VALIDATION CHECKLIST
===============================================================================

Before considering a solution complete, test the following cases:

[1] Both lists have the same length and intersect.

[2] Both lists have the same length but do not intersect.

[3] List A is longer than List B.

[4] List B is longer than List A.

[5] The intersection occurs at the first node of both lists.

[6] The intersection occurs near the end of the lists.

[7] The lists do not intersect.

[8] One list is empty.

[9] Both lists are empty.

[10] Both lists contain equal values but share no actual nodes.

[11] The lists share a suffix containing several nodes.

The implementation must compare node identity and must not modify the original
lists.


===============================================================================
17. TIME COMPLEXITY
===============================================================================

Let:

    M = number of nodes in List A
    N = number of nodes in List B

Length counting:

    O(M) + O(N)

Pointer alignment:

    O(|M - N|)

Simultaneous traversal:

    O(min(M, N)) in the worst case

Total time:

    O(M + N)

The algorithm traverses each list a constant number of times, so the time
complexity is linear in the combined input size.


===============================================================================
18. AUXILIARY SPACE COMPLEXITY
===============================================================================

The algorithm uses a fixed number of variables:

    current1
    current2
    count1
    count2
    diff
    t1
    t2
    iterator

No extra linked list, array, vector, or hash map is created.

Therefore:

    Auxiliary space complexity = O(1)

The input lists are not counted as additional space because they already
exist before the function is called.


===============================================================================
19. ALTERNATIVE APPROACHES
===============================================================================

The accepted solution uses length counting and pointer alignment.

Another common approach is the two-pointer switching-heads technique.

In that approach, two pointers traverse the lists and switch to the opposite
list's head when they reach the end.

It also achieves:

    Time complexity: O(M + N)
    Auxiliary space: O(1)

The switching-heads approach avoids explicitly counting the list lengths.

The length-alignment approach used here is still efficient, correct, and
interview-appropriate.


===============================================================================
20. INTERVIEW TAKEAWAYS
===============================================================================

When explaining this solution in an interview:

1. Define intersection as sharing the exact same node object.
2. Explain why matching values are insufficient.
3. Explain why the brute-force approach is inefficient.
4. Explain how counting lengths reveals the difference in remaining nodes.
5. Explain why advancing the longer list aligns both pointers.
6. Explain why simultaneous traversal finds the first shared node.
7. Explain why nullptr is returned when no intersection exists.
8. State O(M + N) time and O(1) auxiliary space.
9. Mention equal-length and non-intersecting edge cases.
10. Confirm that the original lists remain unchanged.


===============================================================================
21. FINAL SUMMARY
===============================================================================

The solution works in three main phases:

PHASE 1:
    Count the lengths of both linked lists.

PHASE 2:
    Calculate their length difference and advance the pointer of the longer
    list by that difference.

PHASE 3:
    Move both pointers together, comparing their addresses at every step.

If the pointers become equal, return the shared node.

If both pointers reach nullptr without finding a shared node, return nullptr.

The central insight is that pointer alignment gives both pointers the same
number of nodes remaining. This ensures that they encounter a shared node at
the same time, if one exists.

Time complexity:
    O(M + N)

Auxiliary space complexity:
    O(1)

===============================================================================
END OF NOTES
===============================================================================
*/

#include <algorithm>

class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        ListNode* current1 = headA;
        ListNode* current2 = headB;

        int count1 = 0;
        int count2 = 0;

        // Phase 1: Count the nodes in List A.
        while (current1 != nullptr) {
            count1++;
            current1 = current1->next;
        }

        // Count the nodes in List B.
        while (current2 != nullptr) {
            count2++;
            current2 = current2->next;
        }

        // Phase 2: Calculate the absolute difference in lengths.
        int diff = std::max(count1, count2) - std::min(count1, count2);

        // Reset pointers to the heads of the original lists.
        ListNode* t1 = headA;
        ListNode* t2 = headB;

        int iterator = 0;

        // If List A is longer, advance its pointer.
        if (count1 > count2) {
            while (iterator < diff) {
                iterator++;
                t1 = t1->next;
            }
        }

        // If List B is longer, advance its pointer.
        if (count1 < count2) {
            while (iterator < diff) {
                iterator++;
                t2 = t2->next;
            }
        }

        // Phase 3: Traverse both aligned lists together.
        while (t1 != nullptr) {
            // Compare node identity, not node values.
            if (t1 == t2) {
                return t1;
            }

            t1 = t1->next;
            t2 = t2->next;
        }

        // No shared node was found.
        return nullptr;
    }
};
 