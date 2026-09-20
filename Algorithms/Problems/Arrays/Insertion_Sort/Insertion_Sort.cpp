#include <bits/stdc++.h>
using namespace std;

vector<int> insertionSort(vector<int> &arr, int n) {
    int j = 0;
    int temp = 0;

    for (int i = 1; i < n; i ++) {
        j = i - 1;

        if (arr[j] > arr[i]) {
            temp = arr[i];

            while (arr[j] > temp && j >= 0) {
                arr[j + 1] = arr[j];
                j --;
            }

            arr[j + 1] = temp;
        }
    }

    return arr;
}

int main() {

    vector<int> arr = {10, 1, 7, 4, 8, 2, 11, 0, 4, 10};

    insertionSort(arr, 10);

    for (int i = 0; i < arr.size(); i ++) {
        cout << arr[i] << " ";
    }

    return 0;
}