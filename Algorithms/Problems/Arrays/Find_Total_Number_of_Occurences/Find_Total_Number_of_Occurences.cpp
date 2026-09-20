#include <bits/stdc++.h>
using namespace std;

int findTotalOccureneces(vector<int> &arr, int n, int k) {
    int count = 0;

    for (int i = 0; i < n; i ++) {
        if (arr[i] == k) {
            count ++;
        }
    }

    return count;
}

int main() {

    vector<int> arr = {1, 2, 3, 3, 3, 3, 5};

    int ans = findTotalOccureneces(arr, 7, 3);

    cout << ans << "\n";

    return 0;
}