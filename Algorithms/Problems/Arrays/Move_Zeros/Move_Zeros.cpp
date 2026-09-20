#include <bits/stdc++.h>
using namespace std;

vector<int> moveZeros(vector<int> &arr, int n) {
    int j = 0; 

    for (int i = 1; i < n; i ++) {
        if (arr[j] == 0 && arr[i] != 0) {
            swap(arr[j], arr[i]);
            j ++;
        }
    }

    return arr;
}

int main() {

    vector<int> arr = {0, 1, 0, 3, 12};

    moveZeros(arr, 5);

    for (int i = 0; i < arr.size(); i ++) {
        cout << arr[i] << " ";
    }

    return 0;
}