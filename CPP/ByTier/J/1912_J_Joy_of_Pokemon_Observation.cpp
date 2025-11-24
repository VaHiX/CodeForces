// Problem: CF 1912 J - Joy of Pokémon Observation
// https://codeforces.com/contest/1912/problem/J

/*
 * Problem: Joy of Pok�emon Observation
 * Purpose: Count the number of valid combinations of Pok�emon populations 
 *          given total limb counts and species limb requirements.
 * 
 * Algorithms/Techniques:
 *   - Modular Arithmetic
 *   - Linear Diophantine Equations
 *   - GCD-based simplification
 *   - Inclusion-Exclusion (via summation over ranges)
 * 
 * Time Complexity: O(s * t / gcd(a,b)) per query for s=2, where t <= 1e9.
 * Space Complexity: O(1) additional space (excluding input/output buffers).
 * 
 * Input Format:
 *   - h: number of habitats
 *   - For each habitat:
 *     - t: total limbs
 *     - s: number of species
 *     - l[0..s-1]: limbs per species
 *
 * Output Format:
 *   - For each habitat, the count of valid Pok�emon populations.
 */

#include <cstdio>
#include <iostream>

using namespace std;
#define ll long long
int h;                 // Number of habitats
ll t, s;               // Total limbs, number of species
ll a, b, c;            // Limbs per species (a,b,c)
ll gcd(ll a, ll b) {   // Compute GCD of two numbers
  if (b == 0)
    return a;
  return gcd(b, a % b);
}
ll S(ll a, ll b, ll d) {  // Sum arithmetic sequence from a to b with step d
  if (a > b)
    return 0;
  ll cnt = (b - a) / d + 1;   // Number of elements
  return (a + b) * cnt / 2;   // Sum formula for arithmetic progression
}
ll Suan(ll a, ll b, ll t) { // Compute valid combinations for 2 species
  if (t < 0)
    return 0;
  ll g = gcd(a, b);           // Reduce to coprime form
  a /= g, b /= g, t /= g;
  ll ans = 0;
  for (int x = 0; x < b; x++) {  // Iterate through possible values of x
    if (t - a * x < 0)           // No valid y exists
      continue;
    ll tt = (t - a * x) / b;     // Compute upper bound for y
    ans += S((tt + 1) % a, tt + 1, a);  // Add number of solutions in range
  }
  return ans;
}
int main() {
  scanf("%d", &h);
  while (h--) {
    scanf("%lld%lld", &t, &s);
    unsigned long long ans = 0;
    if (s == 1) {               // One species case: check divisibility
      scanf("%lld", &a);
      if (t % a == 0)
        ans = 1;
    } else if (s == 2) {        // Two species case
      scanf("%lld%lld", &a, &b);
      ans = Suan(a, b, t) - Suan(a, b, t - 1);  // Difference gives count
    } else {                    // Three species case
      scanf("%lld%lld%lld", &a, &b, &c);
      for (ll x = 0; x < c; x++) {
        for (ll y = 0; y < c; y++) {
          if ((a * x + b * y - t) % c == 0) {     // Valid z modulo constraint
            ans += Suan(a, b, (t - a * x - b * y) / c);  // Compute contribution
          }
        }
      }
    }
    printf("%llu\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/