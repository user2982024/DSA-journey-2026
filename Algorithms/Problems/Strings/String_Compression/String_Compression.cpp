#include <bits/stdc++.h>
using namespace std;

// string stringCompression(string &s, int n) {
//     unordered_map<char, int> freqMap;
//     string ans = " ";

//     for (int i = 0; i < n; i ++) {
//         freqMap[s[i]] ++;
//     }

//     for (auto it = freqMap.begin(); it != freqMap.end(); it ++) {
//         if (it->second == 1) {
//             ans.push_back(it->first);
//         }
        
//         else {
//             ans.push_back(it->first);
//             ans.push_back(it->second); // Issue of type conversion from int to char. 
//         }
//     }

//     return ans;
// }


string stringCompression(string &s, int n) {
    string ans = " ";
    int i = 0;
    int j = i + 1;
    int count = 1;

    while (i < n) {
        if (s[i] == s[j]) {
            i ++;
            j ++;
            count ++;
        }

        if (s[i] != s[j] || j == n) {
            ans.push_back(s[i]);

            if (count > 1) {
                ans.append(to_string(count));               // Done
            }
            
            i ++;
            j ++;
            count = 1;
        }
    }

    return ans;
}

int main() {

    string s = "abcddeehhh";

    string ans = stringCompression(s, 10);
    cout << ans << "\n";

    return 0;
}