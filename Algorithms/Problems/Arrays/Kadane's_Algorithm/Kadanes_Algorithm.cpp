#include <bits/stdc++.h>
using namespace std;

int kadanesAlgorithm(vector<int> &arr, int n) {
    int currentSum = 0;
    int maxSum = INT_MIN;

    for (int i = 0; i < n; i ++) {
        currentSum += arr[i];

        if (currentSum < 0) {
            currentSum = 0;
        }

        maxSum = max(maxSum, currentSum);
    }

    return maxSum;
}

int main() {
    vector<int> arr = {1, 3, 2, -8, 5, 6, 7};

    int ans = kadanesAlgorithm(arr, 7);
    cout << ans << "\n";

    return 0;
}