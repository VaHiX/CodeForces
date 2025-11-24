// Problem: CF 2029 I - Variance Challenge
// https://codeforces.com/contest/2029/problem/I

/*
Problem: Variance Challenge (I. Variance Challenge)
Purpose:
  Given an array of integers 'a', and operations that add a fixed value 'k' to a subarray,
  find the minimum possible variance after exactly p operations for all p from 1 to m.
  Variance is defined as the sum of squared differences from the mean.
  
Algorithms/Techniques:
- Dynamic Programming with Segment Tree-like approach (sliding window optimization)
- Exhaustive search over possible sums with incremental adjustments
- Efficient computation for minimizing variance after fixed number of operations

Time Complexity: O(n * m * log(n)) for each test case
Space Complexity: O(n + m)

Note:
  The result is multiplied by n^2 to ensure integer output.
*/

#include <limits.h>
#include <algorithm>
#include <iostream>
#include <vector>

#define all(s) s.begin(), s.end()
using namespace std;
using ll = long long;
using ull = unsigned long long;
const int _N = 1e5 + 5;
int T;

void solve() {
  ll n, m, k;
  cin >> n >> m >> k;
  vector<ll> a(n + 1);
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  vector<ll> kans(m + 1, LLONG_MAX); // Stores minimum variance multiplied by n^2 for each p
  vector<ll> f(n + 1), g(n + 1), v(n + 1);
  vector<int> vis(n + 1), L(n + 1), L2(n + 1);
  ll sum = 0;
  for (int i = 1; i <= n; i++)
    sum += a[i];
  ll pans = 0;
  for (int i = 1; i <= n; i++)
    pans += n * a[i] * a[i]; // Initial squared sum contribution
  auto work = [&](ll s) { // For each possible target sum s
    ll ans = pans;
    ans += s * s - 2ll * sum * s; // Add initial constant term based on variance formula
    fill(f.begin(), f.end(), LLONG_MAX); // Reset DP arrays
    fill(g.begin(), g.end(), LLONG_MAX);
    for (int i = 1; i <= n; i++) {
      v[i] = n * (2 * a[i] * k + k * k) - 2ll * s * k; // Precompute contribution of operation at position i
      vis[i] = 0;
    }
    for (int i = 1; i <= m; i++) { // Process each operation sequence
      for (int j = 1; j <= n; j++) {
        L[j] = L2[j] = j;
        if (f[j - 1] < 0)
          f[j] = f[j - 1] + v[j], L[j] = L[j - 1]; // DP for minimizing cost of increasing segment
        else
          f[j] = v[j];
        if (!vis[j]) {
          g[j] = LLONG_MAX;
          continue;
        }
        if (g[j - 1] < 0)
          g[j] = g[j - 1] + 2ll * n * k * k - v[j], L2[j] = L2[j - 1]; // DP for decreasing segment
        else
          g[j] = 2ll * n * k * k - v[j];
      }
      ll min_sum = LLONG_MAX;
      int l = 1, r = n, type = 0;
      for (int j = 1; j <= n; j++) {
        if (f[j] < min_sum) { // Find least cost to increase a subarray
          min_sum = f[j], r = j, l = L[j];
        }
      }
      for (int j = 1; j <= n; j++) {
        if (g[j] < min_sum) { // Compare with decreasing case
          min_sum = g[j], r = j, l = L2[j];
          type = 1;
        }
      }
      ans += min_sum;
      if (type == 0) { // Do increase in subarray [l,r]
        for (int j = l; j <= r; j++)
          vis[j]++, v[j] += 2 * n * k * k;
      } else { // Do decrease in subarray [l,r]
        for (int j = l; j <= r; j++)
          vis[j]--, v[j] -= 2 * n * k * k;
      }
      kans[i] = min(kans[i], ans); // Update final answer
    }
  };
  for (ll x = sum; x <= sum + n * m * k; x += k) { // Try all valid sums with step size k
    work(x);
  }
  for (int i = 1; i <= m; i++)
    cout << kans[i] << " \n"[i == m]; // Output results
  return;
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--) {
    solve();
  }
}


// https://github.com/VaHiX/codeForces/