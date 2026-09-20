#include <bits/stdc++.h>
using namespace std;

// Insertion sort ascending
vector<int> insertionSortAscending(vector<int> &arr, int n) {
    int temp = 0;
    int j = 0;

    for (int i = 1; i < n; i ++) {
        j = i - 1;
        
        if (arr[i] < arr[j]) {
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

// Insertion sort descending
vector<int> insertionSortDescending(vector<int> &arr, int n) {
    int temp = 0;
    int j = 0;

    for (int i = 1; i < n; i ++) {
        j = i - 1;
        
        if (arr[i] > arr[j]) {
            temp = arr[i];

            while (arr[j] < temp && j >= 0) {
                arr[j + 1] = arr[j];
                j --;
            }

            arr[j + 1] = temp;
        }
    }

    return arr;
}

int main() {
    // int arr[] = {10, 6, 4, 2, 1, 7};

    vector<int> arr;
    arr.push_back(5);
    arr.push_back(2);
    arr.push_back(4);
    arr.push_back(6);
    arr.push_back(1);
    arr.push_back(3);

    cout << "The original array (before sorting) is: " << "\n";

    for (int i = 0; i < arr.size(); i ++) {
        cout << arr[i] << "\n";
    }

    // Ascending
    cout << "The sorted array (after applying the algorithm of insertion sort ascending) is: " << "\n";

    insertionSortAscending(arr, 6);

    for (int i = 0; i < arr.size(); i ++) {
        cout << arr[i] << "\n";
    }

    // Descending
    cout << "The sorted array (after applying the algorithm of insertion sort descending) is: " << "\n";

    insertionSortDescending(arr, 6);

    for (int i = 0; i < arr.size(); i ++) {
        cout << arr[i] << "\n";
    }

    return 0;
}