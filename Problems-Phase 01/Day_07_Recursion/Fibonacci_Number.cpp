#include <iostream>
using namespace std;

/*
============================================================
                  FIBONACCI USING RECURSION
============================================================

Problem:
---------
Given an integer N, return the Nth Fibonacci number.

The Fibonacci sequence is:

    F(0) = 0
    F(1) = 1

Every subsequent number is:

    F(n) = F(n - 1) + F(n - 2)

Therefore:

    0, 1, 1, 2, 3, 5, 8, 13, 21, ...


Examples:

    F(0) = 0
    F(1) = 1
    F(2) = 1
    F(3) = 2
    F(4) = 3
    F(5) = 5
    F(6) = 8


============================================================
                    RECURSIVE IDEA
============================================================

The mathematical definition of Fibonacci is itself
recursive:

        F(n) = F(n - 1) + F(n - 2)

Therefore, the code naturally becomes:

        return fib(n - 1) + fib(n - 2);


Unlike factorial:

        factorial(n)
             ↓
        factorial(n - 1)

Fibonacci creates TWO recursive calls:

        fib(n)
        /    \
       /      \
    fib(n-1)  fib(n-2)


This creates a RECURSION TREE.


============================================================
*/


class Solution {
public:

    /*
    --------------------------------------------------------
                    RECURSIVE FUNCTION
    --------------------------------------------------------

    fib(n) returns the nth Fibonacci number.

    Example:

        fib(5)

        returns:

        5
    --------------------------------------------------------
    */

    int fib(int n) {

        /*
        ----------------------------------------------------
                        BASE CASE 1
        ----------------------------------------------------

        The first Fibonacci number is:

            F(0) = 0

        Therefore:

            if n == 0
                return 0
        ----------------------------------------------------
        */

        if (n == 0) {
            return 0;
        }


        /*
        ----------------------------------------------------
                        BASE CASE 2
        ----------------------------------------------------

        The second Fibonacci value is:

            F(1) = 1

        Therefore:

            if n == 1
                return 1

        These two base cases stop the recursion.
        ----------------------------------------------------
        */

        if (n == 1) {
            return 1;
        }


        /*
        ----------------------------------------------------
                    RECURSIVE CASE
        ----------------------------------------------------

        Fibonacci is defined as:

            F(n) = F(n - 1) + F(n - 2)

        Therefore:

            fib(n - 1)
            +
            fib(n - 2)

        Both recursive calls return integers.

        We add those two returned values and return
        the result to the caller.
        ----------------------------------------------------
        */

        return fib(n - 1) + fib(n - 2);
    }
};


/*
============================================================
                        TEST PROGRAM
============================================================

This main() is for local testing.

For LeetCode, normally submit only the Solution class.
============================================================
*/

int main() {

    Solution solution;

    int n;

    cout << "Enter n: ";
    cin >> n;

    cout << "Fibonacci(" << n << ") = "
         << solution.fib(n) << endl;

    return 0;
}


/*
============================================================
                        DRY RUN
============================================================

Let's calculate:

        fib(5)


The first call becomes:

        fib(5)
        =
        fib(4) + fib(3)


Now:

        fib(4)
        =
        fib(3) + fib(2)


And:

        fib(3)
        =
        fib(2) + fib(1)


Eventually, the recursive calls reach:

        fib(1) → 1

        fib(0) → 0


============================================================
                  RECURSION TREE
============================================================

For fib(5):


                         fib(5)
                        /      \
                       /        \
                  fib(4)        fib(3)
                  /   \         /   \
                 /     \       /     \
             fib(3)  fib(2)  fib(2)  fib(1)
             /  \     /  \    /  \
            /    \   /    \  /    \
        fib(2) fib(1) fib(1) fib(0) fib(1) fib(0)
        /   \
       /     \
   fib(1)   fib(0)


Now calculate from the bottom:


    fib(0) = 0
    fib(1) = 1


    fib(2)

    = fib(1) + fib(0)

    = 1 + 0

    = 1


    fib(3)

    = fib(2) + fib(1)

    = 1 + 1

    = 2


    fib(4)

    = fib(3) + fib(2)

    = 2 + 1

    = 3


    fib(5)

    = fib(4) + fib(3)

    = 3 + 2

    = 5


FINAL ANSWER:

    fib(5) = 5


============================================================
              WHY THIS IS DIFFERENT FROM FACTORIAL
============================================================

Factorial:

    factorial(n)
          ↓
    factorial(n - 1)

There is ONE recursive branch.


Fibonacci:

                fib(n)
               /      \
              ↓        ↓
        fib(n-1)     fib(n-2)

There are TWO recursive branches.


Therefore Fibonacci creates a TREE rather than
a simple chain.


============================================================
              FACTORIAL VS FIBONACCI
============================================================


FACTORIAL:


    factorial(5)
          ↓
    factorial(4)
          ↓
    factorial(3)
          ↓
    factorial(2)
          ↓
    factorial(1)


One path.

This is essentially a chain.


FIBONACCI:


              fib(5)
             /      \
        fib(4)      fib(3)
        /   \       /   \
    fib(3) fib(2) fib(2) fib(1)
       ...


Multiple paths.

This is a tree.


============================================================
             WHY DO WE NEED TWO BASE CASES?
============================================================

Fibonacci needs:

    F(0) = 0

and:

    F(1) = 1


Because every recursive call eventually reaches
one of these two values.

For example:

    fib(4)

becomes:

    fib(3) + fib(2)

which eventually reaches:

    fib(1)
    fib(0)


Without these base cases, the recursion would never
know when to stop.


============================================================
                RETURN VALUE FLOW
============================================================

This is another very important concept.

Consider:

    return fib(n - 1) + fib(n - 2);


Suppose:

    fib(3)


First, the recursive calls calculate:

    fib(2) → 1
    fib(1) → 1


Then:

    fib(3)
      ↓
    1 + 1
      ↓
      2


Then the value 2 is returned to whoever called
fib(3).


So the information flows upward through the tree.


============================================================
                    COMPLEXITY
============================================================

TIME COMPLEXITY
---------------

This particular recursive Fibonacci implementation
is NOT efficient.

Why?

Because the same Fibonacci values are calculated
many times.

For example:

    fib(5)

calculates fib(3) multiple times.

The number of recursive calls grows exponentially.

Therefore the time complexity is approximately:

    O(2^n)

More precisely, it is O(phi^n), where phi is the
golden ratio, but O(2^n) is the common interview-level
description.


SPACE COMPLEXITY
----------------

Although there are many nodes in the recursion tree,
we don't keep all of them active simultaneously.

The maximum depth of the recursion tree is n.

Therefore the recursion stack requires:

    O(n)

space.


IMPORTANT:

    Time  → O(2^n)
    Space → O(n)


============================================================
              WHY IS THIS SOLUTION STILL USEFUL?
============================================================

You may wonder:

    "If it is so inefficient, why are we learning it?"

Because the purpose right now is NOT optimization.

We are learning:

    1. Multiple recursive calls
    2. Recursion trees
    3. Base cases
    4. Return values
    5. How branches combine
    6. How recursive problems expand


Later, we will optimize Fibonacci using:

    Memoization
          ↓
    Dynamic Programming


Then:

    Time → O(n)

instead of:

    O(2^n)


============================================================
                 IMPORTANT PATTERN
============================================================

Fibonacci gives us a new recursive pattern:


            CURRENT PROBLEM
                  ↓
          ┌───────┴───────┐
          ↓               ↓
     SMALLER #1       SMALLER #2
          ↓               ↓
        result          result
          └───────┬───────┘
                  ↓
              COMBINE
                  ↓
             final result


For Fibonacci:

            fib(n)
              ↓
      ┌───────┴───────┐
      ↓               ↓
  fib(n-1)         fib(n-2)
      ↓               ↓
      └───────┬───────┘
              ↓
              +
              ↓
           fib(n)


============================================================
                    KEY LESSONS
============================================================

1. Fibonacci has TWO recursive calls.

       fib(n - 1)
       fib(n - 2)


2. Therefore it creates a recursion TREE.


3. We need TWO base cases:

       fib(0) = 0
       fib(1) = 1


4. The recursive results are combined:

       fib(n - 1) + fib(n - 2)


5. The result is returned to the parent call:

       return fib(n - 1) + fib(n - 2);


6. This basic implementation has:

       Time  = O(2^n)
       Space = O(n)


7. The repeated calculations are what make it
   inefficient.


============================================================
                  RECURSION PROGRESSION
============================================================

You've now seen:


    PRINT N → 1
          ↓
    processing BEFORE recursion


    PRINT 1 → N
          ↓
    processing AFTER recursion


    SUM 1 → N
          ↓
    recursive result + current value


    FACTORIAL
          ↓
    recursive result × current value


    FIBONACCI
          ↓
    TWO recursive results
          ↓
    combine them


This is a very important progression in understanding
recursion.


============================================================
*/