#include <bits/stdc++.h>
using namespace std;

/*
Problem: Find all duplicate elements in the given array.

Approach: Frequency Counting using unordered_map
------------------------------------------------
We traverse the array once and store the frequency of each element in an unordered_map.
Then, we traverse the map and collect all elements with frequency > 1.

This approach works efficiently for any unsorted array, and handles duplicates of any number.

Example:
Input:  arr = [1, 2, 3, 1, 3, 6, 6]
Step 1: freqMap = {1:2, 2:1, 3:2, 6:2}
Step 2: Duplicates = [1, 3, 6]
Output: [1, 3, 6]
*/

class Solution {
public:
    vector<int> findDuplicates(vector<int>& arr) {
        vector<int> ans;
        unordered_map<int, int> freqMap;

        // Step 1: Count the frequency of each element
        for (int i = 0; i < arr.size(); i++) {
            freqMap[arr[i]]++;
        }

        // Step 2: Collect elements that appear more than once
        for (auto it = freqMap.begin(); it != freqMap.end(); it++) {
            if (it->second > 1) {
                ans.push_back(it->first);
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;

    // Example 1
    vector<int> arr1 = {1, 2, 3, 1, 3, 6, 6};
    vector<int> res1 = sol.findDuplicates(arr1);
    cout << "Duplicates in arr1: ";
    for (int x : res1) cout << x << " ";
    cout << endl;

    // Example 2
    vector<int> arr2 = {1, 2, 3, 4, 5};
    vector<int> res2 = sol.findDuplicates(arr2);
    cout << "Duplicates in arr2: ";
    for (int x : res2) cout << x << " ";
    cout << endl;

    return 0;
}

/*
--------------------------------
Dry Run Example
--------------------------------
Input: [1, 2, 3, 1, 3, 6, 6]

freqMap after first loop:
{
  1: 2,
  2: 1,
  3: 2,
  6: 2
}

Duplicates collected:
[1, 3, 6]

Output:
Duplicates in arr1: 1 3 6

--------------------------------
Time Complexity:
- Building freqMap → O(n)
- Traversing freqMap → O(n)
Total: O(n) average case
(Worst case with hash collisions → O(n²), rare)

Space Complexity:
- O(n) for unordered_map
- O(k) for ans vector (k = number of duplicates)
Total: O(n)
--------------------------------
*/
