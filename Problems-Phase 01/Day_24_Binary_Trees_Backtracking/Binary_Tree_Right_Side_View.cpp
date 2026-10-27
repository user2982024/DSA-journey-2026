/*
===============================================================================
DSA JOURNEY — BINARY TREE RIGHT SIDE VIEW
Problem: LeetCode 199 — Binary Tree Right Side View
Language: C++
Approach: Depth-First Search (DFS), right-first traversal
Status: Accepted by the user
===============================================================================

HOW TO USE THIS FILE
--------------------
This is a self-contained revision document in C++ comment form, followed by
the actual LeetCode solution. You can keep it in your DSA GitHub repository.

The notes cover:
  1. Problem statement and examples
  2. Meaning of "right-side view"
  3. Core insight
  4. Why DFS works
  5. Explanation of every important line
  6. Detailed dry runs
  7. Call-stack reasoning
  8. Common mistakes
  9. Complexity analysis
 10. Alternative BFS idea
 11. Revision questions
 12. The original solution

IMPORTANT:
The code assumes LeetCode provides the TreeNode definition and required
standard-library declarations. The final section is ready to paste into
LeetCode's editor.
===============================================================================


===============================================================================
1. PROBLEM STATEMENT
===============================================================================

Given the root of a binary tree, imagine standing on its right side. Return
the values of the nodes that are visible, ordered from top to bottom.

In other words, for every level of the tree, we want the rightmost node.

Example 1:

             1
            / \
           2   3
            \   \
             5   4

Right-side view:
  [1, 3, 4]

Why?
  - Level 0: only node 1 exists, so we see 1.
  - Level 1: nodes 2 and 3 exist; from the right, node 3 is visible.
  - Level 2: nodes 5 and 4 exist; from the right, node 4 is visible.

Example 2:

             1
            /
           2
          /
         3

Right-side view:
  [1, 2, 3]

Even though this tree leans left, there is no node to the right of any level's
node. Therefore, each node is visible from the right.

Example 3:
  root = nullptr

Answer:
  []

An empty tree has no visible nodes.


===============================================================================
2. CORE IDEA
===============================================================================

We use Depth-First Search (DFS), visiting the RIGHT child before the LEFT child.

The recursive helper receives:
  - root: the current node
  - level: the current node's depth, starting at 0
  - ans: values already recorded for the right-side view

The crucial condition is:

  if (level == ans.size())

This means the current level has not yet had a node recorded.

Why does that identify the rightmost node?
  Because we always explore the right subtree before the left subtree. The
  first node we encounter at a given depth is therefore the rightmost node
  reached at that depth.

After recording the first node at a level, later nodes at the same level do
not pass the condition, because ans.size() has already grown to include that
level.

KEY RULE:
  Right child first  -> right-side view.
  Left child first   -> left-side view, using the same first-node-per-level
                        strategy.


===============================================================================
3. THE ACTUAL SOLUTION
===============================================================================

class Solution {
private:
    void rightView(TreeNode* root, int level, vector<int>& ans) {
        if (root == nullptr) {
            return;
        }

        if (level == ans.size()) {
            ans.push_back(root->val);
        }

        rightView(root->right, level + 1, ans);
        rightView(root->left, level + 1, ans);
    }

public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;

        rightView(root, 0, ans);

        return ans;
    }
};


===============================================================================
4. LINE-BY-LINE EXPLANATION
===============================================================================

class Solution {
  LeetCode expects a class named Solution.

private:
  The helper function is private because it is an implementation detail.
  The caller only needs to use rightSideView().

void rightView(TreeNode* root, int level, vector<int>& ans)
  TreeNode* root:
    Pointer to the node currently being processed.

  int level:
    The depth of this node.
    The root begins at level 0, its children are at level 1, and so on.

  vector<int>& ans:
    A reference to the same answer vector across recursive calls.
    The ampersand (&) means the vector is not copied at each call.
    Every recursive call can append to the shared answer.

if (root == nullptr) {
    return;
}
  Base case.
  There is no node to process, so this call returns immediately.
  It prevents the code from dereferencing a null pointer.

if (level == ans.size()) {
    ans.push_back(root->val);
}
  If the current depth equals the number of levels already recorded, this is
  the first node reached at this depth.
  Because traversal is right-first, record this node as the visible node.

rightView(root->right, level + 1, ans);
  Explore the right subtree first.
  Its child nodes are one level deeper, so use level + 1.

rightView(root->left, level + 1, ans);
  After the right subtree finishes, explore the left subtree.
  If a node at a depth has already been recorded, this later visit will not
  replace it.

public:
  The method LeetCode calls is public.

vector<int> rightSideView(TreeNode* root)
  Creates the answer vector and starts DFS at depth 0.

vector<int> ans;
  Initially, no levels have been recorded.

rightView(root, 0, ans);
  Start traversal from the root at level 0.

return ans;
  Return the recorded rightmost node from each level.


===============================================================================
5. DETAILED DRY RUN
===============================================================================

Use this tree:

             1
            / \
           2   3
            \   \
             5   4

The recursive order is:
  1 -> 3 -> 4 -> nullptr -> nullptr -> 2 -> 5 -> nullptr -> nullptr -> nullptr

Initial state:
  ans = []

CALL 1: rightView(node 1, level 0, ans)

  root is not nullptr.
  level = 0
  ans.size() = 0

  Check:
    0 == 0 -> true

  Record node 1:
    ans = [1]

  Recurse right:
    rightView(node 3, level 1, ans)

CALL 2: rightView(node 3, level 1, ans)

  root is not nullptr.
  level = 1
  ans.size() = 1

  Check:
    1 == 1 -> true

  Record node 3:
    ans = [1, 3]

  Recurse right:
    rightView(node 4, level 2, ans)

CALL 3: rightView(node 4, level 2, ans)

  root is not nullptr.
  level = 2
  ans.size() = 2

  Check:
    2 == 2 -> true

  Record node 4:
    ans = [1, 3, 4]

  Recurse right:
    rightView(nullptr, level 3, ans)

CALL 4: rightView(nullptr, level 3, ans)

  root == nullptr -> return.

  Execution resumes inside node 4's call, after its right-child call.
  Now node 4 calls its left child, which is also nullptr.

CALL 5: rightView(nullptr, level 3, ans)

  root == nullptr -> return.

  Node 4 has finished both child calls and returns to node 3.

  IMPORTANT:
    The answer remains [1, 3, 4].
    Returning from a child does not erase values from ans.

Back in CALL 2: node 3

  The right subtree is complete.
  Now process node 3's left child, which is nullptr.

CALL 6: rightView(nullptr, level 2, ans)

  root == nullptr -> return.

  Node 3 finishes and returns to node 1.

Back in CALL 1: node 1

  The right subtree has been fully processed.
  Now process node 1's left child, node 2.

CALL 7: rightView(node 2, level 1, ans)

  root is not nullptr.
  level = 1
  ans.size() = 3

  Check:
    1 == 3 -> false

  Do not record node 2.
  Level 1 already has node 3, the first node encountered at that level.

  Recurse right:
    rightView(node 5, level 2, ans)

CALL 8: rightView(node 5, level 2, ans)

  root is not nullptr.
  level = 2
  ans.size() = 3

  Check:
    2 == 3 -> false

  Do not record node 5.
  Level 2 already has node 4.

  Both children of node 5 are nullptr, so their calls return.
  Node 5 returns to node 2.

Back in node 2:
  Its left child is nullptr.
  That call returns.
  Node 2 finishes and returns to node 1.

Node 1 finishes.

FINAL ANSWER:
  [1, 3, 4]


===============================================================================
6. WHY level == ans.size() WORKS
===============================================================================

This is the most important line to understand.

The root has level 0 and the answer initially has size 0.
Therefore, the root is recorded.

The first node visited at level 1 sees ans.size() == 1, so it is recorded.
The first node visited at level 2 sees ans.size() == 2, so it is recorded.

After that, ans.size() becomes larger than the level of any later node at an
already-recorded depth. Such nodes are skipped.

This works because:
  - levels are visited in increasing depth along each root-to-leaf DFS route;
  - the right subtree is explored before the left subtree;
  - the first node encountered at a depth is the one chosen for that depth.

Do not confuse these two values:
  level       = depth of the current node
  ans.size()  = number of levels already represented in the answer

They are equal exactly when the current node is the first one recorded for
that depth.


===============================================================================
7. WHY VISIT RIGHT BEFORE LEFT?
===============================================================================

Suppose a level contains nodes 2 and 3:

          1
         / \
        2   3

If we visit right first:
  - Node 3 is reached first at level 1.
  - Node 3 is recorded.
  - Later, node 2 is reached at level 1.
  - The level has already been recorded, so node 2 is skipped.

Result:
  [1, 3]

If we visited left first instead:
  - Node 2 would be recorded first at level 1.
  - Node 3 would be skipped.

Result:
  [1, 2]

That is the left-side view.

The first-node-per-level condition is reusable; the traversal order determines
whether that first node represents the left or right side.


===============================================================================
8. CALL STACK AND RECURSION
===============================================================================

Consider these two calls:

  rightView(root->right, level + 1, ans);
  rightView(root->left, level + 1, ans);

The second statement does not execute until the first recursive call finishes.

For node 1:
  1. Node 1 records itself.
  2. The call for its right child runs to completion.
  3. Control returns to node 1's invocation.
  4. Node 1 then starts the call for its left child.
  5. After the left call finishes, node 1's invocation finishes.

When a child call returns:
  - Control resumes at the statement immediately after that call.
  - The parent's root parameter still refers to the parent node.
  - The shared answer vector keeps its recorded values.
  - The parent does not restart from the beginning.

This is different from Path Sum II, where the traversal also modifies a current
path and running sum that must be restored. Right Side View only appends to
the answer vector; it does not need to undo those recorded answer values.


===============================================================================
9. COMMON MISTAKES AND HOW TO AVOID THEM
===============================================================================

MISTAKE 1: Visiting left before right.

  Why it is wrong for this approach:
    The first node encountered at each level would be the leftmost node.

  Fix:
    Explore the right child before the left child.

MISTAKE 2: Recording every node.

  Why it is wrong:
    The answer needs only one node per depth, not every node.

  Fix:
    Record a node only when level == ans.size().

MISTAKE 3: Starting the root at level 1 while relying on the current condition.

  Why it causes confusion:
    The answer starts empty, so ans.size() is 0. The root would have level 1,
    and the equality condition would fail.

  Fix:
    Start the root at level 0.

MISTAKE 4: Forgetting the nullptr base case.

  Why it is dangerous:
    Accessing root->val when root is nullptr is invalid.

  Fix:
    Return immediately when root == nullptr.

MISTAKE 5: Passing the answer vector by value.

  Why it is inefficient and incorrect for this design:
    Each call would receive its own copy, so additions may not be reflected
    in the caller's vector.

  Fix:
    Pass vector<int>& ans so all calls share the same vector.

MISTAKE 6: Believing that a later node at the same level should replace the
           first node.

  Why it is wrong:
    Right-first traversal deliberately selects the first node at each depth.

  Fix:
    Understand the relationship between traversal order and the equality
    condition instead of trying to overwrite previous answers.


===============================================================================
10. COMPLEXITY ANALYSIS
===============================================================================

Let:
  n = total number of nodes
  h = height of the tree

TIME COMPLEXITY: O(n)

Every node is processed once.
For each node, the function performs a constant amount of work apart from
the recursive calls.

A nullptr call also takes constant time, and a binary tree has a number of
child links proportional to n.

AUXILIARY RECURSION SPACE: O(h)

The deepest chain of active recursive calls is proportional to the height
of the tree.

  Balanced tree:
    h is approximately O(log n).

  Skewed tree:
    h can be O(n).

ANSWER STORAGE: O(h)

There is at most one recorded node per depth, so the answer contains at most
h values.

Therefore:
  Time: O(n)
  Auxiliary call stack: O(h)
  Returned answer: O(h)

When discussing auxiliary space, distinguish the recursion stack from the
space required to return the answer.


===============================================================================
11. ALTERNATIVE APPROACH — BFS
===============================================================================

The same problem can be solved with Breadth-First Search (BFS).

Idea:
  - Use a queue to process one level at a time.
  - For each level, process all nodes in that level.
  - Record the last node processed at that level, assuming children are
    enqueued left first and then right.

Why does it work?
  BFS processes nodes level by level. When children are enqueued left-to-right,
  the last node processed at each level is the rightmost node.

Comparison:

DFS right-first:
  - Uses recursion.
  - Records the first node encountered at each depth.
  - Uses the condition level == ans.size().

BFS left-to-right:
  - Uses a queue.
  - Records the last node processed at each level.
  - Uses a level-size loop.

Both take O(n) time and O(n) worst-case space when queue/stack and output
storage are considered. The DFS auxiliary stack specifically uses O(h) space.


===============================================================================
12. REVISION QUESTIONS
===============================================================================

Try answering these without reading the explanations above.

1. Why is the root assigned level 0?
2. What does ans.size() represent at any point in the traversal?
3. Why does level == ans.size() mean this is the first node recorded at
   that depth?
4. Why do we visit root->right before root->left?
5. What would happen if we swapped the recursive call order?
6. Why is ans passed by reference?
7. Why does a nullptr call return immediately?
8. When the right subtree returns, where does execution resume?
9. Does a child return change the parent's root pointer?
10. What is the time complexity, and why?
11. What is the auxiliary recursion-space complexity?
12. How could BFS solve the same problem?

Expected core explanation:
  "I use right-first DFS. The first node visited at each depth is the
   rightmost node. I record it when level equals ans.size(), because that
   means no node at that depth has been recorded yet."


===============================================================================
13. FINAL LEETCODE SUBMISSION
===============================================================================

This is the concise working solution, ready for LeetCode.

LeetCode supplies the TreeNode definition and required environment.
===============================================================================
*/

class Solution {
private:
    void rightView(TreeNode* root, int level, vector<int>& ans) {
        if (root == nullptr) {
            return;
        }

        if (level == ans.size()) {
            ans.push_back(root->val);
        }

        rightView(root->right, level + 1, ans);
        rightView(root->left, level + 1, ans);
    }

public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;

        rightView(root, 0, ans);

        return ans;
    }
};

/*
===============================================================================
END OF REVISION FILE
===============================================================================
*/
