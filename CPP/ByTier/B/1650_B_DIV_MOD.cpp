// Problem: CF 1650 B - DIV + MOD
// https://codeforces.com/contest/1650/problem/B

/*
 * Problem: Maximum value of f_a(x) = floor(x/a) + x % a in range [l, r]
 * Algorithm: Mathematical analysis of function behavior
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 *
 * The function f_a(x) = floor(x/a) + x % a can be rewritten as:
 *   If x = k*a + r where 0 <= r < a, then f_a(x) = k + r.
 * To maximize this, we want to maximize k + r subject to constraints.
 *
 * The maximum occurs either at:
 *   - r (the largest value such that r < a), i.e., r = a - 1, so x = k*a + a - 1
 *   - or at the rightmost value in range [l, r]
 * 
 * We compute two candidates:
 *   - d = r / a, m = r % a, res = d + m (from r itself)
 *   - prev = (d - 1) * a + (a - 1), if prev >= l, then tmp = (d - 1) + (a - 1)
 *     This checks whether the maximum value at boundary is achievable within [l,r]
 *
 * Sample:
 *   For l=1, r=4, a=3: f_3(2)=2 and f_3(4)=2 are maxima.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long l, r, a;
    scanf("%ld %ld %ld", &l, &r, &a);
    long d = r / a;          // Quotient when dividing r by a
    long m = r % a;          // Remainder when dividing r by a
    long res = d + m;        // Value at r
    long prev = (d - 1) * a + (a - 1); // Candidate maximum from previous quotient
    if (prev >= l) {         // If this valid point is within range [l,r]
      long tmp = (d - 1) + (a - 1); // Value at prev
      res = (res > tmp) ? res : tmp; // Take maximum of both candidates
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/