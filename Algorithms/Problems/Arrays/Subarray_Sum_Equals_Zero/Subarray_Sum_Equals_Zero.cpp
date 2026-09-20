#include <bits/stdc++.h>
using namespace std;

bool subarraySumEqualsZero(vector<int> &arr, int n) {
    int sum = 0;

    for (int i = 0; i < n; i ++) {
        sum += arr[i];

        if (sum == 0) {
            return true;
        }
    }

    return false;
}

int main() {

    vector<int> arr = {0, 2, 3, -5, 4, 2, 1};
    bool ans = subarraySumEqualsZero(arr, 7);

    cout << ans << "\n";

    return 0;
}