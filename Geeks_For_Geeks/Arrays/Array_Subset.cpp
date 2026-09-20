#include <bits/stdc++.h>
using namespace std;

/*
Problem: Check if vector b[] is a subset of vector a[]
- Duplicates in b[] must be considered.
- Example:
    a = [1, 2, 2], b = [1, 1] → NOT a subset (true output: false)
- We cannot use unordered_set here because it removes duplicates.
*/

class Solution {
public:
    // Function to check if b is a subset of a
    bool isSubset(vector<int> &a, vector<int> &b) {
        // Using unordered_map to store frequency of elements in a
        unordered_map<int, int> freqMap;

        // Step 1: Count frequencies of elements in a[]
        // Why? Because we need to know how many times each element occurs.
        for (int i = 0; i < a.size(); i++) {
            freqMap[a[i]]++;
        }

        // Step 2: Check each element in b[]
        for (int j = 0; j < b.size(); j++) {
            // Check if element is missing or used up
            if (freqMap.find(b[j]) == freqMap.end() || freqMap[b[j]] == 0) {
                // If element not present in a[] or not enough occurrences, b[] is NOT a subset
                return false;
            }
            // Reduce the count as this element from b[] is "used"
            freqMap[b[j]]--;
        }

        // If all elements of b[] have enough occurrences in a[], return true
        return true;
    }
};

int main() {
    Solution sol;

    // Example 1: Normal case
    vector<int> a1 = {11, 7, 1, 13, 21, 3, 7, 3};
    vector<int> b1 = {11, 3, 7, 1, 7};
    if (sol.isSubset(a1, b1))
        cout << "b1[] is a subset of a1[]" << endl;
    else
        cout << "b1[] is NOT a subset of a1[]" << endl;

    // Example 2: Edge case with duplicates
    vector<int> a2 = {1, 2, 2};
    vector<int> b2 = {1, 1};
    if (sol.isSubset(a2, b2))
        cout << "b2[] is a subset of a2[]" << endl;
    else
        cout << "b2[] is NOT a subset of a2[]" << endl;

    return 0;
}

/*
Explanation / Notes:

1. Where you got stuck:
   - Initially tried using unordered_set.
   - Problem: unordered_set removes duplicates.
   - If b[] has multiple occurrences of an element but a[] has fewer, unordered_set incorrectly returns true.

2. Why not unordered_set:
   - unordered_set stores **unique elements only**.
   - For example:
       a = [1, 2, 2], b = [1, 1]
       unordered_set of a → {1, 2}
       Checking b[1] = 1 → exists → returns true (WRONG!)
   - So we must track **frequency of each element** → unordered_map.

3. Algorithm:
   - Build frequency map for a[]
   - Iterate over b[], for each element:
       - If not in map or frequency is 0 → return false
       - Else decrement frequency
   - If loop completes → return true

4. Time Complexity (TC):
   - Building map → O(n), n = a.size()
   - Checking b[] → O(m), m = b.size()
   - Total TC → O(n + m) on average (unordered_map lookup is O(1) average)

5. Space Complexity (SC):
   - O(n) for storing frequencies in unordered_map

6. Important Notes:
   - Used **classic for loops**, no range-based loops (interview-safe)
   - Works correctly for duplicates and all edge cases
   - Can be adapted for raw arrays by replacing vector operations with indexing
*/
