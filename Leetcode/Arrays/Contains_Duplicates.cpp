/*
===============================================================================
PROBLEM: Contains Duplicate

PLATFORM: LeetCode

STATEMENT:
Given an integer array nums, return true if any value appears at least twice
in the array, and return false if every element is distinct.

-------------------------------------------------------------------------------
EXAMPLE:

Input  : [1, 2, 3, 1]
Output : true

Input  : [1, 2, 3, 4]
Output : false

-------------------------------------------------------------------------------
INITIAL APPROACH (MY FIRST THINKING)

I first used an unordered_map to store frequency of each element.

Steps:
1. Traverse array and count occurrences.
2. Traverse map and check if any count > 1.

This works correctly but does extra work because:
- It counts all elements even if duplicate found early.
- Requires two passes.

This approach is valid but not optimal for this problem.

-------------------------------------------------------------------------------
OPTIMIZED APPROACH (FINAL IMPLEMENTATION)

Observation:
We only need to know whether an element appears more than once.
We do NOT need the exact frequency.

So we use unordered_set.

Algorithm:
1. Traverse array.
2. If element already exists in set → duplicate found → return true.
3. Otherwise insert element into set.
4. If traversal completes → no duplicate → return false.

This allows early exit and avoids unnecessary counting.

-------------------------------------------------------------------------------
WHY UNORDERED_SET IS BETTER THAN UNORDERED_MAP HERE

unordered_map → stores frequency
unordered_set → stores presence only

Since only presence is needed → set is more efficient and cleaner.

-------------------------------------------------------------------------------
EDGE CASES

✔ Empty array → no duplicates
✔ Single element → no duplicates
✔ All elements same → duplicate detected quickly
✔ Negative values → handled
✔ Large input → efficient

-------------------------------------------------------------------------------
DRY RUN

nums = [5, 3, 1, 4, 3]

Step 1: seen = {}
Insert 5 → {5}
Insert 3 → {5,3}
Insert 1 → {5,3,1}
Insert 4 → {5,3,1,4}

Next element = 3
3 already exists → return true

-------------------------------------------------------------------------------
TIME COMPLEXITY

Each lookup and insertion in unordered_set:
Average O(1)

Total traversal = n

FINAL:
O(n) average time

Worst case (hash collision):
O(n^2) but rare in practice.

-------------------------------------------------------------------------------
SPACE COMPLEXITY

Set stores at most n elements.

FINAL:
O(n)

-------------------------------------------------------------------------------
INTERVIEW INSIGHT

If interviewer asks for no extra space:
Sort array and check adjacent elements.

Time = O(n log n)
Space = O(1) if in-place sorting allowed.

-------------------------------------------------------------------------------
ALGORITHM SUMMARY

Use hash set to track seen elements and detect duplicate early.

===============================================================================
*/

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {

        unordered_set<int> seen;

        int n = nums.size();

        for (int i = 0; i < n; i++) {

            // Check if element already exists
            if (seen.find(nums[i]) != seen.end()) {
                return true;
            }

            // Insert new element
            seen.insert(nums[i]);
        }

        return false;
    }
};


// -----------------------------------------------------------------------------
// DRIVER CODE (LOCAL TESTING)
// -----------------------------------------------------------------------------
int main() {

    vector<int> nums;

    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(3);
    nums.push_back(1);

    Solution obj;
    bool result = obj.containsDuplicate(nums);

    if (result) {
        cout << "Duplicate exists" << endl;
    } else {
        cout << "All elements are unique" << endl;
    }

    return 0;
}