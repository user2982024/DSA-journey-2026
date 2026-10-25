
/*
===============================================================================
PROBLEM: Check Whether a Binary Tree Is Symmetric
PLATFORM: GeeksforGeeks (GFG)
TOPIC: Binary Trees | Recursion | DFS | Mirror Trees
PURPOSE: Detailed revision notes for understanding, explaining, and recalling
         the recursive solution.
===============================================================================

1. PROBLEM STATEMENT
--------------------
Given the root of a binary tree, determine whether the tree is symmetric
around its center.

A tree is symmetric when its left and right subtrees are mirror images of one
another.

For two subtrees to be mirror images:
1. Their corresponding nodes must have equal data values.
2. The left subtree of the first side must match the right subtree of the
   second side.
3. The right subtree of the first side must match the left subtree of the
   second side.
4. Their structures must mirror each other: corresponding positions must
   both contain nodes or both be empty.

Example A: Symmetric

          1
         / \
        2   2
       / \ / \
      3  4 4  3

The left and right sides mirror each other. Answer: true.

Example B: Not symmetric because values differ

          1
         / \
        2   2
         \   \
          3   3

The node positions do not mirror each other. Answer: false.

Example C: Not symmetric because values differ

          1
         / \
        2   2
       /     \
      3       4

The structure is mirrored, but the corresponding outer values 3 and 4 differ.
Answer: false.

2. CORE IDEA: MIRROR COMPARISON
-------------------------------
The helper function check(r1, r2) does not compare two trees in the ordinary
left-with-left way. It compares them as mirror images.

For each pair of nodes:
- Compare r1 with r2.
- Compare r1->left with r2->right.
- Compare r1->right with r2->left.

That is why the recursive calls cross over:

    bool firstHalf = check(r1->left, r2->right);
    bool secondHalf = check(r1->right, r2->left);

Both results must be true.

3. WHY THE HELPER FUNCTION IS NEEDED
------------------------------------
The public function isSymmetric(root) starts the check by comparing the
root's left and right subtrees:

    return check(root->left, root->right);

The helper function checks whether any two supplied subtrees are mirrors.

It needs two pointers because symmetry is a relationship between two sides
of the same tree. A single subtree cannot establish symmetry by itself.

4. BASE CASES
-------------
A. Both pointers are nullptr:

    if (r1 == nullptr && r2 == nullptr) {
        return true;
    }

Both corresponding mirror positions are empty, so they match.

B. Exactly one pointer is nullptr:

    if (r1 == nullptr || r2 == nullptr) {
        return false;
    }

One side has a node and the corresponding mirror position does not. The
structures are not symmetric.

The first condition handles the case where both pointers are nullptr. If the
code reaches the second condition, exactly one pointer must be nullptr.

C. Why check pointers before data?
The code must not read r1->data or r2->data unless both pointers are valid.
The null checks guarantee that both nodes exist before the value comparison.

5. VALUE CHECK
--------------
    if (r1->data != r2->data) {
        return false;
    }

Corresponding mirror nodes must have equal values. If they differ, the tree
is not symmetric, and there is no need to inspect deeper nodes.

6. WHY THE RECURSIVE CALLS CROSS
--------------------------------
    bool firstHalf = check(r1->left, r2->right);
    bool secondHalf = check(r1->right, r2->left);

Imagine standing at the center of the tree and reflecting one side across
the center line:
- The left child on one side corresponds to the right child on the other.
- The right child on one side corresponds to the left child on the other.

Therefore:
- left is compared with right;
- right is compared with left.

This is the central distinction between checking whether two trees are
identical and checking whether two subtrees are mirrors.

Identical-tree comparison:
    isIdentical(r1->left, r2->left)
    isIdentical(r1->right, r2->right)

Mirror comparison:
    check(r1->left, r2->right)
    check(r1->right, r2->left)

7. WHY BOTH RESULTS USE &&
--------------------------------
    return firstHalf && secondHalf;

The operator && means logical AND. Both mirror comparisons must succeed.

- true && true  -> true
- true && false -> false
- false && true -> false
- false && false -> false

If either side fails to mirror the other, the whole tree is not symmetric.
Using || would be incorrect because it would accept a tree when only one half
matches.

8. THE ORIGINAL SOLUTION
------------------------
The submitted solution is correct:

    class Solution {
      private:
        bool check(Node* r1, Node* r2) {
            if (r1 == nullptr && r2 == nullptr) {
                return true;
            }

            if (r1 == nullptr || r2 == nullptr) {
                return false;
            }

            if (r1->data != r2->data) {
                return false;
            }

            bool firstHalf = check(r1->left, r2->right);
            bool secondHalf = check(r1->right, r2->left);

            return firstHalf && secondHalf;
        }

      public:
        bool isSymmetric(Node* root) {
            if (root == nullptr) {
                return true;
            }

            return check(root->left, root->right);
        }
    };

No logic changes are required.

9. LINE-BY-LINE EXPLANATION
---------------------------

Private helper:
    bool check(Node* r1, Node* r2)

Returns true if the two supplied subtrees are mirror images; otherwise false.
It is private because it is an internal helper used by isSymmetric.

Base case 1:
    if (r1 == nullptr && r2 == nullptr)

Both mirror positions are empty.

    return true;

Two empty positions match.

Base case 2:
    if (r1 == nullptr || r2 == nullptr)

Exactly one mirror position is empty.

    return false;

The structure cannot be symmetric at these positions.

Value comparison:
    if (r1->data != r2->data)

Both nodes exist, so compare their values.

    return false;

Different values at mirror positions make the tree asymmetric.

First recursive call:
    bool firstHalf = check(r1->left, r2->right);

Checks whether the first subtree's left side mirrors the second subtree's
right side.

Second recursive call:
    bool secondHalf = check(r1->right, r2->left);

Checks whether the first subtree's right side mirrors the second subtree's
left side.

Combination:
    return firstHalf && secondHalf;

Both crossed comparisons must succeed.

Public function:
    bool isSymmetric(Node* root)

This is the function called by the platform.

    if (root == nullptr) {
        return true;
    }

An empty tree is symmetric around its center: there is no mismatch.

    return check(root->left, root->right);

For a non-empty tree, start by checking whether the root's two subtrees are
mirror images. The root itself does not need to be compared with another
node because it lies on the center line.

10. COMPLETE DRY RUN: SYMMETRIC TREE
------------------------------------
Consider:

          1
         / \
        2   2
       / \ / \
      3  4 4  3

Call:

    isSymmetric(root)

Step 1: root is not nullptr.
The function calls:

    check(root->left, root->right)
    check(node 2 on left, node 2 on right)

Step 2: Compare the two node-2 values.
- Both pointers exist.
- 2 == 2.
- Continue with crossed child pairs.

Step 3: First crossed comparison:

    check(left node 2's left child,
          right node 2's right child)

This compares node 3 with node 3.
- Both nodes exist and their values match.
- Their outer child pointers are both nullptr, so that pair returns true.
- Their other child pointers are also both nullptr, so that pair returns true.
- The node-3 comparison returns true.

Step 4: Second crossed comparison:

    check(left node 2's right child,
          right node 2's left child)

This compares node 4 with node 4.
- Their values match.
- Their corresponding mirror child positions are all nullptr.
- The comparison returns true.

Step 5: Combine at the node-2 pair.

    firstHalf && secondHalf
    true && true
    true

Step 6: The root call returns true.

Final answer: true.

11. DRY RUN: ASYMMETRIC STRUCTURE
---------------------------------
Consider:

          1
         / \
        2   2
         \   \
          3   3

The root calls check(left node 2, right node 2). Their values match.

The first crossed comparison is:

    check(left node 2's left child, right node 2's right child)

This compares nullptr with node 3.
Exactly one pointer is nullptr, so it returns false.

The second crossed comparison compares node 3 on the left side with nullptr
on the right side and also returns false.

The helper returns:

    false && false = false

Final answer: false.

Although the two sides contain the same values, the node positions do not
mirror each other.

12. RECURSION AND RETURN VALUES
-------------------------------
Each check(r1, r2) call asks:
"Are these two subtrees mirror images?"

The calls move down the tree by comparing crossed child positions. They stop
when:
- both positions are empty (true);
- exactly one position is empty (false); or
- the two node values differ (false).

The boolean results return upward. Every corresponding mirror pair must
match for the original call to return true.

13. WHY THE ALGORITHM IS CORRECT
--------------------------------
At any pair of corresponding mirror positions:
- If both are empty, they match.
- If only one is empty, the structure does not mirror.
- If both exist but their values differ, the values do not mirror.
- Otherwise, symmetry at this pair requires both crossed child pairs to be
  mirror images.

The helper function checks exactly these conditions recursively. The public
function starts this process at the root's left and right subtrees. Therefore,
it returns true exactly when the tree is symmetric.

14. EDGE CASES
--------------
A. Empty tree

    root = nullptr

Returns true.

B. One node

        7

The root has no left or right child. The helper receives nullptr and nullptr,
so the tree is symmetric. Returns true.

C. Root with equal-valued children and no grandchildren

        1
       / \
      2   2

Returns true.

D. Root with unequal child values

        1
       / \
      2   3

The child values differ. Returns false.

E. Same values but different child positions

          1
         / \
        2   2
         \   \
          3   3

Returns false because the shape is not mirrored.

F. Deeper mismatch

Even if the root children match, a value or structural mismatch several
levels down makes the whole tree asymmetric.

G. Negative and zero values

Values are compared for equality, so negative values and zero work normally.

15. COMMON MISTAKES TO AVOID
----------------------------
1. Comparing left with left and right with right
   That checks whether the subtrees are identical, not whether they are mirrors.

2. Forgetting the root == nullptr case
   An empty tree is symmetric and should return true.

3. Returning false when both helper pointers are nullptr
   Two empty mirror positions match, so return true.

4. Returning true when only one helper pointer is nullptr
   The structures do not mirror at that position.

5. Checking node values before checking nullptr
   This could dereference a null pointer.

6. Using || instead of &&
   Both crossed subtree comparisons must succeed.

7. Comparing only values and ignoring structure
   Symmetry requires matching node positions as well as values.

8. Comparing only one crossed pair
   A mismatch can occur in either the outer pair or the inner pair, so both
   crossed comparisons are required.

9. Comparing the root to itself unnecessarily
   The root is on the symmetry center line. The meaningful initial comparison
   is between root->left and root->right.

10. Confusing identical and symmetric trees
    Identical trees compare left-to-left and right-to-right.
    Symmetry compares left-to-right and right-to-left.

16. TIME AND SPACE COMPLEXITY
-----------------------------
Time complexity: O(n)

In the worst case, each node is visited once as part of a mirror comparison.
If a mismatch is found early, the function may stop before visiting every
node.

Auxiliary space: O(h)

Recursive calls use the call stack, where h is the tree height.
- Balanced tree: O(log n) stack space.
- Highly skewed tree: O(n) stack space.

17. COMPARISON WITH IDENTICAL TREES
-----------------------------------
Identical trees:
    isIdentical(r1->left, r2->left)
    isIdentical(r1->right, r2->right)

The same positions are compared.

Symmetric tree:
    check(r1->left, r2->right)
    check(r1->right, r2->left)

Opposite positions are compared to test reflection across the center.

Both algorithms use similar null checks and value comparisons, but their
recursive child pairing is different. This is the most important distinction.

18. SELF-REVISION QUESTIONS
---------------------------
Try to answer these without looking at the explanation:

1. What does symmetric mean for a binary tree?
2. Why does an empty tree return true?
3. Why does check(nullptr, nullptr) return true?
4. Why does check(nullptr, node) return false?
5. Why do the recursive calls cross the child pointers?
6. Why is && used instead of ||?
7. What is the difference between identical trees and symmetric trees?
8. What happens if values match but the structure differs?
9. What are the time and auxiliary-space complexities?
10. What does the helper function return?

19. QUICK REVISION SUMMARY
--------------------------
- A symmetric tree is a mirror image around its center.
- Empty tree: true.
- Both helper pointers nullptr: true.
- Exactly one helper pointer nullptr: false.
- Different mirror-node values: false.
- Compare left with right and right with left.
- Both recursive results must be true: firstHalf && secondHalf.
- Time: O(n).
- Auxiliary space: O(h), due to recursive call-stack depth.

20. ORIGINAL GFG-STYLE SOLUTION
-------------------------------
The code below preserves the submitted algorithm and variable names.

===============================================================================
*/

class Solution {
  private:
    bool check(Node* r1, Node* r2) {
        // Two empty mirror positions match.
        if (r1 == nullptr && r2 == nullptr) {
            return true;
        }

        // Exactly one empty position means the structure is asymmetric.
        if (r1 == nullptr || r2 == nullptr) {
            return false;
        }

        // Corresponding mirror nodes must have equal values.
        if (r1->data != r2->data) {
            return false;
        }

        // Compare the first subtree's left side with the second's right side.
        bool firstHalf = check(r1->left, r2->right);

        // Compare the first subtree's right side with the second's left side.
        bool secondHalf = check(r1->right, r2->left);

        // Both crossed comparisons must match.
        return firstHalf && secondHalf;
    }

  public:
    bool isSymmetric(Node* root) {
        // An empty tree is symmetric.
        if (root == nullptr) {
            return true;
        }

        // The root's left and right subtrees must be mirror images.
        return check(root->left, root->right);
    }
};

/*
===============================================================================
END OF REVISION NOTES
===============================================================================
*/
