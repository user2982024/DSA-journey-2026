/*
    Problem: First Repeated Element in an Array
    ------------------------------------------------
    Given an array of integers, find the first element that repeats.
    Return its **1-based index** (position in array).
    If no element repeats, return -1.

    Example:
        Input: arr = [1, 5, 3, 4, 3, 5, 6]
        Output: 2
        Explanation: The element '5' repeats first in the array. Its 1-based index is 2.

    ------------------------------------------------
    Approach:
    1. Use an unordered_map<int,int> to store frequencies of elements.
    2. First loop: Count frequencies of each element.
    3. Second loop: Traverse the array from left to right and return
       the 1-based index of the first element whose frequency > 1.
    4. If no element repeats, return -1.

    Time Complexity: O(n)  → Two passes over array
    Space Complexity: O(n) → unordered_map stores unique elements
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int firstRepeated(vector<int> &arr) {
        unordered_map<int, int> freqMap;
        int ans = -1;

        // Step 1: Count frequencies of elements
        for (int i = 0; i < arr.size(); i++) {
            freqMap[arr[i]]++;
        }

        // Step 2: Traverse array to find the first repeated element
        for (int i = 0; i < arr.size(); i++) {
            if (freqMap[arr[i]] > 1) {
                ans = i + 1; // 1-based indexing
                break;       // stop at the first repeated element
            }
        }

        return ans;
    }
};

int main() {
    Solution obj;

    // Test Case 1
    vector<int> arr1 = {1, 5, 3, 4, 3, 5, 6};
    cout << "Test Case 1: " << obj.firstRepeated(arr1) << endl;
    // Expected Output: 2 (first repeated element = 5 at 1-based index 2)

    // Test Case 2
    vector<int> arr2 = {1, 2, 3, 4, 5};
    cout << "Test Case 2: " << obj.firstRepeated(arr2) << endl;
    // Expected Output: -1 (no repeated elements)

    // Test Case 3
    vector<int> arr3 = {2, 2};
    cout << "Test Case 3: " << obj.firstRepeated(arr3) << endl;
    // Expected Output: 1 (element 2 repeats, first occurrence at index 0 → 1-based)

    return 0;
}

/*
    ------------------------------------------------
    🔍 Why previous versions could fail:

    1️⃣ Original version without "break":
        for (int i = 0; i < arr.size(); i++) {
            if (freqMap[arr[i]] > 1) {
                ans = i + 1;  // keeps updating ans
            }
        }
        - Problem: `ans` would end up storing the **last repeated element**,
          not the first one.
        - Example: arr = [1, 5, 3, 4, 3, 5, 6]
            - Last repeated element = 5 at index 1 → correct
            - If loop continues, last repeated could incorrectly be 3 at index 4
              → wrong answer

    2️⃣ Using zero-based index incorrectly:
        - If you forgot to add `+1` for 1-based index, output would be off
          for problems expecting 1-based indexing.

    3️⃣ Not counting frequencies first:
        - If you tried to detect repetition in a single pass without a check,
          you could mistakenly return first occurrence instead of **first repeated**.

    ✅ Fixes in this version:
        - Count frequencies first
        - Traverse array in original order
        - Return **first element with frequency > 1**
        - Use `break` to stop immediately
        - Return 1-based index

    ------------------------------------------------
*/
