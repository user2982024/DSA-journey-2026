/************************************************************
 *
 *  Problem: Maximum Average Subarray I
 *  Platform: LeetCode
 *
 *  Description:
 *  Given an integer array nums and an integer k,
 *  return the maximum average value of any contiguous
 *  subarray of length k.
 *
 *  Approach:
 *  Fixed-Size Sliding Window Technique
 *
 *  Core Idea:
 *  - Compute sum of first k elements (initial window)
 *  - Slide window across array:
 *      Remove outgoing element
 *      Add incoming element
 *  - Track maximum window sum
 *  - Return maxSum / k
 *
 *  Time Complexity: O(n)
 *  Space Complexity: O(1)
 *
 ************************************************************/

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class Solution {
public:

    double findMaxAverage(vector<int>& nums, int k) {

        int n = nums.size();

        // Edge Case: If k is greater than array size
        // (Though LeetCode guarantees k <= n)
        if (k > n || n == 0) {
            return 0.0;
        }

        // Step 1: Compute sum of first window (0 to k-1)
        long long windowSum = 0;

        for (int i = 0; i < k; i++) {
            windowSum += nums[i];
        }

        // Initialize maxSum with first window sum
        long long maxSum = windowSum;

        // Step 2: Slide the window
        for (int i = k; i < n; i++) {

            // Remove outgoing element
            windowSum -= nums[i - k];

            // Add incoming element
            windowSum += nums[i];

            // Update maximum sum if needed
            if (windowSum > maxSum) {
                maxSum = windowSum;
            }
        }

        // Step 3: Return maximum average
        return static_cast<double>(maxSum) / k;
    }
};


/***********************
 * Example Usage
 ***********************/
int main() {

    Solution obj;

    vector<int> nums;
    nums.push_back(1);
    nums.push_back(12);
    nums.push_back(-5);
    nums.push_back(-6);
    nums.push_back(50);
    nums.push_back(3);

    int k = 4;

    double result = obj.findMaxAverage(nums, k);

    cout << "Maximum Average Subarray of size "
         << k << " is: " << result << endl;

    return 0;
}