/*
===============================================================================
DSA JOURNEY — LEETCODE 112: PATH SUM
===============================================================================

Problem: LeetCode 112 — Path Sum
Language: C++
Technique: Recursive DFS, running sum, base cases, state restoration
Session: DSA Day 24
Status: Solved after debugging

This file preserves the user's implementation and documents:
  1. The problem statement
  2. What counts as a valid path
  3. How the recursive calls work
  4. Why the running sum must be restored
  5. The bug from the earlier attempt and how it was fixed
  6. Detailed dry runs
  7. Call-stack behavior
  8. Complexity analysis
  9. Common mistakes
 10. Revision questions

LeetCode provides the TreeNode definition and required standard-library setup.
===============================================================================


===============================================================================
1. PROBLEM STATEMENT
===============================================================================

Given the root of a binary tree and an integer targetSum, return true if the
tree has a root-to-leaf path such that the sum of the node values along that
path equals targetSum. Otherwise, return false.

IMPORTANT DEFINITIONS:

Root-to-leaf path:
  A path that starts at the root and ends at a leaf.

Leaf:
  A node whose left child and right child are both nullptr.

The path must:
  - Start at the root.
  - Follow parent-to-child links.
  - End at a leaf.
  - Have a total sum equal to targetSum.

A matching sum at an internal node is not enough.

Example:

             5
            / \
           4   8
          /   / \
         11  13  4
        /  \       \
       7    2       1

If targetSum = 22, a valid path is:
  5 -> 4 -> 11 -> 2

Its sum is:
  5 + 4 + 11 + 2 = 22

Node 13 alone is not a valid root-to-leaf path from the root, and reaching a
matching partial sum at a non-leaf node would not be enough either.


===============================================================================
2. THE USER'S SOLUTION
===============================================================================

class Solution {
private:
    int currentSum = 0;

public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) {
            return false;
        }

        currentSum += root->val;

        if (root->left == nullptr && root->right == nullptr) {
            bool check = currentSum == targetSum;
            currentSum -= root->val;
            return check;
        }

        bool leftAns = hasPathSum(root->left, targetSum);
        bool rightAns = hasPathSum(root->right, targetSum);

        currentSum -= root->val;
        return leftAns || rightAns;
    }
};

This implementation uses a class member called currentSum to track the sum of
the active root-to-current-node path.

IMPORTANT DESIGN NOTE:
  Because currentSum is a class member, it is shared by all recursive calls.
  Every invocation must restore the contribution it adds before it returns.
  If a helper receives the running sum as a normal parameter instead, the
  value is local to that invocation and does not need to be manually restored
  in the caller's variable. Both designs can work when implemented correctly.


===============================================================================
3. UNDERSTANDING THE STATE
===============================================================================

The key variable is:

  int currentSum = 0;

At any point during the traversal, currentSum is intended to equal the sum of
the values on the current root-to-node path.

Suppose the current path is:

  5 -> 4 -> 11

Then:

  currentSum = 5 + 4 + 11 = 20

When we move to child 7:
  currentSum becomes 27.

When the recursive call for node 7 finishes:
  Its contribution must be removed, restoring currentSum to 20.

Then the traversal can explore node 2:
  currentSum becomes 22.

This is how the same running-sum variable can safely be reused across branches.

The important invariant is:
  When a recursive call finishes, currentSum must be restored to the value
  that existed before that call added its own node value.


===============================================================================
4. LINE-BY-LINE EXPLANATION
===============================================================================

A. CLASS MEMBER

  int currentSum = 0;

  Stores the running sum for the current root-to-node path.

  Because it is a member variable, all recursive calls on this Solution
  instance access the same variable.

B. FUNCTION SIGNATURE

  bool hasPathSum(TreeNode* root, int targetSum)

  Returns:
    true  -> a valid root-to-leaf path exists.
    false -> no valid root-to-leaf path exists.

C. NULLPTR BASE CASE

  if (root == nullptr) {
      return false;
  }

  If there is no node, there is no path through that call.

  Notice that this case returns before adding any value to currentSum.
  Therefore, a nullptr call has no contribution to undo.

D. ADD THE CURRENT NODE

  currentSum += root->val;

  Include the current node's value in the active path sum.

E. LEAF CHECK

  if (root->left == nullptr && root->right == nullptr)

  This condition is true only when both children are absent.

  Only a leaf can complete a valid root-to-leaf path.

F. CHECK THE SUM

  bool check = currentSum == targetSum;

  Save the result of the comparison in a boolean variable.

  Why save it?
    The next statement changes currentSum, but the result of the comparison
    must remain available for the return.

G. RESTORE THE LEAF CONTRIBUTION

  currentSum -= root->val;

  Remove this leaf's contribution before returning.

  This is necessary because currentSum is shared across recursive calls.

H. RETURN THE SAVED RESULT

  return check;

  The function returns whether the path ending at this leaf matched the target.

I. EXPLORE THE LEFT SUBTREE

  bool leftAns = hasPathSum(root->left, targetSum);

  This recursively checks whether the left subtree contains a valid path.

  When this call returns, execution resumes at the next statement in the
  current invocation.

J. EXPLORE THE RIGHT SUBTREE

  bool rightAns = hasPathSum(root->right, targetSum);

  This checks the right subtree.

  The left call and right call are separate recursive calls. The state must
  be correctly restored so that one branch does not contaminate the other.

K. RESTORE THE CURRENT INTERNAL NODE

  currentSum -= root->val;

  Both child calls have finished. Now remove the current internal node's
  contribution before this invocation returns.

L. COMBINE THE ANSWERS

  return leftAns || rightAns;

  If either subtree contains a valid root-to-leaf path, the result is true.

  Because leftAns and rightAns have already been calculated, this expression
  combines their results. It does not skip the earlier recursive call.


===============================================================================
5. WHY THE EARLIER ATTEMPT FAILED
===============================================================================

During the first attempt, currentSum was shared across recursive calls, but
the current node's contribution was not reliably restored.

This can contaminate one branch with values from another branch.

Imagine this tree:

        1
       / \
     -2  -3
     / \
    1   3
   /
 -1

The target is 3.

If values from one branch remain in currentSum while another branch is
explored, the sum can accidentally match the target even when no single
root-to-leaf path has that sum.

The problem is not that recursion is inherently unsafe. The problem is that
the shared mutable state must match the active path at every point.

HOW THE SOLUTION WAS IMPROVED:

  1. Add the current node's value.
  2. If the node is a leaf:
       - Compare the current sum with targetSum.
       - Save the comparison result.
       - Undo the leaf's contribution.
       - Return the saved result.
  3. Otherwise:
       - Check the left subtree.
       - Check the right subtree.
       - Undo the current internal node's contribution.
       - Return whether either subtree found a valid path.

This keeps the running sum aligned with the current recursive path.


===============================================================================
6. DETAILED DRY RUN — VALID PATH
===============================================================================

Tree:

             5
            / \
           4   8
          /   / \
         11  13  4
        /  \       \
       7    2       1

targetSum = 22

Focus first on the path:
  5 -> 4 -> 11 -> 2

Start:
  currentSum = 0

CALL FOR NODE 5:
  Add 5:
    currentSum = 5

  Node 5 is not a leaf.
  Call left child 4.

CALL FOR NODE 4:
  Add 4:
    currentSum = 9

  Node 4 is not a leaf.
  Call left child 11.

CALL FOR NODE 11:
  Add 11:
    currentSum = 20

  Node 11 is not a leaf.
  Call left child 7.

CALL FOR NODE 7:
  Add 7:
    currentSum = 27

  Node 7 is a leaf.
  Compare:
    27 == 22 -> false

  Save:
    check = false

  Restore node 7:
    currentSum = 27 - 7 = 20

  Return false to node 11.

BACK IN NODE 11:
  The left call has finished.
  Call right child 2.

CALL FOR NODE 2:
  Add 2:
    currentSum = 20 + 2 = 22

  Node 2 is a leaf.
  Compare:
    22 == 22 -> true

  Save:
    check = true

  Restore node 2:
    currentSum = 22 - 2 = 20

  Return true to node 11.

BACK IN NODE 11:
  leftAns = false
  rightAns = true

  Restore node 11:
    currentSum = 20 - 11 = 9

  Return:
    false || true -> true

BACK IN NODE 4:
  The left subtree returned true.

  Now the function evaluates the right child of node 4, which is nullptr.
  The nullptr call returns false without changing currentSum.

  Restore node 4:
    currentSum = 9 - 4 = 5

  Return:
    true || false -> true

BACK IN NODE 5:
  The left subtree returned true.

  The function also evaluates the right subtree.
  After that call finishes, node 5 restores its contribution before returning.

The overall result is true because at least one root-to-leaf path matches
targetSum.

NOTE:
  This code evaluates both child calls before combining their results.
  It does not short-circuit the traversal merely because leftAns is true.


===============================================================================
7. CALL STACK — WHAT HAPPENS WHEN A CHILD RETURNS?
===============================================================================

Suppose node 2 is currently being processed as the right child of node 11.

When node 2 reaches its leaf case:
  1. It computes check.
  2. It restores node 2's contribution.
  3. It returns check.

Control returns to node 11 immediately after the statement that called node 2.

Node 11's root parameter still points to node 11.
The function does not restart from the beginning.

Node 11 then:
  1. Has both child results.
  2. Restores node 11's contribution.
  3. Returns its combined boolean result.

Control then resumes in node 4.

CRUCIAL RULE:
  A child call restores only the contribution it is responsible for.
  The parent must restore its own contribution when its own execution reaches
  the appropriate restoration statement.

This is the same call-stack principle used in Path Sum II. The difference is
that Path Sum II also stores a mutable vector representing the current path.


===============================================================================
8. DRY RUN — SINGLE NODE
===============================================================================

Tree:
  1

Target:
  1

Initial:
  currentSum = 0

Enter hasPathSum(node 1, target 1):
  Add node value:
    currentSum = 1

Both children are nullptr, so node 1 is a leaf.

Compare:
  currentSum == targetSum
  1 == 1 -> true

Save:
  check = true

Restore:
  currentSum = 1 - 1 = 0

Return:
  true

This demonstrates why the boolean result is saved before restoring the sum.


===============================================================================
9. DRY RUN — EMPTY TREE
===============================================================================

root = nullptr
targetSum = any value

The first condition is true:

  if (root == nullptr)

The function returns false immediately.

currentSum is unchanged because no node value was added.

An empty tree cannot contain a root-to-leaf path.


===============================================================================
10. WHY THE LEAF CONDITION MATTERS
===============================================================================

Suppose a node's current sum equals targetSum, but that node has children.

That does not yet establish a valid answer.

The path must end at a leaf.

For example:

       1
      /
     2
    /
   3

If the target is 3, the sum at node 2 is 3, but node 2 is not a leaf.
The path must continue to node 3.

The full root-to-leaf sum is:
  1 + 2 + 3 = 6

Therefore, the matching partial sum at node 2 must not be accepted as a
complete path.


===============================================================================
11. COMMON MISTAKES
===============================================================================

MISTAKE 1:
  Forgetting to restore currentSum after a leaf is processed.

WHY IT IS WRONG:
  The next recursive branch may inherit a sum containing values from the
  previous branch.

MISTAKE 2:
  Restoring a node's value more than once.

WHY IT IS WRONG:
  The running sum no longer represents the current path.

MISTAKE 3:
  Returning true as soon as the sum matches at any node.

WHY IT IS WRONG:
  A valid path must end at a leaf.

MISTAKE 4:
  Forgetting the nullptr base case.

WHY IT IS WRONG:
  The code might try to read root->val from a null pointer.

MISTAKE 5:
  Assuming that a child return restores the parent's state.

WHY IT IS WRONG:
  Each recursive call has its own execution point. The parent must restore
  the contribution that it added.

MISTAKE 6:
  Forgetting that currentSum is a class member.

WHY IT MATTERS:
  It is shared by all recursive invocations using this Solution instance.
  It is not an independent local variable for every call.

DESIGN IMPROVEMENT TO CONSIDER LATER:
  Passing a sum or remaining target as a function parameter can avoid shared
  mutable state. This is an alternative design to study, not a requirement
  for understanding the accepted implementation.


===============================================================================
12. COMPLEXITY ANALYSIS
===============================================================================

Let:
  n = total number of nodes
  h = height of the tree

TIME COMPLEXITY: O(n)

In the worst case, the function visits every node once.

Each node performs a constant amount of work:
  - Add its value.
  - Check whether it is a leaf.
  - Make recursive calls.
  - Restore its contribution.
  - Combine boolean results.

Therefore, time complexity is O(n).

AUXILIARY SPACE COMPLEXITY: O(h)

The recursion stack contains at most a root-to-leaf chain of active calls.

For a balanced tree:
  h is O(log n).

For a highly skewed tree:
  h can be O(n).

The algorithm uses O(h) auxiliary recursion-stack space.

The algorithm does not construct a separate output list of paths, so there
is no additional result matrix in this problem.


===============================================================================
13. REVISION CHECKLIST
===============================================================================

Before moving on, make sure you can explain:

[ ] What exactly qualifies as a root-to-leaf path?
[ ] Why is a nullptr call false?
[ ] Why is the node value added before checking the leaf?
[ ] Why is the boolean result saved before restoring currentSum?
[ ] Why does a leaf restore its contribution before returning?
[ ] Why must an internal node restore its contribution after its children?
[ ] How could a shared sum contaminate a sibling branch?
[ ] Where does execution resume after a recursive child returns?
[ ] Why is a matching partial sum at an internal node insufficient?
[ ] Why is the time complexity O(n)?
[ ] Why is the recursion-stack space O(h)?

ONE-SENTENCE INTERVIEW SUMMARY:

"I use DFS with a running sum. I add each node's value, check the target only
at leaf nodes, restore the current node's contribution before its call
finishes, and return true if either subtree contains a valid root-to-leaf path."


===============================================================================
14. FINAL LEETCODE SUBMISSION
===============================================================================

This is the user's original working implementation.

LeetCode supplies TreeNode and the required environment.
===============================================================================
*/

class Solution {
private:
    int currentSum = 0;

public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) {
            return false;
        }

        currentSum += root->val;

        if (root->left == nullptr && root->right == nullptr) {
            bool check = currentSum == targetSum;
            currentSum -= root->val;
            return check;
        }

        bool leftAns = hasPathSum(root->left, targetSum);
        bool rightAns = hasPathSum(root->right, targetSum);

        currentSum -= root->val;
        return leftAns || rightAns;
    }
};

/*
===============================================================================
END OF REVISION FILE
===============================================================================
*/
