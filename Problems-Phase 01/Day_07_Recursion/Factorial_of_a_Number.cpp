#include <iostream>
using namespace std;

/*
============================================================
                FACTORIAL USING RECURSION
============================================================

Problem:
---------
Given a non-negative integer N, calculate N! using
recursion.

Factorial is defined as:

    n! = n × (n - 1) × (n - 2) × ... × 2 × 1

Examples:

    0! = 1
    1! = 1
    2! = 2
    3! = 6
    4! = 24
    5! = 120


============================================================
                    RECURSIVE IDEA
============================================================

Instead of calculating:

    5! = 5 × 4 × 3 × 2 × 1

all at once, we express the problem in terms of
a smaller factorial:

    5! = 5 × 4!

And:

    4! = 4 × 3!

Therefore:

    factorial(n)
        =
    n × factorial(n - 1)


This gives us our recursive relationship:

    factorial(n) = n * factorial(n - 1)


============================================================
                    BASE CASE
============================================================

We need to stop recursion at the smallest meaningful
problem.

Mathematically:

    0! = 1

Therefore:

    if (n == 0)
        return 1;


We can also use n == 1 as a base case because:

    1! = 1

Your solution includes both, which is perfectly valid.


============================================================
*/


class Solution {
public:

    /*
    --------------------------------------------------------
                    RECURSIVE FUNCTION
    --------------------------------------------------------

    factorial(n) returns n!

    Example:

        factorial(5)

        returns:

        120
    --------------------------------------------------------
    */

    int factorial(int n) {

        /*
        ----------------------------------------------------
                        BASE CASE 1
        ----------------------------------------------------

        By definition:

            0! = 1

        This stops the recursion when n reaches zero.
        ----------------------------------------------------
        */

        if (n == 0) {
            return 1;
        }


        /*
        ----------------------------------------------------
                        BASE CASE 2
        ----------------------------------------------------

        Also:

            1! = 1

        This is another valid stopping point.

        Technically, if our n is guaranteed to be
        non-negative, we don't need BOTH n == 0 and
        n == 1.

        Either can be used depending on the formulation.

        Your solution using both is completely correct.
        ----------------------------------------------------
        */

        if (n == 1) {
            return 1;
        }


        /*
        ----------------------------------------------------
                    RECURSIVE CASE
        ----------------------------------------------------

        Use the mathematical relationship:

            n! = n × (n - 1)!

        Therefore:

            factorial(n)
                =
            n * factorial(n - 1)

        The recursive call gives us the factorial of
        the smaller number.

        Then we multiply that result by n.
        ----------------------------------------------------
        */

        return n * factorial(n - 1);
    }
};


/*
============================================================
                        TEST PROGRAM
============================================================

This main() is for local testing.

For GFG, normally submit only the Solution class.
============================================================
*/

int main() {

    Solution solution;

    int n;

    cout << "Enter n: ";
    cin >> n;

    cout << "Factorial of " << n << " = "
         << solution.factorial(n) << endl;

    return 0;
}


/*
============================================================
                        DRY RUN
============================================================

Let's calculate:

    factorial(5)


============================================================
                    GOING DOWN
============================================================

factorial(5)

    = 5 * factorial(4)

             ↓

factorial(4)

    = 4 * factorial(3)

             ↓

factorial(3)

    = 3 * factorial(2)

             ↓

factorial(2)

    = 2 * factorial(1)

             ↓

factorial(1)

    = BASE CASE
    = 1


So the calls go:

    5
    ↓
    4
    ↓
    3
    ↓
    2
    ↓
    1


============================================================
                    COMING BACK UP
============================================================

Now the recursive calls return their values.

factorial(1)

    → 1


factorial(2)

    → 2 × factorial(1)

    → 2 × 1

    → 2


factorial(3)

    → 3 × factorial(2)

    → 3 × 2

    → 6


factorial(4)

    → 4 × factorial(3)

    → 4 × 6

    → 24


factorial(5)

    → 5 × factorial(4)

    → 5 × 24

    → 120


FINAL ANSWER:

    120


============================================================
                 CALL STACK VISUALIZATION
============================================================

During the downward phase:


    factorial(5)
          ↓
    factorial(4)
          ↓
    factorial(3)
          ↓
    factorial(2)
          ↓
    factorial(1)
          ↓
       return 1


During the unwinding phase:


    factorial(1) → 1
          ↑
    factorial(2) → 2 × 1 = 2
          ↑
    factorial(3) → 3 × 2 = 6
          ↑
    factorial(4) → 4 × 6 = 24
          ↑
    factorial(5) → 5 × 24 = 120


============================================================
             WHY DOES "return" MATTER HERE?
============================================================

This is an important difference from our printing
problems.

We have:

    int factorial(int n)

The return type is:

    int

So the function must produce an integer.

More importantly, the current call needs the result
from the smaller recursive call.

For example:

    factorial(5)

needs:

    factorial(4)

because:

    5! = 5 × 4!


So:

    return n * factorial(n - 1);

means:

    1. Call factorial(n - 1)
    2. Receive its result
    3. Multiply that result by n
    4. Return the final result


============================================================
              STEP-BY-STEP VALUE FLOW
============================================================

For factorial(4):


    factorial(4)
         |
         | needs factorial(3)
         ↓
    factorial(3)
         |
         | needs factorial(2)
         ↓
    factorial(2)
         |
         | needs factorial(1)
         ↓
    factorial(1)
         |
         ↓
        1


Now:

    factorial(2)
        ↓
    2 × 1
        ↓
        2


Then:

    factorial(3)
        ↓
    3 × 2
        ↓
        6


Then:

    factorial(4)
        ↓
    4 × 6
        ↓
       24


============================================================
              MATHEMATICAL CONNECTION
============================================================

The code:

    return n * factorial(n - 1);

comes directly from:

    n! = n × (n - 1)!

For example:

    5!
     =
    5 × 4!

And:

    4!
     =
    4 × 3!

Therefore:

    5!
     =
    5 × 4 × 3 × 2 × 1


The recursive function is simply expressing this
mathematical definition in code.


============================================================
                    COMPLEXITY
============================================================

TIME COMPLEXITY
---------------

We make one recursive call for every value:

    n
    n-1
    n-2
    ...
    1

Therefore:

    Time = O(n)


SPACE COMPLEXITY
----------------

Each recursive call creates a stack frame.

Maximum recursion depth is proportional to n.

Therefore:

    Space = O(n)


IMPORTANT:

The O(n) space is not because we create n copies
of the integer.

It is because there are O(n) active function calls
on the recursion stack.


============================================================
             CAN WE REMOVE ONE BASE CASE?
============================================================

Yes.

Your solution:

    if (n == 0)
        return 1;

    if (n == 1)
        return 1;


is correct.

But we can simplify it to:

    if (n == 0)
        return 1;

    return n * factorial(n - 1);


Why?

Because:

    factorial(1)

becomes:

    1 * factorial(0)

which becomes:

    1 * 1

which is:

    1


So this is also correct:

    int factorial(int n) {

        if (n == 0)
            return 1;

        return n * factorial(n - 1);
    }


Your original version is still perfectly valid.


============================================================
                    KEY LESSONS
============================================================

1. This is a VALUE-RETURNING recursive function.

       int factorial(int n)


2. The recursive call produces information that the
   current call needs.

       factorial(n - 1)


3. The recursive result is used in a calculation:

       n * factorial(n - 1)


4. Therefore we return the calculated result:

       return n * factorial(n - 1);


5. The recursion goes DOWN:

       5 → 4 → 3 → 2 → 1


6. The answer is constructed while coming BACK UP:

       1 → 2 → 6 → 24 → 120


7. This is different from our printing problems.

   Printing:
       process directly

   Factorial:
       get recursive result
       ↓
       use it
       ↓
       return new result


============================================================
                  RECURSION TEMPLATE
============================================================

This problem gives us a powerful general pattern:


    return CURRENT_VALUE
           OPERATOR
           RECURSIVE_RESULT;


For factorial:

    return n * factorial(n - 1);


For sum:

    return n + recursiveSum(n - 1);


This pattern appears frequently in basic recursion.


============================================================
*/