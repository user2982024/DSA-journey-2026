#include <bits/stdc++.h>
using namespace std;

vector<int> sort01(vector<int> &arr, int n) {
    int start = 0;
    int end = n - 1;

    while (start <= end) {
        if (arr[start] == 1 && arr[end] == 0) {
            swap(arr[start], arr[end]);
            start ++;
            end --;
        }

        if (arr[start] == 0 && arr[end] == 1) {
            start ++;
            end --;
        }

        if (arr[start] == 1 && arr[end] == 1) {
            end --;
        }

        if (arr[start] == 0 && arr[end] == 0) {
            start ++;
        }
    }

    return arr;
}

int main() {

    vector<int> arr = {0, 1, 1, 0, 0, 1};

    sort01(arr, 6);

    for (int i = 0; i < arr.size(); i ++) {
        cout << arr[i] << "\n";
    }

    return 0;
}