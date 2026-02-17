/*
====================================================================
Problem: Find Minimum and Maximum Element in an Array
Sheet: Love Babbar 450 DSA Sheet
Question Number: 2
Topic: Arrays / Traversal
Difficulty: Easy
Author: Sheikh Abrar
Journey: 100 Days of DSA
====================================================================

🧩 Problem Statement:
Given an array of integers, find the minimum and maximum element
present in the array and return both.

Example:
Input:  arr = [3, 5, 4, 1, 9]
Output: min = 1, max = 9

--------------------------------------------------------------------
🧠 Approach: Linear Scan (Single Traversal)

We iterate through the array once while maintaining two variables:

1. smallest → stores minimum value found so far
2. largest  → stores maximum value found so far

Steps:
1. Initialize:
      smallest = INT_MAX
      largest  = INT_MIN
2. Traverse array from start to end
3. Update smallest if current element is smaller
4. Update largest if current element is larger
5. Return both values

This ensures we find min and max in a single pass.

--------------------------------------------------------------------
🔍 Dry Run:

Array: [3, 5, 4, 1, 9]

Start:
smallest = +∞
largest  = -∞

3 → smallest=3, largest=3
5 → largest=5
4 → no change
1 → smallest=1
9 → largest=9

Final:
min = 1
max = 9

--------------------------------------------------------------------
⏱ Time Complexity:
O(n)
We traverse the array exactly once.

--------------------------------------------------------------------
🧠 Space Complexity:
O(1)
Only two variables are used for tracking min and max.
Output size is fixed (2 values), so constant extra space.

--------------------------------------------------------------------
✅ Edge Cases Handled:
- Array with one element
- All elements same
- Negative values
- Sorted / reverse sorted arrays

--------------------------------------------------------------------
⭐ Key Learning:
This is a fundamental array traversal pattern used in many problems.
Always try to compute multiple statistics in one pass if possible.

====================================================================
*/

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Solution {
public:
    vector<int> getMinMax(vector<int>& arr) {

        int smallest = INT_MAX;
        int largest  = INT_MIN;
        int n = arr.size();

        for (int i = 0; i < n; i ++) {
            if (arr[i] < smallest)
                smallest = arr[i];

            if (arr[i] > largest)
                largest = arr[i];
        }

        return {smallest, largest};
    }
};

int main() {

    Solution obj;

    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter elements: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    vector<int> result = obj.getMinMax(arr);

    cout << "Minimum element: " << result[0] << endl;
    cout << "Maximum element: " << result[1] << endl;

    return 0;
}