// Problem: CF 1872 C - Non-coprime Split
// https://codeforces.com/contest/1872/problem/C

/*
 * Problem: C. Non-coprime Split
 * 
 * Algorithm/Techniques:
 * - The key idea is to find two positive integers a and b such that:
 *   1. l <= a + b <= r
 *   2. gcd(a, b) != 1 (i.e., they are not coprime)
 * 
 * Approach:
 * - For small ranges (r < 4), it's impossible to find valid a and b since
 *   all small sums have coprime pairs only.
 * - When l == r (single value), we try to factorize r into two parts a and b
 *   such that gcd(a,b) > 1 (i.e., a and b share a common factor > 1).
 * - For general cases (l < r), we choose a = 2 and b = (r - 2) which must be
 *   at least 2, and if (r - 2) is even, then gcd(2, (r - 2)) = 2 > 1.
 *   If (r - 2) is odd, we adjust b to be even by subtracting 2 more to make it even.
 * 
 * Time Complexity: O(sqrt(r)) per test case, due to factoring in the worst case.
 * Space Complexity: O(1), constant extra space used.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long l, r;
    scanf("%ld %ld", &l, &r);
    if (r < 4) {
      // For r < 4, there's no valid pair (a,b) such that a+b >= 4
      puts("-1");
    } else if (l == r) {
      // When l == r (i.e. a+b = r), we look for a factor of r
      long first(-1);
      for (long p = 2; p * p <= r; p++) {
        // Check if p divides r (and hence r - p)
        if ((r - p) % p == 0) {
          first = p;
          break;
        }
      }
      if (first > 0) {
        // If found, we set a = first and b = r - first
        printf("%ld %ld\n", first, r - first);
      } else {
        // No such factor found, thus no valid split
        puts("-1");
      }
    } else {
      // General case: l < r, we can take a = 2 and b = (r - 2)
      // We ensure b is at least 2 by computing r - r % 2 - 2
      printf("2 %ld\n", r - r % 2 - 2);
    }
  }
}


// https://github.com/VaHiX/CodeForces/