// Problem: CF 1498 A - GCD Sum
// https://codeforces.com/contest/1498/problem/A

/*
 * Problem: A. GCD Sum
 * Purpose: Find the smallest integer x >= n such that gcd(x, sum_of_digits(x)) > 1.
 * Algorithm:
 *   - For each test case, iterate from n to n + 100 (or until a solution is found).
 *   - For each number p, compute sum of its digits s.
 *   - Compute gcd(p, s) and check if it's greater than 1.
 *   - Return the first such p.
 *
 * Time Complexity: O(t * k * log(max(n))), where t is number of test cases,
 *                  k = 100 (upper bound on search range), and log factor comes from GCD computation.
 * Space Complexity: O(1) — only using a few variables regardless of input size.
 */

#include <cstdio>
typedef long long ll;

// Euclidean algorithm to compute GCD
ll gcd(ll a, ll b) { return (b == 0) ? a : gcd(b, a % b); }

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll res(0);
    for (ll p = n; p < n + 100; p++) { // Check up to 100 numbers ahead
      ll x(p), s(0);
      while (x) {
        s += x % 10;   // Extract last digit and add to sum
        x /= 10;       // Remove last digit
      }
      if (gcd(p, s) > 1) {  // If GCD of number and digit sum > 1
        res = p;
        break;
      }
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/