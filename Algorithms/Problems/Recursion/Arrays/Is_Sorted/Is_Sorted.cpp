#include <bits/stdc++.h>
using namespace std;

bool isSorted(int *arr, int n) {
    if (n == 1) {
        return true;
    }

    if (arr[0] > arr[1]) {
        return false;
    }

    return isSorted(arr + 1, n - 1);
}

int main() {
    int arr[6] = {1, 3, 4, 6, 7, 10};

    bool ans = isSorted(arr, 6);
    cout << ans << "\n";

    return 0;
}


#include <iostream>
using namespace std;

int main() {
    cout << "return 0";
    return 0;
}