// Problem: CF 1020 A - New Building for SIS
// https://codeforces.com/contest/1020/problem/A

/*
Problem: A. New Building for SIS
Purpose: Calculate minimum walking time between two locations in a multi-tower building with restricted passage floors.
Algorithms/Techniques: Greedy approach with distance computation and floor adjustments.
Time Complexity: O(k), where k is the number of queries (constant number of operations per query).
Space Complexity: O(1), only using a constant amount of extra space.

The building has n towers, each with h floors. Passages exist between adjacent towers on floors from a to b (inclusive).
Movement within a tower or between adjacent towers is 1 minute per floor/unit.
*/

#include <cstdio>
typedef long long ll;

int main() {
  ll n, h, a, b, k;
  scanf("%lld %lld %lld %lld %lld", &n, &h, &a, &b, &k);
  while (k--) {
    ll ta, fa, tb, fb;
    scanf("%lld %lld %lld %lld", &ta, &fa, &tb, &fb);
    
    // Calculate horizontal distance between towers
    ll ans = (ta > tb) ? (ta - tb) : (tb - ta);
    
    // If towers are different, adjust floor position to nearest valid passage floor
    if (ta != tb && fa < a) {
      ans += a - fa;  // Move up to the lowest valid floor
      fa = a;
    } else if (ta != tb && fa > b) {
      ans += fa - b;  // Move down to the highest valid floor
      fa = b;
    }
    
    // Add vertical distance between floors
    ans += (fb > fa) ? (fb - fa) : (fa - fb);
    printf("%lld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/