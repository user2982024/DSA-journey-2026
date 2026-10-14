/*
===============================================================================
Problem Name   : Invert Binary Tree
LeetCode ID    : 226
Topic          : Binary Trees, Recursion, Depth-First Search (DFS), Pointers
Difficulty     : Easy
Day            : Day 20
Language       : C++
Status         : Accepted
===============================================================================

PROBLEM LINK:
https://leetcode.com/problems/invert-binary-tree/

-------------------------------------------------------------------------------
1. PROBLEM STATEMENT
-------------------------------------------------------------------------------

Given the root of a binary tree, invert the tree and return its root.

Inverting a binary tree means swapping the left and right child pointers
of every node in the tree.

For example, if a node originally has:
    - A left child with value 2
    - A right child with value 7

After inversion:
    - Its left child will be the original right child.
    - Its right child will be the original left child.

The inversion must be performed throughout the entire tree.

IMPORTANT:
The task is to change the tree's structure by swapping child pointers.
It is not asking us to swap the values stored inside the nodes.

-------------------------------------------------------------------------------
2. EXAMPLES
-------------------------------------------------------------------------------

Example 1:

Input:

             4
            / \
           2   7
          / \ / \
         1  3 6  9

Output:

             4
            / \
           7   2
          / \ / \
         9  6 3  1

Explanation:
The left and right child pointers of every node are swapped.

Example 2:

Input:

        2
       / \
      1   3

Output:

        2
       / \
      3   1

Example 3:

Input:
nullptr

Output:
nullptr

Explanation:
An empty tree remains empty after inversion.

Example 4:

Input:

    1
   /
  2

Output:

    1
     \
      2

Explanation:
The existing left child moves to the right side, and the left child
becomes nullptr.

-------------------------------------------------------------------------------
3. INITIAL UNDERSTANDING
-------------------------------------------------------------------------------

The problem involves modifying a binary tree recursively.

At each non-null node, we must:
    1. Invert the left subtree.
    2. Invert the right subtree.
    3. Swap the node's left and right child pointers.

The process is repeated for every node in the tree.

The key observation is that each node can be inverted independently once
its child subtrees have been processed.

The same recursive function can be applied to every subtree.

-------------------------------------------------------------------------------
4. APPROACH: RECURSION AND POINTER SWAPPING
-------------------------------------------------------------------------------

STEP 1: HANDLE THE BASE CASE

Condition:

    if (root == nullptr)

Return:

    return root;

Explanation:
If the current pointer is nullptr, there is no node to invert.

Returning root returns nullptr in this case and terminates that recursive
branch.

STEP 2: INVERT THE LEFT SUBTREE

Call:

    invertTree(root->left);

This recursively inverts the entire left subtree.

When the recursive call finishes, execution resumes in the current call.

STEP 3: INVERT THE RIGHT SUBTREE

Call:

    invertTree(root->right);

This recursively inverts the entire right subtree.

Both subtrees are now processed before the current node's child pointers
are swapped.

STEP 4: SWAP THE CHILD POINTERS

Operation:

    swap(root->left, root->right);

This exchanges the two child pointers.

It does not exchange the values stored inside the child nodes.

The operation handles all possible combinations:
    - Both children point to valid nodes.
    - Only the left child points to a valid node.
    - Only the right child points to a valid node.
    - Both children are nullptr.

No separate condition is needed for these cases.

STEP 5: RETURN THE ROOT POINTER

Operation:

    return root;

The function returns the pointer to the current node, which is now the
root of the inverted subtree.

The original root node remains the root of the complete tree.

-------------------------------------------------------------------------------
5. FINAL SOLUTION
-------------------------------------------------------------------------------

*/

#include <algorithm>

using namespace std;

/*
NOTE ABOUT LEETCODE:

LeetCode supplies the TreeNode structure automatically.

The definition below makes this file self-contained. When submitting to
LeetCode, use the platform-provided TreeNode definition rather than
declaring it a second time.
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
    TreeNode* invertTree(TreeNode* root) {

        // Base case: an empty subtree needs no inversion.
        if (root == nullptr) {
            return root;
        }

        // Recursively invert the left subtree.
        invertTree(root->left);

        // Recursively invert the right subtree.
        invertTree(root->right);

        // Swap the left and right child pointers.
        swap(root->left, root->right);

        // Return the root of the inverted subtree.
        return root;
    }
};

/*
-------------------------------------------------------------------------------
6. STEP-BY-STEP EXECUTION
-------------------------------------------------------------------------------

Consider the following tree:

             4
            / \
           2   7
          / \
         1   3

INITIAL CALL:

    invertTree(root)

The root points to node 4.

The base case is false because root is not nullptr.

LEFT SUBTREE:

    invertTree(root->left)

The function moves to node 2.

Again, the base case is false.

The function first calls invertTree on node 2's left child, node 1.

NODE 1:

Both children of node 1 are nullptr.

The recursive calls reach the base case and return nullptr.

The function then swaps node 1's left and right pointers. Both are nullptr,
so the tree remains unchanged at this node.

The function returns the pointer to node 1.

BACK AT NODE 2:

Node 2's left subtree has been processed.

The function now processes node 2's right child, node 3.

NODE 3:

Both children of node 3 are nullptr.

The base cases return nullptr, and swapping the two null child pointers
does not change the node.

The function returns the pointer to node 3.

BACK AT NODE 2:

Both child subtrees have now been processed.

Before swapping:

        2
       / \
      1   3

After swapping:

        2
       / \
      3   1

The function returns the pointer to node 2.

BACK AT NODE 4:

The left subtree has been processed and inverted.

The function next processes node 4's original right subtree, rooted at 7.

In this example, node 7 has no children, so its recursive calls reach
nullptr and its pointers are swapped without changing the node.

Finally, the function swaps node 4's left and right pointers.

Before swapping:

             4
            / \
           2   7
          / \
         3   1

After swapping:

             4
            / \
           7   2
              / \
             3   1

Final result:
The left and right child pointers have been swapped at every node.

IMPORTANT OBSERVATION:

Recursive calls process the subtrees before the current node's swap occurs.
The function then returns the pointer to the current subtree's root.

-------------------------------------------------------------------------------
7. ISSUES ENCOUNTERED AND HOW THEY WERE RESOLVED
-------------------------------------------------------------------------------

ISSUE 1: CONFUSING NODE VALUES WITH CHILD POINTERS

Initial challenge:
The first idea was to swap the values of the left and right children.

Resolution:
The problem requires inverting the tree's structure, not exchanging the
values stored in nodes.

Therefore, swap the child pointers:

    swap(root->left, root->right);

ISSUE 2: UNDERSTANDING NULL POINTERS

Initial challenge:
It was unclear whether a node with one or both null children needed special
handling before swapping.

Resolution:
The swap operation works for all pointer combinations. A nullptr is a
valid pointer value, and swapping a nullptr with a valid node pointer moves
the existing child to the opposite side.

ISSUE 3: DECIDING WHEN TO SWAP

Initial challenge:
It was necessary to determine whether the swap should happen before or
after the recursive calls.

Resolution:
The chosen approach processes the left and right subtrees first and then
swaps the current node's child pointers.

This ensures that every subtree is inverted and every node is processed.

ISSUE 4: UNDERSTANDING THE RETURN TYPE

Initial challenge:
The function returns TreeNode*, but the recursive calls are used for their
side effects rather than to calculate a value needed by the current call.

Resolution:
The recursive calls modify the tree through the pointers they receive.
Their return values are not needed for the swapping operation.

The current call returns root so that its caller receives the pointer to
the root of the inverted subtree.

ISSUE 5: UNDERSTANDING THE RECURSION FLOW

Initial challenge:
Understanding how the function reaches nullptr and then resumes execution
at the parent node.

Resolution:
Each recursive call executes until it reaches the base case. Once it
returns, execution resumes immediately after that call in the caller.

The parent then continues with the next recursive call or the swap
operation.

NOTE:
These were the principal conceptual questions discussed while deriving the
solution. They are learning observations, not implementation bugs in the
accepted code.

-------------------------------------------------------------------------------
8. EDGE CASES
-------------------------------------------------------------------------------

CASE 1: EMPTY TREE

Input:
nullptr

Output:
nullptr

Reason:
The base case immediately returns nullptr.

CASE 2: SINGLE NODE

Input:
    1

Output:
    1

Reason:
Both children are nullptr. Swapping them does not change the tree.

CASE 3: BOTH CHILDREN EXIST

Input:

        1
       / \
      2   3

Output:

        1
       / \
      3   2

Reason:
The left and right pointers are exchanged.

CASE 4: ONLY A LEFT CHILD EXISTS

Input:

        1
       /
      2

Output:

        1
         \
          2

Reason:
The left pointer is swapped with the right pointer, which is nullptr.

CASE 5: ONLY A RIGHT CHILD EXISTS

Input:

        1
         \
          2

Output:

        1
       /
      2

Reason:
The existing right child moves to the left side.

CASE 6: SKEWED TREE

Input:

    1
   /
  2
 /
3

Output:

    1
     \
      2
       \
        3

Reason:
Each node is inverted recursively.

-------------------------------------------------------------------------------
9. COMPLEXITY ANALYSIS
-------------------------------------------------------------------------------

Let:

    n = number of nodes in the binary tree
    h = height of the binary tree

TIME COMPLEXITY: O(n)

Each node is visited once.

At every node, the function performs constant work apart from the recursive
calls: checking the pointer, swapping two pointers, and returning the root.

Therefore, the total time complexity is O(n).

AUXILIARY SPACE COMPLEXITY: O(h)

The recursive call stack depends on the height of the tree.

For a balanced binary tree:

    h = O(log n)

Therefore, auxiliary stack space is O(log n).

For a completely skewed binary tree:

    h = O(n)

Therefore, auxiliary stack space can be O(n).

The swap operation itself uses constant auxiliary space. The recursive
call stack is the dominant auxiliary-space cost.

-------------------------------------------------------------------------------
10. KEY LEARNINGS
-------------------------------------------------------------------------------

1. A binary tree can be modified recursively by applying the same operation
   to its left and right subtrees.

2. A nullptr represents an absent child.

3. Swapping child pointers changes tree structure; swapping node values
   does not.

4. std::swap can exchange pointers, including when one or both are nullptr.

5. Recursive calls do not automatically require their results to be
   returned by the current function.

6. A function returning TreeNode* must return a suitable pointer on every
   execution path.

7. Returning root provides the caller with the root pointer of the
   inverted subtree.

8. Each node is visited once, giving O(n) time complexity.

9. Recursive stack space depends on tree height, giving O(h) auxiliary
   space complexity.

10. Tracing a small tree by hand is useful for understanding how recursive
    calls return and how pointer modifications affect the tree.

-------------------------------------------------------------------------------
11. FINAL SUMMARY
-------------------------------------------------------------------------------

Problem:
    LeetCode 226 - Invert Binary Tree

Approach:
    Recursive Depth-First Search (DFS)

Core operations:
    1. Check whether the current pointer is nullptr.
    2. Recursively invert the left subtree.
    3. Recursively invert the right subtree.
    4. Swap the left and right child pointers.
    5. Return the current root pointer.

Time Complexity:
    O(n)

Auxiliary Space Complexity:
    O(h)

Result:
    Accepted on LeetCode

Main concept learned:
    Recursion can modify a tree in place by processing each node's
    subtrees and then swapping its child pointers.

===============================================================================
END OF FILE
===============================================================================
*/