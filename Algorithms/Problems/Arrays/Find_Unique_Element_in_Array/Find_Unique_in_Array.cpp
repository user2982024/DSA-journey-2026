#include <bits/stdc++.h>
using namespace std;

int findUnique(vector<int> &arr, int n) {
    int ans = 0;

    for (int i = 0; i < n; i ++) {
        ans ^= arr[i];
    }

    return ans;
}

int main() {

    vector<int> arr = {1, 3, 4, 4, 3, 7, 1};

    int ans = findUnique(arr, 7);
    cout << ans << "\n";

    return 0;
}