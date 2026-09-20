#include <bits/stdc++.h>
using namespace std;

bool findFixedPoint(vector<int> &arr, int n) {
    for (int i = 0; i < n; i ++) {
        if (arr[i] == i) {
            return true;
        }
    }

    return false;
}

int main() {

    vector<int> arr = {1, 2, 4, 3, 4, 10, 0};
    bool ans = findFixedPoint(arr, 7);

    cout << ans << "\n";

    return 0;
}