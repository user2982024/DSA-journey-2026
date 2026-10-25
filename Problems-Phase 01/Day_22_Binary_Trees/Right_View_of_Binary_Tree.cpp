
/*
===============================================================================
PROBLEM: RIGHT VIEW OF BINARY TREE
Platform: GeeksforGeeks
Language: C++
Topic: Binary Trees | DFS | Recursion | Tree Traversal
===============================================================================

IMPORTANT REVISION NOTE
-----------------------
This file explains the submitted solution in detail, including why the
right-first recursive traversal returns the Right View of a binary tree.

The submitted algorithm is correct for a single call on a fresh Solution
object. One robustness improvement is to use a local answer vector in
rightView(), rather than retaining ans as a member variable. That prevents
old values from remaining if the same Solution object is reused for another
test case.

===============================================================================
1. PROBLEM STATEMENT
===============================================================================

Given the root of a binary tree, return the nodes visible when the tree is
viewed from its right side, from top to bottom.

The right view contains the rightmost visible node at each depth/level.

Example:

                 1
               /   \
              2     3
               \     \
                5     4

Right view: [1, 3, 4]

Why?
- Level 0: only node 1 exists, so 1 is visible.
- Level 1: nodes 2 and 3 exist; from the right, node 3 is visible.
- Level 2: nodes 5 and 4 exist; from the right, node 4 is visible.

The answer includes at most one node per level.

===============================================================================
2. SUBMITTED CODE
===============================================================================

/*
Definition for Node
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
  private:
    vector<int> ans;
    int level = 0;
    
    void func(Node* root, int level, vector<int> &ans) {
        if (root == nullptr) {
            return;
        }
        
        if (ans.size() == level) {
            ans.push_back(root->data);
        }
        
        func(root->right, level + 1, ans);
        func(root->left, level + 1, ans);
    }
    
  public:
    vector<int> rightView(Node *root) {
        //  code here
        func(root, level, ans);
        return ans;
    }
};

===============================================================================
3. CORE IDEA
===============================================================================

The solution uses Depth-First Search (DFS) with recursion.

For the Right View, visit the RIGHT child before the LEFT child:

    func(root->right, level + 1, ans);
    func(root->left, level + 1, ans);

This order is the key.

When we visit a node for the first time at a particular level, it is the
rightmost reachable node at that level under this right-first traversal.
We record it. Any other node later reached at the same level is ignored.

For the Left View, the corresponding strategy is:
    visit left first, then right.

For the Right View, reverse the order:
    visit right first, then left.

===============================================================================
4. UNDERSTANDING THE PARAMETERS
===============================================================================

A) Node* root
-------------

This is a pointer to the current node being processed.

At the beginning, root is the root of the entire tree. During recursion, root
becomes the right or left child of the current node.

B) int level
------------

This represents the depth of the current node.

We start the root at level 0:
- Root is at level 0.
- Its children are at level 1.
- Its grandchildren are at level 2.
- And so on.

Every recursive call passes level + 1 because a child is one level below its
parent.

C) vector<int>& ans
-------------------

This is a reference to the answer vector.

The ampersand (&) means the function uses the same vector rather than creating
a separate copy for every recursive call. Therefore, when a recursive call
adds a value, that value remains in the shared answer vector.

The vector stores node DATA (integers), not Node pointers.

===============================================================================
5. THE BASE CASE
===============================================================================

    if (root == nullptr) {
        return;
    }

A null pointer means there is no node at this position.

For example, a leaf node has no left or right child. The function eventually
calls itself with nullptr for those missing children. The base case stops
recursion immediately for those calls.

Without this base case, the function could try to access root->data when root
is nullptr, causing undefined behavior or a crash.

Notice that this base case does not add anything to ans. A missing child is
not a node and cannot appear in the view.

===============================================================================
6. WHY DOES ans.size() == level WORK?
===============================================================================

    if (ans.size() == level) {
        ans.push_back(root->data);
    }

This is the central condition.

The answer vector contains one value for each level discovered so far. Because
the root starts at level 0, the vector's size and the next unrecorded level
match:

Before processing level 0:
    ans.size() == 0

Before recording the first visible node at level 0:
    level == 0
    ans.size() == 0
    Condition is true, so record the root.

Before recording the first visible node at level 1:
    level == 1
    ans.size() == 1
    Condition is true, so record the first node reached at level 1.

Before recording the first visible node at level 2:
    level == 2
    ans.size() == 2
    Condition is true, so record the first node reached at level 2.

Suppose we later reach another node at level 2. The answer already contains
values for levels 0, 1, and 2, so ans.size() is 3, while level is 2:

    ans.size() == 3
    level == 2

The condition is false, so this later node is not added.

Why is the first node reached at each level the rightmost one?
Because the recursion explores the right subtree before the left subtree.
Thus, among nodes at the same depth, the right-side candidates are explored
first.

Important: this technique relies on both facts together:
1. The traversal visits RIGHT before LEFT.
2. A node is recorded only when ans.size() == level.

Changing only one of these details can change the result or break the logic.

===============================================================================
7. LINE-BY-LINE WALKTHROUGH
===============================================================================

Member variables:

    vector<int> ans;
    int level = 0;

- ans stores the answer.
- level is initialized to zero.
- The function also has a parameter named level. That parameter is the value
  actually used inside func(). The member variable is unnecessary; the public
  method could simply call func(root, 0, ans).

Helper function:

    void func(Node* root, int level, vector<int> &ans)

- Returns no value (void).
- Receives the current node.
- Receives the current depth.
- Receives the shared answer vector by reference.

Base case:

    if (root == nullptr) {
        return;
    }

Stop when the current pointer does not point to a node.

Record the visible node:

    if (ans.size() == level) {
        ans.push_back(root->data);
    }

If this is the first node visited at this depth, store its data.

Right recursive call:

    func(root->right, level + 1, ans);

Explore the right subtree first. This makes the first visited node at each
depth the rightmost candidate.

Left recursive call:

    func(root->left, level + 1, ans);

After exploring the right subtree, explore the left subtree. If a level was
already represented in ans, nodes found here will not be added.

Public method:

    vector<int> rightView(Node *root) {
        func(root, level, ans);
        return ans;
    }

Start the recursion at the root and return the collected values.

===============================================================================
8. DRY RUN
===============================================================================

Use this tree:

                 1
               /   \
              2     3
               \     \
                5     4

Initial state:
    ans = []
    Start func(1, 0, ans)

Step 1: Visit node 1 at level 0
--------------------------------
root is not nullptr.
ans.size() is 0 and level is 0.
Condition is true.
Add 1.

    ans = [1]

Then visit the right child first: node 3 at level 1.

Step 2: Visit node 3 at level 1
--------------------------------
ans.size() is 1 and level is 1.
Condition is true.
Add 3.

    ans = [1, 3]

Visit node 3's right child first: node 4 at level 2.

Step 3: Visit node 4 at level 2
--------------------------------
ans.size() is 2 and level is 2.
Condition is true.
Add 4.

    ans = [1, 3, 4]

Node 4 has no children. Calls with nullptr return immediately.
The recursion now backtracks to node 3, then explores node 3's left child,
which is nullptr. It then backtracks to node 1 and explores node 1's left
subtree, beginning at node 2.

Step 4: Visit node 2 at level 1
--------------------------------
ans.size() is 3 and level is 1.
Condition is false.
Do not add node 2 because level 1 already has node 3.

    ans = [1, 3, 4]

Node 2 has no right child, so the right call returns. Its left child is also
nullptr, so the left call returns.

Step 5: Visit node 5 at level 2
--------------------------------
Node 5 is reached as the right child of node 2.
ans.size() is 3 and level is 2.
Condition is false.
Do not add node 5 because level 2 already has node 4.

    ans = [1, 3, 4]

Final answer:
    [1, 3, 4]

The key observation is that node 4 was reached before node 5 at level 2,
because the algorithm explores right branches before left branches.

===============================================================================
9. RECURSION AND BACKTRACKING
===============================================================================

The calls are conceptually:

    func(1, 0)
      func(3, 1)
        func(4, 2)
          func(nullptr, 3) -> return
          func(nullptr, 3) -> return
      func(2, 1)
        func(nullptr, 2) -> return
        func(5, 2)
          func(nullptr, 3) -> return
          func(nullptr, 3) -> return

The exact child-call arrangement depends on each node's left and right links;
the important traversal order is root, right subtree, left subtree.

When a recursive call returns, execution resumes at the next statement in its
parent call. This is recursion backtracking. The algorithm does not remove
values from ans while backtracking, because ans is the final list of visible
nodes and should keep the first selected node for every level.

===============================================================================
10. WHY THE ALGORITHM IS CORRECT
===============================================================================

For each level, the algorithm records only the first node it encounters:
ans.size() == level is true only when no answer has yet been recorded for
that level.

The traversal explores right children before left children. Therefore, nodes
in right-side branches at a given depth are visited before nodes in left-side
branches at that same depth. The first node encountered at each depth is
therefore the rightmost visible node for that level.

Each level contributes at most one value, and every non-empty level is
visited. Thus, the returned vector is the Right View from top to bottom.

===============================================================================
11. EDGE CASES
===============================================================================

1. Empty tree

       root = nullptr

   The first call returns immediately. The answer is [].

2. One-node tree

       1

   Only the root is recorded. Answer: [1].

3. Only right children

       1
        \
         2
          \
           3

   Each node is the only node at its level. Answer: [1, 2, 3].

4. Only left children

       1
      /
     2
    /
   3

   Even though the tree has no right children, each node is the only node at
   its level. Answer: [1, 2, 3].

5. A level has nodes on both sides

       1
      / \
     2   3

   Node 3 is visited before node 2, so answer is [1, 3].

6. A right-side branch ends early

       1
      / \
     2   3
    /
   4

   At level 2, node 4 may be the only node, so it must be included even though
   it belongs to the left subtree. The view is [1, 3, 4].

This last case is important: the Right View does not mean “follow right
pointers only.” It means select the rightmost node at every depth. If there
is no node on the right at a particular depth, a node from the left subtree
can still be visible.

===============================================================================
12. TIME AND SPACE COMPLEXITY
===============================================================================

Time complexity: O(n)

Every node is visited once, and the work done at each node is constant apart
from the vector append, which is amortized O(1). Therefore, total time is O(n),
where n is the number of nodes.

Auxiliary recursion stack: O(h)

The maximum number of active recursive calls is proportional to the height h
of the tree.
- Balanced tree: h is O(log n).
- Skewed tree: h is O(n).

Output space: O(w)

The answer vector stores one value per level, so it contains at most h + 1
values when the root's level is 0. It is common to state the output space as
O(h), or O(n) in the worst case.

Overall space including the recursion stack and output is O(n) in the worst
case.

===============================================================================
13. COMMON MISTAKES
===============================================================================

Mistake 1: Visiting left before right
-------------------------------------
That produces the Left View with this same first-node-per-level technique,
not the Right View.

Mistake 2: Thinking the Right View means only following right pointers
----------------------------------------------------------------------
Wrong. A left-subtree node can be visible when no node farther right exists
at that depth.

Mistake 3: Recording every node
-------------------------------
The condition ans.size() == level ensures only one node is stored per level.

Mistake 4: Using level incorrectly
----------------------------------
The root must start at level 0, and each child must receive level + 1.

Mistake 5: Passing ans by value
-------------------------------
If the parameter were vector<int> ans instead of vector<int>& ans, recursive
calls could modify separate copies rather than one shared answer.

Mistake 6: Forgetting the nullptr base case
-------------------------------------------
A recursive call can reach a missing child. Always stop when root is nullptr.

Mistake 7: Keeping ans as a member without resetting it
------------------------------------------------------
If the same Solution object is reused, old results may remain. Prefer a local
answer vector, or explicitly clear the member before starting a new traversal.

===============================================================================
14. CLEANER / RECOMMENDED IMPLEMENTATION
===============================================================================

This version keeps the answer local to rightView(), starts explicitly at
level 0, and avoids unnecessary member variables:

class Solution {
  private:
    void func(Node* root, int level, vector<int>& ans) {
        if (root == nullptr) {
            return;
        }

        if (ans.size() == level) {
            ans.push_back(root->data);
        }

        // Right first: first node seen at each level is rightmost.
        func(root->right, level + 1, ans);
        func(root->left, level + 1, ans);
    }

  public:
    vector<int> rightView(Node* root) {
        vector<int> ans;
        func(root, 0, ans);
        return ans;
    }
};

Why is this slightly safer?
- Each call to rightView() creates a fresh vector.
- No previous test case's values can remain in ans.
- There is no separate member variable named level.
- The starting depth of 0 is explicit.

===============================================================================
15. DFS APPROACH VS BFS APPROACH
===============================================================================

DFS approach used here:
- Uses recursion.
- Visits right subtree before left subtree.
- Stores the first node reached at each depth.
- Uses a vector size check to know whether that level is already recorded.

BFS alternative:
- Uses a queue to process nodes level by level.
- At each level, the rightmost node can be selected directly.
- Often easier to visualize by levels, but requires explicit queue processing.

Both approaches can solve the Right View in O(n) time.

===============================================================================
16. QUICK REVISION QUESTIONS
===============================================================================

Q1. Why does the recursive function visit the right child first?
A. So the rightmost candidate at each level is encountered first.

Q2. What does level represent?
A. The depth of the current node, with root at level 0.

Q3. Why pass ans by reference?
A. All recursive calls need to update the same answer vector.

Q4. Why use ans.size() == level?
A. It is true when the answer has not yet recorded a node for this level.

Q5. Does the Right View contain only nodes reached by following right pointers?
A. No. It contains the rightmost node at each depth, even if that node is in
   the left subtree.

Q6. What is the time complexity?
A. O(n), because every node is visited once.

Q7. What is the recursion-stack space?
A. O(h), where h is the height of the tree.

Q8. What is the difference between Left View and Right View in this pattern?
A. Left View traverses left then right; Right View traverses right then left.

===============================================================================
17. FINAL TAKEAWAY
===============================================================================

Remember this compact pattern:

    if (root == nullptr) return;

    if (ans.size() == level)
        ans.push_back(root->data);

    func(root->right, level + 1, ans);
    func(root->left, level + 1, ans);

The order of DFS determines which side is prioritized. Right-first DFS plus
“record the first node at each level” gives the Right View.

Your main reasoning point to retain:
The algorithm does not search for a node whose right pointer is non-null. It
uses traversal order to make sure the first node visited at every depth is the
rightmost one available at that depth.
===============================================================================
