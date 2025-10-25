// Problem: CF 1311 D - Three Integers
// https://codeforces.com/contest/1311/problem/D

/*
D. Three Integers
Algorithm: Brute-force search over possible values of A and B, and compute C as a multiple of B.
Time Complexity: O(a * b) per test case, where a and b are up to 10^4.
Space Complexity: O(1), constant extra space.

The algorithm tries all valid combinations of A (from 1 to 2*a) and B (from A to 2*b such that B is a multiple of A).
For each pair (A, B), it computes two candidates for C:
  - C = B * floor(c / B)
  - C = B * ceil(c / B)
Then calculates the number of operations needed to reach those values,
and keeps track of the minimum.

Note: The loop bounds are chosen to prevent excessive computation and ensure correctness.
*/
#include <bits/std_abs.h>
#include <cstdio>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c;
    scanf("%ld %ld %ld", &a, &b, &c);
    long cnt(1e9), A(-1), B(-1), C(-1);
    for (long tstA = 1; tstA <= 2 * a; tstA++) {
      for (long tstB = tstA; tstB <= 2 * b; tstB += tstA) {
        // For each valid pair (tstA, tstB), we try two candidates for C:
        // one using floor division and one using ceiling.
        for (long p = 0; p < 2; p++) {
          long tstC = tstB * (c / tstB) + p * tstB;
          // Compute total operations needed to adjust a, b, c to tstA, tstB, tstC
          long tstcnt =
              std::abs(tstA - a) + std::abs(tstB - b) + std::abs(tstC - c);
          if (tstcnt < cnt) {
            cnt = tstcnt;
            A = tstA;
            B = tstB;
            C = tstC;
          }
        }
      }
    }
    printf("%ld\n%ld %ld %ld\n", cnt, A, B, C);
  }
}


// https://github.com/VaHiX/codeForces/