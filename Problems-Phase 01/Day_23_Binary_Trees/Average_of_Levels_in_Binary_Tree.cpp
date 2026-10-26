
/*
===============================================================================
             LEETCODE 637: AVERAGE OF LEVELS IN BINARY TREE
===============================================================================

Platform          : LeetCode
Problem Number    : 637
Topic             : Binary Trees
Difficulty        : Easy
Language          : C++
Approach          : Breadth-First Search (BFS)
                    Level Order Traversal
                    Level Sum and Level Count
Status            : Accepted
Reported Runtime  : Beating 100% on LeetCode (at the time of submission)

===============================================================================
1. PROBLEM STATEMENT
===============================================================================

Given the root of a binary tree, return an array containing the average
value of the nodes on each level in the tree.

The average of a level is calculated by:

                Sum of all node values at that level
    Average =   -------------------------------------
                    Number of nodes at that level

The result must contain one average for each level, ordered from the
root level to the deepest level.

The answer must contain floating-point values.

IMPORTANT:

We must calculate the average of EACH level separately.

We must NOT calculate the average of all nodes in the entire tree.

===============================================================================
2. EXAMPLE
===============================================================================

Consider the following binary tree:

                 3
               /   \
              9     20
                   /  \
                  15   7

The levels are:

    Level 0: [3]

    Level 1: [9, 20]

    Level 2: [15, 7]

Now calculate the average of each level.

LEVEL 0:

    Sum         = 3
    Node count  = 1

    Average = 3 / 1 = 3.0

LEVEL 1:

    Sum         = 9 + 20 = 29
    Node count  = 2

    Average = 29 / 2 = 14.5

LEVEL 2:

    Sum         = 15 + 7 = 22
    Node count  = 2

    Average = 22 / 2 = 11.0

EXPECTED OUTPUT:

    [3.00000, 14.50000, 11.00000]

LeetCode may display floating-point numbers with a particular precision.
The important point is that the returned values represent the correct
averages.

===============================================================================
3. UNDERSTANDING THE REQUIRED RETURN TYPE
===============================================================================

The function signature is:

    vector<double> averageOfLevels(TreeNode* root)

Let's understand the return type.

A) vector

A vector stores a sequence of elements.

For example:

    vector<int> values = {3, 9, 20};

B) double

A double stores floating-point numbers.

Examples:

    3.0
    14.5
    11.0
    7.25

C) vector<double>

Our result contains one floating-point average per level.

Therefore, we need:

    vector<double> ans;

After processing each level, we append its average:

    ans.push_back(val);

For the example tree, the vector contains:

    ans = {3.0, 14.5, 11.0};

WHY NOT vector<int>?

Because averages do not have to be whole numbers.

For example:

    29 / 2 = 14.5

An integer result cannot represent 14.5 accurately.

===============================================================================
4. WHY DID WE CHOOSE BFS?
===============================================================================

BFS stands for Breadth-First Search.

BFS visits a binary tree level by level.

For the example tree:

                 3
               /   \
              9     20
                   /  \
                  15   7

BFS processes the levels in this order:

    Level 0: 3

    Level 1: 9, 20

    Level 2: 15, 7

This matches our requirement perfectly because we need a separate
average for every level.

We can calculate the sum while processing a level and then divide
by the number of nodes at that level.

The key idea is:

    1. Identify the current level.
    2. Process all nodes belonging to that level.
    3. Calculate the level's sum.
    4. Divide by the level's node count.
    5. Store the average.
    6. Move to the next level.

We do not need to collect every node value into a separate vector.

We only need the running sum and the number of nodes being processed.

===============================================================================
5. DATA STRUCTURES AND VARIABLES
===============================================================================

Our implementation uses:

    vector<double> ans;
    queue<TreeNode*> q;

And the following variables inside the loops:

    int levelSize;
    int i;
    double levelSum;
    double levelCount;
    double val;

Let's understand every one of them.

---------------------------------------
A) ans
---------------------------------------

    vector<double> ans;

Purpose:

Stores the average of every level.

After processing each level, we append its average to this vector.

Example:

    After Level 0:

        ans = {3.0}

    After Level 1:

        ans = {3.0, 14.5}

    After Level 2:

        ans = {3.0, 14.5, 11.0}

---------------------------------------
B) q
---------------------------------------

    queue<TreeNode*> q;

Purpose:

Stores pointers to tree nodes waiting to be processed.

A queue follows FIFO:

    FIFO = First In, First Out

The first node inserted into the queue is the first one removed.

We use a queue because BFS processes nodes in level order.

---------------------------------------
C) levelSize
---------------------------------------

    int levelSize = q.size();

Purpose:

Stores the number of nodes in the current level.

This variable is one of the most important parts of our BFS implementation.

We capture the queue size at the beginning of each level so that we
know exactly how many nodes belong to that level.

Even though children are added to the queue during processing,
levelSize does not change.

This prevents us from mixing nodes from different levels.

---------------------------------------
D) i
---------------------------------------

    int i = 0;

Purpose:

Counts how many nodes from the current level have been processed.

Our inner loop continues while:

    i < levelSize

After processing each node:

    i++;

Once i becomes equal to levelSize, the current level is complete.

---------------------------------------
E) levelSum
---------------------------------------

    double levelSum = 0;

Purpose:

Stores the sum of node values at the current level.

For example, if the current level contains:

    [9, 20]

Then:

    levelSum = 9 + 20 = 29

IMPORTANT:

We initialize levelSum to zero INSIDE the outer loop.

That ensures every new level starts with a fresh sum.

---------------------------------------
F) levelCount
---------------------------------------

    double levelCount = 0;

Purpose:

Counts the nodes processed at the current level.

For example:

    Level = [9, 20]

    After processing 9:

        levelCount = 1

    After processing 20:

        levelCount = 2

The count is reset for every level.

NOTE:

A count is normally represented using int because it is a whole number.

Your original implementation uses double, which works correctly here.
We will preserve your original code and discuss this improvement later.

---------------------------------------
G) val
---------------------------------------

    double val = levelSum / levelCount;

Purpose:

Stores the calculated average for the current level.

We append this average to ans:

    ans.push_back(val);

===============================================================================
6. COMPLETE ACCEPTED IMPLEMENTATION
===============================================================================

LeetCode provides the TreeNode definition.

The following implementation preserves your original approach.

*/

#include <vector>
#include <queue>

using namespace std;

/*
LeetCode supplies the following TreeNode definition:

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
    vector<double> averageOfLevels(TreeNode* root) {

        // An empty tree contains no levels.
        if (root == nullptr) {
            return {};
        }

        // Stores the average of each level.
        vector<double> ans;

        // Queue for breadth-first traversal.
        queue<TreeNode*> q;

        // Begin BFS with the root node.
        q.push(root);

        // Continue while there are nodes waiting to be processed.
        while (!q.empty()) {

            // Capture the number of nodes at the current level.
            int levelSize = q.size();

            // Counts processed nodes in this level.
            int i = 0;

            // Sum of node values at the current level.
            double levelSum = 0;

            // Number of nodes processed at the current level.
            double levelCount = 0;

            // Process exactly the nodes belonging to this level.
            while (i < levelSize) {

                // Get the node at the front of the queue.
                TreeNode* node = q.front();

                // Add its value to the current level's sum.
                levelSum += node->val;

                // Count this node.
                levelCount++;

                // Remove the processed node from the queue.
                q.pop();

                // Add the left child for processing in a future level.
                if (node->left != nullptr) {
                    q.push(node->left);
                }

                // Add the right child for processing in a future level.
                if (node->right != nullptr) {
                    q.push(node->right);
                }

                // One node from the current level has been processed.
                i++;
            }

            // Calculate the average of the completed level.
            double val = levelSum / levelCount;

            // Store the average in the answer vector.
            ans.push_back(val);
        }

        // Return the averages from top level to bottom level.
        return ans;
    }
};

/*
===============================================================================
7. COMPLETE DRY RUN
===============================================================================

Tree:

                 3
               /   \
              9     20
                   /  \
                  15   7

Initially:

    ans = {}

    q = [3]

We now execute the outer while loop.

===============================================================================
ITERATION 1: PROCESS LEVEL 0
===============================================================================

At the beginning of the outer loop:

    q = [3]

Capture the level size:

    levelSize = q.size()
    levelSize = 1

Initialize the variables:

    i = 0
    levelSum = 0
    levelCount = 0

The inner loop condition is:

    i < levelSize

    0 < 1

This is true, so process node 3.

---------------------------------------
PROCESS NODE 3
---------------------------------------

The front node is:

    node = 3

Add its value:

    levelSum = 0 + 3
    levelSum = 3

Increment the count:

    levelCount = 1

Remove node 3:

    q = []

Node 3 has two children.

Enqueue the left child:

    q = [9]

Enqueue the right child:

    q = [9, 20]

Increment i:

    i = 1

Check the inner loop condition:

    i < levelSize

    1 < 1

This is false.

The current level is complete.

IMPORTANT:

Although nodes 9 and 20 are now in the queue, we do not process them
in this inner loop because levelSize was captured as 1.

---------------------------------------
CALCULATE LEVEL 0 AVERAGE
---------------------------------------

Current values:

    levelSum = 3
    levelCount = 1

Calculate:

    val = levelSum / levelCount

    val = 3 / 1

    val = 3.0

Append the average:

    ans = {3.0}

The outer loop starts again.

===============================================================================
ITERATION 2: PROCESS LEVEL 1
===============================================================================

At the beginning:

    q = [9, 20]

Capture the level size:

    levelSize = 2

Initialize:

    i = 0
    levelSum = 0
    levelCount = 0

---------------------------------------
PROCESS NODE 9
---------------------------------------

The front node is:

    node = 9

Update the sum:

    levelSum = 0 + 9
    levelSum = 9

Update the count:

    levelCount = 1

Remove node 9:

    q = [20]

Node 9 has no children.

Increment i:

    i = 1

Check:

    1 < 2

True. Continue processing this level.

---------------------------------------
PROCESS NODE 20
---------------------------------------

The front node is:

    node = 20

Update the sum:

    levelSum = 9 + 20
    levelSum = 29

Update the count:

    levelCount = 2

Remove node 20:

    q = []

Node 20 has two children.

Enqueue node 15:

    q = [15]

Enqueue node 7:

    q = [15, 7]

Increment i:

    i = 2

Check:

    2 < 2

False.

Level 1 is complete.

---------------------------------------
CALCULATE LEVEL 1 AVERAGE
---------------------------------------

Current values:

    levelSum = 29
    levelCount = 2

Calculate:

    val = 29 / 2

    val = 14.5

Append:

    ans = {3.0, 14.5}

The outer loop starts again.

===============================================================================
ITERATION 3: PROCESS LEVEL 2
===============================================================================

At the beginning:

    q = [15, 7]

Capture:

    levelSize = 2

Initialize:

    i = 0
    levelSum = 0
    levelCount = 0

---------------------------------------
PROCESS NODE 15
---------------------------------------

    levelSum = 0 + 15
    levelSum = 15

    levelCount = 1

Remove node 15.

The queue becomes:

    q = [7]

Node 15 has no children.

Increment i:

    i = 1

Since 1 < 2, continue.

---------------------------------------
PROCESS NODE 7
---------------------------------------

    levelSum = 15 + 7
    levelSum = 22

    levelCount = 2

Remove node 7.

The queue becomes empty:

    q = []

Node 7 has no children.

Increment i:

    i = 2

Since 2 < 2 is false, Level 2 is complete.

---------------------------------------
CALCULATE LEVEL 2 AVERAGE
---------------------------------------

    val = levelSum / levelCount

    val = 22 / 2

    val = 11.0

Append:

    ans = {3.0, 14.5, 11.0}

The outer loop checks:

    q.empty() == true

The traversal ends.

FINAL ANSWER:

    [3.0, 14.5, 11.0]

===============================================================================
8. WHY IS levelSize SO IMPORTANT?
===============================================================================

Consider:

                 1
               /   \
              2     3
             / \
            4   5

Initially:

    q = [1]

At the beginning of Level 0:

    levelSize = 1

We process node 1 and enqueue nodes 2 and 3.

Now:

    q = [2, 3]

However, the current level's size remains:

    levelSize = 1

The inner loop stops after processing node 1.

The outer loop then begins Level 1:

    levelSize = 2

Now nodes 2 and 3 are processed.

While processing them, nodes 4 and 5 are added to the queue.

But they are not processed until the next outer-loop iteration.

This is how we maintain clear boundaries between levels.

COMMON MISTAKE:

Using a condition that processes the entire changing queue as part of
the current level.

That can mix children into their parents' level.

CORRECT APPROACH:

    int levelSize = q.size();

Capture the size once, then process exactly that many nodes.

===============================================================================
9. WHY RESET levelSum AND levelCount?
===============================================================================

Notice where these variables are declared:

    while (!q.empty()) {
        int levelSize = q.size();
        int i = 0;

        double levelSum = 0;
        double levelCount = 0;

        // Process current level.
    }

They are initialized inside the outer loop.

This is intentional.

Suppose we did not reset levelSum between levels.

Level 0:

    levelSum = 3

Level 1:

    levelSum = 3 + 9 + 20 = 32

But the correct sum for Level 1 is:

    9 + 20 = 29

We would calculate the wrong average.

By initializing the sum and count for each level, every average is
calculated independently.

===============================================================================
10. WHY USE double?
===============================================================================

Your code declares:

    double levelSum = 0;
    double levelCount = 0;

This ensures the division is performed using floating-point arithmetic.

Consider:

    int sum = 29;
    int count = 2;

If we write:

    double average = sum / count;

The division is performed as integer division because both operands
are integers.

The result becomes:

    29 / 2 = 14

Then the integer result is converted to double:

    average = 14.0

This loses the fractional part.

However, your implementation uses:

    double levelSum = 29;
    double levelCount = 2;

Therefore:

    double val = levelSum / levelCount;

Produces:

    val = 14.5

IMPORTANT:

You do not need both variables to be double.

A common and clear alternative is:

    int levelSum = 0;
    int levelCount = 0;

    double val = static_cast<double>(levelSum) / levelCount;

This explicitly converts the sum to double before division.

Your original implementation is also correct.

===============================================================================
11. A SMALL OPTIMIZATION: REUSE levelSize
===============================================================================

Your implementation uses:

    int levelSize = q.size();

And then:

    double levelCount = 0;

Inside the inner loop, you increment levelCount for every processed node.

This is correct.

However, think about what levelSize already tells us.

At the start of the level, we know exactly how many nodes will be
processed.

For example:

    levelSize = 2

We process exactly two nodes.

Therefore, the count of nodes in the current level is already known.

We can remove levelCount and calculate:

    double val = static_cast<double>(levelSum) / levelSize;

This gives us a simpler implementation:

    while (!q.empty()) {
        int levelSize = q.size();
        int levelSum = 0;

        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();

            levelSum += node->val;

            if (node->left != nullptr) {
                q.push(node->left);
            }

            if (node->right != nullptr) {
                q.push(node->right);
            }
        }

        double average =
            static_cast<double>(levelSum) / levelSize;

        ans.push_back(average);
    }

This is an alternative, not a correction required for your accepted code.

Both approaches have O(n) time complexity.

NOTE:

LeetCode's constraints for this problem ensure that the level sums fit
within the required numeric range for the standard solution.

===============================================================================
12. WHY DO WE NOT NEED A VECTOR FOR EVERY LEVEL?
===============================================================================

In Zigzag Level Order Traversal, we created:

    vector<int> v;

We needed that vector because we had to collect each level's node
values and possibly reverse their order.

In this problem, we do not need to return individual node values.

We only need the average of each level.

Therefore, we can calculate the sum as nodes are processed:

    levelSum += node->val;

And count the nodes:

    levelCount++;

After the level finishes, we calculate its average.

This avoids storing a separate vector of node values for each level.

The queue already maintains the nodes that need to be processed.

===============================================================================
13. EDGE CASES
===============================================================================

CASE 1: EMPTY TREE

        root = nullptr

Expected output:

        []

Your code returns immediately:

        if (root == nullptr) {
            return {};
        }

CASE 2: SINGLE NODE

        5

Only one level exists.

    Sum = 5
    Count = 1
    Average = 5.0

Output:

        [5.0]

CASE 3: NEGATIVE VALUES

                 -2
                /  \
              -4    6

Level 0:

    Average = -2.0

Level 1:

    Sum = -4 + 6 = 2
    Count = 2
    Average = 1.0

Output:

        [-2.0, 1.0]

Negative values are handled naturally by addition and division.

CASE 4: UNEVEN TREE

                 1
                /
               2
                \
                 3

Levels:

    Level 0: [1]
    Level 1: [2]
    Level 2: [3]

Output:

        [1.0, 2.0, 3.0]

The algorithm does not require the tree to be complete or balanced.

CASE 5: A LEVEL WITH THREE NODES

                 1
               /   \
              2     3
             /
            4

Level 2 contains only node 4.

The algorithm uses the actual queue size for that level, so missing
children do not cause incorrect counts.

===============================================================================
14. COMMON MISTAKES TO AVOID
===============================================================================

MISTAKE 1: FORGETTING TO RESET levelSum

If the sum is declared outside the outer loop and never reset, values
from previous levels will contaminate the next average.

CORRECT:

    double levelSum = 0;

Declare it inside the outer loop.

MISTAKE 2: USING INTEGER DIVISION

Incorrect:

    int sum = 29;
    int count = 2;

    double average = sum / count;

This produces 14.0, not 14.5.

CORRECT:

    double average = static_cast<double>(sum) / count;

Or use a double sum, as your accepted solution does.

MISTAKE 3: PROCESSING CHILDREN IN THE WRONG LEVEL

If we do not capture levelSize before the inner loop, newly enqueued
children could be processed as if they belonged to the current level.

CORRECT:

    int levelSize = q.size();

MISTAKE 4: DIVIDING BY ZERO

An empty tree should return before entering the traversal.

For a nonempty tree, every processed level has at least one node, so
levelCount is never zero in your implementation.

MISTAKE 5: APPENDING THE AVERAGE INSIDE THE INNER LOOP

If we append an average after every node, we will produce one result
per node rather than one result per level.

CORRECT:

    double val = levelSum / levelCount;
    ans.push_back(val);

Perform these operations after the inner loop finishes.

MISTAKE 6: USING THE WRONG RETURN TYPE

The problem expects:

    vector<double>

Not:

    vector<int>

Averages can contain fractional values.

===============================================================================
15. TIME COMPLEXITY ANALYSIS
===============================================================================

Let n be the number of nodes in the binary tree.

A) Queue insertion:

Every node is enqueued once.

Total time:

    O(n)

B) Queue removal:

Every node is removed once.

Total time:

    O(n)

C) Sum and count calculations:

Each node contributes once to the sum and count of its level.

Total time:

    O(n)

D) Appending the averages:

If the tree has h levels, we append h averages.

Since h <= n:

    O(h) <= O(n)

TOTAL TIME COMPLEXITY:

    O(n) + O(n) + O(n) + O(n)

    = O(n)

The solution is linear because every node is processed a constant
number of times.

===============================================================================
16. SPACE COMPLEXITY ANALYSIS
===============================================================================

A) Queue:

The queue can contain O(n) nodes in the worst case.

For a broad tree, many nodes can belong to the same level.

Therefore:

    Queue space = O(n)

B) Variables:

We use a fixed number of variables:

    levelSize
    i
    levelSum
    levelCount
    val

Their storage is:

    O(1)

C) Result vector:

If the tree has h levels, ans stores h averages.

Therefore:

    Result space = O(h)

Auxiliary space, excluding the returned answer:

    O(n)

Total space, including the answer:

    O(n)

===============================================================================
17. COMPARISON WITH OUR ZIGZAG SOLUTION
===============================================================================

ZIGZAG LEVEL ORDER TRAVERSAL:

    vector<vector<int>> ans;

    Each level is collected into a vector.

    Alternate levels are reversed.

AVERAGE OF LEVELS:

    vector<double> ans;

    We calculate the sum of each level.

    We divide by the number of nodes at that level.

COMMON FOUNDATION:

Both solutions use:

    queue<TreeNode*> q;

    while (!q.empty()) {
        int levelSize = q.size();

        // Process exactly levelSize nodes.
    }

This is a reusable BFS template.

The main difference lies in what we do with the nodes after processing
each level.

Zigzag:

    Collect values and reverse when needed.

Average:

    Calculate sum / count.

===============================================================================
18. INTERVIEW QUESTIONS AND ANSWERS
===============================================================================

Q1. Why do we use BFS?

Answer:
BFS processes nodes level by level, allowing us to calculate a separate
average for each level.

Q2. Why do we use a queue?

Answer:
A queue follows FIFO order, which supports level-order traversal.

Q3. What does levelSize represent?

Answer:
It is the number of nodes in the current level at the beginning of
that level's processing.

Q4. Why must levelSize be captured before the inner loop?

Answer:
Children are added to the queue while the current level is processed.
Capturing the size prevents those children from being included in the
current level's node count.

Q5. Why reset levelSum?

Answer:
Every level needs an independent sum. Resetting prevents previous
levels' values from affecting the current average.

Q6. Why do we use vector<double>?

Answer:
An average can contain a fractional part, so the result must support
floating-point values.

Q7. Why does integer division cause a problem?

Answer:
When both operands are integers, division discards the fractional part.
We must convert an operand to a floating-point type before division.

Q8. Why does the code work for an uneven tree?

Answer:
The queue contains only existing nodes. The algorithm uses the actual
number of nodes in each level, so missing children are not counted.

Q9. What is the time complexity?

Answer:
O(n), because every node is enqueued, dequeued, and processed once.

Q10. What is the auxiliary space complexity?

Answer:
O(n) in the worst case because the queue can contain O(n) nodes.

Q11. Could we use DFS instead?

Answer:
Yes. A recursive solution could track the depth of each node, maintaining
the sum and count for each depth. BFS is particularly natural because
the problem already asks us to process levels.

Q12. Do we really need levelCount?

Answer:
Not necessarily. Because levelSize already contains the number of nodes
at the current level, we can use levelSize as the divisor.

Q13. Why do we append the average after the inner loop?

Answer:
We need the complete sum and count for the level before calculating
its average. Appending inside the inner loop would create multiple
partial averages for a single level.

Q14. Is the algorithm dependent on the order of values within a level?

Answer:
No. Addition is independent of order. We obtain the same sum regardless
of whether the left or right child is processed first.

===============================================================================
19. REUSABLE BFS TEMPLATE
===============================================================================

Keep this general pattern in mind:

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {

        int levelSize = q.size();

        for (int i = 0; i < levelSize; i++) {

            TreeNode* node = q.front();
            q.pop();

            // Process the current node.

            if (node->left != nullptr) {
                q.push(node->left);
            }

            if (node->right != nullptr) {
                q.push(node->right);
            }
        }

        // Process the completed level.
    }

This template can be adapted to many problems:

    Level Order Traversal:
        Collect node values.

    Zigzag Traversal:
        Collect values and reverse alternate levels.

    Average of Levels:
        Maintain sum and count.

    Maximum Value Per Level:
        Maintain the maximum value.

    Minimum Value Per Level:
        Maintain the minimum value.

The underlying BFS remains the same. We change the processing logic
according to the problem's requirements.

===============================================================================
20. GITHUB DOCUMENTATION
===============================================================================

Suggested filename:

    Average_of_Levels_in_Binary_Tree.cpp

Suggested folder:

    DSA-journey-2026/
        Problems-Phase-01/
            Trees/
                BFS/
                    Average_of_Levels_in_Binary_Tree.cpp

Suggested commit message:

    Add detailed Average of Levels in Binary Tree solution

Suggested README entry:

    Problem: Average of Levels in Binary Tree
    Platform: LeetCode 637
    Approach: BFS + Level Sum + Level Count
    Time Complexity: O(n)
    Auxiliary Space: O(n)
    Status: Accepted
    Reported Runtime: Beating 100% at submission time

===============================================================================
21. FINAL REVISION SUMMARY
===============================================================================

Problem:
    Calculate the average value of every level in a binary tree.

Algorithm:
    Breadth-First Search (BFS).

Data structures:
    queue<TreeNode*>
    vector<double>

Important variables:
    levelSize  -> number of nodes at the current level
    levelSum   -> sum of values at the current level
    levelCount -> number of processed nodes at the current level

Main formula:

                 levelSum
    Average =   -----------
                levelCount

Critical BFS rule:

    Capture q.size() before processing each level.

Time complexity:

    O(n)

Auxiliary space complexity:

    O(n)

Most important lesson:

    Learn the reusable BFS pattern, then adapt the work performed
    at each level to solve different binary-tree problems.

===============================================================================
                    END OF REVISION FILE
===============================================================================
*/
