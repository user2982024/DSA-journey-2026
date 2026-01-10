// ============================================================
// Problem: Rearrange array in alternating positive & negative numbers
// Constraint: Preserve the original order of positives and negatives
// Goal: Alternate positive and negative elements as much as possible
// ============================================================

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * Function: rearrange
     * -------------------
     * Rearranges the given array so that positive and negative numbers
     * alternate. Order of appearance of positives and negatives is preserved.
     *
     * Parameters:
     *   arr - reference to the vector of integers to be rearranged
     *
     * Approach:
     *   1. Separate all positive and negative numbers into two arrays
     *      while maintaining their original order.
     *   2. Merge them back into the original array alternately:
     *      positive, negative, positive, negative, ...
     *   3. If one array is exhausted, append remaining elements from the
     *      other array.
     *
     * Time Complexity: O(n)
     *   - One pass to separate positives and negatives -> O(n)
     *   - One pass to merge them alternately -> O(n)
     *   - Total = O(n + n) = O(n)
     *
     * Space Complexity: O(n)
     *   - Two extra vectors to store positives and negatives
     *   - Cannot reduce space while preserving order
     */
    void rearrange(vector<int> &arr) {
        vector<int> positive;  // stores positive numbers
        vector<int> negative;  // stores negative numbers

        // Step 1: Separate positive and negative numbers
        for (int num : arr) {
            if (num >= 0)
                positive.push_back(num);
            else
                negative.push_back(num);
        }

        int i = 0;              // Index for main array
        int posIdx = 0, negIdx = 0;
        int n = positive.size();
        int m = negative.size();

        // Step 2: Merge them alternately
        while (posIdx < n && negIdx < m) {
            arr[i++] = positive[posIdx++];
            arr[i++] = negative[negIdx++];
        }

        // Step 3: Append remaining positives if any
        while (posIdx < n)
            arr[i++] = positive[posIdx++];

        // Step 4: Append remaining negatives if any
        while (negIdx < m)
            arr[i++] = negative[negIdx++];
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
//   i=8 -> 2 (remaining positive)
// Output: [9, -2, 4, -1, 5, -5, 0, -3, 2]
// ============================================================

// ============================================================
// Edge Cases Considered:
// 1. All positive numbers -> remains unchanged
// 2. All negative numbers -> remains unchanged
// 3. Zeros included -> treated as positive (>=0)
// 4. Unequal numbers of positives & negatives -> remaining elements appended
// ============================================================

int main() {
    vector<int> arr = {9, 4, -2, -1, 5, 0, -5, -3, 2};
    Solution obj;
    obj.rearrange(arr);

    cout << "Rearranged array: ";
    for (int x : arr)
        cout << x << " ";
    cout << endl;

    return 0;
}

/*
Complexity Analysis:
--------------------
Time Complexity:
- O(n) to separate positives and negatives
- O(n) to merge alternately
=> Overall: O(n)

Space Complexity:
- O(n) extra space for two auxiliary arrays
- Stable order requires extra space
=> Overall: O(n)

Stability:
- Preserves the original relative order of positives and negatives
- Cannot achieve in-place stable rearrangement
*/
