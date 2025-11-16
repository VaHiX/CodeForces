// Problem: CF 1781 H1 - Window Signals (easy version)
// https://codeforces.com/contest/1781/problem/H1

/*
 * Problem: H1. Window Signals (easy version)
 * Algorithms/Techniques: Dynamic Programming with inclusion-exclusion principle,
 *                        Grid translation equivalence classes
 * Time Complexity: O(h^2 * w^2 * h * w) per test case, which is acceptable given h,w <= 40
 * Space Complexity: O(h * w) for the DP table and auxiliary arrays
 */

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
#define fi first
#define se second
const int N = 2e6 + 1;
const ll mod = 998244353;
int n, m, k;
int bx[3], by[3]; // Stores positions of broken windows
ll dp[41][41][2]; // DP table for tracking configurations
bool must[41][41]; // Tracks if a cell must be off due to being a broken window
pair<int, int> prv[41][41]; // Tracks predecessor for dynamic programming transitions

// Calculates number of distinct signals for a subgrid
ll cal(int pl, int pr, int ql, int qr, int p, int q) {
  if (pl > pr || ql > qr)
    return 1;
  ll good = 1;
  // Set up initial state for current subgrid
  for (int i = pl; i <= pr; i++) {
    for (int j = ql; j <= qr; j++) {
      good = good * 2 % mod; // Each cell can be on or off
      must[i][j] = false; // Reset
      prv[i][j] = {0, 0}; // Reset predecessor
    }
  }
  vector<pair<int, int>> v; // Stores broken windows in current subgrid
  // Enumerate all possible translations
  for (int dx = 0; dx <= n - p; dx++) {
    for (int dy = 0; dy <= m - q; dy++) {
      v.clear();
      // Check which broken windows are present in the subgrid after translation
      for (int i = 1; i <= k; i++) {
        int cx = bx[i] - dx;
        int cy = by[i] - dy;
        if (pl <= cx && cx <= pr && ql <= cy && cy <= qr) {
          v.push_back({cx, cy});
        }
      }
      sort(v.begin(), v.end()); // Sort to normalize
      if (v.empty())
        return good; // No broken windows in subgrid -> all configurations valid
      if (v.size() == 1)
        must[v[0].fi][v[0].se] = true; // One broken window in subgrid -> must be off
      if (v.size() == 2)
        prv[v[1].fi][v[1].se] = {v[0].fi, v[0].se}; // Two broken windows -> track dependency
    }
  }
  // Perform DP calculation for current subgrid
  for (int i = pl; i <= pr; i++) {
    for (int j = ql; j <= qr; j++) {
      if (prv[i][j].fi != 0) {
        // Transition from predecessor: use previous state to update current state
        int px = prv[i][j].fi;
        int py = prv[i][j].se;
        dp[i][j][1] = dp[px][py][0] + dp[px][py][1];
        if (dp[i][j][1] >= mod)
          dp[i][j][1] -= mod;
        dp[i][j][0] = dp[px][py][1];
        dp[px][py][0] = 1;
        dp[px][py][1] = 0;
      } else {
        // If no dependency, start fresh
        dp[i][j][0] = dp[i][j][1] = 1;
      }
      // If this cell is a broken window, it must be off
      if (must[i][j])
        dp[i][j][0] = 0;
    }
  }
  ll bad = 1;
  // Multiply all possible combinations that are invalid due to constraints
  for (int i = pl; i <= pr; i++) {
    for (int j = ql; j <= qr; j++) {
      bad = bad * (dp[i][j][0] + dp[i][j][1]) % mod;
    }
  }
  // Return total valid combinations minus invalid combinations
  return (good - bad + mod) % mod;
}

void solve() {
  cin >> n >> m >> k;
  for (int i = 1; i <= k; i++)
    cin >> bx[i] >> by[i]; // Read broken windows
  ll ans = 0;
  // Loop over all window sizes (p x q) to use inclusion-exclusion
  for (int p = 1; p <= n; p++) {
    for (int q = 1; q <= m; q++) {
      for (int pl = 1; pl <= 2; pl++) {
        for (int pr = p - 1; pr <= p; pr++) {
          for (int ql = 1; ql <= 2; ql++) {
            for (int qr = q - 1; qr <= q; qr++) {
              // Alternating sign for inclusion-exclusion principle
              int sgn = (pr + pl + p + ql + qr + q) % 2 ? -1 : 1;
              ll res = cal(pl, pr, ql, qr, p, q);
              ans = (ans + res * sgn + mod) % mod;
            }
          }
        }
      }
    }
  }
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/