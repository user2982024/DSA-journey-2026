
/*
===============================================================================
                    DSA JOURNEY — DAY 25
===============================================================================

PROBLEM:
    LeetCode 226 — Invert Binary Tree

TOPIC:
    Binary Trees | DFS | Recursion | Pointers | Tree Manipulation

DIFFICULTY:
    Easy

PROBLEM LINK:
    https://leetcode.com/problems/invert-binary-tree/

APPROACH:
    Recursive Depth First Search (DFS)

===============================================================================
1. PROBLEM STATEMENT
===============================================================================

Given the root of a binary tree, invert the tree and return its root.

Inverting a binary tree means swapping the left and right children of
EVERY node in the tree.

In simple words:

    Every node's left subtree must become its right subtree.

    Every node's right subtree must become its left subtree.

We must perform this operation throughout the entire binary tree.

===============================================================================
2. UNDERSTANDING THE PROBLEM
===============================================================================

Consider the following binary tree:

                         4
                       /   \
                      2     7
                     / \   / \
                    1   3 6   9

We need to invert this tree.

After inversion, the expected tree is:

                         4
                       /   \
                      7     2
                     / \   / \
                    9   6 3   1

Let's understand what happened.

At the root node 4:

    Original:
        left  = 2
        right = 7

    After swapping:
        left  = 7
        right = 2

At node 7:

    Original children:
        left  = 6
        right = 9

    After swapping:
        left  = 9
        right = 6

At node 2:

    Original children:
        left  = 1
        right = 3

    After swapping:
        left  = 3
        right = 1

The same operation must be performed at every node.

===============================================================================
3. DEVELOPING THE INTUITION
===============================================================================

Our first observation:

Every node has two pointers:

    root->left
    root->right

These pointers refer to the left and right children of the current node.

If we swap these two pointers, the current node's children are inverted.

We can use:

    swap(root->left, root->right);

But there is one important question:

How do we perform this operation on EVERY node?

We need to visit all nodes.

This is where Depth First Search (DFS) and recursion come into play.

Our recursive approach:

    1. Reach the current node.
    2. Recursively process its left subtree.
    3. Recursively process its right subtree.
    4. Swap the current node's left and right pointers.
    5. Return the current node.

We repeat this process for every non-null node.

===============================================================================
4. WHY DO WE NEED RECURSION?
===============================================================================

A binary tree is naturally recursive.

Every node can have:

    - A left subtree.
    - A right subtree.

Each subtree is itself a binary tree.

Therefore, we can solve the problem for smaller subtrees using the
same function.

For example:

                         4
                       /   \
                      2     7
                     / \   / \
                    1   3 6   9

We call:

    invertTree(root->left);

This recursively inverts the subtree rooted at node 2.

Then we call:

    invertTree(root->right);

This recursively inverts the subtree rooted at node 7.

After both calls return, we swap the children of node 4.

The same function handles every level of the tree.

===============================================================================
5. DESIGNING THE RECURSIVE FUNCTION
===============================================================================

Our function:

    TreeNode* invertTree(TreeNode* root)

WHY DOES IT RETURN TreeNode*?

Because the problem requires us to return the root of the inverted tree.

The return type is a pointer to a TreeNode.

The function receives:

    TreeNode* root

This pointer represents the current node being processed.

As recursion moves through the tree, root refers to different nodes
in different recursive invocations.

===============================================================================
6. STEP-BY-STEP IMPLEMENTATION
===============================================================================

STEP 1: BASE CASE

    if (root == nullptr) {
        return root;
    }

WHY?

If root is nullptr, there is no node to process.

We immediately return.

Since root is already nullptr, returning root is equivalent to:

    return nullptr;

This prevents us from accessing the left or right children of a
non-existent node.

It also ensures that recursion eventually terminates.

IMPORTANT:

This return only finishes the current recursive invocation.

Control goes back to the caller.

STEP 2: RECURSIVELY INVERT THE LEFT SUBTREE

    invertTree(root->left);

We call the same function for the current node's left child.

The recursive function continues exploring that subtree.

It eventually reaches its deepest non-null nodes and returns.

STEP 3: RECURSIVELY INVERT THE RIGHT SUBTREE

    invertTree(root->right);

After the left recursive call finishes, execution continues here.

We recursively invert the current node's right subtree.

Now both child subtrees have been processed.

STEP 4: SWAP THE CHILD POINTERS

    swap(root->left, root->right);

This is the most important operation.

We exchange the two pointers.

Before swapping:

    root->left  -> Left Child
    root->right -> Right Child

After swapping:

    root->left  -> Previous Right Child
    root->right -> Previous Left Child

The actual TreeNode objects are not copied or recreated.

We simply exchange the pointers connecting the current node to its
children.

STEP 5: RETURN THE CURRENT NODE

    return root;

We return the pointer to the current node.

Because the tree has been modified in place, this is still the same
node, but its left and right pointers have been swapped.

The pointer itself has not changed.

===============================================================================
7. UNDERSTANDING WHY WE DO NOT ASSIGN THE RECURSIVE RETURN VALUES
===============================================================================

Our implementation:

    invertTree(root->left);
    invertTree(root->right);

Notice that we do not write:

    root->left = invertTree(root->left);
    root->right = invertTree(root->right);

WHY?

Because our recursive function modifies the existing tree directly.

Let's understand this.

Suppose we are at node 2:

                         4
                       /   \
                      2     7
                     / \
                    1   3

We execute:

    invertTree(root->left);

The recursive function receives the pointer to node 2.

Inside that invocation, it swaps node 2's own left and right pointers.

The actual node has been modified.

We do not need to assign a new pointer because we are not creating a
replacement node or returning a different subtree root.

The existing subtree is modified in place.

Therefore, simply calling the recursive function is sufficient.

IMPORTANT DISTINCTION:

Our function returns a TreeNode* because the problem asks for the
inverted root.

But the recursive calls themselves modify the existing nodes.

The return values of those calls are not needed by this particular
implementation.

===============================================================================
8. UNDERSTANDING THE RECURSIVE EXECUTION
===============================================================================

Let's trace the following tree:

                         4
                       /   \
                      2     7
                     / \   / \
                    1   3 6   9

Our initial call:

    invertTree(4)

The function executes:

    invertTree(root->left);

Now we enter node 2.

At node 2:

    invertTree(1);

At node 1:

    invertTree(nullptr);
    invertTree(nullptr);

Both calls return nullptr.

Now node 1 executes:

    swap(root->left, root->right);

Both pointers are nullptr, so nothing changes.

Then node 1 returns itself.

We return to node 2.

Next:

    invertTree(3);

Node 3 is processed in the same way.

After both recursive calls have completed, node 2 executes:

    swap(root->left, root->right);

Originally:

    left  = 1
    right = 3

After swapping:

    left  = 3
    right = 1

Node 2 returns to node 4.

Now node 4 executes its right recursive call.

The subtree rooted at node 7 is inverted in the same manner.

After both child subtrees have been processed, node 4 executes:

    swap(root->left, root->right);

Originally:

    left  = 2
    right = 7

After swapping:

    left  = 7
    right = 2

Finally, node 4 is returned as the root of the inverted tree.

===============================================================================
9. WHY DOES THE SWAPPING HAPPEN AFTER THE RECURSIVE CALLS?
===============================================================================

Our implementation uses this order:

    invertTree(root->left);

    invertTree(root->right);

    swap(root->left, root->right);

This means we first process both subtrees and then swap the current
node's children.

This is a bottom-up approach.

The deepest nodes are processed first.

Then their parents are processed.

Finally, the root is processed.

This is similar to postorder traversal because we process:

    Left Subtree
    Right Subtree
    Current Node

IMPORTANT:

For this particular problem, swapping before recursively processing
the children can also work, provided the traversal still visits both
subtrees.

Our implementation uses the bottom-up order.

===============================================================================
10. COMPLETE DRY RUN
===============================================================================

INITIAL TREE:

                         4
                       /   \
                      2     7
                     / \   / \
                    1   3 6   9

INITIAL CALL:

    invertTree(4)

---------------------------------------
STEP 1: PROCESS NODE 4'S LEFT SUBTREE
---------------------------------------

    invertTree(2)

---------------------------------------
STEP 2: PROCESS NODE 2'S LEFT SUBTREE
---------------------------------------

    invertTree(1)

Node 1 has no children.

Both recursive calls receive nullptr.

The base case returns nullptr.

Now we execute:

    swap(1->left, 1->right);

Both pointers are nullptr.

Node 1 returns.

---------------------------------------
STEP 3: PROCESS NODE 2'S RIGHT SUBTREE
---------------------------------------

    invertTree(3)

Node 3 has no children.

Both recursive calls receive nullptr.

The base case returns nullptr.

Now:

    swap(3->left, 3->right);

Both pointers are nullptr.

Node 3 returns.

---------------------------------------
STEP 4: SWAP NODE 2'S CHILDREN
---------------------------------------

Before:

    left  = 1
    right = 3

After:

    left  = 3
    right = 1

Node 2 returns.

---------------------------------------
STEP 5: PROCESS NODE 4'S RIGHT SUBTREE
---------------------------------------

    invertTree(7)

---------------------------------------
STEP 6: PROCESS NODE 7'S LEFT SUBTREE
---------------------------------------

    invertTree(6)

Node 6 has no children.

Both recursive calls receive nullptr.

Node 6 returns.

---------------------------------------
STEP 7: PROCESS NODE 7'S RIGHT SUBTREE
---------------------------------------

    invertTree(9)

Node 9 has no children.

Both recursive calls receive nullptr.

Node 9 returns.

---------------------------------------
STEP 8: SWAP NODE 7'S CHILDREN
---------------------------------------

Before:

    left  = 6
    right = 9

After:

    left  = 9
    right = 6

Node 7 returns.

---------------------------------------
STEP 9: SWAP NODE 4'S CHILDREN
---------------------------------------

Before:

    left  = 2
    right = 7

After:

    left  = 7
    right = 2

Node 4 returns.

FINAL TREE:

                         4
                       /   \
                      7     2
                     / \   / \
                    9   6 3   1

The entire tree has been inverted.

===============================================================================
11. FINAL C++ IMPLEMENTATION
===============================================================================

This is our accepted implementation.

LeetCode provides the TreeNode structure automatically.

For a standalone learning file, the structure is included below.

===============================================================================
*/

#include <bits/stdc++.h>
using namespace std;


/*
Definition for a binary tree node.

LeetCode provides this structure automatically.
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

        // BASE CASE:
        // If the current node is nullptr, return nullptr.
        if (root == nullptr) {
            return root;
        }


        // STEP 1:
        // Recursively invert the left subtree.
        invertTree(root->left);


        // STEP 2:
        // Recursively invert the right subtree.
        invertTree(root->right);


        // STEP 3:
        // Swap the left and right child pointers.
        swap(root->left, root->right);


        // STEP 4:
        // Return the current node.
        return root;
    }

};


/*
===============================================================================
12. COMPLEXITY ANALYSIS
===============================================================================

Let:

    N = Total number of nodes in the binary tree.
    H = Height of the binary tree.

TIME COMPLEXITY:

    O(N)

WHY?

We visit every node exactly once.

At each node, we perform:

    1. One recursive call for the left child.
    2. One recursive call for the right child.
    3. One swap operation.

The swap operation takes O(1) time.

Therefore, the total time complexity is:

    O(N)

SPACE COMPLEXITY:

    O(H)

WHY?

The recursive calls consume stack space.

At any point, the maximum number of active recursive invocations
depends on the height of the tree.

For a balanced binary tree:

    H = O(log N)

For a completely skewed binary tree:

    H = O(N)

Therefore:

    Auxiliary space = O(H)

We are modifying the existing tree in place.

We are not creating another tree or an additional data structure
to store the inverted tree.

===============================================================================
13. IMPORTANT LESSONS LEARNED
===============================================================================

LESSON 1: RECURSIVE TREE STRUCTURE

    Every node can have two smaller binary subtrees.

    We can solve the same problem recursively on both subtrees.

LESSON 2: BASE CASE

    A nullptr node has nothing to invert.

    Returning nullptr prevents further processing.

LESSON 3: POINTER MANIPULATION

    root->left and root->right are pointers.

    Swapping them changes which child each pointer references.

LESSON 4: IN-PLACE MODIFICATION

    We modify the existing tree.

    We do not create a second tree.

LESSON 5: RECURSIVE RETURN VALUES

    The recursive calls modify the existing nodes.

    We do not need to assign their return values to the child pointers.

LESSON 6: CALL STACK

    Every recursive invocation returns to its caller.

    The caller resumes execution after the recursive call.

LESSON 7: BOTTOM-UP EXECUTION

    We process the left subtree, then the right subtree, and finally
    swap the current node's children.

LESSON 8: RETURN ROOT

    We return the pointer to the current node.

    The node itself remains the same; only its child pointers change.

===============================================================================
14. FINAL REVISION CHECKLIST
===============================================================================

[ ] I understand what inverting a binary tree means.

[ ] I understand why DFS is suitable.

[ ] I understand the nullptr base case.

[ ] I understand root->left and root->right.

[ ] I understand how swap() exchanges child pointers.

[ ] I understand why we recursively process both subtrees.

[ ] I understand why swapping happens after both recursive calls.

[ ] I understand why we do not assign the recursive return values.

[ ] I understand in-place tree modification.

[ ] I understand how recursive calls return to their parents.

[ ] I understand the time and space complexity.

[ ] I can implement the solution independently.

===============================================================================
                         END OF DAY 25 NOTES
===============================================================================

PROBLEM:
    LeetCode 226 — Invert Binary Tree

APPROACH:
    Recursive DFS + In-place Pointer Swapping

RESULT:
    Accepted

MAIN CONCEPT MASTERED:
    Recursively modifying a binary tree using pointer manipulation.

ALPHA SIGNING OFF.
OVER AND OUT, COMRADE!
===============================================================================
*/
