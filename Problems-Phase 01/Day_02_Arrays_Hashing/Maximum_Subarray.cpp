#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

/*
    LeetCode #53
    Maximum Subarray

    Problem:
    Given an integer array nums, find the subarray with the largest sum
    and return its sum.

    A subarray must contain at least one element and consist of
    contiguous elements.

    Example:
    Input:
        nums = [-2,1,-3,4,-1,2,1,-5,4]

    Output:
        6

    Explanation:
        The subarray [4,-1,2,1] has the maximum sum.

        4 + (-1) + 2 + 1 = 6
*/


class Solution {
public:

    int maxSubArray(vector<int>& nums) {

        // Stores the sum of the current subarray.
        int currentSum = 0;

        // Stores the maximum sum found so far.
        // INT_MIN is important because the array can contain
        // only negative numbers.
        int maxSum = INT_MIN;

        int n = nums.size();

        for (int i = 0; i < n; i++) {

            // Add the current element to the current subarray sum.
            currentSum += nums[i];

            /*
                Update maxSum BEFORE resetting currentSum.

                This is important for the all-negative case.

                Example:
                    nums = {-2, -1}

                When currentSum = -2, maxSum must become -2
                before currentSum is reset to 0.
            */
            maxSum = max(maxSum, currentSum);

            /*
                If the current sum becomes negative, it cannot help
                a future subarray achieve a larger sum.

                Therefore, discard the current subarray and start
                a new one from the next element.
            */
            if (currentSum < 0) {
                currentSum = 0;
            }
        }

        return maxSum;
    }
};


/*
    ------------------------------------------------------------
    APPROACH — KADANE'S ALGORITHM
    ------------------------------------------------------------

    We maintain two values:

    1. currentSum
       The sum of the current contiguous subarray.

    2. maxSum
       The largest subarray sum found so far.

    At every element:

        currentSum += nums[i]

    Then:

        maxSum = max(maxSum, currentSum)

    If currentSum becomes negative:

        currentSum = 0

    Why?

    A negative sum can only decrease the sum of a future
    subarray, so there is no benefit in carrying it forward.

    ------------------------------------------------------------
    IMPORTANT EDGE CASE
    ------------------------------------------------------------

    Consider:

        nums = {-2, -1}

    If we reset currentSum to 0 BEFORE updating maxSum:

        currentSum = -2
        currentSum = 0
        maxSum = max(INT_MIN, 0)
        maxSum = 0

    This would incorrectly return 0.

    However, the problem requires the subarray to contain
    at least one element.

    The correct answer is:

        -1

    Therefore, we update maxSum BEFORE resetting currentSum.

    ------------------------------------------------------------
    COMPLEXITY
    ------------------------------------------------------------

    Time Complexity:
        O(n)

    We traverse the array exactly once.

    Space Complexity:
        O(1)

    We use only a constant number of variables.

    ------------------------------------------------------------
    KEY PATTERN
    ------------------------------------------------------------

    This is Kadane's Algorithm.

    The main decision at every position is:

        Should I continue the current subarray?

    If the current sum is positive:
        Continue.

    If the current sum becomes negative:
        Discard it and start fresh.

    ------------------------------------------------------------
    DRY RUN
    ------------------------------------------------------------

    nums = [-2,1,-3,4,-1,2,1,-5,4]

    The maximum subarray is:

        [4,-1,2,1]

    Its sum is:

        4 + (-1) + 2 + 1 = 6

    Therefore:

        Answer = 6
*/