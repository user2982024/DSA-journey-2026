#include <bits/stdc++.h>
using namespace std;

bool twoSumEqualsX(vector<int> &arr, int n, int x) {
    sort(arr.begin(), arr.end());

    int start = 0; 
    int end = n - 1;

    while (start < end) {
        if (arr[start] + arr[end] == x) {
            return true;
        }

        if (arr[start] + arr[end] < x) {
            start ++;
        }

        else {
            end --;
        }
    }

    return false;
}

int main() {

    vector<int> arr = {2, 4, 5, 7, 1, 0};

    bool ans = twoSumEqualsX(arr, 6, 4);
    cout << ans << "\n";

    return 0;
}