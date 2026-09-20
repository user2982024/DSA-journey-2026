#include <bits/stdc++.h>
using namespace std;

int findPeakIndex(vector<int> &arr, int n) {
    int peak = 0;

    for (int i = 0; i < n; i ++) {
        peak = max(peak, arr[i]);
    }

    return peak;
}

int main() {

    vector<int> arr = {3, 4, 5, 1};

    int ans = findPeakIndex(arr, 4);

    cout << ans << "\n";

    return 0;
}