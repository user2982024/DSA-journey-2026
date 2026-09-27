#include <iostream>
using namespace std;

/*
============================================================
              PRINT 1 TO N USING RECURSION
============================================================

Problem:
---------
Given an integer N, print all numbers from 1 to N
using recursion.

Example:

    Input:
        N = 5

    Output:
        1 2 3 4 5


============================================================
                    CORE IDEA
============================================================

We want:

        1 2 3 4 5

Instead of printing n immediately, we first solve
the smaller problem:

        printTillN(n - 1)

and AFTER that recursive call returns, we print n.

Therefore:

        printTillN(n - 1);
        cout << n;

This is the key concept of this problem.


============================================================
              RECURSIVE RELATIONSHIP
============================================================

For n = 5:

    printTillN(5)

becomes:

    printTillN(4)
    print 5

Then:

    printTillN(4)

becomes:

    printTillN(3)
    print 4

And so on.


============================================================
*/


class Solution {
public:

    /*
    --------------------------------------------------------
                    RECURSIVE FUNCTION
    --------------------------------------------------------

    printTillN(n) prints:

        1 2 3 ... n

    The function returns nothing, so its return type is void.
    --------------------------------------------------------
    */

    void printTillN(int n) {

        /*
        ----------------------------------------------------
                        BASE CASE
        ----------------------------------------------------

        When n becomes 0, there is nothing left to print.

        We simply terminate the current recursive call.

        Since this is a void function, we don't return
        a value.

        We only write:

            return;
        ----------------------------------------------------
        */

        if (n == 0) {
            return;
        }


        /*
        ----------------------------------------------------
                    RECURSIVE CALL
        ----------------------------------------------------

        First solve the smaller problem:

            printTillN(n - 1)

        For example:

            printTillN(5)
                ↓
            printTillN(4)
                ↓
            printTillN(3)
                ↓
            printTillN(2)
                ↓
            printTillN(1)
                ↓
            printTillN(0)

        Notice that we DO NOT print n yet.
        ----------------------------------------------------
        */

        printTillN(n - 1);


        /*
        ----------------------------------------------------
                        PROCESSING
        ----------------------------------------------------

        The recursive call has now returned.

        We print n.

        This means printing happens during the
        UNWINDING phase of recursion.

        This is why the output becomes:

            1 2 3 4 5

        rather than:

            5 4 3 2 1
        ----------------------------------------------------
        */

        cout << n << " ";
    }
};


/*
============================================================
                        TEST PROGRAM
============================================================

This main() is only for local testing.

For GFG, submit the Solution class according to
the platform's required format.
============================================================
*/

int main() {

    Solution solution;

    int n;

    cout << "Enter n: ";
    cin >> n;

    solution.printTillN(n);

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

    printTillN(5)

It does NOT print 5 yet.

It calls:

    printTillN(4)

It does NOT print 4 yet.

It calls:

    printTillN(3)

It does NOT print 3 yet.

It calls:

    printTillN(2)

It does NOT print 2 yet.

It calls:

    printTillN(1)

It does NOT print 1 yet.

It calls:

    printTillN(0)


============================================================
                    BASE CASE
============================================================

At:

    printTillN(0)

we execute:

    return;


The function terminates.

Now recursion starts UNWINDING.


============================================================
                    COMING BACK UP
============================================================

The call:

    printTillN(1)

resumes AFTER:

    printTillN(0);

Now:

    cout << 1;

Output:

    1


Then:

    printTillN(2)

resumes.

It prints:

    2

Output:

    1 2


Then:

    printTillN(3)

prints:

    3

Output:

    1 2 3


Then:

    printTillN(4)

prints:

    4

Output:

    1 2 3 4


Finally:

    printTillN(5)

prints:

    5

Final output:

    1 2 3 4 5


============================================================
                 CALL STACK VISUALIZATION
============================================================

Going DOWN:

    printTillN(5)
          ↓
    printTillN(4)
          ↓
    printTillN(3)
          ↓
    printTillN(2)
          ↓
    printTillN(1)
          ↓
    printTillN(0)
          ↓
        return


Coming BACK UP:

    printTillN(1)
          ↓
        print 1

    printTillN(2)
          ↓
        print 2

    printTillN(3)
          ↓
        print 3

    printTillN(4)
          ↓
        print 4

    printTillN(5)
          ↓
        print 5


Final:

    1 2 3 4 5


============================================================
              WHY DOES THE ORDER REVERSE?
============================================================

This is one of the most important recursion concepts.

Our code is:

    printTillN(n - 1);

    cout << n;


The recursive call happens FIRST.

Therefore, the program must reach the base case before
the cout statements can execute.

The calls are created in this order:

    5 → 4 → 3 → 2 → 1 → 0


But the printing happens while returning:

    1 → 2 → 3 → 4 → 5


Therefore:

    CALL ORDER:
        5 4 3 2 1

    PRINT ORDER:
        1 2 3 4 5


============================================================
                  COMPARE WITH N TO 1
============================================================

If we instead write:

    cout << n << " ";
    printTillN(n - 1);


then printing happens BEFORE the recursive call.

For n = 5:

    print 5
    call 4

    print 4
    call 3

    print 3
    call 2

    print 2
    call 1

    print 1
    call 0

Output:

    5 4 3 2 1


Therefore:

    PROCESSING BEFORE RECURSION
            ↓
        5 4 3 2 1


    RECURSION BEFORE PROCESSING
            ↓
        1 2 3 4 5


This is a fundamental recursion pattern.


============================================================
                    COMPLEXITY
============================================================

TIME COMPLEXITY
---------------

For every number from n down to 0, one recursive call
is made.

Therefore there are approximately n calls.

Time:

    O(n)


SPACE COMPLEXITY
----------------

Every recursive call creates a stack frame.

For n = 5:

    printTillN(5)
    printTillN(4)
    printTillN(3)
    printTillN(2)
    printTillN(1)
    printTillN(0)

Maximum recursion depth is proportional to n.

Therefore:

    Space = O(n)


============================================================
                    KEY LESSONS
============================================================

1. This is a VOID recursive function.

   It doesn't calculate or return a value.

   Therefore:

       printTillN(n - 1);

   is enough.


2. The base case is:

       if (n == 0)
           return;


3. The recursive call is:

       printTillN(n - 1);


4. Processing happens AFTER recursion:

       cout << n;


5. Because processing happens AFTER the recursive call,
   it executes during stack unwinding.


6. Therefore:

       Call order:
           5 → 4 → 3 → 2 → 1 → 0

       Processing order:
           1 → 2 → 3 → 4 → 5


============================================================
                    FINAL PATTERN
============================================================

Remember this:

        void function
              +
        recursive call
              +
        processing AFTER call
              ↓
        processing happens
        during unwinding


        printTillN(5)

              ↓
        GO DOWN

        5 → 4 → 3 → 2 → 1 → 0

              ↓
        COME BACK UP

        1 → 2 → 3 → 4 → 5


============================================================
*/