
/*
===============================================================================
                    DSA JOURNEY — DAY 25
===============================================================================

PROBLEM:
    LeetCode 236 — Lowest Common Ancestor of a Binary Tree

TOPIC:
    Binary Trees | DFS | Recursion | Pointers | Call Stack

DIFFICULTY:
    Medium

PROBLEM LINK:
    https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/

APPROACH:
    Recursive Depth First Search (DFS)

===============================================================================
1. PROBLEM STATEMENT
===============================================================================

Given a binary tree, find the lowest common ancestor (LCA) of two given
nodes p and q.

According to the definition of LCA:

    The lowest common ancestor of two nodes p and q is the lowest node
    in the tree that has both p and q as descendants.

A node can be considered a descendant of itself.

In simple words:

    We need to find the lowest node in the tree that is an ancestor
    of both given nodes.

IMPORTANT:

    - We are given two TreeNode pointers: p and q.
    - We need to find their lowest common ancestor.
    - Both p and q are guaranteed to exist in the tree.
    - The nodes are identified by their pointers, not just their values.

===============================================================================
2. UNDERSTANDING THE PROBLEM
===============================================================================

Consider this binary tree:

                         3
                       /   \
                      5     1
                     / \   / \
                    6   2 0   8
                       / \
                      7   4

EXAMPLE 1:

    p = 5
    q = 1

The paths from the root are:

    Root -> p:

        3 -> 5

    Root -> q:

        3 -> 1

Both nodes have node 3 as their common ancestor.

Therefore:

    LCA = 3

EXAMPLE 2:

    p = 5
    q = 4

Node 4 is inside the subtree rooted at node 5.

Node 5 itself is also an ancestor of node 4.

Remember that a node can be considered a descendant of itself.

Therefore:

    LCA = 5

EXAMPLE 3:

    p = 6
    q = 4

Their paths are:

    Root -> p:

        3 -> 5 -> 6

    Root -> q:

        3 -> 5 -> 2 -> 4

Their lowest common ancestor is:

    LCA = 5

===============================================================================
3. DEVELOPING THE INTUITION
===============================================================================

Initially, we need to understand what information we want from each
subtree.

We are searching for two specific nodes:

    p
    q

At every node, we need to explore its left and right subtrees.

Our main question is:

    Did we find p or q somewhere in the left subtree?

    Did we find p or q somewhere in the right subtree?

This leads us to two recursive calls:

    TreeNode* leftAns =
        lowestCommonAncestor(root->left, p, q);

    TreeNode* rightAns =
        lowestCommonAncestor(root->right, p, q);

But why do these recursive calls return TreeNode*?

Because we want to pass information about the node we found back
to the parent.

We don't just need to know whether a node exists.

We need the actual pointer to the discovered node or the LCA.

This is the central idea of our solution.

===============================================================================
4. WHY DO WE USE DFS AND RECURSION?
===============================================================================

We can explore the entire binary tree using DFS.

DFS moves deeper into a subtree before returning to explore another
subtree.

At every node, we recursively explore:

    1. Left subtree.
    2. Right subtree.

After both calls return, we examine their results.

The returned pointers allow information to travel upward through
the recursive call stack.

For example:

                         1
                       /   \
                      2     3
                     / \     \
                    4   5     11

Suppose:

    p = 4
    q = 11

The left subtree eventually discovers node 4.

The right subtree eventually discovers node 11.

Their respective parent-side recursive calls receive these pointers.

When both results reach node 1:

    leftAns  = pointer to node 4
    rightAns = pointer to node 11

Both are non-null.

Therefore, node 1 is their lowest common ancestor.

===============================================================================
5. DESIGNING THE RECURSIVE FUNCTION
===============================================================================

Our function:

    TreeNode* lowestCommonAncestor(
        TreeNode* root,
        TreeNode* p,
        TreeNode* q
    )

Let's understand its parameters.

1. TreeNode* root

    Represents the current node being processed.

    During recursive execution, root changes to different nodes.

2. TreeNode* p

    Pointer to the first target node.

3. TreeNode* q

    Pointer to the second target node.

WHY DOES THE FUNCTION RETURN TreeNode*?

Because each recursive invocation needs to return useful information
to its parent.

It can return:

    1. The pointer to p.
    2. The pointer to q.
    3. The pointer to the lowest common ancestor.
    4. nullptr if neither target was found in that subtree.

This is how information bubbles upward.

===============================================================================
6. STEP-BY-STEP IMPLEMENTATION
===============================================================================

STEP 1: BASE CASE — NULLPTR

    if (root == nullptr) {
        return root;
    }

WHY?

If the current node is nullptr, there is no node to process.

We return nullptr.

Since root is already nullptr, these statements are equivalent:

    return root;

    return nullptr;

This finishes only the current recursive invocation.

Control returns to its caller.

STEP 2: CHECK WHETHER THE CURRENT NODE IS p OR q

    if (root == p || root == q) {
        return root;
    }

This is another important base case.

We compare pointers directly.

WHY POINTER COMPARISON?

Because p and q are TreeNode pointers.

We want to identify the exact target nodes.

We are not comparing only their values.

If the current root pointer matches either p or q, we have found
one of our target nodes.

We immediately return root.

For example:

    root == p

    This means the current node is p.

    Return root.

Similarly:

    root == q

    This means the current node is q.

    Return root.

The parent invocation receives this pointer.

IMPORTANT:

When this condition is satisfied, the current invocation returns
immediately.

It does not execute its own left and right recursive calls.

Its parent resumes execution.

STEP 3: SEARCH THE LEFT SUBTREE

    TreeNode* leftAns =
        lowestCommonAncestor(root->left, p, q);

We recursively search the left subtree.

The recursive function can return:

    - Pointer to p.
    - Pointer to q.
    - Pointer to an already identified LCA.
    - nullptr if neither target is found.

The returned pointer is stored in leftAns.

STEP 4: SEARCH THE RIGHT SUBTREE

    TreeNode* rightAns =
        lowestCommonAncestor(root->right, p, q);

After the left recursive call finishes, execution continues.

We recursively search the right subtree.

The returned pointer is stored in rightAns.

Now both child subtrees have been processed.

We can make our decision.

STEP 5: BOTH ANSWERS ARE NON-NULL

    if (leftAns != nullptr && rightAns != nullptr) {
        return root;
    }

This is the most important condition.

What does it mean?

It means:

    - We found one target in the left subtree.
    - We found the other target in the right subtree.

Therefore, the current node is the lowest common ancestor.

WHY RETURN root?

Because this is the first node, moving upward from the two
subtrees, where both returned pointers meet.

For example:

                         1
                       /   \
                      2     3
                     /       \
                    4         11

    p = 4
    q = 11

At node 1:

    leftAns  = pointer to 4
    rightAns = pointer to 11

Both are non-null.

Therefore:

    return root;

Node 1 is the LCA.

STEP 6: ONLY THE LEFT ANSWER IS NON-NULL

    else if (
        leftAns != nullptr &&
        rightAns == nullptr
    ) {
        return leftAns;
    }

This means the current subtree contains a target or an already
identified LCA somewhere in its left subtree.

The right subtree returned nullptr.

We return leftAns.

WHY NOT return root->left?

Because leftAns might point to a node much deeper in the subtree.

It could be p, q, or an LCA already discovered below.

We must preserve the exact pointer returned by the recursive call.

STEP 7: ONLY THE RIGHT ANSWER IS NON-NULL

    else if (
        leftAns == nullptr &&
        rightAns != nullptr
    ) {
        return rightAns;
    }

This is the opposite situation.

The left subtree returned nullptr.

The right subtree returned a valid pointer.

Therefore, we return rightAns.

STEP 8: BOTH ANSWERS ARE NULLPTR

    return nullptr;

If neither subtree contains p or q, and the current node itself
did not match either target, then there is nothing useful to return.

We return nullptr.

===============================================================================
7. UNDERSTANDING THE FOUR POSSIBLE CASES
===============================================================================

After both recursive calls return, we can have four combinations.

CASE 1:

    leftAns  = NON-NULL
    rightAns = NON-NULL

    Meaning:

        Both subtrees returned useful pointers.

    Action:

        return root;

    The current node is the LCA.

CASE 2:

    leftAns  = NON-NULL
    rightAns = NULL

    Meaning:

        A target or an already identified LCA exists in the left subtree.

    Action:

        return leftAns;

CASE 3:

    leftAns  = NULL
    rightAns = NON-NULL

    Meaning:

        A target or an already identified LCA exists in the right subtree.

    Action:

        return rightAns;

CASE 4:

    leftAns  = NULL
    rightAns = NULL

    Meaning:

        Neither subtree contains either target.

    Action:

        return nullptr;

SUMMARY:

    leftAns       rightAns       Return

    Non-null      Non-null       root

    Non-null      nullptr        leftAns

    nullptr       Non-null        rightAns

    nullptr       nullptr        nullptr

===============================================================================
8. UNDERSTANDING THE CALL STACK AND POINTER RETURNS
===============================================================================

This was the most important part of our learning journey.

We spent time understanding exactly how pointers travel from
child nodes to their parent nodes.

Consider:

                         1
                       /   \
                      2     3
                     /       \
                    4         11

    p = 4
    q = 11

Let's trace what happens.

STEP 1: START AT NODE 1

    root = 1

    root is not nullptr.

    root is neither p nor q.

    We make the left recursive call.

STEP 2: REACH NODE 2

    root = 2

    It is not p or q.

    We explore its left subtree.

STEP 3: REACH NODE 4

    root = 4

    root == p

    The condition is satisfied.

    We execute:

        return root;

Node 4 returns its pointer to node 2.

IMPORTANT:

The invocation for node 4 ends.

Control returns to node 2.

STEP 4: NODE 2 RECEIVES THE POINTER

    leftAns = pointer to node 4

Now node 2 continues execution.

It has not finished its function yet.

It must execute its right recursive call.

Its right child is nullptr.

The base case returns nullptr.

Therefore:

    rightAns = nullptr

Node 2 now has:

    leftAns  = pointer to node 4
    rightAns = nullptr

It evaluates its conditions.

Only leftAns is non-null.

Therefore:

    return leftAns;

Node 2 returns the pointer to node 4 to node 1.

STEP 5: NODE 1 RECEIVES THE LEFT RESULT

Node 1 now has:

    leftAns = pointer to node 4

The left recursive call has finished.

Node 1 now executes its right recursive call.

STEP 6: REACH NODE 3

    root = 3

It is neither p nor q.

Its left child is nullptr.

That call returns nullptr.

Its right child is node 11.

STEP 7: REACH NODE 11

    root = 11

    root == q

The condition is satisfied.

Node 11 executes:

    return root;

It returns its pointer to node 3.

Node 3 receives:

    rightAns = pointer to node 11

Its left answer is nullptr.

Therefore, node 3 returns rightAns to node 1.

STEP 8: NODE 1 RECEIVES THE RIGHT RESULT

Now node 1 has:

    leftAns  = pointer to node 4
    rightAns = pointer to node 11

Both are non-null.

It executes:

    if (leftAns != nullptr && rightAns != nullptr) {
        return root;
    }

The current root is node 1.

Therefore:

    return node 1;

FINAL ANSWER:

    Node 1

===============================================================================
9. IMPORTANT: WHEN DOES STACK UNWINDING HAPPEN?
===============================================================================

The call stack is managed automatically by C++.

But we decide what happens when each recursive invocation resumes.

Consider:

    TreeNode* leftAns =
        lowestCommonAncestor(root->left, p, q);

    TreeNode* rightAns =
        lowestCommonAncestor(root->right, p, q);

    if (leftAns != nullptr && rightAns != nullptr) {
        return root;
    }

The execution order is:

    1. The left recursive call executes.

    2. It returns a pointer.

    3. That pointer is stored in leftAns.

    4. The right recursive call executes.

    5. It returns a pointer.

    6. That pointer is stored in rightAns.

    7. The current invocation evaluates its if conditions.

    8. It returns the appropriate pointer to its caller.

IMPORTANT:

The entire call stack does NOT unwind before the if statements.

Each invocation resumes after its recursive calls return.

It then evaluates its own conditions.

It may return a result to its parent, which resumes execution
and performs the same process.

This happens repeatedly until the original function invocation
finishes.

THE KEY CONCEPT:

    C++ manages the call stack.

    Our code determines what information each invocation returns
    and how its parent processes that information.

===============================================================================
10. DRY RUN — BOTH TARGETS IN DIFFERENT SUBTREES
===============================================================================

TREE:

                         1
                       /   \
                      2     3
                     /       \
                    4         11

    p = 4
    q = 11

INITIAL CALL:

    lowestCommonAncestor(1, 4, 11)

At node 1:

    root != nullptr
    root != p
    root != q

Make left call.

---------------------------------------
LEFT SUBTREE
---------------------------------------

At node 2:

    root != nullptr
    root != p
    root != q

Make left call.

At node 4:

    root == p

Return pointer to node 4.

Back at node 2:

    leftAns = pointer to 4

Right call:

    root = nullptr

Return nullptr.

Now:

    leftAns  = pointer to 4
    rightAns = nullptr

Return leftAns.

Node 2 returns pointer to 4 to node 1.

---------------------------------------
RIGHT SUBTREE
---------------------------------------

At node 3:

    root != nullptr
    root != p
    root != q

Left call:

    root = nullptr

Return nullptr.

Right call:

    root = 11

    root == q

Return pointer to 11.

Back at node 3:

    leftAns  = nullptr
    rightAns = pointer to 11

Return rightAns.

Node 3 returns pointer to 11 to node 1.

---------------------------------------
FINAL DECISION AT NODE 1
---------------------------------------

    leftAns  = pointer to 4
    rightAns = pointer to 11

Both are non-null.

Execute:

    return root;

Root is node 1.

FINAL ANSWER:

    Node 1

===============================================================================
11. DRY RUN — ONE TARGET IS AN ANCESTOR OF THE OTHER
===============================================================================

Consider:

                         3
                       /   \
                      5     1
                     / \   / \
                    6   2 0   8
                       / \
                      7   4

    p = 5
    q = 4

Start at node 3.

Node 3 is neither p nor q.

Explore its left subtree.

At node 5:

    root == p

Therefore:

    return root;

Node 5 returns its pointer to node 3.

IMPORTANT:

We do not explore node 5's children in this invocation.

Why?

Because we have already found one of the target nodes.

And node 5 itself is an ancestor of node 4.

Now node 3 receives:

    leftAns = pointer to node 5

It continues with its right subtree.

The right subtree does not contain p or q.

Therefore:

    rightAns = nullptr

At node 3:

    leftAns  = pointer to 5
    rightAns = nullptr

We execute:

    return leftAns;

The final answer is node 5.

WHY DOES THIS WORK?

Because the problem allows a node to be considered a descendant
of itself.

Therefore, when p is an ancestor of q, p can be the LCA.

===============================================================================
12. WHY DO WE RETURN leftAns OR rightAns INSTEAD OF root?
===============================================================================

This is an important design decision.

Suppose we are at node 2.

Its left subtree returns node 4.

Its right subtree returns nullptr.

We have:

    leftAns = pointer to node 4
    rightAns = nullptr

We must return:

    return leftAns;

WHY NOT:

    return root;

Because node 2 is not necessarily the LCA.

It might simply be an intermediate node through which information
must travel upward.

We must preserve the actual pointer returned by the child.

Similarly, if the right subtree returns a useful pointer, we return
rightAns.

Only when BOTH sides return non-null pointers do we return the
current root as the LCA.

===============================================================================
13. FINAL C++ IMPLEMENTATION
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

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


class Solution {

public:

    TreeNode* lowestCommonAncestor(
        TreeNode* root,
        TreeNode* p,
        TreeNode* q
    ) {

        // BASE CASE 1:
        // If the current node is nullptr, return nullptr.
        if (root == nullptr) {
            return root;
        }


        // BASE CASE 2:
        // If we find either target node, return its pointer.
        if (root == p || root == q) {
            return root;
        }


        // STEP 1:
        // Search the left subtree.
        TreeNode* leftAns =
            lowestCommonAncestor(root->left, p, q);


        // STEP 2:
        // Search the right subtree.
        TreeNode* rightAns =
            lowestCommonAncestor(root->right, p, q);


        // CASE 1:
        // Both subtrees returned non-null pointers.
        // The current node is the LCA.
        if (leftAns != nullptr && rightAns != nullptr) {
            return root;
        }


        // CASE 2:
        // Only the left subtree returned a valid pointer.
        else if (
            leftAns != nullptr &&
            rightAns == nullptr
        ) {
            return leftAns;
        }


        // CASE 3:
        // Only the right subtree returned a valid pointer.
        else if (
            leftAns == nullptr &&
            rightAns != nullptr
        ) {
            return rightAns;
        }


        // CASE 4:
        // Both subtrees returned nullptr.
        return nullptr;
    }

};


/*
===============================================================================
14. COMPLEXITY ANALYSIS
===============================================================================

Let:

    N = Total number of nodes in the binary tree.
    H = Height of the binary tree.

TIME COMPLEXITY:

    O(N)

WHY?

In the worst case, we visit every node in the tree exactly once.

At each node, we perform:

    1. A nullptr check.
    2. A pointer comparison against p and q.
    3. A recursive call for the left subtree.
    4. A recursive call for the right subtree.
    5. Constant-time pointer comparisons and return operations.

Each operation at an individual node takes O(1) time.

Therefore:

    Total time complexity = O(N)

SPACE COMPLEXITY:

    O(H)

WHY?

The recursive calls consume call-stack space.

The maximum number of simultaneously active recursive invocations
depends on the height of the tree.

For a balanced binary tree:

    H = O(log N)

For a completely skewed binary tree:

    H = O(N)

We do not create an additional array, map, or other data structure.

We only use a constant number of pointer variables in each invocation.

Therefore:

    Auxiliary space complexity = O(H)

===============================================================================
15. IMPORTANT LESSONS LEARNED
===============================================================================

LESSON 1: DFS

    DFS allows us to search the left and right subtrees recursively.

LESSON 2: POINTER COMPARISON

    We compare root directly with p and q.

    We are identifying the actual target nodes, not merely comparing
    their values.

LESSON 3: RECURSIVE RETURN VALUES

    Our recursive function returns TreeNode*.

    Each invocation communicates useful information to its parent.

LESSON 4: LEFT AND RIGHT ANSWERS

    leftAns stores the result returned by the left subtree.

    rightAns stores the result returned by the right subtree.

LESSON 5: BOTH ANSWERS NON-NULL

    If both sides return non-null pointers, the current root is
    the lowest common ancestor.

LESSON 6: RETURNING A CHILD'S ANSWER

    If only one subtree returns a useful pointer, we pass that
    exact pointer upward.

    We do not replace it with root or root->left/root->right.

LESSON 7: NULLPTR

    If neither subtree contains either target, we return nullptr.

LESSON 8: CALL STACK

    C++ automatically manages recursive function invocations.

    Each invocation resumes after its child calls return.

LESSON 9: DECIDING THE UNWINDING BEHAVIOR

    The programming language manages the call stack.

    Our code decides what each invocation does when control returns.

LESSON 10: INFORMATION BUBBLING UPWARD

    Each recursive invocation returns information to its parent.

    The parent combines the results and decides what to return next.

LESSON 11: ANCESTOR CAN BE A TARGET NODE

    A target node can itself be the LCA.

    For example, if p is an ancestor of q, p can be their LCA.

===============================================================================
16. FINAL REVISION CHECKLIST
===============================================================================

[ ] I understand the Lowest Common Ancestor problem statement.

[ ] I understand why DFS is suitable.

[ ] I understand why the function returns TreeNode*.

[ ] I understand the nullptr base case.

[ ] I understand root == p || root == q.

[ ] I understand why we compare pointers rather than just values.

[ ] I understand leftAns and rightAns.

[ ] I understand all four possible combinations of recursive results.

[ ] I understand why both non-null answers mean the current root is LCA.

[ ] I understand why we return leftAns when only the left side is valid.

[ ] I understand why we return rightAns when only the right side is valid.

[ ] I understand why both nullptr answers result in nullptr.

[ ] I understand how returned pointers travel to parent nodes.

[ ] I understand when each invocation evaluates its if conditions.

[ ] I understand how the call stack unwinds.

[ ] I understand why a target node can itself be the LCA.

[ ] I can implement this solution independently.

===============================================================================
                         END OF DAY 25 NOTES
===============================================================================

PROBLEM:
    LeetCode 236 — Lowest Common Ancestor of a Binary Tree

APPROACH:
    Recursive DFS + Pointer-Based Return Logic

RESULT:
    Accepted

MAIN CONCEPT MASTERED:
    Passing information upward through recursive return values
    to identify the lowest common ancestor.

ALPHA SIGNING OFF.
OVER AND OUT, COMRADE!
===============================================================================
*/
