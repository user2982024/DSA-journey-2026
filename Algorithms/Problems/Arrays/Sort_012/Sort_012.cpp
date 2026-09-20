#include <bits/stdc++.h>
using namespace std;

vector<int> sort012(vector<int> &arr, int n) {
    int zerosCount = 0;
    int onesCount = 0;
    int twosCount = 0;

    for (int i = 0; i < n; i ++) {
        if (arr[i] == 0) {
            zerosCount ++;
        }

        if (arr[i] == 1) {
            onesCount ++;
        }

        else {
            twosCount ++;
        }
    }

    for (int i = 0; i < zerosCount; i ++) {
        arr[i] = 0;
    }

    for (int i = zerosCount; i < zerosCount + onesCount; i ++) {
        arr[i] = 1;
    }

    for (int i = zerosCount + onesCount; i < zerosCount + onesCount + twosCount; i ++) {
        arr[i] = 2;
    }

    return arr;
}

int main() {

    vector<int> arr = {2, 2, 1, 1, 0, 2, 0, 2};

    sort012(arr, 8);

    for (int i = 0; i < arr.size(); i ++) {
        cout << arr[i] << "\n";
    }

    return 0;
}
