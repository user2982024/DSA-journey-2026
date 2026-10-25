
/*
===============================================================================
PROBLEM: BINARY TREE LEVEL ORDER TRAVERSAL
Platform: LeetCode 102
Language: C++
Topics: Binary Trees, BFS, Queue, Nested Vectors
===============================================================================

SOLUTION STATUS
---------------
Your submitted solution is correct.

It uses BFS with a queue. The outer loop handles one level at a time, while
the inner loop processes exactly the nodes that were in the queue at the
beginning of that level. Their values are stored in a temporary vector, which
is then appended to the final answer.

===============================================================================
1. PROBLEM STATEMENT
===============================================================================

Return the binary tree's node values level by level, from left to right.

Example:

                 3
               /   \
              9     20
                   /  \
                  15   7

Output:
    [[3], [9, 20], [15, 7]]

The result is a vector of vectors:
- The outer vector stores all levels.
- Each inner vector stores the values from one level.

This differs from a flat traversal such as [3, 9, 20, 15, 7].

===============================================================================
2. YOUR SUBMITTED CODE
===============================================================================

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        queue<TreeNode*> q;

        if (root == nullptr) {
            return {};
        }

        q.push(root);

        while (!q.empty()) {
            vector<int> v;
            int levelSize = q.size();
            int i = 0;

            while (i < levelSize) {
                TreeNode* node = q.front();
                v.push_back(node->val);
                q.pop();

                if (node->left != nullptr) {
                    q.push(node->left);
                }

                if (node->right != nullptr) {
                    q.push(node->right);
                }

                i++;
            }

            ans.push_back(v);
        }

        return ans;
    }
};

===============================================================================
3. CORE IDEA: BFS AND LEVEL GROUPING
===============================================================================

BFS means Breadth-First Search. It explores a tree level by level.

A queue follows FIFO: First In, First Out.
- q.push(x): add x to the back.
- q.front(): read the front item without removing it.
- q.pop(): remove the front item; it does not return the item.
- q.empty(): check whether the queue is empty.

Your code uses three important containers/variables:

1. queue<TreeNode*> q
   Stores pointers to nodes that still need to be processed.

2. vector<int> v
   Stores the values of the current level only.

3. vector<vector<int>> ans
   Stores each completed level vector.

The most important line is:

    int levelSize = q.size();

It records how many nodes are waiting in the queue at the START of the
current level. The inner loop processes exactly this many nodes. Any children
added while processing those nodes belong to the next level.

===============================================================================
4. LINE-BY-LINE EXPLANATION
===============================================================================

    vector<vector<int>> ans;

Create an empty final answer. Each item added to ans will be one level.

    queue<TreeNode*> q;

Create a queue of node pointers. The queue stores pointers, not integer
values, because we need to access each node's children.

    if (root == nullptr) {
        return {};
    }

If the tree is empty, return an empty result. There is no node to visit.

    q.push(root);

Put the root into the queue. It is the first node to process.

    while (!q.empty()) {

Keep processing while the queue contains nodes.

    vector<int> v;

Create a new, empty vector for this level. It must be created inside the
outer loop so each level gets its own vector.

    int levelSize = q.size();

Capture the number of nodes currently in the queue. This is the number of
nodes belonging to this level.

    int i = 0;

Start a counter for how many nodes from the current level have been processed.

    while (i < levelSize) {

Process exactly levelSize nodes. Even if children are added to the queue,
this loop will not process more than the original levelSize nodes.

    TreeNode* node = q.front();

Read the front pointer from the queue and store it in node.

    v.push_back(node->val);

Append the current node's integer value to the vector for this level.

    q.pop();

Remove the front pointer from the queue. This does not delete the actual
tree node, and it does not return the removed pointer.

    if (node->left != nullptr) {
        q.push(node->left);
    }

If the left child exists, add it to the queue.

    if (node->right != nullptr) {
        q.push(node->right);
    }

If the right child exists, add it to the queue. Adding left before right
preserves left-to-right order at each level.

    i++;

One node from the current level has been processed. Increment i so the inner
loop moves toward completion. Without this increment, the loop could run
forever whenever levelSize is greater than zero.

    ans.push_back(v);

Once the inner loop finishes, v contains the complete current level. Append
it to ans.

    return ans;

When the queue becomes empty, all nodes have been processed and every level
has been added to the answer.

===============================================================================
5. WHY levelSize IS ESSENTIAL
===============================================================================

Consider this tree:

             1
            / \
           2   3
          / \
         4   5

Initially:
    q = [1]

At the beginning of level 0:
    levelSize = q.size() = 1

The inner loop processes node 1. Its children are added:
    q = [2, 3]

But levelSize is still 1. The inner loop ends after processing node 1.
Nodes 2 and 3 wait for the next outer-loop iteration.

At the beginning of level 1:
    levelSize = q.size() = 2

The inner loop processes node 2 and node 3. While processing node 2, it adds
nodes 4 and 5. They are added behind node 3:
    q = [3, 4, 5]

Node 3 is still processed as part of the current level because the loop must
process two nodes. Nodes 4 and 5 wait for the next level.

Do not use a changing q.size() as the inner-loop limit. The queue changes
when children are added. Capturing levelSize once keeps levels separate.

===============================================================================
6. COMPLETE DRY RUN
===============================================================================

Tree:

                 1
               /   \
              2     3
             / \     \
            4   5     6

Expected output:
    [[1], [2, 3], [4, 5, 6]]

Initial:
    ans = []
    q = [1]

OUTER ITERATION 1
-----------------
At the start:
    v = []
    levelSize = 1
    i = 0

Process node 1:
    v = [1]
    q.pop() removes 1
    enqueue left child 2, then right child 3

State:
    v = [1]
    q = [2, 3]
    i = 1

Now i < levelSize means 1 < 1, which is false.
Append v:
    ans = [[1]]

OUTER ITERATION 2
-----------------
At the start:
    v = []
    levelSize = 2
    i = 0
    q = [2, 3]

Process node 2:
    v = [2]
    remove 2
    enqueue children 4 and 5

State:
    q = [3, 4, 5]
    i = 1

Process node 3:
    v = [2, 3]
    remove 3
    enqueue its right child 6

State:
    q = [4, 5, 6]
    i = 2

Now 2 < 2 is false. Append v:
    ans = [[1], [2, 3]]

Notice that children 4, 5, and 6 were added during this iteration, but they
were not processed in this same inner loop. The captured levelSize was 2.

OUTER ITERATION 3
-----------------
At the start:
    v = []
    levelSize = 3
    i = 0
    q = [4, 5, 6]

Process node 4:
    v = [4]
    q = [5, 6]
    i = 1

Process node 5:
    v = [4, 5]
    q = [6]
    i = 2

Process node 6:
    v = [4, 5, 6]
    q = []
    i = 3

Now 3 < 3 is false. Append v:
    ans = [[1], [2, 3], [4, 5, 6]]

The queue is empty, so the outer loop stops.

Final answer:
    [[1], [2, 3], [4, 5, 6]]

===============================================================================
7. WHY LEFT-TO-RIGHT ORDER IS PRESERVED
===============================================================================

Two facts work together:

1. FIFO queue order means nodes already in the queue are processed before
   children added later.
2. Each node's left child is enqueued before its right child.

For example, after processing node 2, the queue can be [3, 4, 5]. Node 3
was already waiting, so it is processed before nodes 4 and 5. This ensures
the whole current level is processed before the next level.

===============================================================================
8. WHY v MUST BE CREATED INSIDE THE OUTER LOOP
===============================================================================

    while (!q.empty()) {
        vector<int> v;
        ...
        ans.push_back(v);
    }

Each outer-loop iteration represents a new level. A fresh v prevents values
from different levels from mixing.

If v were reused without clearing it, it could grow like:
    [1]
    [1, 2, 3]
    [1, 2, 3, 4, 5, 6]

That is not the required answer. Each level needs its own independent vector.

===============================================================================
9. EDGE CASES
===============================================================================

Empty tree:
    root == nullptr
    Output: []

Single node:
        1
    Output: [[1]]

Only left children:
        1
       /
      2
     /
    3
    Output: [[1], [2], [3]]

Only right children:
    1
     \
      2
       \
        3
    Output: [[1], [2], [3]]

Missing children:
        1
       / \
      2   3
       \   \
        5   7
    Output: [[1], [2, 3], [5, 7]]

The independent nullptr checks handle missing children correctly.

===============================================================================
10. TIME AND SPACE COMPLEXITY
===============================================================================

Time: O(n)
Every node is enqueued once and processed once. The operations performed for
each node take constant time on average, so the total time is O(n).

Queue auxiliary space: O(w)
The queue holds nodes waiting to be processed. Its maximum size is related to
the maximum width w of the tree. In the worst case, w can be O(n).

Output space: O(n)
Every node value appears in the returned nested vector.

Overall auxiliary space excluding the output is O(w), worst-case O(n).
Including the output, total space is O(n).

===============================================================================
11. COMMON MISTAKES
===============================================================================

1. Forgetting levelSize:
   Children added during processing could be mixed into the current level.

2. Recalculating q.size() as a changing inner-loop limit:
   The queue changes as children are added. Capture the size once per level.

3. Creating v outside the outer loop and not clearing it:
   Values from previous levels would remain.

4. Forgetting i++:
   The inner loop would not progress and could run indefinitely.

5. Enqueuing right before left:
   This reverses the left-to-right order within each level.

6. Assuming q.pop() returns the node:
   It only removes the front item. Read q.front() first.

7. Enqueuing nullptr:
   Only enqueue children that exist.

===============================================================================
12. CLEANER IMPLEMENTATION USING A FOR LOOP
===============================================================================

Your while-loop solution is correct. A for loop makes the fixed number of
iterations for a level more explicit:

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;

        if (root == nullptr) {
            return ans;
        }

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();
            vector<int> level;

            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();

                level.push_back(node->val);

                if (node->left != nullptr) {
                    q.push(node->left);
                }

                if (node->right != nullptr) {
                    q.push(node->right);
                }
            }

            ans.push_back(level);
        }

        return ans;
    }
};

This is logically equivalent to your submission. The crucial detail remains:
levelSize is captured before the inner loop begins.

===============================================================================
13. CONNECTION TO GFG LEVEL ORDER TRAVERSAL
===============================================================================

The GFG version returns a flat vector:
    [1, 2, 3, 4, 5, 6]

LeetCode 102 returns a nested vector:
    [[1], [2, 3], [4, 5, 6]]

Both use the same BFS queue and enqueue the left child before the right child.

LeetCode 102 adds:
- vector<vector<int>> ans to hold all levels.
- vector<int> v to hold the current level.
- levelSize to freeze the number of nodes in the current level.
- An inner loop to process exactly that number of nodes.

===============================================================================
14. QUICK REVISION QUESTIONS
===============================================================================

Q1. Which traversal is used?
A. Breadth-First Search (BFS).

Q2. What does levelSize mean?
A. The number of nodes in the queue at the beginning of the current level.

Q3. Why capture levelSize before processing nodes?
A. Children added while processing belong to the next level.

Q4. Why create a new v each outer iteration?
A. To keep each level's values separate.

Q5. Why enqueue left before right?
A. To preserve left-to-right order.

Q6. Why is i++ required?
A. It advances the inner loop after processing each node.

Q7. What is the time complexity?
A. O(n).

Q8. Why use a nested vector?
A. Each inner vector represents one level.

===============================================================================
15. FINAL TAKEAWAY
===============================================================================

The essential pattern is:

    while (!q.empty()) {
        int levelSize = q.size();
        vector<int> level;

        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();

            level.push_back(node->val);

            if (node->left)
                q.push(node->left);

            if (node->right)
                q.push(node->right);
        }

        ans.push_back(level);
    }

The key idea is that levelSize freezes the number of nodes to process for the
current level. Newly enqueued children wait until the next outer iteration.

Your submitted solution correctly implements this pattern.
===============================================================================
*/
