/*
===============================================================================
Problem Name   : Same Tree
LeetCode ID    : 100
Topic          : Binary Trees, Recursion, Depth-First Search (DFS)
Difficulty     : Easy
Day            : Day 20
Language       : C++
Status         : Solution implemented; submission status not recorded
===============================================================================

PROBLEM LINK:
https://leetcode.com/problems/same-tree/

-------------------------------------------------------------------------------
1. PROBLEM STATEMENT
-------------------------------------------------------------------------------

Given the roots of two binary trees, p and q, write a function to determine
whether the two trees are the same.

Two binary trees are considered the same if:

1. They have the same structure.
2. The corresponding nodes have the same values.

Return true if both trees are identical; otherwise, return false.

IMPORTANT:
Comparing only the root values is insufficient. The corresponding left and
right subtrees must also have identical structures and values.

-------------------------------------------------------------------------------
2. EXAMPLES
-------------------------------------------------------------------------------

Example 1:

Tree P:                 Tree Q:

       1                       1
      / \                     / \
     2   3                   2   3

Output:
true

Explanation:
Both trees have the same structure, and all corresponding node values match.


Example 2:

Tree P:                 Tree Q:

       1                       1
      /                         \
     2                           2

Output:
false

Explanation:
The node with value 2 is the left child in Tree P but the right child in
Tree Q. Therefore, the structures differ.


Example 3:

Tree P:                 Tree Q:

       1                       1
      / \                     / \
     2   1                   1   2

Output:
false

Explanation:
The structures are the same, but the corresponding child values differ.


Example 4:

Tree P: nullptr          Tree Q: nullptr

Output:
true

Explanation:
Both trees are empty, so they have the same structure and values.

-------------------------------------------------------------------------------
3. INITIAL UNDERSTANDING
-------------------------------------------------------------------------------

This problem introduces recursive comparison of two binary trees.

Unlike Maximum Depth of Binary Tree, which calculates a result for one tree,
this problem compares two trees at the same time.

At each recursive call, the function receives two pointers:

    TreeNode* p
    TreeNode* q

These pointers identify the corresponding nodes currently being compared.

The function must determine:

1. Whether both current nodes are empty.
2. Whether only one current node is empty.
3. Whether the current node values differ.
4. Whether the corresponding left subtrees are identical.
5. Whether the corresponding right subtrees are identical.

The overall result depends on all corresponding parts of both trees.

-------------------------------------------------------------------------------
4. APPROACH: RECURSIVE TREE COMPARISON
-------------------------------------------------------------------------------

The solution uses recursion to compare corresponding nodes in both trees.

STEP 1: BOTH POINTERS ARE NULL

Condition:

    p == nullptr && q == nullptr

Return:

    true

Explanation:

Both corresponding positions are empty. Neither tree has an additional
node at this position, so these subtrees match.

This is a base case that terminates recursion successfully.

STEP 2: ONLY ONE POINTER IS NULL

Condition:

    p == nullptr || q == nullptr

Return:

    false

Explanation:

If execution reaches this condition, the previous base case has already
established that the pointers are not both null.

Therefore, exactly one pointer is null.

One tree has a node where the other tree has no node, meaning their
structures differ.

This check must occur before accessing p->val or q->val.

STEP 3: COMPARE NODE VALUES

Condition:

    p->val != q->val

Return:

    false

Explanation:

If the current node values differ, the trees cannot be identical.

There is no need to compare their remaining subtrees after this mismatch.

STEP 4: COMPARE THE LEFT SUBTREES

Call:

    isSameTree(p->left, q->left)

Store the result in a Boolean variable named left.

The recursive call determines whether the corresponding left subtrees
have identical structures and values.

STEP 5: COMPARE THE RIGHT SUBTREES

Call:

    isSameTree(p->right, q->right)

Store the result in a Boolean variable named right.

The recursive call determines whether the corresponding right subtrees
have identical structures and values.

STEP 6: COMBINE THE RESULTS

Return:

    left && right

Explanation:

The logical AND operator returns true only when both operands are true.

Therefore:

    left = true,  right = true  -> true
    left = true,  right = false -> false
    left = false, right = true  -> false
    left = false, right = false -> false

The current node values have already been checked, so if both subtree
comparisons succeed, the two current subtrees are identical.

-------------------------------------------------------------------------------
5. FINAL SOLUTION
-------------------------------------------------------------------------------

*/

#include <iostream>

using namespace std;

/*
NOTE ABOUT LEETCODE:

LeetCode provides the TreeNode structure automatically.

This definition is included to make the file self-contained. When submitting
to LeetCode, use the platform-provided TreeNode definition rather than
declaring the structure a second time.
*/

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {

        // Base case 1: both corresponding nodes are empty.
        if (p == nullptr && q == nullptr) {
            return true;
        }

        // Base case 2: only one corresponding node is empty.
        if (p == nullptr || q == nullptr) {
            return false;
        }

        // If current node values differ, the trees are not identical.
        if (p->val != q->val) {
            return false;
        }

        // Compare the corresponding left subtrees.
        bool left = isSameTree(p->left, q->left);

        // Compare the corresponding right subtrees.
        bool right = isSameTree(p->right, q->right);

        // Both subtrees must match.
        return left && right;
    }
};

/*
-------------------------------------------------------------------------------
6. STEP-BY-STEP EXECUTION
-------------------------------------------------------------------------------

Consider two trees:

Tree P:                 Tree Q:

        1                       1
       / \                     / \
      2   3                   2   3
     /                           /
    4                           4

Both trees have the same structure and corresponding node values.

INITIAL CALL:

    isSameTree(P_root, Q_root)

Both pointers reference nodes with value 1.

1. Neither pointer is null.
2. Their values match.
3. The function compares their left subtrees.
4. The function compares their right subtrees.

LEFT SUBTREE:

    isSameTree(P_node_2, Q_node_2)

Both current node values are 2.

The function recursively compares their left children.

LEFT CHILD OF NODE 2:

    isSameTree(P_node_4, Q_node_4)

Both node values are 4.

Their left children are both nullptr:

    isSameTree(nullptr, nullptr) -> true

Their right children are also both nullptr:

    isSameTree(nullptr, nullptr) -> true

Therefore:

    left  = true
    right = true

    return left && right
    return true

The recursive call for node 4 returns true.

BACK AT NODE 2:

The left-subtree comparison returns true.

The right children of both node-2 nodes are nullptr:

    isSameTree(nullptr, nullptr) -> true

Therefore:

    left  = true
    right = true

    return true

RIGHT SUBTREE OF THE ROOT:

    isSameTree(P_node_3, Q_node_3)

Both node values are 3.

Their left children are both nullptr, and their right children are both
nullptr. Both recursive comparisons return true.

Therefore, the comparison at node 3 returns true.

FINAL RESULT AT THE ROOT:

    left  = true
    right = true

    return left && right
    return true

Final answer: true

IMPORTANT OBSERVATION:

The recursive calls compare corresponding positions, not just the values
that appear somewhere in the trees. This is how the algorithm verifies
both structure and node values.

-------------------------------------------------------------------------------
7. ISSUES ENCOUNTERED AND HOW THEY WERE RESOLVED
-------------------------------------------------------------------------------

ISSUE 1: ASSUMING THE TREES HAVE THE SAME NUMBER OF NODES

Initial challenge:
Initially, it was tempting to consider the case where both pointers are
nullptr and assume the trees would have matching lengths.

However, two trees may contain different numbers of nodes.

Resolution:
Handle both situations explicitly:

    if (p == nullptr && q == nullptr) {
        return true;
    }

    if (p == nullptr || q == nullptr) {
        return false;
    }

The first condition handles two empty positions. The second handles
structural mismatches.

ISSUE 2: ACCESSING NODE VALUES WHEN A POINTER MAY BE NULL

Initial challenge:
The node values cannot safely be compared until the code establishes that
both pointers reference actual nodes.

Resolution:
Check the null-pointer cases before evaluating:

    p->val != q->val

This prevents dereferencing a null pointer.

ISSUE 3: COMPARING ONLY THE CURRENT NODE VALUES

Initial challenge:
Matching root values do not prove that two trees are identical.

Resolution:
Recursively compare the left subtrees and the right subtrees.

The recursive calls apply the same checks to every corresponding position.

ISSUE 4: RETURNING AFTER ONLY THE LEFT-SUBTREE COMPARISON

Initial challenge:
A return statement immediately exits the current function call. Returning
the result of the left comparison alone would prevent that function call
from checking its right subtree.

Resolution:
Store both recursive results:

    bool left = isSameTree(p->left, q->left);
    bool right = isSameTree(p->right, q->right);

Then combine them:

    return left && right;

This ensures that both comparisons contribute to the final result.

ISSUE 5: UNDERSTANDING THE LOGICAL AND OPERATOR

Initial challenge:
Both subtree comparisons must succeed, but a single Boolean result must
be returned from the function.

Resolution:
The logical AND operator expresses the requirement directly:

    left && right

It evaluates to true only if both values are true.

KEY LEARNING:
Each recursive call returns a Boolean answer about its own pair of subtrees.
The parent combines the two answers after checking its own node values.

-------------------------------------------------------------------------------
8. EDGE CASES
-------------------------------------------------------------------------------

CASE 1: BOTH TREES ARE EMPTY

p = nullptr
q = nullptr

Expected output:
true

Reason:
Both pointers are null, so the first base case returns true.

CASE 2: ONLY THE FIRST TREE IS EMPTY

p = nullptr
q = a valid node

Expected output:
false

Reason:
The structures differ.

CASE 3: ONLY THE SECOND TREE IS EMPTY

p = a valid node
q = nullptr

Expected output:
false

Reason:
The structures differ.

CASE 4: DIFFERENT ROOT VALUES

Tree P: 1
Tree Q: 2

Expected output:
false

Reason:
The current node values differ.

CASE 5: IDENTICAL SINGLE-NODE TREES

Tree P: 1
Tree Q: 1

Expected output:
true

Reason:
The root values match, and both corresponding children are null.

CASE 6: IDENTICAL MULTI-LEVEL TREES

Both trees contain the same structure and the same value at every
corresponding node.

Expected output:
true

Reason:
Every node comparison and every subtree comparison succeeds.

CASE 7: SAME VALUES, DIFFERENT STRUCTURES

Tree P:                 Tree Q:

        1                       1
       /                         \
      2                           2

Expected output:
false

Reason:
The node with value 2 occupies different positions.

CASE 8: DIFFERENT VALUE IN A DEEPER NODE

Tree P:                 Tree Q:

        1                       1
       / \                     / \
      2   3                   2   3
     /                           /
    4                           5

Expected output:
false

Reason:
The recursive comparison eventually reaches nodes 4 and 5, whose values
differ.

-------------------------------------------------------------------------------
9. COMPLEXITY ANALYSIS
-------------------------------------------------------------------------------

Let:

    N  = number of nodes in tree P
    M  = number of nodes in tree Q
    H1 = height of tree P
    H2 = height of tree Q

TIME COMPLEXITY:

    O(min(N, M))

In the worst case, the algorithm examines all corresponding nodes of the
smaller tree before it can determine the result.

If the trees are identical, they necessarily have the same number of nodes,
and every node is compared. The time complexity is then Theta(N), where
N = M.

If the algorithm discovers a mismatching node value or structure earlier,
it may return before examining all nodes.

AUXILIARY SPACE COMPLEXITY:

    O(min(H1, H2))

The algorithm uses recursive calls, so its auxiliary space is determined
by the maximum depth of the active recursive call stack.

The calls continue down corresponding paths while both current pointers
are non-null. The stack depth is therefore bounded by the smaller of the
two tree heights, up to constant differences in how height is counted.

For balanced trees of comparable size:

    O(log N)

For skewed trees of comparable size:

    O(N)

The solution does not create a separate collection to store the nodes.

-------------------------------------------------------------------------------
10. KEY LEARNINGS
-------------------------------------------------------------------------------

1. Recursive tree problems can involve one tree or multiple trees.

2. When comparing two trees, each recursive call receives a corresponding
   pair of nodes.

3. Both-null and one-null cases have different meanings.

4. Null-pointer checks must occur before accessing node values.

5. Matching current node values is necessary but not sufficient.

6. Both the left and right subtrees must be compared.

7. A Boolean variable can store the result of a recursive call.

8. The logical AND operator combines conditions that must all be true.

9. A return statement exits the current function call immediately.

10. Recursive results propagate back to callers, allowing each pair of
    subtrees to contribute to the final answer.

-------------------------------------------------------------------------------
11. FINAL SUMMARY
-------------------------------------------------------------------------------

Problem:
    LeetCode 100 - Same Tree

Approach:
    Recursive Depth-First Search (DFS)

Main checks:
    1. Both pointers are nullptr.
    2. Exactly one pointer is nullptr.
    3. Current node values differ.
    4. Corresponding left subtrees.
    5. Corresponding right subtrees.

Final combination:
    return left && right;

Time Complexity:
    O(min(N, M))

Auxiliary Space Complexity:
    O(min(H1, H2))

Main concept learned:
    Two binary trees are identical only when their corresponding node
    values and structures match throughout both trees.

===============================================================================
END OF FILE
===============================================================================
*/