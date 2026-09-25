// ```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {

        int n = nums.size();

        // Step 1: Calculate the sum of the first window
        double currentSum = 0;

        for (int i = 0; i < k; i++) {
            currentSum += nums[i];
        }

        // The first window is our initial maximum
        double maxSum = currentSum;

        // Step 2: Slide the window
        for (int right = k; right < n; right++) {

            // Remove the element leaving the window
            currentSum -= nums[right - k];

            // Add the new element entering the window
            currentSum += nums[right];

            // Update maximum window sum
            maxSum = max(maxSum, currentSum);
        }

        // Step 3: Maximum average = maximum sum / window size
        return maxSum / k;
    }
};
// ```

// ### 🧠 Pattern

// ```text
// Build first window
//        ↓
// Calculate its state
//        ↓
// Slide window
//        ↓
// Remove outgoing element
//        ↓
// Add incoming element
//        ↓
// Update answer
// ```

// ### Complexity

// * **Time:** `O(n)`
// * **Space:** `O(1)`

// ### Why this version is cleaner

// Instead of maintaining both `left` and `right`, we can observe that when `right` is at a particular position, the element leaving the window is always:

// ```cpp
// nums[right - k]
// ```

// So one pointer is enough for the implementation.

// Your original solution was **correct and accepted**; this version is simply a cleaner form that I would prefer you keep as your reference implementation.

// And yes — **Day 5 can end here for today.** You learned a completely new pattern, struggled with it, debugged it, solved multiple fixed-window problems, and reached the point where you can explain the mechanism yourself. Tomorrow, inshallah, we'll continue with **LeetCode 438 and then move toward variable-size sliding windows**. 🔥
