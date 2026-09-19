#include <bits/stdc++.h>
using namespace std;

/*
Problem: Find the missing number in an array containing numbers from 1 to n (inclusive)
         with exactly one number missing.

Approach: XOR Trick
--------------------------------
Properties of XOR:
1. a ^ a = 0
2. a ^ 0 = a
3. XOR is commutative and associative, so order doesn't matter.

Logic:
If we XOR all numbers from 1 to n, and also XOR all elements of the array,
the duplicate numbers cancel each other (because x ^ x = 0),
and only the missing number remains.

Example:
arr = [1, 2, 4, 5]
n = 5
xor_1 = 1 ^ 2 ^ 3 ^ 4 ^ 5 = 1
xor_2 = 1 ^ 2 ^ 4 ^ 5 = 2
missing = xor_1 ^ xor_2 = 1 ^ 2 = 3  
*/

class Solution {
public:
    int missingNum(vector<int>& arr) {
        int n = arr.size() + 1; // Array of n-1 elements, range should be [1..n]
        int xor_1 = 0;          // XOR of all numbers from 1 to n
        int xor_2 = 0;          // XOR of all elements in array

        // XOR all numbers from 1 to n
        for (int i = 1; i <= n; i++) {
            xor_1 ^= i;
        }

        // XOR all elements of the array
        for (int i = 0; i < arr.size(); i++) {
            xor_2 ^= arr[i];
        }

        // XOR both results to get the missing number
        int missing = xor_1 ^ xor_2;
        return missing;
    }
};

int main() {
    Solution sol;

    // Example 1: Missing number in middle
    vector<int> arr1 = {1, 2, 4, 5};
    cout << "Missing number: " << sol.missingNum(arr1) << endl; // Output: 3

    // Example 2: Missing smallest number
    vector<int> arr2 = {2, 3, 4, 5};
    cout << "Missing number: " << sol.missingNum(arr2) << endl; // Output: 1

    // Example 3: Missing largest number
    vector<int> arr3 = {1, 2, 3, 4};
    cout << "Missing number: " << sol.missingNum(arr3) << endl; // Output: 5

    return 0;
}

/*
--------------------------------
Dry Run (Example: arr = [1, 2, 4, 5])
--------------------------------
n = 5
xor_1 = 1 ^ 2 ^ 3 ^ 4 ^ 5 = 1
xor_2 = 1 ^ 2 ^ 4 ^ 5 = 2
missing = xor_1 ^ xor_2 = 1 ^ 2 = 3 

--------------------------------
Time Complexity:  O(n)
Space Complexity: O(1)
--------------------------------
Works for all cases:
Missing smallest number
Missing largest number
Missing middle number
--------------------------------
*/
