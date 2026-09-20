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
    vector<int> arr;
    
    arr.push_back(8);
    arr.push_back(7);
    arr.push_back(6);
    arr.push_back(5);
    arr.push_back(4);
    arr.push_back(3);
    arr.push_back(2);
    arr.push_back(1);

    cout << "The array before sorting: " << "\n";

    for (int i = 0; i < 8; i ++) {
        cout << arr[i] << " ";
    }

    cout << "\n";

    bubbleSort(arr, 8);

    cout << "The array after applying bubble sort algorithm: " << "\n";

    for (int i = 0; i < 8; i ++) {
        cout << arr[i] << " ";
    }

    return 0;
}
