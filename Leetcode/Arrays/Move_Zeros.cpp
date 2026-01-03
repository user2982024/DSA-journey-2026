#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Move all zeros in an array to the end while maintaining the relative order of non-zero elements.
    Source: LeetCode 283

    Approach: In-place Two-Pointer Method

    Detailed Explanation:
    ------------------------------------------
    1. **Idea:**
       - We want to shift all non-zero elements to the front of the array.
       - Zeros will naturally be placed at the end after all non-zero elements.
       - We do this **without using extra space**, in O(n) time.

    2. **Two Pointers Used:**
       - `i` → iterator scanning the entire array from left to right.
       - `position` → tracks the index where the next non-zero element should be placed.

    3. **Algorithm Steps:**
       a) Initialize `position = 0`.
       b) Traverse the array with index `i`:
          - If `nums[i] != 0`:
            - Place it at `nums[position]`.
            - Increment `position` by 1.
          - If `nums[i] == 0`:
            - Do nothing, just continue scanning.
       c) After traversing the array, all non-zero elements are in order from index 0 to `position - 1`.
       d) Fill remaining positions from `position` to the end of the array with zeros.
    
    4. **Key Observations:**
       - Relative order of non-zero elements is maintained.
       - Works **in-place**, using only O(1) extra space.
       - Single-pass traversal for non-zeros, second pass to fill zeros.
       - Total Time Complexity: O(n)
       - Space Complexity: O(1)

    Example:
    ------------
    Input:  [0, 1, 0, 3, 12]
    Process:
      - position=0, i=0 → nums[0]=0 → skip
      - i=1 → nums[1]=1 → nums[position]=1 → nums=[1,1,0,3,12], position=1
      - i=2 → nums[2]=0 → skip
      - i=3 → nums[3]=3 → nums[position]=3 → nums=[1,3,0,3,12], position=2
      - i=4 → nums[4]=12 → nums[position]=12 → nums=[1,3,12,3,12], position=3
    Fill remaining positions with zeros:
      - nums[3]=0, nums[4]=0 → Final array: [1,3,12,0,0]
*/

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int position = 0;  // Tracks where the next non-zero element should go

        // First pass: place all non-zero elements at the correct position
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != 0) {
                nums[position] = nums[i];
                position++;
            }
        }

        // Second pass: fill remaining positions with zeros
        for (int i = position; i < nums.size(); i++) {
            nums[i] = 0;
        }
    }
};

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Enter array elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    Solution sol;
    sol.moveZeroes(nums);

    cout << "Array after moving zeros to the end: ";
    for (int x : nums)
        cout << x << " ";
    cout << endl;

    return 0;
}
