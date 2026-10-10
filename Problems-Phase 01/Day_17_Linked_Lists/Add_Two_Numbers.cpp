
/*
===============================================================================
PROBLEM: ADD TWO NUMBERS
PLATFORM: LeetCode
PROBLEM NUMBER: 2
DIFFICULTY: MEDIUM
TOPIC: SINGLY LINKED LIST
APPROACH: ITERATIVE ADDITION WITH CARRY AND DUMMY NODE
STATUS: ACCEPTED
===============================================================================

1. PROBLEM STATEMENT
--------------------

You are given two non-empty singly linked lists representing two non-negative
integers.

Each node contains a single digit. The digits are stored in REVERSE ORDER,
meaning that the first node contains the least significant digit.

Add the two numbers and return the sum as a linked list, also in reverse order.

IMPORTANT:
- Each node stores a single digit from 0 to 9.
- The input lists may have different lengths.
- The result may contain an additional digit because of a final carry.
- The input lists do not need to be modified.
- The result must be represented by newly created nodes.

Example 1:
----------

Input:
l1 = [2, 4, 3]
l2 = [5, 6, 4]

Interpretation:
342 + 465 = 807

Output:
[7, 0, 8]

Explanation:
2 + 5 = 7
4 + 6 = 10  -> write 0, carry 1
3 + 4 + 1 = 8

The resulting linked list is:
7 -> 0 -> 8 -> nullptr


Example 2:
----------

Input:
l1 = [0]
l2 = [0]

Interpretation:
0 + 0 = 0

Output:
[0]


Example 3:
----------

Input:
l1 = [9, 9, 9, 9, 9, 9, 9]
l2 = [9, 9, 9, 9]

Interpretation:
9999999 + 9999 = 10009998

Output:
[8, 9, 9, 9, 0, 0, 0, 1]

This example demonstrates how carry can continue through several nodes and
produce an additional node at the end.


===============================================================================
2. UNDERSTANDING THE REVERSE-ORDER REPRESENTATION
===============================================================================

A linked list such as:

2 -> 4 -> 3

represents the number 342, NOT 243.

The first node contains the units digit.
The second node contains the tens digit.
The third node contains the hundreds digit.

This arrangement allows us to add the numbers from left to right through the
linked lists, beginning with their least significant digits.

We do not need to reverse either list before adding the numbers.


===============================================================================
3. INITIAL APPROACH AND REASONING
===============================================================================

The solution uses elementary addition, similar to how addition is performed
digit by digit on paper.

For each position:

    sum = digit1 + digit2 + carry

The resulting digit is:

    digit = sum % 10

The carry for the next position is:

    carry = sum / 10

Since integer division is used, sum / 10 discards the fractional part.

Examples:

    sum = 7:
    digit = 7 % 10 = 7
    carry = 7 / 10 = 0

    sum = 12:
    digit = 12 % 10 = 2
    carry = 12 / 10 = 1

    sum = 19:
    digit = 19 % 10 = 9
    carry = 19 / 10 = 1

The digit is placed into a new result node, and the carry is used during the
next iteration.


===============================================================================
4. POINTERS AND VARIABLES USED
===============================================================================

current1:
    Traverses the first input linked list.

current2:
    Traverses the second input linked list.

dummy:
    A dummy node placed before the first result node.
    It simplifies result-list construction because we do not need a separate
    special case for creating the first actual result node.

ans:
    Points to the last node of the result list.
    New result nodes are attached using ans->next.

sum:
    Stores the sum of the two current digits and the incoming carry.

digit:
    Stores the digit that belongs in the current result node.

carry:
    Stores the carry produced by the current addition.


===============================================================================
5. WHY USE A DUMMY NODE?
===============================================================================

Without a dummy node, the first result node would require special handling.

We would need to check whether the result list is empty before deciding whether
to initialize its head or append a node.

The dummy node avoids this special case.

Initially:

    dummy -> nullptr
    ans = dummy

When the first result digit is created:

    ans->next = new ListNode(digit)

The result now looks like:

    dummy -> first digit -> nullptr

Then:

    ans = ans->next

The ans pointer moves to the newly created node.

After all digits have been processed, the actual answer begins at:

    dummy->next

The dummy node itself is not part of the returned answer.


===============================================================================
6. WHY THE WHILE-LOOP CONDITION IS IMPORTANT
===============================================================================

The loop condition is:

    while (current1 != nullptr ||
           current2 != nullptr ||
           carry != 0)

There are THREE reasons to continue the loop.

A. The first list still contains digits.

B. The second list still contains digits.

C. A carry remains even though both lists have ended.

The third condition is particularly important.

For example:

    l1 = [9]
    l2 = [1]

First iteration:
    9 + 1 + 0 = 10
    digit = 0
    carry = 1

Both input pointers now become nullptr, but the carry is still 1.

The loop must execute one more time to create the final node containing 1.

Output:
    [0, 1]

If carry != 0 were omitted from the loop condition, this final digit would
be lost.


===============================================================================
7. HANDLING DIFFERENT-LENGTH LINKED LISTS
===============================================================================

The two lists may contain different numbers of nodes.

For example:

    l1 = [2, 4, 3]
    l2 = [5, 6]

When the second list ends, current2 becomes nullptr.

We must not dereference current2 when it is nullptr.

Therefore, we use conditional expressions:

    int x = (current1 != nullptr) ? current1->val : 0;
    int y = (current2 != nullptr) ? current2->val : 0;

If a list has ended, its contribution is treated as zero.

For the example above:

First iteration:
    2 + 5 = 7

Second iteration:
    4 + 6 = 10
    digit = 0
    carry = 1

Third iteration:
    3 + 0 + 1 = 4

Output:
    [7, 0, 4]

This is equivalent to adding 342 + 65 = 407.


===============================================================================
8. HOW THE POINTERS ADVANCE
===============================================================================

After processing the current digits, each input pointer advances only if it
still points to a valid node.

    if (current1 != nullptr) {
        current1 = current1->next;
    }

    if (current2 != nullptr) {
        current2 = current2->next;
    }

This prevents invalid memory access.

It also allows one list to finish before the other.

Both input lists are traversed from beginning to end, and neither list needs
to be reversed or modified.


===============================================================================
9. STEP-BY-STEP DRY RUN
===============================================================================

Input:

    l1 = [2, 4, 3]
    l2 = [5, 6, 4]

Initially:

    carry = 0
    result = empty

ITERATION 1
-----------

Current digits:
    x = 2
    y = 5

Calculation:
    sum = 2 + 5 + 0 = 7
    digit = 7 % 10 = 7
    carry = 7 / 10 = 0

Append digit 7.

Result:
    [7]


ITERATION 2
-----------

Current digits:
    x = 4
    y = 6

Calculation:
    sum = 4 + 6 + 0 = 10
    digit = 10 % 10 = 0
    carry = 10 / 10 = 1

Append digit 0.

Result:
    [7, 0]


ITERATION 3
-----------

Current digits:
    x = 3
    y = 4

Calculation:
    sum = 3 + 4 + 1 = 8
    digit = 8 % 10 = 8
    carry = 8 / 10 = 0

Append digit 8.

Result:
    [7, 0, 8]


TERMINATION
-----------

Both input pointers are nullptr.
The carry is also zero.

The loop terminates.

Return:
    dummy->next

Final output:
    [7, 0, 8]


===============================================================================
10. PROBLEMS AND COMMON MISTAKES
===============================================================================

The following are important failure cases to understand when implementing
this problem.

A. FORGETTING THE CARRY

Incorrect:
    digit = sum % 10;

If carry is not retained using sum / 10, additions greater than or equal to
10 produce an incorrect result.

Correct:
    digit = sum % 10;
    carry = sum / 10;


B. IGNORING UNEQUAL LIST LENGTHS

Incorrect:
    int sum = current1->val + current2->val + carry;

This dereferences both pointers without checking whether either has reached
nullptr.

Correct:
    int x = (current1 != nullptr) ? current1->val : 0;
    int y = (current2 != nullptr) ? current2->val : 0;


C. OMITTING CARRY FROM THE LOOP CONDITION

If both lists end but carry remains, another result node may be necessary.

Correct loop condition:

    while (current1 != nullptr ||
           current2 != nullptr ||
           carry != 0)


D. FORGETTING TO ADVANCE AN INPUT POINTER

If current1 or current2 is not advanced, the same digit may be processed
repeatedly, potentially causing an infinite loop.

Both pointers must advance independently when non-null.


E. FORGETTING TO ADVANCE THE RESULT POINTER

After attaching a result node, ans must move to that node.

Otherwise, subsequent result nodes may overwrite existing next connections
or the result may not be constructed correctly.


F. RETURNING THE DUMMY NODE

The dummy node is an implementation convenience, not part of the answer.

Correct:
    return dummy->next;

Incorrect:
    return dummy;


G. INCORRECT DIGIT ORDER

The problem already stores digits in reverse order. Reversing the lists first
is unnecessary and can complicate the implementation.

Process each list from its head and append each calculated digit.


===============================================================================
11. DEBUGGING AND VALIDATION CHECKLIST
===============================================================================

When testing a solution, verify the following cases:

[1] Both lists contain one digit.
    Example: [2] + [3] -> [5]

[2] Both lists have the same length.
    Example: [2,4,3] + [5,6,4] -> [7,0,8]

[3] The first list is longer.
    Example: [2,4,3] + [5,6] -> [7,0,4]

[4] The second list is longer.
    Example: [9] + [1,2,3] -> [0,3,3]

[5] A carry remains after both lists end.
    Example: [9] + [1] -> [0,1]

[6] Carry continues across multiple positions.
    Example: [9,9,9] + [1] -> [0,0,0,1]

[7] Both numbers contain zero.
    Example: [0] + [0] -> [0]

[8] A carry is produced while one list is already exhausted.

The solution must correctly handle all of these cases.


===============================================================================
12. TIME COMPLEXITY
===============================================================================

Let:

    M = number of nodes in the first linked list
    N = number of nodes in the second linked list

The algorithm processes each digit position once.

The number of iterations is at most:

    max(M, N) + 1

The additional iteration accounts for a possible final carry.

Therefore, the time complexity is:

    O(max(M, N))

This is equivalent to:

    O(M + N)

in Big-O notation for this problem.


===============================================================================
13. AUXILIARY SPACE COMPLEXITY
===============================================================================

The algorithm uses a fixed number of pointer and integer variables:

    current1, current2, dummy, ans, sum, digit, carry

The number of these variables does not grow with the input size.

Therefore, auxiliary space complexity, excluding the output list, is:

    O(1)

However, the result list contains O(max(M, N)) nodes in the worst case.

Therefore:

    Output space: O(max(M, N))
    Auxiliary space excluding output: O(1)

If the output list is included in total additional memory usage, the overall
additional space is O(max(M, N)).


===============================================================================
14. IMPORTANT CONCEPTS LEARNED
===============================================================================

1. Dummy nodes simplify linked-list construction.
2. Pointer checks prevent dereferencing nullptr.
3. The modulo operator (%) extracts the last decimal digit.
4. Integer division (/) calculates the carry.
5. Different-length lists can be processed in a single loop.
6. Carry may require an extra output node.
7. A result list can be built incrementally using a tail pointer.
8. The input lists do not need to be modified.
9. Always consider termination conditions carefully.
10. Test edge cases, especially unequal lengths and final carry.


===============================================================================
15. INTERVIEW TAKEAWAYS
===============================================================================

When explaining this solution in an interview:

- Begin by explaining the reverse-order representation.
- Explain how ordinary addition translates into node-by-node processing.
- Explain the role of carry.
- Explain why the loop continues when a carry remains.
- Explain why null input pointers contribute zero.
- Explain the dummy node and the returned pointer.
- State time and auxiliary space complexity separately.
- Mention the final-carry and unequal-length edge cases.

A strong interview answer should explain not only WHAT the code does, but WHY
each condition and pointer operation is necessary.


===============================================================================
16. FINAL SUMMARY
===============================================================================

The solution adds two reverse-order linked-list numbers one digit at a time.

For each iteration:
    1. Read available digits, using zero for an exhausted list.
    2. Add both digits and the incoming carry.
    3. Extract the result digit using modulo 10.
    4. Calculate the outgoing carry using integer division by 10.
    5. Append a new node containing the result digit.
    6. Advance each input pointer if it is not nullptr.

The dummy node makes result construction simple, while the loop condition
ensures that a final carry is never lost.

Time complexity:
    O(M + N)

Auxiliary space excluding output:
    O(1)

Output space:
    O(max(M, N))

===============================================================================
END OF NOTES
===============================================================================
*/

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* current1 = l1;
        ListNode* current2 = l2;

        ListNode* dummy = new ListNode(0);
        ListNode* ans = dummy;

        int sum = 0;
        int digit = 0;
        int carry = 0;

        while (current1 != nullptr ||
               current2 != nullptr ||
               carry != 0) {

            int x = (current1 != nullptr) ? current1->val : 0;
            int y = (current2 != nullptr) ? current2->val : 0;

            sum = x + y + carry;

            digit = sum % 10;
            carry = sum / 10;

            ans->next = new ListNode(digit);
            ans = ans->next;

            if (current1 != nullptr) {
                current1 = current1->next;
            }

            if (current2 != nullptr) {
                current2 = current2->next;
            }
        }

        return dummy->next;
    }
};
