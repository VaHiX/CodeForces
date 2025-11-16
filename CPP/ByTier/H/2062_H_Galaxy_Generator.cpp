// Problem: CF 2062 H - Galaxy Generator
// https://codeforces.com/contest/2062/problem/H

/*
Algorithms/Techniques: 
- Dynamic Programming with bitmasking
- Preprocessing of prefix sums for rectangle queries
- Enumeration of connected components in subsets of stars
- Inclusion-exclusion principle applied via DP transitions
- Fast exponentiation for powers of 2

Time Complexity: O(n^4 * 2^n) where n <= 14
Space Complexity: O(n^4 + 2^n * n) for memoization and DP arrays
*/

#include <string.h>
#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef long long ll;
typedef array<int, 3> tr;
const int N = 15, M = 200, mod = 1e9 + 7, INF = 1e9;
template <typename T> void tomin(T &x, T y) { x = min(x, y); }
template <typename T> void tomax(T &x, T y) { x = max(x, y); }
int addv(int x, int y) { return (x + y >= mod) ? (x + y - mod) : (x + y); }
int subv(int x, int y) { return (x >= y) ? (x - y) : (x - y + mod); }
void add(int &x, int y) { x = addv(x, y); }
void sub(int &x, int y) { x = subv(x, y); }
int pw[M];
int T, n, a[N][N], b[N][N];
int f[N][N][N][N], g[N][1 << N], h[N][1 << N], ans;
vector<tr> ti[1 << N];
vector<int> ts[N][N];

// Query the number of stars in rectangle (x1,y1) to (x2,y2)
int qb(int x1, int y1, int x2, int y2) {
  if (x1 > x2 || y1 > y2)
    return 0;
  return b[x2][y2] - b[x1 - 1][y2] - b[x2][y1 - 1] + b[x1 - 1][y1 - 1];
}

void solve() {
  cin >> n;
  ans = 0;
  for (int i = 1; i <= n; i++) {
    string s;
    cin >> s;
    for (int j = 1; j <= n; j++)
      a[i][j] = b[i][j] = s[j - 1] - '0';
  }
  // Compute prefix sums for 2D range queries
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      b[i][j] += b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1];
  memset(f, 0, sizeof f);

  // Preprocessing step: for each subset S, compute valid partitions
  for (int S = 0; S < (1 << n); S++) {
    ti[S].clear();
    for (int l = 1; l <= n; l++)
      for (int r = l; r <= n; r++) {
        int flag = 1, T = S;
        for (int x = l; x <= r; x++) {
          if (S >> (x - 1) & 1) {
            flag = 0;
            break;
          }
          T ^= 1 << (x - 1);
        }
        if (flag)
          ti[S].push_back({l, r, T});
      }
  }

  // Preprocessing step: for each interval [l,r], compute subset S such that all
  // selected stars are within [l,r] in terms of rows
  for (int l = 1; l <= n; l++)
    for (int r = l; r <= n; r++) {
      ts[l][r].clear();
      for (int S = 0; S < (1 << n); S++) {
        int flag = 1;
        for (int x = 1; x <= n; x++)
          if (S >> (x - 1) & 1)
            flag &= x >= l && x <= r;
        if (flag)
          ts[l][r].push_back(S);
      }
    }

  // Main DP recursion: traverse from right to left (l from n downto 1)
  for (int l = n; l >= 1; l--) {
    memset(g, 0, sizeof g);
    memset(h, 0, sizeof h);
    g[l - 1][0] = 1;
    for (int r = l; r <= n; r++) {
      // Copy previous values
      memcpy(g[r], g[r - 1], sizeof g[r]);
      memcpy(h[r], h[r - 1], sizeof h[r]);

      // Process segments [z, r] from r down to l+1
      for (int z = r; z > l; z--) {
        for (int S = 0; S < (1 << n); S++)
          if (g[z - 1][S]) {
            // Iterate over valid partitions of current subset S
            for (auto [p, q, T] : ti[S]) {
              add(g[r][T], 1ll * g[z - 1][S] * f[z][r][p][q] % mod);
              add(h[r][T],
                  1ll * addv(g[z - 1][S], h[z - 1][S]) * f[z][r][p][q] % mod);
            }
          }
      }

      // Compute f[l][r][x][y] for all x,y such that star at x,y is in [l,r] in rows
      for (int x = n; x >= 1; x--)
        for (int y = x; y <= n; y++) {
          int &res = f[l][r][x][y];
          // Initially assume 2^(number of stars) configurations
          res = pw[qb(l, x, r, y)];

          // Subtract contribution of subsets that are already counted in g/r
          for (auto S : ts[x][y]) {
            sub(res, g[r][S]);
          }
          
          // Update bitmask for column group [x,y]
          int T = 0;
          for (int z = x; z <= y; z++)
            T ^= 1 << (z - 1);
          add(g[r][T], res);
          add(h[r][T], res);
        }
    }
  }

  // Aggregate all results for the final answer
  int ans = 0;
  for (int S = 0; S < (1 << n); S++)
    add(ans, h[n][S]);
  cout << ans << "\n";
}
int main() {
  pw[0] = 1;
  for (int i = 1; i < M; i++)
    pw[i] = 2ll * pw[i - 1] % mod;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/