// Problem: CF 1475 A - Odd Divisor
// https://codeforces.com/contest/1475/problem/A

#include <cstdio>
typedef long long ll;
int main() {
  long t;  // Number of test cases
  scanf("%ld", &t);
  while (t--) {
    ll n;  // Input number
    scanf("%lld", &n);
    while (n % 2 == 0) {  // Remove all factors of 2
      n /= 2;
    }
    puts(n > 1 ? "YES" : "NO");  // If remaining n > 1, it has an odd divisor > 1
  }
}
/*
 * Problem: Check if a number has an odd divisor greater than one.
 *
 * Algorithm:
 *   - Keep dividing the number by 2 until it's no longer even.
 *   - If the result is greater than 1, then the original number had an odd divisor > 1.
 *
 * Time Complexity: O(log n) per test case
 * Space Complexity: O(1)
 */

// https://github.com/VaHiX/codeForces/