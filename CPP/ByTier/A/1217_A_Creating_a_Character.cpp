// Problem: CF 1217 A - Creating a Character
// https://codeforces.com/contest/1217/problem/A

#include <cstdio>
typedef long long ll;

/*
 * Problem: Count valid character builds where strength > intelligence after investing all exp points.
 *
 * Algorithm: 
 * - For a character with initial str, int and exp points:
 *   - We want final_str > final_int
 *   - Let x = points added to strength, (exp - x) points added to intelligence
 *   - Condition becomes: str + x > int + (exp - x)
 *   - Simplifying: 2*x > int - str + exp => x > (int - str + exp)/2
 *   - Also x must be in [0, exp] range.
 *   - So valid x are from ceil((int - str + exp)/2) to exp inclusive.
 *   - But if final_str <= final_int, that's invalid — count those cases too.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll a, b, n;
    scanf("%lld %lld %lld", &a, &b, &n);
    ll tmp = a + n - b - 1; // tmp represents (str - int + exp - 1)
    if (tmp < 0) {          // If not possible to have strength > intelligence
      puts("0");
    } else {
      // Calculate how many valid distributions there are
      printf("%lld\n", 1 + (((tmp / 2) < n) ? (tmp / 2) : n));
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/