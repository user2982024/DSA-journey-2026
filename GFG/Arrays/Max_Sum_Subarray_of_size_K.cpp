/************************************************************
 *
 *  Problem: Maximum Sum Subarray of Size K
 *
 *  Description:
 *  Given an integer array arr and an integer k,
 *  return the maximum sum of any contiguous
 *  subarray of size k.
 *
 *  Approach:
 *  Fixed-Size Sliding Window Technique
 *
 *  Time Complexity: O(n)
 *  Space Complexity: O(1)
 *
 ************************************************************/

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:

    int maxSubarraySum(vector<int>& arr, int k) {

        int n = arr.size();

        // Edge Case Handling
        if (n == 0 || k > n || k <= 0) {
            return 0;
        }

        // Step 1: Compute first window sum
        long long windowSum = 0;

        for (int i = 0; i < k; i++) {
            windowSum += arr[i];
        }

        long long maxSum = windowSum;

        // Step 2: Slide window from index k to n-1
        for (int i = k; i < n; i++) {

            // Remove outgoing element
            windowSum -= arr[i - k];

            // Add incoming element
            windowSum += arr[i];

            // Update maximum sum
            if (windowSum > maxSum) {
                maxSum = windowSum;
            }
        }

        return static_cast<int>(maxSum);
    }
};


/***********************
 * Example Usage
 ***********************/
int main() {

    Solution obj;

    vector<int> arr;
    arr.push_back(2);
    arr.push_back(1);
    arr.push_back(5);
    arr.push_back(1);
    arr.push_back(3);
    arr.push_back(2);

    int k = 3;

    int result = obj.maxSubarraySum(arr, k);

    cout << "Maximum Sum Subarray of size "
         << k << " is: " << result << endl;

    return 0;
}