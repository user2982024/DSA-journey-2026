// File: max_subarray_sum.cpp
// Author: Sheikh Abrar
// Description: Find the largest sum contiguous subarray using intuitive Kadane's logic.
// Approach: 
//   Traverse the array once, keep adding elements to a running sum (currentSum).
//   If at any point currentSum becomes negative, reset it to zero because 
//   negative values decrease our future sum and can't contribute to the maximum sum.
//   Keep track of the largestSum found so far during the traversal.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSubarraySum(vector<int> &arr) {
        // Handle single-element edge case
        if (arr.size() == 1) {
            return arr[0];
        }

        int largestSum = INT_MIN;  // Stores the maximum sum encountered so far
        int currentSum = 0;        // Running sum of the current subarray

        for (int i = 0; i < arr.size(); i++) {
            currentSum = currentSum + arr[i];   // Keep adding elements
            largestSum = max(largestSum, currentSum);  // Update max if current sum is greater

            // Core condition:
            // If the currentSum becomes negative, it means it's reducing our result.
            // So, we reset it to zero to start a new subarray from the next element.
            if (currentSum < 0) {
                currentSum = 0;
            }
        }

        return largestSum;
    }
};

// Helper function to print result
int main() {
    Solution sol;

    vector<int> arr = {-2, -3, 4, -1, -2, 1, 5, -3};

    cout << "Array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    int maxSum = sol.maxSubarraySum(arr);

    cout << "Maximum Subarray Sum: " << maxSum << endl;

    return 0;
}

/*
Explanation of Core Condition:
--------------------------------
- When currentSum < 0:
    We reset currentSum = 0 because a negative sum won't help in 
    forming a maximum contiguous subarray. It only reduces our total.
    In other words, if our running sum becomes negative, 
    it's better to start fresh from the next index.

- When currentSum >= 0:
    We continue adding values because we are still on a positive gain path.

Key Points:
------------
* The line "if (currentSum < 0) currentSum = 0;" is the core logic.
* The rest is just simple accumulation and comparison.
* This algorithm ensures O(n) time and O(1) space.
* Works efficiently for all integer arrays (positive, negative, mixed).

Complexity:
-----------
Time Complexity: O(n)
Space Complexity: O(1)
*/
