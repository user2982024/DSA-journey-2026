
/*
===============================================================================
PROBLEM: Check Whether Two Binary Trees Are Identical
PLATFORM: GeeksforGeeks (GFG)
TOPIC: Binary Trees | Recursion | DFS | Tree Comparison
PURPOSE: Detailed revision notes for understanding, explaining, and recalling
         the recursive solution.
===============================================================================

1. PROBLEM STATEMENT
--------------------
Given the roots of two binary trees, r1 and r2, determine whether the trees
are identical.

Two binary trees are identical when BOTH conditions hold:
1. They have the same structure: corresponding child positions are either
   both empty or both occupied.
2. Corresponding nodes contain the same data values.

If both conditions hold throughout the entire trees, return true.
Otherwise, return false.

Example A: Identical trees

       Tree 1          Tree 2
          1               1
         / \             / \
        2   3           2   3

Both structure and values match. Answer: true.

Example B: Different values

       Tree 1          Tree 2
          1               1
         / \             / \
        2   3           2   4

The right child values differ (3 versus 4). Answer: false.

Example C: Different structure

       Tree 1          Tree 2
          1               1
         /                 \
        2                   2

The values are the same, but the child positions differ. Answer: false.

2. CORE RECURSIVE IDEA
----------------------
Compare the two trees at corresponding positions.

For the current pair of pointers:
1. If both pointers are nullptr, both subtrees are empty, so they match.
2. If exactly one pointer is nullptr, the structures differ, so they do not
   match.
3. If both pointers exist but their data values differ, the trees do not match.
4. Otherwise, recursively compare their left subtrees and their right
   subtrees. Both comparisons must be true.

In short:

    Identical(r1, r2) =
        Identical(r1->left,  r2->left)
        AND
        Identical(r1->right, r2->right)

provided both current nodes exist and have equal data.

3. WHY THE BASE CASES COME FIRST
--------------------------------
A. Both pointers are nullptr:

    if (r1 == nullptr && r2 == nullptr) {
        return true;
    }

Both corresponding subtrees are empty. Since they have the same structure
and contain no values that could differ, they are identical.

B. Exactly one pointer is nullptr:

    if (r1 == nullptr || r2 == nullptr) {
        return false;
    }

One subtree is empty and the other has a node. Their structures differ, so
the trees cannot be identical.

The second condition is checked only after the first condition. If both
pointers are nullptr, the first condition returns true immediately. If the
code reaches the second condition, at least one pointer is nullptr and the
other is not.

C. Why check pointers before accessing data?
The code must not read r1->data or r2->data unless both pointers point to
valid nodes. The two pointer checks guarantee that both nodes exist before
the value comparison.

4. THE VALUE CHECK
------------------
    if (r1->data != r2->data) {
        return false;
    }

If the corresponding nodes contain different values, the trees are not
identical. There is no need to inspect the rest of the trees after finding a
difference, because the final answer must already be false.

This is an example of an early return: stop as soon as a condition proves
that the answer is false.

5. WHY BOTH SUBTREES MUST MATCH
-------------------------------
    bool leftAns = isIdentical(r1->left, r2->left);
    bool rightAns = isIdentical(r1->right, r2->right);

    return leftAns && rightAns;

The left recursive call compares the left subtrees in corresponding positions.
The right recursive call compares the right subtrees in corresponding
positions.

The operator && means logical AND:
- true && true  -> true
- true && false -> false
- false && true -> false
- false && false -> false

Therefore, the current pair of nodes is considered identical only if BOTH
left subtrees and right subtrees are identical.

Why not use ||?
Using OR would allow the function to return true when only one side matches.
That is not sufficient: a single mismatch anywhere makes the trees different.

6. THE ORIGINAL SOLUTION
------------------------
The submitted solution is correct:

    bool isIdentical(Node* r1, Node* r2) {
        if (r1 == nullptr && r2 == nullptr) {
            return true;
        }

        if (r1 == nullptr || r2 == nullptr) {
            return false;
        }

        if (r1->data != r2->data) {
            return false;
        }

        bool leftAns = isIdentical(r1->left, r2->left);
        bool rightAns = isIdentical(r1->right, r2->right);

        return leftAns && rightAns;
    }

No logic changes are required.

7. LINE-BY-LINE EXPLANATION
---------------------------

Line 1:
    bool isIdentical(Node* r1, Node* r2)

Receives two node pointers and returns a boolean:
- true means the two subtrees rooted at these pointers are identical.
- false means they differ in structure or in at least one value.

Line 2:
    if (r1 == nullptr && r2 == nullptr)

Checks whether both current subtrees are empty.

Line 3:
    return true;

Two empty subtrees match.

Line 4:
    if (r1 == nullptr || r2 == nullptr)

Checks whether exactly one of the two pointers is empty. Because the previous
condition has already handled the case where both are empty, reaching this
condition means one is empty and the other is not.

Line 5:
    return false;

An empty subtree cannot be identical to a non-empty subtree.

Line 6:
    if (r1->data != r2->data)

At this point, both pointers are non-null, so it is safe to compare their data.
If their values differ, the trees cannot be identical.

Line 7:
    return false;

Stops immediately when a mismatch is found.

Line 8:
    bool leftAns = isIdentical(r1->left, r2->left);

Recursively compares the left child of the first tree with the left child of
the second tree.

Line 9:
    bool rightAns = isIdentical(r1->right, r2->right);

Recursively compares the right child of the first tree with the right child
of the second tree.

Line 10:
    return leftAns && rightAns;

Returns true only if both subtree comparisons returned true.

8. COMPLETE DRY RUN: IDENTICAL TREES
------------------------------------
Tree 1 and Tree 2:

       Tree 1          Tree 2
          1               1
         / \             / \
        2   3           2   3

Call:

    isIdentical(root1, root2)

Step 1: Compare root nodes.
- Both pointers are non-null.
- Both data values are 1.
- Continue to compare left and right subtrees.

Step 2: Compare the left children.
- Compare node 2 with node 2.
- Both pointers are non-null and both data values are 2.
- Compare their left children: nullptr and nullptr -> true.
- Compare their right children: nullptr and nullptr -> true.
- Return true && true = true.

Therefore, leftAns = true.

Step 3: Compare the right children.
- Compare node 3 with node 3.
- Both pointers are non-null and both data values are 3.
- Compare their left children: nullptr and nullptr -> true.
- Compare their right children: nullptr and nullptr -> true.
- Return true && true = true.

Therefore, rightAns = true.

Step 4: Return from the root call.

    leftAns && rightAns
    true && true
    true

Final answer: true.

9. DRY RUN: DIFFERENT VALUES
----------------------------
Tree 1:                Tree 2:

    1                     1
   / \                   / \
  2   3                 2   4

1. The root values are both 1, so comparison continues.
2. The left subtrees rooted at 2 match.
3. The right recursive call compares node 3 with node 4.
4. Both pointers are non-null, but 3 != 4.
5. That call returns false immediately.
6. The root ultimately returns false because both subtrees must match.

Final answer: false.

The implementation evaluates leftAns before rightAns. If the left comparison
is false, the code still computes rightAns because it stores both results in
separate statements. This does not affect correctness, though a mismatch
already guarantees the final result will be false.

10. DRY RUN: DIFFERENT STRUCTURE
-------------------------------
Tree 1:                Tree 2:

    1                     1
   /                       \
  2                         2

1. The roots both exist and have value 1.
2. The left comparison receives node 2 from Tree 1 and nullptr from Tree 2.
3. Exactly one pointer is nullptr, so that call returns false.
4. The right comparison receives nullptr from Tree 1 and node 2 from Tree 2.
5. Exactly one pointer is nullptr, so that call returns false.
6. The root returns false && false = false.

Final answer: false.

Even though both trees contain the values 1 and 2, the structure differs:
node 2 is on the left in one tree and on the right in the other.

11. RECURSION AND RETURN VALUES
-------------------------------
Each recursive call answers a smaller question:
"Are these two particular subtrees identical?"

The calls continue downward until they encounter:
- two empty child pointers, which match; or
- a missing node on only one side, which does not match; or
- a pair of nodes with different values, which does not match.

The boolean answers then return upward. Every pair of corresponding nodes
must pass all required checks for the original call to return true.

12. WHY THE ALGORITHM IS CORRECT
--------------------------------
At each pair of positions:
- If both nodes are absent, the corresponding subtrees match.
- If only one node is absent, the structures differ.
- If both nodes exist but have different values, the trees differ.
- Otherwise, the trees match at this position exactly when their left
  subtrees match and their right subtrees match.

The recursive calls check those two remaining requirements. Thus the function
returns true exactly when the trees have the same structure and the same data
at every corresponding position.

13. EDGE CASES
--------------
A. Both trees are empty

    r1 = nullptr
    r2 = nullptr

Returns true.

B. One tree is empty and the other is not

    r1 = nullptr
    r2 points to a node

Returns false.

C. Both trees contain one node with equal values

    Tree 1: 5
    Tree 2: 5

Returns true because values match and both child positions are empty.

D. Both trees contain one node with different values

    Tree 1: 5
    Tree 2: 8

Returns false at the value comparison.

E. Same values but different shape

Returns false because at some corresponding position one pointer will be
nullptr while the other is non-null.

F. Same root but a different deep descendant

Returns false when the recursive call reaches the first mismatching value or
structure position.

G. Negative or zero values

The algorithm compares values for equality, so zero and negative data values
work normally.

14. COMMON MISTAKES TO AVOID
----------------------------
1. Checking data before checking nullptr
   Dereferencing a null pointer is invalid. Confirm both pointers exist first.

2. Returning false when both pointers are nullptr
   Two empty subtrees match; this base case must return true.

3. Returning true when only one pointer is nullptr
   One empty subtree and one non-empty subtree have different structures.

4. Checking only the data values
   Equal values are not enough if the structures differ.

5. Comparing r1->left with r2->right by mistake
   Corresponding positions must be compared: left with left and right with
   right.

6. Using || instead of &&
   Both subtree comparisons must succeed.

7. Forgetting to return the recursive combination
   The current call must return leftAns && rightAns.

8. Comparing only one subtree
   A mismatch can exist on either side, so both sides must be checked.

9. Assuming equal node counts guarantee identical trees
   Trees can have the same number of nodes and values but arrange them in
   different structures.

15. TIME AND SPACE COMPLEXITY
-----------------------------
Let n1 and n2 be the number of nodes in the two trees.

Time complexity:
- Worst case: O(min(n1, n2)) comparisons before a mismatch is found, or
  O(n) when both trees have n nodes and the algorithm must inspect all nodes.
- If the trees are identical, every node pair is checked, so time is O(n).

Auxiliary space:
- O(h), where h is the maximum recursive depth reached while comparing the
  trees.
- If both trees are balanced, this is O(log n).
- If the trees are skewed, this can be O(n).

The function uses recursive calls rather than an explicit queue or stack.

16. COMPARISON WITH RELATED TREE PROBLEMS
-----------------------------------------
Size:
    return 1 + leftSize + rightSize;

Counts all nodes in one tree.

Sum:
    return root->data + leftSum + rightSum;

Adds all node values.

Count leaves:
    if (root->left == nullptr && root->right == nullptr) return 1;
    return leftAns + rightAns;

Counts nodes that have no children.

Height:
    return 1 + max(leftHeight, rightHeight);

Finds the longest path height under the chosen height convention.

Identical trees:
    return leftAns && rightAns;

Checks whether corresponding parts of two trees both match.

Notice how the return type helps express the problem:
- int for counts, sums, and heights.
- bool for a yes/no comparison.

17. SELF-REVISION QUESTIONS
---------------------------
Try answering these without looking at the explanation:

1. Why does the function return true when both pointers are nullptr?
2. Why does exactly one nullptr cause false?
3. Why must pointer checks happen before comparing data?
4. Why do we compare left with left and right with right?
5. Why is && used instead of ||?
6. Can trees with the same values be non-identical? Explain.
7. What happens when a deep node's value differs?
8. What are the time and auxiliary-space complexities?
9. What is the answer when both trees are empty?
10. What is the answer when one tree has a left child and the other has a
    right child with the same value?

18. QUICK REVISION SUMMARY
--------------------------
- Identical trees need the same structure and the same values.
- Both nullptr: return true.
- Exactly one nullptr: return false.
- Different node values: return false.
- Otherwise compare left subtrees and right subtrees recursively.
- Final result: leftAns && rightAns.
- Time: O(n) when both trees have n nodes and all corresponding positions
  must be checked; an early mismatch may stop the work sooner.
- Auxiliary space: O(h) for recursive call-stack depth.

19. ORIGINAL GFG-STYLE SOLUTION
-------------------------------
The code below preserves the submitted algorithm and variable names.

===============================================================================
*/

class Solution {
  public:
    bool isIdentical(Node* r1, Node* r2) {
        // Two empty subtrees are identical.
        if (r1 == nullptr && r2 == nullptr) {
            return true;
        }

        // If only one subtree is empty, their structures differ.
        if (r1 == nullptr || r2 == nullptr) {
            return false;
        }

        // Both nodes exist, so compare their stored values.
        if (r1->data != r2->data) {
            return false;
        }

        // Compare the corresponding left subtrees.
        bool leftAns = isIdentical(r1->left, r2->left);

        // Compare the corresponding right subtrees.
        bool rightAns = isIdentical(r1->right, r2->right);

        // Both sides must match for the trees to be identical.
        return leftAns && rightAns;
    }
};

/*
===============================================================================
END OF REVISION NOTES
===============================================================================
*/
