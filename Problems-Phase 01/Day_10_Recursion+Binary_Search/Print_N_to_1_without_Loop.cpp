
/*
==========================================================
Problem: Print N to 1 Without Loop
Platform: GeeksforGeeks
Topic: Recursion
==========================================================

PROBLEM STATEMENT:
Given a positive integer N, print numbers from N down to 1
without using any loop.

Example 1:
Input:
N = 5

Output:
5 4 3 2 1

Example 2:
Input:
N = 1

Output:
1

==========================================================
APPROACH: RECURSION
==========================================================

1. BASE CASE:
   If n == 0, return from the function.
   This stops the recursive calls.

2. PRINT CURRENT NUMBER:
   Print n followed by a space.

3. RECURSIVE CALL:
   Call printNos(n - 1) to print the next smaller number.

4. Each recursive call decreases n by 1 until it reaches 0.

==========================================================
CODE:
==========================================================
*/

#include <iostream>
using namespace std;

class Solution {
public:
    void printNos(int n) {
        // Base case: stop when n reaches 0
        if (n == 0) {
            return;
        }

        // Print the current number
        cout << n << " ";

        // Recursively print the remaining numbers
        printNos(n - 1);
    }
};

/*
==========================================================
DRY RUN:
==========================================================

Input:
n = 4

Execution:

printNos(4)
    Print 4
    Call printNos(3)

        printNos(3)
            Print 3
            Call printNos(2)

                printNos(2)
                    Print 2
                    Call printNos(1)

                        printNos(1)
                            Print 1
                            Call printNos(0)

                                printNos(0)
                                    Return (base case)

Output:
4 3 2 1

==========================================================
EDGE CASES:
==========================================================

1. n = 0
   Output: No numbers printed.
   The base case returns immediately.

2. n = 1
   Output: 1

3. n = 5
   Output: 5 4 3 2 1

==========================================================
WHY DOES IT PRINT IN DESCENDING ORDER?
==========================================================

The current number is printed BEFORE the recursive call.

For example:
    cout << n << " ";
    printNos(n - 1);

Therefore, 5 is printed first, then 4, then 3,
then 2, and finally 1.

If the print statement were placed AFTER the recursive
call, the numbers would be printed in ascending order.

==========================================================
TIME AND SPACE COMPLEXITY:
==========================================================

Time Complexity: O(n)
- The function processes each number from n down to 1.
- There are n recursive calls that print numbers.

Auxiliary Space Complexity: O(n)
- Recursive calls occupy the call stack.
- The maximum recursion depth is n + 1, including
  the base-case call for n >= 0.

==========================================================
KEY LEARNINGS:
==========================================================

1. Every recursive function needs a suitable base case.
2. Each call reduces the problem size by 1.
3. Printing before recursion produces descending order.
4. Printing after recursion produces ascending order.
5. Recursion uses the call stack instead of an explicit loop.
==========================================================
*/