#include <bits/stdc++.h>
using namespace std;

int maxConsecutiveOnes(vector<int> &arr, int n) {
    int currentCount = 0;
    int maxCount = 0;

    for (int i = 0; i < n; i ++) {
        if (arr[i] == 1) {
            currentCount ++;
        }

        maxCount = max(maxCount, currentCount);

        if (arr[i] != 1) {
            currentCount = 0;
        }
    }

    return maxCount;
}

int main() {

    vector<int> arr = {2, 1, 1, 2, 4, 6, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1};

    int ans = maxConsecutiveOnes(arr, 17);
    cout << ans << "\n";

    return 0;
}