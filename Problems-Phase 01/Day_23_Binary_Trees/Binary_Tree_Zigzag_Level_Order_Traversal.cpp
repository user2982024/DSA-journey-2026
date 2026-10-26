
/*
===============================================================================
                    BINARY TREE ZIGZAG LEVEL ORDER TRAVERSAL
===============================================================================

Platform          : LeetCode
Problem Number    : 103
Topic             : Binary Trees
Category          : BFS, Level Order Traversal, Queue, Vectors
Language          : C++
Approach          : BFS + Level-by-Level Processing + Reversing Alternate Levels
Status            : Accepted (as reported)

===============================================================================
1. PROBLEM STATEMENT
===============================================================================

Given the root of a binary tree, return its zigzag level order traversal.

Zigzag level order traversal means:

    Level 0: Traverse from LEFT to RIGHT.
    Level 1: Traverse from RIGHT to LEFT.
    Level 2: Traverse from LEFT to RIGHT.
    Level 3: Traverse from RIGHT to LEFT.

Continue alternating the direction at every level.

Example tree:

                 3
               /   \
              9     20
                   /  \
                  15   7

Ordinary level order traversal:

    [
        [3],
        [9, 20],
        [15, 7]
    ]

Zigzag level order traversal:

    [
        [3],
        [20, 9],
        [15, 7]
    ]

Explanation:

    Level 0:
        Only node 3 exists.
        Direction: Left to right.
        Result: [3]

    Level 1:
        Nodes are 9 and 20.
        Zigzag requires right to left.
        Result: [20, 9]

    Level 2:
        Nodes are 15 and 7.
        Zigzag requires left to right.
        Result: [15, 7]

Final answer:

    [[3], [20, 9], [15, 7]]

IMPORTANT:

We must preserve the order of levels. Only the order of nodes within
alternate levels changes.

===============================================================================
2. UNDERSTANDING THE TWO-DIMENSIONAL VECTOR
===============================================================================

Your function returns:

    vector<vector<int>>

Why do we need a vector of vectors?

The answer contains multiple levels, and each level contains multiple
node values.

For example:

    [
        [3],
        [20, 9],
        [15, 7]
    ]

This is a two-dimensional vector.

The outer vector:

    ans

Stores one vector per level.

The inner vector:

    v

Stores the values of nodes belonging to the current level.

During the traversal, we repeatedly build one inner vector and then
append it to the outer vector:

    ans.push_back(v);

For example, after processing the first level:

    ans = [[3]]

After processing the second level:

    ans = [[3], [20, 9]]

After processing the third level:

    ans = [[3], [20, 9], [15, 7]]

===============================================================================
3. WHY DO WE USE BFS?
===============================================================================

BFS stands for Breadth-First Search.

BFS processes a tree level by level.

Consider:

                 1
               /   \
              2     3
             / \   / \
            4   5 6   7

BFS visits nodes in this order:

    1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7

The levels are:

    Level 0: [1]
    Level 1: [2, 3]
    Level 2: [4, 5, 6, 7]

Zigzag traversal uses the same level-by-level processing, but reverses
the collected values at every other level.

That makes BFS a natural choice.

We use:

    queue<TreeNode*> q;

A queue follows FIFO:

    FIFO = First In, First Out

The node added earliest is processed first.

When processing a node, we add its left child and then its right child.

This naturally collects each level from left to right before we apply
the zigzag reversal.

===============================================================================
4. YOUR COMPLETE ACCEPTED IMPLEMENTATION
===============================================================================

LeetCode provides the TreeNode definition.

Your implementation:

*/

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

/*
LeetCode provides this definition:

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};
*/

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {

        // Stores the final result.
        // Each inner vector represents one tree level.
        vector<vector<int>> ans;

        // BFS queue stores pointers to tree nodes.
        queue<TreeNode*> q;

        // If the tree is empty, there are no levels to return.
        if (root == nullptr) {
            return {};
        }

        // Start BFS from the root.
        q.push(root);

        // false means left-to-right.
        // true means right-to-left.
        bool direction = false;

        // Continue while there are nodes waiting to be processed.
        while (!q.empty()) {

            // Stores values belonging to the current level.
            vector<int> v;

            // IMPORTANT:
            // Capture the number of nodes currently in the queue.
            // These are exactly the nodes belonging to this level.
            int levelSize = q.size();

            // Counts how many nodes from this level we have processed.
            int i = 0;

            // Process only the nodes that belonged to this level
            // when levelSize was captured.
            while (i < levelSize) {

                // Get the front node.
                TreeNode* node = q.front();

                // Collect its value in ordinary left-to-right order.
                v.push_back(node->val);

                // Remove the processed node.
                q.pop();

                // Increase the number of processed nodes.
                i++;

                // Add the left child for processing in a future level.
                if (node->left != nullptr) {
                    q.push(node->left);
                }

                // Add the right child for processing in a future level.
                if (node->right != nullptr) {
                    q.push(node->right);
                }
            }

            // If this level must be traversed right-to-left,
            // reverse only this level's vector.
            if (direction == true) {
                reverse(v.begin(), v.end());
            }

            // Append the completed level to the final answer.
            ans.push_back(v);

            // Alternate the direction for the next level.
            direction = !direction;
        }

        // Return all levels in zigzag order.
        return ans;
    }
};

/*
===============================================================================
5. UNDERSTANDING THE direction VARIABLE
===============================================================================

Your code:

    bool direction = false;

And later:

    if (direction == true) {
        reverse(v.begin(), v.end());
    }

    direction = !direction;

The direction variable tells us whether the current level needs reversing.

We use these meanings:

    false -> Do not reverse the level.
    true  -> Reverse the level.

Initially:

    direction = false;

Therefore, the root level is not reversed.

After processing that level:

    direction = !direction;

The ! operator means logical NOT.

Examples:

    !false = true
    !true  = false

So the variable alternates:

    false -> true -> false -> true -> false -> ...

This produces the required zigzag pattern.

Direction table:

    Level       direction       Action
    ------------------------------------------------
      0          false          Keep normal order
      1          true           Reverse
      2          false          Keep normal order
      3          true           Reverse
      4          false          Keep normal order

An equally valid implementation could use a variable named leftToRight,
initialized to true. Your direction variable uses the opposite naming
convention, but the logic is correct.

===============================================================================
6. THE MOST IMPORTANT CONCEPT: levelSize = q.size()
===============================================================================

Your code:

    int levelSize = q.size();

This line is critical.

Why?

Because while processing the current level, we also add children to
the queue. Those children belong to the NEXT level.

We must not accidentally process those children as if they belonged to
the current level.

Consider this tree:

                 1
               /   \
              2     3
             / \
            4   5

Initially:

    Queue = [1]

At the beginning of Level 0:

    levelSize = 1

We process exactly one node: 1.

While processing node 1, we add nodes 2 and 3.

The queue becomes:

    Queue = [2, 3]

However, levelSize remains 1 for the current inner loop.

Therefore, nodes 2 and 3 are NOT processed in the same iteration of
the inner loop.

After finishing Level 0, the outer loop starts again:

    levelSize = q.size() = 2

Now we process exactly nodes 2 and 3.

This is how the code maintains the boundaries between levels.

IMPORTANT RULE:

Capture q.size() ONCE at the beginning of each level.

Do not recalculate the level boundary after adding children.

If we used the changing queue size as our stopping condition, we could
accidentally mix nodes from different levels.

===============================================================================
7. COMPLETE DRY RUN
===============================================================================

Consider the example:

                 3
               /   \
              9     20
                   /  \
                  15   7

Initially:

    ans       = []
    q         = [3]
    direction = false

---------------------------------------
LEVEL 0
---------------------------------------

At the beginning:

    levelSize = 1
    v = []

Inner loop:

    i = 0

Since 0 < 1, process node 3.

    node = 3
    v = [3]

Node 3 has two children:

    Left child 9
    Right child 20

Enqueue both children:

    q = [9, 20]

Increment i:

    i = 1

Now i < levelSize is false because 1 < 1 is false.

The inner loop ends.

Current level:

    v = [3]

direction = false

Do not reverse.

Append to answer:

    ans = [[3]]

Toggle direction:

    direction = !false
    direction = true

---------------------------------------
LEVEL 1
---------------------------------------

At the beginning:

    q = [9, 20]
    levelSize = 2
    v = []
    direction = true

Process node 9:

    v = [9]

Node 9 has no children.

Queue after removing 9:

    q = [20]

Increment i:

    i = 1

Since 1 < 2, continue.

Process node 20:

    v = [9, 20]

Node 20 has two children:

    Left child 15
    Right child 7

Enqueue both:

    q = [15, 7]

Increment i:

    i = 2

Now 2 < 2 is false, so Level 1 is complete.

Collected level:

    v = [9, 20]

But direction is true.

Therefore:

    reverse(v.begin(), v.end());

The vector becomes:

    v = [20, 9]

Append to answer:

    ans = [[3], [20, 9]]

Toggle direction:

    direction = !true
    direction = false

---------------------------------------
LEVEL 2
---------------------------------------

At the beginning:

    q = [15, 7]
    levelSize = 2
    v = []
    direction = false

Process node 15:

    v = [15]

Node 15 has no children.

Process node 7:

    v = [15, 7]

Node 7 has no children.

The queue becomes empty.

Collected level:

    v = [15, 7]

direction is false, so we do not reverse.

Append to answer:

    ans = [[3], [20, 9], [15, 7]]

Toggle direction:

    direction = true

The outer loop ends because the queue is empty.

Final answer:

    [[3], [20, 9], [15, 7]]

===============================================================================
8. WHY DO WE REVERSE ONLY v?
===============================================================================

Your code:

    reverse(v.begin(), v.end());

Here, v contains only the values from the current level.

For example:

    v = [9, 20]

Reversing it gives:

    v = [20, 9]

We do NOT reverse ans because ans contains all previously completed levels.

If we reversed ans, we would change the order of the levels themselves.

That would violate the problem's requirement to return levels from top
to bottom.

The correct strategy is:

    1. Collect one level.
    2. Reverse that level if required.
    3. Append it to ans.
    4. Toggle the direction.
    5. Process the next level.

This preserves the order of levels while alternating the order of values
inside each level.

===============================================================================
9. WHY DO WE INSERT LEFT CHILD BEFORE RIGHT CHILD?
===============================================================================

Your code:

    if (node->left != nullptr) {
        q.push(node->left);
    }

    if (node->right != nullptr) {
        q.push(node->right);
    }

This makes BFS collect each level in its normal left-to-right order.

For example:

                 1
               /   \
              2     3

The queue processes:

    1

Then it enqueues:

    2, 3

The next level vector becomes:

    [2, 3]

When direction is true, we reverse it:

    [3, 2]

This is simple and reliable.

An alternative is to arrange insertion and collection differently to
avoid reversing, but that requires more complicated indexing or
direction-aware insertion logic. Your approach is easy to understand
and perfectly appropriate.

===============================================================================
10. WHY CHECK root == nullptr?
===============================================================================

Your code:

    if (root == nullptr) {
        return {};
    }

A nullptr root means the tree has no nodes.

There is nothing to process, so we return an empty two-dimensional vector.

Expected result:

    []

This check is important because it prevents us from pushing an invalid
node pointer into the queue.

The early return also keeps the rest of the implementation simple.

===============================================================================
11. TIME COMPLEXITY
===============================================================================

Let n be the number of nodes in the tree.

A) BFS traversal:

    Every node is inserted into the queue at most once and removed once.

    Time: O(n)

B) Collecting values:

    Each node's value is added to exactly one level vector.

    Total: O(n)

C) Reversing alternate levels:

    Reversing a level with k nodes takes O(k) time.

    Across all levels, the sum of their sizes is n.

    Therefore, the total time spent reversing is at most O(n).

D) Appending levels to ans:

    Each level vector is appended once.

    The total number of values copied into the answer is n.

    Total: O(n)

TOTAL TIME COMPLEXITY:

    O(n) + O(n) + O(n) + O(n)

    = O(n)

The solution is linear because each node is processed a constant number
of times, and the total amount of reversing is bounded by the number
of nodes.

===============================================================================
12. SPACE COMPLEXITY
===============================================================================

A) Queue:

    The queue can hold up to O(n) nodes in the worst case.

    For a broad tree, a single level may contain many nodes.

B) Current-level vector:

    v can hold up to O(n) node values.

C) Answer:

    ans stores all n values, grouped into levels.

Auxiliary space excluding the returned answer:

    O(n)

Total space including the answer:

    O(n)

The solution does not use recursive calls, so it does not need a
recursive call stack.

===============================================================================
13. EDGE CASES
===============================================================================

CASE 1: EMPTY TREE

    root = nullptr

Output:

    []

Reason:

    No nodes exist.

CASE 2: SINGLE NODE

        1

Output:

    [[1]]

Reason:

    Only one level exists. No reversal changes it.

CASE 3: LEFT-SKEWED TREE

        1
       /
      2
     /
    3

Levels:

    Level 0: [1]
    Level 1: [2]
    Level 2: [3]

Zigzag result:

    [[1], [2], [3]]

Every level contains only one node, so reversing does not change anything.

CASE 4: RIGHT-SKEWED TREE

    1
     \
      2
       \
        3

Result:

    [[1], [2], [3]]

Again, every level has only one node.

CASE 5: COMPLETE BINARY TREE

                 1
               /   \
              2     3
             / \   / \
            4   5 6   7

Ordinary levels:

    [1]
    [2, 3]
    [4, 5, 6, 7]

Zigzag result:

    [[1], [3, 2], [4, 5, 6, 7]]

CASE 6: ROOT WITH ONLY ONE CHILD

        1
         \
          2

Result:

    [[1], [2]]

The algorithm handles missing children by simply not enqueueing them.

===============================================================================
14. COMMON MISTAKES AND HOW TO AVOID THEM
===============================================================================

MISTAKE 1: FORGETTING TO CAPTURE levelSize

Incorrect idea:

    Process nodes until the queue is empty inside the current level.

Why it fails:

    Children added during the current level could be processed immediately,
    mixing different levels in the same vector.

Correct:

    int levelSize = q.size();

    Process exactly levelSize nodes.

MISTAKE 2: REVERSING THE ENTIRE ANSWER

Incorrect:

    reverse(ans.begin(), ans.end());

Why it fails:

    It reverses the order of the levels, rather than the order of nodes
    within a level.

Correct:

    reverse(v.begin(), v.end());

MISTAKE 3: TOGGLING direction TOO EARLY

If direction is changed before deciding whether to reverse the current
level, the first level could accidentally be reversed or the pattern
could shift by one level.

Correct order:

    1. Collect the current level.
    2. Reverse if direction is true.
    3. Append the level.
    4. Toggle direction.

MISTAKE 4: USING THE WRONG INITIAL DIRECTION

Your convention:

    false -> no reversal
    true  -> reversal

Therefore, initialize:

    bool direction = false;

This makes the root level left-to-right.

MISTAKE 5: FORGETTING TO TOGGLE direction

If direction never changes, every level follows the same ordering.

Correct:

    direction = !direction;

MISTAKE 6: NOT CHECKING FOR nullptr CHILDREN

Never push a missing child into the queue.

Correct:

    if (node->left != nullptr) {
        q.push(node->left);
    }

    if (node->right != nullptr) {
        q.push(node->right);
    }

MISTAKE 7: THINKING THE QUEUE ITSELF PERFORMS ZIGZAG

The queue still performs ordinary BFS.

The zigzag behavior is created by reversing the current level vector
after its values have been collected.

This separation is one of the strengths of your solution.

===============================================================================
15. INTERVIEW QUESTIONS AND ANSWERS
===============================================================================

Q1. What is zigzag level order traversal?

Answer:
It visits a binary tree level by level while alternating the direction
of traversal at each level.

Q2. Which algorithm did we use?

Answer:
Breadth-First Search (BFS), implemented with a queue.

Q3. Why is BFS suitable?

Answer:
BFS naturally groups nodes by depth, and zigzag traversal requires
processing one complete level at a time.

Q4. What does levelSize represent?

Answer:
The number of nodes belonging to the current level when that level
begins processing.

Q5. Why capture q.size() before the inner loop?

Answer:
Because processing current-level nodes adds children to the queue.
Capturing the size prevents those newly added children from being
processed as part of the current level.

Q6. What does direction mean in our implementation?

Answer:
false means keep the current level in its collected order.
true means reverse the current level.

Q7. Why initialize direction to false?

Answer:
The first level must be traversed from left to right, so it should
not be reversed.

Q8. What does !direction do?

Answer:
It toggles the Boolean value: false becomes true and true becomes false.

Q9. Why do we use reverse(v.begin(), v.end())?

Answer:
It reverses the values of the current level when that level requires
right-to-left ordering.

Q10. Why not reverse ans?

Answer:
ans stores all levels. Reversing it would change their top-to-bottom
order, which the problem requires us to preserve.

Q11. What is the time complexity?

Answer:
O(n), because each node is processed a constant number of times, and
the total cost of reversing all selected levels is also O(n).

Q12. What is the auxiliary space complexity?

Answer:
O(n), due to the queue and temporary level vector in the worst case.
The returned answer also requires O(n) storage.

Q13. Can we solve this using DFS?

Answer:
Yes. We can use recursion while tracking the current depth and append
values to the appropriate level. We would then need to place values
at the correct side of each level vector according to the depth.
BFS is generally more straightforward for this problem.

Q14. Does the queue process odd levels in reverse order?

Answer:
No. The queue always processes nodes according to ordinary BFS order.
We reverse the collected vector afterward.

Q15. Why do we enqueue left before right?

Answer:
It gives us normal left-to-right level vectors, making alternate-level
reversal simple.

===============================================================================
16. ALTERNATIVE APPROACH: INDEXING INSTEAD OF REVERSING
===============================================================================

Your current approach is:

    Collect the level normally.
    Reverse it when needed.

Another approach is to place each node directly into its final position.

Suppose:

    levelSize = 4

For a normal left-to-right level, use the current index i:

    index = i

For a reversed right-to-left level, use:

    index = levelSize - 1 - i

Example:

    Collected BFS order: [2, 3, 4, 5]
    levelSize: 4

    i = 0 -> index = 3
    i = 1 -> index = 2
    i = 2 -> index = 1
    i = 3 -> index = 0

The resulting vector becomes:

    [5, 4, 3, 2]

This avoids calling reverse(), but requires more careful index management.

Your original approach is easier to read and is fully suitable for
interviews.

===============================================================================
17. IMPORTANT COMPARISON WITH OUR RECENT TREE PROBLEMS
===============================================================================

A) TOP VIEW OF BINARY TREE

Main idea:

    BFS + horizontal distance + ordered map.

We preserve the first node encountered at each horizontal distance.

B) BOTTOM VIEW OF BINARY TREE

Main idea:

    BFS + horizontal distance + ordered map.

We overwrite the map entry at each horizontal distance as nodes are visited.

C) ZIGZAG LEVEL ORDER TRAVERSAL

Main idea:

    BFS + fixed level size + alternating direction.

We collect each level into a vector and reverse alternate levels.

Common concept:

All three problems use BFS to process nodes in a controlled order.

Different goal:

    Top View:
        Select one node per horizontal distance based on the top-view rule.

    Bottom View:
        Select one node per horizontal distance based on the bottom-view rule.

    Zigzag:
        Return every node, grouped by level, with alternating level order.

===============================================================================
18. FINAL REVISION CHECKLIST
===============================================================================

Before an interview, make sure you can explain these points without
looking at the code:

[ ] Why BFS is used.
[ ] Why we need a queue.
[ ] Why levelSize must be captured before processing a level.
[ ] What each variable represents.
[ ] Why direction starts as false.
[ ] How !direction alternates the direction.
[ ] Why only the current-level vector is reversed.
[ ] Why left and right children are enqueued in that order.
[ ] Why the algorithm handles an empty tree.
[ ] Why the time complexity is O(n).
[ ] Why the auxiliary space complexity is O(n).
[ ] How this differs from ordinary level order traversal.
[ ] How this differs from Top View and Bottom View.

===============================================================================
19. GITHUB ORGANIZATION
===============================================================================

Suggested filename:

    Binary_Tree_Zigzag_Level_Order_Traversal.cpp

Suggested folder:

    DSA-journey-2026/
        Problems-Phase-01/
            Trees/
                Traversals/
                    Binary_Tree_Zigzag_Level_Order_Traversal.cpp

Suggested commit message:

    Add detailed Zigzag Level Order Traversal solution and revision notes

Suggested README entry:

    Problem: Binary Tree Zigzag Level Order Traversal
    Platform: LeetCode 103
    Approach: BFS + Level Size + Alternate-Level Reversal
    Time Complexity: O(n)
    Auxiliary Space: O(n)
    Status: Accepted

===============================================================================
                         END OF REVISION FILE
===============================================================================
*/
