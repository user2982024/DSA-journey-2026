/*
===============================================================================
DSA JOURNEY — LINKED LISTS
===============================================================================

PROBLEM: 430. Flatten a Multilevel Doubly Linked List
PLATFORM: LeetCode
DIFFICULTY: Medium
LANGUAGE: C++

===============================================================================
1. PROBLEM STATEMENT
===============================================================================

A doubly linked list contains nodes with four members:

    val   -> Stores the node's value.
    prev  -> Points to the previous node.
    next  -> Points to the next node.
    child -> Points to the head of another doubly linked list, or nullptr.

A child list can itself contain nodes with child lists, creating multiple
levels.

The task is to flatten the structure into one doubly linked list.

The flattened order is depth-first:
- Visit a node.
- If it has a child list, process that child list before continuing with
  the original next node.
- Preserve the order of nodes within each list.
- Set every child pointer to nullptr.

Example:

    Original top-level list:

    1 <-> 2 <-> 3 <-> 4 <-> 5 <-> 6
                  |
                child
                  |
                  v
                  7 <-> 8 <-> 9 <-> 10
                       |
                     child
                       |
                       v
                       11 <-> 12

    Flattened result:

    1 <-> 2 <-> 3 <-> 7 <-> 8 <-> 11 <-> 12
                                  |
                                  | then return
                                  v
    ... <-> 9 <-> 10 <-> 4 <-> 5 <-> 6

    Final order:

    1 <-> 2 <-> 3 <-> 7 <-> 8 <-> 11 <-> 12
       <-> 9 <-> 10 <-> 4 <-> 5 <-> 6

The exact structure is flattened in depth-first order.

===============================================================================
2. OUR INITIAL APPROACH
===============================================================================

We began by reasoning through the linked list manually.

Our plan was:

1. Create a current pointer to traverse the list.
2. Check whether the current node has a child.
3. If there is a child:
   - Save the original next pointer.
   - Move into the child list.
   - Connect the parent to the child.
   - Connect the child's head back to the parent.
4. Continue traversing the child list.
5. Once a list ends, retrieve a saved continuation from a stack.
6. Reconnect the saved continuation to the flattened chain.
7. Continue until all saved continuations are processed.

This led us to recognize that a stack is useful because nested child lists
require returning to the most recently encountered continuation first.

===============================================================================
3. WHY A STACK?
===============================================================================

A stack follows LIFO:

    Last In, First Out

Suppose the original list contains:

    1 <-> 2 <-> 3 <-> 4 <-> 5 <-> 6
                  |
                  v
                  7 <-> 8 <-> 9 <-> 10
                       |
                       v
                       11 <-> 12

At node 3, we need to process its child list before node 4.

We save node 4 as a continuation.

At node 8, we need to process its child list before node 9.

We save node 9 as another continuation.

Stack, from bottom to top:

    [4, 9]

After processing nodes 11 and 12, node 9 must be processed before node 4.

That is exactly the LIFO order:

    First retrieve 9.
    Then retrieve 4.

C++ stack operations:

    s.push(node);  // Save a pointer.
    s.top();       // Read the most recently pushed pointer.
    s.pop();       // Remove the top entry.

IMPORTANT:
    pop() does not return the element. Read top() before calling pop().

===============================================================================
4. POINTER CONNECTIONS
===============================================================================

Suppose node 3 has a child pointing to node 7.

Before flattening:

    3.next  -> 4
    3.child -> 7
    7.prev  -> nullptr

After connecting the child list:

    3.next  -> 7
    7.prev  -> 3
    3.child -> nullptr

The required updates are conceptually:

    current->next = current->child;
    current->next->prev = current;
    current->child = nullptr;

Before overwriting current->next, preserve its original value if it exists:

    Node* continuation = current->next;

Otherwise, the original continuation could be lost.

IMPORTANT:
    Updating next without updating prev leaves an inconsistent doubly linked
    list.

===============================================================================
5. ISSUES WE FACED AND HOW WE FIXED THEM
===============================================================================

ISSUE 1: LOSING THE ORIGINAL NEXT POINTER

Initially, replacing current->next with current->child would lose the original
continuation.

LESSON:
    Save the original next pointer before overwriting it.

ISSUE 2: USING A MAP INSTEAD OF A STACK

We considered storing node associations in a map.

However, we needed the most recently saved continuation first, which is the
natural behavior of a stack.

LESSON:
    Choose data structures based on the ordering behavior required.

ISSUE 3: FORGETTING THE PREV POINTER

After connecting a parent to its child, the child's prev pointer also needs
to point back to the parent.

LESSON:
    Every forward connection in a doubly linked list must have a matching
    backward connection.

ISSUE 4: NOT CLEARING CHILD POINTERS

A flattened list must not retain child connections.

LESSON:
    Once a child list is connected into the main chain, set the corresponding
    child pointer to nullptr.

ISSUE 5: PUSHING nullptr ONTO THE STACK

If a node has a child but no original next node, its saved continuation is
nullptr.

Pushing nullptr creates an invalid continuation for later reconnection.

LESSON:
    Only push a continuation when the pointer is non-null.

ISSUE 6: CURRENT BECOMES nullptr

A loop such as:

    while (current != nullptr)

eventually leaves current as nullptr.

Dereferencing current afterward is invalid:

    current->next = something; // Invalid if current == nullptr.

LESSON:
    If a later operation needs the final node, preserve a valid pointer or
    use an approach that processes the continuation before advancing.

ISSUE 7: REPEATEDLY SEARCHING FOR THE END

Our original approach reconnected saved sublists and then traversed the
extended chain to locate its final node.

That can repeatedly visit already processed nodes.

LESSON:
    A standard stack-based depth-first traversal can process each node once,
    avoiding repeated end-of-list traversals.

ISSUE 8: MEMORY MANAGEMENT

The flatten operation rearranges the existing nodes. It does not need to
allocate replacement nodes or delete any nodes.

LESSON:
    Reuse the existing nodes and update their pointers.

===============================================================================
6. CORRECTED STACK-BASED IMPLEMENTATION
===============================================================================

This implementation uses an iterative depth-first traversal.

Instead of waiting until the first traversal ends and then reconnecting
continuations, it saves the original next node whenever a child list must be
processed first.

The stack preserves the nodes that must be visited after the child list.

*/

#include <stack>
using namespace std;

/*
LeetCode provides the Node definition.

Do not redefine Node when submitting to LeetCode.

The expected definition is:

class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

class Solution {
public:

    /*
    ===========================================================================
    FUNCTION: flatten
    ===========================================================================

    PURPOSE:
        Flatten a multilevel doubly linked list in depth-first order.

    APPROACH:
        1. Handle an empty input.
        2. Initialize current at head.
        3. Traverse while current exists.
        4. If current has a child:
           - Save current->next if it exists.
           - Connect current to its child.
           - Fix the child's prev pointer.
           - Clear current->child.
           - Continue into the child list.
        5. When a child list ends, use the saved continuation from the stack.
        6. Continue until all nodes have been processed.

    TIME COMPLEXITY:
        O(n), where n is the number of nodes across all levels.

        Each node is visited a constant number of times.

    AUXILIARY SPACE:
        O(d), where d is the maximum number of simultaneously saved
        continuations. In the worst case, this can be O(n).

    NOTE:
        This is an iterative depth-first traversal that uses a stack.
    */

    Node* flatten(Node* head) {

        // An empty list is already flattened.
        if (head == nullptr) {
            return nullptr;
        }

        // Stack stores original next pointers that must be visited later.
        stack<Node*> s;

        // Begin at the head of the multilevel list.
        Node* current = head;

        // Traverse every reachable node.
        while (current != nullptr) {

            /*
            If current has a child list, that list must be processed before
            the original next node.
            */

            if (current->child != nullptr) {

                /*
                Preserve the original continuation.

                Example:
                    current = 3
                    current->next = 4
                    current->child = 7

                Node 4 must be visited after the child list beginning at 7.
                */

                if (current->next != nullptr) {
                    s.push(current->next);
                }

                /*
                Connect the current node to the child-list head.
                */

                current->next = current->child;

                // Establish the backward connection.
                current->child->prev = current;

                // The child connection must be removed after flattening it.
                current->child = nullptr;
            }

            /*
            If the current node has no next node, but saved continuations
            remain, resume the most recently saved continuation.

            This is what lets the traversal return from a completed child list.
            */

            if (current->next == nullptr && !s.empty()) {

                // Retrieve the most recently saved continuation.
                Node* continuation = s.top();
                s.pop();

                // Connect the current final node to that continuation.
                current->next = continuation;
                continuation->prev = current;
            }

            /*
            Advance after all pointer updates for this node are complete.
            */

            current = current->next;
        }

        // The original nodes have been flattened in place.
        return head;
    }
};

/*
===============================================================================
7. COMPLEXITY ANALYSIS
===============================================================================

Let n be the total number of nodes across every level.

TIME COMPLEXITY: O(n)

Reason:
- Each node is visited a constant number of times.
- Pointer reconnection takes O(1) time per processed node.
- Stack push and pop operations take O(1) time each.

AUXILIARY SPACE: O(d), worst-case O(n)

Reason:
- The stack stores saved continuation pointers.
- d is the maximum number of simultaneously saved continuations.
- In the worst case, the stack can hold O(n) pointers.

OUTPUT SPACE:
    O(1) additional node storage.

We reuse the original nodes rather than constructing a separate list.

===============================================================================
8. IMPORTANT EDGE CASES
===============================================================================

CASE 1: EMPTY LIST

    head == nullptr

Expected:
    Return nullptr.

CASE 2: SINGLE NODE

    1

Expected:
    The node remains unchanged, with next, prev, and child equal to nullptr.

CASE 3: NO CHILD POINTERS

    1 <-> 2 <-> 3

Expected:
    The original list remains unchanged.

CASE 4: CHILD AT THE LAST NODE

    1 <-> 2 <-> 3
              |
              v
              7 <-> 8

Expected:
    1 <-> 2 <-> 3 <-> 7 <-> 8

This case is important because the parent has no original next continuation.

CASE 5: NESTED CHILD LISTS

    1 <-> 2 <-> 3 <-> 4
              |
              v
              7 <-> 8
                    |
                    v
                    11 <-> 12

Expected order:
    1, 2, 3, 7, 8, 11, 12, 4

CASE 6: ALL CHILD POINTERS MUST BE CLEARED

After flattening, every node must satisfy:

    node->child == nullptr

CASE 7: PREV POINTERS MUST MATCH NEXT POINTERS

For each pair of adjacent nodes A and B:

    A->next == B
    B->prev == A

The head's prev and the tail's next must be nullptr.

===============================================================================
9. FINAL TAKEAWAYS
===============================================================================

This problem taught us how to combine:

- Doubly linked list pointer manipulation.
- Depth-first traversal.
- Stack-based continuation management.
- LIFO ordering.
- Null-pointer safety.
- Preserving pointers before overwriting them.
- Maintaining both next and prev connections.
- Clearing child pointers after flattening.
- Time and auxiliary-space complexity analysis.

The most important lesson is that a stack can remember where to resume when
a nested child list must be processed first.

The corrected implementation uses that idea directly, without repeatedly
traversing the flattened chain to find its end.

===============================================================================
END OF STUDY NOTES
===============================================================================
*/