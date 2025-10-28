// Problem: CF 1197 A - DIY Wooden Ladder
// https://codeforces.com/contest/1197/problem/A

/*
 * Problem: A. DIY Wooden Ladder
 * Purpose: Given n planks with lengths a_i, find the maximum number k such that we can form
 *          a k-step ladder using some subset of these planks.
 *
 * Algorithm:
 *   - For each query:
 *     1. Find the two largest plank lengths (ma and mb) among all planks.
 *     2. The base of the ladder requires two planks of length at least k+1,
 *        so we need ma >= k+1 and mb >= k+1.
 *     3. The number of steps is k, so we have k planks each of length at least 1.
 *     4. We use the two largest planks as the base and can make at most (mb - 1) steps
 *        because one of the base planks must be at least (k+1), and we want to maximize k.
 *     5. Thus, the maximum k is min(n - 2, mb - 1).
 *
 * Time Complexity: O(n) per query, where n is the number of planks.
 * Space Complexity: O(1)
 */

#include <cstdio>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long ma(0), mb(0); // ma = largest length, mb = second largest length
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x >= ma) {
        mb = ma;  // Previous max becomes second max
        ma = x;   // Update max
      } else if (x > mb) {
        mb = x;   // Update second max
      }
    }
    long ans = n - 2;   // At most n-2 steps can be made (2 for base, rest for steps)
    ans = (ans < mb - 1) ? ans : (mb - 1);  // But limited by second largest length minus 1
    printf("%ld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/