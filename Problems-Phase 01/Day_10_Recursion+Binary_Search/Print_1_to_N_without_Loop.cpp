
/*
    ============================================================
    Problem: Print 1 To N Without Loop
    Platform: GeeksforGeeks (GFG)
    Topic: Recursion
    Difficulty: Basic
    ============================================================

    PROBLEM STATEMENT
    ------------------------------------------------------------
    Given a positive integer N, print all integers from 1 to N
    in increasing order, separated by spaces.

    The task must be completed without using loops.

    EXAMPLE 1
    ------------------------------------------------------------
    Input:
        N = 5

    Output:
        1 2 3 4 5

    Explanation:
        The numbers from 1 through 5 are printed in increasing
        order.

    EXAMPLE 2
    ------------------------------------------------------------
    Input:
        N = 10

    Output:
        1 2 3 4 5 6 7 8 9 10

    Explanation:
        The function prints each integer from 1 to 10.


    ============================================================
    APPROACH: RECURSION
    ============================================================

    Recursion is a programming technique in which a function
    calls itself to solve a smaller version of the same problem.

    This solution uses two important components:

        1. Base Case
        2. Recursive Case


    BASE CASE
    ------------------------------------------------------------

        if (n == 0) {
            return;
        }

    When n becomes zero, the function stops calling itself.

    This prevents infinite recursion and allows the recursive
    calls to return.


    RECURSIVE CASE
    ------------------------------------------------------------

        printTillN(n - 1);

    The function calls itself with n - 1, gradually reducing
    the problem until the base case is reached.

    After the recursive call returns, we execute:

        cout << n << " ";

    This prints the current value of n.


    WHY DOES THE OUTPUT APPEAR IN INCREASING ORDER?
    ------------------------------------------------------------

    The recursive call happens BEFORE the print statement.

    For example, when printTillN(5) is called, the function
    first calls printTillN(4), which calls printTillN(3),
    continuing until printTillN(0) reaches the base case.

    Once the base case returns, the suspended function calls
    resume in reverse order:

        printTillN(1) prints 1
        printTillN(2) prints 2
        printTillN(3) prints 3
        printTillN(4) prints 4
        printTillN(5) prints 5

    Therefore, the final output is:

        1 2 3 4 5


    ============================================================
    C++ IMPLEMENTATION
    ============================================================
*/

#include <iostream>

using namespace std;

class Solution {
public:
    void printTillN(int n) {

        // Base case: stop when n reaches zero.
        if (n == 0) {
            return;
        }

        // Recursive call: solve the smaller problem first.
        printTillN(n - 1);

        // Print n after the recursive call returns.
        cout << n << " ";
    }
};


/*
    ============================================================
    DRY RUN
    ============================================================

    Input:
        n = 3

    Assume the initial call is:

        printTillN(3)


    ------------------------------------------------------------
    RECURSIVE DESCENT
    ------------------------------------------------------------

    Call 1:
        printTillN(3)

        3 != 0
        Calls printTillN(2)
        Printing is postponed.


    Call 2:
        printTillN(2)

        2 != 0
        Calls printTillN(1)
        Printing is postponed.


    Call 3:
        printTillN(1)

        1 != 0
        Calls printTillN(0)
        Printing is postponed.


    Call 4:
        printTillN(0)

        n == 0
        Base case reached.
        Return without printing anything.


    ------------------------------------------------------------
    RECURSIVE UNWINDING
    ------------------------------------------------------------

    The calls now resume in reverse order.

    Return to printTillN(1):
        Print 1

    Return to printTillN(2):
        Print 2

    Return to printTillN(3):
        Print 3


    FINAL OUTPUT
    ------------------------------------------------------------

        1 2 3


    ============================================================
    RECURSION CALL TREE
    ============================================================

                    printTillN(3)
                         |
                    printTillN(2)
                         |
                    printTillN(1)
                         |
                    printTillN(0)
                         |
                      return
                         |
                      print 1
                         |
                      print 2
                         |
                      print 3


    ============================================================
    EDGE CASES
    ============================================================

    CASE 1: n = 1
    ------------------------------------------------------------

    Input:
        n = 1

    Output:
        1

    Explanation:
    The function calls printTillN(0), returns, and then prints 1.


    CASE 2: n = 2
    ------------------------------------------------------------

    Input:
        n = 2

    Output:
        1 2

    Explanation:
    The recursive call reaches zero before printing begins.


    CASE 3: n = 5
    ------------------------------------------------------------

    Input:
        n = 5

    Output:
        1 2 3 4 5

    Explanation:
    Each suspended call prints its own value as recursion
    unwinds.


    CASE 4: n = 0
    ------------------------------------------------------------

    Input:
        n = 0

    Output:
        No numbers are printed.

    Explanation:
    The base case is reached immediately.


    CASE 5: Negative input
    ------------------------------------------------------------

    If n is negative, the current implementation will continue
    decreasing n and will not reach the base case n == 0.

    Therefore, negative input is outside the intended domain
    of this implementation.

    The standard problem assumes a non-negative or positive N.


    ============================================================
    WHERE I GOT STUCK / DEBUGGING NOTES
    ============================================================

    IMPLEMENTATION STATUS
    ------------------------------------------------------------

    My original implementation is correct for the standard
    problem constraints. No logical correction is required.


    1. UNDERSTANDING THE BASE CASE
    ------------------------------------------------------------

    The base case is:

        if (n == 0) {
            return;
        }

    Every recursive function needs a stopping condition.

    Without a reachable base case, the function would continue
    making recursive calls until the program ran out of stack
    space.


    2. WHY IS THE PRINT STATEMENT AFTER THE RECURSIVE CALL?
    ------------------------------------------------------------

    The order of these two statements determines the output:

        printTillN(n - 1);
        cout << n << " ";

    The recursive call must finish before n is printed.

    This causes the smallest value to print first, followed
    by the larger values as the function calls return.

    If we printed before the recursive call instead:

        cout << n << " ";
        printTillN(n - 1);

    the output would be in decreasing order:

        5 4 3 2 1


    3. UNDERSTANDING THE CALL STACK
    ------------------------------------------------------------

    Each function call pauses while waiting for the next
    recursive call to finish.

    Its current value of n is retained on the call stack.

    Once the base case returns, the calls resume in reverse
    order, and each call prints its own value.

    This is known as recursive unwinding.


    4. WHY IS THERE NO LOOP?
    ------------------------------------------------------------

    The function processes one value of n per recursive call.

    Instead of using a loop to move through all the numbers,
    recursion repeatedly calls the same function with a smaller
    argument until the base case is reached.


    ============================================================
    COMPLEXITY ANALYSIS
    ============================================================

    TIME COMPLEXITY: O(n)
    ------------------------------------------------------------

    The function is called for:

        n, n - 1, n - 2, ..., 1, 0

    This produces n + 1 function calls for non-negative n.

    Each call performs a constant amount of work, excluding
    the cost of output operations.

    Therefore, the algorithm has O(n) time complexity.


    AUXILIARY SPACE COMPLEXITY: O(n)
    ------------------------------------------------------------

    Each recursive call occupies a stack frame.

    The deepest point of recursion contains approximately
    n + 1 active calls, including the base case.

    Therefore, the recursion stack requires O(n) space.


    ============================================================
    KEY LEARNINGS
    ============================================================

    1. Every recursive function needs an appropriate base case.

    2. Each recursive call should move toward the base case.

    3. Code placed after a recursive call executes during
       recursive unwinding.

    4. Printing before recursion produces decreasing order,
       while printing after recursion produces increasing order.

    5. Recursion uses the call stack to remember suspended
       function calls.

    6. This problem demonstrates linear time complexity and
       linear auxiliary stack space.

    ============================================================
    END OF SOLUTION
    ============================================================
*/