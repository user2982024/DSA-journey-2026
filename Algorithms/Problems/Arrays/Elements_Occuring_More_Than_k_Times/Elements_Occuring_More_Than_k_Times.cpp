#include <bits/stdc++.h>
using namespace std;

vector<int> elementsOccuringMoreThanKTimes(vector<int> &arr, int n, int k) {
    unordered_map<int, int> freqMap;
    vector<int> ans;

    for (int i = 0; i < n; i ++) {
        freqMap[arr[i]] ++;
    }

    for (auto it = freqMap.begin(); it != freqMap.end(); it ++) {
        if (it->second > k) {
            ans.push_back(it->first);
        }
    }

    return ans;
}

int main() {

    vector<int> arr = {1, 1, 1, 3, 4, 2, 2, 2, 5, 6, 7, 7, 7, 7, 8, 9, 9, 9, 10, 20};
    vector<int> ans = elementsOccuringMoreThanKTimes(arr, 20, 2);

    for (int i = 0; i < ans.size(); i ++) {
        cout << ans[i] << " ";
    }

    return 0;
}