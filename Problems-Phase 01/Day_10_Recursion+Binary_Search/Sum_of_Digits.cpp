
/*
==========================================================
Problem: Sum of Digits
Platform: GeeksforGeeks
Topic: Recursion, Mathematics
==========================================================

PROBLEM STATEMENT:
Given a non-negative integer n, find the sum of its digits
using recursion.

Example 1:
Input:
n = 1234

Output:
10

Explanation:
1 + 2 + 3 + 4 = 10

Example 2:
Input:
n = 987

Output:
24

Explanation:
9 + 8 + 7 = 24

==========================================================
APPROACH: RECURSION
==========================================================

1. BASE CASE:
   If n == 0, return 0.
   There are no remaining digits to add.

2. EXTRACT THE LAST DIGIT:
   digit = n % 10

   The modulo operator returns the last digit.

   Example:
   1234 % 10 = 4

3. REMOVE THE LAST DIGIT:
   n /= 10

   Integer division removes the last digit.

   Example:
   1234 / 10 = 123

4. RECURSIVE CALL:
   Return digit + sumOfDigits(n).

   The function adds the last digit to the sum of all
   the digits remaining in n.

==========================================================
CODE:
==========================================================
*/

#include <iostream>
using namespace std;

class Solution {
public:
    int sumOfDigits(int n) {
        // Base case: no digits remain
        if (n == 0) {
            return 0;
        }

        // Extract the last digit
        int digit = n % 10;

        // Remove the last digit
        n /= 10;

        // Add the extracted digit to the sum of remaining digits
        return digit + sumOfDigits(n);
    }
};

/*
==========================================================
DRY RUN:
==========================================================

Input:
n = 1234

The recursive calls extract digits from right to left.

CALLS (RECURSION DESCENT):
----------------------------------------------------------
sumOfDigits(1234)
    digit = 4
    return 4 + sumOfDigits(123)

sumOfDigits(123)
    digit = 3
    return 3 + sumOfDigits(12)

sumOfDigits(12)
    digit = 2
    return 2 + sumOfDigits(1)

sumOfDigits(1)
    digit = 1
    return 1 + sumOfDigits(0)

sumOfDigits(0)
    return 0  (base case)

----------------------------------------------------------
RETURN VALUES (RECURSION UNWINDING):
----------------------------------------------------------

sumOfDigits(0)    = 0
sumOfDigits(1)    = 1 + 0       = 1
sumOfDigits(12)   = 2 + 1       = 3
sumOfDigits(123)  = 3 + 3       = 6
sumOfDigits(1234) = 4 + 6       = 10

Final Output:
10

==========================================================
EDGE CASES:
==========================================================

1. n = 0
   Output: 0
   The base case returns immediately.

2. n = 7
   Output: 7

3. n = 10
   Output: 1 + 0 = 1

4. n = 999
   Output: 9 + 9 + 9 = 27

5. n = 1005
   Output: 1 + 0 + 0 + 5 = 6

==========================================================
TIME AND SPACE COMPLEXITY:
==========================================================

Time Complexity: O(d)
- Each recursive call processes one digit.
- d represents the number of digits in n.
- Since d = floor(log10(n)) + 1 for n > 0,
  the time complexity can also be expressed as O(log n).

Auxiliary Space Complexity: O(d)
- Each digit creates a recursive call.
- The maximum recursion depth is d + 1, including
  the base-case call.

==========================================================
KEY LEARNINGS:
==========================================================

1. n % 10 extracts the last digit.
2. n / 10 removes the last digit through integer division.
3. Each recursive call reduces the number of digits.
4. The base case prevents infinite recursion.
5. The return statement combines the current digit with
   the result of the recursive call.
6. Digits are processed from right to left, but addition
   produces the same sum regardless of digit order.

==========================================================
*/