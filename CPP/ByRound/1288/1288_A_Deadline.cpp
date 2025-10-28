// Problem: CF 1288 A - Deadline
// https://codeforces.com/contest/1288/problem/A

/*
 * Code Purpose: Determines if Adilbek can complete a program optimization and execution
 *               within n days given that the program needs d days to run.
 *               By optimizing for x days, the program runs in ceil(d / (x + 1)) days.
 *               Total time = x + ceil(d / (x + 1)).
 *
 * Algorithms/Techniques: Brute-force search over possible optimization days
 *                        (p represents x from the formula)
 *
 * Time Complexity: O(sqrt(d) * T), where T is number of test cases
 * Space Complexity: O(1)
 */

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, d;
    scanf("%lld %lld", &n, &d);
    bool ans(false);
    // Iterate through possible values of p (optimization days)
    // We check up to sqrt(d) + 10 to ensure we cover all valid cases
    for (ll p = 0; p * p <= d + 10; p++) {
      // Calculate total days needed if we optimize for p days
      // u represents the execution time after optimization: ceil(d / (p + 1))
      ll u = p + (d + p) / (p + 1);
      if (u <= n) {
        ans = true;
        break;
      }
    }
    puts(ans ? "YES" : "NO");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/