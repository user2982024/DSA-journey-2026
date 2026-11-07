
/*
================================================================================
                     LEETCODE 404 - SUM OF LEFT LEAVES
================================================================================

PROBLEM:
--------
Given the root of a binary tree, return the sum of all left leaf nodes.

A leaf is a node that has no children.

A left leaf is a leaf node that is the LEFT CHILD of another node.

LeetCode:
---------
Problem Number : 404
Difficulty     : Easy
Topic          : Binary Trees
Category       : Tree / DFS / Recursion
Technique      : Depth-First Search (DFS)
Traversal      : Recursive Tree Traversal
Time           : O(n)
Space          : O(h)

================================================================================
1. UNDERSTANDING THE PROBLEM
================================================================================

We are given the root of a binary tree.

Our task is to calculate the sum of all LEFT LEAF nodes.

First, understand two important terms.

A LEAF NODE:
------------
A node is a leaf if:

    root->left == nullptr
    AND
    root->right == nullptr

In other words, a leaf has no children.

A LEFT LEAF:
------------
A left leaf is a node that satisfies BOTH conditions:

    1. It is the left child of its parent.
    2. It has no children of its own.

IMPORTANT:
A leaf node on the right side must NOT be included.

Example:

                 3
                / \
               9   20
                  /  \
                 15   7

Left leaves:

    9
    15

Right leaf:

    7

Therefore:

    Sum = 9 + 15 = 24

Expected Output:

    24


================================================================================
2. IDENTIFYING THE LEFT LEAF CONDITION
================================================================================

This is the most important observation in this problem.

How do we identify whether a node is a left leaf?

We examine the LEFT CHILD of the current node.

Suppose we are currently at:

        root

Its left child is:

        root->left

We need to verify two things.

CONDITION 1:
------------
The left child must exist.

    root->left != nullptr

CONDITION 2:
------------
The left child must have no children.

    root->left->left == nullptr

    AND

    root->left->right == nullptr

Combining all three conditions:

    root->left != nullptr

    root->left->left == nullptr

    root->left->right == nullptr

If all conditions are true, root->left is a left leaf.

Therefore, we add:

    ans += root->left->val;


================================================================================
3. INITIAL PROBLEM-SOLVING APPROACH
================================================================================

Our approach is based on recursive DFS.

We need to visit the nodes of the binary tree and
identify every left leaf.

The basic steps are:

    1. Start from the root.
    2. Check whether the current node is nullptr.
    3. Recursively visit the left subtree.
    4. Recursively visit the right subtree.
    5. Check whether the current node's left child is a leaf.
    6. If it is a left leaf, add its value to the answer.
    7. Return the accumulated sum.

We use a class-level variable:

    int ans = 0;

This variable stores the sum of all left leaves.

Whenever we find a left leaf, we update it.

    ans += root->left->val;


================================================================================
4. HOW RECURSION WORKS
================================================================================

We use Depth-First Search (DFS).

The traversal follows this order:

    Left Subtree -> Right Subtree -> Current Node

This is POSTORDER traversal.

Why does this approach work?

Because we recursively explore both subtrees and,
at each current node, inspect whether its left child
is a leaf.

Consider:

                 3
                / \
               9   20
                  /  \
                 15   7

STEP 1:
-------

We start at node 3.

We recursively visit its left subtree.

STEP 2:
-------

We reach node 9.

Node 9 is a leaf.

However, we do not add node 9 by checking whether
the current node itself is a leaf.

Instead, when we were at node 3, we identified
that node 9 was its left leaf.

Therefore:

    ans = 9

STEP 3:
-------

We return to node 3 and visit its right subtree.

We reach node 20.

Its left child is node 15.

We check:

    root->left != nullptr             TRUE

    root->left->left == nullptr       TRUE

    root->left->right == nullptr      TRUE

Therefore, node 15 is a left leaf.

Update:

    ans = 9 + 15 = 24

STEP 4:
-------

We visit node 7.

Node 7 is a right leaf.

It must NOT be included in the answer.

FINAL RESULT:

    ans = 24


================================================================================
5. COMPLETE C++ IMPLEMENTATION
================================================================================

We will use two functions:

    1. dfs():
       Traverses the binary tree and updates the answer.

    2. sumOfLeftLeaves():
       Resets the answer, starts DFS, and returns the result.

WHY USE A SEPARATE DFS FUNCTION?

Our original implementation used sumOfLeftLeaves()
for recursive calls as well.

Although that approach works with the class-level
accumulator, separating the traversal into a helper
function makes the responsibilities clearer.

The public function is responsible for starting
a new calculation.

The helper is responsible for traversing the tree.


================================================================================
6. OPTIMIZED AND CLEAN IMPLEMENTATION
================================================================================
*/

#include <algorithm>
using namespace std;


/*
 * Definition for a binary tree node.
 *
 * LeetCode provides this structure automatically.
 * It is included here to make this file self-contained
 * for a personal GitHub repository.
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

private:

    // Stores the sum of all left leaf nodes.
    int ans = 0;


    /*
     * Function: dfs()
     *
     * Purpose:
     *     Traverses the binary tree and identifies left leaves.
     *
     * Return:
     *     void
     *
     * Additional responsibility:
     *     Updates the class-level variable ans.
     *
     * Traversal:
     *     Postorder DFS.
     */
    void dfs(TreeNode* root) {

        // Base case:
        // If the current node is nullptr, stop recursion.
        if (root == nullptr) {
            return;
        }


        // Recursively traverse the left subtree.
        dfs(root->left);


        // Recursively traverse the right subtree.
        dfs(root->right);


        /*
         * Check whether the current node's left child
         * exists and is a leaf.
         *
         * A left leaf must:
         *
         * 1. Exist.
         * 2. Have no left child.
         * 3. Have no right child.
         */
        if (root->left != nullptr &&
            root->left->left == nullptr &&
            root->left->right == nullptr) {

            // Add the left leaf's value to the answer.
            ans += root->left->val;
        }
    }


public:

    /*
     * Function: sumOfLeftLeaves()
     *
     * Purpose:
     *     Returns the sum of all left leaf nodes.
     *
     * Steps:
     *     1. Reset the answer.
     *     2. Start DFS.
     *     3. Return the accumulated sum.
     */
    int sumOfLeftLeaves(TreeNode* root) {

        /*
         * Reset the accumulator.
         *
         * This ensures that previous function calls
         * do not affect the result of a new tree.
         */
        ans = 0;


        // Traverse the tree.
        dfs(root);


        // Return the sum of all left leaves.
        return ans;
    }
};


/*
================================================================================
7. UNDERSTANDING YOUR ORIGINAL IMPLEMENTATION
================================================================================

Your original implementation:

    class Solution {
    private:
        int ans = 0;

    public:
        int sumOfLeftLeaves(TreeNode* root) {

            if (root == nullptr) {
                return 0;
            }

            sumOfLeftLeaves(root->left);
            sumOfLeftLeaves(root->right);

            if ((root->left != nullptr) &&
                (root->left->left == nullptr &&
                 root->left->right == nullptr)) {

                ans += root->left->val;
            }

            return ans;
        }
    };


WHAT DID YOU DO CORRECTLY?
--------------------------

1. You correctly handled the nullptr base case.

2. You recursively visited the left subtree.

3. You recursively visited the right subtree.

4. You correctly identified the left leaf condition.

5. You correctly accumulated the values using:

       ans += root->left->val;

6. You returned the accumulated answer.


IMPORTANT OBSERVATION:
---------------------

Your recursive calls:

    sumOfLeftLeaves(root->left);
    sumOfLeftLeaves(root->right);

do not use their return values.

Instead, both recursive calls modify the shared
class-level variable ans.

This is why your implementation works.

The recursive function is effectively using
the class-level variable as an accumulator.


ISSUE 1: THE ANSWER IS NOT RESET
-------------------------------

Your original implementation initializes:

    int ans = 0;

at the class level.

However, it does not reset ans when sumOfLeftLeaves()
is called again on the same Solution object.

For example:

    First tree:

        Sum = 24

    ans = 24

    Second tree:

        Sum = 10

If the same object is reused without resetting ans,
the second call could return:

    24 + 10 = 34

Instead of:

    10

SOLUTION:

    ans = 0;

at the beginning of sumOfLeftLeaves().


ISSUE 2: RECURSIVE FUNCTION HAS TWO RESPONSIBILITIES
----------------------------------------------------

Your original sumOfLeftLeaves() function:

    - Traverses the tree.
    - Updates the accumulator.
    - Returns the accumulated result.

However, the recursive calls do not need to return
the accumulated sum.

We can make the code easier to understand by
separating these responsibilities.

SOLUTION:

    void dfs(TreeNode* root);

    int sumOfLeftLeaves(TreeNode* root);

The helper performs traversal.

The public function manages the answer and returns it.

This is a code-organization improvement, not a correction
to your original left-leaf detection logic.


================================================================================
8. WHY DO WE CHECK THE LEFT CHILD?
================================================================================

This is an important conceptual detail.

Suppose we have:

             10
            /  \
           5    20
          /      \
         3        25

We are currently at node 10.

Its left child is node 5.

Is node 5 a left leaf?

No, because it has a left child (node 3).

Now consider node 5.

Its left child is node 3.

Node 3 has no children.

Therefore, node 3 is a left leaf.

Notice that we identify the left leaf by checking
the child of the current node.

This is why our condition uses:

    root->left

rather than simply checking whether root itself
is a leaf.


================================================================================
9. DRY RUN - EXAMPLE 1
================================================================================

Input:

                 3
                / \
               9   20
                  /  \
                 15   7

Expected output:

    24


INITIAL STATE:

    ans = 0


RECURSION:

STEP 1:

    Start at node 3.

    Visit its left subtree.


STEP 2:

    Reach node 9.

    Node 9 has no children.

    Return from dfs(9).

    At node 3, the left child is node 9.

    Node 9 is a leaf.

    ans = 0 + 9 = 9


STEP 3:

    Visit the right subtree of node 3.

    Reach node 20.


STEP 4:

    Visit node 20's left subtree.

    Reach node 15.

    Node 15 is a leaf.

    Return from dfs(15).

    At node 20, its left child is node 15.

    Node 15 is a left leaf.

    ans = 9 + 15 = 24


STEP 5:

    Visit node 7.

    Node 7 is a right leaf.

    It is not added.


FINAL RESULT:

    ans = 24

    Output = 24


================================================================================
10. DRY RUN - EXAMPLE 2
================================================================================

Input:

                 1
                / \
               2   3
              / \
             4   5

Expected output:

    4 + 5 = 9


Let's examine:

    Node 4:
        Left leaf of node 2.
        Include it.

    Node 5:
        Right leaf of node 2.
        Do NOT include it.

    Node 3:
        Right leaf of node 1.
        Do NOT include it.

    Node 2:
        Not a leaf because it has children.

    Node 1:
        Not a leaf because it has children.

IMPORTANT:

    Wait: node 5 is also the RIGHT child of node 2.

Therefore, it must not be included.

Correct expected output:

    4


This example demonstrates why simply adding every
leaf node would produce an incorrect result.


================================================================================
11. DRY RUN - EXAMPLE 3
================================================================================

Input:

                 1
                  \
                   2
                  /
                 3

Expected output:

    3

Reason:

    Node 3 is a leaf.

    It is the LEFT child of node 2.

    Therefore, it is a left leaf.

Even though the root itself has no left child,
we must continue exploring its right subtree.


================================================================================
12. TIME COMPLEXITY ANALYSIS
================================================================================

Let n represent the total number of nodes in the tree.

TIME COMPLEXITY: O(n)
---------------------

Every node is visited exactly once.

At every node, we perform constant-time operations:

    - Check whether the node is nullptr.
    - Access its left child.
    - Check whether the left child is a leaf.
    - Possibly add one value to ans.

Therefore:

    Time Complexity = O(n)


AUXILIARY SPACE COMPLEXITY: O(h)
--------------------------------

The recursive DFS calls use the call stack.

The maximum number of active recursive calls
depends on the height of the tree.

For a balanced tree:

    h = O(log n)

For a completely skewed tree:

    h = O(n)

Therefore:

    Auxiliary Space = O(h)

Worst-case auxiliary space:

    O(n)

The accumulator ans requires O(1) additional space.


================================================================================
13. EDGE CASES
================================================================================

CASE 1: EMPTY TREE

        nullptr

    Output: 0

    Reason:
        No nodes exist.


CASE 2: SINGLE NODE

        1

    Output: 0

    Reason:
        The root is a leaf, but it is not a left leaf.


CASE 3: ONLY LEFT CHILD

        1
       /
      2

    Output: 2

    Reason:
        Node 2 is a left leaf.


CASE 4: ONLY RIGHT CHILD

        1
         \
          2

    Output: 0

    Reason:
        Node 2 is a right leaf.


CASE 5: BOTH CHILDREN ARE LEAVES

             1
            / \
           2   3

    Output: 2

    Reason:
        Node 2 is a left leaf.
        Node 3 is a right leaf.


CASE 6: DEEPER LEFT LEAF

             1
              \
               2
              /
             3

    Output: 3

    Reason:
        Node 3 is the left child of node 2
        and has no children.


================================================================================
14. IMPORTANT CONCEPTS LEARNED
================================================================================

1. TREE RECURSION

   We use recursive calls to explore the entire tree.

2. DEPTH-FIRST SEARCH

   We explore subtrees before returning to their parent.

3. POSTORDER TRAVERSAL

   Left -> Right -> Root.

4. LEAF IDENTIFICATION

   A node is a leaf when both children are nullptr.

5. LEFT LEAF IDENTIFICATION

   A node must be the left child of its parent
   and must have no children.

6. CLASS-LEVEL ACCUMULATOR

   We maintain a shared variable to collect values
   throughout recursion.

7. RECURSION STACK

   Recursive calls are stored on the call stack
   until their execution completes.

8. EDGE CASE HANDLING

   Empty trees, single-node trees, left-only trees,
   and right-only trees must be handled correctly.


================================================================================
15. INTERVIEW EXPLANATION
================================================================================

If an interviewer asks you to explain your solution,
you can say:

"I use a recursive DFS traversal to solve this problem.

The key observation is that a left leaf must be
the left child of its parent and must not have
any children of its own.

For every node, I recursively traverse its left
and right subtrees.

I then check whether its left child exists and
whether both of that child's children are null.

If these conditions are satisfied, I add the
left child's value to my answer.

I maintain the accumulated sum in a variable
and return it after the traversal is complete.

Every node is visited exactly once, so the time
complexity is O(n).

The recursion stack requires O(h) auxiliary space,
where h represents the height of the tree."


================================================================================
16. FINAL TAKEAWAYS
================================================================================

PROBLEM:
    LeetCode 404 - Sum of Left Leaves

APPROACH:
    Recursive DFS

TRAVERSAL:
    Postorder

LEFT LEAF CONDITION:

    root->left != nullptr

    root->left->left == nullptr

    root->left->right == nullptr


ANSWER UPDATE:

    ans += root->left->val;


TIME COMPLEXITY:
    O(n)

AUXILIARY SPACE:
    O(h)

KEY OBSERVATION:
    A left leaf is identified by examining the
    left child of the current node.

IMPORTANT IMPLEMENTATION LESSON:
    Reset class-level accumulators before processing
    a new input.

================================================================================
                         END OF SOLUTION
================================================================================
*/
