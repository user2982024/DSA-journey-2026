
/*
==========================================================
Problem: Sum of First N Natural Numbers Using Recursion
Topic: Recursion
Language: C++
==========================================================

PROBLEM STATEMENT:
Given a non-negative integer N, calculate the sum of the
first N natural numbers using recursion.

The sum is:

S(N) = 1 + 2 + 3 + ... + N

Examples:

Example 1:
Input:
5

Output:
15

Explanation:
1 + 2 + 3 + 4 + 5 = 15


Example 2:
Input:
3

Output:
6

Explanation:
1 + 2 + 3 = 6


Example 3:
Input:
0

Output:
0

Explanation:
The sum of zero natural numbers is 0.

==========================================================
APPROACH: RECURSION
==========================================================

1. BASE CASE:
   If n == 0, return 0.

   This stops the recursive calls.

2. RECURSIVE CASE:
   Return n + calcSum(n - 1).

   The current value n is added to the sum of all
   smaller positive integers.

3. Every recursive call reduces n by 1.

4. When n becomes 0, the function returns 0.
   The pending recursive calls then return their results.

==========================================================
CODE:
==========================================================
*/

#include <iostream>
using namespace std;

int calcSum(int n) {
    // Base case
    if (n == 0) {
        return 0;
    }

    // Add n to the sum of all numbers from 1 to n - 1
    return n + calcSum(n - 1);
}

int main() {
    int n;
    cin >> n;

    cout << calcSum(n);

    return 0;
}

/*
==========================================================
DRY RUN:
==========================================================

Input:
n = 4

RECURSION DESCENT:
----------------------------------------------------------

calcSum(4)
    return 4 + calcSum(3)

calcSum(3)
    return 3 + calcSum(2)

calcSum(2)
    return 2 + calcSum(1)

calcSum(1)
    return 1 + calcSum(0)

calcSum(0)
    return 0  (base case)


RECURSION UNWINDING:
----------------------------------------------------------

calcSum(0) = 0

calcSum(1) = 1 + 0 = 1

calcSum(2) = 2 + 1 = 3

calcSum(3) = 3 + 3 = 6

calcSum(4) = 4 + 6 = 10


Final Output:
10

==========================================================
EDGE CASES:
==========================================================

1. n = 0
   Output: 0

2. n = 1
   Output: 1

3. n = 2
   Output: 3

4. n = 5
   Output: 15

5. n = 10
   Output: 55

Note:
The function assumes n is non-negative.
Negative inputs are not supported by this recursive
definition because n would continue decreasing away
from the base case.

==========================================================
TIME AND SPACE COMPLEXITY:
==========================================================

Time Complexity: O(n)
- Each value from n down to 1 is processed once.
- There are n + 1 function calls, including calcSum(0).

Auxiliary Space Complexity: O(n)
- Each recursive call occupies stack space.
- The maximum recursion depth is n + 1.

==========================================================
MATHEMATICAL FORMULA:
==========================================================

The sum can also be calculated using:

S(n) = n * (n + 1) / 2

For example, when n = 5:

S(5) = 5 * 6 / 2 = 15

However, this solution deliberately uses recursion
to practice recursive problem-solving.

==========================================================
KEY LEARNINGS:
==========================================================

1. The base case stops the recursion.
2. Each recursive call reduces the problem size.
3. The return value combines the current number with
   the result of the smaller subproblem.
4. Recursive calls return values while unwinding.
5. Recursion has O(n) time and O(n) stack space here.
6. The mathematical formula solves this problem in O(1)
   time, but recursion is useful for learning the concept.

==========================================================
*/