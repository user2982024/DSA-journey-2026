/*
================================================================================
DSA JOURNEY — LINKED LISTS
Problem: Partition List
Platform: LeetCode
Problem Number: 86
Topic: Linked List / Pointer Manipulation / Partitioning
Difficulty: Medium
================================================================================

PROBLEM STATEMENT
================================================================================

Given the head of a linked list and an integer x, partition the list so that
all nodes with values LESS THAN x come before all nodes with values GREATER
THAN OR EQUAL TO x.

The relative order of nodes within each partition must be preserved.

Example:

Input:
    1 -> 4 -> 3 -> 2 -> 5 -> 2 -> NULL
    x = 3

Output:
    1 -> 2 -> 2 -> 4 -> 3 -> 5 -> NULL

Important:

    First partition:
        values < x

    Second partition:
        values >= x

The problem is NOT:
    values <= x followed by values > x.

The equality case belongs to the second partition.


================================================================================
INITIAL UNDERSTANDING
================================================================================

For:

    1 -> 4 -> 3 -> 2 -> 5 -> 2
    x = 3

Separate the nodes into two groups while preserving their relative order.

First group: values < 3

    1 -> 2 -> 2

Second group: values >= 3

    4 -> 3 -> 5

Then connect them:

    1 -> 2 -> 2 -> 4 -> 3 -> 5 -> NULL


================================================================================
FIRST IDEA — TWO PASS APPROACH
================================================================================

The first idea was to traverse the original list more than once.

Conceptually:

    Pass 1:
        Find/build the nodes whose values are < x.

    Pass 2:
        Find/build the nodes whose values are >= x.

Then connect the two resulting lists.

This approach can work, but it introduces unnecessary complexity because
the same original list has to be traversed multiple times.

The key realization was:

    Every node only needs to be inspected once.

When we are looking at a node, we already know which partition it belongs to:

    if current->val < x
        -> first partition

    else
        -> second partition

Therefore, we can construct BOTH partitions during one traversal.


================================================================================
ONE-PASS IDEA
================================================================================

We decided to maintain two independent sublists:

    LESS THAN x

    GREATER THAN OR EQUAL TO x

For each node:

    1. Save enough information to continue traversing the original list.
    2. Detach the current node from its old connection.
    3. Append it to the appropriate partition.
    4. Continue with the next original node.

This gives:

    Original list
          |
          v
       current
        /    \
       /      \
     < x      >= x
      |         |
      v         v
   first      second
   list       list

At the end:

    first list -> second list


================================================================================
POINTER DESIGN
================================================================================

The final solution uses five pointers:

    current
    temp1
    temp2
    link
    newHead


1. current
--------------------------------------------------------------------------------

Role:

    Traverses the original list.

Example:

    4 -> 1 -> 5 -> 2 -> 3 -> NULL
    ^
    current

After processing 4:

    4 -> NULL

    1 -> 5 -> 2 -> 3 -> NULL
    ^
    current


2. temp1
--------------------------------------------------------------------------------

Role:

    Tail of the < x partition.

Example:

    1 -> 2 -> NULL
         ^
       temp1

Whenever another node belongs to the first partition, it is appended after
temp1, and temp1 is moved to the newly appended node.


3. temp2
--------------------------------------------------------------------------------

Role:

    Tail of the >= x partition.

Example:

    4 -> 5 -> 3 -> NULL
              ^
            temp2

Whenever another node belongs to the second partition, it is appended after
temp2, and temp2 is moved forward.


4. link
--------------------------------------------------------------------------------

Role:

    Head of the >= x partition.

Example:

    link
      |
      v
    4 -> 5 -> 3 -> NULL

This pointer is established only when the FIRST >= x node is encountered.


5. newHead
--------------------------------------------------------------------------------

Role:

    Head of the < x partition and therefore the head of the final answer when
    that partition exists.

Example:

    newHead
       |
       v
    1 -> 2 -> NULL

It is established only when the FIRST < x node is encountered.


================================================================================
IMPORTANT LINKED-LIST INSIGHT — DETACHING NODES
================================================================================

One of the biggest insights during the debugging process was that merely
deciding which partition a node belongs to is not enough.

We are REARRANGING existing nodes.

Therefore, the node's old next connection must be controlled.

For example:

    Original:

    4 -> 1 -> 5 -> 2 -> 3 -> NULL

If 4 belongs to the >= x partition, we want:

    4 -> NULL

while preserving the remaining original traversal:

    1 -> 5 -> 2 -> 3 -> NULL

The important idea is:

    DETACH the processed node from the original structure.

This prevents the two newly constructed partitions from accidentally sharing
nodes or retaining unwanted old connections.


================================================================================
IMPORTANT POINTER SAFETY RULE
================================================================================

Before changing the current node's next pointer, we must know where the
original traversal should continue.

The robust general pattern is:

    ListNode* next = current->next;

    // manipulate current

    current = next;

In the final implementation below, the original next node is stored by
advancing current BEFORE detaching the current tail:

    current = current->next;
    temp1->next = nullptr;

or:

    current = current->next;
    temp2->next = nullptr;

This works because current has already moved to the next original node before
the processed node is disconnected.

The general linked-list lesson is:

    SAVE / PRESERVE THE TRAVERSAL PATH
    BEFORE DESTROYING OR MODIFYING THE CONNECTION YOU NEED.


================================================================================
INITIAL FAILED VERSION
================================================================================

The initial implementation attempted to construct the two partitions but
did not properly preserve structural connectivity.

A major issue was discovered through dry-running:

    temp1->next = current

or:

    temp2->next = current

changes an existing connection in the original list.

For example:

    4 -> 1 -> 5 -> 2 -> 3

If temp2 points to 4 and current points to 5:

    temp2->next = current

changes:

    4 -> 1

into:

    4 -> 5

Therefore, node 1 is removed from that original chain.

If node 1 is not already safely stored in the first partition, it can become
detached from the structure.

This led to the realization that the processed nodes must be explicitly
detached and the original traversal must remain safe.


================================================================================
DRY RUN — TEST CASE
================================================================================

We used:

    4 -> 1 -> 5 -> 2 -> 3 -> NULL

with:

    x = 3


================================================================================
ITERATION 1 — CURRENT = 4
================================================================================

Check:

    4 < 3 ?

False.

Therefore 4 belongs to the >= x partition.

Initially:

    temp2  = NULL
    link   = NULL
    temp1  = NULL
    newHead = NULL

Since temp2 is NULL, 4 is the first node of the second partition.

Execute:

    temp2 = current;
    link = temp2;

Now:

    link  -> 4
    temp2 -> 4

Then advance:

    current = current->next;

Now:

    current -> 1

Finally detach:

    temp2->next = NULL;

Therefore:

    >= x partition:

    link
      |
      v
    4 -> NULL
    ^
    temp2

Remaining original traversal:

    current
       |
       v
    1 -> 5 -> 2 -> 3 -> NULL


================================================================================
ITERATION 2 — CURRENT = 1
================================================================================

Check:

    1 < 3 ?

True.

Therefore 1 belongs to the < x partition.

Initially:

    temp1 = NULL

So this is the first node of the first partition.

Execute:

    temp1 = current;
    newHead = current;

Now:

    newHead -> 1
    temp1   -> 1

Advance:

    current = current->next;

Now:

    current -> 5

Detach:

    temp1->next = NULL;

Therefore:

    < x partition:

    newHead
       |
       v
    1 -> NULL
    ^
    temp1

    >= x partition:

    link
      |
      v
    4 -> NULL
    ^
    temp2

    Remaining original traversal:

    current
       |
       v
    5 -> 2 -> 3 -> NULL


================================================================================
ITERATION 3 — CURRENT = 5
================================================================================

Check:

    5 < 3 ?

False.

Therefore 5 belongs to the >= x partition.

Now:

    temp2 -> 4

So temp2 is not NULL.

Append 5:

    temp2->next = current;

Now:

    4 -> 5

Move the tail:

    temp2 = temp2->next;

Now:

    temp2 -> 5

Advance current:

    current = current->next;

Now:

    current -> 2

Detach:

    temp2->next = NULL;

Therefore:

    >= x partition:

    link
      |
      v
    4 -> 5 -> NULL
         ^
       temp2

    < x partition:

    newHead
       |
       v
    1 -> NULL
    ^
    temp1

    Remaining original traversal:

    current
       |
       v
    2 -> 3 -> NULL


================================================================================
ITERATION 4 — CURRENT = 2
================================================================================

Check:

    2 < 3 ?

True.

Therefore 2 belongs to the < x partition.

Now:

    temp1 -> 1

Append:

    temp1->next = current;

Now:

    1 -> 2

Move tail:

    temp1 = temp1->next;

Now:

    temp1 -> 2

Advance:

    current = current->next;

Now:

    current -> 3

Detach:

    temp1->next = NULL;

Therefore:

    < x partition:

    newHead
       |
       v
    1 -> 2 -> NULL
         ^
       temp1

    >= x partition:

    link
      |
      v
    4 -> 5 -> NULL
         ^
       temp2

    Remaining:

    current
       |
       v
    3 -> NULL


================================================================================
ITERATION 5 — CURRENT = 3
================================================================================

Check:

    3 < 3 ?

False.

Therefore 3 belongs to the >= x partition.

Append it:

    temp2->next = current;

So:

    4 -> 5 -> 3

Move tail:

    temp2 = temp2->next;

Now:

    temp2 -> 3

Advance:

    current = current->next;

Therefore:

    current = NULL

Detach:

    temp2->next = NULL;

Final partitions:

    < x:

    newHead
       |
       v
    1 -> 2 -> NULL
         ^
       temp1

    >= x:

    link
      |
      v
    4 -> 5 -> 3 -> NULL
              ^
            temp2


================================================================================
FINAL CONNECTION
================================================================================

Now both partitions are independently correct.

First partition:

    1 -> 2 -> NULL

Second partition:

    4 -> 5 -> 3 -> NULL

We connect them:

    temp1->next = link;

Therefore:

    1 -> 2 -> 4 -> 5 -> 3 -> NULL

Return:

    newHead


================================================================================
EDGE CASES
================================================================================

CASE 1: Empty list
--------------------------------------------------------------------------------

Input:

    NULL

The code immediately returns head.

No pointer manipulation is needed.


CASE 2: One-node list
--------------------------------------------------------------------------------

Input:

    1 -> NULL

No partitioning is necessary.

The code immediately returns head.


CASE 3: No nodes are < x
--------------------------------------------------------------------------------

Example:

    4 -> 5 -> 6 -> 7
    x = 3

Then:

    newHead = NULL
    link = 4

The first partition does not exist.

Therefore:

    return link;

Result:

    4 -> 5 -> 6 -> 7


CASE 4: No nodes are >= x
--------------------------------------------------------------------------------

Example:

    1 -> 2 -> 1 -> 2
    x = 3

Then:

    newHead -> 1
    temp1   -> 2
    link    = NULL

The final operation:

    temp1->next = link;

simply terminates the first partition:

    1 -> 2 -> 1 -> 2 -> NULL

Return newHead.


CASE 5: Both partitions exist
--------------------------------------------------------------------------------

Example:

    4 -> 1 -> 5 -> 2 -> 3
    x = 3

Result:

    1 -> 2 -> 4 -> 5 -> 3 -> NULL


CASE 6: Values equal to x
--------------------------------------------------------------------------------

Example:

    1 -> 3 -> 2
    x = 3

Because the condition is:

    current->val < x

the value 3 belongs to the SECOND partition.

Result:

    1 -> 3 -> 2

The relative ordering of the >= x partition is preserved.


================================================================================
FINAL ALGORITHM
================================================================================

1. Handle an empty list.
2. Handle a one-node list.
3. Initialize:
       current
       temp1
       temp2
       link
       newHead
4. Traverse the list once.
5. If current->val < x:
       - If first node of first partition:
             set temp1 and newHead.
       - Otherwise append after temp1 and move temp1.
       - Advance current.
       - Detach the processed node.
6. Otherwise:
       - If first node of second partition:
             set temp2 and link.
       - Otherwise append after temp2 and move temp2.
       - Advance current.
       - Detach the processed node.
7. If no < x partition exists:
       return link.
8. Connect:
       temp1->next = link
9. Return:
       newHead.


================================================================================
FINAL CODE
================================================================================
*/

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {

        // Edge case:
        // Empty linked list.
        if (head == nullptr) {
            return head;
        }

        // Edge case:
        // Only one node exists.
        if (head->next == nullptr) {
            return head;
        }

        /*
        Pointer roles:

        current:
            Traverses the original list.

        temp1:
            Tail of the < x partition.

        temp2:
            Tail of the >= x partition.

        link:
            Head of the >= x partition.

        newHead:
            Head of the < x partition.
        */

        ListNode* current = head;
        ListNode* temp1 = nullptr;
        ListNode* temp2 = nullptr;
        ListNode* link = nullptr;
        ListNode* newHead = nullptr;

        while (current != nullptr) {

            // ---------------------------------------------------------------
            // FIRST PARTITION: current->val < x
            // ---------------------------------------------------------------
            if (current->val < x) {

                // A < x node already exists.
                if (temp1 != nullptr) {

                    // Append current to the first partition.
                    temp1->next = current;

                    // Move the tail to the newly appended node.
                    temp1 = temp1->next;

                    /*
                    Move current BEFORE detaching the processed node.

                    This preserves our traversal of the original list.
                    */
                    current = current->next;

                    // Detach the processed node from its old connection.
                    temp1->next = nullptr;
                }

                // This is the first < x node.
                else {

                    // Establish the tail.
                    temp1 = current;

                    // Establish the head of the final answer.
                    newHead = current;

                    // Move to the next original node.
                    current = current->next;

                    // Detach this node.
                    temp1->next = nullptr;
                }
            }

            // ---------------------------------------------------------------
            // SECOND PARTITION: current->val >= x
            // ---------------------------------------------------------------
            else {

                // A >= x node already exists.
                if (temp2 != nullptr) {

                    // Append current to the second partition.
                    temp2->next = current;

                    // Move the tail to the newly appended node.
                    temp2 = temp2->next;

                    /*
                    Move current before disconnecting the processed node.
                    */
                    current = current->next;

                    // Detach the processed node.
                    temp2->next = nullptr;
                }

                // This is the first >= x node.
                else {

                    // Establish the tail.
                    temp2 = current;

                    // Establish the head of the second partition.
                    link = temp2;

                    // Move to the next original node.
                    current = current->next;

                    // Detach this node.
                    temp2->next = nullptr;
                }
            }
        }

        /*
        If no node was < x, then the first partition does not exist.

        Example:

            4 -> 5 -> 6
            x = 3

        Therefore the second partition is already the complete answer.
        */
        if (newHead == nullptr) {
            return link;
        }

        /*
        Both partitions exist.

        Connect the tail of the < x partition to the head of the
        >= x partition.
        */
        temp1->next = link;

        return newHead;
    }
};


/*
================================================================================
COMPLEXITY ANALYSIS
================================================================================

TIME COMPLEXITY
---------------

O(n)

We traverse every node exactly once.

For each node we perform only constant-time pointer operations.

Therefore:

    Time = O(n)

where n is the number of nodes.


SPACE COMPLEXITY
----------------

O(1) auxiliary space.

We only use a fixed number of pointer variables:

    current
    temp1
    temp2
    link
    newHead

No array, vector, map, recursion, or other structure proportional to n is
created.

Therefore:

    Auxiliary Space = O(1)


================================================================================
INTERVIEW EXPLANATION
================================================================================

A concise interview explanation:

"I maintain two separate linked-list partitions while traversing the original
list once.

The first partition contains nodes whose values are less than x, and the
second contains nodes whose values are greater than or equal to x.

For each partition I maintain a tail pointer. I also maintain a pointer to
the head of each partition so I can connect them at the end.

When I process a node, I move current to the next original node and then
disconnect the processed node from its previous connection. This prevents the
two partitions from accidentally sharing old links.

After the traversal, if the < x partition is empty, I return the head of the
>= x partition. Otherwise I connect the tail of the first partition to the
head of the second partition.

The algorithm runs in O(n) time and O(1) auxiliary space."


================================================================================
IMPORTANT LESSONS LEARNED
================================================================================

1. ONE-PASS THINKING
--------------------

The original idea was a two-pass solution.

The stronger realization was:

    Every node only needs to be classified once.

Therefore both partitions can be constructed in one traversal.


2. HEAD VS TAIL
---------------

A linked-list partition usually needs both concepts:

    HEAD:
        Where the sublist starts.

    TAIL:
        Where the next node should be appended.

In this solution:

    newHead = head of < x partition
    temp1   = tail of < x partition

    link    = head of >= x partition
    temp2   = tail of >= x partition


3. POINTER VARIABLE VS NODE CONNECTION
--------------------------------------

These are completely different operations:

    temp2 = nullptr;

changes the pointer variable.

It does NOT change the linked list.

Whereas:

    temp2->next = nullptr;

changes the actual connection inside the node.

This distinction is fundamental in C++ linked-list problems.


4. STRUCTURAL INTEGRITY
-----------------------

A pointer algorithm can look correct locally while destroying the global
structure of the linked list.

When changing:

    node->next

always ask:

    "What node was previously connected here?"

and:

    "Where does my traversal need to continue?"


5. PRESERVE THE TRAVERSAL
-------------------------

Before destroying a connection, we must know where the original traversal
continues.

The general principle is:

    Save the next node
        OR
    advance the traversal pointer before disconnecting the processed node.

Never destroy the only connection to the remaining list without first
preserving the traversal path.


6. RELATIVE ORDER
-----------------

The problem requires stable partitioning.

For:

    1 -> 4 -> 3 -> 2 -> 5 -> 2

and x = 3:

The < x nodes appear in their original order:

    1 -> 2 -> 2

The >= x nodes also appear in their original order:

    4 -> 3 -> 5

This is why nodes are appended to the tails rather than inserted at the
front.


7. EDGE CASE THINKING
---------------------

Important cases include:

    - Empty list
    - One node
    - No node < x
    - No node >= x
    - Both partitions exist
    - Nodes equal to x
    - Already partitioned list
    - All nodes on one side of x


================================================================================
PERSONAL DSA JOURNEY NOTE
================================================================================

This problem was solved independently through reasoning, brainstorming,
implementation, dry-running, debugging, and repeated correction rather than
copying a tutorial solution.

The important progression was:

    Initial two-pass idea
            ↓
    One-pass realization
            ↓
    Two partition lists
            ↓
    Head/tail pointer roles
            ↓
    Structural connectivity problem
            ↓
    Detaching processed nodes
            ↓
    Preserving original traversal
            ↓
    Handling empty partitions
            ↓
    Final O(n) / O(1) solution

The solution may use more pointers than the most common textbook solution,
but the important achievement is that the pointer architecture was developed
through independent problem solving.

The goal is not merely to increase the number of solved questions.

The goal is to develop the ability to look at an unfamiliar linked-list
problem, reason about its structure, build a solution, debug it, and
eventually recognize the underlying pattern.

================================================================================
END
================================================================================
