/*
===============================================================================
PROBLEM: Maximum Subarray (Kadane’s Algorithm)
Platform: LeetCode / GFG

Given an integer array nums, find the contiguous subarray (containing at least
one number) which has the largest sum and return that sum.

A subarray is a continuous part of the array.

Example:
Input:  [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: [4, -1, 2, 1] has the largest sum = 6
===============================================================================
*/

/*
===============================================================================
INTUITION

Brute force approach:
- Generate all subarrays
- Compute sum of each
- Track maximum

Time complexity: O(n^2) or O(n^3) ❌ too slow

Optimized idea (Kadane’s Algorithm):

If current running sum becomes negative,
it will only reduce future sums.

So we discard it and start fresh.

At every index:
1. Add current element to running sum
2. Update global maximum
3. If running sum < 0 → reset to 0

BUT IMPORTANT:
We must track max BEFORE resetting,
otherwise all-negative arrays fail.
===============================================================================
*/

/*
===============================================================================
ALGORITHM

1. Initialize:
   currentSum = 0
   largestSum = INT_MIN

2. Traverse array:
   currentSum += nums[i]
   update largestSum
   if currentSum < 0 → reset to 0

3. Return largestSum
===============================================================================
*/

/*
===============================================================================
EDGE CASES

1. All numbers negative
   Example: [-5, -2, -8]
   Answer = largest element = -2

Why it works?
Because we update largestSum BEFORE resetting currentSum.

2. Single element array
   Works automatically.

3. Mixed positive and negative
   Normal Kadane behavior.
===============================================================================
*/

/*
===============================================================================
DRY RUN

nums = [-2,1,-3,4,-1,2,1,-5,4]

i   num   currentSum   largestSum
---------------------------------
0   -2    -2           -2
          reset→0

1    1     1            1
2   -3    -2            1
          reset→0

3    4     4            4
4   -1     3            4
5    2     5            5
6    1     6            6
7   -5     1            6
8    4     5            6

Final Answer = 6
===============================================================================
*/

/*
===============================================================================
TIME & SPACE COMPLEXITY

Time Complexity  : O(n)
Space Complexity : O(1)

Single pass, constant memory.
===============================================================================
*/

#include <vector>
#include <climits>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {

        int n = nums.size();

        int currentSum = 0;
        int largestSum = INT_MIN;

        for (int i = 0; i < n; i++) {

            currentSum += nums[i];

            // Update best answer found so far
            if (currentSum > largestSum) {
                largestSum = currentSum;
            }

            // If running sum becomes negative, discard it
            if (currentSum < 0) {
                currentSum = 0;
            }
        }

        return largestSum;
    }
};