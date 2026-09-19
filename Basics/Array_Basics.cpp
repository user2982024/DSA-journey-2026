//  Task 01: Creating and printing array.
// #include <iostream>
// using namespace std;

// int main() {
//     int arr[5] = {10, 20, 30, 40, 50};

//     for (int i = 0; i < 5; i ++) {
//         cout<<"The array elements are: "<<arr[i]<<endl;
//     }

//     return 0;
// }


// Task 02: Inserting an element into array and printing.
// #include <iostream>
// using namespace std;

// int main() {
//     int n = 6;
//     int arr[n] = {1, 2, 3, 4, 5};

//     for (int i = 5; i > 2; i -- ) {
//         arr[i] = arr[i - 1];
//     }

//     arr[2] = 99;

//     for (int i = 0; i < n; i ++) {
//         cout<<arr[i]<<" ";
//     }

//     return 0;
// }


// Task 03: Deeleting an element from array and printing.
// #include <iostream>
// using namespace std;

// int main() {
//     int n = 6;
//     int arr[n] = {10, 20, 30, 40, 50};

//     for (int i = 0; i < n - 1; i ++) {
//         arr[i] = arr[i + 1];
//     }

//     n--;

//     for (int i = 0; i < n; i ++) {
//         cout<<arr[i]<<" ";
//     }

//     return 0;
// }


// Task 04: Search for an element (linear search)
// #include <iostream>
// using namespace std;
 
// void linearSearch(int arr[], int size, int target) {
//     bool found = false;
//     for (int i = 0; i < size; i ++) {   // Looping through the array
//         if (arr[i] == target) {     // searching for target
//             cout<<"Element found at index: "<<i<<endl;      // found case
//             found = true;
//             break;     // early return
//         }
//     }

//     if (!found) cout<<"Element is not present";      // not found case
// }
// int main() {
//     int arr[6]= {10, 20, 30, 40, 50, 60};

//     int target;
//     cout<<"Enter the number you want to search for"<<endl;
//     cin>>target;        // User input

//     linearSearch(arr, 6, target);       // Function call

//     return 0;
// }


// Task 05: Find minimum and maximum from the array
// #include <iostream>
// using namespace std;

// int findMin(int arr[], int size) {      // Min function
//     int minVal = INT_MAX;

//     for (int i = 0; i < size; i ++) {
//         if (arr[i] < minVal) {
//             minVal = arr[i];
//         }
//     }

//     return minVal;
// }

// int findMax(int arr[], int size) {      // Max function
//     int maxVal = INT_MIN;

//     for (int i = 0; i < size; i ++) {
//         if (arr[i] > maxVal) {
//             maxVal = arr[i];
//         }
//     }

//     return maxVal;
// }

// int main() { 

//     int arr[6] = {12, 45, 23, 51, 19, 8};

//     int ans1 = findMin(arr, 6);
//     int ans2 = findMax(arr, 6);

//     cout<<"Minimum element: "<<ans1<<endl;
//     cout<<"Maximum element: "<<ans2<<endl;

//     return 0;
// }


// Task 06: Reverse an Array
#include <iostream>
using namespace std;

void reverseArray(int arr[], int size) {
    int start = 0; 
    int end = size - 1;

    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        start ++;
        end --;
    }
}

int main() {

    int arr[6] = {10, 20, 30, 40, 50, 60};

    reverseArray(arr, 6);

    for (int i = 0; i < 6; i ++) {
        cout<<arr[i]<<" ";
    }

    return 0;
}

// These are the basics of array that will act as a foundation for problem solving. (Revision)