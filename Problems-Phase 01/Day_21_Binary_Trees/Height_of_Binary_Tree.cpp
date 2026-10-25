
/*
===============================================================================
PROBLEM: Height of Binary Tree
PLATFORM: GeeksforGeeks (GFG)
TOPIC: Binary Trees | Recursion | DFS | Tree Height
PURPOSE: Detailed revision notes for understanding, explaining, and recalling
         the recursive solution.
===============================================================================

1. PROBLEM STATEMENT
--------------------
Given the root of a binary tree, calculate its height.

IMPORTANT: In this GFG problem, height is measured in NUMBER OF EDGES on the
longest path from the root to a leaf.

That means:
- An empty tree has height 0 according to the submitted implementation.
- A tree containing only one node has height 0 because there are no edges.
- A tree with root and one child has height 1.
- A longest root-to-leaf path containing three edges has height 3.

Example:

          1
         / \
        2   3
       /
      4

Longest root-to-leaf path: 1 -> 2 -> 4
Number of edges on this path: 2
Expected height: 2

Some textbooks and platforms define height as the number of nodes on the
longest root-to-leaf path instead. Under that convention, a one-node tree has
height 1 and the recurrence differs at the base case. Always check the
platform's definition. This file explains the edge-count convention used by
the submitted solution.

2. NODE STRUCTURE
-----------------
Each node contains:
- data: the value stored in the node.
- left: pointer to the left child.
- right: pointer to the right child.

A pointer equal to nullptr means the child does not exist.

The function receives Node* root, which points to the root of the subtree
currently being processed. Recursive calls calculate the height of smaller
subtrees.

3. CORE RECURSIVE IDEA
----------------------
For a non-leaf node, the longest path must continue through either the left
subtree or the right subtree. We therefore:
1. Calculate the left subtree's height.
2. Calculate the right subtree's height.
3. Choose the larger height using max().
4. Add 1 for the edge from the current node to the child along that longer
   path.

Formula for a non-leaf node:

    height(root) = 1 + max(height(root->left),
                          height(root->right))

The +1 represents one edge connecting the current node to the next node on
the longest path.

4. WHY THE BASE CASES ARE DIFFERENT
-----------------------------------
The submitted solution has two base cases.

A. Empty subtree:

    if (root == nullptr) {
        return 0;
    }

This returns 0 for a missing child pointer.

B. Leaf node:

    if (root->left == nullptr && root->right == nullptr) {
        return 0;
    }

A leaf has no children, so the longest path from that leaf down to a leaf has
zero edges. The path consists of the leaf itself but contains no edges.

Why check for nullptr first?
If root is nullptr, it is not a real node and cannot be checked as if it had
children. The first condition safely returns before accessing root->left or
root->right.

Why do both base cases return 0 in this implementation?
Because the function measures height in edges. Neither an empty child pointer
nor a leaf has any downward edge to count.

Note: Some standard formulations use height(nullptr) = -1 and height(leaf) = 0
to make the recurrence 1 + max(leftHeight, rightHeight) work for every
non-null node without a separate leaf check. The submitted implementation
instead explicitly returns 0 for a leaf and keeps nullptr at 0. Both approaches
can be used with their corresponding recurrence, but they must not be mixed.
The supplied code is correct for the GFG convention described above.

5. THE ORIGINAL SOLUTION
------------------------
The submitted solution is:

    int height(Node* root) {
        if (root == nullptr) {
            return 0;
        }

        if (root->left == nullptr && root->right == nullptr) {
            return 0;
        }

        int leftHeight = height(root->left);
        int rightHeight = height(root->right);

        return 1 + max(leftHeight, rightHeight);
    }

This is correct for the edge-count definition used here.

6. LINE-BY-LINE EXPLANATION
---------------------------

Line 1:
    int height(Node* root)

Defines a function that returns the height of the subtree whose root is root.

Line 2:
    if (root == nullptr)

Checks whether this recursive call has received an empty subtree.

Line 3:
    return 0;

Returns zero because an empty subtree has no edges.

Line 4:
    if (root->left == nullptr && root->right == nullptr)

Checks whether the current real node is a leaf. Both child pointers must be
nullptr.

Line 5:
    return 0;

Returns zero because there are zero edges from a leaf down to itself.

Line 6:
    int leftHeight = height(root->left);

Recursively calculates the height of the left subtree and stores the result
in leftHeight.

Line 7:
    int rightHeight = height(root->right);

Recursively calculates the height of the right subtree and stores the result
in rightHeight.

Line 8:
    return 1 + max(leftHeight, rightHeight);

The longer of the two subtree paths determines the longest path below the
current node. Add one for the edge connecting the current node to the first
node on that longer path.

Why max() instead of min()?
Height is based on the longest root-to-leaf path, so we choose the larger of
the two subtree heights. min() would select the shorter path instead.

7. COMPLETE DRY RUN
-------------------
Use this tree:

          1
         / \
        2   3
       /
      4

The longest path is 1 -> 2 -> 4, which has two edges. Expected height = 2.

A. At node 1
------------
Node 1 is not a leaf.
- It calls height(node 2) for the left subtree.
- It calls height(node 3) for the right subtree.
- It waits for both results.

B. At node 2
------------
Node 2 is not a leaf because it has a left child.
- It calls height(node 4).
- It calls height(nullptr) for its missing right child.

C. At node 4
------------
Node 4 is a leaf because both child pointers are nullptr.
It returns 0.

D. The missing right child of node 2
------------------------------------
height(nullptr) returns 0.

Node 2 now has:
- leftHeight = 0 (height of node 4, a leaf)
- rightHeight = 0 (empty right subtree)

It returns:

    1 + max(0, 0) = 1

This correctly represents the one edge from node 2 to node 4.

E. At node 3
------------
Node 3 is a leaf, so it returns 0.

F. Back at node 1
-----------------
Node 1 now has:
- leftHeight = 1
- rightHeight = 0

It returns:

    1 + max(1, 0)
    = 1 + 1
    = 2

Final answer: 2 edges.

8. CALL-STACK / RETURN-VALUE TRACE
----------------------------------
The recursion travels down to leaf nodes and empty child pointers. Then the
heights are returned upward:

    height(node 4)  -> 0
    height(node 2)  -> 1
    height(node 3)  -> 0
    height(node 1)  -> 2

The function explores the left subtree before the right subtree because the
left recursive call appears first. The final height is calculated while the
calls return.

9. WHY THE FORMULA WORKS
------------------------
For a leaf, there are no downward edges, so its height is 0.

For a non-leaf node:
- The longest path through the left child has 1 + leftHeight edges.
- The longest path through the right child has 1 + rightHeight edges.
- The longest of these paths has 1 + max(leftHeight, rightHeight) edges.

Therefore, the recurrence correctly returns the number of edges on the
longest downward path from the current node to a leaf.

10. EDGE CASES
--------------
A. Empty tree

    root = nullptr

Returns 0 in this implementation.

B. Single node

        7

The node is a leaf. Returns 0 because there are no edges.

C. Root with one child

        1
       /
      2

Node 2 has height 0. Node 1 returns 1 + max(0, 0) = 1.

D. Three nodes in a chain

        1
       /
      2
     /
    3

Node 3 returns 0.
Node 2 returns 1.
Node 1 returns 2.
Height = 2 edges.

E. Three nodes in a balanced tree

        1
       / \
      2   3

Both children are leaves with height 0.
The root returns 1 + max(0, 0) = 1.
Height = 1 edge.

F. Left and right paths have different lengths

          1
         / \
        2   3
       /
      4

The left subtree height is 1 and the right subtree height is 0.
The root uses max(1, 0), not min(1, 0), so the longer path is selected.

11. COMMON MISTAKES TO AVOID
----------------------------
1. Confusing edges and nodes
   In this problem, a single-node tree has height 0, not 1, because height
   counts edges on the longest path.

2. Forgetting the leaf base case when using this exact recurrence
   If the leaf check is removed while nullptr still returns 0, then a leaf
   would calculate 1 + max(0, 0) = 1. That would count height in nodes for
   a one-node tree, not edges.

3. Returning 1 for a leaf
   That is appropriate for a node-counting convention, not this edge-count
   convention.

4. Using min() instead of max()
   The height is the longest path, so the larger subtree height is needed.

5. Forgetting +1
   The current node adds one edge between itself and the child path selected
   by max().

6. Using || instead of &&
   A leaf has neither child. Both child pointers must be nullptr.

7. Accessing children before checking root
   Always handle root == nullptr before reading root->left or root->right.

8. Mixing base-case conventions
   Do not combine height(nullptr) = 0 with a recurrence that assumes
   height(nullptr) = -1 unless the leaf handling is adjusted appropriately.

12. TIME AND SPACE COMPLEXITY
-----------------------------
Time complexity: O(n)

Every node is visited once. At each non-leaf node, the function makes
constant-time comparisons and uses max() on two integer values.

Auxiliary space: O(h)

Recursive calls occupy the call stack, where h is the height of the tree.

- Balanced tree: O(log n) stack space.
- Highly skewed tree: O(n) stack space.

13. ALTERNATIVE FORMULATION: HEIGHT COUNTED IN NODES
----------------------------------------------------
Some resources define height as the number of nodes on the longest
root-to-leaf path. Under that definition:
- An empty tree commonly returns 0.
- A leaf returns 1.
- The recurrence is 1 + max(leftHeight, rightHeight).

Example:

        7

Height in edges = 0
Height in nodes = 1

Do not change the submitted solution unless the problem statement uses the
node-count definition. For the current edge-count version, a leaf returns 0.

14. COMPARISON WITH OTHER TREE RECURSION PROBLEMS
-------------------------------------------------
Size:
    return 1 + leftSize + rightSize;

Counts every real node.

Sum:
    return root->data + leftSum + rightSum;

Adds the values of every node.

Count leaves:
    if (root->left == nullptr && root->right == nullptr) return 1;
    return leftAns + rightAns;

Counts only nodes with no children.

Height in edges:
    return 1 + max(leftHeight, rightHeight);

For non-leaf nodes, selects the longest subtree path and adds one edge.
The base case for a leaf is 0.

The structure of recursion is similar, but each function returns a different
kind of information.

15. SELF-REVISION QUESTIONS
---------------------------
Try to answer these without looking at the explanation:

1. In this problem, is height measured in edges or nodes?
2. Why does a single-node tree have height 0?
3. Why is max() required instead of min()?
4. What does the +1 represent?
5. Why does the code check root == nullptr first?
6. What does the leaf check accomplish?
7. What is the height of a chain with five nodes?
8. What is the height of a root with two leaf children?
9. What are the time and auxiliary-space complexities?
10. How would the base case change if height were measured in nodes?

16. QUICK REVISION SUMMARY
--------------------------
- This solution measures height in edges.
- Empty tree returns 0.
- Leaf node returns 0 because there are no downward edges.
- A non-leaf returns 1 + max(leftHeight, rightHeight).
- max() selects the longer subtree path.
- +1 counts the edge from the current node to the selected child path.
- Time complexity: O(n).
- Auxiliary space: O(h), due to the recursive call stack.

17. ORIGINAL GFG-STYLE SOLUTION
-------------------------------
The code below preserves the submitted algorithm and variable names.

===============================================================================
*/

class Solution {
  public:
    int height(Node* root) {
        // Empty subtree: zero edges.
        if (root == nullptr) {
            return 0;
        }

        // A leaf has no downward edges.
        if (root->left == nullptr && root->right == nullptr) {
            return 0;
        }

        // Height of the left subtree.
        int leftHeight = height(root->left);

        // Height of the right subtree.
        int rightHeight = height(root->right);

        // Choose the longer subtree path and add its connecting edge.
        return 1 + max(leftHeight, rightHeight);
    }
};

/*
===============================================================================
END OF REVISION NOTES
===============================================================================
*/
