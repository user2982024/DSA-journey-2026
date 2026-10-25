
/*
===============================================================================
PROBLEM: Count Leaf Nodes in a Binary Tree
PLATFORM: GeeksforGeeks (GFG)
TOPIC: Binary Trees | Recursion | Depth-First Search (DFS)
PURPOSE: Detailed revision notes for understanding, explaining, and recalling
         the recursive solution.
===============================================================================

1. PROBLEM STATEMENT
--------------------
Given the root of a binary tree, count how many leaf nodes exist in the tree.

A leaf node is a node that has NO children:
- left == nullptr
- right == nullptr

A node with only one child is NOT a leaf.
A node with both a left and a right child is NOT a leaf.

Example:

          1
         / \
        2   3
       /   / \
      4   5   6

Leaf nodes: 4, 5, 6
Expected answer: 3

2. NODE STRUCTURE
-----------------
Each node contains:
- data: the value stored in the node.
- left: pointer to the left child.
- right: pointer to the right child.

A child pointer equal to nullptr means that child does not exist.

The function receives Node* root, a pointer to the root of the subtree it is
currently processing. Recursive calls pass the left and right child pointers
so the same function can solve the problem for smaller subtrees.

3. CORE RECURSIVE IDEA
----------------------
For each subtree:
1. If it is empty, it contributes zero leaf nodes.
2. If the current node is a leaf, it contributes exactly one leaf.
3. Otherwise, its leaf count is the sum of the leaf counts of its left and
   right subtrees.

The main formula for a non-leaf node is:

    LeafCount(tree) = LeafCount(left subtree)
                    + LeafCount(right subtree)

For a leaf node, the answer is 1.

4. BASE CASE: WHY nullptr RETURNS 0
-----------------------------------
    if (root == nullptr) {
        return 0;
    }

An empty subtree contains no nodes, and therefore cannot contain any leaf
nodes. Returning 0 is the correct contribution.

This check also prevents the function from accessing root->left or
root->right when root is nullptr.

5. WHAT MAKES A NODE A LEAF?
----------------------------
    if (root->left == nullptr && root->right == nullptr) {
        return 1;
    }

Both conditions must be true:
- root->left == nullptr means there is no left child.
- root->right == nullptr means there is no right child.
- && means AND: both conditions must be true.

Why not use || (OR)?
If only one child is missing, the node may still have another child and is
not a leaf. For example, a node with a left child but no right child is not
a leaf. Therefore, both child pointers must be nullptr.

Why return 1?
The current node itself is one leaf node. Returning 1 counts it exactly once.

Why do we check for a leaf before returning leftAns + rightAns?
A leaf's children are both nullptr, so both recursive calls would return 0.
If we returned only leftAns + rightAns, the leaf would incorrectly contribute
zero. The explicit leaf check ensures it contributes 1.

6. THE ORIGINAL SOLUTION
------------------------
The submitted solution is logically correct:

    int countLeaves(Node* root) {
        if (root == nullptr) {
            return 0;
        }

        int leftAns = countLeaves(root->left);
        int rightAns = countLeaves(root->right);

        if (root->left == nullptr && root->right == nullptr) {
            return 1;
        }

        return leftAns + rightAns;
    }

No logic change is required.

7. LINE-BY-LINE EXPLANATION
---------------------------

Line 1:
    int countLeaves(Node* root)

Defines a function that receives the root pointer for the current subtree and
returns an integer representing how many leaves are in that subtree.

Line 2:
    if (root == nullptr)

Checks whether this subtree is empty.

Line 3:
    return 0;

An empty subtree has no leaves, so it contributes zero. This is the base case.

Line 4:
    int leftAns = countLeaves(root->left);

Recursively counts the leaves in the entire left subtree and stores that
count in leftAns. This is not just checking whether the immediate left child
is a leaf; the recursive call explores all descendants in that subtree.

Line 5:
    int rightAns = countLeaves(root->right);

Recursively counts the leaves in the entire right subtree and stores that
count in rightAns.

Line 6:
    if (root->left == nullptr && root->right == nullptr)

Checks whether the current node has no children. If both pointers are nullptr,
the current node is a leaf.

Line 7:
    return 1;

Returns one because the current subtree consists of a single leaf node at
this point. This return ends this function call immediately.

Line 8:
    return leftAns + rightAns;

If the current node is not a leaf, all leaves below it must be in either the
left subtree or the right subtree. Add those two counts and return the result.

Notice that the code does not add root->data. This problem counts leaf nodes;
it does not sum node values.

8. COMPLETE DRY RUN
-------------------
Use this tree:

          1
         / \
        2   3
       /   / \
      4   5   6

Leaves are 4, 5, and 6, so the expected answer is 3.

A. Start at node 1
------------------
The function calls:
- countLeaves(node 2)
- countLeaves(node 3)

It waits for the recursive results before combining them.

B. At node 2
------------
Node 2 has:
- left child: node 4
- right child: nullptr

It calls countLeaves(node 4), then countLeaves(nullptr).

C. At node 4
------------
Node 4 has no left or right child.
- The nullptr base case would return 0 for each missing child.
- Both child pointers are nullptr, so node 4 is a leaf.
- It returns 1.

Node 2 receives leftAns = 1 and rightAns = 0.
Node 2 is not a leaf because it has a left child.
It returns 1 + 0 = 1.

D. At node 3
------------
Node 3 has two children: nodes 5 and 6.
It calls countLeaves(node 5) and countLeaves(node 6).

At node 5:
- Both child pointers are nullptr.
- It is a leaf and returns 1.

At node 6:
- Both child pointers are nullptr.
- It is a leaf and returns 1.

Node 3 receives:
- leftAns = 1
- rightAns = 1

Node 3 is not a leaf because it has children.
It returns 1 + 1 = 2.

E. Back at node 1
-----------------
Node 1 receives:
- leftAns = 1 (leaf node 4)
- rightAns = 2 (leaf nodes 5 and 6)

Node 1 is not a leaf because it has children.
It returns:

    1 + 2 = 3

Final answer: 3

9. RECURSION AND RETURN VALUES
------------------------------
Each call returns the number of leaves inside its own subtree.

For the example tree:

    countLeaves(node 4) -> 1
    countLeaves(node 2) -> 1
    countLeaves(node 5) -> 1
    countLeaves(node 6) -> 1
    countLeaves(node 3) -> 2
    countLeaves(node 1) -> 3

The recursion travels down to individual nodes and nullptr children. When
calls return, the counts are combined on the way back up.

This solution uses a depth-first recursive traversal. Because the left call
appears first, the left subtree is explored before the right subtree.

10. WHY THE FORMULA WORKS
-------------------------
For an empty subtree, the leaf count is zero.

For a non-empty subtree:
- If the current node has no children, the subtree has exactly one leaf: the
  current node. The function returns 1.
- Otherwise, the current node is not a leaf. Every leaf must belong to the
  left subtree or the right subtree. These subtrees do not overlap, so adding
  their leaf counts gives the total without double-counting.

This explains why the solution is correct for every binary tree.

11. EDGE CASES
--------------
A. Empty tree

    root = nullptr

Returns 0 because there are no nodes and no leaves.

B. One node

        7

The only node has no children, so it is a leaf. Returns 1.

C. Only a left child

        1
       /
      2

Node 1 is not a leaf; node 2 is a leaf. Returns 1.

D. Only a right child

      1
       \
        2

Node 1 is not a leaf; node 2 is a leaf. Returns 1.

E. Full binary tree with three nodes

        1
       / \
      2   3

Nodes 2 and 3 are leaves. Returns 2.

F. A chain of nodes

        1
       /
      2
     /
    3

Only node 3 is a leaf. Returns 1. Nodes 1 and 2 each have a child, so they
are not leaves.

G. A root with two leaf children

        1
       / \
      2   3

The two children are leaves; the root is not. Returns 2.

12. COMMON MISTAKES TO AVOID
----------------------------
1. Using || instead of &&
   A leaf must have neither child. If only one child is missing, the node is
   still an internal node if the other child exists.

2. Returning 0 for a leaf
   A leaf contributes one, not zero.

3. Forgetting the leaf check
   If the function always returns leftAns + rightAns for non-null nodes,
   leaf nodes would return 0 + 0 and never be counted.

4. Returning 1 for every non-null node
   That would count all nodes, not just leaves.

5. Counting a node with one child as a leaf
   A node is a leaf only when both child pointers are nullptr.

6. Adding node data
   root->data is not needed because the task is to count leaf nodes, not to
   sum values.

7. Forgetting the nullptr base case
   The recursive calls eventually receive nullptr pointers. The base case is
   necessary to stop recursion safely.

8. Thinking the left and right recursive calls only inspect immediate children
   Each recursive call explores its entire subtree, not just one node.

9. Confusing leaves with nodes at the deepest level
   A leaf has no children. A node at a certain depth can still have children,
   so depth alone does not define a leaf.

13. TIME AND SPACE COMPLEXITY
-----------------------------
Time complexity: O(n)

Every node is visited once. The function checks its children and combines the
two recursive results using constant-time operations.

Auxiliary space: O(h)

The recursive call stack can contain up to h active calls, where h is the
height of the tree.

- Balanced tree: O(log n) stack space.
- Highly skewed tree: O(n) stack space.

14. COMPARISON WITH RELATED TREE PROBLEMS
-----------------------------------------
Size of binary tree:

    return 1 + leftSize + rightSize;

Every non-null node contributes one to the count of all nodes.

Sum of binary tree:

    return root->data + leftSum + rightSum;

Every node contributes its stored data value to the total sum.

Count leaves:

    if (root->left == nullptr && root->right == nullptr) {
        return 1;
    }

    return leftAns + rightAns;

A leaf contributes one. A non-leaf contributes the number of leaves in its
two subtrees.

These problems share the same overall recursive approach, but the meaning of
the return value and the combine step differ.

15. SELF-REVISION QUESTIONS
---------------------------
Try to answer these from memory:

1. What exactly is a leaf node?
2. Why must both child pointers be nullptr?
3. Why does countLeaves(nullptr) return 0?
4. Why does a leaf return 1?
5. Why would leftAns + rightAns alone fail for a leaf?
6. Is a node with only one child a leaf? Why or why not?
7. What is the answer for an empty tree?
8. What is the answer for a chain containing ten nodes?
9. What are the time and auxiliary-space complexities?
10. How does counting leaves differ from counting all nodes?

16. QUICK REVISION SUMMARY
--------------------------
- A leaf has no left child AND no right child.
- Empty subtree: return 0.
- Leaf node: return 1.
- Non-leaf node: return leftAns + rightAns.
- Do not add root->data; this is a counting problem, not a sum problem.
- Time complexity: O(n).
- Auxiliary space: O(h), due to recursive call-stack depth.
- The solution uses DFS recursion and combines subtree results on return.

17. ORIGINAL GFG-STYLE SOLUTION
-------------------------------
The code below preserves the submitted algorithm and variable names.

===============================================================================
*/

class Solution {
  public:
    int countLeaves(Node* root) {
        // An empty subtree contains no leaf nodes.
        if (root == nullptr) {
            return 0;
        }

        // Count leaves in the left subtree.
        int leftAns = countLeaves(root->left);

        // Count leaves in the right subtree.
        int rightAns = countLeaves(root->right);

        // A leaf has neither a left child nor a right child.
        if (root->left == nullptr && root->right == nullptr) {
            return 1;
        }

        // A non-leaf's leaves are in its left and right subtrees.
        return leftAns + rightAns;
    }
};

/*
===============================================================================
END OF REVISION NOTES
===============================================================================
*/
