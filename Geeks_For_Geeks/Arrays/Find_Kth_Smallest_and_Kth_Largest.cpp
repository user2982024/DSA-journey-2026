/*
====================================================================
Problem: Kth Smallest Element in an Array
Sheet: Love Babbar 450 DSA Sheet
Question Number: 3
Topic: Arrays / Sorting / Order Statistics
Difficulty: Easy–Medium
Author: Sheikh Abrar
Journey: 100 Days of DSA
====================================================================

🧩 Problem Statement:
Given an array of integers and an integer k,
find the kth smallest element in the array.

IMPORTANT:
Duplicates are counted separately.
We are NOT looking for kth distinct element.

Example:
Input:
arr = [7, 10, 4, 3, 20, 15]
k = 3

Sorted array:
[3, 4, 7, 10, 15, 20]

Output:
7

--------------------------------------------------------------------
⚠ Common Misinterpretation (Very Important Learning)

"kth smallest element"  ≠  "kth smallest distinct element"

Example:
arr = [1, 2, 2, 2, 3]
k = 3

Sorted:
[1, 2, 2, 2, 3]

3rd smallest = 2

If we removed duplicates using set:
{1, 2, 3}

3rd smallest distinct = 3 (WRONG for this problem)

So duplicates MUST be preserved.

--------------------------------------------------------------------
🧠 Approach Used: Sorting (Simple and Reliable)

Steps:
1. Sort the array in ascending order.
2. The kth smallest element will be at index (k-1).

Why (k-1)?
Because arrays use 0-based indexing.

--------------------------------------------------------------------
🔍 Dry Run:

arr = [7, 10, 4, 3, 20, 15]
k = 3

After sorting:
[3, 4, 7, 10, 15, 20]

Indexing:
0 → 3
1 → 4
2 → 7  ← answer

Return arr[2]

--------------------------------------------------------------------
⏱ Time Complexity:

Sorting takes:
O(n log n)

Accessing kth element:
O(1)

Total:
O(n log n)

--------------------------------------------------------------------
🧠 Space Complexity:

Depends on sorting implementation.
C++ std::sort uses Introsort (hybrid quicksort + heapsort + insertion sort).

Auxiliary space:
O(log n) due to recursion stack (average case)

--------------------------------------------------------------------
✅ Edge Cases Handled:

✔ k = 1 → smallest element
✔ k = n → largest element
✔ duplicates present
✔ negative values
✔ already sorted array
✔ reverse sorted array

--------------------------------------------------------------------
⭐ Related Variation (Important Concept)

If problem asked:
"kth smallest DISTINCT element"

Then we would:
1. Insert elements into set (removes duplicates)
2. Traverse to kth element

But that is NOT this problem.

--------------------------------------------------------------------
⭐ Key Learning:

Always check whether duplicates should be counted
before choosing data structure.

Sorting preserves duplicates.
Set removes duplicates.

Choose carefully based on problem definition.

====================================================================
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int kthSmallest(vector<int>& arr, int k) {

        // Step 1: Sort array in ascending order
        sort(arr.begin(), arr.end());

        // Step 2: Return kth smallest (0-based indexing)
        return arr[k - 1];
    }
};

int main() {

    Solution obj;

    int n, k;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter elements: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    cout << "Enter k: ";
    cin >> k;

    cout << "Kth smallest element: "
         << obj.kthSmallest(arr, k) << endl;

    return 0;
}