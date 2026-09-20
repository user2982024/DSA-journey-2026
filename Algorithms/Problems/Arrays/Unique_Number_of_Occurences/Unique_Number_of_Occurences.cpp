#include <bits/stdc++.h>
using namespace std;

bool findUniqueOccurences(vector<int> &arr, int n) {
    unordered_map<int, int> freqMap;
    vector<int> v;

    for (int i = 0; i < n; i ++) {
        freqMap[arr[i]] ++;
    }

    for (auto it = freqMap.begin(); it != freqMap.end(); it ++) {
        v.push_back(it->second);
    }

    for (int i = 0; i < v.size() - 1; i ++) {
        if (v[i] == v[i + 1]) {
            return false;
        }
    }

    return true;
}

int main() {

    vector<int> arr = {1, 2, 2, 1, 1, 3, 4, 5, 6, 7, 7, 7};

    bool ans = findUniqueOccurences(arr, 12);
    cout << ans << "\n";

    return 0;
}