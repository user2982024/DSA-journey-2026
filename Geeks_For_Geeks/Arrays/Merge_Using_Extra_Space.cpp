/*
===============================================================================
PROBLEM: Merge Two Sorted Arrays
Platform: GeeksforGeeks

Given two sorted arrays a[] and b[] of size n and m respectively,
merge them so that:

- a[] contains the first n smallest elements
- b[] contains the remaining m largest elements
- Final arrays remain sorted
- This version uses extra space

Example:
Input:
a = [1, 4, 7, 8, 10]
b = [2, 3, 9]

Output:
a = [1, 2, 3, 4, 7]
b = [8, 9, 10]
===============================================================================
*/

/*
===============================================================================
INTUITION

Both arrays are already sorted.

Simplest idea:
1. Merge them like merge step of merge sort
2. Store result in a temporary array
3. Copy first n elements back to a[]
4. Copy remaining m elements to b[]

This guarantees sorted order.

Time efficient but uses extra memory.
===============================================================================
*/

/*
===============================================================================
ALGORITHM

1. Use two pointers:
   i → start of array a
   j → start of array b

2. Compare elements and push smaller into merged array

3. Append remaining elements of either array

4. Overwrite:
   first m elements → a
   remaining → b
===============================================================================
*/

/*
===============================================================================
EDGE CASES

1. One array empty
2. All elements of a smaller than b
3. All elements of b smaller than a
4. Duplicate values
===============================================================================
*/

/*
===============================================================================
DRY RUN

a = [1,4,7]
b = [2,3,6]

Merged = [1,2,3,4,6,7]

a = first 3 → [1,2,3]
b = last 3  → [4,6,7]
===============================================================================
*/

/*
===============================================================================
TIME & SPACE COMPLEXITY

Time  : O(m + n)
Space : O(m + n)   (temporary merged array)
===============================================================================
*/

#include <vector>
using namespace std;

class Solution {
public:
    void mergeArrays(vector<int>& a, vector<int>& b) {

        int m = a.size();
        int n = b.size();

        int i = 0;
        int j = 0;

        vector<int> merged;

        // Merge both arrays
        while (i < m && j < n) {
            if (a[i] <= b[j]) {
                merged.push_back(a[i]);
                i++;
            } else {
                merged.push_back(b[j]);
                j++;
            }
        }

        // Remaining elements of a
        while (i < m) {
            merged.push_back(a[i]);
            i++;
        }

        // Remaining elements of b
        while (j < n) {
            merged.push_back(b[j]);
            j++;
        }

        // Copy first m elements into a
        for (int k = 0; k < m; k++) {
            a[k] = merged[k];
        }

        // Copy remaining n elements into b
        int index = 0;
        for (int k = m; k < m + n; k++) {
            b[index] = merged[k];
            index++;
        }
    }
};