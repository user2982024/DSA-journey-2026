/*
===============================================================
PROBLEM: Maximum Subarray Sum (Kadane’s Algorithm)
Platform: GeeksforGeeks / LeetCode (Classic Problem)
Author: Sheikh Abrar (DSA Challenge)
===============================================================

PROBLEM STATEMENT
-----------------
Given an array of integers (positive, negative, or zero),
find the contiguous subarray (containing at least one number)
which has the maximum possible sum, and return that sum.

This is known as the "Maximum Subarray Problem".

---------------------------------------------------------------
INTUITION
---------------------------------------------------------------
At every index, we must decide:

1) Should we continue the previous subarray?
2) Or should we start a new subarray from current element?

If the running sum becomes negative, it will only reduce
future subarray sums. So we discard it and restart.

This greedy decision at every index forms Kadane’s Algorithm.

---------------------------------------------------------------
KEY OBSERVATIONS
---------------------------------------------------------------
1) Running sum (currentSum) tracks current subarray.
2) largestSum tracks best answer so far.
3) Update largestSum BEFORE resetting currentSum.
4) Initialize largestSum = INT_MIN to handle all-negative arrays.

---------------------------------------------------------------
COMMON MISTAKES (IMPORTANT LEARNING)
---------------------------------------------------------------
Mistake 1:
Resetting currentSum BEFORE updating largestSum.
This fails for arrays with all negative numbers.

Mistake 2:
Initializing largestSum = 0.
Wrong when all elements are negative.

Correct approach:
largestSum must start from INT_MIN.

---------------------------------------------------------------
EDGE CASES HANDLED
---------------------------------------------------------------
✔ Single element array
✔ All negative numbers
✔ All positive numbers
✔ Mixed values
✔ Large inputs

---------------------------------------------------------------
TIME COMPLEXITY
---------------------------------------------------------------
O(N) → Single traversal

SPACE COMPLEXITY
---------------------------------------------------------------
O(1) → No extra space used

---------------------------------------------------------------
ALGORITHM STEPS
---------------------------------------------------------------
1) Initialize:
      currentSum = 0
      largestSum = INT_MIN

2) Traverse array:
      add element to currentSum
      update largestSum
      if currentSum < 0 → reset to 0

3) Return largestSum

===============================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSubarraySum(vector<int> &arr) {

        // Running sum of current subarray
        int currentSum = 0;

        // Best sum found so far (must handle negative arrays)
        int largestSum = INT_MIN;

        int n = arr.size();

        for (int i = 0; i < n; i++) {

            // Extend current subarray
            currentSum += arr[i];

            // Update best answer found so far
            if (currentSum > largestSum) {
                largestSum = currentSum;
            }

            // If running sum becomes harmful, discard it
            if (currentSum < 0) {
                currentSum = 0;
            }
        }

        return largestSum;
    }
};

/*
===============================================================
DRY RUN EXAMPLE
---------------------------------------------------------------
Array: [-2, -3, 4, -1, -2, 1, 5, -3]

i=0 → current=-2 → largest=-2 → reset
i=1 → current=-3 → largest=-2 → reset
i=2 → current=4  → largest=4
i=3 → current=3  → largest=4
i=4 → current=1  → largest=4
i=5 → current=2  → largest=4
i=6 → current=7  → largest=7
i=7 → current=4  → largest=7

Answer = 7

Subarray = [4, -1, -2, 1, 5]

===============================================================
*/