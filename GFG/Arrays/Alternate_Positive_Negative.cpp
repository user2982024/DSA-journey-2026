// ============================================================
// Problem: Rearrange array in alternating positive & negative numbers
// Constraint: Preserve the original order of positives and negatives
// Approach: Use two auxiliary arrays to store positives and negatives,
//           then merge them back into the original array alternately.
// ============================================================

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    /*
     * Function: rearrange
     * -------------------
     * Rearranges the given array such that positive and negative numbers
     * alternate. Preserves the relative order of positives and negatives.
     *
     * Parameters:
     *   arr - reference to the vector of integers to rearrange
     *
     * Approach:
     *   1. Create two auxiliary arrays: positive[] and negative[]
     *      to store the numbers separately while preserving order.
     *   2. Use indices j and k to traverse positive[] and negative[]
     *      while merging them alternately back into arr[].
     *   3. If any numbers remain in either array after alternation,
     *      append them at the end.
     *
     * Time Complexity: O(n)
     *   - One pass to separate positives and negatives
     *   - One pass to merge alternately
     * Space Complexity: O(n)
     *   - Extra space for positive[] and negative[]
     *   - Required to preserve original relative order
     */
    void rearrange(vector<int> &arr) {
        vector<int> positive;
        vector<int> negative;

        // Step 1: Separate positive and negative numbers
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] >= 0) {
                positive.push_back(arr[i]);
            } else if (arr[i] < 0) {
                negative.push_back(arr[i]);
            }
        }

        // Step 2: Merge them alternately back into arr
        int i = 0;          // index for main array
        int j = 0;          // index for positive[]
        int k = 0;          // index for negative[]
        int n = positive.size();
        int m = negative.size();

        while (j < n && k < m) {
            arr[i] = positive[j];
            i ++;
            j ++;
            arr[i] = negative[k];
            i ++;
            k ++;
        }
        
        // Step 3: Append remaining positives, if any
        if (!positive.empty()) {
            while (j < n) {
                arr[i] = positive[j];
                i ++;
                j ++;
            }
        }
        
        // Step 4: Append remaining negatives, if any
        if (!negative.empty()) {
            while (k < m) {
                arr[i] = negative[k];
                i ++;
                k ++;
            }
        }
    }
};

// ============================================================
// Dry Run Example
// ------------------------------------------------------------
// Input:  [9, 4, -2, -1, 5, 0, -5, -3, 2]
// Positives: [9, 4, 5, 0, 2]
// Negatives: [-2, -1, -5, -3]
// Merge alternately:
//   i=0 -> 9
//   i=1 -> -2
//   i=2 -> 4
//   i=3 -> -1
//   i=4 -> 5
//   i=5 -> -5
//   i=6 -> 0
//   i=7 -> -3
//   i=8 -> 2
// Output: [9, -2, 4, -1, 5, -5, 0, -3, 2]
// ============================================================

// ============================================================
// Edge Cases Considered:
// 1. All positives -> array remains as is
// 2. All negatives -> array remains as is
// 3. Zeros included -> treated as positive (>=0)
// 4. Unequal counts -> remaining elements appended at end
// ============================================================

int main() {
    vector<int> arr = {9, 4, -2, -1, 5, 0, -5, -3, 2};
    Solution sol;
    sol.rearrange(arr);

    cout << "Rearranged array: ";
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
- O(n) to merge alternately
=> Total = O(n)

Space Complexity:
- O(n) extra space for positive[] and negative[]
- Required to preserve original relative order
=> Total = O(n)

Stability:
- Preserves the relative order of positive numbers
- Preserves the relative order of negative numbers
- Cannot be done in-place while preserving order
*/
