// Problem: CF 1118 A - Water Buying
// https://codeforces.com/contest/1118/problem/A

/*
 * Problem: A. Water Buying
 * Algorithm/Techniques: Greedy approach
 * 
 * Time Complexity: O(q), where q is the number of queries
 * Space Complexity: O(1)
 *
 * Description:
 * Polycarp needs to buy exactly n liters of water using 1-liter and 2-liter bottles.
 * The cost of a 1-liter bottle is a, and the cost of a 2-liter bottle is b.
 * We want to minimize the total cost.
 *
 * Strategy:
 * - If 2*a < b, then it's always better to buy individual 1-liter bottles.
 * - Otherwise, we should use as many 2-liter bottles as possible,
 *   and only use 1-liter bottles for the remaining liters (if odd).
 */

#include <cstdio>
typedef long long ll;

int main() {
  long q;
  scanf("%ld", &q);
  while (q--) {
    ll n, a, b;
    scanf("%lld %lld %lld", &n, &a, &b);
    ll ans(0);
    // If buying two 1-liter bottles is cheaper than one 2-liter bottle,
    // we use only 1-liter bottles
    if (2 * a < b) {
      ans = n * a;
    } else {
      // Otherwise, use as many 2-liter bottles as possible
      // and pay for the remaining 1-liter if needed
      ans = (n % 2) * a + (n / 2) * b;
    }
    printf("%lld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/