// Problem: CF 2077 B - Finding OR Sum
// https://codeforces.com/contest/2077/problem/B

/*
B. Finding OR Sum
time limit per test: 2 seconds
memory limit per test: 256 megabytes

This problem involves determining the values of two hidden integers x and y (0 ≤ x, y < 2^30)
using at most 2 queries of the form (n|x)+(n|y). After these queries, a value m is given
and the solution must compute (m|x)+(m|y).

The approach uses bitwise operations:
- First query with n=0 gives (0|x)+(0|y) = x+y.
- Second query with n=1 gives (1|x)+(1|y) = (1|x)+(1|y).
Using these, we can deduce the values of x and y in a clever way using bit manipulation.

Time Complexity: O(1) - only a constant number of operations per test case
Space Complexity: O(1) - only a few variables used
*/

#include <iostream>
using namespace std;

int main() {
  int t, a = 715827882, c, d, m;  // a is a precomputed constant for bit manipulation
  cin >> t;
  while (t--)
    cout << a / 2 << " " << a << " !\n",   /* Initial query: uses fixed constants to get base values */
        cin >> c >> d >> m,                 /* Read the results of the two queries */
        cout << ((a / 2 & ~m) * 3 & d - 2 * a) + 2 * m + ((a & ~m) * 3 & c - a)   /* Compute final result using bitwise tricks */
             << '\n';
}


// https://github.com/VaHiX/codeForces/