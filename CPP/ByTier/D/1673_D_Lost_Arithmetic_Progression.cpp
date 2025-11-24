// Problem: CF 1673 D - Lost Arithmetic Progression
// https://codeforces.com/contest/1673/problem/D

/*
 * Problem: Lost Arithmetic Progression
 * 
 * Algorithm:
 * We are given two arithmetic progressions B and C, where C contains all elements common to both A and B.
 * We need to count how many different finite arithmetic progressions A could have been.
 * 
 * Approach:
 * 1. The key insight is that the common elements of A and B form progression C.
 * 2. A must contain all elements of C and must be a subsequence of B.
 * 3. Since we know B and C, we derive constraints on A:
 *    - First term of A should match some term in B
 *    - Common difference of A should be a multiple of gcd(q, r)
 *    - Number of terms in A should be sufficient to cover C, and fit within B's bounds
 * 4. The main logic involves:
 *    - Checking if C can be a subsequence of B with some valid A
 *    - Enumerating valid common differences using divisors of r
 *    - For each valid common difference, calculating how many valid starting points exist
 *    - Using inclusion-exclusion or counting via divisors.
 * 
 * Time Complexity: O(sqrt(r) * T) where T is number of test cases and r is the common difference of C.
 * Space Complexity: O(1) - only using a few variables.
 */
#include <algorithm>
#include <iostream>

#define ll long long
#define gcd __gcd
using namespace std;
const int mod = 1e9 + 7;
inline ll lcm(ll a, ll b) { return a * b / gcd(a, b); }
signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    ll b, q, y, c, r, z, ans = 0;
    cin >> b >> q >> y >> c >> r >> z;
    if (r % q == 0 && c >= b && (c - b) % q == 0 &&
        c + r * (z - 1) <= b + q * (y - 1)) {
      // Check if C fits within B
      if (c + r * z > b + q * (y - 1) || c - r < b)
        cout << -1 << endl; // infinitely many such A
      else {
        // Enumerate divisors of r to find valid A progressions
        for (ll i = 1; i * i <= r; ++i) {
          if (r % i)
            continue;
          // Check if i can be a valid common difference for A
          if (lcm(i, q) == r)
            (ans += (r / i) * (r / i) % mod) %= mod;
          // Check if r/i can be a valid common difference for A
          if (lcm(r / i, q) == r && i != r / i)
            (ans += i * i % mod) %= mod;
        }
        cout << ans << endl;
      }
    } else
      cout << 0 << endl; // No such A exists
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/