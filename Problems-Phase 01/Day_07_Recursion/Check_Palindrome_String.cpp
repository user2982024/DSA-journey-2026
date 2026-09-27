#include <iostream>
#include <string>
using namespace std;

/*
============================================================
                RECURSIVE PALINDROME CHECK
============================================================

Problem:
---------
Given a string, determine whether it is a palindrome.

A palindrome is a string that reads the same from left
to right and right to left.

Examples:
    "racecar" -> Palindrome
    "madam"   -> Palindrome
    "hello"   -> Not a palindrome


------------------------------------------------------------
APPROACH
------------------------------------------------------------

We use:

    1. Two Pointers
    2. Recursion

Two pointers:
    start -> points to the beginning of the string
    end   -> points to the end of the string

At every recursive call:

    Compare:
        s[start] and s[end]

    If they are different:
        The string cannot be a palindrome.
        Return false.

    If they are equal:
        Move both pointers toward the center:

            start + 1
            end - 1

        Then recursively check the smaller
        remaining portion of the string.


------------------------------------------------------------
BASE CASE
------------------------------------------------------------

    if (start >= end)

When start reaches or crosses end, we have checked all
necessary pairs of characters.

Therefore, the string is a palindrome.

Example:

    "racecar"

             start
               ↓
        r a c e c a r
        ↑           ↑
      start        end

Eventually:

        r a c e c a r
              ↑
          start/end

At this point:

    start >= end

So we return true.


------------------------------------------------------------
RECURSIVE RELATION
------------------------------------------------------------

    checkPalindrome(s, start, end)

becomes:

    checkPalindrome(s, start + 1, end - 1)

We remove one character from each side of the problem
and recursively check the smaller problem.


============================================================
*/


class Solution {
public:

    /*
    --------------------------------------------------------
                    RECURSIVE FUNCTION
    --------------------------------------------------------

    Parameters:
        s     -> reference to the string
        start -> index from the left
        end   -> index from the right

    Return:
        true  -> substring is a palindrome
        false -> substring is not a palindrome
    --------------------------------------------------------
    */

    bool checkPalindrome(string &s, int start, int end) {

        /*
        ----------------------------------------------------
                        BASE CASE
        ----------------------------------------------------

        If start reaches or crosses end, all required
        character comparisons have been completed.

        Therefore, the string is a palindrome.
        ----------------------------------------------------
        */

        if (start >= end) {
            return true;
        }


        /*
        ----------------------------------------------------
                    CHARACTER COMPARISON
        ----------------------------------------------------

        Compare the characters at both ends.

        Example:

            "racecar"

             r         r
             ↑         ↑
           start      end

        If they are different, the string cannot be
        a palindrome.
        ----------------------------------------------------
        */

        if (s[start] != s[end]) {
            return false;
        }


        /*
        ----------------------------------------------------
                    RECURSIVE CALL
        ----------------------------------------------------

        The current characters matched.

        Therefore, move toward the center:

            start + 1
            end - 1

        Then check the remaining substring.

        IMPORTANT:
        We use:

            start + 1
            end - 1

        NOT:

            start++
            end--

        Why?

        start++ means:

            Use the current value first,
            then increment the variable.

        But we want the NEXT recursive call to receive
        the updated positions directly.

        Therefore:

            start + 1
            end - 1

        is clearer and correct for our recursive state.
        ----------------------------------------------------
        */

        return checkPalindrome(s, start + 1, end - 1);
    }


    /*
    --------------------------------------------------------
                        MAIN FUNCTION
    --------------------------------------------------------

    This is the function that the user/problem calls.

    We start with:

        start = 0

    and:

        end = s.length() - 1

    Example:

        s = "racecar"

        indices:

          0 1 2 3 4 5 6
          r a c e c a r

        start = 0
        end   = 6
    --------------------------------------------------------
    */

    bool isPalindrome(string& s) {

        return checkPalindrome(
            s,
            0,
            s.length() - 1
        );
    }
};


/*
============================================================
                        MAIN FUNCTION
============================================================

This main() is included so that you can compile and test
the program locally.

For an online judge such as GFG, you generally submit only
the Solution class and do NOT need this main() function.
============================================================
*/

int main() {

    Solution solution;

    string s;

    cout << "Enter a string: ";
    cin >> s;


    /*
    --------------------------------------------------------
                        TEST THE RESULT
    --------------------------------------------------------
    */

    if (solution.isPalindrome(s)) {

        cout << "Result: Palindrome" << endl;

    } else {

        cout << "Result: Not a Palindrome" << endl;
    }


    return 0;
}


/*
============================================================
                        DRY RUN
============================================================

Suppose:

    s = "racecar"

Indices:

     0 1 2 3 4 5 6
     r a c e c a r

First call:

    checkPalindrome(s, 0, 6)

Compare:

    s[0] = 'r'
    s[6] = 'r'

They match.

Recursive call:

    checkPalindrome(s, 1, 5)


Second call:

    s[1] = 'a'
    s[5] = 'a'

They match.

Recursive call:

    checkPalindrome(s, 2, 4)


Third call:

    s[2] = 'c'
    s[4] = 'c'

They match.

Recursive call:

    checkPalindrome(s, 3, 3)


Fourth call:

    start = 3
    end   = 3

Therefore:

    start >= end

Base case is reached.

Return:

    true


============================================================
                RETURN / UNWINDING
============================================================

The true value travels back through the call stack:

    check(3,3)
        ↓ true

    check(2,4)
        ↓ true

    check(1,5)
        ↓ true

    check(0,6)
        ↓ true

Finally:

    isPalindrome()
        ↓
       true


============================================================
                WHAT IF IT IS NOT A PALINDROME?
============================================================

Suppose:

    s = "hello"

Indices:

     0 1 2 3 4
     h e l l o

First comparison:

    s[0] = 'h'
    s[4] = 'o'

They are different.

Therefore:

    return false;

No further recursive calls are necessary.


============================================================
                    COMPLEXITY ANALYSIS
============================================================

TIME COMPLEXITY
---------------

At every recursive call, we compare one pair of
characters and move:

    start + 1
    end - 1

Therefore, approximately n/2 comparisons are performed.

Ignoring constants:

    Time = O(n)


SPACE COMPLEXITY
----------------

Every recursive call creates a new stack frame.

For a string of length n, the recursion depth is
approximately n/2.

Therefore:

    Space = O(n)

This space is used by the recursion call stack.

IMPORTANT:

The string itself is passed by reference:

    string &s

so we are NOT creating a new copy of the string
at every recursive call.


============================================================
                    KEY LESSONS
============================================================

1. Recursion needs a BASE CASE.

       if (start >= end)
           return true;


2. Each recursive call should move toward the base case.

       start + 1
       end - 1


3. A mismatch immediately gives us the answer.

       if (s[start] != s[end])
           return false;


4. Because the function returns bool, the result of the
   recursive call must be propagated:

       return checkPalindrome(...);


5. This problem combines two DSA concepts:

       Two Pointers
              +
          Recursion
              ↓
       Recursive Palindrome


6. The most important mistake encountered was:

       start++
       end--

   instead of:

       start + 1
       end - 1


7. Remember:

       i + 1
       means "pass the next index"

       i++
       means "use the current value, then increment"


============================================================
                    FINAL PATTERN
============================================================

Recursive problems can often be understood through:

        1. What is my current state?
        2. What is my base case?
        3. What work do I do now?
        4. What smaller problem do I call?
        5. What information comes back?

For this problem:

        State:
            start, end

        Base case:
            start >= end

        Current work:
            compare s[start] and s[end]

        Smaller problem:
            start + 1, end - 1

        Returned information:
            true / false

============================================================
*/