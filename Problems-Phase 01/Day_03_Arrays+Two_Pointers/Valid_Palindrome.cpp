/*
===========================================================
DSA Journey 2026 - Phase 01
Day 03 - Arrays + Two Pointers
Problem 02: Valid Palindrome
LeetCode 125
===========================================================

Problem Link:
https://leetcode.com/problems/valid-palindrome/

-----------------------------------------------------------
PROBLEM STATEMENT
-----------------------------------------------------------

A phrase is a palindrome if, after converting all uppercase
letters into lowercase letters and removing all
non-alphanumeric characters, it reads the same forward and
backward.

Alphanumeric characters include:

    - Lowercase letters: a-z
    - Uppercase letters: A-Z
    - Digits: 0-9

Given a string `s`, return true if it is a palindrome,
otherwise return false.

-----------------------------------------------------------
EXAMPLES
-----------------------------------------------------------

Example 1:

Input:
s = "A man, a plan, a canal: Panama"

Output:
true

Explanation:

After removing non-alphanumeric characters and converting
uppercase letters to lowercase:

"amanaplanacanalpanama"

This reads the same forward and backward.


Example 2:

Input:
s = "race a car"

Output:
false


Example 3:

Input:
s = " "

Output:
true


===========================================================
INITIAL IDEA
===========================================================

The first observation is that this is naturally a
Two-Pointer problem.

We can place:

    start -> beginning of the string
    end   -> end of the string

Then compare characters from both sides.

Conceptually:

    start →                 ← end
    A man, a plan, a canal: Panama

However, the string contains:

    - spaces
    - commas
    - colons
    - other non-alphanumeric characters

These characters should be ignored.

Therefore, before comparing characters, we need to move
the pointers until they reach valid alphanumeric characters.


===========================================================
TWO-POINTER APPROACH
===========================================================

Initialize:

    start = 0
    end = s.length() - 1


While:

    start < end

perform the following:

-----------------------------------------------------------
STEP 1 - SKIP INVALID CHARACTERS FROM THE LEFT
-----------------------------------------------------------

If the character at `start` is not alphanumeric, move
the start pointer forward.

Conceptually:

    while character is NOT alphanumeric:
        start++


For example:

    "...,A..."

        ↑
      start

The comma should be ignored.

The pointer continues moving until it reaches:

    'A'


-----------------------------------------------------------
STEP 2 - SKIP INVALID CHARACTERS FROM THE RIGHT
-----------------------------------------------------------

Similarly, if the character at `end` is not alphanumeric,
move the end pointer backward.

Conceptually:

    while character is NOT alphanumeric:
        end--


-----------------------------------------------------------
STEP 3 - COMPARE THE VALID CHARACTERS
-----------------------------------------------------------

Once both pointers point to valid alphanumeric characters,
convert both characters to lowercase and compare them.

If:

    tolower(s[start]) != tolower(s[end])

then the string cannot be a palindrome.

Return:

    false


-----------------------------------------------------------
STEP 4 - MOVE BOTH POINTERS
-----------------------------------------------------------

If the characters match:

    start++
    end--

Continue until:

    start >= end


If no mismatch is found:

    return true


===========================================================
IMPORTANT LOGIC DISCOVERED DURING DEBUGGING
===========================================================

Initially, the idea was to skip invalid characters using
a condition such as:

    while (character is alphanumeric)

This was incorrect.

The pointer needs to move while the character is
NON-alphanumeric.

Therefore:

    while (!isalnum(character))


-----------------------------------------------------------
BOOLEAN LOGIC
-----------------------------------------------------------

A character is alphanumeric if:

    lowercase
    OR
    uppercase
    OR
    digit

Conceptually:

    isAlphanumeric =
        lowercase || uppercase || digit

Therefore, a character is NOT alphanumeric when:

    !(lowercase || uppercase || digit)

This is why the following structure is correct:

    while (!(
        lowercase ||
        uppercase ||
        digit
    ))


This is an application of De Morgan's Law:

    !(A || B || C)

is equivalent to:

    (!A && !B && !C)


===========================================================
WHY `isalnum()` IS USED
===========================================================

Instead of manually checking:

    'a' to 'z'
    'A' to 'Z'
    '0' to '9'

C++ provides:

    isalnum()

Therefore:

    isalnum(character)

returns true when the character is alphanumeric.

This makes the code shorter and easier to understand.


===========================================================
WHY `tolower()` IS USED
===========================================================

The problem is case-insensitive.

For example:

    'A' and 'a'

should be considered equal.

C++ provides:

    tolower()

Therefore:

    tolower(s[start])
    tolower(s[end])

allows us to compare characters without worrying about
uppercase/lowercase differences.


===========================================================
IMPORTANT EDGE CASE
===========================================================

The pointer movement must account for the possibility that
the pointers cross each other while skipping invalid
characters.

For example:

    "....."

There are no alphanumeric characters.

Therefore, while skipping characters, we must ensure:

    start < end

This prevents the pointers from continuing beyond the
valid comparison range.


===========================================================
WHY TWO INNER WHILE LOOPS DO NOT MAKE THIS O(n^2)
===========================================================

At first, it may appear that:

    while (start < end)

contains two additional `while` loops, which could suggest
O(n^2).

However, that is not the case.

The `start` pointer only moves forward.

The `end` pointer only moves backward.

Each character can be skipped only a limited number of
times.

Therefore, the total number of pointer movements remains
linear.

For an input of size n:

    start moves at most n positions
    end moves at most n positions

Total work:

    O(n) + O(n)

which simplifies to:

    O(n)


===========================================================
SPACE COMPLEXITY
===========================================================

No additional string or array is created.

We process the original string directly.

Therefore:

    Space Complexity = O(1)


===========================================================
ALTERNATIVE APPROACH
===========================================================

Another valid solution is to create a cleaned string.

Process the original string:

    1. Keep only alphanumeric characters.
    2. Convert them to lowercase.
    3. Store them in a new string.
    4. Use two pointers to check the cleaned string.

Example:

    "A man, a plan, a canal: Panama"

becomes:

    "amanaplanacanalpanama"

Then perform the palindrome check.

Complexity:

    Time  = O(n)
    Space = O(n)

This approach is simpler conceptually but uses additional
memory.

The direct two-pointer approach is more space efficient.


===========================================================
FINAL OPTIMIZED SOLUTION
===========================================================
*/

#include <string>
#include <cctype>

using namespace std;

class Solution {
public:

    bool isPalindrome(string s) {

        int n = s.length();

        int start = 0;
        int end = n - 1;

        while (start < end) {

            // Skip non-alphanumeric characters from the left.
            while (start < end && !isalnum(s[start])) {
                start++;
            }

            // Skip non-alphanumeric characters from the right.
            while (start < end && !isalnum(s[end])) {
                end--;
            }

            // Compare characters without considering case.
            if (tolower(s[start]) != tolower(s[end])) {
                return false;
            }

            // Move toward the center.
            start++;
            end--;
        }

        return true;
    }
};


/*
===========================================================
COMPLEXITY ANALYSIS
===========================================================

Time Complexity:

    O(n)

Each character is processed at most a constant number of
times by the two pointers.


Space Complexity:

    O(1)

Only a few integer variables are used and the original
string is processed directly.


===========================================================
KEY LEARNING
===========================================================

1. Two Pointers can be used on strings, not only arrays.

2. When characters need to be ignored, pointers can skip
   them instead of creating another data structure.

3. A `while` loop inside another loop does not automatically
   mean O(n^2).

4. Always analyze how many times the pointers can actually
   move throughout the entire algorithm.

5. Boolean expressions involving NOT and OR must be handled
   carefully.

6. `isalnum()` can simplify alphanumeric checks.

7. `tolower()` can simplify case-insensitive comparisons.

8. Edge cases where pointers cross must be considered when
   skipping elements.


===========================================================
FINAL RESULT
===========================================================

Problem:
LeetCode 125 - Valid Palindrome

Pattern:
Two Pointers

Difficulty:
Easy

Time:
O(n)

Space:
O(1)

Status:
SOLVED

===========================================================
*/