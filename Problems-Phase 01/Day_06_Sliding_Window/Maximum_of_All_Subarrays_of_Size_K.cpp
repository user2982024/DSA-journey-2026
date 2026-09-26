#include <bits/stdc++.h>
using namespace std;

/*
    Problem:
    Maximum of All Subarrays of Size K

    Approach:
    - Maintain the maximum value of the current window.
    - If the outgoing element is not the current maximum,
      the maximum remains valid. We only compare it with the
      newly incoming element.
    - If the outgoing element is the current maximum, the
      maximum may no longer exist in the new window, so we
      recompute the maximum of the new window.

    Time Complexity:
    O(n * k) in the worst case.

    Space Complexity:
    O(1) auxiliary space
    O(n) including the output vector.

    Note:
    This is a correct but non-optimal solution.
    An O(n) solution can be achieved using a monotonic deque.
*/

class Solution {
public:
    vector<int> maxOfSubarrays(vector<int>& arr, int k) {
        vector<int> ans;

        int n = arr.size();
        int start = 0;
        int end = k - 1;
        int maxVal = 0;

        // Find the maximum of the first window.
        for (int i = 0; i <= end; i++) {
            maxVal = max(maxVal, arr[i]);
        }

        ans.push_back(maxVal);

        // Slide the window.
        while (end < n) {
            // Move the window forward.
            start++;
            end++;

            // No complete window remains.
            if (end == n) {
                break;
            }

            /*
                If the outgoing element was not the maximum,
                the current maximum is still valid.
            */
            if (arr[start - 1] != maxVal) {
                maxVal = max(maxVal, arr[end]);
            }

            /*
                If the outgoing element was the maximum,
                recompute the maximum for the new window.
            */
            else {
                maxVal = 0;

                for (int i = start; i <= end; i++) {
                    maxVal = max(maxVal, arr[i]);
                }
            }

            ans.push_back(maxVal);
        }

        return ans;
    }
};

int main() {
    Solution solution;

    vector<int> arr = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;

    vector<int> result = solution.maxOfSubarrays(arr, k);

    cout << "Maximum of every subarray of size " << k << ": ";

    for (int value : result) {
        cout << value << " ";
    }

    cout << '\n';

    return 0;
}