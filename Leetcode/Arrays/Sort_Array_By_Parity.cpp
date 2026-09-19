#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Sort Array By Parity
    Source: LeetCode 905

    Approach: In-place Two-Pointer Swap

    Detailed Explanation:
    ------------------------------------------
    1. **Idea:**
       - Move all even numbers to the front and odd numbers to the back.
       - Use a pointer 'position' to track the next slot for an even number.
       - Swap in-place to avoid extra space usage.

    2. **Two Pointers Used:**
       - `i` → scans the entire array.
       - `position` → next position to place an even number.

    3. **Algorithm Steps:**
       a) Initialize `position = 0`.
       b) Traverse array with index `i`:
          - If `nums[i]` is even:
              - Swap `nums[i]` with `nums[position]`.
              - Increment `position`.
          - If `nums[i]` is odd:
              - Do nothing, just move `i` forward.
       c) After traversal, all even numbers are in front, odd numbers at the back.

    4. **Key Observations:**
       - Relative order of even or odd numbers is not guaranteed.
       - Works in-place → O(1) extra space.
       - Single-pass → O(n) time complexity.

    Example:
    ------------
    Input:  [3, 1, 2, 4]
    Process:
      - position=0, i=0 → nums[0]=3 (odd) → skip
      - i=1 → nums[1]=1 (odd) → skip
      - i=2 → nums[2]=2 (even) → swap(nums[2], nums[0]) → nums=[2,1,3,4], position=1
      - i=3 → nums[3]=4 (even) → swap(nums[3], nums[1]) → nums=[2,4,3,1], position=2
    Final array: [2,4,3,1]
*/

class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        int position = 0; // Next index to place an even number

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] % 2 == 0) {
                swap(nums[position], nums[i]);
                position++;
            }
        }

        return nums;
    }
};

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Enter array elements:\n";
    for (int i = 0; i < n; i++)
        cin >> nums[i];

    Solution sol;
    vector<int> result = sol.sortArrayByParity(nums);

    cout << "Array after sorting by parity: ";
    for (int x : result)
        cout << x << " ";
    cout << endl;

    return 0;
}
