// File: rotate_array_by_one.cpp
// Author: Sheikh Abrar
// Description: Rotate an array cyclically by one position to the right in-place.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void rotate(vector<int> &arr) {
        int n = arr.size();
        if (n <= 1) return; // No rotation needed for empty or single-element arrays

        // Step 1: Store the last element temporarily
        int temp = arr[n - 1];

        // Step 2: Shift all elements one position to the right
        for (int i = n - 1; i > 0; i--) {
            arr[i] = arr[i - 1];
        }

        // Step 3: Place the last element at the first position
        arr[0] = temp;
    }
};

// Helper function to print the array
void printArray(const vector<int> &arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// Example usage
int main() {
    Solution sol;
    vector<int> arr = {1, 2, 3, 4, 5};

    cout << "Original array: ";
    printArray(arr);

    sol.rotate(arr);

    cout << "Array after rotation by one: ";
    printArray(arr);

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(n)
    * Need to shift all n elements one step → O(n)
- Space Complexity: O(1)
    * Only a temporary variable is used
- Notes:
    * Works for empty or single-element arrays
    * Can be generalized to rotate by k positions using reversal algorithm
*/
