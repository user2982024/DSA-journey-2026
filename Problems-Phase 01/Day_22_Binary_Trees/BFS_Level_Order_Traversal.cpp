
/*
===============================================================================
PROBLEM: LEVEL ORDER TRAVERSAL OF A BINARY TREE
Platform: GeeksforGeeks
Language: C++
Topics: Binary Trees | Breadth-First Search (BFS) | Queue
===============================================================================

IMPORTANT REVISION NOTE
-----------------------
Your submitted algorithm is correct for a single call on a fresh Solution
object. It performs a standard level-order traversal: visit nodes from top to
bottom, and within each level from left to right.

One improvement: ans and q are member variables. If the same Solution object
is reused for multiple calls, old values can remain in the vector or queue.
A safer implementation creates both containers locally inside levelOrder().

===============================================================================
1. PROBLEM STATEMENT
===============================================================================

Given the root of a binary tree, return the values of its nodes in Level Order
Traversal.

Level order traversal means:
- Visit the root first.
- Then visit all nodes one level below the root, from left to right.
- Then visit all nodes on the next level, from left to right.
- Continue until every node has been visited.

Example tree:

                 1
               /   \
              2     3
             / \     \
            4   5     6

Level order output:

    [1, 2, 3, 4, 5, 6]

The result is a single vector, not a vector of vectors. The values are placed
in the order in which the nodes are visited.

===============================================================================
2. YOUR SUBMITTED CODE
===============================================================================

/* Structure of Binary Tree Node
class Node {
  public:
    int data;
    Node* left;
    Node* right;

    // Constructor
    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};*/

class Solution {
  private:
    vector<int> ans;
    queue<Node*> q;

  public:
    vector<int> levelOrder(Node *root) {
        // code here
        if (root == nullptr) {
            return {};
        }
        
        q.push(root);
        
        while (!q.empty()) {
            Node* node = q.front();
            ans.push_back(node->data);
            q.pop();
            
            if (node->left != nullptr) {
                q.push(node->left);
            }
            
            if (node->right != nullptr) {
                q.push(node->right);
            }
        }
        
        return ans;
    }
};

===============================================================================
3. CORE IDEA: BFS USING A QUEUE
===============================================================================

Your solution uses Breadth-First Search (BFS).

BFS explores a tree level by level. A queue is the natural data structure for
this because a queue follows FIFO:

    FIFO = First In, First Out

The first node added to the queue is the first node removed from it.

In C++:
- q.push(value) adds an item to the BACK of the queue.
- q.front() reads the item at the FRONT without removing it.
- q.pop() removes the item at the FRONT. It does not return that item.
- q.empty() is true when the queue has no elements.

The queue stores Node pointers:

    queue<Node*> q;

It does not store node values directly. Each queue entry points to a node,
which lets the algorithm access that node's data and its children.

The answer vector stores integers:

    vector<int> ans;

So the two containers have different responsibilities:
- q: nodes that still need to be processed.
- ans: node values already visited, in traversal order.

===============================================================================
4. UNDERSTANDING THE QUEUE
===============================================================================

Consider this tree:

           1
          / \
         2   3

Initially:
    q = []

After q.push(root):
    q = [1]

Read q.front():
    current node is 1

After q.pop():
    q = []

Then add node 1's children:
    q.push(2)
    q.push(3)

Now:
    q = [2, 3]

Because the queue is FIFO, node 2 will be processed before node 3. That
preserves left-to-right order at the same level.

Process node 2:
- Read node 2 from the front.
- Record its value.
- Remove it.
- Add any children it has to the rear.

Then process node 3 in the same way.

The queue controls the order in which nodes are visited.

===============================================================================
5. LINE-BY-LINE EXPLANATION
===============================================================================

A) Member variables

    vector<int> ans;
    queue<Node*> q;

ans:
- Stores the data of nodes in the order they are visited.

q:
- Stores pointers to nodes waiting to be processed.

Because these are member variables, they belong to the Solution object and
persist between calls on that same object. For reusable code, local variables
are safer; see the recommended implementation later in this file.

B) Public method

    vector<int> levelOrder(Node *root)

The function receives the root pointer and returns a vector of integers.

C) Empty-tree check

    if (root == nullptr) {
        return {};
    }

If root is nullptr, the tree has no nodes. The correct traversal result is an
empty vector, so the function returns {}.

This also prevents trying to push or access a nonexistent root node.

D) Start the traversal

    q.push(root);

Put the root into the queue because it is the first node to visit.

At this point, the queue contains one node: the root.

E) Continue while nodes are waiting

    while (!q.empty()) {

As long as the queue has nodes, there is still a node to process.

Each loop iteration processes exactly one node. The loop ends when every node
has been removed from the queue and processed.

F) Read the front node

    Node* node = q.front();

q.front() gives access to the pointer at the front of the queue. It does not
remove the pointer.

The pointer is stored in the local variable node so the code can read the
node's data and child pointers.

G) Record the node's value

    ans.push_back(node->data);

node->data accesses the integer stored in this node.

ans.push_back(...) appends that integer to the end of the result vector.

This is where the visited node's value enters the final answer.

H) Remove the processed node

    q.pop();

This removes the front entry from the queue.

Important: q.pop() does not return the removed node. That is why the code first
stores q.front() in node and then calls q.pop().

The pointer in node remains usable after q.pop(), because removing a pointer
from the queue does not delete the actual tree node.

I) Add the left child

    if (node->left != nullptr) {
        q.push(node->left);
    }

If a left child exists, enqueue it. If it is nullptr, do not enqueue anything.

J) Add the right child

    if (node->right != nullptr) {
        q.push(node->right);
    }

If a right child exists, enqueue it.

Why left before right?
Because level order traversal usually visits each level from left to right.
Enqueuing the left child before the right child preserves that order.

K) Return the answer

    return ans;

Once the queue is empty, all reachable nodes have been processed. Return the
vector of values collected in traversal order.

===============================================================================
6. COMPLETE DRY RUN
===============================================================================

Use this tree:

                 1
               /   \
              2     3
             / \     \
            4   5     6

Initial state:
    q   = []
    ans = []

Step 1: Enqueue root 1
----------------------
Execute:
    q.push(root);

State:
    q   = [1]
    ans = []

Step 2: Process node 1
----------------------
The queue is not empty.

    node = q.front();       // node points to 1
    ans.push_back(1);
    q.pop();

Then enqueue node 1's children, left first:
    q.push(2);
    q.push(3);

State:
    q   = [2, 3]
    ans = [1]

Step 3: Process node 2
----------------------
The front is node 2.

    node = q.front();
    ans.push_back(2);
    q.pop();

Node 2 has left child 4 and right child 5:
    q.push(4);
    q.push(5);

State:
    q   = [3, 4, 5]
    ans = [1, 2]

Notice that nodes 4 and 5 go BEHIND node 3, which was already waiting in the
queue. This is why the entire second level is processed before the third
level.

Step 4: Process node 3
----------------------
The front is node 3.

    ans.push_back(3);
    q.pop();

Node 3 has no left child. Its right child is 6, so enqueue 6.

State:
    q   = [4, 5, 6]
    ans = [1, 2, 3]

Step 5: Process node 4
----------------------
Node 4 is at the front.

    ans.push_back(4);
    q.pop();

Node 4 has no children.

State:
    q   = [5, 6]
    ans = [1, 2, 3, 4]

Step 6: Process node 5
----------------------
    ans.push_back(5);
    q.pop();

Node 5 has no children.

State:
    q   = [6]
    ans = [1, 2, 3, 4, 5]

Step 7: Process node 6
----------------------
    ans.push_back(6);
    q.pop();

Node 6 has no children.

State:
    q   = []
    ans = [1, 2, 3, 4, 5, 6]

Step 8: Stop
------------
The condition !q.empty() is now false, so the while loop ends.

Returned answer:
    [1, 2, 3, 4, 5, 6]

===============================================================================
7. WHY THE ORDER IS LEVEL BY LEVEL
===============================================================================

This is the most important BFS concept.

When node 1 is processed, its children 2 and 3 are added to the back:
    q = [2, 3]

When node 2 is processed, its children 4 and 5 are added after node 3:
    q = [3, 4, 5]

The queue already contains all nodes from the current level before the
children of those nodes are processed. Because FIFO removes older entries
first, the nodes at the current level are processed before their children.

That is why BFS naturally moves level by level.

The left-child-first enqueue order makes nodes within each level appear from
left to right.

===============================================================================
8. WHY DO WE CHECK FOR nullptr CHILDREN?
===============================================================================

These checks:

    if (node->left != nullptr)
    if (node->right != nullptr)

ensure that only real nodes are inserted into the queue.

Suppose node 3 has no left child. If we inserted nullptr into the queue, then
later this line could be unsafe:

    Node* node = q.front();
    ans.push_back(node->data);

If node were nullptr, node->data would be invalid to access.

By only enqueuing non-null children, every pointer removed from the queue
points to an actual tree node.

===============================================================================
9. EDGE CASES
===============================================================================

1. Empty tree

       root = nullptr

   The function returns [] immediately.

2. One-node tree

       1

   The root is enqueued, processed, and removed. It has no children.
   Result: [1].

3. Tree with only left children

       1
      /
     2
    /
   3

   Result: [1, 2, 3].

4. Tree with only right children

       1
        \
         2
          \
           3

   Result: [1, 2, 3].

5. A node has only a right child

       1
      /
     2
      \
       4

   Result: [1, 2, 4].

6. A node has only a left child

       1
        \
         3
        /
       5

   Result: [1, 3, 5].

The algorithm handles these cases because it checks each child independently.

===============================================================================
10. TIME COMPLEXITY
===============================================================================

Time complexity: O(n)

Let n be the number of nodes.

Every node is:
- Enqueued once.
- Removed from the queue once.
- Added to ans once.
- Checked for left and right children once.

Each operation takes O(1) time on average, so the total time complexity is
O(n).

===============================================================================
11. SPACE COMPLEXITY
===============================================================================

Queue space: O(w)

The queue can contain nodes from a level that are waiting to be processed.
The maximum number of queued nodes is proportional to the maximum width w of
the tree.

For a very wide tree, the queue can contain O(n) nodes in the worst case.

Output space: O(n)

The answer vector stores every node's value, so it contains n values.

Overall auxiliary space excluding the returned answer: O(w), which is O(n) in
the worst case.

If counting the output vector as well, total space is O(n).

Unlike the recursive DFS view solutions, this algorithm does not use a
recursive call stack.

===============================================================================
12. COMMON MISTAKES
===============================================================================

Mistake 1: Using a stack instead of a queue
-------------------------------------------
A stack follows LIFO (Last In, First Out), which does not naturally produce
standard level-order traversal. A queue's FIFO behavior is the key to BFS.

Mistake 2: Enqueuing the right child before the left child
---------------------------------------------------------
That would visit nodes from right to left within each level. For standard
left-to-right level order, enqueue left first, then right.

Mistake 3: Forgetting q.pop()
-----------------------------
If the front node is never removed, the same node remains at the front and
the loop may never finish.

Mistake 4: Assuming q.pop() returns the removed item
----------------------------------------------------
It does not. Read q.front() first, store it, then call q.pop().

Mistake 5: Pushing nullptr children
-----------------------------------
Only enqueue a child when it is not nullptr.

Mistake 6: Confusing node pointers and node values
--------------------------------------------------
The queue stores Node* pointers. The answer vector stores int values:
    q.push(node->left);
    ans.push_back(node->data);

Mistake 7: Forgetting member variables persist
----------------------------------------------
In your submitted code, ans and q are members of Solution. If the same object
is used for another call, they may still contain values from the previous
call. Local containers avoid this problem.

===============================================================================
13. CLEANER / RECOMMENDED IMPLEMENTATION
===============================================================================

This version uses local variables so every function call starts with a fresh
answer vector and an empty queue:

class Solution {
  public:
    vector<int> levelOrder(Node* root) {
        vector<int> ans;
        queue<Node*> q;

        if (root == nullptr) {
            return ans;
        }

        q.push(root);

        while (!q.empty()) {
            Node* node = q.front();
            q.pop();

            ans.push_back(node->data);

            if (node->left != nullptr) {
                q.push(node->left);
            }

            if (node->right != nullptr) {
                q.push(node->right);
            }
        }

        return ans;
    }
};

This is logically equivalent to your submitted code. The order of recording
the value and popping the node is not important as long as q.front() is read
before q.pop(). This version pops immediately after saving the pointer, then
records its data.

Why prefer local variables?
- Each invocation starts with ans empty.
- Each invocation starts with q empty.
- No state leaks between calls.
- The function is easier to reason about.

===============================================================================
14. LEVEL ORDER TRAVERSAL VS LEVEL-BY-LEVEL GROUPING
===============================================================================

Your GFG solution returns a single vector:

    [1, 2, 3, 4, 5, 6]

LeetCode 102, Binary Tree Level Order Traversal, asks for a vector of vectors:

    [[1], [2, 3], [4, 5, 6]]

Both use BFS and a queue.

The difference is how the output is organized.

For LeetCode 102, you capture the queue size at the start of each level:

    int levelSize = q.size();

Then process exactly levelSize nodes in an inner loop, collecting their
values into one temporary vector. Children added during that inner loop are
saved for the next level.

For the GFG problem in this file, there is no need to separate levels, so one
while loop is sufficient.

===============================================================================
15. QUICK REVISION QUESTIONS
===============================================================================

Q1. Which algorithm does this solution use?
A. Breadth-First Search (BFS).

Q2. Why is a queue used?
A. FIFO order makes nodes get processed level by level.

Q3. What does queue<Node*> store?
A. Pointers to tree nodes, not their integer data.

Q4. What does q.front() do?
A. Gives access to the first queued item without removing it.

Q5. What does q.pop() do?
A. Removes the front item; it does not return that item.

Q6. Why enqueue left before right?
A. To preserve left-to-right order within each level.

Q7. Why check whether each child is nullptr?
A. To avoid adding nonexistent nodes to the queue.

Q8. What is the time complexity?
A. O(n), because every node is processed once.

Q9. What is the queue's auxiliary space?
A. O(w), where w is the maximum width of the tree; worst case O(n).

Q10. What changes for LeetCode 102?
A. Use an inner loop that processes exactly the number of nodes currently in
   the queue at the start of each level, and store each level in its own
   vector.

===============================================================================
16. FINAL TAKEAWAY
===============================================================================

Remember the standard BFS pattern:

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* node = q.front();
        q.pop();

        ans.push_back(node->data);

        if (node->left != nullptr)
            q.push(node->left);

        if (node->right != nullptr)
            q.push(node->right);
    }

The queue decides the processing order. Adding the left child before the
right child ensures the traversal visits nodes from left to right within
each level.

Your submitted algorithm is correct. The main improvement is to make ans and
q local variables rather than member variables, so repeated calls cannot
accidentally reuse old state.
===============================================================================
*/
