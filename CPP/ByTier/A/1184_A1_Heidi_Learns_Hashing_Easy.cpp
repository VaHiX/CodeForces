// Problem: CF 1184 A1 - Heidi Learns Hashing (Easy)
// https://codeforces.com/contest/1184/problem/A1

/*
 * Problem: Heidi Learns Hashing (Easy)
 * Purpose: Given a value r, find positive integers x, y such that H(x,y) = x^2 + 2xy + x + 1 = r.
 *          Output the pair with smallest x, or "NO" if none exists.
 *
 * Algorithm:
 *   - We iterate over possible values of x from 1 to 1e6.
 *   - For each x, we rearrange H(x,y) = r to solve for y:
 *     x^2 + 2xy + x + 1 = r
 *     2xy = r - x^2 - x - 1
 *     y = (r - x^2 - x - 1) / (2x)
 *   - Check if this y is a positive integer, and verify that the equation holds.
 *   - Return first valid pair with smallest x.
 *
 * Time Complexity: O(√r) in worst case, but bounded by 1e6 due to loop limit.
 * Space Complexity: O(1)
 */
#include <cstdio>
typedef long long ll;
int main() {
  ll r;
  scanf("%lld", &r);
  ll x(0), y(0);
  for (ll w = 1; w <= 1e6; w++) { // Iterate through possible values of x
    if (w * w + 3 * w + 1 > r) {   // Early termination condition
      break;
    }
    ll z = (r - w * w - w - 1) / (2 * w); // Compute potential y value
    if (w * w + 2 * w * z + w + 1 == r) { // Verify that this x, y pair satisfies H(x,y) = r
      x = w;
      y = z;
      break;
    }
  }
  if (x && y) {
    printf("%lld %lld\n", x, y);
  } else {
    puts("NO");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/