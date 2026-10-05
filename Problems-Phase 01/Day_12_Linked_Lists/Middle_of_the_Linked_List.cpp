/*
===============================================================================
Problem: Middle of the Linked List
Platform: LeetCode
Problem Number: 876
Topic: Singly Linked List
Difficulty: Easy

===============================================================================
PROBLEM STATEMENT
===============================================================================

Given the head of a singly linked list, return the middle node of the linked
list.

If there are two middle nodes, return the SECOND middle node.

Example 1:

    Input:
        1 -> 2 -> 3 -> 4 -> 5 -> nullptr

    Output:
        3 -> 4 -> 5 -> nullptr

Example 2:

    Input:
        1 -> 2 -> 3 -> 4 -> 5 -> 6 -> nullptr

    Output:
        4 -> 5 -> 6 -> nullptr

Important:
    For an even number of nodes, the problem requires the SECOND middle node.

===============================================================================
1. INITIAL OBSERVATION
===============================================================================

The first thing to understand is what the problem means by "middle".

For an odd number of nodes:

    1 -> 2 -> 3 -> 4 -> 5

The middle node is:

    3

For an even number of nodes:

    1 -> 2 -> 3 -> 4 -> 5 -> 6

There are two middle nodes:

    3 and 4

LeetCode asks us to return the SECOND middle node:

    4

Therefore, our solution must correctly handle both odd and even lengths.

===============================================================================
2. EDGE CASE: ONE NODE
===============================================================================

According to the problem constraints, the linked list contains at least
one node.

Therefore, an empty linked list is not a valid input.

If the list contains only one node:

    1 -> nullptr

that node is automatically the middle.

We can handle this with:

    if (head->next == nullptr) {
        return head;
    }

There is no need to traverse the list in this case.

===============================================================================
3. BASIC APPROACH
===============================================================================

The approach used in this solution is:

    Step 1:
        Count the total number of nodes.

    Step 2:
        Calculate the middle index using:

            mid = count / 2;

    Step 3:
        Move head forward 'mid' positions.

    Step 4:
        Return head.

This approach uses TWO traversals:

    First traversal:
        Count the number of nodes.

    Second traversal:
        Move to the middle node.

===============================================================================
4. WHY count / 2 WORKS
===============================================================================

Consider an odd-length list:

    1 -> 2 -> 3 -> 4 -> 5

Number of nodes:

    count = 5

Integer division:

    5 / 2 = 2

Using zero-based indexing:

    index:    0   1   2   3   4
    value:    1   2   3   4   5
                      ^
                    middle

Index 2 contains:

    3

Therefore:

    mid = 2

Moving head forward 2 positions gives:

    3 -> 4 -> 5 -> nullptr

which is the correct answer.

-------------------------------------------------------------------------------

Now consider an even-length list:

    1 -> 2 -> 3 -> 4 -> 5 -> 6

Number of nodes:

    count = 6

Integer division:

    6 / 2 = 3

Using zero-based indexing:

    index:    0   1   2   3   4   5
    value:    1   2   3   4   5   6
                          ^
                        index 3

Index 3 contains:

    4

Therefore:

    mid = 3

Moving head forward 3 positions gives:

    4 -> 5 -> 6 -> nullptr

which is exactly what the problem requires.

===============================================================================
5. IMPORTANT DEBUGGING LESSON: count = 1 VS count = 0
===============================================================================

During the first attempt, there was an important mistake.

The initial idea was:

    int count = 1;

The reason was:

    current initially points to head,
    so the first node is already present.

However, the traversal loop was:

    while (current != nullptr) {
        current = current->next;
        count++;
    }

This means the first node is ALSO counted by the loop.

Example:

    1 -> 2 -> 3 -> nullptr

Initially:

    current -> 1
    count = 1

First iteration:

    current != nullptr

The loop executes:

    current = current->next;
    count++;

Now:

    count = 2

But only one node has been processed.

The loop will eventually produce:

    count = 4

instead of:

    count = 3

Therefore:

    int count = 1;

was incorrect for this particular loop structure.

The correct initialization is:

    int count = 0;

Then the loop counts every node exactly once.

===============================================================================
6. WHY count = 0 IS CORRECT
===============================================================================

Consider:

    1 -> 2 -> 3 -> nullptr

Initial state:

    count = 0
    current -> 1

Iteration 1:

    current = 1

    count++;

    count = 1

Move:

    current = current->next

Now:

    current -> 2

Iteration 2:

    count = 2

Move:

    current -> 3

Iteration 3:

    count = 3

Move:

    current -> nullptr

Loop stops.

Final:

    count = 3

This is exactly the number of nodes in the linked list.

===============================================================================
7. WHY WE USE current FOR COUNTING
===============================================================================

We create:

    ListNode* current = head;

because we want to traverse the list without changing head.

Initially:

    head
     |
     v
    1 -> 2 -> 3 -> 4 -> 5 -> nullptr

    current
       |
       v
       1

During traversal:

    current -> 2
    current -> 3
    current -> 4
    current -> 5
    current -> nullptr

Meanwhile:

    head

still points to the first node.

This is important because after counting the nodes, we still need head to
start from the beginning so that we can move it to the middle.

===============================================================================
8. FIRST TRAVERSAL: COUNT THE NODES
===============================================================================

The first traversal is:

    ListNode* current = head;

    while (current != nullptr) {
        current = current->next;
        count++;
    }

Its only job is to determine the total number of nodes.

After this traversal:

    current == nullptr

but:

    head

still points to the first node.

===============================================================================
9. CALCULATING THE MIDDLE
===============================================================================

After counting:

    mid = count / 2;

Integer division is being used.

Examples:

    1 / 2 = 0
    2 / 2 = 1
    3 / 2 = 1
    4 / 2 = 2
    5 / 2 = 2
    6 / 2 = 3

For this problem, these results are exactly what we need because an even
length requires the SECOND middle node.

===============================================================================
10. SECOND TRAVERSAL: MOVE HEAD TO THE MIDDLE
===============================================================================

We create:

    int iterator = 0;

Then:

    while (iterator < mid) {
        head = head->next;
        iterator++;
    }

This moves head forward exactly 'mid' positions.

Example:

    1 -> 2 -> 3 -> 4 -> 5

count = 5

mid = 2

Initially:

    iterator = 0
    head -> 1

First iteration:

    iterator < 2

Move:

    head = head->next

Now:

    head -> 2

    iterator = 1

Second iteration:

    iterator < 2

Move:

    head = head->next

Now:

    head -> 3

    iterator = 2

Loop stops.

Therefore:

    head -> 3

and the returned list is:

    3 -> 4 -> 5 -> nullptr

===============================================================================
11. COMPLETE DRY RUN: ODD NUMBER OF NODES
===============================================================================

Input:

    1 -> 2 -> 3 -> 4 -> 5 -> nullptr

Initial:

    count = 0
    current = head

--------------------------------------------------
Traversal
--------------------------------------------------

current -> 1

count = 1

current -> 2

count = 2

current -> 3

count = 3

current -> 4

count = 4

current -> 5

count = 5

current -> nullptr

Loop stops.

Therefore:

    count = 5

--------------------------------------------------
Calculate middle
--------------------------------------------------

    mid = count / 2

    mid = 5 / 2

    mid = 2

--------------------------------------------------
Move head
--------------------------------------------------

Initial:

    head -> 1

iterator = 0

Move 1:

    head -> 2

iterator = 1

Move 2:

    head -> 3

iterator = 2

Loop stops.

Final:

    head -> 3 -> 4 -> 5 -> nullptr

Return:

    head

Answer:

    3 -> 4 -> 5 -> nullptr

===============================================================================
12. COMPLETE DRY RUN: EVEN NUMBER OF NODES
===============================================================================

Input:

    1 -> 2 -> 3 -> 4 -> 5 -> 6 -> nullptr

Initial:

    count = 0

After complete traversal:

    count = 6

--------------------------------------------------
Calculate middle
--------------------------------------------------

    mid = 6 / 2

    mid = 3

--------------------------------------------------
Move head
--------------------------------------------------

Initially:

    head -> 1

iterator = 0

Move 1:

    head -> 2

iterator = 1

Move 2:

    head -> 3

iterator = 2

Move 3:

    head -> 4

iterator = 3

Loop stops.

Final:

    head -> 4 -> 5 -> 6 -> nullptr

Return:

    head

Answer:

    4 -> 5 -> 6 -> nullptr

This is the SECOND middle node, exactly as required.

===============================================================================
13. EDGE CASES
===============================================================================

Edge Case 1: One Node
----------------------

Input:

    1 -> nullptr

Condition:

    head->next == nullptr

Therefore:

    return head;

Answer:

    1

-------------------------------------------------------------------------------

Edge Case 2: Two Nodes
-----------------------

Input:

    1 -> 2 -> nullptr

count = 2

mid = 2 / 2 = 1

Move head one position:

    head -> 2

Answer:

    2

This is the SECOND middle node.

-------------------------------------------------------------------------------

Edge Case 3: Three Nodes
-------------------------

Input:

    1 -> 2 -> 3 -> nullptr

count = 3

mid = 3 / 2 = 1

Move head one position:

    head -> 2

Answer:

    2

-------------------------------------------------------------------------------

Edge Case 4: Large List
------------------------

The algorithm still works for a large linked list because it only requires:

    1. One traversal to count.
    2. One traversal to reach the middle.

No additional data structure proportional to the list size is created.

===============================================================================
14. COMMON MISTAKES
===============================================================================

Mistake 1:
    Initializing count incorrectly.

Incorrect for our traversal:

    int count = 1;

Correct:

    int count = 0;

because the first node is already processed by the loop.

-------------------------------------------------------------------------------

Mistake 2:
    Forgetting that integer division is being used.

For example:

    5 / 2 = 2

not:

    2.5

because count and mid are integers.

-------------------------------------------------------------------------------

Mistake 3:
    Returning the node before the required middle.

For an even list:

    1 -> 2 -> 3 -> 4 -> 5 -> 6

There are two middle nodes:

    3 and 4

The problem wants:

    4

Therefore:

    mid = count / 2

gives:

    3

which correctly reaches node 4 using zero-based indexing.

-------------------------------------------------------------------------------

Mistake 4:
    Losing the original head unnecessarily.

We use:

    current = head;

for counting.

Then we use head again to reach the middle.

This allows us to keep the traversal logic simple.

===============================================================================
15. TIME COMPLEXITY
===============================================================================

There are two main traversals.

First traversal:

    Count all nodes.

Time:

    O(n)

Second traversal:

    Move head to the middle.

In the worst case, this moves approximately n/2 nodes.

Therefore:

    O(n/2)

But constants are ignored in Big-O notation:

    O(n/2) = O(n)

Total:

    O(n) + O(n)
    = O(n)

Therefore:

    TIME COMPLEXITY = O(n)

===============================================================================
16. SPACE COMPLEXITY
===============================================================================

We only use a constant number of variables:

    count
    mid
    iterator
    current

We do not create:

    another linked list
    array
    vector
    hash map
    recursion stack proportional to n

Therefore:

    AUXILIARY SPACE = O(1)

===============================================================================
17. WHY THIS IS O(n), NOT O(2n)
===============================================================================

We technically perform two traversals.

Someone might say:

    O(n) + O(n) = O(2n)

That is true mathematically.

But Big-O ignores constant factors.

Therefore:

    O(2n) = O(n)

Similarly:

    O(n) + O(n/2) = O(n)

So the final complexity is:

    Time: O(n)
    Space: O(1)

===============================================================================
18. FINAL SOLUTION
===============================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
LeetCode provides ListNode automatically.

The structure is:

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
*/

class Solution {
public:

    ListNode* middleNode(ListNode* head) {

        /*
        Edge Case:
        If there is only one node, that node is automatically the middle.
        */
        if (head->next == nullptr) {
            return head;
        }

        /*
        count:
            Stores the total number of nodes.

        mid:
            Stores the middle index.

        iterator:
            Used while moving head toward the middle.

        current:
            Used to traverse the linked list while counting nodes.
        */
        int count = 0;
        int mid = 0;
        int iterator = 0;

        ListNode* current = head;

        /*
        First traversal:
        Count the total number of nodes.
        */
        while (current != nullptr) {

            current = current->next;
            count++;
        }

        /*
        Calculate the middle index.

        Examples:

            count = 5
            mid = 2

            count = 6
            mid = 3

        For an even-sized list, this gives the SECOND middle node.
        */
        mid = count / 2;

        /*
        Second traversal:
        Move head forward 'mid' positions.
        */
        while (iterator < mid) {

            head = head->next;
            iterator++;
        }

        /*
        head now points to the required middle node.
        */
        return head;
    }
};

/*
===============================================================================
19. FINAL ALGORITHM SUMMARY
===============================================================================

1. Handle the one-node case.

2. Create a traversal pointer:

       current = head

3. Traverse the entire linked list and count the nodes.

4. Calculate:

       mid = count / 2

5. Create an iterator starting at 0.

6. Move head forward until:

       iterator == mid

7. Return head.

===============================================================================
20. FINAL MENTAL MODEL
===============================================================================

Think of the algorithm as:

        FIRST PASS
        ----------
        Count nodes

             |
             v

        Calculate middle

             |
             v

        SECOND PASS
        -----------
        Move head to middle

             |
             v

        Return head


For:

    1 -> 2 -> 3 -> 4 -> 5

count = 5
mid = 2

Answer:

    3 -> 4 -> 5


For:

    1 -> 2 -> 3 -> 4 -> 5 -> 6

count = 6
mid = 3

Answer:

    4 -> 5 -> 6

===============================================================================
21. KEY LESSONS LEARNED FROM THIS PROBLEM
===============================================================================

Lesson 1:
    Understand how the traversal loop counts nodes.

    If:

        current = head
        count = 0

    then the first iteration counts the first node.

-------------------------------------------------------------------------------

Lesson 2:
    Always trace pointer movement when debugging.

    Drawing:

        head
         |
         v
        1 -> 2 -> 3 -> ...

    and physically moving the pointer can reveal mistakes that are not
    obvious from the code alone.

-------------------------------------------------------------------------------

Lesson 3:
    Divide the problem into smaller operations.

    Instead of trying to find the middle immediately:

        1. Count nodes.
        2. Calculate middle.
        3. Move to middle.

-------------------------------------------------------------------------------

Lesson 4:
    Integer division can be useful.

        5 / 2 = 2
        6 / 2 = 3

    These values naturally give us the correct zero-based index for this
    problem.

-------------------------------------------------------------------------------

Lesson 5:
    Multiple traversals do not necessarily mean inefficient complexity.

    Two linear traversals are still:

        O(n)

-------------------------------------------------------------------------------

Lesson 6:
    Returning a node means returning the pointer to that node.

    If:

        head -> 3 -> 4 -> 5 -> nullptr

    then returning head returns the node containing 3 and its remaining
    linked-list portion.

===============================================================================
22. ALTERNATIVE APPROACH
===============================================================================

There is a more efficient-looking one-pass approach using two pointers,
commonly known as the slow-and-fast pointer technique.

However, this solution intentionally does NOT use that technique.

Reason:

This implementation was developed by first understanding the linked list
fundamentals and solving the problem independently using:

    Count -> Calculate middle -> Traverse to middle

Learning and implementing the basic approach first makes it easier to
understand the one-pass pointer technique later.

===============================================================================
23. GITHUB INFORMATION
===============================================================================

Suggested filename:

    Middle_of_the_Linked_List.cpp

Suggested commit message:

    Solve Middle of the Linked List using traversal

Suggested GitHub description:

    Solved LeetCode 876 using a two-pass linked-list traversal approach.
    The solution first counts the nodes, calculates the middle index using
    integer division, and then moves the head pointer to the required middle
    node. Handles both odd and even-sized linked lists and returns the second
    middle node when the list length is even.

Complexity:

    Time:  O(n)
    Space: O(1)

===============================================================================
END
===============================================================================
*/