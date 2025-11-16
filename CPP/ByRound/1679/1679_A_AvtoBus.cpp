// Problem: CF 1679 A - AvtoBus
// https://codeforces.com/contest/1679/problem/A

/*
 * Problem: A. AvtoBus
 * Purpose: Determine the minimum and maximum number of buses that can exist
 *          given the total number of wheels n, where buses are either 2-axle (4 wheels)
 *          or 3-axle (6 wheels).
 *
 * Algorithm:
 * - For a given n, we want to find the minimum and maximum number of buses.
 * - Let x be the number of 2-axle buses (4 wheels each) and y be the number of 3-axle buses (6 wheels each).
 * - We have: 4x + 6y = n
 * - Simplifying: 2x + 3y = n/2
 * - Let m = n/2, then 2x + 3y = m
 * - Solving for x in terms of y: x = (m - 3y) / 2
 * - x must be non-negative integer, so (m - 3y) must be even and non-negative.
 * - Also, x >= 0 and y >= 0.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    if (n < 4 || n % 2) { // If n is less than 4 or odd, impossible to form valid combination
      puts("-1");
      continue;
    }
    n /= 2; // Now n represents total units of 2 wheels each (since 4x + 6y = 2*(2x + 3y) => 2x + 3y = n/2)
    // To get max buses: minimize y by setting y = 0 => x = n
    // But we need to check if it's valid (i.e., non-negative integer).
    // Since x = n and n >= 2, x is always valid. So max buses = n + 0 = n.
    // To get min buses: maximize y to minimize x, i.e., try largest possible y such that:
    //   - n - 3y >= 0 (x non-negative)
    //   - n - 3y must be even for integer x
    printf("%lld %lld\n", ((n + 2) / 3), (n / 2));
    // The formula gives us first value as minimum number of buses.
    // Second value is maximum: n/2 (when all are 2-axle).
    // For min case, it computes the minimal number of buses by trying combinations.
    // ((n+2)/3) derived from mathematical derivation considering optimal y
  }
}


// https://github.com/VaHiX/codeForces/