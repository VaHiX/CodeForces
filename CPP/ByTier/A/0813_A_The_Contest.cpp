// Problem: CF 813 A - The Contest
// https://codeforces.com/contest/813/problem/A

/*
 * Problem: Pasha wants to solve all n problems and submit solutions during working periods of a website.
 *          Each problem takes a[i] time units to solve.
 *          Website is working during m time periods [l_j, r_j].
 *          Goal: Find the earliest time Pasha can submit ALL solutions,
 *                or -1 if impossible.
 *
 * Algorithm:
 *   1. Sum up total time needed to solve all problems: a = sum(a[i])
 *   2. For each working period [l, r]:
 *      - If total time a <= r (can finish within this period),
 *        check if a >= l (can start at time a).
 *        - If yes, earliest valid time is a.
 *        - If no, earliest valid time is l.
 *   3. Return the minimal valid time found, or -1 if none.

 * Time Complexity: O(n + m), where n is number of problems and m is number of working periods.
 * Space Complexity: O(1), only using a few variables.
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long a(0);  // Total time to solve all problems
  while (n--) {
    long x;
    scanf("%ld", &x);
    a += x;  // Accumulate total solving time
  }
  long m;
  scanf("%ld", &m);
  long t(-1);  // Result: earliest time to submit all solutions, or -1
  while (m--) {
    long l, r;
    scanf("%ld %ld", &l, &r);
    if (a <= r) {  // If total time fits within this period
      t = (a >= l) ? a : l;  // Earliest valid time
      break;
    }
  }
  printf("%ld\n", t);
  return 0;
}


// https://github.com/VaHiX/CodeForces/