/*
===============================================================================
Problem Name   : Maximum Depth of Binary Tree
LeetCode ID    : 104
Topic          : Binary Trees, Recursion, Depth-First Search (DFS)
Difficulty     : Easy
Day            : Day 20
Language       : C++
Status         : Accepted
===============================================================================

PROBLEM LINK:
https://leetcode.com/problems/maximum-depth-of-binary-tree/

-------------------------------------------------------------------------------
1. PROBLEM STATEMENT
-------------------------------------------------------------------------------

Given the root of a binary tree, return its maximum depth.

The maximum depth of a binary tree is the number of nodes along the longest
path from the root node down to the farthest leaf node.

A leaf node is a node that has no left or right child.

-------------------------------------------------------------------------------
2. EXAMPLES
-------------------------------------------------------------------------------

Example 1:

Input:
        3
       / 
      9   20
          / 
         15  7

Output:
3

Explanation:
The longest path from the root to a leaf contains three nodes.

One such path is:
3 -> 20 -> 15

Therefore, the maximum depth is 3.


Example 2:

Input:
        1
         
          2

Output:
2

Explanation:
The longest path contains two nodes: 1 -> 2.

Therefore, the maximum depth is 2.


Example 3:

Input:
nullptr

Output:
0

Explanation:
An empty binary tree has a maximum depth of 0.

-------------------------------------------------------------------------------
3. INITIAL UNDERSTANDING
-------------------------------------------------------------------------------

This problem introduced the fundamentals of recursive problem-solving on
binary trees.

The main questions were:

1. What should happen when the current node is nullptr?
2. How can the maximum depth of a tree be calculated using its subtrees?
3. What do the recursive calls return?
4. How do the returned values help calculate the answer for the current node?

The key observation is that the maximum depth of a non-empty binary tree
depends on the maximum depth of its left and right subtrees.

We do not need to calculate the entire tree's depth in a single operation.
Instead, each node calculates its answer using the results returned by its
children.

-------------------------------------------------------------------------------
4. APPROACH: RECURSION
-------------------------------------------------------------------------------

The solution uses recursion to calculate the maximum depth.

STEP 1: BASE CASE

If root == nullptr, return 0.

A null pointer represents an empty subtree. An empty subtree contributes
zero nodes to the depth.

This condition also ensures that recursion eventually terminates when
the traversal reaches a missing child.

STEP 2: CALCULATE THE LEFT SUBTREE DEPTH

Call maxDepth(root->left).

The recursive call calculates and returns the maximum depth of the left
subtree.

Store the returned value in leftMaxDepth.

STEP 3: CALCULATE THE RIGHT SUBTREE DEPTH

Call maxDepth(root->right).

The recursive call calculates and returns the maximum depth of the right
subtree.

Store the returned value in rightMaxDepth.

STEP 4: CALCULATE THE CURRENT NODE'S DEPTH

Compare the depths of the two subtrees and select the larger one.

Add 1 to account for the current node.

Formula:

maximum depth =
    1 + max(left subtree depth, right subtree depth)

The additional 1 represents the current node itself.

STEP 5: RETURN THE RESULT

Return the calculated depth to the previous recursive call.

Each node performs the same calculation until the original call returns
the maximum depth of the entire tree.

-------------------------------------------------------------------------------
5. FINAL SOLUTION
-------------------------------------------------------------------------------

*/

#include <algorithm>

using namespace std;

/*
NOTE ABOUT LEETCODE:

LeetCode provides the TreeNode structure automatically.

The following definition is included here so that this file is self-contained
and can be compiled independently. When submitting to LeetCode, use its
provided TreeNode definition instead of defining TreeNode a second time.
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
    int maxDepth(TreeNode* root) {

        // Base case: an empty subtree has depth zero.
        if (root == nullptr) {
            return 0;
        }

        // Calculate the maximum depth of the left subtree.
        int leftMaxDepth = maxDepth(root->left);

        // Calculate the maximum depth of the right subtree.
        int rightMaxDepth = maxDepth(root->right);

        // Include the current node and select the deeper subtree.
        return max(leftMaxDepth, rightMaxDepth) + 1;
    }
};

/*
-------------------------------------------------------------------------------
6. STEP-BY-STEP EXECUTION
-------------------------------------------------------------------------------

Consider the following binary tree:

             1
            / \
           2   3
          /     \
         4       5

The maximum depth is 3.

Execution begins with:

maxDepth(root)

The function receives the root node with value 1.

At node 1:
    The function recursively calculates the left subtree depth.
    It also recursively calculates the right subtree depth.

At node 2:
    Its left child is node 4.
    Its right child is nullptr.

At node 4:
    Both children are nullptr.
    Each null child returns 0.

    Depth of node 4:
        max(0, 0) + 1 = 1

Back at node 2:
    leftMaxDepth  = 1
    rightMaxDepth = 0

    Depth of node 2:
        max(1, 0) + 1 = 2

At node 3:
    Its left child is nullptr.
    Its right child is node 5.

At node 5:
    Both children are nullptr.

    Depth of node 5:
        max(0, 0) + 1 = 1

Back at node 3:
    leftMaxDepth  = 0
    rightMaxDepth = 1

    Depth of node 3:
        max(0, 1) + 1 = 2

Finally, back at node 1:
    leftMaxDepth  = 2
    rightMaxDepth = 2

    Depth of node 1:
        max(2, 2) + 1 = 3

Final answer: 3

IMPORTANT OBSERVATION:

The recursive calls first reach the base cases. Their return values then
propagate back through the call stack, allowing each parent node to
calculate its own depth.

-------------------------------------------------------------------------------
7. ISSUES ENCOUNTERED AND HOW THEY WERE RESOLVED
-------------------------------------------------------------------------------

ISSUE 1: UNDERSTANDING THE BASE CASE

Initial challenge:
Understanding what should happen when a recursive call reaches nullptr.

Resolution:
An empty subtree contributes zero nodes to the depth, so the base case is:

    if (root == nullptr) {
        return 0;
    }

This also terminates the recursion.

ISSUE 2: UNDERSTANDING RECURSIVE RETURN VALUES

Initial challenge:
Understanding how recursive calls calculate a result and pass it back to
their callers.

Resolution:
Each call returns the maximum depth of its own subtree. The parent receives
those results and uses them to calculate its depth.

ISSUE 3: COMBINING LEFT AND RIGHT SUBTREE RESULTS

Initial challenge:
Understanding why the solution compares both subtree depths instead of
simply choosing one side.

Resolution:
The longest path may go through either the left or right subtree. Therefore,
the larger depth must be selected:

    max(leftMaxDepth, rightMaxDepth)

ISSUE 4: COUNTING THE CURRENT NODE

Initial challenge:
Understanding why the formula adds 1 to the larger subtree depth.

Resolution:
The subtree result does not include the current parent node. Adding 1
counts that node as part of the path.

ISSUE 5: UNDERSTANDING RECURSION ON A TREE

Initial challenge:
Understanding how the function processes a tree without explicitly
traversing it using a loop.

Resolution:
Every recursive call processes one node and delegates the calculation of
its left and right subtrees to further calls. The call stack keeps track of
unfinished calculations until their results are returned.

NOTE:
These were the principal conceptual challenges addressed while learning
tree recursion. They are learning observations, not claims that the
accepted implementation contained these bugs.

-------------------------------------------------------------------------------
8. EDGE CASES
-------------------------------------------------------------------------------

CASE 1: EMPTY TREE

Input:
nullptr

Output:
0

Reason:
The base case immediately returns 0.

CASE 2: SINGLE NODE

Input:
    1

Output:
1

Reason:
Both children are nullptr.

    max(0, 0) + 1 = 1

CASE 3: LEFT-SKEWED TREE

Input:
        1
       /
      2
     /
    3

Output:
3

Reason:
The longest path contains three nodes.

CASE 4: RIGHT-SKEWED TREE

Input:
    1
     
      2
       
        3

Output:
3

Reason:
The longest path contains three nodes.

CASE 5: BALANCED TREE

Input:
        1
       / 
      2   3
     / 
    4   5

Output:
3

Reason:
The longest path contains three nodes.

CASE 6: DIFFERENT SUBTREE DEPTHS

Input:
        1
       /
      2
     /
    3

Output:
3

Reason:
The left subtree is deeper than the right subtree. The maximum is selected,
and the current node is added to that depth.

-------------------------------------------------------------------------------
9. COMPLEXITY ANALYSIS
-------------------------------------------------------------------------------

Let:

    n = number of nodes in the binary tree
    h = height of the binary tree

TIME COMPLEXITY: O(n)

Each node is processed once. At each node, the function performs constant
work apart from its recursive calls.

Therefore, the total running time is O(n).

A tighter bound for a non-empty tree is Theta(n), since every node must be
visited to determine the maximum depth in the general case.

AUXILIARY SPACE COMPLEXITY: O(h)

The recursive call stack can contain up to h active calls along a path
from the root toward a leaf.

For a balanced binary tree:

    h = O(log n)

Therefore, auxiliary stack space is O(log n).

For a completely skewed binary tree:

    h = O(n)

Therefore, auxiliary stack space can be O(n).

The recursive implementation does not create a separate array, vector, or
other data structure proportional to the number of nodes.

-------------------------------------------------------------------------------
10. KEY LEARNINGS
-------------------------------------------------------------------------------

1. A binary tree can be processed recursively by solving the same problem
   on its left and right subtrees.

2. Every recursive function needs a correct stopping condition.

3. A nullptr represents an empty subtree.

4. Recursive calls return results to their immediate callers.

5. A parent node can combine the results returned by its children.

6. The maximum depth formula is:

       maxDepth(root) =
           0                                      if root == nullptr
           1 + max(maxDepth(root->left),
                   maxDepth(root->right))          otherwise

7. The call stack manages recursive execution and return values.

8. Time complexity and auxiliary space complexity describe different costs:
   processing every node takes O(n) time, while recursive stack space
   depends on the tree's height.

9. A recursive solution can be concise while still requiring careful
   understanding of base cases, return values, and the call stack.

-------------------------------------------------------------------------------
11. FINAL RESULT
-------------------------------------------------------------------------------

Problem:
    LeetCode 104 - Maximum Depth of Binary Tree

Approach:
    Recursive Depth-First Search (DFS)

Result:
    Accepted

Time Complexity:
    O(n)

Auxiliary Space Complexity:
    O(h), worst case O(n)

Main concept learned:
    Calculate the result for a node using the results returned by its
    left and right subtrees.

===============================================================================
END OF FILE
===============================================================================
*/