#include <bits/stdc++.h>
using namespace std;

int main()
{

    vector<int> arr;

    arr.push_back(5);
    arr.push_back(400);
    arr.push_back(3);
    arr.push_back(-2);
    arr.push_back(1);

    cout << "The array elements before sorting are: " << "\n";

    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << "\n";
    }

    sort(arr.begin(), arr.end());

    cout << "The array elements after sorting are: " << "\n";

    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << "\n";
    }

    sort(arr.rbegin(), arr.rend());

    cout << "The array elements after sorting in reverse order are: " << "\n";

    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << "\n";
    }

    string s = "mango";

    cout << "String before sorting is: " << "\n";

    for (int i = 0; i < s.length(); i ++) {
        cout << s[i] << "\n";
    }

    sort(s.begin(), s.end());

    cout << "String after sorting is: " << "\n";

    for (int i = 0; i < s.length(); i ++) {
        cout << s[i] << "\n";
    }

    vector<string> v;
    v.push_back("a");
    v.push_back("b");
    v.push_back("c");
    v.push_back("d");
    v.push_back("e");

    cout << "Vcetor of string before sorting: " << "\n";

    for (int i = 0; i < v.size(); i ++) {
        cout << v[i] << "\n";
    }

    // sort(v.begin(), v.end(), comp);            // Check the usage of comp in sorting strings.

    return 0;
}