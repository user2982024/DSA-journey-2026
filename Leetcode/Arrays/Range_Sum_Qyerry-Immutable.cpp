/************************************************************
 *
 *  File: NumArray.cpp
 *  Problem: Range Sum Query - Immutable (LeetCode 303)
 *
 *  --------------------------------------------------------
 *  DESIGN OVERVIEW
 *  --------------------------------------------------------
 *
 *  We use Prefix Sum with n+1 design.
 *
 *  Definition:
 *      prefix[i] = sum of elements in nums[0 ... i-1]
 *
 *  That is:
 *      prefix represents cumulative function f(i)
 *      where f(i) = sum of first i elements.
 *
 *  Query:
 *      sumRange(left, right)
 *
 *  Using interval subtraction:
 *      sum(left, right) = prefix[right + 1] - prefix[left]
 *
 *  --------------------------------------------------------
 *  TIME COMPLEXITY
 *  --------------------------------------------------------
 *  Constructor  : O(n)
 *  Each Query   : O(1)
 *
 *  --------------------------------------------------------
 *  SPACE COMPLEXITY
 *  --------------------------------------------------------
 *  O(n)
 *
 ************************************************************/

#include <iostream>
#include <vector>

using namespace std;

class NumArray {

private:
    /*
     * prefix[i] stores sum of nums[0] to nums[i-1]
     * Size of prefix = n + 1
     */
    vector<long long> prefix;

public:

    /********************************************************
     * Constructor
     *
     * Builds prefix array in O(n).
     * Runs once when object is instantiated.
     ********************************************************/
    NumArray(vector<int>& nums) {

        int n = nums.size();

        // Allocate memory for prefix (n + 1)
        prefix.resize(n + 1);

        // Base case: sum of 0 elements
        prefix[0] = 0;

        /*
         * Build prefix array.
         *
         * Loop invariant:
         * After iteration i,
         * prefix[i + 1] = sum of nums[0 ... i]
         */
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
    }

    /********************************************************
     * sumRange(left, right)
     *
     * Returns sum of elements from index left to right
     * (both inclusive).
     *
     * Formula:
     *      prefix[right + 1] - prefix[left]
     *
     * Why no special case?
     * Because prefix[0] = 0.
     ********************************************************/
    int sumRange(int left, int right) {

        // Optional defensive boundary check
        if (left < 0 || right < 0)
            return 0;

        if (left > right)
            return 0;

        if (right >= (int)prefix.size() - 1)
            return 0;

        long long result = prefix[right + 1] - prefix[left];

        return static_cast<int>(result);
    }
};


/************************************************************
 *
 * DRY RUN EXAMPLE
 *
 * nums = [3, -1, 4, 2]
 *
 * Step 1: Build prefix
 *
 * index:   0   1   2   3   4
 * prefix:  0   3   2   6   8
 *
 * prefix[0] = 0
 * prefix[1] = 3
 * prefix[2] = 3 + (-1) = 2
 * prefix[3] = 2 + 4 = 6
 * prefix[4] = 6 + 2 = 8
 *
 * Step 2: Query sumRange(1, 3)
 *
 * prefix[4] - prefix[1]
 * = 8 - 3
 * = 5
 *
 * Manual verification:
 * -1 + 4 + 2 = 5
 *
 ************************************************************/