// Problem: CF 1442 A - Extreme Subtraction
// https://codeforces.com/contest/1442/problem/A

/*
 * Problem: A. Extreme Subtraction
 * Purpose: Determine if it's possible to make all elements of an array equal to zero
 *          using operations that decrement k elements from either the start or end.
 *
 * Algorithm:
 *   - For each test case, process elements from left to right.
 *   - Keep track of the minimum value seen so far (`m`) and cumulative decrement (`k`).
 *   - At each step, determine how much we can reduce current element without making previous
 *     elements negative (using `f |= (a -= k) < 0`).
 *   - Update running minimum (`m = a < m ? a : m`) and adjust `k`.
 *   - If any element becomes negative during processing, output "NO".
 *
 * Time Complexity: O(n) per test case.
 * Space Complexity: O(1).
 */

#include <stdio.h>
#include <stdlib.h>
#include <iosfwd>

using namespace std;
int t, n, a, m, k, f;
int main() {
  for (scanf("%d", &t); t--; printf(f ? "NO\n" : "YES\n"), k = f = 0)
    for (m = 2e6, scanf("%d", &n); n--;
         scanf("%d", &a), 
         f |= (a -= k) < 0,          // Check if current value becomes negative after subtracting k
         a < m ? m = a : 0,          // Update minimal value seen so far
         k += a -= m)                // Adjust k and subtract minimal value from current
      ;
  exit(0);
}


// https://github.com/VaHiX/codeForces/