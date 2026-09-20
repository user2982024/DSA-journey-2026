#include <bits/stdc++.h>
using namespace std;

vector<int> bubbleSort(vector<int> &arr, int n) {

    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n - i - 1; j ++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }

    return arr;
}

int main() {

    vector<int> arr = {10, 1, 7, 6, 14, 9, 0};

    bubbleSort(arr, 7);

    for (int i = 0; i < arr.size(); i ++) {
        cout << arr[i] << " ";
    }

    return 0;
}