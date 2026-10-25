
/*
================================================================================
PROBLEM: Left View of Binary Tree
PLATFORM: GeeksforGeeks (GFG)
TOPIC: Binary Trees | DFS | Recursion | Tree Views
APPROACH: Recursive DFS, visiting LEFT before RIGHT
PURPOSE: Comprehensive revision notes intended to be sufficient for later
         review without needing to reopen the original discussion.
================================================================================

0. IMPORTANT REVIEW OF THE SUBMITTED CODE
-----------------------------------------
Your core algorithm is correct: it records the first node encountered at each
depth by doing a depth-first traversal that visits the left child before the
right child.

There is one implementation detail worth improving for reusable code:
the submitted class has these member variables:

    vector<int> ans;
    int level = 0;

and leftView() appends into ans without clearing it. If the same Solution
object is used for more than one call, old answers could remain in ans.
Many coding-platform test harnesses create a fresh Solution object per test,
but robust code should not rely on that assumption.

The helper also accepts ans by reference and level as a parameter, so the
member variables are unnecessary. A clean version is included at the end that
preserves your algorithm and helper style while making the answer local to
leftView(). The original submitted version is discussed below as written.

One more detail: `ans.size() == level` works here because:
- level starts at 0;
- the DFS visits levels in order of first discovery;
- exactly one node is added the first time each depth is reached.
Using `ans.size()` is valid because it is the number of levels already
represented in the answer, not the number of nodes visited overall.

================================================================================
1. PROBLEM STATEMENT
================================================================================
Given the root of a binary tree, return the nodes visible when the tree is
viewed from its left side, ordered from top to bottom.

At each depth, the left view contains the leftmost node that exists at that
depth. If there is no node at a particular possible position, we do not invent
one: we record the first actual node reached at that depth.

Example:

              1
             / \
            2   3
           / \   \
          4   5   6
               \
                7

The levels contain:
- Level 0: node 1
- Level 1: nodes 2, 3             -> leftmost is 2
- Level 2: nodes 4, 5, 6          -> leftmost is 4
- Level 3: node 7                 -> leftmost/only node is 7

Left view: [1, 2, 4, 7]

The exact example shape is not important; the rule is:
ONE visible node per depth, specifically the first node reached from the left.

================================================================================
2. WHAT DOES "LEFT VIEW" MEAN?
================================================================================
Imagine standing to the left of the tree and looking toward it. Nodes hidden
behind other nodes at the same depth are not visible from that side.

For algorithm purposes, this means:
- At depth 0, the root is visible.
- At depth 1, the leftmost existing node is visible.
- At depth 2, the leftmost existing node is visible.
- Continue the same way for every depth containing a node.

The left view is not simply "all nodes that have no left sibling", nor is it
"follow the left pointer until nullptr". A visible node can be reached by
moving right at some point if all nodes further left at that same depth are
missing.

Example:

        1
       /
      2
       \
        3
         \
          4

Left view: [1, 2, 3, 4]

Even though node 3 is reached by a right pointer from node 2, it is the only
node at its depth, so it is visible from the left.

================================================================================
3. THE MAIN ALGORITHM
================================================================================
Your algorithm uses recursive Depth-First Search (DFS).

The key lines are:

    if (ans.size() == level) {
        ans.push_back(root->data);
    }

    func(root->left, level + 1, ans);
    func(root->right, level + 1, ans);

The traversal visits:
1. Current node.
2. Entire left subtree.
3. Entire right subtree.

This is a preorder-style DFS (Node -> Left -> Right).

Why visit left first?
At each depth, we want the leftmost node. By exploring the left subtree
before the right subtree, DFS reaches the leftmost available node at that
depth first. Once a value is stored for that depth, later nodes at the same
depth are ignored.

This is the key invariant:

    ans contains exactly one value for every depth visited so far,
    and that value is the first node DFS encountered at that depth.

Because the traversal visits left before right, that first node is the
leftmost node at the depth.

================================================================================
4. UNDERSTANDING THE LEVEL PARAMETER
================================================================================
The helper has this signature:

    void func(Node* root, int level, vector<int>& ans)

Parameters:
- root: the node currently being processed.
- level: the depth of this node, measured in edges from the root.
- ans: reference to the result vector that all recursive calls share.

The level convention used by your code is:
- Root is at level 0.
- Root's children are at level 1.
- Grandchildren are at level 2.
- And so on.

Why does every recursive call use level + 1?

    func(root->left, level + 1, ans);
    func(root->right, level + 1, ans);

Moving from a parent to either child moves exactly one edge downward, so the
child's depth is one more than the parent's depth.

The `level` parameter is passed by value. Each recursive call receives its
own integer copy, so the left recursion's level changes do not mutate the
level variable belonging to the parent call. The vector is passed by
reference, however, so every call updates the same answer vector.

================================================================================
5. THE NULLPTR BASE CASE
================================================================================
    if (root == nullptr) {
        return;
    }

A nullptr is not a real node, so there is no value to record and no children
to visit. The function simply stops that branch of recursion.

This base case is necessary because leaf nodes have left and right pointers
that are nullptr. The recursive calls eventually reach those pointers.

Notice the return type is `void`: the helper does not return a value. It
updates `ans` through its reference parameter.

================================================================================
6. WHY `ans.size() == level` WORKS
================================================================================
    if (ans.size() == level) {
        ans.push_back(root->data);
    }

This condition is the heart of the algorithm.

`ans.size()` tells us how many depths have already contributed a value.

Because the root is at level 0:
- Before visiting the root, ans.size() is 0. Since 0 == 0, add the root.
- Before the first node at level 1, ans.size() is 1. Since 1 == 1, add it.
- Before the first node at level 2, ans.size() is 2. Since 2 == 2, add it.
- Once a level already has a value, ans.size() is greater than that level,
  so a later node at that level is not added.

Example: suppose the first node at level 2 is node 4.
- ans.size() is 2.
- level is 2.
- Condition is true, so node 4 is added.
- ans.size() becomes 3.
- If DFS later reaches node 5 at level 2, ans.size() is 3 while level is 2.
- 3 == 2 is false, so node 5 is ignored.

Why use equality (`==`) instead of a condition like `ans.size() <= level`?
In this traversal, the first visit to each depth happens in increasing depth
order, and exactly one value is appended for each new depth. Thus, when the
first node at a new depth is visited, ans.size() equals that depth. For
subsequent visits to an already-recorded depth, ans.size() is larger than
that depth.

This reasoning depends on starting the root at level 0 and recording one
answer per depth. Do not change the level convention without adjusting the
condition accordingly.

================================================================================
7. WHY LEFT RECURSION MUST COME FIRST
================================================================================
Your code uses:

    func(root->left, level + 1, ans);
    func(root->right, level + 1, ans);

The order is important.

Suppose this tree is given:

          1
         / \
        2   3
         \   \
          5   6

At level 2, node 5 is reached before node 6 because DFS fully explores the
left side first. Node 5 is therefore recorded as the visible node at level 2.

If you reverse the recursive calls:

    func(root->right, level + 1, ans);
    func(root->left, level + 1, ans);

then the same logic records the rightmost node at each depth. That produces
the RIGHT VIEW, not the left view.

So the relationship is:
- Left-first DFS + first node at each depth -> left view.
- Right-first DFS + first node at each depth -> right view.

================================================================================
8. COMPLETE DRY RUN
================================================================================
Consider this tree:

              1
             / \
            2   3
           / \   \
          4   5   6
               \
                7

Initial call:

    leftView(root)
        -> func(root, 0, ans)

Initially:
    ans = []
    level = 0

STEP 1: Visit node 1 at level 0
--------------------------------
root is not nullptr.

Check:
    ans.size() == level
    0 == 0 -> true

Append 1:
    ans = [1]

Then visit node 1's left child: node 2 at level 1.

STEP 2: Visit node 2 at level 1
--------------------------------
Check:
    ans.size() == level
    1 == 1 -> true

Append 2:
    ans = [1, 2]

Then visit node 2's left child: node 4 at level 2.

STEP 3: Visit node 4 at level 2
--------------------------------
Check:
    ans.size() == level
    2 == 2 -> true

Append 4:
    ans = [1, 2, 4]

Node 4 has no children:
- func(nullptr, 3, ans) returns immediately for its left child.
- func(nullptr, 3, ans) returns immediately for its right child.

DFS returns to node 2 and continues with node 2's right child, node 5.

STEP 4: Visit node 5 at level 2
--------------------------------
Current answer:
    ans = [1, 2, 4]

Check:
    ans.size() == level
    3 == 2 -> false

Node 5 is not appended because level 2 already has its left-view value, 4.

Node 5 has no left child, so that nullptr call returns. Then DFS visits node 5's
right child, node 7 at level 3.

STEP 5: Visit node 7 at level 3
--------------------------------
Check:
    ans.size() == level
    3 == 3 -> true

Append 7:
    ans = [1, 2, 4, 7]

Node 7 has no children, so both nullptr calls return.

DFS returns up to node 1 and visits its right child, node 3 at level 1.

STEP 6: Visit node 3 at level 1
--------------------------------
Current answer:
    ans = [1, 2, 4, 7]

Check:
    ans.size() == level
    4 == 1 -> false

Node 3 is not appended because level 1 already has node 2.

DFS then visits node 3's left child, nullptr, and then its right child, node 6
at level 2.

STEP 7: Visit node 6 at level 2
--------------------------------
Check:
    ans.size() == level
    4 == 2 -> false

Node 6 is not appended because level 2 already has node 4.

Both children of node 6 are nullptr, so recursion ends.

FINAL RESULT:
    [1, 2, 4, 7]

The answer records the first node reached at each depth during left-first DFS.

================================================================================
9. CALL-STACK AND BACKTRACKING
================================================================================
A simplified traversal order for the example is:

    1
    2
    4
    nullptr
    nullptr
    5
    nullptr
    7
    nullptr
    nullptr
    3
    nullptr
    6
    nullptr
    nullptr

The exact calls include nullptr pointers because the function recursively
visits each child pointer. Null calls immediately return.

Important distinction:
- The recursive call stack controls which node is visited next.
- The shared ans vector keeps the values selected for the left view.
- Returning from a recursive call does not remove values from ans.
- The algorithm does not need to undo any vector changes because each depth
  is recorded only once.

Backtracking simply returns execution to the parent call so it can continue
with the other child.

================================================================================
10. CORRECTNESS REASONING
================================================================================
We want to prove that ans contains the leftmost node at every depth.

1. DFS processes a node before its children, and explores the left subtree
   before the right subtree.
2. Therefore, among nodes at any fixed depth, the leftmost existing node is
   encountered before nodes to its right.
3. The first time a depth is reached, ans.size() equals that depth, so the
   node's value is appended.
4. Later nodes at that depth are encountered after the answer already has a
   value for that depth. The condition is false, so they are not appended.
5. Consequently, exactly the leftmost node at each depth is recorded.

Thus, the algorithm returns the left view in top-to-bottom order.

================================================================================
11. EDGE CASES
================================================================================
A. Empty tree

    root = nullptr

The helper returns immediately. The answer is an empty vector: [].

B. Single-node tree

        1

The root is the only node at level 0. Answer: [1].

C. Only left children

        1
       /
      2
     /
    3

Each level has only one node. Answer: [1, 2, 3].

D. Only right children

    1
     \
      2
       \
        3

Each level has only one node. These nodes are still visible from the left
because they are the only nodes at their respective depths.
Answer: [1, 2, 3].

E. Root has only a right child, and that child has a left child

      1
       \
        2
       /
      3

Answer: [1, 2, 3]. At every depth, there is only one node.

F. Several nodes at one level

          1
         / \
        2   3
       / \ / \
      4  5 6  7

Answer: [1, 2, 4]. Nodes 5, 6, and 7 are not selected because a leftmost
node was already recorded at each corresponding depth.

G. Repeated data values

The algorithm still works if different nodes have equal data values. It uses
depth and traversal order, not value uniqueness, to select visible nodes.

H. Calling leftView more than once on the same Solution object

In the submitted code, `ans` is a member variable and is not cleared at the
start of leftView(). Reusing the same object can return old results mixed with
new ones. A local vector avoids this state-leak issue.

================================================================================
12. COMMON MISTAKES TO AVOID
================================================================================
1. Visiting the right child before the left child
   With the same first-node-per-level logic, that produces the right view.

2. Adding every node
   The condition must prevent later nodes at the same depth from being added.

3. Using the wrong level for the root
   This implementation starts the root at level 0. The ans.size() == level
   condition relies on that convention.

4. Confusing level with the number of nodes visited
   level is the depth of the current node, not a traversal counter.

5. Passing ans by value
   If ans were passed by value, recursive calls would update copies rather
   than one shared answer vector. The reference `vector<int>& ans` is needed.

6. Returning a vector from the helper without a reason
   The helper's job is to update the shared answer. A void return type is
   appropriate here.

7. Forgetting the nullptr base case
   Every leaf has nullptr child pointers, and the recursive calls must stop.

8. Assuming the left view is just the root-to-leftmost-leaf path
   The visible node at each level can be reached through a right edge if no
   more-left node exists at that level.

9. Forgetting to clear a member answer vector
   Reusing the same object can leave previous answers in the vector. Prefer
   a local vector or explicitly clear the member vector.

10. Using `ans.size() <= level` without understanding why
    The current logic is designed around one value per level, with root level
    0 and DFS visiting the first occurrence of every level in order.

================================================================================
13. TIME AND SPACE COMPLEXITY
================================================================================
Let n be the number of nodes and h the height of the tree.

Time complexity: O(n)
Every node is visited once, and each visit performs constant-time work aside
from the recursive calls.

Auxiliary space:
- O(h) for the recursive call stack.
- The result vector stores one value per level, using O(h) additional output
  space in the worst case.

If discussing auxiliary space excluding the returned output, recursion uses
O(h). If counting the result vector too, total additional storage is O(h).

For a balanced tree, h = O(log n).
For a skewed tree, h = O(n).

================================================================================
14. ALTERNATIVE: BFS / LEVEL-ORDER SOLUTION
================================================================================
The left view can also be found with Breadth-First Search (BFS) using a queue.

Process one level at a time:
1. Record the queue size at the start of a level.
2. Process exactly that many nodes.
3. The first node processed at that level is the leftmost node.
4. Add its value to the answer.
5. Enqueue children from left to right.

Both BFS and DFS solutions run in O(n) time.

DFS approach in this file:
- Uses recursion.
- Visits left first.
- Records the first node at each depth.
- Uses O(h) recursion stack space.

BFS approach:
- Uses a queue.
- Processes nodes level by level.
- Uses O(w) queue space, where w is the maximum width of the tree.

Your submitted DFS solution is concise and correct once the answer storage is
managed safely across calls.

================================================================================
15. COMPARISON: LEFT VIEW VS RIGHT VIEW
================================================================================
Left view:
    Visit left before right.
    Record the first node encountered at each depth.

Right view:
    Visit right before left.
    Record the first node encountered at each depth.

The core idea is identical. Only the traversal order changes.

================================================================================
16. SELF-REVISION QUESTIONS
================================================================================
Try answering these without looking at the explanation:

1. What does the left view represent?
2. Why is the root assigned level 0?
3. What does ans.size() represent in this algorithm?
4. Why does ans.size() == level identify the first node at a level?
5. Why must the left recursive call come before the right recursive call?
6. Why is ans passed by reference?
7. Why does a node reached through a right pointer sometimes belong to the
   left view?
8. What would happen if the recursive calls were reversed?
9. What is the time complexity?
10. Why can a member answer vector cause trouble if leftView is called twice?
11. What is the output for an empty tree?
12. How does the BFS solution differ from the DFS solution?

================================================================================
17. QUICK REVISION SUMMARY
================================================================================
- The left view contains the leftmost existing node at each depth.
- Root depth is 0.
- The helper stops at nullptr.
- `ans.size() == level` means no node has been recorded for this depth yet.
- Visit left before right so the first node at each depth is the leftmost.
- Pass the vector by reference so recursive calls share the same result.
- Time complexity: O(n).
- Recursion stack: O(h).
- Use a local answer vector to avoid stale results across repeated calls.

================================================================================
18. CLEAN GFG-STYLE IMPLEMENTATION
================================================================================
This version preserves your recursive algorithm and variable naming where
practical, but makes the answer vector local so repeated calls are safe.

If you need to match the exact submitted class for a record of what you wrote,
see the original code above in this document's discussion. This is the
recommended version for a reusable implementation.

================================================================================
*/

class Solution {
  private:
    void func(Node* root, int level, vector<int>& ans) {
        // No node exists at this position, so this branch is finished.
        if (root == nullptr) {
            return;
        }

        // The first node reached at this level belongs to the left view.
        if (ans.size() == level) {
            ans.push_back(root->data);
        }

        // Visit left first so leftmost nodes are encountered first per level.
        func(root->left, level + 1, ans);

        // Visit right after the entire left subtree has been explored.
        func(root->right, level + 1, ans);
    }

  public:
    vector<int> leftView(Node* root) {
        // Local state ensures every call starts with an empty result.
        vector<int> ans;

        // Root starts at level 0.
        func(root, 0, ans);

        return ans;
    }
};

/*
================================================================================
END OF REVISION NOTES
================================================================================
*/
