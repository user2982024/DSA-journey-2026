#include <bits/stdc++.h>
using namespace std;

/*
    Problem:
    Maximum Sum of a Subarray of Size K

    Approach:
    - Calculate the sum of the first window of size K.
    - Slide the window one position at a time.
    - Remove the element leaving the window.
    - Add the new element entering the window.
    - Keep track of the maximum window sum.

    Time Complexity:
    O(n)

    Space Complexity:
    O(1) auxiliary space.
*/

class Solution {
public:
    int maxSubarraySum(vector<int>& arr, int k) {
        int n = arr.size();

        int start = 0;
        int end = k - 1;
        int currentSum = 0;
        int maxSum = 0;

        // Calculate the sum of the first window.
        for (int i = 0; i <= end; i++) {
            currentSum += arr[i];
        }

        maxSum = currentSum;

        // Slide the window across the array.
        while (end < n) {
            // Remove the element leaving the window.
            currentSum -= arr[start];
            start++;

            // Add the new element entering the window.
            end++;

            // No complete window remains.
            if (end == n) {
                break;
            }

            currentSum += arr[end];

            // Update the maximum sum.
            maxSum = max(maxSum, currentSum);
        }

        return maxSum;
    }
};

int main() {
    Solution solution;

    vector<int> arr = {100, 200, 300, 400};
    int k = 2;

    int result = solution.maxSubarraySum(arr, k);

    cout << "Maximum sum of a subarray of size "
         << k << ": " << result << '\n';

    return 0;
}