// ============================================================
// File: first_non_repeating.cpp
// Author: Sheikh Abrar
// Description: Find the first non-repeating element in an array
// ============================================================

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * Function: firstNonRepeating
     * ---------------------------
     * Finds the first element in the array that occurs exactly once.
     *
     * Parameters:
     *   arr - reference to the vector of integers
     *
     * Approach:
     *   1. Use unordered_map to count frequency of each element.
     *   2. Iterate over the array using indices.
     *   3. Return the first element with frequency 1.
     *
     * Time Complexity: O(n) - one pass to count + one pass to find
     * Space Complexity: O(n) - for unordered_map
     */
    int firstNonRepeating(vector<int>& arr) {
        unordered_map<int, int> freqMap;
        int ans = 0;

        // Step 1: Count frequency of each element
        for (int i = 0; i < arr.size(); i++) {
            freqMap[arr[i]]++;
        }

        // Step 2: Iterate over original array to preserve order
        for (int i = 0; i < arr.size(); i++) {
            if (freqMap[arr[i]] == 1) {
                ans = arr[i];
                break; // First non-repeating found
            }
        }

        // Step 3: If all elements repeat, ans remains -1
        return ans;
    }
};

// ============================================================
// Dry Run Example
// ------------------------------------------------------------
// Input:  [4, 5, 4, 3, 5, 1, 3]
// Frequency Map:
//   4 -> 2
//   5 -> 2
//   3 -> 2
//   1 -> 1
// Iterate original array:
//   4 -> freq 2 -> skip
//   5 -> freq 2 -> skip
//   4 -> freq 2 -> skip
//   3 -> freq 2 -> skip
//   5 -> freq 2 -> skip
//   1 -> freq 1 -> return 1
// Output: 1
// ============================================================

int main() {
    Solution sol;
    vector<int> arr = {4, 5, 4, 3, 5, 1, 3};

    cout << "Original Array: ";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    int firstNonRepeatingElement = sol.firstNonRepeating(arr);

    if (firstNonRepeatingElement != -1)
        cout << "First Non-Repeating Element: " << firstNonRepeatingElement << endl;
    else
        cout << "No Non-Repeating Element Found" << endl;

    return 0;
}

/*
Complexity Analysis:
--------------------
Time Complexity:
- O(n) to count frequencies
- O(n) to find first non-repeating
=> Total = O(n)

Space Complexity:
- O(n) for unordered_map to store frequencies
- n = number of distinct elements in the array

Notes:
- Preserves original order
- Handles positive, negative, and zero
- Returns -1 if no non-repeating element exists
*/
