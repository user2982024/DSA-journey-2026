#include <bits/stdc++.h>
using namespace std;

int sumArray(vector<int> &arr, int n) {
    int arraySum = 0;

    for (int i = 0; i < n; i ++) {
        arraySum += arr[i];
    }

    return arraySum;
}

int main() {

    vector<int> arr = {1, 3, 1, 3, 1};

    int ans = sumArray(arr, 5);
    cout << ans << "\n";

    return 0;
}