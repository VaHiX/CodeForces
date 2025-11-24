// Problem: CF 1372 B - Omkar and Last Class of Math
// https://codeforces.com/contest/1372/problem/B

#include <cstdio>
typedef long long ll;

/*
 * Problem: Omkar and Last Class of Math
 * 
 * Given an integer n, find positive integers a and b such that a + b = n
 * and LCM(a, b) is minimized.
 *
 * Algorithm:
 * - For a given n, we want to minimize LCM(a, b) where a + b = n.
 * - We know that LCM(a, b) = (a * b) / GCD(a, b).
 * - To minimize LCM, we want to maximize GCD(a, b) and keep a and b as close as possible.
 * - If n is even, then a = b = n/2 gives GCD = n/2 and LCM = n/2.
 * - If n is odd, the best choice is a = 1, b = n-1 since GCD(1, n-1) = 1,
 *   which minimizes LCM.
 * 
 * However, the code does something different:
 * - It finds the smallest divisor p of n (starting from 2).
 * - Then it sets a = n/p and b = n*(p-1)/p which gives a + b = n.
 * - The reasoning being: we want to minimize LCM. If we let p be the smallest prime
 *   factor of n, then setting a = n/p and b = n – (n/p) (i.e., n * (p - 1) / p)
 *   results in LCM being minimized, because this choice minimizes the product while
 *   satisfying a + b = n.
 *
 * Time Complexity: O(sqrt(n)) per test case
 * Space Complexity: O(1)
 */

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll div(n); // Initialize with n (worst case divisor)
    for (ll p = 2; p * p <= n; p++) {
      if (n % p == 0) { // If p divides n
        div = p; // Set smallest divisor found
        break;
      }
    }
    printf("%lld %lld\n", n / div, n / div * (div - 1)); // Output a and b
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/