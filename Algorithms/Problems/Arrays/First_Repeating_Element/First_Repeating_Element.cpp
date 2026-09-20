#include <bits/stdc++.h>
using namespace std;

int firstRepeating(vector<int> &arr, int n) {
    unordered_map<int, int> freqMap;

    for (int i = 0; i < n; i ++) {
        freqMap[arr[i]] ++;
    }

    for (int i = 0; i < n; i ++) {
        if (freqMap[arr[i]] > 1) {
            return arr[i];
        }
    }

    return -1;
}

int main() {

    vector<int> arr = {0, 1, 3, 2, 2, 4, 4, 1, 0};
    int ans = firstRepeating(arr, 9);

    cout << ans << "\n";

    return 0;
}