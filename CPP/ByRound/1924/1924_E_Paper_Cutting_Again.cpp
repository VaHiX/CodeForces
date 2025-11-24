// Problem: CF 1924 E - Paper Cutting Again
// https://codeforces.com/contest/1924/problem/E

/*
 * Problem: E. Paper Cutting Again
 *
 * Purpose: This code calculates the expected number of steps required to reduce the area
 *          of a rectangular paper sheet to strictly less than k, where cuts are made
 *          randomly along grid lines and right/bottom pieces are discarded.
 *
 * Algorithm:
 *   - Uses inclusion-exclusion and modular arithmetic to compute the expected value.
 *   - Precomputes modular inverses using the extended Euclidean algorithm for fast lookup.
 *   - Iterates over possible cuts along rows and columns, using mathematical formulas
 *     to count contributions to the expectation.
 *
 * Time Complexity: O(H + W)
 *   - Preprocessing of modular inverses takes O(H + W)
 *   - Two loops each iterate up to H and W respectively
 *
 * Space Complexity: O(H + W)
 *   - Stores a vector of size H + W for modular inverse precalculation
 */

#include <algorithm>
#include <iostream>
#include <vector>

#pragma GCC optimize("unroll-loops")
using namespace std;
using ll = long long;
const int mod = 1'000'000'007;
#define rep(i, a, b) for (int i = (int)(a); i < (int)(b); i++)
void solve();
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  rep(i, 0, t) solve();
}
void solve() {
  ll H, W, K;
  cin >> H >> W >> K;
  if (H * W < K) {
    cout << "0\n";
    return;
  }
  // Precompute modular inverses using extended Euclidean algorithm
  vector<int> rev(H + W, 1);
  rep(i, 2, H + W) rev[i] = mod - ll(mod / i) * rev[mod % i] % mod;
  int ans = 1;  // Start with 1 because we count the first step

  // Process cuts along rows
  rep(i, 1, H) {
    if (ll(i) * W < K)
      continue; // No need to cut if area already less than K
    ll tmp = ((K - 1) / i) + 1;  // Calculate threshold for this cut
    ans += rev[tmp + i - 1];  // Add modular inverse contribution
    if (ans >= mod)
      ans -= mod;
  }

  // Process cuts along columns
  rep(i, 1, W) {
    if (ll(i) * H < K)
      continue; // No need to cut if area already less than K
    ll tmp = ((K - 1) / i) + 1; // Calculate threshold for this cut
    ans += rev[tmp + i - 1];  // Add modular inverse contribution
    if (ans >= mod)
      ans -= mod;
  }
  
  cout << ans % mod << "\n";
}


// https://github.com/VaHiX/CodeForces/