
/*
===============================================================================
PROBLEM: Sum of Binary Tree
PLATFORM: GeeksforGeeks (GFG)
TOPIC: Binary Trees | Recursion | Depth-First Search (DFS)
PURPOSE: Detailed revision notes for understanding, explaining, and recalling
         the recursive solution.
===============================================================================

1. PROBLEM STATEMENT
--------------------
Given the root of a binary tree, return the sum of the data values stored in
all nodes of the tree.

Every node must contribute its value exactly once.

Example tree:

          1
         / \
        2   3
       / \
      4   5

The sum is:

    1 + 2 + 3 + 4 + 5 = 15

Expected return value: 15

Important distinction:
- Size of a binary tree counts how many nodes exist.
- Sum of a binary tree adds the data values stored in those nodes.

For example, the tree above has size 5 and sum 15.

2. NODE STRUCTURE
-----------------
A node contains:
- data: the value stored at the node.
- left: pointer to the left child.
- right: pointer to the right child.

A pointer equal to nullptr means that child does not exist.

The recursive function receives a Node* root:
- If root points to a node, that node and its subtrees are part of the tree
  currently being processed.
- If root == nullptr, the current subtree is empty.

3. CORE RECURSIVE IDEA
----------------------
The sum of a tree can be calculated by adding three things:

    Sum(tree) = root->data
                + Sum(left subtree)
                + Sum(right subtree)

In code:

    int leftSum = sumBT(root->left);
    int rightSum = sumBT(root->right);
    return root->data + leftSum + rightSum;

Why does this work?
1. Add the value at the current root.
2. Ask recursion to calculate the sum of the entire left subtree.
3. Ask recursion to calculate the sum of the entire right subtree.
4. Add all three results and return the total to the caller.

Each recursive call solves the same problem on a smaller subtree.

4. BASE CASE: WHY nullptr RETURNS 0
-----------------------------------
    if (root == nullptr) {
        return 0;
    }

A nullptr represents an empty subtree, so it contains no node values to add.
The sum of no values is 0.

Returning 0 is important because it allows the parent node to add the result
without needing special handling for missing children.

Example: if a node has no left child, then:

    leftSum = sumBT(nullptr) = 0

So the node's value plus its existing right-subtree sum is calculated normally.

Do not return 1 here: 1 is useful for counting a real node in a size problem,
but this function adds node values. An empty subtree contributes zero.

5. THE ORIGINAL SOLUTION
------------------------
The submitted solution is preserved below.

    int sumBT(Node* root) {
        if (root == nullptr) {
            return 0;
        }

        int leftSum = sumBT(root->left);
        int rightSum = sumBT(root->right);

        return root->data + leftSum + rightSum;
    }

This solution is correct. No logic change is required.

6. LINE-BY-LINE EXPLANATION
---------------------------

Line 1:
    int sumBT(Node* root)

Defines a function that receives a pointer to the root of the current subtree
and returns an int: the sum of the values in that subtree.

Line 2:
    if (root == nullptr)

Checks whether the current subtree is empty. This check must happen before
accessing root->data, root->left, or root->right. Accessing members through a
nullptr would be invalid.

Line 3:
    return 0;

Stops this recursive call and reports that an empty subtree contributes zero
to the total sum. This is the base case.

Line 4:
    int leftSum = sumBT(root->left);

Recursively computes the sum of the entire left subtree and stores the
returned value in leftSum. The call does not merely add the left child's
value; it includes every node below that child as well.

Line 5:
    int rightSum = sumBT(root->right);

Recursively computes the sum of the entire right subtree and stores the
returned value in rightSum.

Line 6:
    return root->data + leftSum + rightSum;

Adds the current node's value to the two subtree sums, then returns that
combined total to the caller.

Why is root->data included directly?
The recursive calls calculate only the left and right subtrees. Neither call
includes the current root node, so root->data must be added here.

7. COMPLETE DRY RUN
-------------------
Use this tree:

          1
         / \
        2   3
       / \
      4   5

The answer should be 15.

The function starts with sumBT(node 1).

A. At node 1
------------
- root->data is 1.
- It calls sumBT(node 2) for the left subtree.
- It calls sumBT(node 3) for the right subtree.
- It waits for both recursive calls to return before calculating its answer.

B. At node 2
------------
- root->data is 2.
- It calls sumBT(node 4) for the left subtree.
- It calls sumBT(node 5) for the right subtree.
- It waits for both calls to return.

C. At node 4
------------
- root->data is 4.
- Its left child is nullptr, so sumBT(nullptr) returns 0.
- Its right child is nullptr, so sumBT(nullptr) returns 0.
- It returns 4 + 0 + 0 = 4.

Therefore, node 2 receives leftSum = 4.

D. At node 5
------------
- root->data is 5.
- Its left and right children are nullptr.
- Both recursive calls return 0.
- It returns 5 + 0 + 0 = 5.

Node 2 now has:
- leftSum = 4
- rightSum = 5

It returns 2 + 4 + 5 = 11.

E. At node 3
------------
- root->data is 3.
- Its left child is nullptr, so the left-subtree sum is 0.
- Its right child is nullptr, so the right-subtree sum is 0.
- It returns 3 + 0 + 0 = 3.

F. Back at node 1
-----------------
Node 1 now has:
- leftSum = 11 (sum of nodes 2, 4, and 5)
- rightSum = 3 (sum of node 3)

It returns:

    1 + 11 + 3 = 15

Final answer: 15

8. RECURSION AND RETURN VALUES
------------------------------
A useful mental model is that each function call is responsible for one
subtree and returns one integer to its parent call.

The calls first travel downward until they reach nullptr pointers. Then return
values travel upward:

    sumBT(nullptr) -> 0
    sumBT(node 4)  -> 4
    sumBT(node 5)  -> 5
    sumBT(node 2)  -> 11
    sumBT(node 3)  -> 3
    sumBT(node 1)  -> 15

The exact execution explores the left subtree before the right subtree
because the left recursive call appears first in the code.

The function cannot calculate the current node's final total until both
recursive calls have returned. This is often called postorder-style
processing: process the left subtree, process the right subtree, then combine
their results at the current node.

9. WHY EVERY NODE IS COUNTED EXACTLY ONCE
-----------------------------------------
For any non-empty subtree:
- root->data contributes the current root's value once.
- leftSum contains every value in the left subtree.
- rightSum contains every value in the right subtree.

A binary tree's left and right subtrees do not overlap, and neither contains
the current root. Therefore, adding these three parts includes every node
exactly once without double-counting.

10. EDGE CASES
--------------
A. Empty tree

    root = nullptr

The base case returns 0. This is correct because there are no values.

B. One node with value 7

        7

The left and right calls each return 0:

    7 + 0 + 0 = 7

C. A node with only a left child

        5
       /
      8

The total is 5 + 8 = 13. The missing right subtree contributes 0.

D. A node with only a right child

      5
       \
        8

The total is also 13. The missing left subtree contributes 0.

E. Values include zero

        0
       / \
      4   6

The sum is 0 + 4 + 6 = 10. A node with value zero is still a real node, but
its contribution to the sum is zero.

F. Negative values

        2
       / \
     -5   4

The sum is 2 + (-5) + 4 = 1. The algorithm works with negative values too,
provided the total fits in the return type int.

G. All node values are negative

The algorithm still adds all values normally. Do not initialize the answer
to zero and accidentally skip negative contributions; this recursive formula
already handles them correctly.

11. COMMON MISTAKES TO AVOID
----------------------------
1. Forgetting the base case
   Without the nullptr check, recursion would continue into empty children
   and eventually attempt to access a null pointer.

2. Returning 1 for nullptr
   That is a common base case for counting nodes only when the recursive
   formula is designed around it in a different way. For this sum function,
   an empty subtree contributes 0.

3. Forgetting root->data
   Returning only leftSum + rightSum omits the current node's value.

4. Including only one subtree
   Using root->data + leftSum or root->data + rightSum ignores values in the
   other subtree.

5. Adding the child pointer instead of its subtree sum
   The task is to add data values, not pointer addresses. Use recursive
   results and root->data.

6. Confusing sum with size
   Size returns 1 + leftSize + rightSize because each real node counts as one.
   Sum returns root->data + leftSum + rightSum because each node contributes
   its stored value.

7. Trying to use one shared accumulator unnecessarily
   A global or reference accumulator could solve this problem, but the
   returned-value approach is simple and naturally combines subtree results.

8. Integer overflow
   The function returns int. If constraints allow a sum outside the int range,
   a wider return type such as long long would be needed. Follow the platform's
   required signature and constraints.

12. CORRECTNESS INTUITION / PROOF
---------------------------------
We can reason by induction on the number of nodes in a subtree.

Base case:
If the subtree is empty, root is nullptr and the function returns 0. That is
the correct sum of an empty tree.

Recursive case:
Suppose root is not nullptr. The left and right subtrees are smaller trees.
Assume the recursive function correctly returns the sum of each smaller
subtree. The current call returns:

    root->data + leftSum + rightSum

This combines the current root's value with the correct sum of each subtree.
Every node in the current tree is therefore included exactly once, so the
returned result is correct.

13. TIME AND SPACE COMPLEXITY
-----------------------------
Time complexity: O(n)

The function visits each of the n nodes once. At each node, the work outside
the recursive calls is constant-time addition and assignment.

Auxiliary space: O(h)

Recursive calls use the call stack. The maximum number of simultaneously
active calls follows the tree height h.

- Balanced tree: h = O(log n), so auxiliary stack space is O(log n).
- Highly skewed tree: h = O(n), so auxiliary stack space is O(n).

The returned integer values and local variables use constant space per active
call; the recursion stack is the source of the O(h) auxiliary space.

14. COMPARISON WITH RELATED TREE RECURSION PROBLEMS
---------------------------------------------------
Tree size:

    return 1 + leftSize + rightSize;

Each real node contributes 1 because size counts nodes.

Tree sum:

    return root->data + leftSum + rightSum;

Each node contributes its stored data value.

Tree height:
The formula depends on the platform's definition of height. If height is
counted in nodes, a common recurrence is 1 + max(leftHeight, rightHeight)
with an appropriate empty-tree base case. If height is counted in edges, the
base case and formula are adjusted accordingly.

The shared structure is:
1. Define what an empty subtree returns.
2. Recursively solve the left subtree.
3. Recursively solve the right subtree.
4. Combine both results with information from the current node.

15. SELF-REVISION QUESTIONS
---------------------------
Try answering these without looking at the solution:

1. Why does sumBT(nullptr) return 0?
2. Why do we add root->data directly?
3. What exactly is stored in leftSum?
4. Does leftSum include the current root's value?
5. In what order are the left subtree, right subtree, and current node handled?
6. What is the sum of a single-node tree containing -9?
7. What is the difference between the size and sum of a tree?
8. What are the time and auxiliary-space complexities?
9. Why does a missing child not require a separate if statement?
10. What could happen if the total exceeds the range of int?

16. QUICK REVISION SUMMARY
--------------------------
- Problem: add the values of all nodes in a binary tree.
- Base case: nullptr returns 0 because an empty subtree has no values.
- Recursive step: sum left subtree + sum right subtree + current node value.
- Formula: Sum(tree) = root->data + Sum(left) + Sum(right).
- Time: O(n), because every node is visited once.
- Auxiliary space: O(h), because of recursive call-stack depth.
- The solution uses DFS recursion and combines results while recursion returns.

17. ORIGINAL GFG-STYLE SOLUTION
-------------------------------
The code below preserves the submitted algorithm and variable names.

===============================================================================
*/

class Solution {
  public:
    int sumBT(Node* root) {
        // An empty subtree contains no node values.
        if (root == nullptr) {
            return 0;
        }

        // Calculate the sum of every node in the left subtree.
        int leftSum = sumBT(root->left);

        // Calculate the sum of every node in the right subtree.
        int rightSum = sumBT(root->right);

        // Add this node's value to both subtree sums.
        return root->data + leftSum + rightSum;
    }
};

/*
===============================================================================
END OF REVISION NOTES
===============================================================================
*/
