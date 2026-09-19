/*
    ✅ Problem: Find Missing and Repeating Number
    ------------------------------------------------
    You are given an array of size n containing numbers from 1 to n.
    One number is missing and one number occurs twice.
    Your task is to find both numbers.

    Example:
        Input:  arr = [1, 3, 3]
        Output: [3, 2]
        Explanation: 3 is repeating, 2 is missing.

    ------------------------------------------------
    🔍 Approach Used: Hash Map (Frequency Counting)
    ------------------------------------------------
    1. Traverse the array once and count the frequency of each number using
       an unordered_map<int, int>.
    2. Traverse from 1 to n:
        - If frequency[i] == 0 → that number is missing.
        - If frequency[i] > 1 → that number is repeating.
    3. Store and return both values.

    ------------------------------------------------
    ⚙️ Notes:
    - Do NOT break the loop after finding repeating number.
      Otherwise the missing number might not be checked.
    - No range-based loops are used; compatible with pre-C++11.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findTwoElement(vector<int>& arr) {
        int n = arr.size();
        unordered_map<int, int> freqMap;
        vector<int> ans(2);
        int missing = 0, repeating = 0;

        // Step 1: Count frequency of each element
        for (int i = 0; i < n; i++) {
            freqMap[arr[i]]++;
        }

        // Step 2: Identify missing and repeating numbers
        for (int i = 1; i <= n; i++) {
            if (freqMap[i] == 0) {
                missing = i;      // not present → missing
            } 
            else if (freqMap[i] > 1) {
                repeating = i;    // appears twice → repeating
            }
            if (repeating != 0 && missing != 0) {
                break;
            }
        }

        ans[0] = repeating;
        ans[1] = missing;
        return ans;
    }
};

int main() {
    Solution obj;

    // 🔸 Test 1
    int arr1[] = {1, 3, 3};
    vector<int> vec1(arr1, arr1 + sizeof(arr1)/sizeof(arr1[0]));
    vector<int> res1 = obj.findTwoElement(vec1);
    cout << "Input: [1, 3, 3]\n";
    cout << "Output: Repeating = " << res1[0] << ", Missing = " << res1[1] << "\n\n";

    // 🔸 Test 2
    int arr2[] = {6, 5, 8, 7, 1, 4, 1, 3, 2};
    vector<int> vec2(arr2, arr2 + sizeof(arr2)/sizeof(arr2[0]));
    vector<int> res2 = obj.findTwoElement(vec2);
    cout << "Input: [6, 5, 8, 7, 1, 4, 1, 3, 2]\n";
    cout << "Output: Repeating = " << res2[0] << ", Missing = " << res2[1] << "\n\n";

    // 🔸 Test 3
    int arr3[] = {2, 2};
    vector<int> vec3(arr3, arr3 + sizeof(arr3)/sizeof(arr3[0]));
    vector<int> res3 = obj.findTwoElement(vec3);
    cout << "Input: [2, 2]\n";
    cout << "Output: Repeating = " << res3[0] << ", Missing = " << res3[1] << "\n";

    return 0;
}

/*
    ------------------------------------------------
    🧮 Dry Run for arr = [6,5,8,7,1,4,1,3,2]
    ------------------------------------------------
    freqMap after counting:
      {1:2, 2:1, 3:1, 4:1, 5:1, 6:1, 7:1, 8:1}

    Loop 1..9:
      i=1 → freq=2 → repeating=1
      i=2..8 → freq=1 → ok
      i=9 → freq=0 → missing=9

    ✅ Output: [1, 9]
*/
