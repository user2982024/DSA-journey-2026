// ============================================================
// Problem: Segregate Positive and Negative Elements
// Constraint: Preserve the original order of positives and negatives
// Approach: Use two auxiliary arrays for positives and negatives,
//           then overwrite the original array.
// ============================================================

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    /*
     * Function: segregateElements
     * ---------------------------
     * Rearranges the array such that all positive numbers appear
     * before all negative numbers. The relative order of positives
     * and negatives is preserved.
     *
     * Parameters:
     *   arr - reference to the vector of integers to rearrange
     *
     * Approach:
     *   1. Separate all positives and negatives into two arrays
     *      to preserve order.
     *   2. Copy positives first into original array.
     *   3. Then copy negatives into original array.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    void segregateElements(vector<int>& arr) {
        vector<int> positive;
        vector<int> negative;

        // Step 1: Separate positives and negatives
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] >= 0) {
                positive.push_back(arr[i]);
            } else {
                negative.push_back(arr[i]);
            }
        }

        // Step 2: Copy positives back to original array
        int i = 0, j = 0, k = 0;
        while (j < positive.size()) {
            arr[i] = positive[j];
            i ++;
            j ++;
        }

        // Step 3: Copy negatives back to original array
        while (k < negative.size()) {
            arr[i] = negative[k];
            i ++;
            k ++;
        }
    }
};

// ============================================================
// Dry Run Example
// ------------------------------------------------------------
// Input:  [9, -3, 4, -2, 5, -7, 0, -1]
// Positives: [9, 4, 5, 0]
// Negatives: [-3, -2, -7, -1]
// Output: [9, 4, 5, 0, -3, -2, -7, -1]
// ============================================================

// ============================================================
// Edge Cases Considered:
// 1. All positives -> array unchanged
// 2. All negatives -> array unchanged
// 3. Zeros -> treated as positive (>=0)
// ============================================================

int main() {
    vector<int> arr = {9, -3, 4, -2, 5, -7, 0, -1};
    Solution sol;
    sol.segregateElements(arr);

    cout << "Segregated array: ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}

/*
Complexity Analysis:
--------------------
Time Complexity:
- O(n) to separate positives and negatives
- O(n) to copy back to arr
=> Total = O(n)

Space Complexity:
- O(n) extra space for positive[] and negative[]
- Required to preserve original relative order
=> Total = O(n)

Stability:
- Relative order of positive numbers is preserved
- Relative order of negative numbers is preserved
*/
