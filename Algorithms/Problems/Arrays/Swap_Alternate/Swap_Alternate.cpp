#include <bits/stdc++.h>
using namespace std;

vector<int> swapAlternate(vector<int> &arr, int n) {
    for (int i = 0; i < n - 1; i += 2) {
        swap(arr[i], arr[i + 1]);
    }

    return arr;
}

int main() {

    vector<int> arr = {1, 2, 3, 4, 5, 6};

    cout << "Original array: " << "\n";
    
    for (int i = 0; i < 6; i++) {
        cout << arr[i] << "\n";
    }

    swapAlternate(arr, 6);
    
    cout << "Swapped array: " << "\n";
    
    for (int i = 0; i < 6; i++) {
        cout << arr[i] << "\n";
    }

    return 0;
}