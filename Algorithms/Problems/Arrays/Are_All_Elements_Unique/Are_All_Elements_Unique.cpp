#include <bits/stdc++.h>
using namespace std;

// Approach 1:
// bool areAllElementsUnique(vector<int> &arr, int n) {          // T.C = O(n^2), S.C = O(1) for this approach
//     for (int i = 0; i < n; i ++) {
//         for (int j = i + 1; j < n - 1; j ++) {              
//             if (arr[j] == arr[i]) {
//                 return false;
//             }
//         }
//     }

//     return true;
// }

// Approach 2:
// bool areAllElementsUnique(vector<int> &arr, int n) {            // T.C = O(n), S.C = O(1) for this approach
//     for (int i = 0; i < n - 1; i ++) {
//         if (arr[i] == arr[i + 1]) {
//             return false;
//         }
//     }

//     return true;
// }

// Approach 3:
bool areAllElementsUnique(vector<int> &arr, int n) {            // T.C = O(n), S.C = O(n) for this approach(most optimal)
    unordered_map<int, int> frequencyMap;

    for (int i = 0; i < n; i ++) {
        frequencyMap[arr[i]] ++;
    }

    for (auto it = frequencyMap.begin(); it != frequencyMap.end(); it ++) {
        if (it->second > 1) {
            return false;
        }
    }

    return true;
}

int main() {

    vector<int> arr;

    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(4);
    arr.push_back(5);
    arr.push_back(6);
    arr.push_back(7);
    arr.push_back(8);

    bool ans = areAllElementsUnique(arr, 8);
    cout << ans;

    return 0;
}