
/*
===============================================================================
PROBLEM: MERGE K SORTED LISTS
PLATFORM: LeetCode
PROBLEM NUMBER: 23
DIFFICULTY: HARD
TOPIC: LINKED LISTS, HEAPS, PRIORITY QUEUE, POINTER MANIPULATION
APPROACH: MIN-HEAP WITH A CUSTOM COMPARATOR
===============================================================================

PROBLEM STATEMENT
-----------------

You are given an array/vector of k linked lists, where each linked list is
sorted in ascending order.

Merge all the linked lists into one sorted linked list and return its head.

Example:

    Input:
    lists = [
        1 -> 4 -> 5,
        1 -> 3 -> 4,
        2 -> 6
    ]

    Output:
    1 -> 1 -> 2 -> 3 -> 4 -> 4 -> 5 -> 6

The linked lists may be empty, and multiple nodes may have the same value.

The goal is to merge the lists efficiently while preserving ascending order.


===============================================================================
SECTION 1: INITIAL THINKING AND THE FIRST APPROACH
===============================================================================

Initially, I approached this problem by thinking about how to compare nodes
from different linked lists and connect them in sorted order.

The main challenge was not simply finding the smallest value. It was managing
the pointers correctly while merging several lists.

Questions that arose during the initial approach:

1. How do I identify the smallest currently available node?
2. How do I connect that node to the merged list?
3. How do I access the next node from the original list?
4. How do I prevent an existing next pointer from producing an incorrect link?
5. How do I repeat this process until every node has been processed?

One possible approach is to merge two lists at a time, then merge the result
with the next list. However, sequential merging can take O(N * k) time in a
straightforward implementation, where N is the total number of nodes and k
is the number of lists.

Instead, we chose a min-heap.

The min-heap allows us to efficiently select the smallest node among the
currently available candidates from all the lists.

IMPORTANT LESSON:

When a problem repeatedly asks us to select the smallest or largest available
element, consider whether a heap can manage those candidates efficiently.


===============================================================================
SECTION 2: WHAT IS A HEAP?
===============================================================================

A heap is a data structure that maintains a priority relationship between
elements.

A binary heap is commonly implemented using an array or vector and satisfies
the heap property.

There are two common types:

1. MIN-HEAP
   The smallest element has the highest priority and appears at the top.

2. MAX-HEAP
   The largest element has the highest priority and appears at the top.

A heap is NOT a completely sorted collection. It only maintains the ordering
needed to identify the highest-priority element efficiently.

For example, a min-heap containing the values 10, 4, 7, and 2 has 2 at the top.
The remaining values are not guaranteed to be fully sorted.


===============================================================================
SECTION 3: MIN-HEAP VS MAX-HEAP IN C++
===============================================================================

C++ provides priority_queue through the <queue> header.

A MAX-HEAP USING INTEGERS:

    priority_queue<int> maxHeap;

By default, priority_queue places the largest integer at the top.

Example:

    maxHeap.push(10);
    maxHeap.push(4);
    maxHeap.push(7);
    maxHeap.push(2);

    maxHeap.top() returns 10.

A MIN-HEAP USING INTEGERS:

    priority_queue<int, vector<int>, greater<int>> minHeap;

Here, greater<int> provides the ordering rule that places the smallest integer
at the top.

Example:

    minHeap.push(10);
    minHeap.push(4);
    minHeap.push(7);
    minHeap.push(2);

    minHeap.top() returns 2.

IMPORTANT OPERATIONS:

    push(x)  - Inserts an element. O(log n)
    top()    - Reads the top element. O(1)
    pop()    - Removes the top element. O(log n)
    empty()  - Checks whether the heap is empty. O(1)
    size()   - Returns the number of elements. O(1)

IMPORTANT DISTINCTION:

priority_queue::pop() does not return the removed element.

If the top element is needed, read top() before calling pop().

Also, pop() removes the element from the heap. It does not delete the actual
object or linked-list node pointed to by a stored pointer.


===============================================================================
SECTION 4: WHY DO WE NEED A CUSTOM COMPARATOR?
===============================================================================

In this problem, the heap must store actual linked-list node pointers:

    ListNode*

We do not want to store only integer values because we need to reconnect the
actual nodes into the final linked list.

We therefore need to tell priority_queue how to compare two ListNode pointers.

A normal comparison between pointers does not express the ordering we want.
Our priority rule must be based on the values stored inside the nodes:

    A->val
    B->val

We define a custom comparator:

    struct Compare {
        bool operator()(ListNode* A, ListNode* B) {
            return A->val > B->val;
        }
    };

WHY DOES THIS CREATE A MIN-HEAP?

For priority_queue, the comparator returns true when its first argument should
come after its second argument in the priority ordering.

Suppose:

    A->val = 7
    B->val = 2

The comparison is:

    7 > 2

This evaluates to true, meaning A should come after B in the heap's priority
ordering. The smaller-valued node B therefore has higher priority.

Now suppose:

    A->val = 1
    B->val = 3

The comparison is:

    1 > 3

This evaluates to false, which is consistent with the smaller-valued node
having higher priority.

Therefore:

    return A->val > B->val;

creates the required min-heap ordering.

IMPORTANT:

The comparator does not directly place a particular node on top. It defines
the ordering rule that priority_queue maintains during its operations.

When values are equal, neither node has priority over the other based on this
comparison. Their relative order is not guaranteed, and that is fine because
the problem does not require stable ordering between equal values.


===============================================================================
SECTION 5: OUR CUSTOM MIN-HEAP DECLARATION
===============================================================================

The declaration is:

    priority_queue<ListNode*, vector<ListNode*>, Compare> minHeap;

Breaking it down:

1. ListNode*
   The heap stores pointers to actual linked-list nodes.

2. vector<ListNode*>
   The underlying container stores those pointers.

3. Compare
   Our custom comparator orders nodes by their val fields.

4. minHeap
   The name of our priority queue.

The heap contains node pointers, not copies of the nodes.

This allows us to reconnect the original nodes directly without allocating a
new node for every value.


===============================================================================
SECTION 6: THE KEY ALGORITHM IDEA
===============================================================================

Initially, we insert only the head of each non-empty linked list into the
min-heap.

For example:

    List 1: 1 -> 4 -> 5
    List 2: 1 -> 3 -> 4
    List 3: 2 -> 6

Initially, the heap contains pointers to nodes with values:

    1, 1, 2

We do not insert every node from every list at the beginning.

WHY ONLY THE HEADS?

Each input list is already sorted in ascending order.

Therefore, its head is the smallest node that has not yet been processed
from that list.

Every later node in the same list cannot be smaller than its head.

We only need to compare the currently available candidates. Once we process
a candidate, we introduce the next node from that candidate's original list.

This maintains at most one candidate per non-empty list in the heap.

THE MAIN LOOP:

    while (!minHeap.empty())

During each iteration:

1. Read the smallest node from the heap.
2. Save its original successor.
3. Detach the selected node from its original successor.
4. Append the selected node to the merged list.
5. Remove the selected node's pointer from the heap.
6. Insert the saved successor if it exists.

Repeat until the heap becomes empty.


===============================================================================
SECTION 7: POINTER RESPONSIBILITIES
===============================================================================

Our solution uses four pointers:

1. current
   Points to the node currently selected from the min-heap.

2. iterator
   Saves the selected node's original successor before its next pointer
   is modified.

3. head
   Preserves the beginning of the merged linked list so that we can return it.

4. tail
   Points to the last node currently attached to the merged list.

Each pointer has a separate responsibility.

CURRENT:

    current = minHeap.top();

This retrieves the pointer to the smallest-valued node.

ITERATOR:

    iterator = current->next;

This preserves access to the next node in the selected node's original list.

HEAD:

    head = current;

This happens when the first node is appended to the output.

TAIL:

    tail = current;

This initially points to the first output node. Later, it advances as new
nodes are appended.

IMPORTANT LESSON:

A pointer variable and a node's next pointer are different things.

Assigning current = minHeap.top() does not change the original linked list.

Similarly, removing a pointer from the heap does not delete its node or
automatically break the node's original links.


===============================================================================
SECTION 8: THE POINTER-CONNECTION PROBLEM WE ENCOUNTERED
===============================================================================

During the dry run, we discovered an important issue.

Each selected node originally belongs to one of the input linked lists.
Its next pointer may still point to the next node in that original list.

Suppose the original list contains:

    2 -> 6

When the node containing 2 is selected, its next pointer still points to 6.

But the final sorted output may need to place another node between 2 and 6:

    2 -> 3 -> 6

If we append node 3 after node 2 without updating node 2's next pointer,
the original link from 2 to 6 can conflict with the required output order.

Therefore, we must manage the links explicitly.

OUR SOLUTION:

    current = minHeap.top();
    iterator = current->next;
    current->next = nullptr;

WHY THIS ORDER MATTERS:

First, current identifies the selected node.

Second, iterator saves the original successor.

Third, current->next is set to nullptr so the selected node is detached from
its original successor before it is appended to the merged output.

We do not lose access to the remaining nodes because iterator still points
to the saved successor.

Later, after removing the selected node from the heap, we insert iterator
back into the heap if it is not nullptr.

IMPORTANT:

Never overwrite current->next before saving the original successor if that
successor is still needed.

Otherwise, we may lose access to the remaining nodes in that list.


===============================================================================
SECTION 9: HOW WE BUILD THE MERGED LINKED LIST
===============================================================================

Initially:

    head = nullptr;
    tail = nullptr;

This means the output list is empty.

When the first minimum node is selected, tail is nullptr.

Therefore:

    tail = current;
    head = current;

Both head and tail now point to the first output node.

For every later selected node:

    tail->next = current;
    tail = tail->next;

The first statement connects the previous output tail to the new node.

The second statement advances tail to the new last node.

WHY DO WE NEED BOTH HEAD AND TAIL?

head preserves the starting point of the merged list.

tail allows us to append a node in O(1) time without traversing the output
list from its beginning.

If we only kept tail and moved it forward, we would lose the direct reference
to the first node and would not know where the final output begins.

The final answer is returned through head.


===============================================================================
SECTION 10: COMPLETE DRY RUN
===============================================================================

INPUT:

    List A: 1 -> 4 -> 5
    List B: 1 -> 3 -> 4
    List C: 2 -> 6

The initial heap contains the heads:

    [1 from A, 1 from B, 2 from C]

The order of equal-valued nodes inside the heap is not guaranteed, but the
minimum value is always available at the top.

ITERATION 1:

    Selected node: 1 from List A
    Saved successor: 4 from List A
    Detach selected node.
    Output: 1
    Insert successor 4.

    Remaining candidate values: 1, 2, 4

ITERATION 2:

    Selected node: 1 from List B
    Saved successor: 3 from List B
    Detach selected node.
    Append it to the output.
    Insert successor 3.

    Output: 1 -> 1
    Remaining candidate values: 2, 3, 4

ITERATION 3:

    Selected node: 2 from List C
    Saved successor: 6 from List C
    Detach selected node.
    Append it to the output.
    Insert successor 6.

    Output: 1 -> 1 -> 2
    Remaining candidate values: 3, 4, 6

ITERATION 4:

    Selected node: 3 from List B
    Saved successor: 4 from List B
    Detach selected node.
    Append it to the output.
    Insert successor 4.

    Output: 1 -> 1 -> 2 -> 3
    Remaining candidate values: 4, 4, 6

ITERATION 5:

    Select one of the nodes containing 4.
    Save its original successor before detaching it.
    Append it to the output.
    Insert its saved successor if it exists.

    Output: 1 -> 1 -> 2 -> 3 -> 4

    The heap still contains the other available candidates.

ITERATION 6:

    Select the other node containing 4.
    Save its original successor.
    Append it to the output.
    Insert the saved successor if it exists.

    Output: 1 -> 1 -> 2 -> 3 -> 4 -> 4

ITERATIONS 7 AND 8:

    Process the remaining nodes 5 and 6 in ascending order.

    Final output:

    1 -> 1 -> 2 -> 3 -> 4 -> 4 -> 5 -> 6 -> nullptr

The heap becomes empty after all nodes have been processed.

The precise order in which equal-valued nodes are selected can vary, but
the final output remains sorted.


===============================================================================
SECTION 11: EDGE CASES
===============================================================================

1. EMPTY VECTOR OF LISTS

   If lists is empty, the initialization loop does nothing. The heap remains
   empty, and the main loop never executes.

   head remains nullptr, which is the correct result.

2. ALL LISTS ARE EMPTY

   Every head is nullptr, so nothing is inserted into the heap.

   The function returns nullptr.

3. ONLY ONE NON-EMPTY LIST

   The heap processes that list's nodes in order and reconstructs the same
   sorted sequence.

4. DUPLICATE VALUES

   The comparator supports duplicate values. Equal-valued nodes can be
   selected in either order without breaking ascending ordering.

5. DIFFERENT LIST LENGTHS

   A list contributes its next node only when that successor exists.
   Once a list is exhausted, it contributes no more nodes.

6. SINGLE NODE

   Its successor is nullptr. The node is appended, and nothing else from that
   list is pushed into the heap.

7. ALL LISTS HAVE BEEN PROCESSED

   Once the heap becomes empty, every node has been processed and head points
   to the complete merged list.


===============================================================================
SECTION 12: TIME AND SPACE COMPLEXITY
===============================================================================

Let:

    k = number of input linked lists
    N = total number of nodes across all lists

TIME COMPLEXITY:

    O(N log k)

WHY?

The initialization inserts at most k heads. Each insertion costs O(log k).

Every one of the N nodes is subsequently removed from the heap exactly once.
Each removal costs O(log k).

Each node, except the last node of its original list, can introduce one
successor into the heap. Each such insertion also costs O(log k).

The heap contains at most one candidate from each original list, so it holds
at most k nodes.

The total cost of processing all nodes is therefore O(N log k), with
initialization costing O(k log k). For k >= 2 and N >= k, the total is
O(N log k).

For k = 1, the heap-based implementation still has the usual overhead of
heap operations; asymptotically, the single-list case is linear in N.

A precise general bound for the algorithm is:

    O(k log k + N log(k + 1))

This expresses the behavior even in small edge cases. In typical interview
analysis, the conventional bound for merging k lists using a min-heap is
O(N log k), assuming k >= 2.

AUXILIARY SPACE COMPLEXITY:

    O(k)

WHY?

The heap holds at most one candidate from each non-empty list.

The current, iterator, head, and tail pointers require only O(1) additional
space.

We reuse the existing nodes rather than allocating a new node for every
output value.

Therefore, the additional working space is O(k), excluding the input lists
and the linked-list nodes themselves.

The final merged list reuses the original nodes, so no separate O(N) output
allocation is required.


===============================================================================
SECTION 13: WHY THIS IS A STRONG INTERVIEW SOLUTION
===============================================================================

This solution demonstrates several important skills:

1. Selecting a data structure based on the repeated operation required by
   the problem.

2. Using a priority queue to efficiently select the smallest available node.

3. Defining a custom comparator for user-defined objects.

4. Understanding the distinction between node pointers and node values.

5. Preserving a node's original successor before modifying its links.

6. Maintaining head and tail pointers while building a linked list.

7. Handling empty lists, duplicate values, and lists of different lengths.

8. Explaining complexity based on the total number of nodes and the number
   of lists.

A divide-and-conquer approach can also solve this problem in O(N log k) time.
The heap approach is not the only optimal method, but it is an excellent
demonstration of how a priority queue can simplify a multi-list merge.


===============================================================================
SECTION 14: LESSONS LEARNED DURING THIS SESSION
===============================================================================

LESSON 1: DO NOT MEMORIZE THE COMPARATOR.

Understand what the comparator tells priority_queue.

For this min-heap:

    return A->val > B->val;

The larger-valued node is ordered behind the smaller-valued node.

LESSON 2: A HEAP DOES NOT FULLY SORT ALL ELEMENTS.

It efficiently exposes the current minimum. We still need to repeat the
process and insert new candidates as the algorithm progresses.

LESSON 3: STORE NODE POINTERS WHEN THE NODES THEMSELVES ARE NEEDED.

Storing only integer values would lose the direct references needed to
reconnect the original linked-list nodes.

LESSON 4: PRESERVE THE SUCCESSOR BEFORE MODIFYING A LINK.

The line:

    iterator = current->next;

must occur before:

    current->next = nullptr;

Otherwise, detaching current could make the original successor inaccessible
through current.

LESSON 5: CURRENT AND TAIL HAVE DIFFERENT RESPONSIBILITIES.

current represents the node selected by the heap.

tail represents the last node of the output list.

They should not be treated as interchangeable pointers.

LESSON 6: HEAD MUST REMAIN AVAILABLE.

tail moves throughout the algorithm. head must preserve the beginning of the
final list so it can be returned.

LESSON 7: DRY RUNS SHOULD TRACK LINKS, NOT JUST VALUES.

It is not enough to write the heap values after each operation. We must also
check which nodes the pointers refer to and where each next pointer leads.

LESSON 8: LEARN BY BUILDING.

This problem was my first substantial use of a heap in C++. I learned the
priority_queue syntax, custom comparison, pointer storage, and heap processing
while developing the solution instead of copying a complete implementation.


===============================================================================
SECTION 15: FINAL ALGORITHM SUMMARY
===============================================================================

1. Create a min-heap that stores ListNode pointers and orders them by val.

2. Insert the head of every non-empty input list.

3. Initialize head and tail to nullptr.

4. While the heap is not empty:

   a. Retrieve the smallest node into current.

   b. Save current->next in iterator.

   c. Detach current from its original successor.

   d. If the output is empty, initialize head and tail to current.

   e. Otherwise, connect tail->next to current and advance tail.

   f. Remove the selected node from the heap.

   g. If iterator is not nullptr, insert it into the heap.

5. Return head.

FINAL RESULT:

    A single sorted linked list containing every node from all input lists.

FINAL COMPLEXITY:

    Time: O(N log k) under the conventional k >= 2 analysis.
    Auxiliary space: O(k).

PROBLEM STATUS:

    SOLVED AND ACCEPTED ON LEETCODE.

===============================================================================
END OF LEARNING DOCUMENT
===============================================================================
*/

#include <queue>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;

    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    struct Compare {
        bool operator()(ListNode* A, ListNode* B) {
            return A->val > B->val;
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, Compare> minHeap;

        ListNode* current = nullptr;
        ListNode* head = nullptr;
        ListNode* tail = nullptr;
        ListNode* iterator = nullptr;

        int n = lists.size();

        for (int i = 0; i < n; i++) {
            if (lists[i] != nullptr) {
                minHeap.push(lists[i]);
            }
        }

        while (!minHeap.empty()) {
            current = minHeap.top();
            iterator = current->next;
            current->next = nullptr;

            if (tail == nullptr) {
                tail = current;
                head = current;
            } else {
                tail->next = current;
                tail = tail->next;
            }

            minHeap.pop();

            if (iterator != nullptr) {
                minHeap.push(iterator);
            }
        }

        return head;
    }
};
