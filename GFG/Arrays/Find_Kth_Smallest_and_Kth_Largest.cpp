#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Find the Kth Smallest and Kth Largest Element in an Array
    Source: Love Babbar DSA Sheet (Arrays - Q3)

    Approach:
    → Sort the array in ascending order.
    → Kth smallest element is at index k-1 (0-based indexing).
    → Kth largest element is at index arr.size() - k.
    → This approach is simple and works efficiently for most interview problems.

    Time Complexity: O(n log n) — due to sorting
    Space Complexity: O(1) — in-place sorting, no extra array needed
*/

class Solution {
public:
    int kthSmallest(vector<int> &arr, int k) {
        sort(arr.begin(), arr.end());
        return arr[k - 1]; // 0-based indexing
    }

    int kthLargest(vector<int> &arr, int k) {
        sort(arr.begin(), arr.end());
        return arr[arr.size() - k]; // kth largest
    }
};

int main() {
    int n, k;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter array elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Enter value of k: ";
    cin >> k;

    Solution sol;

    cout << k << "th smallest element = " << sol.kthSmallest(arr, k) << endl;
    cout << k << "th largest element = " << sol.kthLargest(arr, k) << endl;

    return 0;
}
