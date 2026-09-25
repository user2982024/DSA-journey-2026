// ```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // Helper function to check whether a character is a vowel
    bool isVowel(char ch) {
        return ch == 'a' ||
               ch == 'e' ||
               ch == 'i' ||
               ch == 'o' ||
               ch == 'u';
    }

    int maxVowels(string s, int k) {

        int n = s.length();
        int countVowels = 0;

        // Step 1: Build the first window
        for (int i = 0; i < k; i++) {
            if (isVowel(s[i])) {
                countVowels++;
            }
        }

        // The first window is our initial maximum
        int maxCount = countVowels;

        // Step 2: Slide the window
        for (int right = k; right < n; right++) {

            // Remove the outgoing character
            if (isVowel(s[right - k])) {
                countVowels--;
            }

            // Add the incoming character
            if (isVowel(s[right])) {
                countVowels++;
            }

            // Update maximum
            maxCount = max(maxCount, countVowels);
        }

        return maxCount;
    }
};
// ```

// ### Complexity

// **Time:** `O(n)`
// **Space:** `O(1)`

// ### The important pattern

// ```text
// First window
//     ↓
// Process k elements
//     ↓
// Store window state
//     ↓
// Slide
//     ↓
// Remove outgoing contribution
//     ↓
// Add incoming contribution
//     ↓
// Update answer
// ```

// The only change from your original implementation is that I've replaced the `start/end` + `break` structure with a cleaner `right` loop.

// Your original algorithmic idea was correct and **LeetCode accepted it**. The cleaned-up version is simply easier to read and easier to reproduce during an interview.

// And your helper function is now a perfectly natural part of the solution:

// ```cpp
// bool isVowel(char ch)
// ```

// You don't need the reference `char&` because the function doesn't modify the character.
