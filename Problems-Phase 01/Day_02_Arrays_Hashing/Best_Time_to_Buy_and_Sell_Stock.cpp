#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

/*
    LeetCode #121
    Best Time to Buy and Sell Stock

    Problem:
    Given an array of stock prices where prices[i] represents the
    stock price on day i, find the maximum profit that can be achieved
    by buying on one day and selling on a later day.

    If no profit can be made, return 0.

    Example:
    prices = {7, 1, 5, 3, 6, 4}

    Buy at 1
    Sell at 6

    Maximum Profit = 6 - 1 = 5
*/


class Solution {
public:

    int maxProfit(vector<int>& prices) {

        // Stores the minimum buying price seen so far.
        int buyingPrice = INT_MAX;

        // Stores the maximum profit found so far.
        int profit = INT_MIN;

        int n = prices.size();

        /*
            We stop at n - 1 because we use prices[i + 1]
            as the selling price.

            The last element cannot be used as a buying price
            because there is no element after it to sell at.
        */
        for (int i = 0; i < n - 1; i++) {

            // Find the minimum buying price seen so far.
            buyingPrice = min(buyingPrice, prices[i]);

            /*
                Consider prices[i + 1] as the selling price.

                Calculate the possible profit and keep
                the maximum profit found so far.
            */
            profit = max(profit, prices[i + 1] - buyingPrice);
        }

        /*
            If every possible transaction results in a loss,
            no transaction should be made.
        */
        if (profit < 0) {
            return 0;
        }

        return profit;
    }
};


/*
    Complexity Analysis:

    Time Complexity:
    O(n)

    We traverse the array only once.

    Space Complexity:
    O(1)

    We only use a few variables regardless of the input size.


    Key Pattern:

    - Track the minimum buying price seen so far.
    - Calculate the profit for each possible selling day.
    - Keep the maximum profit found so far.

    Important Learning:

    Initially, the idea was to find the minimum price in the
    entire array and then find the maximum selling price after it.

    However, this fails for cases such as:

        prices = {2, 4, 1}

    The minimum price is 1, but it occurs at the last position,
    so we cannot sell after buying at 1.

    The valid transaction is:

        Buy at 2
        Sell at 4
        Profit = 2

    Therefore, we need to continuously track the best buying
    price and the maximum profit instead of simply finding
    the global minimum and maximum.
*/