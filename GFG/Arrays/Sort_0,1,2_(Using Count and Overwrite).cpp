#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Sort an array containing only 0s, 1s, and 2s
    Source: Love Babbar DSA Sheet (Arrays - Q4)

    Approach:
    → Count the number of 0s, 1s, and 2s in the array.
    → Overwrite the array:
        • First 'count_0' elements with 0
        • Next 'count_1' elements with 1
        • Remaining 'count_2' elements with 2
    → This is an in-place, 2-pass solution.

    Time Complexity: O(n) — first pass counts, second pass overwrites
    Space Complexity: O(1) — only 3 integer counters used
*/

class Solution {
public:
    void sort012(vector<int>& arr) {
        int count_0 = 0;
        int count_1 = 0;
        int count_2 = 0;

        // Count 0s, 1s, and 2s
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == 0) count_0++;
            else if (arr[i] == 1) count_1++;
            else count_2++;
        }

        // Overwrite array with 0s
        for (int i = 0; i < count_0; i++)
            arr[i] = 0;

        // Overwrite array with 1s
        for (int i = count_0; i < count_0 + count_1; i++)
            arr[i] = 1;

        // Overwrite array with 2s
        for (int i = count_0 + count_1; i < count_0 + count_1 + count_2; i++)
            arr[i] = 2;
    }
};

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter array elements (0, 1, or 2 only):\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    Solution sol;
    sol.sort012(arr);

    cout << "Sorted array: ";
    for (int x : arr)
        cout << x << " ";
    cout << endl;

    return 0;
}
