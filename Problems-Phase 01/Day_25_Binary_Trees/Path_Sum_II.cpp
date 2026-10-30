
/*
===============================================================================
                    DSA JOURNEY — DAY 25
===============================================================================

PROBLEM:
    LeetCode 113 — Path Sum II

TOPIC:
    Binary Trees | Depth First Search | Recursion | Backtracking

DIFFICULTY:
    Medium

PROBLEM LINK:
    https://leetcode.com/problems/path-sum-ii/

===============================================================================
1. PROBLEM STATEMENT
===============================================================================

Given the root of a binary tree and an integer targetSum, return all
root-to-leaf paths where the sum of the node values in each path equals
targetSum.

A root-to-leaf path is a path starting from the root and ending at a leaf
node.

A leaf node is a node that has no left child and no right child.

We must return all valid paths in the form of a 2D vector.

IMPORTANT:
    - We can only travel from parent to child.
    - We must start at the root.
    - We must finish at a leaf node.
    - The sum must equal targetSum.
    - We must collect ALL valid paths, not just one.

===============================================================================
2. UNDERSTANDING THE PROBLEM
===============================================================================

Consider the following binary tree:

                         5
                       /   \
                      4     8
                     /     / \
                    11    13  4
                   /  \       / \
                  7    2     5   1

Target Sum = 22

We need to find every root-to-leaf path whose sum equals 22.

Let's examine the possible root-to-leaf paths.

PATH 1:
    5 -> 4 -> 11 -> 7

    Sum = 5 + 4 + 11 + 7
        = 27

    Not valid.

PATH 2:
    5 -> 4 -> 11 -> 2

    Sum = 5 + 4 + 11 + 2
        = 22

    VALID!

PATH 3:
    5 -> 8 -> 13

    Sum = 5 + 8 + 13
        = 26

    Not valid.

PATH 4:
    5 -> 8 -> 4 -> 5

    Sum = 5 + 8 + 4 + 5
        = 22

    VALID!

PATH 5:
    5 -> 8 -> 4 -> 1

    Sum = 5 + 8 + 4 + 1
        = 18

    Not valid.

EXPECTED OUTPUT:

    [
        [5, 4, 11, 2],
        [5, 8, 4, 5]
    ]

Our task is to discover these paths using recursion.

===============================================================================
3. DEVELOPING THE INTUITION
===============================================================================

Before writing code, we need to understand how we can solve this problem.

The first question is:

How can we explore every possible root-to-leaf path?

A binary tree gives us two possible directions at every node:

    1. Left child
    2. Right child

We can use Depth First Search (DFS).

DFS explores one branch deeply before returning and exploring another
branch.

For example:

                         5
                       /   \
                      4     8
                     /
                    11
                   /  \
                  7    2

We start at node 5.

We move to its left child, 4.

Then we move to 4's left child, 11.

Then we explore 11's left child, 7.

After finishing that branch, recursion returns to node 11.

Now we explore 11's right child, 2.

This is exactly what DFS does.

But simply visiting nodes is not enough.

We need to maintain two important pieces of information:

    1. The sum of the current path.
    2. The actual nodes belonging to the current path.

This leads us to two variables:

    currentSum
    vector<int> v

We also need a 2D vector to store all valid paths:

    vector<vector<int>> ans

===============================================================================
4. UNDERSTANDING OUR DATA STRUCTURES
===============================================================================

A. currentSum

    int currentSum = 0;

This variable maintains the sum of all nodes in the current root-to-node
path.

For example:

    Root = 5

    Move to 4:

        currentSum = 5 + 4
                   = 9

    Move to 11:

        currentSum = 9 + 11
                   = 20

    Move to 2:

        currentSum = 20 + 2
                   = 22

Now currentSum equals targetSum.

However, we must also verify that node 2 is a leaf.

B. vector<int> v

    vector<int> v;

This vector stores the actual nodes belonging to our current path.

For the path:

    5 -> 4 -> 11 -> 2

Our vector contains:

    v = {5, 4, 11, 2}

Why do we need this vector?

Because currentSum only tells us the total sum.

It does not tell us which nodes produced that sum.

We need the vector to save the complete path in our answer.

C. vector<vector<int>> ans

    vector<vector<int>> ans;

This stores all valid root-to-leaf paths.

For example:

    ans = {
        {5, 4, 11, 2},
        {5, 8, 4, 5}
    };

Whenever we discover a valid path, we copy the current vector into ans.

We use:

    ans.push_back(v);

IMPORTANT:

This creates a copy of the current path.

Therefore, modifying v later during backtracking does not modify the
path already stored in ans.

===============================================================================
5. DESIGNING OUR RECURSIVE FUNCTION
===============================================================================

Our helper function:

    void solve(
        TreeNode* root,
        vector<vector<int>>& ans,
        vector<int>& v,
        int target
    )

Let's understand every parameter.

1. TreeNode* root

    Represents the current node being processed.

    As recursion moves through the tree, root changes to the current node
    of each recursive invocation.

2. vector<vector<int>>& ans

    Stores all valid root-to-leaf paths.

    We pass it by reference because every recursive invocation must
    contribute to the same answer vector.

3. vector<int>& v

    Stores the nodes belonging to the current path.

    We pass it by reference because we want to modify the same path vector
    while moving down and backtracking while returning.

4. int target

    Represents the required target sum.

    We compare currentSum against this value.

===============================================================================
6. STEP-BY-STEP IMPLEMENTATION
===============================================================================

STEP 1: BASE CASE

    if (root == nullptr) {
        return;
    }

WHY?

When root is nullptr, there is no node to process.

We immediately return from that particular recursive invocation.

This does NOT mean the entire recursion terminates.

Control returns to the caller, which can continue executing its remaining
instructions.

This is important for understanding recursive control flow.

STEP 2: ADD THE CURRENT NODE TO OUR SUM

    currentSum += root->val;

WHY?

We are moving through a root-to-leaf path.

Every time we visit a node, we must include its value in the current path
sum.

For example:

    Visit 5:

        currentSum = 5

    Visit 4:

        currentSum = 5 + 4 = 9

    Visit 11:

        currentSum = 9 + 11 = 20

    Visit 2:

        currentSum = 20 + 2 = 22

STEP 3: ADD THE CURRENT NODE TO OUR PATH VECTOR

    v.push_back(root->val);

WHY?

We need to preserve the actual nodes of the current path.

For example:

    Visit 5:

        v = {5}

    Visit 4:

        v = {5, 4}

    Visit 11:

        v = {5, 4, 11}

    Visit 2:

        v = {5, 4, 11, 2}

STEP 4: CHECK WHETHER WE FOUND A VALID PATH

    if (
        currentSum == target &&
        root->left == nullptr &&
        root->right == nullptr
    ) {
        ans.push_back(v);
    }

There are THREE things to understand here.

CONDITION 1:

    currentSum == target

The current path's sum must equal the target sum.

CONDITION 2:

    root->left == nullptr

The current node must not have a left child.

CONDITION 3:

    root->right == nullptr

The current node must not have a right child.

Why do we check both children?

Because the problem specifically requires a root-to-leaf path.

A node is a leaf only when BOTH its children are nullptr.

We cannot accept a path merely because its sum equals targetSum.

For example:

    5
   /
  4
 /
11
/
7

If a non-leaf node happens to produce the target sum, we cannot save that
path because the path has not reached a leaf.

When all conditions are satisfied:

    ans.push_back(v);

We save a copy of the complete current path.

IMPORTANT:

We do NOT return immediately after finding a valid path.

We still allow the recursive function to continue its normal execution
and perform cleanup.

STEP 5: EXPLORE THE LEFT SUBTREE

    solve(root->left, ans, v, target);

We recursively process the left child.

STEP 6: EXPLORE THE RIGHT SUBTREE

    solve(root->right, ans, v, target);

After the left recursive call finishes, execution resumes and the right
recursive call is made.

This allows us to explore both sides of the current node.

STEP 7: BACKTRACKING

    currentSum -= root->val;
    v.pop_back();

This is one of the most important parts of the entire solution.

WHY DO WE NEED BACKTRACKING?

Suppose we have:

                         5
                       /   \
                      4     8
                     /     / \
                    11    13  4
                   /  \       / \
                  7    2     5   1

We explore the left subtree first.

Our path becomes:

    5 -> 4 -> 11 -> 7

After finishing node 7, we return to node 11.

We must remove 7 from our current path before exploring 11's right child.

Then we explore:

    5 -> 4 -> 11 -> 2

If we do not remove 7, our vector would incorrectly contain:

    {5, 4, 11, 7, 2}

That is not a valid root-to-leaf path.

Therefore, we must undo the changes made when entering the current node.

We perform:

    currentSum -= root->val;

This removes the current node's contribution from the running sum.

And:

    v.pop_back();

This removes the current node from the path vector.

IMPORTANT:

We must perform this cleanup exactly once for every non-null recursive
invocation.

This is the backtracking process.

===============================================================================
7. UNDERSTANDING RECURSION AND THE CALL STACK
===============================================================================

This problem helped us understand how recursive calls execute and return.

Let's examine this path:

    5 -> 4 -> 11 -> 2

Suppose we are currently visiting node 2.

Our recursive calls have created separate function invocations.

Conceptually:

    solve(5)
        solve(4)
            solve(11)
                solve(2)

Each invocation has its own root pointer and its own execution position.

When node 2 finishes processing:

    1. It performs its cleanup.
    2. Its function invocation completes.
    3. Control returns to its caller, node 11.

Node 11 resumes from the instruction immediately after its recursive call.

It can then explore its right child, if it has one.

After finishing both children, node 11 performs its own cleanup and returns
to node 4.

This continues until the original invocation finishes.

IMPORTANT CONCEPT:

C++ manages the call stack automatically.

It remembers:

    - Which function invocation is currently executing.
    - Where execution should resume after a recursive call returns.
    - The local state of each invocation.

However, WE decide what happens when execution resumes.

Our code determines:

    - What information is returned.
    - Which subtree is explored next.
    - What conditions are checked.
    - What cleanup must happen.
    - What information is passed back to the parent.

The programming language manages the call stack.

Our algorithm determines the behavior.

===============================================================================
8. THE DEBUGGING JOURNEY — RUNTIME ERROR
===============================================================================

During our initial implementation, we encountered an important issue.

We received an AddressSanitizer error:

    AddressSanitizer: heap-buffer-overflow

The error occurred around vector operations.

The problem was caused by incorrect backtracking.

OUR INITIAL LOGIC:

We were performing cleanup inside the leaf-node conditions.

Conceptually, the code looked like this:

    if (currentSum == target &&
        root->left == nullptr &&
        root->right == nullptr) {

        ans.push_back(v);

        currentSum -= root->val;
        v.pop_back();
    }
    else if (root->left == nullptr &&
             root->right == nullptr) {

        currentSum -= root->val;
        v.pop_back();
    }

    solve(root->left, ans, v, target);
    solve(root->right, ans, v, target);

    currentSum -= root->val;
    v.pop_back();

WHAT WAS WRONG?

We were cleaning up a leaf node inside the if/else branches.

But after those branches finished, execution continued to the final cleanup:

    currentSum -= root->val;
    v.pop_back();

Therefore, the same node was removed TWICE.

Let's understand the problem.

Suppose our current vector is:

    v = {5, 4, 11, 2}

We reach leaf node 2.

Inside the leaf condition, we execute:

    v.pop_back();

Now:

    v = {5, 4, 11}

Then execution reaches the final cleanup:

    v.pop_back();

Now:

    v = {5, 4}

We have accidentally removed another node!

This corrupts the path state.

Repeated incorrect removals can eventually cause an invalid vector
access, resulting in a heap-buffer-overflow.

THE FIX:

We removed the cleanup operations from the leaf conditions.

We now save the path if it is valid, explore both children, and then
perform cleanup exactly once at the end.

CORRECT LOGIC:

    if (currentSum == target &&
        root->left == nullptr &&
        root->right == nullptr) {

        ans.push_back(v);
    }

    solve(root->left, ans, v, target);
    solve(root->right, ans, v, target);

    currentSum -= root->val;
    v.pop_back();

WHY DOES THIS WORK?

Every non-null invocation follows the same structure:

    1. Add the current node.
    2. Check whether the path is valid.
    3. Explore the left subtree.
    4. Explore the right subtree.
    5. Remove the current node.

The cleanup happens exactly once.

This was the key debugging lesson from our Path Sum II implementation.

===============================================================================
9. COMPLETE DRY RUN
===============================================================================

TREE:

                         5
                       /   \
                      4     8
                     /     / \
                    11    13  4
                   /  \       / \
                  7    2     5   1

TARGET = 22

INITIAL STATE:

    currentSum = 0
    v = {}
    ans = {}

---------------------------------------
STEP 1: VISIT NODE 5
---------------------------------------

    currentSum = 0 + 5 = 5

    v = {5}

    Is currentSum equal to 22?

    No.

    Explore the left subtree.

---------------------------------------
STEP 2: VISIT NODE 4
---------------------------------------

    currentSum = 5 + 4 = 9

    v = {5, 4}

    Is currentSum equal to 22?

    No.

    Explore the left subtree.

---------------------------------------
STEP 3: VISIT NODE 11
---------------------------------------

    currentSum = 9 + 11 = 20

    v = {5, 4, 11}

    Is currentSum equal to 22?

    No.

    Explore the left subtree.

---------------------------------------
STEP 4: VISIT NODE 7
---------------------------------------

    currentSum = 20 + 7 = 27

    v = {5, 4, 11, 7}

    Node 7 is a leaf.

    Is currentSum equal to 22?

    No.

    No path is stored.

    Both recursive calls return nullptr.

BACKTRACK:

    currentSum = 27 - 7 = 20

    v = {5, 4, 11}

We have returned to node 11.

---------------------------------------
STEP 5: VISIT NODE 2
---------------------------------------

    currentSum = 20 + 2 = 22

    v = {5, 4, 11, 2}

    Node 2 is a leaf.

    Is currentSum equal to 22?

    YES!

SAVE:

    ans = {
        {5, 4, 11, 2}
    }

The recursive calls for node 2's children return nullptr.

BACKTRACK:

    currentSum = 22 - 2 = 20

    v = {5, 4, 11}

We have finished the subtree rooted at node 11.

BACKTRACK NODE 11:

    currentSum = 20 - 11 = 9

    v = {5, 4}

We return to node 4.

BACKTRACK NODE 4 AFTER ITS CHILDREN:

    currentSum = 9 - 4 = 5

    v = {5}

Now node 4's subtree has been completely processed.

---------------------------------------
STEP 6: EXPLORE NODE 8
---------------------------------------

    currentSum = 5 + 8 = 13

    v = {5, 8}

---------------------------------------
STEP 7: VISIT NODE 13
---------------------------------------

    currentSum = 13 + 13 = 26

    v = {5, 8, 13}

    Node 13 is a leaf.

    Sum is not equal to 22.

BACKTRACK:

    currentSum = 13
    v = {5, 8}

---------------------------------------
STEP 8: VISIT NODE 4
---------------------------------------

    currentSum = 13 + 4 = 17

    v = {5, 8, 4}

---------------------------------------
STEP 9: VISIT NODE 5
---------------------------------------

    currentSum = 17 + 5 = 22

    v = {5, 8, 4, 5}

    Node 5 is a leaf.

    Sum equals 22.

SAVE:

    ans = {
        {5, 4, 11, 2},
        {5, 8, 4, 5}
    }

BACKTRACK:

    currentSum = 17

    v = {5, 8, 4}

---------------------------------------
STEP 10: VISIT NODE 1
---------------------------------------

    currentSum = 17 + 1 = 18

    v = {5, 8, 4, 1}

    Node 1 is a leaf.

    Sum is not equal to 22.

BACKTRACK:

    currentSum = 17

    v = {5, 8, 4}

We finish node 4.

BACKTRACK:

    currentSum = 13

    v = {5, 8}

We finish node 8.

BACKTRACK:

    currentSum = 5

    v = {5}

Finally, we finish node 5.

BACKTRACK:

    currentSum = 0

    v = {}

The entire tree has been processed.

FINAL ANSWER:

    [
        [5, 4, 11, 2],
        [5, 8, 4, 5]
    ]

===============================================================================
10. FINAL C++ IMPLEMENTATION
===============================================================================

The following is our accepted recursive DFS + backtracking solution.

We use a class variable currentSum and pass the answer vector and current
path vector by reference.

NOTE:

The currentSum variable is initialized to zero when the Solution object
is constructed. We also explicitly reset it in pathSum so that the
function starts with a clean state if the same Solution object is reused.

===============================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
Definition for a binary tree node.

LeetCode provides this structure automatically.

We include it here to make our learning file self-contained.
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

    // Maintains the sum of the current root-to-node path.
    int currentSum = 0;


    /*
    Recursive DFS helper function.

    root:
        Current node being processed.

    ans:
        Stores every valid root-to-leaf path.

    v:
        Stores the current root-to-node path.

    target:
        Required target sum.
    */

    void solve(
        TreeNode* root,
        vector<vector<int>>& ans,
        vector<int>& v,
        int target
    ) {

        // BASE CASE:
        // If the current node is nullptr, there is nothing to process.
        if (root == nullptr) {
            return;
        }


        // STEP 1:
        // Include the current node's value in the running sum.
        currentSum += root->val;


        // STEP 2:
        // Add the current node to our current path.
        v.push_back(root->val);


        // STEP 3:
        // Check whether we have reached a valid root-to-leaf path.
        //
        // A valid path must satisfy:
        // 1. Its sum equals target.
        // 2. The current node has no left child.
        // 3. The current node has no right child.

        if (
            currentSum == target &&
            root->left == nullptr &&
            root->right == nullptr
        ) {

            // Store a COPY of the current path.
            ans.push_back(v);
        }


        // STEP 4:
        // Explore the left subtree.
        solve(root->left, ans, v, target);


        // STEP 5:
        // Explore the right subtree.
        solve(root->right, ans, v, target);


        // STEP 6: BACKTRACKING
        //
        // Both child subtrees have been processed.
        // Remove the current node's contribution before returning
        // to the parent invocation.

        currentSum -= root->val;

        v.pop_back();
    }


public:

    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {

        // Stores all valid root-to-leaf paths.
        vector<vector<int>> ans;


        // Stores the currently explored path.
        vector<int> v;


        // Ensure that the running sum starts clean.
        currentSum = 0;


        // Start recursive DFS from the root.
        solve(root, ans, v, targetSum);


        // Return all valid paths.
        return ans;
    }

};


/*
===============================================================================
11. COMPLEXITY ANALYSIS
===============================================================================

Let:

    N = Total number of nodes in the binary tree.
    H = Height of the binary tree.
    K = Number of valid root-to-leaf paths.
    L = Maximum number of nodes in a root-to-leaf path.

TIME COMPLEXITY:

    O(N + K * L)

WHY?

1. DFS visits every node exactly once.

       O(N)

2. Whenever we discover a valid path, we execute:

       ans.push_back(v);

   This copies the current path into the answer vector.

   The maximum path length is H, so each valid path copy costs O(H).

   For K valid paths, the total path-copying cost is:

       O(K * H)

Therefore:

    O(N + K * H)

Since H is the maximum root-to-leaf path length, we can also express
this as:

    O(N + K * L)

For a balanced binary tree, H is approximately O(log N).

For a completely skewed binary tree, H can be O(N).

SPACE COMPLEXITY:

1. RECURSION STACK:

       O(H)

   DFS can have at most H recursive invocations active at once.

2. CURRENT PATH VECTOR:

       O(H)

   The current path contains at most H nodes.

3. ANSWER VECTOR:

       O(K * H)

   We store K valid paths, each containing at most H nodes.

Therefore:

    Auxiliary space excluding the returned answer:

       O(H)

    Including the returned answer:

       O(K * H)

IMPORTANT:

The answer vector is output storage. It is generally discussed separately
from auxiliary space.

===============================================================================
12. IMPORTANT LESSONS LEARNED
===============================================================================

LESSON 1: DFS

    DFS allows us to explore every possible root-to-leaf path.

LESSON 2: RECURSION

    Every recursive invocation processes one current node and then
    explores its children.

LESSON 3: REFERENCE PARAMETERS

    We pass ans and v by reference so all recursive invocations share
    the same containers.

LESSON 4: BACKTRACKING

    Every change made while moving down the tree must be undone when
    returning from that node.

LESSON 5: LEAF NODE CHECK

    A valid path must end at a node whose left and right children are
    both nullptr.

LESSON 6: COPYING A VALID PATH

    ans.push_back(v) stores a copy of the current path.

LESSON 7: RECURSIVE CONTROL FLOW

    A nullptr base case returns from only that particular invocation.

    Control resumes in the parent invocation.

LESSON 8: CLEANUP EXACTLY ONCE

    Every non-null invocation must remove its own contribution exactly
    once.

    Incorrect cleanup can corrupt the shared path vector and running sum.

LESSON 9: DEBUGGING WITH ADDRESS SANITIZER

    AddressSanitizer helped us identify an invalid vector access caused
    by double backtracking.

LESSON 10: UNDERSTANDING OVER MEMORIZATION

    We did not simply memorize the accepted solution.

    We traced the recursive calls, understood the call stack, identified
    the double-pop bug, and corrected the implementation.

===============================================================================
13. FINAL REVISION CHECKLIST
===============================================================================

[ ] I understand the Path Sum II problem statement.

[ ] I understand why DFS is suitable.

[ ] I understand the role of currentSum.

[ ] I understand why we need a vector to store the current path.

[ ] I understand why ans is a 2D vector.

[ ] I understand why we pass vectors by reference.

[ ] I understand the nullptr base case.

[ ] I understand why both children must be nullptr for a leaf.

[ ] I understand how recursive calls execute.

[ ] I understand how control returns to the parent invocation.

[ ] I understand why backtracking is necessary.

[ ] I understand why we must clean up exactly once.

[ ] I understand the AddressSanitizer heap-buffer-overflow we encountered.

[ ] I can explain the complete dry run without looking at the solution.

[ ] I can implement this solution independently.

===============================================================================
                         END OF DAY 25 NOTES
===============================================================================

PROBLEM:
    LeetCode 113 — Path Sum II

APPROACH:
    Recursive DFS + Backtracking

RESULT:
    Accepted

MAIN CONCEPT MASTERED:
    Maintaining and restoring state during recursive tree traversal.

ALPHA SIGNING OFF.
OVER AND OUT, COMRADE!
===============================================================================
*/
