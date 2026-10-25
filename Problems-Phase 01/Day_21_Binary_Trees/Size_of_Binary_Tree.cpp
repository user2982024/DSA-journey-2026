
/*
================================================================================
                         DSA JOURNEY — C++ SOLUTION NOTES
================================================================================

Problem Title : Size of Binary Tree
Platform      : GeeksforGeeks
Topic         : Binary Trees
Core Concepts : Recursion, Depth-First Search (DFS), Base Cases, Return Values
Suggested Path: DSA-journey-2026 / Trees / Size_of_Binary_Tree.cpp

PURPOSE OF THIS FILE
--------------------
This file is designed to be a complete revision note for the "Size of Binary
Tree" problem. The aim is not only to remember the final code, but also to
recall:
  - what the problem asks,
  - how to recognize the recursive structure,
  - why the base case returns 0,
  - why we add 1 for the current node,
  - how recursive calls return their results,
  - how the call stack evaluates the function,
  - how to dry-run the solution,
  - which mistakes are common,
  - and how to analyze time and auxiliary space complexity.

The solution below preserves the logic and variable names from my submitted
solution.

================================================================================
1. PROBLEM DESCRIPTION
================================================================================

Given the root pointer of a binary tree, calculate and return the total number
of nodes present in the tree.

The "size" of a binary tree means the number of nodes in the entire tree.
Every node is counted exactly once.

For example, in this tree:

                 1
                / \
               2   3
              /
             4

The nodes are: 1, 2, 3, 4

Therefore, the size of the tree is 4.

Expected result:
    4

IMPORTANT:
- We are counting nodes, not edges.
- We are not calculating the height or depth of the tree.
- We are not summing the values stored in the nodes.
- The actual values (1, 2, 3, 4, etc.) do not affect the count.
- Each existing node contributes exactly 1 to the total size.

If the node values were 10, 20, 30, and 40, the answer would still be 4.

--------------------------------------------------------------------------------
2. UNDERSTAND THE NODE STRUCTURE
--------------------------------------------------------------------------------

The platform provides a node structure similar to this:

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

Each node contains three important parts:

1. data
   The integer value stored inside the node.

2. left
   A pointer to the left child, if one exists.

3. right
   A pointer to the right child, if one exists.

If a child does not exist, its pointer is nullptr.

For this problem, we do not need to inspect the actual data value. We only
need to determine how many nodes exist. A node containing data = 100 contributes
exactly as much to the size as a node containing data = -7: one node.

--------------------------------------------------------------------------------
3. EDGE CASES TO UNDERSTAND BEFORE CODING
--------------------------------------------------------------------------------

CASE A — Empty tree

    root = nullptr

There are no nodes, so the answer is 0.

CASE B — A single node

        10

There is one node, so the answer is 1.

CASE C — A root with two children

        10
       /  \
      20   30

There are three nodes, so the answer is 3.

CASE D — A left-skewed tree

        10
       /
      20
     /
    30

There are three nodes, so the answer is 3. The tree does not need to be
balanced for this algorithm to work.

CASE E — A right-skewed tree

    10
      \
       20
         \
          30

There are three nodes, so the answer is 3.

CASE F — A tree with missing children

        10
       /  \
      20   30
     /
    40

There are four nodes. Missing children do not contribute anything; each
nullptr subtree contributes 0.

The recursive solution naturally handles all these cases without needing
separate code for every tree shape.

================================================================================
4. CORE IDEA: COUNT THE ROOT, THEN COUNT BOTH SUBTREES
================================================================================

For any non-empty binary tree, the total number of nodes is:

    Size(tree) = 1 + Size(left subtree) + Size(right subtree)

This formula is the heart of the solution.

Why is there a +1?
------------------
Because we must count the current root node itself.

Why count the left subtree?
---------------------------
The left subtree may contain zero, one, or many nodes. We ask the same
function to count them.

Why count the right subtree?
----------------------------
The right subtree may also contain zero, one, or many nodes. We ask the same
function to count them too.

Why can the same function solve a subtree?
-------------------------------------------
A subtree is itself a binary tree. The rules for counting its nodes are
identical to the rules for counting the entire tree.

This is the recursive insight:
    A large problem can be solved by solving smaller problems of the same kind.

The current node contributes 1, and the two recursive calls provide the counts
for the two smaller trees.

================================================================================
5. BASE CASE — WHY nullptr RETURNS 0
================================================================================

The base case is:

    if (root == nullptr) {
        return 0;
    }

A nullptr pointer means there is no node at that position. If there is no node,
there is nothing to count, so the count is 0.

The base case also stops the recursion.

Consider a leaf node:

        4
       / \
   null   null

When getSize(4) is called, the function asks for:
    getSize(4->left)
    getSize(4->right)

Both child pointers are nullptr. Each recursive call returns 0.

So:
    getSize(4) = 1 + 0 + 0 = 1

This is exactly right: node 4 exists, but its children do not.

What if we forgot the base case?
--------------------------------
The function would have no proper rule for handling missing children. It would
try to continue recursively without reaching the necessary stopping condition.
Every recursive tree function needs an appropriate base case.

Why not return 1 for nullptr?
-----------------------------
Because nullptr is not a node. Returning 1 would incorrectly count every
missing child as if it were a real node.

================================================================================
6. MY SUBMITTED SOLUTION
================================================================================

The following is my original solution, preserving its structure and variable
names:

    class Solution {
      public:
        int getSize(Node* root) {
            // code here
            if (root == nullptr) {
                return 0;
            }

            int leftSize = getSize(root->left);
            int rightSize = getSize(root->right);

            return 1 + leftSize + rightSize;
        }
    };

The solution is short because the recursive relationship captures the entire
problem. The important work is understanding why each line is necessary.

================================================================================
7. LINE-BY-LINE EXPLANATION
================================================================================

LINE 1:
    int getSize(Node* root)

This declares a function named getSize.

- It receives a pointer named root.
- root identifies the root node of the current tree or subtree.
- The return type is int because the number of nodes is an integer.

The function can be called on the original tree or on any subtree. That is
what makes the recursive approach possible.

LINE 2:
    if (root == nullptr)

This checks whether the current tree/subtree is empty.

Remember that a recursive call does not always receive the original root.
For example, getSize(root->left) receives the left child as its own root
argument. If that child is missing, the argument is nullptr.

LINE 3:
    return 0;

An empty tree has zero nodes. The function immediately returns 0 for this case.

LINE 4:
    int leftSize = getSize(root->left);

This recursively counts every node in the left subtree.

The returned integer is stored in leftSize. It represents the complete count
of nodes below the current node on its left side, including the left child
itself if that child exists.

LINE 5:
    int rightSize = getSize(root->right);

This does the same thing for the right subtree. Its returned count is stored
in rightSize.

LINE 6:
    return 1 + leftSize + rightSize;

This combines the three contributions:

    1          = the current node
    leftSize   = all nodes in the left subtree
    rightSize  = all nodes in the right subtree

The current node is not included in leftSize or rightSize. Therefore, the +1
is needed to count it.

The returned value travels back to the recursive call that requested it.

================================================================================
8. COMPLETE DRY RUN — EXAMPLE TREE
================================================================================

Use this tree:

                 1
                / \
               2   3
              /
             4

We want:
    getSize(1)

We can expand the calculation:

    getSize(1)
      = 1 + getSize(2) + getSize(3)

To calculate getSize(2):

    getSize(2)
      = 1 + getSize(4) + getSize(nullptr)

To calculate getSize(4):

    getSize(4)
      = 1 + getSize(nullptr) + getSize(nullptr)
      = 1 + 0 + 0
      = 1

Now calculate node 2:

    getSize(2)
      = 1 + 1 + 0
      = 2

Node 3 has no children:

    getSize(3)
      = 1 + 0 + 0
      = 1

Finally, calculate node 1:

    getSize(1)
      = 1 + getSize(2) + getSize(3)
      = 1 + 2 + 1
      = 4

Final answer:
    4

Notice that we do not count the same node twice. The left subtree count covers
nodes 2 and 4; the right subtree count covers node 3; and the outer +1 counts
node 1.

================================================================================
9. CALL-STACK WALKTHROUGH
================================================================================

Recursion uses the program's call stack. Each function call pauses while it
waits for the recursive calls it made to return.

For the tree:

                 1
                / \
               2   3
              /
             4

A simplified sequence is:

1. Call getSize(1).
   It cannot calculate the final answer until the left and right subtree
   counts return.

2. Call getSize(2) to count node 1's left subtree.
   This call also waits for its children.

3. Call getSize(4).
   Node 4 is a leaf. Its two child calls receive nullptr and return 0.
   Therefore, getSize(4) returns 1.

4. The missing right child of node 2 returns 0.
   Now getSize(2) can return 1 + 1 + 0 = 2.

5. The right subtree of node 1 is node 3.
   Its two missing children return 0, so getSize(3) returns 1.

6. The original call can now finish:
   getSize(1) returns 1 + 2 + 1 = 4.

Conceptually, calls go deeper into the tree until they hit the base case.
Then return values travel back up the call stack. This is often called
"unwinding" the recursion.

IMPORTANT:
The function does not need to store all nodes in a vector. Each recursive call
returns a count, and its caller combines the returned counts.

================================================================================
10. WHY THE CODE COUNTS EACH NODE EXACTLY ONCE
================================================================================

Every non-null node performs exactly one local contribution: +1.

The function then counts the left and right subtrees. Those subtrees contain
all descendants belonging to those sides.

For each node:
- the current node is counted by its own +1,
- descendants in the left subtree are counted by the left recursive call,
- descendants in the right subtree are counted by the right recursive call.

The left and right subtrees do not overlap, so their node sets are disjoint.
Every node belongs to exactly one of these parts: the current node, the left
subtree, or the right subtree.

Therefore, every node is counted exactly once.

================================================================================
11. COMMON MISTAKES AND HOW TO AVOID THEM
================================================================================

MISTAKE 1 — Forgetting the base case

Incorrect or incomplete recursive functions may continue into missing children
without a valid stopping condition.

Correction:
    if (root == nullptr) return 0;

MISTAKE 2 — Returning only leftSize + rightSize

If we wrote:

    return leftSize + rightSize;

we would omit the current node. A single-node tree would incorrectly return 0.

Correction:
    return 1 + leftSize + rightSize;

MISTAKE 3 — Returning 1 for nullptr

A missing child is not a node. Returning 1 would overcount the tree.

Correction:
    return 0;

MISTAKE 4 — Counting only one side

If we counted only the left subtree, every node in the right subtree would be
missed. The same issue occurs if we count only the right subtree.

Correction:
Count both:
    getSize(root->left)
    getSize(root->right)

MISTAKE 5 — Confusing size with height

Size asks: "How many nodes are in the tree?"
Height asks: "How many levels or edges are in the longest root-to-leaf path?"
Height definitions can vary by problem, but size always counts all nodes.

For the example tree with nodes 1, 2, 3, and 4:
    size = 4
The height is not 4.

MISTAKE 6 — Confusing size with sum of node values

For nodes with values 10, 20, and 30:
    size = 3
    sum of values = 60

The current solution counts nodes; it does not add their data values.

MISTAKE 7 — Thinking the original root stays the argument in every call

Each recursive call receives a different pointer:
    getSize(root->left)
    getSize(root->right)

Inside each call, its parameter named root refers to the root of that
particular subtree. This is normal function-parameter behavior.

================================================================================
12. TIME COMPLEXITY
================================================================================

Let n be the total number of nodes.

Time Complexity: O(n)

Reason:
Every non-null node is visited once. At each node, the function performs a
constant amount of work besides its two recursive calls:
- check whether the pointer is nullptr,
- make two recursive calls,
- add three integer values.

The total work therefore grows linearly with the number of nodes.

Even if the tree is skewed, each node is still visited once, so the time
complexity remains O(n).

================================================================================
13. AUXILIARY SPACE COMPLEXITY
================================================================================

Auxiliary Space Complexity: O(h), where h is the height of the tree.

The function uses recursion. Each active call occupies a stack frame until its
recursive calls return. The maximum number of simultaneously active calls is
proportional to the tree height.

Balanced tree:
- Height is O(log n).
- Maximum recursive stack space is O(log n).

Highly skewed tree:
- Height can be O(n).
- Maximum recursive stack space can be O(n).

We usually describe the auxiliary space as O(h), because that covers both
shapes.

The algorithm does not allocate an additional array, map, or queue. Its main
additional memory use comes from the recursive call stack.

================================================================================
14. RECURSION PATTERN TO REMEMBER
================================================================================

This problem follows a reusable pattern:

    if (subtree is empty) {
        return the base answer;
    }

    leftAnswer  = solve(left subtree);
    rightAnswer = solve(right subtree);

    return combine(current node, leftAnswer, rightAnswer);

For Size of Binary Tree:
    base answer = 0
    current node contribution = 1
    combine = addition

So:
    getSize(root) = 1 + getSize(root->left) + getSize(root->right)
for a non-null root.

This general structure appears in many tree problems. The base case and the
combination operation change depending on what the problem asks.

For example:
- Counting nodes: add 1 and both subtree counts.
- Summing values: add root->data and both subtree sums.
- Height: combine subtree heights using a maximum and an appropriate base case.
- Counting leaves: add 1 only when the current node is a leaf.

These are related patterns, not interchangeable formulas. Always derive the
base case and combination rule from the exact problem definition.

================================================================================
15. HOW TO RE-DERIVE THE SOLUTION DURING REVISION
================================================================================

If revisiting this problem after several weeks, do not start by memorizing
the code. Ask yourself these questions:

1. What does "size of a binary tree" mean?
   The total number of nodes.

2. What should an empty tree return?
   Zero, because there are no nodes.

3. If the current node exists, what must be counted?
   The current node, its left subtree, and its right subtree.

4. What does the left recursive call return?
   The number of nodes in the left subtree.

5. What does the right recursive call return?
   The number of nodes in the right subtree.

6. Why is there a +1?
   To count the current node itself.

7. What is the final formula?
   1 + leftSize + rightSize.

If you can answer these questions and reproduce the function, you understand
the logic rather than merely recognizing the code.

================================================================================
16. FINAL QUICK REVISION
================================================================================

PROBLEM:
Count all nodes in a binary tree.

BASE CASE:
nullptr -> 0

RECURSIVE STEPS:
1. Count the left subtree.
2. Count the right subtree.
3. Add 1 for the current node.

FORMULA:
    size = 1 + leftSize + rightSize

TIME:
    O(n)

AUXILIARY SPACE:
    O(h), due to the recursive call stack.

MAIN LESSON:
Each node contributes 1, and the recursive calls count all nodes in its two
subtrees.

================================================================================
17. GEEKSFORGEEKS SUBMISSION NOTE
================================================================================

The code is written in the GeeksforGeeks style, where the platform provides the
Node structure and the required environment.

For a standalone local C++ file, you would need to include the appropriate
standard headers and define the Node structure before the Solution class.
The online-judge submission normally expects only the requested class/method.

================================================================================
END OF NOTES
================================================================================
*/

class Solution {
  public:
    int getSize(Node* root) {
        // Base case: an empty tree has zero nodes.
        if (root == nullptr) {
            return 0;
        }

        // Recursively count every node in the left subtree.
        int leftSize = getSize(root->left);

        // Recursively count every node in the right subtree.
        int rightSize = getSize(root->right);

        // Count the current node and both of its subtrees.
        return 1 + leftSize + rightSize;
    }
};
