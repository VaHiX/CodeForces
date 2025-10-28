// Problem: CF 1855 A - Dalton the Teacher
// https://codeforces.com/contest/1855/problem/A

/*
 * Problem: A. Dalton the Teacher
 * Purpose: Given a permutation representing students seated on chairs,
 *          determine the minimum number of swaps required to make all
 *          students unhappy (i.e., student i is not seated on chair i).
 *
 * Algorithm:
 *   - For each student, check if they are currently seated on their own
 *     chair number.
 *   - Count how many such "happy" students there are.
 *   - The minimum number of swaps needed is (cnt + 1) / 2, where cnt
 *     is the count of happy students. This works because each swap
 *     fixes at most two happy students.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long cnt(0);
    for (long p = 1; p <= n; p++) {
      long x;
      scanf("%ld", &x);
      cnt += (x == p);  // Increment count if student p is on chair p
    }
    printf("%ld\n", (cnt + 1) / 2);  // Minimum swaps needed
  }
}


// https://github.com/VaHiX/codeForces/