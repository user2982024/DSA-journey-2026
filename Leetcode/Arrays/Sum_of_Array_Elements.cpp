/******************************************************************************************
* Problem: Sum of Array Elements
*
* Platform: GeeksforGeeks
*
* Description:
* Given an array of integers, return the sum of all elements in the array.
*
* Example:
* Input:  arr = {1, 2, 3, 4}
* Output: 10
*
* Explanation:
* 1 + 2 + 3 + 4 = 10
*
******************************************************************************************/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to return sum of elements
    int arraySum(vector<int>& arr) {
        
        // Step 1: Initialize sum variable
        int sum = 0;

        // Step 2: Traverse the entire array
        int n = arr.size();
        for (int i = 0; i < n; i++) {
            sum += arr[i];
        }

        // Step 3: Return the final accumulated sum
        return sum;
    }
};

/******************************************************************************************
* 🔎 Approach:
*
* This is a basic accumulation problem.
* We iterate through the array once and keep adding elements to a running total.
*
* Mathematical Representation:
* If arr = {a1, a2, a3, ..., an}
* Then sum = a1 + a2 + a3 + ... + an
*
******************************************************************************************/

/******************************************************************************************
* 🧪 Dry Run:
*
* Input: arr = {5, 10, 15}
*
* Initial:
* sum = 0
*
* Iteration 1:
* sum = 0 + 5 = 5
*
* Iteration 2:
* sum = 5 + 10 = 15
*
* Iteration 3:
* sum = 15 + 15 = 30
*
* Final Answer = 30
*
******************************************************************************************/

/******************************************************************************************
* ⚠️ Edge Cases:
*
* 1. Empty array:
*    If arr.size() == 0 → loop does not run → sum remains 0.
*
* 2. Negative numbers:
*    Works correctly because addition handles negatives naturally.
*
* 3. Large numbers:
*    If constraints are large (e.g., 10^5 elements with value 10^9),
*    consider using long long instead of int to avoid overflow.
*
******************************************************************************************/

/******************************************************************************************
* ⏱ Time Complexity:
* O(n)
* We traverse the array exactly once.
*
* 💾 Space Complexity:
* O(1)
* Only one extra variable (sum) is used.
*
******************************************************************************************/

/******************************************************************************************
* 💡 Prefix Sum Connection:
*
* This is the most basic form of prefix accumulation.
*
* If we store intermediate sums:
*
* prefix[i] = arr[0] + arr[1] + ... + arr[i]
*
* Then:
* prefix[n-1] gives total array sum.
*
* This idea is the foundation of:
* - Range Sum Queries
* - Subarray Sum problems
* - Kadane’s Algorithm
*
******************************************************************************************/