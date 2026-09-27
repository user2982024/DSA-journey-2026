#include <iostream>
using namespace std;

/*
============================================================
              PRINT N TO 1 USING RECURSION
============================================================

Problem:
---------
Given an integer N, print:

    N N-1 N-2 ... 2 1

using recursion.

Example:

    Input:
        N = 5

    Output:
        5 4 3 2 1


============================================================
                    CORE IDEA
============================================================

At every function call:

    1. Check the base case.
    2. Print the current value of n.
    3. Recursively solve the smaller problem n - 1.

The important point is that the PRINTING happens
BEFORE the recursive call.

Therefore, the output follows the same order in which
the recursive calls are initially made.


============================================================
*/


class Solution {
public:

    /*
    --------------------------------------------------------
                    RECURSIVE FUNCTION
    --------------------------------------------------------

    printNos(n) prints:

        n, n-1, n-2, ..., 1

    The function is void because we don't need to return
    a calculated value.
    --------------------------------------------------------
    */

    void printNos(int n) {

        /*
        ----------------------------------------------------
                        BASE CASE
        ----------------------------------------------------

        When n reaches 0, there is nothing left to print.

        We simply terminate this recursive call.

        Since the function is void, we use:

            return;

        rather than returning a value.
        ----------------------------------------------------
        */

        if (n == 0) {
            return;
        }


        /*
        ----------------------------------------------------
                        PROCESSING
        ----------------------------------------------------

        Print the current value BEFORE making the recursive
        call.

        For n = 5:

            print 5
            print 4
            print 3
            print 2
            print 1
        ----------------------------------------------------
        */

        cout << n << " ";


        /*
        ----------------------------------------------------
                    RECURSIVE CALL
        ----------------------------------------------------

        Now solve the smaller problem:

            printNos(n - 1)

        Therefore:

            printNos(5)
                ↓
            printNos(4)
                ↓
            printNos(3)
                ↓
            printNos(2)
                ↓
            printNos(1)
                ↓
            printNos(0)

        ----------------------------------------------------
        */

        printNos(n - 1);
    }
};


/*
============================================================
                        TEST PROGRAM
============================================================

This main() is for local testing.

For GFG, submit the Solution class according to
the platform's required format.
============================================================
*/

int main() {

    Solution solution;

    int n;

    cout << "Enter n: ";
    cin >> n;

    solution.printNos(n);

    cout << endl;

    return 0;
}


/*
============================================================
                        DRY RUN
============================================================

Suppose:

    n = 5


                    GOING DOWN
                    ──────────

Call:

    printNos(5)

First:

    n != 0

So:

    print 5

Then:

    printNos(4)


Next:

    printNos(4)

Print:

    4

Then:

    printNos(3)


Next:

    printNos(3)

Print:

    3

Then:

    printNos(2)

Print:

    2

Then:

    printNos(1)

Print:

    1

Then:

    printNos(0)


============================================================
                    BASE CASE
============================================================

At:

    printNos(0)

we execute:

    return;


The recursive chain ends.


============================================================
                    FINAL OUTPUT
============================================================

Because printing happened BEFORE the recursive call:

    5
    4
    3
    2
    1

Therefore:

    5 4 3 2 1


============================================================
                 CALL STACK VISUALIZATION
============================================================

For n = 5:


    printNos(5)
        |
        | print 5
        ↓
    printNos(4)
        |
        | print 4
        ↓
    printNos(3)
        |
        | print 3
        ↓
    printNos(2)
        |
        | print 2
        ↓
    printNos(1)
        |
        | print 1
        ↓
    printNos(0)
        |
        | BASE CASE
        ↓
      return


The output is produced while the stack is being built:

    5 4 3 2 1


============================================================
             IMPORTANT RECURSION CONCEPT
============================================================

Notice the order:

    cout << n;
    printNos(n - 1);


Processing happens BEFORE recursion.

Therefore:

    PROCESSING
        ↓
    RECURSIVE CALL


For:

    n = 5

we get:

    print 5
        ↓
    call 4

    print 4
        ↓
    call 3

    print 3
        ↓
    call 2

    print 2
        ↓
    call 1

    print 1
        ↓
    call 0

    stop


Therefore:

    5 4 3 2 1


============================================================
                  COMPARE WITH 1 TO N
============================================================

Previous problem:

    void printTillN(int n) {

        if (n == 0)
            return;

        printTillN(n - 1);

        cout << n << " ";
    }


Here:

    RECURSION
        ↓
    PROCESSING


Output:

    1 2 3 4 5


Current problem:

    void printNos(int n) {

        if (n == 0)
            return;

        cout << n << " ";

        printNos(n - 1);
    }


Here:

    PROCESSING
        ↓
    RECURSION


Output:

    5 4 3 2 1


============================================================
              SIDE-BY-SIDE COMPARISON
============================================================


        N → 1

        cout << n;
        recursiveCall(n - 1);

        Output:

            5 4 3 2 1


        1 → N

        recursiveCall(n - 1);
        cout << n;

        Output:

            1 2 3 4 5


This difference is extremely important.

The location of the processing relative to the
recursive call changes the output order.


============================================================
                    COMPLEXITY
============================================================

TIME COMPLEXITY
---------------

For each number from n down to 1, exactly one recursive
call is made.

Therefore:

    Number of calls = n + 1

Ignoring constants:

    Time = O(n)


SPACE COMPLEXITY
----------------

Each recursive call creates a stack frame.

Maximum recursion depth:

    n

Therefore:

    Space = O(n)


============================================================
                    KEY LESSONS
============================================================

1. The function is VOID.

   We don't need to return a calculated value.

       printNos(n - 1);


2. The base case is:

       if (n == 0)
           return;


3. Processing occurs BEFORE recursion:

       cout << n;

       printNos(n - 1);


4. Therefore, the numbers are printed in descending
   order:

       N → N-1 → ... → 1


5. The previous problem printed ascending order because
   processing happened AFTER recursion.


============================================================
                 MENTAL MODEL
============================================================

Remember:

    BEFORE recursive call
            ↓
        PROCESS NOW
            ↓
        then recurse


    AFTER recursive call
            ↓
        recurse first
            ↓
        PROCESS LATER
            ↓
        happens during unwinding


This distinction is one of the most important
foundations of recursion.


============================================================
*/