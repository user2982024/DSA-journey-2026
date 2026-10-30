
/*
===============================================================================
                    DSA JOURNEY — DAY 25
===============================================================================

PROBLEM:
    LeetCode 100 — Same Tree

TOPIC:
    Binary Trees | DFS | Recursion | Pointer Comparison

DIFFICULTY:
    Easy

PROBLEM LINK:
    https://leetcode.com/problems/same-tree/

APPROACH:
    Recursive Depth First Search (DFS)

===============================================================================
1. PROBLEM STATEMENT
===============================================================================

Given the roots of two binary trees, p and q, write a function to check
whether they are the same or not.

Two binary trees are considered the same if:

    1. They are structurally identical.
    2. The nodes at corresponding positions have the same values.

In simple words, we need to check:

    - Whether both trees have the same structure.
    - Whether their corresponding nodes contain equal values.
    - Whether their left subtrees are also identical.
    - Whether their right subtrees are also identical.

Return:

    true  -> If both trees are identical.

    false -> If they are different.

===============================================================================
2. UNDERSTANDING THE PROBLEM
===============================================================================

Consider two binary trees:

TREE P:

                         1
                       /   \
                      2     3

TREE Q:

                         1
                       /   \
                      2     3

Both trees have:

    Root value = 1

    Left child value = 2

    Right child value = 3

Their structures are also identical.

Therefore:

    Output = true

Now consider another example.

TREE P:

                         1
                       /   \
                      2     3

TREE Q:

                         1
                       /   \
                      2     4

Both trees have the same structure, but their right children have
different values.

Therefore:

    Output = false

Another example:

TREE P:

                         1
                       /
                      2

TREE Q:

                         1
                           \
                            2

Both trees contain the same values, but their structures are different.

Therefore:

    Output = false

IMPORTANT:

Having the same values is not sufficient.

The positions and structure of the nodes must also match.

===============================================================================
3. DEVELOPING THE INTUITION
===============================================================================

We are given two binary trees.

Our job is to compare them.

The first question is:

How can we compare every corresponding node in both trees?

We can use DFS and recursion.

We start at both root nodes simultaneously.

At each recursive invocation, we compare the current nodes of both trees.

There are three important situations:

CASE 1:

    Both current pointers are nullptr.

    This means both trees have reached an empty position.

    They match at this position.

    Return true.

CASE 2:

    One pointer is nullptr, but the other is not.

    This means the structures are different.

    Return false.

CASE 3:

    Both pointers exist.

    We compare their values.

    If their values are different, return false.

    Otherwise, recursively compare their left and right children.

The final result depends on BOTH recursive comparisons being true.

This gives us our recursive algorithm.

===============================================================================
4. DESIGNING THE RECURSIVE FUNCTION
===============================================================================

Our function:

    bool isSameTree(TreeNode* p, TreeNode* q)

WHY DOES IT RETURN bool?

Because we are checking whether two trees are identical.

There are only two possible answers:

    true
    false

WHY DO WE HAVE TWO POINTER PARAMETERS?

    TreeNode* p

        Represents the current node in the first tree.

    TreeNode* q

        Represents the current node in the second tree.

Every recursive invocation receives two corresponding positions
from the trees.

As recursion progresses, both pointers move through their respective
trees.

===============================================================================
5. STEP-BY-STEP IMPLEMENTATION
===============================================================================

STEP 1: CHECK WHETHER BOTH POINTERS ARE NULLPTR

    if (p == nullptr && q == nullptr) {
        return true;
    }

WHY?

If both pointers are nullptr, both trees have reached an empty position.

There is no structural difference at this position.

Therefore, we return true.

IMPORTANT:

This does not mean the entire tree comparison is finished.

It only returns true for this particular recursive invocation.

The parent invocation will use this result when checking its own
left or right subtree.

STEP 2: CHECK WHETHER ONLY ONE POINTER IS NULLPTR

    if (
        (p == nullptr && q != nullptr) ||
        (p != nullptr && q == nullptr)
    ) {
        return false;
    }

WHY?

If one tree has a node but the other tree has no node at the
corresponding position, their structures are different.

For example:

TREE P:

        1
       /
      2

TREE Q:

        1

At the left child position:

    p = pointer to node 2
    q = nullptr

The structures are different.

Therefore, we return false.

This condition also prevents us from accessing p->val or q->val
when one pointer is nullptr.

STEP 3: COMPARE THE CURRENT NODE VALUES

    if (p->val != q->val) {
        return false;
    }

At this point, both pointers are guaranteed to be non-null.

Therefore, it is safe to access their values.

If the values differ, the trees cannot be identical.

We immediately return false.

For example:

    p->val = 5
    q->val = 8

Since:

    5 != 8

We return false.

STEP 4: RECURSIVELY COMPARE THE LEFT SUBTREES

    bool leftAns = isSameTree(p->left, q->left);

We compare the left child of the first tree with the left child
of the second tree.

The recursive function repeats the same checks.

It returns true if both left subtrees are identical.

Otherwise, it returns false.

STEP 5: RECURSIVELY COMPARE THE RIGHT SUBTREES

    bool rightAns = isSameTree(p->right, q->right);

After the left recursive call finishes, we compare the right subtrees.

The result is stored in rightAns.

STEP 6: COMBINE BOTH RESULTS

    return leftAns && rightAns;

This is the final decision.

We use logical AND (&&).

The AND operator returns true only when BOTH operands are true.

TRUTH TABLE:

    leftAns     rightAns     Result

    true        true         true

    true        false        false

    false       true         false

    false       false        false

Therefore, both the left and right subtrees must be identical.

===============================================================================
6. WHY DO WE NEED BOTH RECURSIVE CALLS?
===============================================================================

Consider:

TREE P:

                         1
                       /   \
                      2     3

TREE Q:

                         1
                       /   \
                      2     3

At the root:

    p->val = 1
    q->val = 1

The values match.

Now we must verify both sides.

LEFT:

    isSameTree(p->left, q->left)

    Compare node 2 with node 2.

    Their values match.

    Their children are both nullptr.

    Result = true.

RIGHT:

    isSameTree(p->right, q->right)

    Compare node 3 with node 3.

    Their values match.

    Their children are both nullptr.

    Result = true.

Finally:

    leftAns && rightAns

    true && true

    Result = true.

Therefore, both trees are identical.

===============================================================================
7. UNDERSTANDING RECURSION AND THE CALL STACK
===============================================================================

Our function makes recursive calls for both corresponding children.

Conceptually:

    isSameTree(rootP, rootQ)

        isSameTree(rootP->left, rootQ->left)

        isSameTree(rootP->right, rootQ->right)

Each invocation checks its own pair of nodes.

When a recursive invocation reaches its base case, it returns a
boolean value.

That value goes back to the caller.

The parent invocation stores the returned result in its corresponding
variable.

For example:

    bool leftAns = isSameTree(p->left, q->left);

When the left recursive call finishes, its boolean result is stored
in leftAns.

Then the right recursive call executes.

After both calls return, the current invocation evaluates:

    return leftAns && rightAns;

IMPORTANT:

The call stack is managed automatically by C++.

But our code decides how the returned boolean values are used.

In this problem, we combine the two results using logical AND.

===============================================================================
8. COMPLETE DRY RUN
===============================================================================

TREE P:

                         1
                       /   \
                      2     3

TREE Q:

                         1
                       /   \
                      2     3

INITIAL CALL:

    isSameTree(P, Q)

---------------------------------------
STEP 1: COMPARE ROOT POINTERS
---------------------------------------

    p != nullptr
    q != nullptr

Neither pointer is null.

The first base case is false.

The second base case is also false.

---------------------------------------
STEP 2: COMPARE ROOT VALUES
---------------------------------------

    p->val = 1
    q->val = 1

Both values are equal.

Continue.

---------------------------------------
STEP 3: COMPARE LEFT SUBTREES
---------------------------------------

    leftAns = isSameTree(2, 2)

Both pointers exist.

Compare values:

    2 == 2

Now compare their left children:

    isSameTree(nullptr, nullptr)

Both are nullptr.

Return true.

Compare their right children:

    isSameTree(nullptr, nullptr)

Both are nullptr.

Return true.

Now:

    leftAns = true && true

    leftAns = true

The invocation comparing node 2 with node 2 returns true.

---------------------------------------
STEP 4: COMPARE RIGHT SUBTREES
---------------------------------------

    rightAns = isSameTree(3, 3)

Both pointers exist.

Compare values:

    3 == 3

Now compare their left children:

    isSameTree(nullptr, nullptr)

Return true.

Compare their right children:

    isSameTree(nullptr, nullptr)

Return true.

Now:

    rightAns = true && true

    rightAns = true

The invocation comparing node 3 with node 3 returns true.

---------------------------------------
STEP 5: COMBINE RESULTS AT ROOT
---------------------------------------

At node 1:

    leftAns = true
    rightAns = true

Execute:

    return leftAns && rightAns;

    return true && true;

FINAL RESULT:

    true

Both trees are identical.

===============================================================================
9. DRY RUN WITH DIFFERENT VALUES
===============================================================================

TREE P:

                         1
                       /   \
                      2     3

TREE Q:

                         1
                       /   \
                      2     4

At the root:

    1 == 1

Continue.

Compare the left subtrees:

    2 == 2

Their children are also structurally identical.

Therefore:

    leftAns = true

Now compare the right subtrees:

    3 != 4

Our condition executes:

    if (p->val != q->val) {
        return false;
    }

The right recursive invocation returns false.

Therefore:

    rightAns = false

At the root:

    return leftAns && rightAns;

    return true && false;

FINAL RESULT:

    false

The trees are not identical.

===============================================================================
10. IMPORTANT EDGE CASES
===============================================================================

CASE 1: BOTH TREES ARE EMPTY

    p = nullptr
    q = nullptr

Expected:

    true

Reason:

Both trees have the same empty structure.

CASE 2: ONLY THE FIRST TREE IS EMPTY

    p = nullptr
    q = pointer to a node

Expected:

    false

Reason:

Their structures differ.

CASE 3: ONLY THE SECOND TREE IS EMPTY

    p = pointer to a node
    q = nullptr

Expected:

    false

Reason:

Their structures differ.

CASE 4: BOTH ROOTS EXIST BUT VALUES DIFFER

    p->val = 5
    q->val = 10

Expected:

    false

Reason:

Corresponding node values are different.

CASE 5: SAME VALUES, DIFFERENT STRUCTURES

TREE P:

        1
       /
      2

TREE Q:

        1
         \
          2

Expected:

    false

Reason:

The corresponding child positions are different.

CASE 6: BOTH TREES ARE IDENTICAL

Expected:

    true

Reason:

All corresponding nodes and structures match.

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

    bool isSameTree(TreeNode* p, TreeNode* q) {

        // CASE 1:
        // Both pointers are nullptr.
        // Both trees have reached an empty position.
        if (p == nullptr && q == nullptr) {
            return true;
        }


        // CASE 2:
        // Exactly one pointer is nullptr.
        // The structures are different.
        if (
            (p == nullptr && q != nullptr) ||
            (p != nullptr && q == nullptr)
        ) {
            return false;
        }


        // CASE 3:
        // Both pointers exist, but their values are different.
        if (p->val != q->val) {
            return false;
        }


        // STEP 1:
        // Recursively compare the left subtrees.
        bool leftAns = isSameTree(p->left, q->left);


        // STEP 2:
        // Recursively compare the right subtrees.
        bool rightAns = isSameTree(p->right, q->right);


        // STEP 3:
        // Both left and right subtrees must be identical.
        return leftAns && rightAns;
    }

};


/*
===============================================================================
12. COMPLEXITY ANALYSIS
===============================================================================

Let:

    N = Number of nodes in the first tree.
    M = Number of nodes in the second tree.
    H = Maximum height of the recursive comparison.

TIME COMPLEXITY:

    O(min(N, M)) in the worst case when the trees are structurally
    compatible and all corresponding nodes must be examined.

WHY?

Every corresponding pair of nodes is checked at most once.

At each pair, we perform:

    1. Null pointer comparisons.
    2. A node-value comparison.
    3. Recursive comparisons of the left and right children.

Each operation takes O(1) time.

If a mismatch is found early, the function can return before visiting
the remaining nodes.

Therefore, the worst-case time complexity is:

    O(min(N, M))

SPACE COMPLEXITY:

    O(H)

WHY?

The recursive calls consume stack space.

The maximum number of simultaneously active recursive invocations
depends on the height of the compared trees.

For balanced trees:

    O(log N)

For completely skewed trees:

    O(N)

No additional data structure is created to store the comparison results.

Therefore, auxiliary space complexity is:

    O(H)

===============================================================================
13. IMPORTANT LESSONS LEARNED
===============================================================================

LESSON 1: COMPARING TWO TREES SIMULTANEOUSLY

    We pass two TreeNode pointers to the recursive function.

    Each invocation compares corresponding positions in both trees.

LESSON 2: STRUCTURAL COMPARISON

    Same values do not necessarily mean identical trees.

    Their structures must also match.

LESSON 3: NULLPTR BASE CASES

    Both nullptr means true.

    Exactly one nullptr means false.

LESSON 4: SAFE POINTER ACCESS

    We compare null pointers before accessing p->val and q->val.

    This prevents null pointer dereferencing.

LESSON 5: RECURSIVE COMPARISON

    We compare the left subtree with the left subtree.

    We compare the right subtree with the right subtree.

LESSON 6: BOOLEAN RETURN VALUES

    Every recursive invocation returns true or false.

    The parent uses these results to make its decision.

LESSON 7: LOGICAL AND

    Both recursive comparisons must be true.

    Therefore, we use:

        leftAns && rightAns

LESSON 8: CALL STACK

    Recursive calls return to their callers.

    Each parent resumes execution and combines the returned results.

===============================================================================
14. FINAL REVISION CHECKLIST
===============================================================================

[ ] I understand the Same Tree problem statement.

[ ] I understand why DFS is suitable.

[ ] I understand why we pass two TreeNode pointers.

[ ] I understand why both nullptr pointers return true.

[ ] I understand why exactly one nullptr returns false.

[ ] I understand why we compare node values.

[ ] I understand why corresponding left children are compared.

[ ] I understand why corresponding right children are compared.

[ ] I understand how leftAns and rightAns work.

[ ] I understand the logical AND operator.

[ ] I understand recursive boolean returns.

[ ] I understand the call-stack behavior.

[ ] I can implement the solution independently.

===============================================================================
                         END OF DAY 25 NOTES
===============================================================================

PROBLEM:
    LeetCode 100 — Same Tree

APPROACH:
    Recursive DFS + Boolean Comparison

RESULT:
    Accepted

MAIN CONCEPT MASTERED:
    Comparing two binary trees recursively using corresponding nodes
    and combining boolean results.

ALPHA SIGNING OFF.
OVER AND OUT, COMRADE!
===============================================================================
*/
