// Problem: CF 2034 F1 - Khayyam's Royal Decree (Easy Version)
// https://codeforces.com/contest/2034/problem/F1

/*
 * Problem: Khayyam's Royal Decree (Easy Version)
 * 
 * Purpose: 
 *   This code computes the expected value of Khayyam's satchel at the end of the game,
 *   where gems are drawn from a chest and special configurations trigger royal decrees
 *   that double the value of the satchel.
 *
 * Algorithms/Techniques:
 *   - Dynamic Programming with inclusion-exclusion principle
 *   - Modular arithmetic with precomputed factorials and inverses
 *   - Combinatorial calculations for probabilities
 *   - Fast exponentiation for modular inverse
 *
 * Time Complexity:
 *   O(k^2 * (n + m) + k * log(P)) per test case, where P is the modulus 998244353.
 *   Preprocessing of factorials and inverses takes O(n + m).
 *   The DP calculation and final expected value computation are bounded by k^2 and
 *   the number of combinations involved.
 *
 * Space Complexity:
 *   O(n + m + k) for storing factorials, inverses, and auxiliary arrays.
 */

#include <algorithm>
#include <iostream>
#include <utility>

#define int long long
using namespace std;
using Pii = pair<int, int>;
const int N = 5e3 + 5, L = 4e5 + 5, P = 998244353;
int t, n, m, k, f[L], I[L], g[N], r;
Pii a[N];

// Fast exponentiation to compute modular inverse
int Q(int x, int y) {
  if (!y) {
    return 1;
  }
  int z = Q(x, y / 2);
  return z * z % P * (y & 1 ? x : 1) % P;
}

// Computes combination C(x, y) = x! / (y! * (x - y)!)
int C(int x, int y) { return f[x] * I[y] % P * I[x - y] % P; }

signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  
  // Precompute factorials and their modular inverses
  f[0] = I[0] = 1;
  for (int i = 1; i < L; i++) {
    f[i] = f[i - 1] * i % P;
  }
  I[L - 1] = Q(f[L - 1], P - 2);
  for (int i = L - 2; i; i--) {
    I[i] = I[i + 1] * (i + 1) % P;
  }
  
  for (cin >> t; t--; fill(g, g + k + 1, r = 0)) {
    cin >> n >> m >> k;
    
    // Transform scroll conditions into "remaining gems" format
    for (int i = 1; i <= k; i++) {
      cin >> a[i].first >> a[i].second;
      a[i].first = n - a[i].first;
      a[i].second = m - a[i].second;
    }
    
    // Sort scroll conditions by number of remaining gems
    sort(a + 1, a + k + 1);
    
    // DP: calculate contribution of each scroll condition
    for (int i = 1; i <= k; i++) {
      // Contribution of current scroll condition, factoring in all previous ones
      g[i] = C(a[i].first + a[i].second, a[i].first) *
             (2 * a[i].first + a[i].second) % P;
      
      // Add contributions from earlier conditions using inclusion-exclusion
      for (int j = 0; j < i; j++) {
        if (a[j].second <= a[i].second) {
          g[i] = (g[i] +
                  g[j] * C(a[i].first + a[i].second - a[j].first - a[j].second,
                           a[i].first - a[j].first)) %
                 P;
        }
      }
      
      // Add total contribution to final result
      r = (r + g[i] * C(n - a[i].first + m - a[i].second, n - a[i].first)) % P;
    }
    
    // Final expected value includes base value plus correction for all paths
    cout << (r + (2 * n + m) * C(n + m, n)) % P * Q(C(n + m, n), P - 2) % P
         << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/