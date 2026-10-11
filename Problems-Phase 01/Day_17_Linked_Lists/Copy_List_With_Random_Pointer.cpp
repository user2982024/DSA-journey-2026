/*
    ================================================================
    PROBLEM: Copy List with Random Pointer
    PLATFORM: LeetCode
    PROBLEM NUMBER: 138
    DIFFICULTY: Medium
    TOPIC: Linked List, Hash Map, Pointers, Deep Copy
    ================================================================

    PROBLEM STATEMENT
    -----------------
    We are given a linked list in which every node contains three
    fields:

        1. val    -> The integer value stored in the node.
        2. next   -> A pointer to the next node.
        3. random -> A pointer to any node in the list, or nullptr.

    We must create a DEEP COPY of the entire linked list.

    A deep copy must satisfy the following conditions:

        1. Every original node has a corresponding newly created node.
        2. Each copied node contains the same value as its original.
        3. The next pointers must preserve the original next relationships.
        4. The random pointers must preserve the original random relationships.
        5. No copied pointer may refer to an original node.
        6. Changes to the copied nodes must not modify the original list.

    IMPORTANT:
    We must preserve node relationships, not merely node values.

    Two different nodes can contain the same value. Therefore, values
    alone cannot uniquely identify the nodes and their relationships.


    ================================================================
    APPROACH: TWO PASSES + HASH MAP
    ================================================================

    The key idea is to create every copied node first and then use a
    hash map to reproduce the random-pointer relationships.

    We use:

        unordered_map<Node*, Node*> freqMap;

    The map stores:

        KEY   -> Address of an original node.
        VALUE -> Address of its corresponding copied node.

    For example:

        freqMap[originalNode] = copiedNode;

    This association allows us to translate an original node's address
    into the address of its corresponding copied node.


    ------------------------------------------------
    WHY DO WE NEED A HASH MAP?
    ------------------------------------------------

    Consider an original node A whose random pointer points to node C.

    We create a copied node A' and a copied node C'.

    The copied node A' must point to C', NOT to the original node C.

    The hash map lets us find C' using the address of C:

        freqMap[C] gives the address of C'.

    Since every copied node is created during the first pass, all
    original-to-copy associations are available before we assign the
    random pointers during the second pass.


    ================================================================
    STEP 1: CREATE THE COPIED NEXT CHAIN
    ================================================================

    We begin by traversing the original list.

    For each original node:

        1. Create a new node with the same integer value.
        2. Attach the new node to the copied list.
        3. Store the original-node-to-copied-node association in the map.
        4. Advance both traversal pointers.

    We use a dummy node to simplify construction of the copied list.

        Node* dummy = new Node(0);
        Node* it = dummy;

    The dummy node is a temporary starting point. It is not part of the
    final answer.

    The pointer 'it' always points to the last node in the copied chain.

    When a new node is created:

        it->next = newNode;
        it = it->next;

    This attaches the new node and advances 'it'.

    At the same time:

        freqMap[current] = newNode;

    Here:

        current -> Original node.
        newNode  -> Corresponding copied node.

    IMPORTANT:
    The map key is the original node's ADDRESS, not its integer value.

    At the end of this pass, the copied list has all its nodes and next
    pointers, but its random pointers have not yet been connected.


    ================================================================
    STEP 2: ASSIGN THE RANDOM POINTERS
    ================================================================

    After creating the copied list, we reset our traversal pointer:

        current = head;

    We traverse the ORIGINAL list again.

    Why traverse the original list?

    Because each original node already contains the correct random
    pointer relationship that we need to reproduce.

    For each original node, we use:

        freqMap[current]->random = freqMap[current->random];

    Let's understand both sides.

    LEFT SIDE:

        freqMap[current]->random

    First, freqMap[current] retrieves the copied node corresponding
    to the current original node.

    Then, ->random accesses the random pointer of that copied node.

    RIGHT SIDE:

        freqMap[current->random]

    First, current->random retrieves the address of the original node
    targeted by the current original node's random pointer.

    Then, the map retrieves the copied version of that target node.

    Therefore, the assignment connects one copied node to another
    copied node while preserving the original random relationship.


    ------------------------------------------------
    IMPORTANT NULLPTR CASE
    ------------------------------------------------

    An original node's random pointer may be nullptr.

    For example:

        current->random == nullptr

    In this situation, we must set the corresponding copied node's
    random pointer to nullptr too.

    We handle this explicitly:

        if (current->random == nullptr) {
            freqMap[current]->random = nullptr;
        } else {
            freqMap[current]->random = freqMap[current->random];
        }

    Why not directly use freqMap[current->random] in every case?

    Because unordered_map::operator[] inserts a new entry if the key
    does not already exist. Looking up nullptr in this way can create
    an unnecessary nullptr-key entry whose value is also nullptr.

    Explicitly handling nullptr avoids that unnecessary map entry.

    After assigning the random pointer, we advance:

        current = current->next;

    This ensures that every original node is processed exactly once
    during the second pass.


    ================================================================
    STEP 3: RETURN THE COPIED LIST
    ================================================================

    We return:

        return dummy->next;

    Why not return dummy?

    The dummy node was introduced only to simplify list construction.
    The actual copied list begins at dummy->next.

    Returning dummy would incorrectly include the temporary dummy node
    as the first node of the result.

    We therefore return the head of the actual copied list.


    ================================================================
    COMPLETE C++ SOLUTION
    ================================================================
*/

#include <unordered_map>
using namespace std;

/*
// Definition for a Node.

class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {

        // =========================================================
        // STEP 1: CREATE COPIED NODES AND POPULATE THE HASH MAP
        // =========================================================

        // Each key is an original node address.
        // Each value is the address of its corresponding copied node.
        unordered_map<Node*, Node*> freqMap;

        // Traverse the original list.
        Node* current = head;

        // The dummy node simplifies construction of the copied list.
        // It is not included in the final returned list.
        Node* dummy = new Node(0);

        // 'it' points to the last node in the copied chain.
        Node* it = dummy;

        // Create a copy of every original node and connect next pointers.
        while (current != nullptr) {

            // Create a new node containing the original node's value.
            Node* newNode = new Node(current->val);

            // Append the new node to the copied list.
            it->next = newNode;

            // Associate the original node with its copied node.
            freqMap[current] = newNode;

            // Advance to the newly appended copied node.
            it = it->next;

            // Advance through the original list.
            current = current->next;
        }

        // =========================================================
        // STEP 2: REPRODUCE THE RANDOM-POINTER RELATIONSHIPS
        // =========================================================

        // Restart traversal from the original list's head.
        current = head;

        while (current != nullptr) {

            // If the original random pointer is nullptr, preserve
            // that relationship in the corresponding copied node.
            if (current->random == nullptr) {

                freqMap[current]->random = nullptr;

            } else {

                // Find the copied version of the node targeted by
                // the original node's random pointer.
                freqMap[current]->random =
                    freqMap[current->random];
            }

            // Move to the next original node.
            current = current->next;
        }

        // =========================================================
        // STEP 3: RETURN THE HEAD OF THE COPIED LIST
        // =========================================================

        // Skip the temporary dummy node and return the actual copy.
        return dummy->next;
    }
};


/*
    ================================================================
    COMPLEXITY ANALYSIS
    ================================================================

    Let n be the number of nodes in the original linked list.

    TIME COMPLEXITY: O(n)

    First pass:
        We traverse the original list once, creating n copied nodes
        and inserting n associations into the hash map.

        Expected time: O(n).

    Second pass:
        We traverse the original list once more and assign each
        copied node's random pointer using expected O(1) hash-map
        lookups.

        Expected time: O(n).

    Total:
        O(n) + O(n) = O(n).

    Hash-map operations have expected O(1) time complexity under
    typical hashing behavior. In pathological collision scenarios,
    individual operations may take longer.


    AUXILIARY SPACE COMPLEXITY: O(n)

    The hash map stores one entry per original node.

    Therefore, the map requires O(n) additional space.

    OUTPUT SPACE: O(n)

    We create n new nodes for the copied linked list.

    If the output list is counted separately from auxiliary space:

        Auxiliary space: O(n)
        Output space:    O(n)

    Overall additional memory, including the output: O(n).

    The dummy node requires only O(1) additional space.


    ================================================================
    EDGE CASES
    ================================================================

    1. EMPTY LIST

       Input:
           head = nullptr

       The first and second loops execute zero times.
       dummy->next remains nullptr.
       The function returns nullptr.

    2. SINGLE NODE WITH A NULL RANDOM POINTER

       The copied list contains one node with the same value.
       Its next and random pointers are both nullptr.

    3. RANDOM POINTER POINTS TO THE SAME NODE

       If an original node points to itself through random, the
       copied node must point to itself through random as well.

    4. RANDOM POINTER POINTS TO AN EARLIER NODE

       The map already contains the corresponding copied node,
       so the correct copied relationship can be established.

    5. RANDOM POINTER POINTS TO A LATER NODE

       The first pass has already created every copied node before
       the second pass begins, so the target is available in the map.

    6. DUPLICATE INTEGER VALUES

       Different nodes may contain identical values. Since the map
       uses node addresses as keys, those nodes remain distinguishable.

    7. UNEVEN RANDOM-POINTER RELATIONSHIPS

       Every random pointer is reproduced independently according
       to its original target, regardless of the next-chain order.


    ================================================================
    WHY THIS APPROACH WORKS
    ================================================================

    The algorithm maintains a one-to-one correspondence between
    every original node and its copied node.

    During the first pass, it establishes this correspondence and
    reconstructs the next chain.

    During the second pass, it uses the correspondence to reconstruct
    each random-pointer relationship.

    Consequently, the returned list contains newly allocated nodes
    whose values and pointer relationships match the original list,
    without reusing any original node.

    ================================================================
    INTERVIEW TAKEAWAYS
    ================================================================

    1. Explain why values cannot be used as unique map keys.
    2. Explain why original-node addresses are used as keys.
    3. Explain why the algorithm uses two passes.
    4. Explain the difference between current->random and
       freqMap[current->random].
    5. Explain why nullptr must be preserved.
    6. Explain why dummy->next is returned.
    7. State O(n) time and O(n) auxiliary space.
    8. Be prepared to discuss an alternative approach that interleaves
       copied nodes with original nodes to reduce auxiliary map space.

    FINAL SUMMARY:

        PASS 1:
            Create copied nodes.
            Connect next pointers.
            Populate the original-to-copy hash map.

        PASS 2:
            Reproduce random pointers using the hash map.
            Preserve nullptr random pointers.

        RETURN:
            dummy->next

    ================================================================
    END OF SOLUTION
    ================================================================
*/