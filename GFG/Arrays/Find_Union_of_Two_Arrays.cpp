// File: union_of_arrays.cpp
// Author: Sheikh Abrar
// Description: Find the union of two unsorted arrays and return it as a sorted vector.
// Approach: 
//   1. Use a set to store unique elements from both arrays.
//   2. A set automatically removes duplicates and keeps elements sorted.
//   3. Insert all elements from the first array into the set.
//   4. Insert all elements from the second array into the set.
//   5. Convert the set into a vector and return it.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findUnion(vector<int>& a, vector<int>& b) {
        // Step 1: Declare a set to store unique elements
        set<int> unionSet; // set automatically sorts elements in ascending order

        // Step 2: Insert elements from the first array into the set
        for (int i = 0; i < a.size(); i++) {
            // Insertion into a set costs O(log k) where k = current set size
            unionSet.insert(a[i]);
        }

        // Step 3: Insert elements from the second array into the set
        for (int j = 0; j < b.size(); j++) {
            // Set will ignore duplicates automatically
            unionSet.insert(b[j]);
        }

        // Step 4: Convert the set into a vector
        // Copying all n + m elements into a vector costs O(n + m)
        return vector<int>(unionSet.begin(), unionSet.end());
    }
};

// Helper function to print a vector
void printVector(const vector<int>& v) {
    for (int num : v) {
        cout << num << " ";
    }
    cout << endl;
}

// Example usage
int main() {
    Solution sol;

    // Example arrays
    vector<int> arr1 = {5, 3, 8, 3, 2};
    vector<int> arr2 = {7, 2, 8, 1};

    cout << "Array 1: ";
    printVector(arr1);
    cout << "Array 2: ";
    printVector(arr2);

    // Step 5: Get union of both arrays
    vector<int> result = sol.findUnion(arr1, arr2);

    // Step 6: Print the sorted, unique union
    cout << "Union of Array 1 and Array 2 (sorted, unique): ";
    printVector(result);

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: 
    * Insertion into set for array a: O(n log n)
    * Insertion into set for array b: O(m log(n + m))
    * Converting set to vector: O(n + m)
    → Total: O((n + m) log(n + m))

- Space Complexity:
    * Set stores up to n + m elements: O(n + m)
    * Result vector stores n + m elements: O(n + m)
    → Total: O(n + m)

Notes:
- Works for unsorted arrays.
- Set ensures no duplicates and elements are sorted.
- Optimal for unsorted input arrays. 
*/
