
/*
===============================================================================
                        BOTTOM VIEW OF A BINARY TREE
===============================================================================

Platform       : GeeksforGeeks (GFG)
Topic          : Binary Trees
Category       : Tree Views, Breadth-First Search (BFS), Queue, Ordered Map
Status         : Accepted
Language       : C++

===============================================================================
1. PROBLEM STATEMENT
===============================================================================

Given the root of a binary tree, return the bottom view of the binary tree.

The bottom view consists of the nodes that are visible when the tree is
observed from the bottom.

If multiple nodes occupy the same horizontal distance from the root, the
node that appears lower in the tree should be visible.

For nodes that have the same horizontal distance and the same depth, this
implementation follows the traversal order used by GFG's expected solution:
BFS, processing the left child before the right child, with later visits
overwriting earlier ones.

The returned vector must contain the visible node values ordered from the
leftmost horizontal distance to the rightmost horizontal distance.

Example tree:

                 1
               /   \
              2     3
             / \     \
            4   5     6

Expected bottom view:

        [4, 2, 5, 3, 6]

Explanation:

- Node 4 is visible at horizontal distance -2.
- Node 2 is visible at horizontal distance -1.
- Node 5 is visible at horizontal distance  0.
- Node 3 is visible at horizontal distance +1.
- Node 6 is visible at horizontal distance +2.

Notice that node 5 replaces node 1 at horizontal distance 0 because node 5
is deeper than node 1.

===============================================================================
2. CORE CONCEPT: HORIZONTAL DISTANCE
===============================================================================

To determine which nodes appear in the same vertical column, we assign
each node a horizontal distance (HD).

Definition:

    Horizontal distance = horizontal position relative to the root.

Rules:

    Root node:          HD =  0
    Left child:         HD = parent HD - 1
    Right child:        HD = parent HD + 1

For the example tree:

                 1 (HD 0)
               /          \
         2 (HD -1)       3 (HD +1)
          /    \                 \
   4 (HD -2) 5 (HD 0)          6 (HD +2)

Nodes 1 and 5 have the same horizontal distance: 0.

However, node 5 is deeper, so it appears in the bottom view instead of
node 1.

IMPORTANT:

Horizontal distance determines the column of a node, not its depth.

Two nodes can share the same horizontal distance while being at different
depths.

===============================================================================
3. WHY DO WE USE BFS?
===============================================================================

BFS stands for Breadth-First Search.

BFS visits nodes level by level, starting at the root.

For example:

                 1
               /   \
              2     3
             / \     \
            4   5     6

BFS order:

    1 -> 2 -> 3 -> 4 -> 5 -> 6

BFS is useful because it processes nodes in nondecreasing order of depth.

When we visit a node, we store it in the map at its horizontal distance:

    m[horizontalDistance] = node;

If another node later appears at the same horizontal distance, the new
node overwrites the old one.

Because BFS visits deeper levels after shallower levels, the map gradually
retains the deepest node encountered in each column.

IMPORTANT DETAIL:

If two nodes have the same depth and horizontal distance, BFS alone does
not distinguish which one should win. The result depends on traversal order
and the problem's tie-breaking convention.

Here, we process left children before right children and overwrite on every
visit. This matches the accepted GFG implementation.

===============================================================================
4. DATA STRUCTURES USED
===============================================================================

A) VECTOR

    vector<int> ans;

Purpose:

Stores the final bottom-view values.

The vector is filled only after the traversal finishes.

B) QUEUE OF PAIRS

    queue<pair<Node*, int>> q;

Each queue entry stores two pieces of information:

    pair.first  -> pointer to the current tree node
    pair.second -> horizontal distance of that node

Why do we need both?

The node pointer lets us access its value and children.

The horizontal distance tells us which vertical column the node belongs to.

For example:

    q.push({root, 0});

This means that the root is located at horizontal distance zero.

C) ORDERED MAP

    map<int, Node*> m;

The map associates each horizontal distance with the node currently
selected for that column.

Example:

    m[-2] = node4;
    m[-1] = node2;
    m[ 0] = node5;
    m[ 1] = node3;
    m[ 2] = node6;

WHY USE map INSTEAD OF unordered_map?

A C++ map keeps its keys sorted in ascending order.

Therefore, iterating over the map automatically processes horizontal
distances from left to right.

This eliminates the need to sort the horizontal distances separately.

===============================================================================
5. THE MOST IMPORTANT LINE
===============================================================================

    m[horizontalDistance] = node;

This line is the central idea behind our solution.

Unlike Top View, we do NOT check whether the horizontal distance already
exists.

Every node we visit replaces the currently stored node at that horizontal
distance.

Consider the following sequence:

    Visit node 1 at HD 0:

        m[0] = node1;

    Later, visit node 5 at HD 0:

        m[0] = node5;

The previous value, node1, is replaced by node5.

If another deeper node is encountered at HD 0, it will replace node5 too.

The final value stored at that horizontal distance is the last node
encountered there by our BFS traversal.

Because BFS processes levels from top to bottom, this is a deepest node
for that horizontal distance.

===============================================================================
6. TOP VIEW VS BOTTOM VIEW
===============================================================================

TOP VIEW:

    if (m.find(horizontalDistance) == m.end()) {
        m[horizontalDistance] = node;
    }

Only store a node if that horizontal distance has not appeared before.

Why?

The first node encountered in BFS at a horizontal distance is at the
minimum depth among nodes in that column.

BOTTOM VIEW:

    m[horizontalDistance] = node;

Always update the map.

Why?

We want a deeper node to replace a shallower node in the same column.

SUMMARY:

    Top View    -> first node encountered at each HD
    Bottom View -> last node encountered at each HD

This summary assumes BFS, the same child-processing order, and the usual
bottom-view tie convention used by this implementation.

===============================================================================
7. COMPLETE ALGORITHM
===============================================================================

Step 1:
    Create an empty answer vector, queue, and ordered map.

Step 2:
    If root is nullptr, return an empty vector.

Step 3:
    Assign horizontal distance 0 to the root and push it into the queue.

Step 4:
    While the queue is not empty:

        a. Read the front pair.
        b. Extract the node pointer and horizontal distance.
        c. Remove the pair from the queue.
        d. Push the left child with HD - 1, if it exists.
        e. Push the right child with HD + 1, if it exists.
        f. Assign the current node to m[HD], overwriting any previous node.

Step 5:
    Iterate through the ordered map from beginning to end.

Step 6:
    Append each stored node's data to the answer vector.

Step 7:
    Return the answer vector.

===============================================================================
8. COMPLETE DRY RUN
===============================================================================

Consider this tree:

                 1
               /   \
              2     3
             / \     \
            4   5     6

Initially:

    Queue = [(1, 0)]
    Map   = {}

---------------------------------------
ITERATION 1: PROCESS NODE 1
---------------------------------------

Front pair:

    (1, 0)

Current node:

    node = 1
    HD   = 0

Enqueue children:

    Left child 2 -> HD -1
    Right child 3 -> HD +1

Queue:

    [(2, -1), (3, +1)]

Update map:

    m[0] = node1

Map:

    HD -1 : not present
    HD  0 : 1
    HD +1 : not present

---------------------------------------
ITERATION 2: PROCESS NODE 2
---------------------------------------

Front pair:

    (2, -1)

Current node:

    node = 2
    HD   = -1

Enqueue children:

    Left child 4 -> HD -2
    Right child 5 -> HD  0

Queue:

    [(3, +1), (4, -2), (5, 0)]

Update map:

    m[-1] = node2

Map:

    HD -1 : 2
    HD  0 : 1

---------------------------------------
ITERATION 3: PROCESS NODE 3
---------------------------------------

Front pair:

    (3, +1)

Current node:

    node = 3
    HD   = +1

Left child:

    Does not exist.

Right child:

    Node 6 -> HD +2

Queue:

    [(4, -2), (5, 0), (6, +2)]

Update map:

    m[+1] = node3

Map:

    HD -1 : 2
    HD  0 : 1
    HD +1 : 3

---------------------------------------
ITERATION 4: PROCESS NODE 4
---------------------------------------

Front pair:

    (4, -2)

Current node:

    node = 4
    HD   = -2

Node 4 has no children.

Queue:

    [(5, 0), (6, +2)]

Update map:

    m[-2] = node4

Map:

    HD -2 : 4
    HD -1 : 2
    HD  0 : 1
    HD +1 : 3

---------------------------------------
ITERATION 5: PROCESS NODE 5
---------------------------------------

Front pair:

    (5, 0)

Current node:

    node = 5
    HD   = 0

Node 5 has no children.

Queue:

    [(6, +2)]

Update map:

    m[0] = node5

IMPORTANT:

    Previously, m[0] = node1.
    Now,   m[0] = node5.

Node 5 replaces node 1 because it is encountered later at the same HD.

Map:

    HD -2 : 4
    HD -1 : 2
    HD  0 : 5
    HD +1 : 3

---------------------------------------
ITERATION 6: PROCESS NODE 6
---------------------------------------

Front pair:

    (6, +2)

Current node:

    node = 6
    HD   = +2

Node 6 has no children.

Queue:

    []

Update map:

    m[+2] = node6

Final map:

    HD -2 : 4
    HD -1 : 2
    HD  0 : 5
    HD +1 : 3
    HD +2 : 6

---------------------------------------
BUILD THE ANSWER
---------------------------------------

The map is ordered by horizontal distance.

Iterating from begin() to end():

    HD -2 -> 4
    HD -1 -> 2
    HD  0 -> 5
    HD +1 -> 3
    HD +2 -> 6

Final answer:

    [4, 2, 5, 3, 6]

===============================================================================
9. WHY DOES THE MAP PRODUCE LEFT-TO-RIGHT ORDER?
===============================================================================

We use:

    map<int, Node*> m;

The keys are integers representing horizontal distances.

A std::map maintains its keys in ascending order.

For example, if the keys are:

    2, -1, 0, -2, 1

The map iterates through them in this order:

    -2, -1, 0, 1, 2

Negative horizontal distances are to the left of the root.

Positive horizontal distances are to the right of the root.

Therefore, ascending key order gives the correct left-to-right output.

===============================================================================
10. FULL IMPLEMENTATION
===============================================================================

The Node definition is supplied by GFG.

The following implementation can be used inside the GFG Solution class.

*/

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <utility>

using namespace std;

/*
GFG supplies the Node definition:

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};
*/

class Solution {
public:
    vector<int> bottomView(Node* root) {

        // Stores the final bottom-view values from left to right.
        vector<int> ans;

        // Each entry contains:
        // {pointer to node, horizontal distance from the root}.
        queue<pair<Node*, int>> q;

        // Maps each horizontal distance to the currently selected node.
        // The map keeps horizontal distances sorted.
        map<int, Node*> m;

        // An empty tree has an empty bottom view.
        if (root == nullptr) {
            return {};
        }

        // The root has horizontal distance zero.
        int horizontalDistance = 0;

        // Begin BFS with the root.
        q.push({root, horizontalDistance});

        // Process nodes level by level.
        while (!q.empty()) {

            // Read the front entry.
            auto current = q.front();

            // Extract the node pointer and its horizontal distance.
            Node* node = current.first;
            horizontalDistance = current.second;

            // Remove the current entry from the queue.
            q.pop();

            // A left child is one column to the left.
            if (node->left != nullptr) {
                q.push({
                    node->left,
                    horizontalDistance - 1
                });
            }

            // A right child is one column to the right.
            if (node->right != nullptr) {
                q.push({
                    node->right,
                    horizontalDistance + 1
                });
            }

            // BOTTOM VIEW KEY IDEA:
            // Always update the map.
            //
            // If a node already exists at this horizontal distance,
            // the current node replaces it.
            //
            // BFS processes deeper levels after shallower levels.
            // Consequently, deeper nodes overwrite shallower nodes
            // at the same horizontal distance.
            m[horizontalDistance] = node;
        }

        // The map is sorted by horizontal distance.
        // Append node values from the leftmost column to the rightmost.
        for (auto it = m.begin(); it != m.end(); it++) {
            ans.push_back(it->second->data);
        }

        // Return the bottom view.
        return ans;
    }
};

/*
===============================================================================
11. TIME COMPLEXITY ANALYSIS
===============================================================================

Let n be the number of nodes in the tree.

A) BFS traversal:

    Every node is inserted into the queue once and removed once.

    Queue traversal alone: O(n)

B) Map operations:

    For every node, we perform:

        m[horizontalDistance] = node;

    A std::map generally performs insertion or lookup/update in O(log k),
    where k is the number of distinct horizontal distances.

    Since k <= n, each map update takes O(log n) time in the worst case.

    Across n nodes:

        O(n log n)

C) Building the answer:

    The map contains k distinct horizontal distances.

    Iterating through the map takes O(k), which is at most O(n).

TOTAL TIME COMPLEXITY:

    O(n) + O(n log n) + O(n)

    = O(n log n)

Auxiliary space:

    Queue: at most O(n) nodes in the worst case.
    Map:   at most O(n) distinct horizontal distances.
    Answer vector: O(n) output storage.

Auxiliary space, excluding the returned output vector:

    O(n)

If the output vector is included in total storage usage, the overall
space consumption is still O(n).

===============================================================================
12. EDGE CASES
===============================================================================

CASE 1: EMPTY TREE

        root = nullptr

The function returns:

        []

Reason:

There are no nodes to display.

CASE 2: SINGLE NODE

        1

Output:

        [1]

Reason:

Only horizontal distance zero exists.

CASE 3: LEFT-SKEWED TREE

        1
       /
      2
     /
    3

Horizontal distances:

        Node 1 ->  0
        Node 2 -> -1
        Node 3 -> -2

Output:

        [3, 2, 1]

CASE 4: RIGHT-SKEWED TREE

    1
     \
      2
       \
        3

Horizontal distances:

        Node 1 -> 0
        Node 2 -> 1
        Node 3 -> 2

Output:

        [1, 2, 3]

CASE 5: MULTIPLE NODES AT THE SAME HD

                 1
               /   \
              2     3
               \   /
                4 5

Horizontal distances:

        Node 1 ->  0
        Node 2 -> -1
        Node 3 -> +1
        Node 4 ->  0
        Node 5 ->  0

Nodes 1, 4, and 5 share HD 0.

BFS processes nodes 4 and 5 at the same depth.
Since node 5 is visited after node 4 in this traversal, node 5 remains
at HD 0.

The map's HD 0 entry is therefore node 5.

This demonstrates why tie-breaking matters when two nodes share both
horizontal distance and depth.

===============================================================================
13. COMMON MISTAKES TO AVOID
===============================================================================

MISTAKE 1: USING THE TOP-VIEW CONDITION

Incorrect for this bottom-view approach:

    if (m.find(horizontalDistance) == m.end()) {
        m[horizontalDistance] = node;
    }

That condition preserves the first node and prevents later nodes from
overwriting it.

It is the standard first-encounter approach for Top View, not Bottom View.

Correct:

    m[horizontalDistance] = node;

MISTAKE 2: FORGETTING TO TRACK HORIZONTAL DISTANCE

If the queue stores only Node*, the algorithm does not directly know which
vertical column each node belongs to.

Correct queue type:

    queue<pair<Node*, int>> q;

MISTAKE 3: ASSIGNING THE WRONG HD TO A CHILD

Incorrect:

    Left child  -> HD + 1
    Right child -> HD - 1

Correct:

    Left child  -> parent HD - 1
    Right child -> parent HD + 1

MISTAKE 4: USING AN UNORDERED MAP WITHOUT SORTING

An unordered_map does not guarantee ascending key order.

Even if the correct nodes are stored, iterating through an unordered_map
does not guarantee the required left-to-right result.

Using std::map avoids that extra sorting step.

MISTAKE 5: ADDING NODE VALUES INSTEAD OF NODE POINTERS

The map is declared as:

    map<int, Node*> m;

Therefore, each map value is a Node pointer.

To retrieve its integer data, use:

    it->second->data

MISTAKE 6: FORGETTING THE EMPTY-TREE CASE

Always consider:

    if (root == nullptr) {
        return {};
    }

This prevents unnecessary traversal logic when the tree is empty.

MISTAKE 7: ASSUMING BFS ALONE RESOLVES ALL TIES

BFS guarantees that shallower levels are processed first.

However, nodes at the same depth may share the same horizontal distance.
The traversal order then determines which node is retained by overwriting.

Follow the specific tie-breaking rules required by the problem.

===============================================================================
14. INTERVIEW QUESTIONS AND ANSWERS
===============================================================================

Q1. Why do we use BFS for Bottom View?

Answer:
BFS visits nodes level by level. Deeper nodes are processed after
shallower nodes, so overwriting the map lets deeper nodes replace
shallower nodes at the same horizontal distance.

Q2. Why do we store horizontal distance?

Answer:
It identifies the vertical column occupied by each node.

Q3. Why is the root's horizontal distance zero?

Answer:
The root is the reference point. Left columns have negative distances,
and right columns have positive distances.

Q4. Why does a left child receive HD - 1?

Answer:
It is one horizontal column to the left of its parent.

Q5. Why does a right child receive HD + 1?

Answer:
It is one horizontal column to the right of its parent.

Q6. Why use a queue?

Answer:
A queue supports FIFO processing, which enables level-order traversal.

Q7. Why use a map?

Answer:
It associates each horizontal distance with a node and keeps the
distances sorted from left to right.

Q8. Why overwrite an existing map entry?

Answer:
A later BFS visit at the same horizontal distance is at the same or
a deeper level. Overwriting ensures that deeper nodes replace shallower
ones. For equal-depth ties, the result follows the chosen traversal order.

Q9. What is the main difference between Top View and Bottom View?

Answer:
Top View stores only the first node encountered at each horizontal
distance. Bottom View overwrites the stored node whenever another node
at that distance is visited.

Q10. What is the time complexity?

Answer:
O(n log n), because n nodes are processed and each map update costs
O(log n) in the worst case.

Q11. What is the auxiliary space complexity?

Answer:
O(n), because the queue and map can each contain O(n) entries.

Q12. Why not use a vector indexed directly by horizontal distance?

Answer:
Horizontal distances can be negative, and the required index range is
not known beforehand. A map handles negative and positive distances
naturally and maintains sorted order.

Q13. Can DFS solve Bottom View?

Answer:
Yes. A DFS approach can record each node's depth and horizontal distance,
then retain the deepest node at each horizontal distance. Equal-depth
ties must be handled explicitly to match the problem's requirements.

Q14. Does map store every node?

Answer:
No. It stores at most one selected node per distinct horizontal distance.
Each new node at that distance replaces the previously stored pointer.

Q15. What happens if the same HD is visited many times?

Answer:
The map entry is overwritten each time. At the end, it holds the last
node encountered at that HD under the selected BFS traversal order.

===============================================================================
15. FINAL REVISION SUMMARY
===============================================================================

Problem:
    Find the nodes visible from the bottom of a binary tree.

Core idea:
    Associate each node with a horizontal distance.

Horizontal-distance rules:
    Root  = 0
    Left  = parent HD - 1
    Right = parent HD + 1

Data structures:
    Queue of {Node*, HD}
    Ordered map of {HD, Node*}
    Vector for the final answer

Traversal:
    BFS (level-order traversal)

Bottom View update:
    m[horizontalDistance] = node;

Output:
    Iterate over the ordered map and collect node values.

Time complexity:
    O(n log n)

Auxiliary space complexity:
    O(n)

Key difference from Top View:
    Top View preserves the first node at each HD.
    Bottom View overwrites the entry as nodes are visited.

===============================================================================
16. GITHUB DOCUMENTATION SUGGESTION
===============================================================================

Suggested filename:

    Bottom_View_of_Binary_Tree.cpp

Suggested folder:

    DSA-journey-2026/
        Problems-Phase-01/
            Trees/
                Views/
                    Top_View_of_Binary_Tree.cpp
                    Bottom_View_of_Binary_Tree.cpp

Suggested commit message:

    Add detailed Bottom View of Binary Tree solution and revision notes

Suggested README entry:

    Problem: Bottom View of Binary Tree
    Platform: GeeksforGeeks
    Approach: BFS + Horizontal Distance + Ordered Map
    Time Complexity: O(n log n)
    Auxiliary Space: O(n)
    Status: Accepted

===============================================================================
                         END OF REVISION FILE
===============================================================================
*/
