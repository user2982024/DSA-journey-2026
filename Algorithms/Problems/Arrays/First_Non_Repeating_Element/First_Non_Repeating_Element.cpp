#include <bits/stdc++.h>
using namespace std;

int firstNonRepeating(vector<int> &arr, int n) {
    unordered_map<int, int> freqMap;

    for (int i = 0; i < n; i ++) {
        freqMap[arr[i]] ++;
    }

    for (int i = 0; i < n; i ++) {
        if (freqMap[arr[i]] == 1) {
            return arr[i];
        }
    }

    return -1;

}

int main() {

    vector<int> arr = {1, 2, 1, 2, 3, 2};
    int ans = firstNonRepeating(arr, 6);

    cout << ans << "\n";

    return 0;
}