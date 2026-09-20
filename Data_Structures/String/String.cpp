#include <bits/stdc++.h>
using namespace std;

int main() {

    // string s = "Abrar";

    // s.append("t");               // Inserts at the ending of the string

    // s.back();                    // The last element of the string (right side)

    // s.begin();                   // A pointer to first index. * can be used to get the actual value

    // s.clear();                   // Removes all elements from the string

    // s.empty()                    // Checks whether the string is empty or not

    // s.find("a")                  // Gives the index of the element

    // s.erase(s.find("b"));        // Removes all the elements including b and after b

    // s.erase(1);                  // Removes all the elements from the given index onwards including the given index too 

    // s.erase(2, 3);               // Removes parameter 2 number of elements from parameter 1 index including itself 

    // s.substr(0, 3);              // Gives elements from first parameter index to the second parameter index - 1, here from 0 index to 2 index (excluding 3 index)

    string s = "bcdefabcdef";
    string part = "xk";

    cout << s.find(part) << "\n";

    // cout << s << "\n";

    return 0;
}