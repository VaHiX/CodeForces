// Problem: CF 1985 E - Secret Box
// https://codeforces.com/contest/1985/problem/E

/*
E. Secret Box

Purpose:
This code solves the problem of finding the maximum number of distinct locations
a secret box S with volume k can be placed inside a given box B with dimensions x, y, z.
The solution tries all combinations of valid dimensions (a, b, c) for S such that a*b*c = k,
and computes how many placements are possible for each valid dimension set. It returns the
maximum count among all valid configurations.

Algorithms/Techniques:
- Brute force over all divisors of k for one dimension (a)
- For each valid a, iterate through all valid b values such that a*b divides k
- Compute c = k / (a * b) and validate if c <= z
- Count valid placements using formula: (x - a + 1) * (y - b + 1) * (z - c + 1)

Time Complexity:
O(k^(2/3) * log k) per test case, where k is the volume. This arises from iterating over 
divisors of k and checking divisibility conditions efficiently.

Space Complexity:
O(1), only using constant extra space apart from input/output.
*/

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll x, y, z, k;
    scanf("%lld %lld %lld %lld", &x, &y, &z, &k);
    ll ans = 0;
    for (ll a = 1; a <= x; a++) { // Iterate through all possible values of 'a'
      if (k % a) // If 'a' does not divide k, skip
        continue;
      for (ll b = 1; b <= y; b++) { // Iterate through all possible values of 'b'
        if (k % (a * b)) // If a*b does not divide k, skip
          continue;
        ll c = k / (a * b); // Compute third dimension 'c' such that a*b*c == k
        if (c > z) // Check if 'c' exceeds the limit of box B
          continue;
        ll ways = (x - a + 1) * (y - b + 1) * (z - c + 1); // Count possible placements
        ans = (ans > ways ? ans : ways); // Update maximum number of placements
      }
    }
    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/