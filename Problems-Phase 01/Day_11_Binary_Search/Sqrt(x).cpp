
/*
============================================================
Problem: Sqrt(x)
Platform: LeetCode
Problem Number: 69
Topic: Binary Search
Difficulty: Easy
============================================================

PROBLEM STATEMENT:
------------------
Given a non-negative integer x, return the square root of x
rounded down to the nearest integer.

The returned value must be an integer.

You must not use built-in exponent functions or operators
that calculate powers or square roots directly.

Examples of disallowed approaches include:
    sqrt(x)
    pow(x, 0.5)


EXAMPLE 1:
----------
Input:
x = 4

Output:
2

Explanation:
The square root of 4 is exactly 2.


EXAMPLE 2:
----------
Input:
x = 8

Output:
2

Explanation:
The square root of 8 is approximately 2.828.

Rounding down to the nearest integer gives 2.


EXAMPLE 3:
----------
Input:
x = 0

Output:
0

Explanation:
The square root of 0 is 0.


============================================================
APPROACH: BINARY SEARCH
============================================================

We need to find the integer square root of x.

Instead of calculating the square root directly, we search
for the largest integer whose square is less than or equal
to x.

For example, if x = 8:

1 * 1 = 1
2 * 2 = 4
3 * 3 = 9

Since 2 * 2 <= 8 but 3 * 3 > 8, the answer is 2.


INITIALIZATION:
---------------

start = 0
end   = x
ans   = 0

The search range is from 0 to x.

The variable ans stores the best valid candidate found
so far, meaning an integer whose square is less than x
or equal to x.


CALCULATING THE MIDDLE:
-----------------------

mid = start + (end - start) / 2

We compare mid * mid with x.


CASE 1: mid * mid == x
----------------------
We found an exact square root.

Return mid immediately.


CASE 2: mid * mid < x
---------------------
The square of mid is smaller than x.

This means mid could be the integer square root, but
a larger valid candidate may exist to its right.

Therefore:
start = mid + 1;
ans = mid;


CASE 3: mid * mid > x
---------------------
The square of mid is greater than x.

Therefore, mid and every larger number are too large.

We search to the left:

end = mid - 1;


AFTER THE LOOP:
---------------
When start becomes greater than end, the search ends.

The variable ans contains the largest valid candidate
whose square is less than x, unless an exact square root
was found earlier.

Return ans.


============================================================
COMPLETE C++ SOLUTION
============================================================

NOTE:
The solution below is preserved exactly as originally
written. No changes have been made to your code.
*/

#include <iostream>
using namespace std;

class Solution {
public:
    int mySqrt(int x) {
        int start = 0;
        int end = x;
        int ans = 0;

        while (start <= end) {
            long long mid = start + (end - start) / 2;

            if (mid * mid == x) {
                return mid;
            }

            else if (mid * mid < x) {
                start = mid + 1;
                ans = mid;
            }

            else {
                end = mid - 1;
            }
        }

        return ans;
    }
};


/*
============================================================
WHERE WE GOT STUCK: INTEGER OVERFLOW
============================================================

During testing, we encountered a runtime error similar to:

    1073697799 * 1073697799 cannot be represented in type int

WHY DID THIS HAPPEN?
--------------------

The int data type has a maximum value of approximately:

    2,147,483,647

However, squaring a large integer can exceed that limit.

For example:

    1,073,697,799 * 1,073,697,799

produces a value much larger than the maximum value that
a signed 32-bit int can represent.

This causes signed integer overflow, which is undefined
behavior in C++.


HOW DID WE SOLVE IT?
--------------------

We changed the type of mid from int to long long:

    long long mid = start + (end - start) / 2;

A long long can represent much larger integer values.

Because mid is a long long, the expression:

    mid * mid

is also evaluated using long long arithmetic.

This prevents overflow for the input range of this problem.

IMPORTANT:
The multiplication itself must be performed using a
sufficiently wide type. Assigning an already-overflowed
int multiplication result to a long long afterward would
not fix the issue.

Your solution correctly makes the multiplication safe
by declaring mid as long long.


============================================================
STEP-BY-STEP DRY RUN 1: PERFECT SQUARE
============================================================

Input:
x = 4

Initial values:
start = 0
end   = 4
ans   = 0


Iteration 1:
------------
mid = 0 + (4 - 0) / 2
mid = 2

mid * mid = 4

Since mid * mid == x:
return mid;

Output:
2


============================================================
STEP-BY-STEP DRY RUN 2: NON-PERFECT SQUARE
============================================================

Input:
x = 8

Initial values:
start = 0
end   = 8
ans   = 0


Iteration 1:
------------
mid = 0 + (8 - 0) / 2
mid = 4

mid * mid = 16

Since 16 > 8:
end = mid - 1
end = 3

Current state:
start = 0
end   = 3
ans   = 0


Iteration 2:
------------
mid = 0 + (3 - 0) / 2
mid = 1

mid * mid = 1

Since 1 < 8:
start = mid + 1
start = 2

ans = mid
ans = 1

Current state:
start = 2
end   = 3
ans   = 1


Iteration 3:
------------
mid = 2 + (3 - 2) / 2
mid = 2

mid * mid = 4

Since 4 < 8:
start = mid + 1
start = 3

ans = mid
ans = 2

Current state:
start = 3
end   = 3
ans   = 2


Iteration 4:
------------
mid = 3 + (3 - 3) / 2
mid = 3

mid * mid = 9

Since 9 > 8:
end = mid - 1
end = 2

Current state:
start = 3
end   = 2
ans   = 2

Now start > end, so the loop terminates.

Return ans.

Output:
2

Explanation:
The square root of 8 is approximately 2.828.

The required answer is the integer part, which is 2.


============================================================
STEP-BY-STEP DRY RUN 3: ZERO
============================================================

Input:
x = 0

Initial values:
start = 0
end   = 0
ans   = 0


Iteration 1:
------------
mid = 0 + (0 - 0) / 2
mid = 0

mid * mid = 0

Since mid * mid == x:
return mid;

Output:
0


============================================================
STEP-BY-STEP DRY RUN 4: x = 1
============================================================

Input:
x = 1

Initial values:
start = 0
end   = 1
ans   = 0


Iteration 1:
------------
mid = 0 + (1 - 0) / 2
mid = 0

mid * mid = 0

Since 0 < 1:
start = 1
ans = 0


Iteration 2:
------------
mid = 1 + (1 - 1) / 2
mid = 1

mid * mid = 1

Since mid * mid == x:
return mid;

Output:
1


============================================================
EDGE CASES
============================================================

1. ZERO
-------
Input:
x = 0

Output:
0


2. ONE
------
Input:
x = 1

Output:
1


3. PERFECT SQUARE
-----------------
Input:
x = 16

Output:
4


4. NON-PERFECT SQUARE
---------------------
Input:
x = 10

Output:
3

Explanation:
3 * 3 = 9 <= 10
4 * 4 = 16 > 10


5. LARGE INPUT
--------------
Input:
x = 2147395600

Output:
46340

Explanation:
46340 * 46340 = 2147395600


6. MAXIMUM 32-BIT SIGNED INTEGER INPUT
--------------------------------------
Input:
x = 2147483647

Output:
46340

Explanation:
46340 * 46340 = 2147395600, which is less than x.

46341 * 46341 = 2147488281, which is greater than x.

Therefore, the integer square root is 46340.


============================================================
TIME COMPLEXITY ANALYSIS
============================================================

The search interval is reduced by approximately half
during each iteration.

The initial search range is from 0 to x.

Binary search takes logarithmic time relative to the
size of this range.

Therefore:

TIME COMPLEXITY = O(log x)

More precisely, the number of iterations is proportional
to log2(x + 1).


============================================================
SPACE COMPLEXITY ANALYSIS
============================================================

The algorithm uses only a fixed number of variables:

start, end, ans, and mid.

No additional data structures are used, and there is
no recursion.

Therefore:

AUXILIARY SPACE COMPLEXITY = O(1)


============================================================
COMMON MISTAKES TO AVOID
============================================================

1. USING A BUILT-IN SQUARE ROOT FUNCTION
----------------------------------------
The problem requires implementing the integer square root
without using a built-in square root function.


2. IGNORING INTEGER OVERFLOW
----------------------------
Using int for mid * mid can overflow for large values.

Use a sufficiently wide type for the multiplication.

Your solution uses long long for mid, which ensures
that mid * mid is evaluated using long long arithmetic.


3. FORGETTING TO SAVE A VALID CANDIDATE
---------------------------------------
When mid * mid < x, mid is a valid candidate.

Update:
ans = mid;


4. MOVING IN THE WRONG DIRECTION
--------------------------------
If mid * mid < x:
    Search right.

If mid * mid > x:
    Search left.


5. RETURNING MID WHEN IT IS TOO LARGE
-------------------------------------
If mid * mid > x, mid cannot be the answer.

The search must continue to the left.


6. CONFUSING THE EXACT SQUARE ROOT WITH THE FLOOR
-------------------------------------------------
For x = 8, the mathematical square root is approximately
2.828, but the required integer answer is 2.

The problem asks for the square root rounded down.


============================================================
KEY LEARNINGS
============================================================

1. Binary search can be applied to numerical ranges,
   not only sorted arrays.

2. We can find the integer square root by searching for
   the largest integer whose square does not exceed x.

3. If mid * mid < x, save mid and search right.

4. If mid * mid > x, search left.

5. If mid * mid == x, return mid immediately.

6. Using long long for mid prevents overflow in the
   multiplication for the problem's input constraints.

7. Time complexity is O(log x).

8. Auxiliary space complexity is O(1).


============================================================
FINAL SUMMARY
============================================================

Problem:
Find the integer square root of a non-negative integer.

Approach:
Binary search.

If mid * mid == x:
Return mid.

If mid * mid < x:
Save mid and search right.

If mid * mid > x:
Search left.

If no exact square root is found:
Return the best valid candidate stored in ans.

Time Complexity:
O(log x)

Auxiliary Space Complexity:
O(1)

Main concept learned:
Binary search can solve numerical problems efficiently,
and careful data type selection prevents integer overflow.

============================================================
END OF FILE
============================================================
*/
