#include <iostream>
using namespace std;

/*
============================================================
        SUM OF FIRST N NATURAL NUMBERS USING RECURSION
============================================================

Problem:
---------
Given an integer N, calculate:

    1 + 2 + 3 + ... + N

using recursion.

Example:

    n = 5

    1 + 2 + 3 + 4 + 5 = 15


------------------------------------------------------------
RECURSIVE IDEA
------------------------------------------------------------

Instead of calculating everything at once:

    sum(5) = 1 + 2 + 3 + 4 + 5

we break the problem into smaller problems:

    sum(5) = 5 + sum(4)

    sum(4) = 4 + sum(3)

    sum(3) = 3 + sum(2)

    sum(2) = 2 + sum(1)

    sum(1) = 1


Therefore:

    sum(n) = n + sum(n - 1)


This is our recursive relationship.


============================================================
*/


class Solution {
public:

    /*
    --------------------------------------------------------
                    RECURSIVE FUNCTION
    --------------------------------------------------------

    recursiveSum(n) returns:

        1 + 2 + 3 + ... + n

    Example:

        recursiveSum(5)

        returns:

        15
    --------------------------------------------------------
    */

    int recursiveSum(int n) {

        /*
        ----------------------------------------------------
                        BASE CASE 1
        ----------------------------------------------------

        When n = 1:

            1

        is the answer.

        Therefore, return 1.
        ----------------------------------------------------
        */

        if (n == 1) {
            return 1;
        }


        /*
        ----------------------------------------------------
                        BASE CASE 2
        ----------------------------------------------------

        When n = 0:

            There are no positive natural numbers
            remaining to add.

        Therefore:

            sum(0) = 0

        This also prevents the recursion from continuing
        indefinitely if 0 is supplied.
        ----------------------------------------------------
        */

        if (n == 0) {
            return 0;
        }


        /*
        ----------------------------------------------------
                    RECURSIVE CASE
        ----------------------------------------------------

        The current number n is added to the answer
        returned by the smaller problem:

            recursiveSum(n - 1)

        Therefore:

            sum(n) = n + sum(n - 1)

        Example:

            sum(5)
            = 5 + sum(4)

            sum(4)
            = 4 + sum(3)

            ...

        ----------------------------------------------------
        */

        return n + recursiveSum(n - 1);
    }
};


/*
============================================================
                        TEST PROGRAM
============================================================

This main() allows us to test the solution locally.

For GFG submission, you normally submit only the
Solution class.
============================================================
*/

int main() {

    Solution solution;

    int n;

    cout << "Enter n: ";
    cin >> n;

    int result = solution.recursiveSum(n);

    cout << "Sum from 1 to " << n << " = "
         << result << endl;

    return 0;
}


/*
============================================================
                        DRY RUN
============================================================

Let's calculate:

    recursiveSum(5)


                GOING DOWN
                ──────────

recursiveSum(5)
       |
       | 5 + recursiveSum(4)
       ↓
recursiveSum(4)
       |
       | 4 + recursiveSum(3)
       ↓
recursiveSum(3)
       |
       | 3 + recursiveSum(2)
       ↓
recursiveSum(2)
       |
       | 2 + recursiveSum(1)
       ↓
recursiveSum(1)
       |
       | BASE CASE
       ↓
       return 1


============================================================
                    UNWINDING
============================================================

Now the returned values travel back upward.

recursiveSum(1)
        ↓
       1

recursiveSum(2)

    2 + recursiveSum(1)

    2 + 1

    = 3


recursiveSum(3)

    3 + recursiveSum(2)

    3 + 3

    = 6


recursiveSum(4)

    4 + recursiveSum(3)

    4 + 6

    = 10


recursiveSum(5)

    5 + recursiveSum(4)

    5 + 10

    = 15


Final Answer:

    15


============================================================
                CALL STACK VISUALIZATION
============================================================

Going DOWN:

        recursiveSum(5)
              ↓
        recursiveSum(4)
              ↓
        recursiveSum(3)
              ↓
        recursiveSum(2)
              ↓
        recursiveSum(1)
              ↓
           return 1


Coming BACK UP:

        recursiveSum(1) → 1
              ↑
        recursiveSum(2) → 2 + 1 = 3
              ↑
        recursiveSum(3) → 3 + 3 = 6
              ↑
        recursiveSum(4) → 4 + 6 = 10
              ↑
        recursiveSum(5) → 5 + 10 = 15


============================================================
            WHY DO WE NEED "return" HERE?
============================================================

This is the perfect example of the concept you
were asking about earlier.

Consider:

    return n + recursiveSum(n - 1);


The recursive function produces a VALUE.

For example:

    recursiveSum(4) → 10

The call:

    recursiveSum(5)

needs that value:

    5 + 10

Therefore:

    return 5 + recursiveSum(4);

gives us:

    15


The recursive result is PART of the current answer.


Compare this with a void function:

    print(n);
    recursivePrint(n - 1);

There is no value coming back that needs to be
used.


============================================================
                BASE CASE DISCUSSION
============================================================

Your original solution contains:

    if (n == 1)
        return 1;

and:

    if (n == 0)
        return 0;


Both are valid.

For a typical problem where:

    n >= 1

the following is sufficient:

    if (n == 1)
        return 1;

Because recursion eventually reaches 1.

Alternatively, we could use:

    if (n == 0)
        return 0;

Then:

    recursiveSum(1)
        = 1 + recursiveSum(0)
        = 1 + 0
        = 1

Both approaches work.


============================================================
                    COMPLEXITY
============================================================

TIME COMPLEXITY
---------------

For every n, we make one recursive call:

    n
    n-1
    n-2
    ...
    1

Therefore, there are approximately n calls.

Time:

    O(n)


SPACE COMPLEXITY
----------------

Every recursive call creates a stack frame.

For:

    recursiveSum(5)

there are:

    recursiveSum(5)
    recursiveSum(4)
    recursiveSum(3)
    recursiveSum(2)
    recursiveSum(1)

So the recursion depth is O(n).

Space:

    O(n)


============================================================
                    IMPORTANT LESSON
============================================================

The most important line is:

    return n + recursiveSum(n - 1);


This teaches us a fundamental recursion pattern:

        CURRENT WORK
             +
        SMALLER PROBLEM
             ↓
        CURRENT ANSWER


In mathematical form:

    sum(n) = n + sum(n - 1)

Base case:

    sum(1) = 1

This pattern appears everywhere in recursive DSA.


============================================================
                    FINAL PATTERN
============================================================

When solving a recursive problem, ask:

    1. What is the smallest problem I can solve directly?

    2. What is my base case?

    3. How can I express the current problem
       using a smaller problem?

    4. What information does the recursive call
       return to me?

For this problem:

    Base case:
        n == 1

    Current work:
        add n

    Smaller problem:
        n - 1

    Recursive result:
        sum from 1 to n-1

    Final relationship:

        sum(n) = n + sum(n-1)


============================================================
*/