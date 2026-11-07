
/*
================================================================================
                    LEETCODE 543 - DIAMETER OF BINARY TREE
================================================================================

Problem:
--------
Given the root of a binary tree, return the length of the diameter of the tree.

The diameter of a binary tree is defined as the length of the longest path
between any two nodes in the tree.

This path may or may not pass through the root.

IMPORTANT:
The length of a path is measured by the NUMBER OF EDGES between nodes,
not by the number of nodes.

LeetCode:
---------
Problem Number : 543
Difficulty     : Medium
Topic          : Binary Trees
Category       : Tree / DFS / Recursion
Technique      : Postorder DFS + Height Calculation
Time           : O(n)
Space          : O(h)

================================================================================
1. UNDERSTANDING THE PROBLEM
================================================================================

We are given a binary tree, and our task is to calculate its diameter.

The diameter represents the longest possible path between any two nodes.

For example:

                1
               / \
              2   3
             / \
            4   5

The longest path is:

        4 -> 2 -> 1 -> 3

This path contains:

    4 nodes
    3 edges

Therefore:

    Diameter = 3

Remember that LeetCode asks for the number of EDGES, not nodes.

An important observation:

The longest path does not necessarily have to pass through the root.

Consider:

                 1
                /
               2
              / \
             3   4
            /     \
           5       6

The longest path is:

    5 -> 3 -> 2 -> 4 -> 6

The diameter is 4 edges.

The key challenge is to calculate the longest path efficiently
without repeatedly calculating subtree heights.


================================================================================
2. MATHEMATICAL OBSERVATION
================================================================================

Consider any node in the binary tree.

The longest path passing THROUGH that node can be calculated using:

    Diameter Through Current Node =
        Height of Left Subtree + Height of Right Subtree

Mathematically:

    D = L + R

Where:

    L = Height of the left subtree
    R = Height of the right subtree

Why does this work?

A path passing through a node can extend:

    - Down through its left subtree.
    - Down through its right subtree.

The longest such path combines the maximum possible extension
from both sides.

However, the diameter of the entire tree is not necessarily
the diameter through the root.

Therefore, we must calculate this value at EVERY node
and maintain the maximum diameter encountered.

Our global answer becomes:

    diameter = max(diameter, leftHeight + rightHeight)


================================================================================
3. FIRST APPROACH: BRUTE FORCE
================================================================================

Our first idea can be:

    1. Calculate the height of the left subtree.
    2. Calculate the height of the right subtree.
    3. Calculate their sum.
    4. Update the maximum diameter.
    5. Repeat this process for every node.

We could implement this using two separate recursive functions:

    - height(): Calculates the height of a subtree.
    - diameter(): Calculates the maximum diameter.

Pseudocode:

    diameter(root):

        if root == nullptr:
            return 0

        leftHeight = height(root->left)
        rightHeight = height(root->right)

        currentDiameter = leftHeight + rightHeight

        leftDiameter = diameter(root->left)
        rightDiameter = diameter(root->right)

        return max(currentDiameter,
                   max(leftDiameter, rightDiameter))

This approach is logically correct.

PROBLEM WITH THIS APPROACH:
---------------------------

The height() function may repeatedly visit the same nodes.

For example:

    When calculating the diameter at the root,
    we calculate the heights of its subtrees.

    Then, when calculating the diameter at its children,
    we calculate those subtree heights again.

    This repeated work increases the time complexity.

Worst-case time complexity:

    O(n²)

For a balanced tree, the complexity can be better,
but in a skewed tree, it can reach O(n²).

We want to eliminate this unnecessary repeated work.


================================================================================
4. OPTIMIZED APPROACH: HEIGHT + DIAMETER
================================================================================

Instead of calculating height separately for every node,
we can calculate the height and update the diameter
during the SAME recursive traversal.

This is the main optimization.

We use:

    1. A recursive height() function.
    2. A class-level variable named diameter.

The height() function will do TWO things:

    A. Return the height of the current subtree.
    B. Update the maximum diameter encountered so far.

This allows us to solve the problem in O(n) time.


================================================================================
5. HOW THE RECURSION WORKS
================================================================================

We use a postorder DFS traversal.

Postorder means:

    1. Process the left subtree.
    2. Process the right subtree.
    3. Process the current node.

Why postorder?

Because to calculate the height of the current node,
we must first know the heights of its left and right subtrees.

The recursive process is:

    height(root):

        if root == nullptr:
            return 0

        leftHeight = height(root->left)

        rightHeight = height(root->right)

        diameter = max(diameter,
                       leftHeight + rightHeight)

        return 1 + max(leftHeight, rightHeight)


WHY RETURN 1 + MAXIMUM HEIGHT?
------------------------------

We are calculating height using the NUMBER OF NODES.

For a null node:

    height(nullptr) = 0

For a leaf node:

    leftHeight  = 0
    rightHeight = 0

    height(leaf) = 1 + max(0, 0)
                 = 1

For any other node:

    height(node) = 1 + max(leftHeight, rightHeight)

The additional 1 represents the current node.


WHY IS DIAMETER = LEFT HEIGHT + RIGHT HEIGHT?
---------------------------------------------

We are measuring diameter in EDGES.

Suppose:

    leftHeight  = 2
    rightHeight = 3

The longest path passing through the current node contains:

    2 + 3 = 5 edges

The current node itself is not counted as an additional edge.

This is why we do NOT add 1 to the diameter calculation.

Notice the difference:

    Height    = 1 + max(leftHeight, rightHeight)

    Diameter  = leftHeight + rightHeight


================================================================================
6. IMPLEMENTATION
================================================================================

The implementation uses a class-level variable to maintain
the maximum diameter.

We initialize it to zero.

During recursion, every node calculates the longest path
passing through itself.

We update the variable whenever we find a larger diameter.

After the recursion finishes, the variable contains
the diameter of the entire tree.


================================================================================
7. COMPLETE OPTIMIZED C++ SOLUTION
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

    // Stores the maximum diameter found during DFS.
    int diameter = 0;


    /*
     * Function: height()
     *
     * Purpose:
     *     Calculates the height of a binary tree using recursion.
     *
     * Additional responsibility:
     *     Updates the maximum diameter while calculating heights.
     *
     * Return:
     *     Height of the current subtree, measured in nodes.
     *
     * Traversal:
     *     Postorder DFS.
     */
    int height(TreeNode* root) {

        // Base case:
        // An empty subtree has height zero.
        if (root == nullptr) {
            return 0;
        }


        // Calculate the height of the left subtree.
        int leftHeight = height(root->left);


        // Calculate the height of the right subtree.
        int rightHeight = height(root->right);


        /*
         * Calculate the longest path passing through
         * the current node.
         *
         * Both heights are measured in nodes.
         * Their sum represents the number of edges
         * in the path passing through this node.
         */
        int currentDiameter = leftHeight + rightHeight;


        // Maintain the maximum diameter found so far.
        diameter = max(diameter, currentDiameter);


        /*
         * Return the height of the current subtree.
         *
         * Height = 1 + maximum height of either subtree.
         *
         * The additional 1 represents the current node.
         */
        return 1 + max(leftHeight, rightHeight);
    }


public:

    /*
     * Function: diameterOfBinaryTree()
     *
     * Purpose:
     *     Returns the diameter of the entire binary tree.
     *
     * Steps:
     *     1. Reset the diameter variable.
     *     2. Perform DFS using height().
     *     3. Return the maximum diameter.
     */
    int diameterOfBinaryTree(TreeNode* root) {

        /*
         * IMPORTANT:
         *
         * Reset the class-level variable before processing
         * a new tree.
         *
         * This ensures that previous test cases do not
         * affect the result when the same Solution object
         * is used for multiple function calls.
         */
        diameter = 0;


        // An empty tree has a diameter of zero.
        if (root == nullptr) {
            return 0;
        }


        // Calculate heights and update diameter in one traversal.
        height(root);


        // Return the maximum diameter found.
        return diameter;
    }
};


/*
================================================================================
8. DRY RUN - EXAMPLE 1
================================================================================

Consider the following tree:

                 1
                / \
               2   3
              / \
             4   5


Expected longest path:

    4 -> 2 -> 1 -> 3

Number of edges:

    3

Therefore:

    Expected Diameter = 3


RECURSION EXECUTION:
--------------------

STEP 1:
    We start from node 1.

    The function recursively visits the left subtree first.

STEP 2:
    We reach node 4.

    Node 4 is a leaf.

    leftHeight  = 0
    rightHeight = 0

    currentDiameter = 0 + 0 = 0

    diameter = max(0, 0) = 0

    Return height = 1


STEP 3:
    We return to node 2.

    Its left subtree (node 4) has height 1.

    We now visit its right subtree (node 5).

    Node 5 is also a leaf.

    Return height = 1


STEP 4:
    We process node 2.

    leftHeight  = 1
    rightHeight = 1

    currentDiameter = 1 + 1 = 2

    diameter = max(0, 2) = 2

    Return height:

        1 + max(1, 1) = 2


STEP 5:
    We return to node 1.

    Now we process the right subtree (node 3).

    Node 3 is a leaf.

    Return height = 1


STEP 6:
    We process the root node 1.

    leftHeight  = 2
    rightHeight = 1

    currentDiameter = 2 + 1 = 3

    diameter = max(2, 3) = 3

    Return height:

        1 + max(2, 1) = 3


FINAL RESULT:

    diameter = 3

    Output = 3


================================================================================
9. DRY RUN - EXAMPLE 2
================================================================================

Consider:

                 1
                /
               2
              / \
             3   4
            /     \
           5       6


The longest path is:

    5 -> 3 -> 2 -> 4 -> 6

Number of edges = 4

The important observation here is that the diameter
is not necessarily calculated at the root's immediate
left and right children.

It is updated whenever a node produces a larger
leftHeight + rightHeight value.

This is why we maintain a maximum diameter variable
throughout the recursive traversal.


================================================================================
10. ISSUES ENCOUNTERED AND HOW WE RESOLVED THEM
================================================================================

ISSUE 1: REPEATED HEIGHT CALCULATIONS
-------------------------------------

Initial thinking:

    Calculate the height of every node's left and right
    subtrees separately.

Problem:

    The same nodes can be visited multiple times.

Resolution:

    Combine height calculation and diameter updating
    into a single recursive traversal.

Result:

    Time complexity improves from O(n²) to O(n).


ISSUE 2: UNDERSTANDING HEIGHT VS DIAMETER
----------------------------------------

Initially, it is easy to confuse the two calculations.

Height:

    1 + max(leftHeight, rightHeight)

Diameter through a node:

    leftHeight + rightHeight

Why are they different?

    Height measures the maximum number of nodes
    along a downward path.

    Diameter measures the number of edges along
    a path connecting the left and right sides.

Resolution:

    We consistently calculate height in nodes
    and diameter in edges.

    This makes the formulas straightforward.


ISSUE 3: DIAMETER MAY NOT PASS THROUGH THE ROOT
-----------------------------------------------

A common mistake is to calculate only:

    height(root->left) + height(root->right)

This only calculates the longest path passing
through the root.

However, the actual diameter may exist entirely
inside one subtree.

Resolution:

    Update the diameter at EVERY node.

    Use:

        diameter = max(diameter,
                       leftHeight + rightHeight)

    This ensures that we never miss a larger path
    located deeper inside the tree.


ISSUE 4: WHY DO WE NEED A CLASS-LEVEL VARIABLE?
-----------------------------------------------

The recursive height function needs to return the
height of a subtree.

But we also need to maintain the maximum diameter
found anywhere in the tree.

If the function only returns height, it cannot
simultaneously return the maximum diameter using
a single integer return value.

Resolution:

    Use a class-level variable:

        int diameter = 0;

    The height() function returns subtree height
    while updating diameter as a side effect.

    This allows both pieces of information to be
    maintained during one traversal.


ISSUE 5: LEAF NODE HANDLING
---------------------------

An earlier implementation included a special condition:

    if (root->left == nullptr && root->right == nullptr) {
        return 1;
    }

This is logically correct.

However, it is unnecessary.

Why?

    For a leaf node:

        leftHeight  = 0
        rightHeight = 0

    Therefore:

        diameter = max(diameter, 0 + 0)

    And:

        height = 1 + max(0, 0) = 1

Resolution:

    We removed the special leaf-node condition.

    The normal recursive logic already handles leaf nodes.

    This makes the implementation simpler and cleaner.


ISSUE 6: RESETTING THE DIAMETER VARIABLE
----------------------------------------

The diameter variable is a class-level member.

Suppose the same Solution object is used to process
two different trees.

If we do not reset diameter, the second tree may
inherit the diameter from the first tree.

For example:

    First tree diameter = 7

    Second tree diameter = 2

Without resetting the variable, the second call
could incorrectly return 7.

Resolution:

    Reset the variable at the beginning of every call:

        diameter = 0;

This ensures that every tree is processed independently.


================================================================================
11. DEBUGGING AND PROBLEM-SOLVING APPROACH
================================================================================

Our problem-solving journey involved the following steps:

1. We first understood that diameter means the longest
   path between any two nodes.

2. We identified that the path length is measured
   in edges, not nodes.

3. We observed that the longest path passing through
   a node is the sum of its left and right subtree heights.

4. We realized that the diameter might exist inside
   any subtree, not necessarily through the root.

5. We considered calculating heights independently.

6. We identified repeated recursive calculations
   as the main inefficiency.

7. We optimized the approach by calculating height
   and updating diameter in the same DFS traversal.

8. We used a class-level variable to maintain
   the maximum diameter.

9. We used postorder traversal because the current
   node needs the heights of both children first.

10. We removed unnecessary special handling for leaf nodes.

11. We reset the diameter variable before each new
    function call to ensure correct behavior.

The final approach processes each node once.


================================================================================
12. TIME COMPLEXITY ANALYSIS
================================================================================

Let n represent the total number of nodes in the tree.

TIME COMPLEXITY: O(n)
---------------------

Every node is visited exactly once by height().

At each node, we perform constant-time operations:

    - Compare two heights.
    - Add two heights.
    - Update the maximum diameter.
    - Calculate the current height.

Therefore:

    T(n) = O(n)


AUXILIARY SPACE COMPLEXITY: O(h)
--------------------------------

The recursive calls use the call stack.

The maximum recursion depth depends on the height of
the binary tree.

For a balanced binary tree:

    h = O(log n)

Therefore:

    Space = O(log n)

For a completely skewed binary tree:

    h = O(n)

Therefore:

    Space = O(n)

General auxiliary space complexity:

    O(h)

Worst-case auxiliary space complexity:

    O(n)

NOTE:

The diameter variable itself requires O(1) space.
The recursion stack is responsible for O(h) space.


================================================================================
13. IMPORTANT CONCEPTS LEARNED
================================================================================

This problem reinforces several important tree concepts.

1. DFS (Depth-First Search)
   We explore a subtree deeply before processing its parent.

2. POSTORDER TRAVERSAL
   Left subtree -> Right subtree -> Current node.

3. RECURSION
   Each recursive call solves the height problem
   for a smaller subtree.

4. TREE HEIGHT
   Maximum number of nodes from a node to a leaf.

5. TREE DIAMETER
   Maximum number of edges between any two nodes.

6. GLOBAL / CLASS-LEVEL STATE
   Used to maintain an answer while recursion returns
   information through its call stack.

7. OPTIMIZATION
   Combining multiple recursive operations into one
   traversal avoids repeated work.

8. EDGE CASES
   Empty trees, single-node trees, balanced trees,
   and skewed trees must all be handled correctly.


================================================================================
14. EDGE CASES TO TEST
================================================================================

CASE 1: EMPTY TREE

        root = nullptr

    Expected output: 0


CASE 2: SINGLE NODE

        1

    Expected output: 0

    Reason:
        There are no edges.


CASE 3: TWO NODES

        1
       /
      2

    Expected output: 1


CASE 4: THREE NODES

        1
       / \
      2   3

    Expected output: 2


CASE 5: COMPLETELY SKEWED TREE

        1
         \
          2
           \
            3
             \
              4

    Expected output: 3

    Reason:
        The longest path contains three edges.


CASE 6: DIAMETER INSIDE A SUBTREE

                 1
                /
               2
              / \
             3   4
            /     \
           5       6

    Expected output: 4

    Reason:
        The longest path is entirely contained
        in the left subtree of the root.


================================================================================
15. INTERVIEW EXPLANATION
================================================================================

If an interviewer asks you to explain your solution,
you can present it like this:

"I use a postorder DFS traversal to solve this problem.

The key observation is that the longest path passing
through any particular node is the sum of the heights
of its left and right subtrees.

I maintain a class-level variable called diameter
to store the maximum value encountered.

My recursive height function first calculates the
height of the left subtree and then the height of
the right subtree.

Once both heights are available, I calculate their
sum and update the maximum diameter.

Finally, the function returns one plus the maximum
of the two subtree heights.

This way, I calculate subtree heights and update
the diameter in the same traversal.

Every node is visited exactly once, so the time
complexity is O(n).

The recursion stack requires O(h) auxiliary space,
where h is the height of the tree."



/*
================================================================================
16. FINAL TAKEAWAYS
================================================================================

PROBLEM:
    LeetCode 543 - Diameter of Binary Tree

APPROACH:
    Optimized DFS + Postorder Traversal

MAIN OBSERVATION:
    Diameter through a node =
    Left subtree height + Right subtree height

HEIGHT FORMULA:
    1 + max(leftHeight, rightHeight)

DIAMETER FORMULA:
    leftHeight + rightHeight

ANSWER UPDATE:
    diameter = max(diameter,
                   leftHeight + rightHeight)

TIME COMPLEXITY:
    O(n)

AUXILIARY SPACE:
    O(h)

KEY OPTIMIZATION:
    Calculate height and update diameter
    in the same recursive traversal.

MOST IMPORTANT LESSON:
    Do not repeatedly calculate subtree heights.
    Use information returned by recursive calls
    to solve the problem efficiently.

================================================================================
                         END OF SOLUTION
================================================================================
*/
