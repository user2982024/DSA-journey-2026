
/*
===============================================================================
                    DSA JOURNEY 2026 — BINARY TREES
                    PROBLEM: TOP VIEW OF A BINARY TREE
===============================================================================

Platform       : GeeksforGeeks
Problem        : Top View of Binary Tree
Topic          : Binary Trees, Breadth-First Search (BFS), Queue, Map
Difficulty     : Medium (platform-dependent)
Language       : C++
Status         : ACCEPTED
Test Result    : Passed 1111 test cases on GeeksforGeeks
Approach       : BFS + Horizontal Distance + Ordered Map

Author's Notes:
---------------
This solution was developed by understanding the problem and building the
algorithm step by step, rather than memorizing an existing implementation.

The key ideas discovered during the problem-solving session were:

1. A binary tree can be traversed level by level using BFS.
2. Every node can be assigned a horizontal distance (HD).
3. The root has HD 0.
4. A left child has HD = parent HD - 1.
5. A right child has HD = parent HD + 1.
6. We need to remember the first node encountered at every horizontal distance.
7. An ordered map keeps horizontal distances sorted from smallest to largest.
8. Iterating through that map produces the answer from left to right.

The final algorithm uses:
    queue<pair<Node*, int>>
    map<int, Node*>
    vector<int>

===============================================================================
1. PROBLEM STATEMENT
===============================================================================

Given the root of a binary tree, return the TOP VIEW of the tree.

The top view contains the nodes that would be visible if we looked at the
binary tree from directly above.

Imagine that you are standing above the tree and looking vertically downward.

At each horizontal position, only the highest visible node should appear
in the answer.

If multiple nodes occupy the same horizontal position, the node closest
to the root is visible from above.

The answer must be arranged from the leftmost visible node to the rightmost
visible node.

IMPORTANT:
---------
The top view is NOT simply:
    - all leaf nodes,
    - the left view,
    - the right view,
    - or the nodes at the deepest level.

It is determined by horizontal position and visibility from above.

===============================================================================
2. UNDERSTANDING THE HORIZONTAL DISTANCE TECHNIQUE
===============================================================================

We imagine a horizontal number line passing through the root.

The root is assigned horizontal distance 0.

Moving to the left decreases the horizontal distance by 1.
Moving to the right increases the horizontal distance by 1.

Rules:

    Root:       HD = 0
    Left child: HD = parent HD - 1
    Right child: HD = parent HD + 1

For example, consider this binary tree:

                    1
                   / \
                  2   3
                 / \   \
                4   5   6

The horizontal distances are:

    Node 1: HD =  0
    Node 2: HD = -1
    Node 3: HD = +1
    Node 4: HD = -2
    Node 5: HD =  0
    Node 6: HD = +2

Why does node 5 have HD 0?

Node 5 is the right child of node 2.

Node 2 has HD -1.

Therefore:

    HD(5) = HD(2) + 1
          = -1 + 1
          = 0

Node 5 and node 1 share the same horizontal distance.

However, node 1 is at level 0, while node 5 is at level 2.

When looking from above, node 1 is visible and node 5 is hidden behind it.

Therefore, node 1 must be retained for HD 0.

The top view of this example is:

    [4, 2, 1, 3, 6]

Notice that the answer is ordered by horizontal distance:

    -2  ->  4
    -1  ->  2
     0  ->  1
    +1  ->  3
    +2  ->  6

===============================================================================
3. WHY DO WE NEED BFS?
===============================================================================

BFS stands for Breadth-First Search.

For a binary tree, BFS visits nodes level by level.

The traversal begins at the root, then visits the root's children, followed
by the next level, and continues until every reachable node is processed.

Example:

                    1
                   / \
                  2   3
                 / \   \
                4   5   6

BFS visitation order:

    Level 0: 1
    Level 1: 2, 3
    Level 2: 4, 5, 6

Overall visitation order:

    1, 2, 3, 4, 5, 6

WHY IS BFS USEFUL FOR TOP VIEW?

The top view requires the highest visible node at every horizontal distance.

BFS processes nodes in nondecreasing order of their depth.

Therefore, the first time we encounter a horizontal distance, we have found
a node at the minimum depth among all nodes at that distance.

We can record that node and ignore later nodes at the same distance.

This is the central reason why BFS works for this approach.

IMPORTANT DISTINCTION:

BFS does not guarantee that every later node has a greater depth.
Two nodes at the same level can share a horizontal distance.

However, because the first encountered node is already at the minimum depth,
we never need to replace it for the top view.

===============================================================================
4. WHY DO WE NEED A QUEUE OF PAIRS?
===============================================================================

A normal BFS queue can store only node pointers:

    queue<Node*> q;

This is enough for ordinary level-order traversal.

However, for the top view, we must also know the horizontal distance of
every node when it is processed.

Therefore, we use:

    queue<pair<Node*, int>> q;

Each queue entry contains two associated values:

    first  -> Node* : pointer to the current node
    second -> int   : horizontal distance of that node

For example:

    {root, 0}
    {root->left, -1}
    {root->right, +1}

These pairs allow us to carry the horizontal distance through BFS.

When we retrieve an entry:

    auto current = q.front();

The compiler deduces that current has the type:

    pair<Node*, int>

We can then extract both values:

    Node* node = current.first;
    int horizontalDistance = current.second;

The expression q.front() returns the pair at the front of the queue.

The expression current.first accesses its node pointer.

The expression current.second accesses its horizontal distance.

The keyword auto allows C++ to deduce the variable's type automatically.

We could write the longer declaration explicitly:

    pair<Node*, int> current = q.front();

Both versions are valid.

===============================================================================
5. WHY DO WE NEED AN ORDERED MAP?
===============================================================================

We use:

    map<int, Node*> m;

This map stores:

    KEY   -> horizontal distance
    VALUE -> pointer to the visible node

For example, the map might contain:

    -2 -> pointer to node 4
    -1 -> pointer to node 2
     0 -> pointer to node 1
    +1 -> pointer to node 3
    +2 -> pointer to node 6

WHY NOT JUST USE A VECTOR?

The horizontal distances can be negative, zero, or positive.

A vector indexed directly by horizontal distance would not naturally support
negative indices, and we would need additional bookkeeping to translate
distances into valid vector indices.

A map provides a convenient association between each horizontal distance
and its corresponding node.

WHY USE map INSTEAD OF unordered_map?

An ordered map maintains its keys in ascending order.

Therefore, when we iterate from m.begin() to m.end(), the horizontal
distances are processed from leftmost to rightmost.

An unordered_map does not guarantee this ordering.

Since the required answer is ordered from left to right, map<int, Node*>
makes the final step straightforward.

===============================================================================
6. THE MOST IMPORTANT LOGIC: FIRST ENCOUNTER WINS
===============================================================================

The top view requires the first node encountered at every horizontal distance.

We check:

    if (m.find(horizontalDistance) == m.end())

What does this condition mean?

m.find(horizontalDistance) searches the map for the specified key.

If the key exists:
    find() returns an iterator pointing to the existing entry.

If the key does not exist:
    find() returns m.end().

Therefore:

    m.find(horizontalDistance) == m.end()

means:

    This horizontal distance has not been stored in the map yet.

Only then do we insert the current node:

    m[horizontalDistance] = node;

If the horizontal distance already exists, the condition is false and
the existing entry remains unchanged.

This is essential.

Suppose BFS encounters:

    Node 1 at HD 0
    Node 5 at HD 0

Node 1 is encountered first because it is closer to the root.

The map initially stores:

    m[0] = pointer to node 1

When node 5 is processed, HD 0 already exists.

The map remains unchanged.

Thus, node 1 remains visible in the top view.

IMPORTANT COMPARISON WITH BOTTOM VIEW:

Top View:
    Insert only when the horizontal distance is absent.

    if (m.find(horizontalDistance) == m.end()) {
        m[horizontalDistance] = node;
    }

Bottom View:
    Overwrite the entry whenever a node is processed.

    m[horizontalDistance] = node;

The difference is the map-update policy.

===============================================================================
7. BUILDING THE ALGORITHM STEP BY STEP
===============================================================================

STEP 1: Create the answer vector.

    vector<int> ans;

This will contain the visible node values in left-to-right order.

STEP 2: Create the BFS queue.

    queue<pair<Node*, int>> q;

Each entry contains a node pointer and its horizontal distance.

STEP 3: Create the ordered map.

    map<int, Node*> m;

This associates each horizontal distance with the first node encountered
at that distance.

STEP 4: Handle an empty tree.

    if (root == nullptr) {
        return {};
    }

An empty tree has no visible nodes, so the result is an empty vector.

This check also prevents us from trying to access children through a null
pointer.

STEP 5: Initialize the root's horizontal distance.

    int horizontalDistance = 0;
    q.push({root, horizontalDistance});

The root is the reference point, so its horizontal distance is zero.

The queue receives the pair {root, 0}.

STEP 6: Process nodes using BFS.

    while (!q.empty())

While the queue is not empty, retrieve the front pair.

    auto current = q.front();

Extract its components:

    Node* node = current.first;
    horizontalDistance = current.second;

Then remove the current pair:

    q.pop();

The local variables retain their values after the queue entry is removed.

STEP 7: Add the left child, if it exists.

    if (node->left != nullptr) {
        q.push({node->left, horizontalDistance - 1});
    }

The left child's horizontal distance is one less than the parent's.

STEP 8: Add the right child, if it exists.

    if (node->right != nullptr) {
        q.push({node->right, horizontalDistance + 1});
    }

The right child's horizontal distance is one greater than the parent's.

STEP 9: Record the current node only if its HD is new.

    if (m.find(horizontalDistance) == m.end()) {
        m[horizontalDistance] = node;
    }

This preserves the first node encountered at every horizontal distance.

STEP 10: Traverse the ordered map.

    for (auto it = m.begin(); it != m.end(); it++) {
        ans.push_back(it->second->data);
    }

Because map keys are sorted, the nodes are collected from left to right.

Understanding the iterator:

    it             -> current map entry
    it->first      -> horizontal distance
    it->second     -> Node* pointer
    it->second->data -> actual integer stored in the node

We must use it->second->data because the map's value is a node pointer,
not the node's integer data itself.

STEP 11: Return the answer.

    return ans;

===============================================================================
8. COMPLETE DRY RUN
===============================================================================

Consider the following tree:

                    1
                   / \
                  2   3
                 / \   \
                4   5   6

Horizontal distances:

    Node 1 ->  0
    Node 2 -> -1
    Node 3 -> +1
    Node 4 -> -2
    Node 5 ->  0
    Node 6 -> +2

Initial state:

    Queue: {1, 0}
    Map:   empty

------------------------------------------------------------
ITERATION 1: PROCESS NODE 1
------------------------------------------------------------

The front pair is:

    {1, 0}

Therefore:

    node = 1
    horizontalDistance = 0

Remove the pair from the queue.

Node 1 has a left child, node 2.

Enqueue:

    {2, -1}

Node 1 has a right child, node 3.

Enqueue:

    {3, +1}

The map does not contain HD 0.

Insert:

    m[0] = node 1

State:

    Queue: {2, -1}, {3, +1}
    Map:    0 -> 1

------------------------------------------------------------
ITERATION 2: PROCESS NODE 2
------------------------------------------------------------

The front pair is:

    {2, -1}

Therefore:

    node = 2
    horizontalDistance = -1

Remove the pair.

Node 2 has a left child, node 4.

Enqueue:

    {4, -2}

Node 2 has a right child, node 5.

Enqueue:

    {5, 0}

The map does not contain HD -1.

Insert:

    m[-1] = node 2

State:

    Queue: {3, +1}, {4, -2}, {5, 0}
    Map:   -1 -> 2
            0 -> 1

------------------------------------------------------------
ITERATION 3: PROCESS NODE 3
------------------------------------------------------------

The front pair is:

    {3, +1}

Therefore:

    node = 3
    horizontalDistance = +1

Remove the pair.

Node 3 has no left child.

Node 3 has a right child, node 6.

Enqueue:

    {6, +2}

The map does not contain HD +1.

Insert:

    m[+1] = node 3

State:

    Queue: {4, -2}, {5, 0}, {6, +2}
    Map:   -1 -> 2
            0 -> 1
           +1 -> 3

------------------------------------------------------------
ITERATION 4: PROCESS NODE 4
------------------------------------------------------------

The front pair is:

    {4, -2}

Node 4 is a leaf.

It has no children to enqueue.

HD -2 does not exist in the map.

Insert:

    m[-2] = node 4

State:

    Queue: {5, 0}, {6, +2}
    Map:   -2 -> 4
           -1 -> 2
            0 -> 1
           +1 -> 3

------------------------------------------------------------
ITERATION 5: PROCESS NODE 5
------------------------------------------------------------

The front pair is:

    {5, 0}

Node 5 is a leaf.

It has no children to enqueue.

Now check the map.

HD 0 already exists:

    m[0] = node 1

Therefore:

    m.find(0) != m.end()

The insertion condition is false.

Node 5 is not inserted, and node 1 remains stored at HD 0.

This is the most important step in the dry run.

Although node 5 has the same horizontal distance as node 1, node 1 is
at a shallower level and remains visible from above.

State:

    Queue: {6, +2}
    Map:   -2 -> 4
           -1 -> 2
            0 -> 1
           +1 -> 3

------------------------------------------------------------
ITERATION 6: PROCESS NODE 6
------------------------------------------------------------

The front pair is:

    {6, +2}

Node 6 is a leaf.

HD +2 does not exist in the map.

Insert:

    m[+2] = node 6

The queue is now empty.

BFS is complete.

------------------------------------------------------------
FINAL MAP
------------------------------------------------------------

Because map sorts keys in ascending order:

    HD -2 -> Node 4
    HD -1 -> Node 2
    HD  0 -> Node 1
    HD +1 -> Node 3
    HD +2 -> Node 6

Iterating through the map and extracting each node's data produces:

    ans = [4, 2, 1, 3, 6]

This is the correct top view.

===============================================================================
9. WHY THE ALGORITHM IS CORRECT
===============================================================================

We can justify correctness using three observations.

OBSERVATION 1: BFS processes nodes by nondecreasing depth.

The root is processed first, followed by nodes at the next level, and then
nodes at subsequent levels.

Consequently, the first node encountered at any horizontal distance has
the minimum depth among all nodes at that distance.

OBSERVATION 2: The map stores only the first node at each horizontal
distance.

The find() condition inserts a node only if its horizontal distance has
not been recorded before.

Therefore, the first node at each horizontal distance is retained, and
later nodes at that distance cannot replace it.

OBSERVATION 3: The ordered map produces left-to-right output.

A std::map<int, Node*> stores keys in ascending order.

Since the keys are horizontal distances, the leftmost horizontal distance
is processed first, followed by progressively more rightward distances.

CONCLUSION:

For every horizontal distance, the algorithm selects the shallowest node
encountered by BFS and returns these selected nodes from left to right.

Therefore, the algorithm correctly computes the top view of the binary
tree.

===============================================================================
10. TIME COMPLEXITY
===============================================================================

Let n be the total number of nodes in the binary tree.

BFS processes each node exactly once.

For every node, we perform a constant number of pointer checks and queue
operations, plus map operations.

The map can contain at most n distinct horizontal distances.

An insertion or lookup in std::map takes O(log n) time in the worst case.

There are at most n map lookups and n insertions.

Therefore, the total time complexity is:

    O(n log n)

The final traversal of the map takes O(n) time.

Combining the costs:

    BFS and map operations: O(n log n)
    Final map traversal:    O(n)

Total:

    O(n log n) + O(n)
    = O(n log n)

FINAL TIME COMPLEXITY:

    O(n log n)

IMPORTANT:
----------
The BFS itself takes O(n) time. The additional logarithmic factor comes
from using an ordered map.

===============================================================================
11. SPACE COMPLEXITY
===============================================================================

The algorithm uses several data structures.

QUEUE:

    queue<pair<Node*, int>> q;

In the worst case, the queue may contain O(n) entries.

Therefore, queue space is O(n).

MAP:

    map<int, Node*> m;

Each distinct horizontal distance stores at most one node pointer.

There can be at most n distinct horizontal distances.

Therefore, map space is O(n).

ANSWER VECTOR:

    vector<int> ans;

The result contains one value for each distinct horizontal distance.

Its size is at most n.

Therefore, output space is O(n).

The local variables such as node, current, and horizontalDistance use O(1)
additional space at a time.

Combining these bounds:

    O(n) + O(n) + O(n) = O(n)

FINAL AUXILIARY SPACE COMPLEXITY:

    O(n)

The returned answer itself also requires O(n) output space.

===============================================================================
12. EDGE CASES
===============================================================================

CASE 1: EMPTY TREE

Input:

    root = nullptr

Expected output:

    []

Reason:

The base case returns an empty vector immediately.

CASE 2: SINGLE NODE

Tree:

        10

Expected output:

    [10]

Reason:

The root is the only node, and its horizontal distance is zero.

CASE 3: LEFT-SKEWED TREE

Tree:

        1
       /
      2
     /
    3

Horizontal distances:

    Node 1 ->  0
    Node 2 -> -1
    Node 3 -> -2

Expected top view:

    [3, 2, 1]

Every node is visible because every node occupies a new horizontal distance.

CASE 4: RIGHT-SKEWED TREE

Tree:

    1
     \
      2
       \
        3

Horizontal distances:

    Node 1 -> 0
    Node 2 -> 1
    Node 3 -> 2

Expected top view:

    [1, 2, 3]

CASE 5: MULTIPLE NODES SHARE THE SAME HD

Tree:

        1
       / \
      2   3
       \
        4

Node 1 has HD 0.
Node 2 has HD -1.
Node 3 has HD +1.
Node 4 has HD 0.

Node 1 is encountered before node 4.

Therefore, node 1 remains stored at HD 0.

Expected top view:

    [2, 1, 3]

CASE 6: A NODE IS HIDDEN BEHIND A SHALLOWER NODE

Tree:

          1
         /
        2
         \
          3

Node 1 and node 3 both have HD 0.

Node 1 is at level 0.
Node 3 is at level 2.

The top view contains node 1, not node 3.

Expected output:

    [2, 1]

===============================================================================
13. COMMON MISTAKES AND HOW THEY WERE RESOLVED
===============================================================================

MISTAKE 1: THINKING WE MUST FIRST REACH THE BOTTOM-LEFT LEAF

Initially, it may seem that we must navigate to the bottom-left leaf before
calculating the top view.

This is unnecessary.

BFS naturally visits nodes level by level, and horizontal distance can
be calculated as each node is processed.

MISTAKE 2: USING queue<Node*> WITHOUT TRACKING HORIZONTAL DISTANCE

A normal queue does not remember each node's horizontal position.

We resolved this by using:

    queue<pair<Node*, int>> q;

This carries the node and its horizontal distance together.

MISTAKE 3: CONFUSING THE PAIR WITH THE NODE POINTER

The expression:

    auto current = q.front();

returns a pair, not a Node*.

We then extract the two components:

    Node* node = current.first;
    int horizontalDistance = current.second;

MISTAKE 4: CONFUSING map KEYS AND VALUES

The map is declared as:

    map<int, Node*> m;

Therefore:

    it->first  -> horizontal distance
    it->second -> node pointer

To retrieve the actual integer value:

    it->second->data

Using it->first in the answer would incorrectly return horizontal distances
instead of node values.

MISTAKE 5: OVERWRITING THE FIRST NODE

If we assigned:

    m[horizontalDistance] = node;

on every visit, deeper nodes could replace shallower nodes.

That update rule is appropriate for the standard bottom-view approach,
but not for top view.

For top view, we first check whether the horizontal distance already exists.

MISTAKE 6: USING unordered_map WHEN SORTED OUTPUT IS REQUIRED

An unordered_map does not guarantee ascending key order.

Using std::map lets us traverse horizontal distances from left to right
without performing a separate sorting step.

MISTAKE 7: FORGETTING THE EMPTY-TREE BASE CASE

Without a null-root check, the algorithm could enqueue a null pointer and
eventually attempt to access its children.

We handle this safely:

    if (root == nullptr) {
        return {};
    }

===============================================================================
14. COMPARISON: TOP VIEW VS BOTTOM VIEW
===============================================================================

Both approaches can use:

    queue<pair<Node*, int>>
    map<int, Node*>

Both calculate horizontal distances in the same way.

Both traverse the map in ascending order to produce left-to-right output.

The key difference is how the map is updated.

TOP VIEW:

    if (m.find(horizontalDistance) == m.end()) {
        m[horizontalDistance] = node;
    }

Keep the first node encountered at each horizontal distance.

BOTTOM VIEW:

    m[horizontalDistance] = node;

Overwrite the entry whenever a node at that horizontal distance is visited.

BFS processes nodes in nondecreasing order of depth, which is why these
different update rules produce the desired views.

For the standard GFG bottom-view convention, when nodes at the same depth
share a horizontal distance, processing left children before right children
and overwriting on every visit gives the expected tie-breaking behavior.

===============================================================================
15. INTERVIEW QUESTIONS AND ANSWERS
===============================================================================

Q1. Why do we use BFS?

Answer:
BFS processes nodes level by level. Therefore, the first node encountered
at each horizontal distance is at the minimum depth for that distance.

Q2. Why do we need horizontal distance?

Answer:
Horizontal distance identifies the relative horizontal position of a node.
Nodes with the same horizontal distance compete for visibility in the
top view.

Q3. Why is the root's horizontal distance zero?

Answer:
The root is the reference point from which horizontal positions are
calculated. Leftward movement decreases HD, and rightward movement
increases HD.

Q4. Why use queue<pair<Node*, int>>?

Answer:
We must carry both the node pointer and its horizontal distance during BFS.

Q5. Why use map<int, Node*>?

Answer:
The map associates horizontal distances with nodes and keeps the keys
sorted, allowing us to produce left-to-right output.

Q6. Why not overwrite an existing map entry?

Answer:
The first node encountered at a horizontal distance is at the minimum
depth for that distance. Overwriting it could replace a visible node with
a node hidden farther down the tree.

Q7. What does m.find(hd) == m.end() mean?

Answer:
It means the map does not currently contain the key hd.

Q8. What does it->second->data mean?

Answer:
it->second retrieves the Node* stored in the map entry, and ->data accesses
the integer stored inside that node.

Q9. What is the time complexity?

Answer:
O(n log n), because each node is processed once and map operations take
O(log n) time in the worst case.

Q10. What is the auxiliary space complexity?

Answer:
O(n), due to the queue and map in the worst case.

Q11. Can DFS solve the top-view problem?

Answer:
Yes, but a simple first-encounter DFS rule is not sufficient because DFS
does not process nodes in nondecreasing depth order. A DFS solution needs
to track depth and retain the shallowest node for every horizontal distance.

Q12. What is the difference between top view and left view?

Answer:
Top view selects nodes by horizontal distance.
Left view selects the first visible node at each depth when viewed from
the left side.

Q13. What is the difference between top view and bottom view?

Answer:
Top view retains the shallowest node at each horizontal distance.
Bottom view retains a deepest node at each horizontal distance, according
to the problem's tie-breaking convention.

Q14. Why is the output ordered from left to right?

Answer:
The map keys are horizontal distances, and std::map stores integer keys in
ascending order.

Q15. Why is the map value a Node* rather than an int?

Answer:
Storing Node* preserves access to the actual node. We can then retrieve its
data field when constructing the answer. A map<int, int> could also work
if we stored node values directly instead.

===============================================================================
16. FINAL TAKEAWAYS
===============================================================================

The most important lessons from this problem are:

1. BFS is useful when processing nodes by level.
2. A pair can carry additional information alongside a node pointer.
3. Horizontal distance is calculated using the parent node's distance.
4. The first-encounter rule selects the shallowest node at each HD.
5. An ordered map automatically sorts horizontal distances.
6. Iterators let us access both map keys and values.
7. The correct time complexity is O(n log n) for this map-based solution.
8. The auxiliary space complexity is O(n).
9. Top View and Bottom View use the same basic BFS framework but different
   map-update policies.
10. Understanding why the algorithm works is more valuable than memorizing
    the final code.

===============================================================================
17. COMPLETE ACCEPTED IMPLEMENTATION
===============================================================================

The implementation below preserves the accepted GeeksforGeeks solution.

The null-root check is included for safety.

===============================================================================
*/

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <utility>

using namespace std;

/*
GeeksforGeeks node definition:

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

The judge supplies this definition, so do not duplicate it when submitting
the Solution class to GeeksforGeeks.
*/

class Solution {
public:
    vector<int> topView(Node* root) {

        // Stores the final top-view node values from left to right.
        vector<int> ans;

        // Each entry stores:
        // first  = pointer to a tree node
        // second = horizontal distance of that node
        queue<pair<Node*, int>> q;

        // Key   = horizontal distance
        // Value = pointer to the first node encountered at that distance
        map<int, Node*> m;

        // An empty tree has an empty top view.
        if (root == nullptr) {
            return {};
        }

        // The root is at horizontal distance zero.
        int horizontalDistance = 0;

        // Begin BFS with the root and its horizontal distance.
        q.push({root, horizontalDistance});

        // Process the tree level by level.
        while (!q.empty()) {

            // Retrieve the front pair from the queue.
            auto current = q.front();

            // Extract the node pointer.
            Node* node = current.first;

            // Extract the node's horizontal distance.
            horizontalDistance = current.second;

            // Remove the processed pair from the queue.
            q.pop();

            // A left child is one horizontal position to the left.
            if (node->left != nullptr) {
                q.push({
                    node->left,
                    horizontalDistance - 1
                });
            }

            // A right child is one horizontal position to the right.
            if (node->right != nullptr) {
                q.push({
                    node->right,
                    horizontalDistance + 1
                });
            }

            // For top view, preserve the first node encountered
            // at each horizontal distance.
            if (m.find(horizontalDistance) == m.end()) {
                m[horizontalDistance] = node;
            }
        }

        // The ordered map sorts horizontal distances from left to right.
        for (auto it = m.begin(); it != m.end(); it++) {

            // The map value is a Node*.
            // Access its data field to obtain the actual node value.
            ans.push_back(it->second->data);
        }

        // Return the completed top view.
        return ans;
    }
};

/*
===============================================================================
END OF NOTES
===============================================================================

Problem status:
    ACCEPTED — GeeksforGeeks
    1111 test cases passed

Recommended revision:
    1. Reconstruct the solution without looking at these notes.
    2. Explain why BFS guarantees the first encounter is shallowest.
    3. Explain why map keys are horizontal distances.
    4. Compare the top-view and bottom-view map-update rules.
    5. State the time and auxiliary space complexities.

Remember:
    Do not memorize the code alone.
    Understand the reasoning behind every data structure and condition.

===============================================================================
*/
