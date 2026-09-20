#include <bits/stdc++.h>
using namespace std;

bool binarySearch(int *arr, int k, int s, int e) {
    if (s > e) {
        return false;
    }

    int mid = s + (e - s) / 2;

    if (arr[mid] == k) {
        return true;
    }

    if (arr[mid] < k) {
        s = mid + 1;
    }

    else {
        e = mid - 1;
    }

    return binarySearch(arr, k, s, e);
}

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int key = 2;
    int start = 0;
    int end = 5;

    bool ans = binarySearch(arr, key, start, end);
    cout << ans << "\n";

    return 0;
}