
/*
================================================================================
                     LEETCODE 110 - BALANCED BINARY TREE
================================================================================

PROBLEM:
--------
Given a binary tree, determine whether it is height-balanced.

A binary tree is height-balanced if:

    For EVERY node in the tree, the absolute difference between
    the heights of its left and right subtrees is no greater than 1.

Mathematically:

    |Left Subtree Height - Right Subtree Height| <= 1

This condition must hold at EVERY node, not just the root.

LeetCode:
---------
Problem Number : 110
Difficulty     : Easy
Topic          : Binary Trees
Category       : Tree / DFS / Recursion
Technique      : Postorder DFS + Height Calculation
Optimization   : Sentinel Value (-1)
Time           : O(n)
Space          : O(h)

================================================================================
1. UNDERSTANDING THE PROBLEM
================================================================================

We are given the root of a binary tree.

Our task is to determine whether the tree is balanced.

A tree is balanced if the height difference between the
left and right subtrees of EVERY node is at most 1.

Let's understand this with examples.


EXAMPLE 1: BALANCED TREE
-----------------------

                 3
                / \
               9   20
                  /  \
                 15   7

At node 20:

    Left Height  = 1
    Right Height = 1

    Difference = |1 - 1| = 0

At node 3:

    Left Height  = 1
    Right Height = 2

    Difference = |1 - 2| = 1

Both differences are <= 1.

Therefore:

    Output = true


EXAMPLE 2: UNBALANCED TREE
--------------------------

                 1
                /
               2
              /
             3
            /
           4

At node 3:

    Left Height  = 1
    Right Height = 0

    Difference = 1

At node 2:

    Left Height  = 2
    Right Height = 0

    Difference = 2

Since 2 > 1, node 2 is unbalanced.

Therefore:

    Output = false


IMPORTANT OBSERVATION:
----------------------

We cannot simply check whether the ROOT is balanced.

Every node must satisfy the height-balance condition.

Even if the root's immediate left and right subtree
heights differ by at most 1, a deeper subtree may
still be unbalanced.

Therefore, we need to check the entire tree.


================================================================================
2. UNDERSTANDING HEIGHT
================================================================================

Before solving this problem, we need to understand
how to calculate the height of a binary tree.

We use the following definition:

    Height of a tree = Maximum number of nodes
                       along a path from root to leaf.

For our implementation:

    height(nullptr) = 0

For a leaf node:

    Left Height  = 0
    Right Height = 0

    Height = 1 + max(0, 0)

    Height = 1

For any other node:

    Height = 1 + max(leftHeight, rightHeight)


C++ FORMULA:

    return 1 + max(leftAns, rightAns);


We use height measured in NODES.

This is important because the difference between
the left and right heights is what determines
whether a node is balanced.


================================================================================
3. INITIAL APPROACH: SEPARATE HEIGHT AND BALANCE CHECK
================================================================================

Our first idea was to create a helper function
that calculates the height of a subtree.

The helper:

    int depth(TreeNode* root)

The logic:

    1. If root is nullptr, return 0.
    2. Calculate the left subtree height.
    3. Calculate the right subtree height.
    4. Return 1 + maximum of both heights.

This helper correctly calculates the height.

Next, we could create another recursive function
to check whether the tree is balanced.

At every node:

    leftHeight = depth(root->left)

    rightHeight = depth(root->right)

    difference = abs(leftHeight - rightHeight)

    If difference > 1:
        return false

    Otherwise:
        Check the left and right subtrees.

The approach is logically correct.

HOWEVER, THERE IS A PERFORMANCE ISSUE.


================================================================================
4. WHY THE INITIAL APPROACH IS INEFFICIENT
================================================================================

Suppose we calculate the height of a subtree
while checking whether its parent is balanced.

Then, when we move to the child node, we calculate
the height of that child's subtree again.

This results in repeated recursive calculations.

For example:

                 1
                / \
               2   3
              / \
             4   5

When checking node 1:

    We calculate the height of its left subtree.
    We calculate the height of its right subtree.

When checking node 2:

    We calculate the heights of node 2's subtrees again.

The same nodes may be visited multiple times.

In a skewed tree, this approach can reach:

    O(n²) time complexity.

We need a better approach.

Our goal is:

    Calculate the height of every node only once.


================================================================================
5. THE IMPORTANT INSIGHT: COMBINE HEIGHT AND BALANCE CHECKING
================================================================================

Instead of using separate recursive traversals,
we can perform both operations in a single DFS traversal.

Our helper function will:

    1. Calculate the height of the current subtree.
    2. Check whether the current subtree is balanced.
    3. Communicate the result to its parent.

But there is one important challenge.

WHAT SHOULD THE HELPER RETURN?


================================================================================
6. WHY A BOOLEAN RETURN TYPE IS NOT ENOUGH
================================================================================

Initially, we considered changing the helper's
return type from int to bool.

For example:

    bool depth(TreeNode* root);

A Boolean function can tell us:

    true  = Balanced
    false = Unbalanced

But there is a problem.

We also need the HEIGHT of the subtree.

Consider a parent node.

To check whether the parent is balanced,
we need:

    Left Subtree Height
    Right Subtree Height

If our helper returns only true or false,
we lose the height information.

For example:

    Left subtree is balanced.
    Right subtree is balanced.

But what are their heights?

A Boolean return value cannot tell us.

We need to communicate TWO types of information:

    1. The height of the subtree.
    2. Whether the subtree is balanced.

We could use a pair or a custom structure,
but there is a simpler technique.


================================================================================
7. OPTIMIZED APPROACH: USING -1 AS A SENTINEL VALUE
================================================================================

This is the most important concept we learned
while solving this problem.

We continue using an integer-returning helper:

    int depth(TreeNode* root);

But we assign a special meaning to -1.

OUR RETURN VALUE CONVENTION:
----------------------------

    Non-negative integer:
        The subtree is balanced.
        The returned integer represents its height.

    -1:
        The subtree is unbalanced.

Examples:

    return 0:
        Empty subtree. Balanced.

    return 1:
        Balanced subtree with height 1.

    return 2:
        Balanced subtree with height 2.

    return 3:
        Balanced subtree with height 3.

    return -1:
        Unbalanced subtree.


WHY IS THIS USEFUL?

Normally, our helper returns the height.

But if it discovers that a subtree is unbalanced,
it returns -1 instead.

This allows the parent node to immediately recognize
that its child subtree is already unbalanced.

We no longer need to calculate a separate Boolean
result for every node.

We can communicate both pieces of information
through a single integer return value.


================================================================================
8. STEP-BY-STEP RECURSIVE LOGIC
================================================================================

Our optimized helper function follows these steps.


STEP 1: BASE CASE
-----------------

If the current node is nullptr:

    return 0;

An empty subtree has height zero.

It is considered balanced.


STEP 2: CALCULATE LEFT SUBTREE HEIGHT
-------------------------------------

    leftAns = depth(root->left);

The recursive call returns either:

    - A non-negative height.
    - -1 if the left subtree is unbalanced.


STEP 3: CALCULATE RIGHT SUBTREE HEIGHT
--------------------------------------

    rightAns = depth(root->right);

The recursive call returns either:

    - A non-negative height.
    - -1 if the right subtree is unbalanced.


STEP 4: CHECK FOR AN ALREADY UNBALANCED SUBTREE
------------------------------------------------

    if (leftAns == -1 || rightAns == -1) {
        return -1;
    }

This is extremely important.

If either child subtree is already unbalanced,
the current subtree cannot be balanced.

Therefore, we propagate -1 to the parent.

We do not treat -1 as an actual height.


STEP 5: CALCULATE THE HEIGHT DIFFERENCE
---------------------------------------

If both child subtrees are balanced,
we can safely calculate their height difference.

    diff = max(leftAns, rightAns) -
           min(leftAns, rightAns);

Why do we use max() and min()?

Because the absolute difference between two
non-negative heights is equivalent to:

    max(leftAns, rightAns) - min(leftAns, rightAns)

We could also write:

    abs(leftAns - rightAns)

Both are valid.


STEP 6: CHECK WHETHER THE CURRENT NODE IS BALANCED
--------------------------------------------------

    if (diff > 1) {
        return -1;
    }

If the difference is greater than 1,
the current node is unbalanced.

Therefore, return -1.


STEP 7: RETURN THE CURRENT SUBTREE HEIGHT
-----------------------------------------

If both child subtrees are balanced and the
current node's height difference is at most 1:

    return 1 + max(leftAns, rightAns);

This returns the height of the current subtree.

The parent can now use this height in its own
balance calculation.


================================================================================
9. COMPLETE OPTIMIZED C++ SOLUTION
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

    /*
     * Function: depth()
     *
     * Purpose:
     *     Calculates the height of a subtree and checks
     *     whether that subtree is balanced.
     *
     * Return convention:
     *
     *     Non-negative integer:
     *         Balanced subtree.
     *         Integer represents its height.
     *
     *     -1:
     *         Unbalanced subtree.
     *
     * Traversal:
     *     Postorder DFS.
     */
    int depth(TreeNode* root) {

        // Base case:
        // An empty subtree has height zero.
        if (root == nullptr) {
            return 0;
        }


        // Store the heights returned by recursive calls.
        int leftAns = 0;
        int rightAns = 0;

        int diff = 0;


        // Calculate the height of the left subtree.
        leftAns = depth(root->left);


        // Calculate the height of the right subtree.
        rightAns = depth(root->right);


        /*
         * If either child subtree is already unbalanced,
         * propagate -1 to the parent.
         *
         * -1 is our sentinel value.
         * It does NOT represent an actual height.
         */
        if (leftAns == -1 || rightAns == -1) {
            return -1;
        }


        /*
         * Both child subtrees are balanced.
         *
         * Calculate the absolute difference between
         * their heights.
         *
         * Since both values are non-negative,
         * max - min gives the absolute difference.
         */
        diff = max(leftAns, rightAns) -
               min(leftAns, rightAns);


        /*
         * If the height difference is greater than 1,
         * the current subtree is unbalanced.
         */
        if (diff > 1) {
            return -1;
        }


        /*
         * Both child subtrees are balanced,
         * and their height difference is at most 1.
         *
         * Return the height of the current subtree.
         */
        return 1 + max(leftAns, rightAns);
    }


public:

    /*
     * Function: isBalanced()
     *
     * Purpose:
     *     Determines whether the entire binary tree
     *     is height-balanced.
     *
     * Steps:
     *     1. Calculate the result using depth().
     *     2. If the result is -1, return false.
     *     3. Otherwise, return true.
     */
    bool isBalanced(TreeNode* root) {

        // An empty tree is balanced.
        if (root == nullptr) {
            return true;
        }


        // Calculate the height or receive the -1 sentinel.
        int ans = depth(root);


        // A non-negative result means the tree is balanced.
        if (ans != -1) {
            return true;
        }


        // -1 means that the tree is unbalanced.
        return false;
    }
};


/*
================================================================================
10. UNDERSTANDING THE RECURSION FLOW
================================================================================

The most important thing is understanding how
the recursive calls communicate with their parents.

Consider this tree:

                 1
                / \
               2   3
              / \
             4   5

We process the tree using postorder DFS.

The order is:

    Left subtree
    Right subtree
    Current node


NODE 4:
-------

    leftAns  = 0
    rightAns = 0

    diff = 0

    diff <= 1

    Return height = 1


NODE 5:
-------

    leftAns  = 0
    rightAns = 0

    diff = 0

    Return height = 1


NODE 2:
-------

    leftAns  = 1
    rightAns = 1

    diff = 0

    Return height:

        1 + max(1, 1) = 2


NODE 3:
-------

    leftAns  = 0
    rightAns = 0

    diff = 0

    Return height = 1


NODE 1:
-------

    leftAns  = 2
    rightAns = 1

    diff = 1

    Return height:

        1 + max(2, 1) = 3


FINAL RESULT:

    depth(root) = 3

    Since the result is not -1:

        isBalanced(root) = true


================================================================================
11. DRY RUN - UNBALANCED TREE
================================================================================

Consider:

                 1
                /
               2
              /
             3
            /
           4


Expected output:

    false


Let's follow the recursion.


NODE 4:
-------

    leftAns  = 0
    rightAns = 0

    diff = 0

    Return height = 1


NODE 3:
-------

    leftAns  = 1
    rightAns = 0

    diff = 1

    Return height = 2


NODE 2:
-------

    leftAns  = 2
    rightAns = 0

    diff = 2

    Since:

        diff > 1

    Return -1.


NODE 1:
-------

    leftAns = -1

    rightAns = 0

    The condition:

        leftAns == -1 || rightAns == -1

    becomes TRUE.

    Therefore:

        Return -1.


FINAL RESULT:

    depth(root) = -1

    Therefore:

        isBalanced(root) = false


IMPORTANT OBSERVATION:
----------------------

Once an unbalanced subtree returns -1,
its parent receives -1.

The parent propagates -1.

This continues while the recursive call stack unwinds.

Eventually, the original call receives -1.

The public function then returns false.


================================================================================
12. THE ACTUAL PROBLEM-SOLVING JOURNEY
================================================================================

This section records how we approached this problem
and the important decisions made along the way.


CHALLENGE 1: UNDERSTANDING THE BALANCE CONDITION
------------------------------------------------

Initially, we needed to understand what makes
a binary tree balanced.

The important realization was:

    Every node must satisfy:

        |leftHeight - rightHeight| <= 1

It is not sufficient to check only the root.

A deeper subtree can be unbalanced even when
the root's immediate height difference is acceptable.


CHALLENGE 2: CREATING A HEIGHT HELPER
-------------------------------------

We started by writing a helper:

    int depth(TreeNode* root)

The helper calculates the height of a subtree.

The formula:

    return 1 + max(leftAns, rightAns);

This part was already correct.

However, repeatedly using this helper separately
inside another recursive balance-checking function
could result in O(n²) time complexity.


CHALLENGE 3: CONSIDERING A BOOLEAN RETURN TYPE
----------------------------------------------

We considered returning bool from the helper.

However, we realized that we needed two things:

    - Whether the subtree is balanced.
    - The height of the subtree.

A Boolean return value provides only one piece
of information.

We needed another way to communicate both.


CHALLENGE 4: DISCOVERING THE SENTINEL TECHNIQUE
-----------------------------------------------

We decided to keep the return type as int.

We assigned a special meaning to -1:

    -1 = Unbalanced subtree.

Any non-negative value represents the height
of a balanced subtree.

This allowed us to communicate both the height
and balance status using one integer.


CHALLENGE 5: PROPAGATING THE UNBALANCED STATE
---------------------------------------------

We needed to understand what happens when
a recursive call returns -1.

The important condition became:

    if (leftAns == -1 || rightAns == -1) {
        return -1;
    }

This prevents us from treating -1 as an actual height.

The unbalanced state propagates upward
through the recursive call stack.


CHALLENGE 6: CHECKING THE CURRENT NODE
--------------------------------------

If both child subtrees are balanced,
we calculate their height difference.

    diff = max(leftAns, rightAns) -
           min(leftAns, rightAns);

If:

    diff > 1

The current subtree is unbalanced.

Therefore:

    return -1;


CHALLENGE 7: RETURNING THE HEIGHT
---------------------------------

If neither child is unbalanced and the current
difference is at most 1, we return:

    1 + max(leftAns, rightAns);

This allows the parent to continue its own
balance calculation.


================================================================================
13. WHY POSTORDER DFS?
================================================================================

We use postorder traversal:

    Left -> Right -> Root

Why?

Because the current node cannot determine whether
it is balanced until it knows the heights of
both child subtrees.

Therefore, we first process the children.

After receiving their results, we process
the current node.

This is exactly what postorder traversal provides.

The recursive calls naturally perform this order.


================================================================================
14. TIME COMPLEXITY ANALYSIS
================================================================================

Let n represent the total number of nodes in the tree.


TIME COMPLEXITY: O(n)
---------------------

Every node is visited at most once.

At every node, we perform constant-time operations:

    - Compare the left and right results.
    - Check whether either result is -1.
    - Calculate the height difference.
    - Calculate the current height.

There are no repeated height calculations.

Therefore:

    Time Complexity = O(n)


AUXILIARY SPACE COMPLEXITY: O(h)
--------------------------------

The recursive calls use the call stack.

The maximum recursion depth depends on the
height of the tree.

For a balanced tree:

    h = O(log n)

For a completely skewed tree:

    h = O(n)

Therefore:

    Auxiliary Space = O(h)

Worst-case auxiliary space:

    O(n)


================================================================================
15. COMPARISON: INITIAL APPROACH VS OPTIMIZED APPROACH
================================================================================

INITIAL APPROACH:
-----------------

    1. Calculate left subtree height.
    2. Calculate right subtree height.
    3. Check the difference.
    4. Recursively check both subtrees.

Problem:

    Repeated height calculations.

Time Complexity:

    O(n²) in the worst case.


OPTIMIZED APPROACH:
-------------------

    1. Calculate left subtree result.
    2. Calculate right subtree result.
    3. Propagate -1 if either subtree is unbalanced.
    4. Check the current height difference.
    5. Return the current height.

Advantage:

    Each node is processed at most once.

Time Complexity:

    O(n)


================================================================================
16. IMPORTANT EDGE CASES
================================================================================

CASE 1: EMPTY TREE

        nullptr

    Expected output: true

    Reason:
        An empty tree is balanced.


CASE 2: SINGLE NODE

        1

    Expected output: true

    Reason:
        Both subtree heights are zero.


CASE 3: TWO CHILDREN

          1
         / \
        2   3

    Expected output: true

    Reason:
        Height difference = 0.


CASE 4: LEFT-SKEWED TREE

          1
         /
        2
       /
      3

    Expected output: false

    Reason:
        At node 1, the height difference is 2.


CASE 5: RIGHT-SKEWED TREE

        1
         \
          2
           \
            3

    Expected output: false

    Reason:
        At node 1, the height difference is 2.


CASE 6: BALANCED ROOT, UNBALANCED SUBTREE

                 1
                / \
               2   3
              /
             4
            /
           5

    Expected output: false

    Reason:
        Node 2 is unbalanced.

        Even if the root's immediate height difference
        is acceptable, the entire tree is not balanced.


================================================================================
17. INTERVIEW EXPLANATION
================================================================================

If an interviewer asks you to explain your solution,
you can say:

"I solve this problem using postorder DFS.

My recursive helper calculates the height of a subtree
while also checking whether that subtree is balanced.

A balanced subtree returns its height.

An unbalanced subtree returns -1, which I use as
a sentinel value.

First, I recursively calculate the results of the
left and right subtrees.

If either result is -1, I immediately propagate -1
because the current subtree cannot be balanced.

Otherwise, I calculate the difference between
the two subtree heights.

If the difference is greater than 1, I return -1.

If the difference is at most 1, I return one plus
the maximum of the two heights.

This allows me to calculate heights and verify
balance in a single traversal.

Every node is processed at most once, giving O(n)
time complexity.

The recursion stack requires O(h) auxiliary space."


================================================================================
18. IMPORTANT INTERVIEW LESSONS
================================================================================

1. POSTORDER DFS

   Process children before the parent when the
   parent depends on information from its children.


2. SENTINEL VALUES

   A special return value can communicate an
   exceptional state through recursion.

   Here:

       -1 = Unbalanced.


3. COMBINING INFORMATION

   We can communicate both the height and balance
   status through one integer return value.


4. RECURSIVE PROPAGATION

   Once a subtree becomes unbalanced, the information
   can propagate all the way to the root.


5. AVOIDING REPEATED WORK

   Calculate each subtree's height only once.


6. RECOGNIZING BASE CASES

   An empty subtree has height zero and is balanced.


7. CHECKING EVERY NODE

   A tree is balanced only when every node satisfies
   the height-difference condition.


================================================================================
19. FINAL SUMMARY
================================================================================

PROBLEM:
    LeetCode 110 - Balanced Binary Tree

APPROACH:
    Optimized DFS + Postorder Traversal

HELPER FUNCTION:
    int depth(TreeNode* root)

BASE CASE:
    if (root == nullptr)
        return 0;

BALANCED SUBTREE:
    Return its height.

UNBALANCED SUBTREE:
    Return -1.

PROPAGATION CONDITION:

    if (leftAns == -1 || rightAns == -1)
        return -1;

HEIGHT DIFFERENCE:

    diff = max(leftAns, rightAns) -
           min(leftAns, rightAns);

UNBALANCED CONDITION:

    if (diff > 1)
        return -1;

HEIGHT FORMULA:

    return 1 + max(leftAns, rightAns);

FINAL CHECK:

    depth(root) != -1

    true  = Balanced
    false = Unbalanced

TIME COMPLEXITY:
    O(n)

AUXILIARY SPACE:
    O(h)

MOST IMPORTANT LESSON:

    Use a sentinel value to communicate an
    unbalanced subtree through recursive calls.

    This eliminates repeated height calculations
    and allows the entire problem to be solved
    in one DFS traversal.

================================================================================
                         END OF SOLUTION
================================================================================
*/
