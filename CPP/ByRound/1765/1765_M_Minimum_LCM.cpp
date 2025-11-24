// Problem: CF 1765 M - Minimum LCM
// https://codeforces.com/contest/1765/problem/M

/*
 * Problem: M. Minimum LCM
 * Purpose: For each test case, find two positive integers a and b such that a + b = n 
 *          and their LCM is minimized.
 *
 * Algorithm: 
 *   - For a + b = n, we want to minimize LCM(a, b) = (a * b) / GCD(a, b)
 *   - To minimize the LCM, we want a and b to share as many common factors as possible.
 *   - If n is odd, then n = 1 + (n-1), and GCD(1, n-1) = 1 → LCM = n-1
 *   - If n is even:
 *     - If n is a power of 2, we must try to make a and b as close as possible to minimize LCM.
 *     - Otherwise, let p be the smallest prime divisor of n. Then a = n/p and b = (p-1)*n/p
 *       This ensures GCD(a,b) is maximized and the LCM is minimized.
 *
 * Time Complexity: O(sqrt(n)) per test case due to finding the smallest prime factor
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long div(n); // Initialize divisor to n itself
    for (long p = 2; p * p <= n; p++) { // Loop up to sqrt(n) to find smallest prime factor
      if (n % p == 0) {
        div = p; // Found smallest prime factor
        break;
      }
    }
    printf("%ld %ld\n", (n / div), (div - 1) * (n / div)); // Output a and b as per formula
  }
}


// https://github.com/VaHiX/codeForces/