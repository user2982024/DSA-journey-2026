#include <bits/stdc++.h>
using namespace std;

// bool findDuplicates(vector<int> &arr, int n) {
//     sort(arr.begin(), arr.end());

//     for (int i = 0; i < n; i ++) {
//         if (arr[i] == arr[i + 1]) {
//             return true;
//         }
//     }

//     return false;
// }

bool findDuplicates(vector<int> &arr, int n) {
    unordered_map<int, int> freqMap;

    for (int i = 0; i < n; i ++) {
        freqMap[arr[i]] ++;
    }

    for (auto it = freqMap.begin(); it != freqMap.end(); it ++) {
        if (it->second > 1) {
            return true;
        }
    }

    return false;
}

int main() {

    vector<int> arr = {1, 3, 8, 8, 0, 2, 4, 4};

    bool ans = findDuplicates(arr, 8);
    cout << ans << "\n";

    return 0;
}