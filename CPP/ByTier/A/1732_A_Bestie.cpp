// Problem: CF 1732 A - Bestie
// https://codeforces.com/contest/1732/problem/A

/*
 * Problem: Make GCD of array elements equal to 1 with minimum cost
 * Algorithm:
 *   - We try to make the overall GCD of the array equal to 1.
 *   - For each element, we can apply operation a[i] = gcd(a[i], i), with cost (n - i + 1).
 *   - Strategy:
 *     1. If current GCD is already 1, return 0
 *     2. Otherwise, compute the overall GCD of array.
 *     3. Check if we can achieve GCD = 1 by applying operation on some index j:
 *        - If gcd(g, n) == 1, then cost 1
 *        - Else if gcd(g, n-1) == 1, then cost 2
 *        - Else if gcd(g, n-2) == 1, then cost 3
 *        - Otherwise, it's definitely possible in at most 3 steps (this is proven).
 *
 * Time Complexity: O(n log(max(a))) due to GCD computation repeated up to n times.
 * Space Complexity: O(1), only using constant extra space.
 */

#include <cstdio>
long gcd(long a, long b) { return (b == 0) ? a : gcd(b, a % b); }
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long g(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      g = gcd(g, x); // Compute the GCD of all elements so far
    }
    if (g == 1) {
      puts("0"); // Already all elements have GCD = 1
    } else if (gcd(g, n) == 1) {
      puts("1"); // Can be made with one operation at index 0 (last element)
    } else if (gcd(g, n - 1) == 1) {
      puts("2"); // Two operations needed
    } else {
      puts("3"); // Three operations always sufficient to make GCD = 1
    }
  }
}


// https://github.com/VaHiX/codeForces/