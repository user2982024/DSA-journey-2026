/*
===============================================================================
PROBLEM: Best Time to Buy and Sell Stock (Single Transaction)
Platform: LeetCode

You are given an array prices where prices[i] is the price of a given stock
on the i-th day.

You want to maximize your profit by choosing:
- one day to buy the stock
- a different future day to sell the stock

Return the maximum profit you can achieve.
If no profit is possible, return 0.

Example:
Input:  [7,1,5,3,6,4]
Output: 5
Explanation:
Buy on day 2 (price = 1)
Sell on day 5 (price = 6)
Profit = 6 - 1 = 5
===============================================================================
*/

/*
===============================================================================
INTUITION

Brute force approach:
Try every pair (buy day, sell day) where sell > buy.

Time complexity: O(n^2) ❌ too slow

Optimized idea:

At each day, ask:
"What is the cheapest price I have seen so far to buy?"

If I sell today, profit = today_price - minimum_price_so_far.

Keep updating:
- minimum purchase price
- maximum profit

We scan left → right, so buying always happens before selling.
===============================================================================
*/

/*
===============================================================================
CORE INVARIANT

While iterating:
1. purchasingPrice = minimum price seen from day 0 to i
2. profit = maximum profit achievable so far

At each index i:
profit_today = prices[i] - purchasingPrice
profit = max(profit, profit_today)

This guarantees valid buy-before-sell ordering.
===============================================================================
*/

/*
===============================================================================
ALGORITHM

1. Initialize:
   purchasingPrice = INT_MAX
   profit = 0

2. Traverse prices:
   update purchasingPrice
   compute profit if sold today
   update best profit

3. Return profit
===============================================================================
*/

/*
===============================================================================
EDGE CASES

1. Prices always decreasing
   Example: [7,6,4,3,1]
   No profit possible → return 0

2. Single element array
   Cannot sell → return 0

3. Profit occurs in middle of array
   Works naturally.
===============================================================================
*/

/*
===============================================================================
DRY RUN

prices = [7,1,5,3,6,4]

i   price   minPrice   profitToday   maxProfit
----------------------------------------------
0     7        7           0            0
1     1        1           0            0
2     5        1           4            4
3     3        1           2            4
4     6        1           5            5
5     4        1           3            5

Final Answer = 5
===============================================================================
*/

/*
===============================================================================
TIME & SPACE COMPLEXITY

Time Complexity  : O(n)
Space Complexity : O(1)

Single pass, constant extra memory.
===============================================================================
*/

#include <vector>
#include <climits>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {

        int n = prices.size();

        int purchasingPrice = INT_MAX;
        int profit = 0;

        for (int i = 0; i < n; i++) {

            // Update minimum price seen so far
            if (prices[i] < purchasingPrice) {
                purchasingPrice = prices[i];
            }

            // Profit if sold today
            int currentProfit = prices[i] - purchasingPrice;

            // Update maximum profit
            if (currentProfit > profit) {
                profit = currentProfit;
            }
        }

        return profit;
    }
};