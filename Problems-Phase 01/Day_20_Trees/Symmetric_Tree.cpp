/*
 * ============================================================
 * Problem: 101. Symmetric Tree
 * Platform: LeetCode
 * Topic: Binary Trees, Recursion, DFS, Mirror Comparison
 * Difficulty: Easy
 * Language: C++
 * Status: Accepted
 * ============================================================
 *
 * PROBLEM STATEMENT:
 *
 * Given the root of a binary tree, determine whether the tree
 * is symmetric around its center.
 *
 * A binary tree is symmetric if its left and right subtrees
 * are mirror images of each other.
 *
 * Two subtrees are mirror images when:
 * 1. Their corresponding nodes have equal values.
 * 2. The left child of one node matches the right child
 *    of its mirror node.
 * 3. The right child of one node matches the left child
 *    of its mirror node.
 * 4. The structure of both subtrees matches symmetrically.
 *
 * Return true if the tree is symmetric; otherwise, return false.
 *
 * ============================================================
 * EXAMPLE 1:
 *
 * Input:
 *         1
 *        / \
 *       2   2
 *      / \ / \
 *     3  4 4  3
 *
 * Output: true
 *
 * Explanation:
 * The root's left and right subtrees are mirror images.
 * The outer nodes contain 3 and 3, and the inner nodes
 * contain 4 and 4. Their structures also match.
 *
 * ============================================================
 * EXAMPLE 2:
 *
 * Input:
 *         1
 *        / \
 *       2   2
 *        \   \
 *         3   3
 *
 * Output: false
 *
 * Explanation:
 * The left subtree's right child contains 3, but the
 * right subtree's left child is nullptr.
 * The structures do not match as mirror images.
 *
 * ============================================================
 * EXAMPLE 3:
 *
 * Input: root = nullptr
 * Output: true
 *
 * Explanation:
 * An empty binary tree is considered symmetric.
 *
 * ============================================================
 * APPROACH: RECURSIVE MIRROR COMPARISON
 *
 * We create a helper function:
 *
 *     bool check(TreeNode* l, TreeNode* r)
 *
 * It receives two nodes that must be mirror images.
 *
 * BASE CASE 1:
 * If both pointers are nullptr, return true.
 *
 * Both corresponding positions are empty, so they match.
 *
 * BASE CASE 2:
 * If exactly one pointer is nullptr, return false.
 *
 * One side contains a node while the other side does not.
 * Therefore, the structures are not symmetric.
 *
 * BASE CASE 3:
 * If both nodes exist but their values differ, return false.
 *
 * Corresponding mirror nodes must contain equal values.
 *
 * RECURSIVE CASE:
 *
 * Compare the following two mirror pairs:
 *
 * Pair 1:
 *     l->left  and  r->right
 *
 * Pair 2:
 *     l->right and  r->left
 *
 * Store both recursive results and return their logical AND.
 *
 * Both pairs must be symmetric for the current pair to
 * be considered symmetric.
 *
 * MAIN FUNCTION:
 *
 * If root is nullptr, return true.
 * Otherwise, compare root->left and root->right using check().
 *
 * The root itself does not need to be compared with another
 * node because it is the center of the symmetry.
 *
 * ============================================================
 * FINAL SOLUTION:
 */

class Solution {
private:
    bool check(TreeNode* l, TreeNode* r) {

        // Base Case 1:
        // Both corresponding nodes are absent.
        if (l == nullptr && r == nullptr) {
            return true;
        }

        // Base Case 2:
        // The left node is absent, but the right node exists.
        if (!l && r) {
            return false;
        }

        // Base Case 3:
        // The right node is absent, but the left node exists.
        if (!r && l) {
            return false;
        }

        // Base Case 4:
        // Both nodes exist, but their values do not match.
        if (l->val != r->val) {
            return false;
        }

        // Recursive Comparison 1:
        // Compare the left child of l with the right child of r.
        bool val1 = check(l->left, r->right);

        // Recursive Comparison 2:
        // Compare the right child of l with the left child of r.
        bool val2 = check(l->right, r->left);

        // Both mirror comparisons must succeed.
        return val1 && val2;
    }

public:
    bool isSymmetric(TreeNode* root) {

        // An empty tree is symmetric.
        if (root == nullptr) {
            return true;
        }

        // Compare the left and right subtrees of the root.
        return check(root->left, root->right);
    }
};

/*
 * ============================================================
 * DETAILED EXECUTION TRACE — EXAMPLE 1
 *
 * Tree:
 *
 *         1
 *        / \
 *       2   2
 *      / \ / \
 *     3  4 4  3
 *
 * STEP 1:
 *
 * isSymmetric(root) receives the root containing 1.
 *
 * The root is not nullptr.
 *
 * Call:
 *     check(root->left, root->right)
 *
 * Now l points to 2 on the left and r points to 2 on the right.
 *
 * STEP 2:
 *
 * Both pointers exist.
 * Their values are equal: 2 == 2.
 *
 * First recursive call:
 *     check(l->left, r->right)
 *
 * This compares the outer nodes: 3 and 3.
 *
 * Second recursive call:
 *     check(l->right, r->left)
 *
 * This compares the inner nodes: 4 and 4.
 *
 * STEP 3 — OUTER PAIR:
 *
 * Both nodes contain 3.
 *
 * Compare their outer children:
 *     check(nullptr, nullptr)
 *
 * Returns true.
 *
 * Compare their inner children:
 *     check(nullptr, nullptr)
 *
 * Returns true.
 *
 * Therefore:
 *     true && true = true
 *
 * The comparison of the outer pair returns true.
 *
 * STEP 4 — INNER PAIR:
 *
 * Both nodes contain 4.
 *
 * Their corresponding children are all nullptr.
 *
 * Both recursive comparisons return true.
 *
 * Therefore:
 *     true && true = true
 *
 * The comparison of the inner pair returns true.
 *
 * STEP 5 — RETURN TO THE PAIR OF 2s:
 *
 * The first recursive comparison returned true.
 * The second recursive comparison returned true.
 *
 * Therefore:
 *     val1 && val2
 *     true && true = true
 *
 * check(2, 2) returns true.
 *
 * STEP 6 — FINAL RESULT:
 *
 * isSymmetric(root) receives true from check().
 *
 * Final output:
 *     true
 *
 * ============================================================
 * ISSUES ENCOUNTERED AND HOW THEY WERE RESOLVED
 *
 * ISSUE 1: Initially considering only one recursive comparison
 *
 * Initial idea:
 *     check(l->left, r->right)
 *
 * Why it was insufficient:
 * This checks only the outer mirror pair.
 * The inner mirror pair would remain unchecked.
 *
 * Resolution:
 * Add the second comparison:
 *     check(l->right, r->left)
 *
 * Lesson:
 * Always identify every pair of corresponding positions
 * required by the recursive definition of the problem.
 *
 * ------------------------------------------------------------
 *
 * ISSUE 2: Dereferencing pointers before checking nullptr
 *
 * Initial idea:
 *     if (l->val != r->val)
 *
 * Why it was incorrect:
 * Either pointer might be nullptr.
 * Accessing ->val through a nullptr causes undefined behavior
 * and may cause a runtime error.
 *
 * Resolution:
 * First handle the both-null and one-null cases.
 * Only then compare the node values.
 *
 * Lesson:
 * Validate pointers before dereferencing them.
 *
 * ------------------------------------------------------------
 *
 * ISSUE 3: Returning after the first recursive call
 *
 * Initial idea:
 *     return check(l->left, r->right);
 *     return check(l->right, r->left);
 *
 * Why it was incorrect:
 * Once the first return executes, the function exits.
 * The second recursive call becomes unreachable.
 *
 * Resolution:
 * Store both results:
 *     bool val1 = check(l->left, r->right);
 *     bool val2 = check(l->right, r->left);
 *
 * Then combine them:
 *     return val1 && val2;
 *
 * Lesson:
 * A return statement ends the current function call.
 * Multiple recursive results must be combined when the
 * problem requires all comparisons to succeed.
 *
 * Note:
 * The Boolean expression could also be returned directly:
 *     return check(l->left, r->right) &&
 *            check(l->right, r->left);
 *
 * Logical AND short-circuits if the first comparison is false.
 *
 * ------------------------------------------------------------
 *
 * ISSUE 4: Using 'return l && r' as the final result
 *
 * Why it was incorrect:
 * This expression checks whether both pointers are non-null.
 * It does not verify whether their children are mirror images.
 *
 * Resolution:
 * Return the results of both recursive comparisons:
 *     return val1 && val2;
 *
 * Lesson:
 * Return the condition that represents the actual problem,
 * not merely a condition that is true for the current nodes.
 *
 * ------------------------------------------------------------
 *
 * ISSUE 5: Thinking a single-node tree needs a separate case
 *
 * Initial idea:
 * Add a special condition to handle a tree with one node.
 *
 * Why it was unnecessary:
 * For a single-node tree, root->left and root->right are
 * both nullptr.
 *
 * The helper function receives:
 *     check(nullptr, nullptr)
 *
 * Its first base case returns true.
 *
 * Resolution:
 * Keep the main function simple:
 *     if (root == nullptr) return true;
 *     return check(root->left, root->right);
 *
 * Lesson:
 * Before adding another special case, check whether the
 * existing recursive base cases already handle it.
 *
 * ============================================================
 * EDGE CASES
 *
 * 1. Empty tree:
 *    root == nullptr
 *    Expected result: true
 *
 * 2. Single-node tree:
 *        1
 *    Expected result: true
 *
 * 3. Two equal children:
 *        1
 *       / \
 *      2   2
 *    Expected result: true
 *
 * 4. Unequal child values:
 *        1
 *       / \
 *      2   3
 *    Expected result: false
 *
 * 5. Equal values but different structures:
 *        1
 *       / \
 *      2   2
 *       \   \
 *        3   3
 *    Expected result: false
 *
 * 6. Symmetric tree with several levels:
 *    Every corresponding mirror node has the same value,
 *    and both sides have matching mirrored structures.
 *    Expected result: true
 *
 * 7. Deep or skewed trees:
 *    The algorithm remains correct, but recursion depth
 *    can become large.
 *
 * ============================================================
 * COMPLEXITY ANALYSIS
 *
 * TIME COMPLEXITY: O(n)
 *
 * n = number of nodes in the binary tree.
 *
 * Each node is visited at most once as part of the mirror
 * comparisons. Therefore, the total work is linear.
 *
 * AUXILIARY SPACE COMPLEXITY: O(h)
 *
 * h = height of the binary tree.
 *
 * The recursive calls consume stack space proportional to
 * the height of the tree.
 *
 * Balanced tree:
 *     h = O(log n)
 *     Auxiliary space = O(log n)
 *
 * Worst-case skewed tree:
 *     h = O(n)
 *     Auxiliary space = O(n)
 *
 * The two Boolean variables use O(1) additional space per
 * active call; the recursive call stack determines the
 * overall auxiliary-space bound.
 *
 * ============================================================
 * KEY LEARNINGS
 *
 * 1. Binary-tree recursion often requires comparing two
 *    nodes together rather than processing one subtree alone.
 *
 * 2. Mirror comparisons reverse the child directions:
 *       left with right
 *       right with left
 *
 * 3. Recursive base cases must handle both-null and
 *    exactly-one-null pointer situations.
 *
 * 4. Never dereference a pointer before establishing that
 *    it points to a valid node.
 *
 * 5. A return statement immediately exits its current call.
 *
 * 6. Use logical AND when every required comparison must
 *    succeed.
 *
 * 7. A recursive function should return the actual Boolean
 *    condition required by the problem.
 *
 * 8. Trace recursive calls and returns separately:
 *    calls move down the tree; results return up the stack.
 *
 * 9. Analyze recursive space using tree height, not merely
 *    the number of recursive calls.
 *
 * 10. Test the structure of a tree, not only the values.
 *     Equal values alone do not guarantee symmetry.
 *
 * ============================================================
 * FINAL STATUS
 *
 * LeetCode 101 — Symmetric Tree
 * Solution: Accepted
 * Time Complexity: O(n)
 * Auxiliary Space: O(h)
 *
 * The solution was developed by reasoning through mirror
 * pairs, fixing pointer-check ordering, and combining the
 * Boolean results of recursive calls.
 *
 * ============================================================
 */ 