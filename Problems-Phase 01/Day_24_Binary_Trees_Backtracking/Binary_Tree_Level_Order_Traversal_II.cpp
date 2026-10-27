
/*
===============================================================================
DSA JOURNEY — BINARY TREE LEVEL ORDER TRAVERSAL II
===============================================================================

Problem: LeetCode 107 — Binary Tree Level Order Traversal II
Language: C++
Approach: Breadth-First Search (BFS) using a queue
Status: Solved
Session: DSA Day 24
Purpose: Detailed revision notes for GitHub and interview preparation

===============================================================================
1. PROBLEM STATEMENT
===============================================================================

Given the root of a binary tree, return its bottom-up level order traversal.

This means:
  1. Visit the tree level by level.
  2. Keep nodes within each level in left-to-right order.
  3. Return the levels in reverse order, from bottom to top.

Example:

             3
            / \
           9   20
              /  \
             15   7

Normal level-order traversal:
  [[3], [9, 20], [15, 7]]

Required bottom-up traversal:
  [[15, 7], [9, 20], [3]]

IMPORTANT:
  We reverse the ORDER OF THE LEVELS.
  We do not reverse the values inside each level.

===============================================================================
2. APPROACH — BREADTH-FIRST SEARCH (BFS)
===============================================================================

We use a queue to visit the tree level by level.

A queue follows FIFO:
  First In, First Out.

The node inserted first is removed first.

Our algorithm:

  1. Create an empty answer matrix ans.
  2. Create a queue of TreeNode pointers.
  3. If root is nullptr, return an empty result.
  4. Insert root into the queue.
  5. While the queue is not empty:
       a. Create an empty vector v for the current level.
       b. Store the current queue size in levelSize.
       c. Process exactly levelSize nodes.
       d. Store each node's value in v.
       e. Insert its existing left and right children into the queue.
       f. Append v to ans.
  6. Reverse ans.
  7. Return ans.

WHY BFS?
  BFS naturally processes all nodes at one depth before processing nodes
  at the next depth.

WHY REVERSE AT THE END?
  BFS produces top-to-bottom levels.
  The problem asks for bottom-to-top levels.
  Reversing the outer vector is a simple way to change that order.

===============================================================================
3. YOUR SOLUTION
===============================================================================

class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
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

                i ++;
            }

            ans.push_back(v);
        }

        reverse(ans.begin(), ans.end());
        return ans;
    }
};

===============================================================================
4. LINE-BY-LINE EXPLANATION
===============================================================================

A. ANSWER MATRIX

  vector<vector<int>> ans;

  ans stores the values of all levels.

  Each inner vector represents one level.

  Example:
    ans = [[3], [9, 20], [15, 7]]

  At this stage, levels are stored from top to bottom.

B. QUEUE

  queue<TreeNode*> q;

  The queue stores pointers to tree nodes waiting to be processed.

  We store pointers instead of copying the actual tree nodes.

C. EMPTY TREE CHECK

  if (root == nullptr) {
      return {};
  }

  If the tree is empty, there are no levels to return.

  An empty vector of vectors is the correct result.

D. INSERT THE ROOT

  q.push(root);

  The root is the first node to be processed.

E. OUTER WHILE LOOP

  while (!q.empty())

  Continue while there are nodes waiting in the queue.

  Each iteration of this outer loop processes exactly one tree level.

F. CURRENT LEVEL VECTOR

  vector<int> v;

  This vector stores the values belonging to the current level.

  It is created inside the outer loop because every level needs its own
  separate vector.

G. LEVEL SIZE

  int levelSize = q.size();

  This is one of the most important lines in the algorithm.

  It records how many nodes are currently waiting in the queue.

  At the beginning of a level, these nodes belong to that level.

  While processing them, we may enqueue children. Those children belong to
  the next level, not the current level.

  Saving levelSize prevents the newly inserted children from being processed
  as part of the current level.

H. COUNTER

  int i = 0;

  The counter tracks how many nodes from the current level have been processed.

I. INNER WHILE LOOP

  while (i < levelSize)

  Process exactly levelSize nodes.

  This ensures that one iteration of the outer loop corresponds to one
  complete level.

J. ACCESS THE FRONT NODE

  TreeNode* node = q.front();

  q.front() returns the pointer at the front of the queue.

  We process that node first because the queue follows FIFO order.

K. STORE THE NODE VALUE

  v.push_back(node->val);

  Append the current node's value to the vector for this level.

  Because nodes are processed left to right, their values remain in
  left-to-right order within the level.

L. REMOVE THE PROCESSED NODE

  q.pop();

  Remove the front node from the queue.

  Its value has already been recorded, and its children will be added if
  they exist.

M. ADD THE LEFT CHILD

  if (node->left != nullptr) {
      q.push(node->left);
  }

  Insert the left child if it exists.

  It will be processed in the next level.

N. ADD THE RIGHT CHILD

  if (node->right != nullptr) {
      q.push(node->right);
  }

  Insert the right child if it exists.

  Since the left child is enqueued first, BFS preserves left-to-right order.

O. INCREMENT THE COUNTER

  i++;

  One node from the current level has been processed.

  When i reaches levelSize, the inner loop ends.

P. SAVE THE COMPLETED LEVEL

  ans.push_back(v);

  The current level is complete, so append it to the answer matrix.

  The outer loop then starts the next level if the queue is not empty.

Q. REVERSE THE LEVELS

  reverse(ans.begin(), ans.end());

  This reverses the order of the inner vectors.

  Example:

    Before:
      [[3], [9, 20], [15, 7]]

    After:
      [[15, 7], [9, 20], [3]]

  Notice that [9, 20] remains [9, 20].

R. RETURN THE ANSWER

  return ans;

  The matrix now contains the levels from bottom to top.

===============================================================================
5. COMPLETE DRY RUN
===============================================================================

Consider this tree:

             3
            / \
           9   20
              /  \
             15   7

INITIAL STATE:

  ans = []
  q   = [3]

----------------------------------------
ITERATION 1 — PROCESS LEVEL 0
----------------------------------------

At the beginning:
  q = [3]

Save the queue size:
  levelSize = 1

Create:
  v = []
  i = 0

Since i < levelSize, process node 3.

Step 1:
  node = q.front() = 3

Step 2:
  Append its value:
    v = [3]

Step 3:
  Remove node 3:
    q = []

Step 4:
  Enqueue its left child, 9:
    q = [9]

Step 5:
  Enqueue its right child, 20:
    q = [9, 20]

Step 6:
  Increment i:
    i = 1

Now:
  i == levelSize

The inner loop ends.

Save the completed level:
  ans = [[3]]

State before the next outer iteration:
  q = [9, 20]

IMPORTANT:
  Even though 9 and 20 were added during the first iteration, they were not
  processed as part of level 0. levelSize was fixed at 1.

----------------------------------------
ITERATION 2 — PROCESS LEVEL 1
----------------------------------------

At the beginning:
  q = [9, 20]

Save:
  levelSize = 2

Create:
  v = []
  i = 0

Process node 9:

  node = q.front() = 9
  v = [9]
  q.pop() removes 9

  Node 9 has no children.

  q = [20]

  Increment:
    i = 1

Since 1 < 2, continue.

Process node 20:

  node = q.front() = 20
  v = [9, 20]
  q.pop() removes 20

  Enqueue left child 15:
    q = [15]

  Enqueue right child 7:
    q = [15, 7]

  Increment:
    i = 2

Now:
  i == levelSize

The inner loop ends.

Save:
  ans = [[3], [9, 20]]

Queue:
  q = [15, 7]

----------------------------------------
ITERATION 3 — PROCESS LEVEL 2
----------------------------------------

At the beginning:
  q = [15, 7]

Save:
  levelSize = 2

Create:
  v = []
  i = 0

Process node 15:

  node = 15
  v = [15]
  q = [7]

  Node 15 has no children.

  Increment:
    i = 1

Process node 7:

  node = 7
  v = [15, 7]
  q = []

  Node 7 has no children.

  Increment:
    i = 2

Now:
  i == levelSize

The inner loop ends.

Save:
  ans = [[3], [9, 20], [15, 7]]

The queue is empty, so the outer loop ends.

----------------------------------------
FINAL REVERSAL
----------------------------------------

Before reverse:
  [[3], [9, 20], [15, 7]]

After reverse:
  [[15, 7], [9, 20], [3]]

FINAL ANSWER:
  [[15, 7], [9, 20], [3]]

===============================================================================
6. WHY LEVEL SIZE IS ESSENTIAL
===============================================================================

Suppose we do not save the current queue size.

We process node 3 and enqueue nodes 9 and 20.

The queue now contains:
  [9, 20]

If we use a loop that continues until the queue is empty, we could process
nodes from multiple levels in one iteration.

That would destroy the separation between levels.

By saving:
  levelSize = q.size()

we commit to processing exactly the nodes that were waiting at the beginning
of the current level.

Newly enqueued children remain in the queue until the next outer iteration.

This is a standard BFS pattern used in many tree problems.

===============================================================================
7. WHY REVERSE THE OUTER VECTOR?
===============================================================================

The answer has type:

  vector<vector<int>>

It is a vector whose elements are themselves vectors.

For example:

  ans = {
      {3},
      {9, 20},
      {15, 7}
  };

There are two levels of ordering:

  Outer vector:
    The order of tree levels.

  Inner vectors:
    The order of nodes within each level.

The call:

  reverse(ans.begin(), ans.end());

reverses the outer vector only.

Result:

  {
      {15, 7},
      {9, 20},
      {3}
  }

It does not reverse the elements inside each inner vector.

Do not confuse this with reversing every individual level.

===============================================================================
8. COMMON MISTAKES
===============================================================================

MISTAKE 1 — Not saving levelSize.

  Problem:
    Newly enqueued children may be processed during the current level.

  Prevention:
    Save the queue size before entering the inner loop.

MISTAKE 2 — Using the wrong loop boundary.

  Problem:
    Processing until the queue is empty does not preserve level boundaries.

  Prevention:
    Process exactly levelSize nodes.

MISTAKE 3 — Reversing every inner vector.

  Problem:
    The problem asks for bottom-up levels, while preserving left-to-right
    order within each level.

  Prevention:
    Reverse the outer vector, not each inner vector.

MISTAKE 4 — Enqueuing null children.

  Problem:
    Null pointers do not represent real nodes and should not be processed.

  Prevention:
    Check node->left and node->right against nullptr before enqueueing.

MISTAKE 5 — Forgetting to pop the front node.

  Problem:
    The same node would remain at the front and could be processed repeatedly.

  Prevention:
    After retrieving the front node, remove it from the queue.

MISTAKE 6 — Creating the current-level vector outside the outer loop.

  Problem:
    Values from different levels could be mixed into the same vector.

  Prevention:
    Create a fresh vector<int> v for every level.

MISTAKE 7 — Forgetting the empty-tree case.

  Problem:
    An empty tree has no levels to process.

  Prevention:
    Return an empty result when root == nullptr.

===============================================================================
9. COMPLEXITY ANALYSIS
===============================================================================

Let:
  n = total number of nodes
  w = maximum width of the tree

TIME COMPLEXITY: O(n)

Every node is:
  - Enqueued once.
  - Removed from the queue once.
  - Processed once.

The final reverse operation processes the level vectors. Across all levels,
the total number of stored values is n, so reversing the outer vector takes
O(number of levels), which is at most O(n).

Therefore, total time complexity is O(n).

QUEUE SPACE: O(w)

The queue stores nodes waiting to be processed.
At most a level's worth of nodes may be in the queue, so queue space is
O(w), where w is the maximum width.

In the worst case, w can be O(n).

RESULT SPACE: O(n)

The answer matrix stores every node value exactly once.

TOTAL SPACE INCLUDING RESULT: O(n) in the worst case.

For interview discussions, distinguish auxiliary queue space from the
space needed to return the answer.

===============================================================================
10. DFS VS BFS FOR THIS PROBLEM
===============================================================================

BFS approach — your solution:
  - Uses a queue.
  - Processes one complete level at a time.
  - Stores each level in a vector.
  - Reverses the outer answer vector.

DFS alternative:
  - Could track the depth and build level vectors recursively.
  - Would need to reverse the levels afterward.
  - Does not naturally process the tree in level order, so BFS is the more
    direct approach for this problem.

BFS is a natural fit because the problem explicitly asks for level order.

===============================================================================
11. REVISION QUESTIONS
===============================================================================

Try answering these without looking at the earlier explanations.

1. What does FIFO mean?
2. Why do we use queue<TreeNode*>?
3. Why is levelSize saved before the inner loop?
4. What happens if we process the queue until it is empty inside the inner
   loop?
5. Why is v created inside the outer loop?
6. Why do we enqueue the left child before the right child?
7. What does ans.push_back(v) do?
8. What exactly does reverse(ans.begin(), ans.end()) reverse?
9. Why does an empty tree return an empty matrix?
10. Why is the time complexity O(n)?
11. What does w represent in the space complexity?
12. Can the queue contain O(n) nodes in the worst case?
13. Why does reversing the outer vector preserve left-to-right order within
    each level?

KEY INTERVIEW EXPLANATION:

"I use BFS with a queue. At the start of each level, I save the queue size so
I process exactly the nodes belonging to that level. I collect their values
in a separate vector and enqueue their children for the next level. BFS gives
me top-to-bottom levels, so I reverse the outer answer vector to return them
from bottom to top while preserving left-to-right order within each level."

===============================================================================
12. FINAL CODE — LEETCODE SUBMISSION
===============================================================================

The code below is your original implementation.

LeetCode supplies the TreeNode definition and required environment.
===============================================================================
*/

class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
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

        reverse(ans.begin(), ans.end());
        return ans;
    }
};

/*
===============================================================================
END OF REVISION FILE
===============================================================================
*/
