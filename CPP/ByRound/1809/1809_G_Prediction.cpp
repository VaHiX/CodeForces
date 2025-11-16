// Problem: CF 1809 G - Prediction
// https://codeforces.com/contest/1809/problem/G

/*
 * Problem: Prediction
 * Algorithm: Dynamic Programming with Sliding Window
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * 
 * Approach:
 * The key idea is that we can predict a game result only when the rating difference
 * between two players is greater than k. So we need to ensure that in the sequence
 * of matches (where each new player fights the current winner), the difference in
 * ratings between consecutive players in the sequence is always > k.
 * 
 * To achieve this:
 * - We sort participants by rating (already given as sorted)
 * - Use dynamic programming with sliding window:
 *   - f[i] represents number of valid ways to assign indices ending at position i
 *   - g[i] represents prefix sum of f up to i
 * - Use modular arithmetic for large results
 */

#include <iostream>

#define ll long long
using namespace std;
const int N = 1e6 + 5;
const int mod = 998244353;
int n, k, a[N], f[N], g[N], fact[N], inv[N];
signed main() {
  ios::sync_with_stdio(false), cin.tie(0);
  cout.precision(10), cout.setf(ios::fixed);
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  // If the highest and second-highest ratings differ by <= k, no valid arrangement exists
  if (a[n] - a[n - 1] <= k) {
    cout << "0\n";
    return 0;
  }
  // Precompute factorials
  for (int i = fact[0] = 1; i <= n; i++) {
    fact[i] = 1LL * fact[i - 1] * i % mod;
  }
  // Precompute modular inverses
  inv[0] = inv[1] = 1;
  for (int i = 2; i <= n; i++) {
    inv[i] = 1LL * inv[mod % i] * (mod - mod / i) % mod;
  }
  // Initialize DP arrays
  f[0] = g[0] = inv[n];
  for (int i = 1, j = 1; i <= n; i++) {
    // Sliding window: move j forward until a[i] - a[j] <= k
    while (a[i] - a[j] > k) {
      j++;
    }
    // f[i] = g[j - 1] (number of valid sequences ending at j - 1)
    f[i] = g[j - 1];
    // g[i] = g[i - 1] + f[i] * inv[n - j] (prefix sum updated)
    g[i] = (g[i - 1] + 1LL * f[i] * inv[n - j]) % mod;
  }
  // Final answer = f[n] * n! (total arrangements)
  cout << 1LL * f[n] * fact[n] % mod << "\n";
  return 0;
}


// https://github.com/VaHiX/CodeForces/