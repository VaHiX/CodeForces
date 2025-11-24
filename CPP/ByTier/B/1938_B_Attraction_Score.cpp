// Problem: CF 1938 B - Attraction Score
// https://codeforces.com/contest/1938/problem/B

/*
 * Purpose: Find the maximum attraction score among all possible non-empty subsets of cities
 *          in a graph with weighted edges, where the score includes attraction points from 
 *          connected cities and penalizes disconnected pairs.
 *
 * Algorithm: 
 * - The code uses a combination of geometric analysis (cross products) and graph traversal
 *   to evaluate potential subsets and compute optimal attraction scores.
 * - It processes edges in a specific order, maintaining maximum attraction values for each node.
 * - Cross products are used to determine orientation of points and identify potential triangle
 *   configurations that contribute to the score.
 * - The solution considers both direct edge weights and combinations involving up to three edges.
 * 
 * Time Complexity: O(m^2) in worst case due to nested iterations over edges,
 *                  but optimized in practice with careful data structures.
 * Space Complexity: O(n + m) for storing graph data, coordinates, and auxiliary arrays.
 */

#include <algorithm>
#include <iostream>
#include <map>
#include <utility>

#pragma GCC optimize("O2")
#define ll long long
#define pb emplace_back
#define mp make_pair
#define orz 1000000007
#define fi first
#define se second
using namespace std;
int n, m, x[300005], y[300005], z[300005];
int ans, d[100005], l[100005], t[300005], I[300005], w[300005], u[300005];
int mx[300005][2];
pair<ll, int> fmx[300005], fmn[300005];
int fx[300005], fn[300005];
pair<int, int> p[100005];
map<int, int> M[100005];
void U(int x, int y) {
  if (y > mx[x][0])
    mx[x][1] = mx[x][0], mx[x][0] = y;
  else if (y > mx[x][1])
    mx[x][1] = y;
}
void u2(int i, int z, int _) {
  int X = x[i], Y = y[i];
  pair<int, int> p1, p2;
  p1 = mp(p[Y].fi - p[X].fi, p[Y].se - p[X].se);
  p2 = mp(p[z].fi - p[Y].fi, p[z].se - p[Y].se);
  ll o = p1.fi * 1ll * p2.se - p1.se * 1ll * p2.fi;
  if (o > fmx[i].fi)
    fmx[i] = mp(o, z), fx[i] = _;
  if (o < fmn[i].fi)
    fmn[i] = mp(o, z), fn[i] = _;
}
ll dis(int x, int y) {
  ll X = p[x].fi - p[y].fi, Y = p[x].se - p[y].se;
  return X * 1ll * X + Y * 1ll * Y;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    cin >> p[i].fi >> p[i].se;
  for (int i = 1; i <= m; ++i)
    cin >> x[i] >> y[i] >> z[i], ans = max(ans, z[i]), ++d[x[i]], ++d[y[i]],
                                 M[x[i]][y[i]] = i, M[y[i]][x[i]] = i;
  for (int i = 1; i <= m; ++i) {
    if (mp(d[x[i]], x[i]) > mp(d[y[i]], y[i]))
      swap(x[i], y[i]);
    ++l[x[i]];
  }
  for (int i = 1; i <= m; ++i)
    mx[i][0] = mx[i][1] = -1;
  for (int i = 1; i <= n; ++i)
    l[i + 1] += l[i];
  for (int i = 1; i <= m; ++i) {
    t[l[x[i]]] = y[i];
    I[l[x[i]]] = i;
    w[l[x[i]]--] = z[i];
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = l[i + 1]; j != l[i]; --j)
      u[t[j]] = I[j];
    for (int j = l[i + 1]; j != l[i]; --j) {
      int o = t[j];
      for (int k = l[o + 1]; k != l[o]; --k) {
        if (u[t[k]]) {
          ans = max(ans, w[j] + w[k] + z[u[t[k]]]);
          U(I[j], w[k] + z[u[t[k]]]);
          U(I[k], w[j] + z[u[t[k]]]);
          U(u[t[k]], w[j] + w[k]);
          u2(I[j], t[k], w[k] + z[u[t[k]]]);
          u2(I[k], i, w[j] + z[u[t[k]]]);
          u2(u[t[k]], o, w[j] + w[k]);
        }
      }
    }
    for (int j = l[i + 1]; j != l[i]; --j)
      u[t[j]] = 0;
  }
  for (int i = 1; i <= m; ++i)
    if (mx[i][1] != -1)
      ans = max(ans, z[i] + mx[i][0] + mx[i][1] - 1000000);
  for (int i = 1; i <= m; ++i)
    if (fmx[i].se && fmn[i].se) {
      int o = M[fmx[i].se][fmn[i].se];
      if (o) {
        int bas = z[i] + fx[i] + fn[i] + z[o];
        int X, Y;
        if (dis(x[i], fmn[i].se) > dis(y[i], fmn[i].se))
          X = x[i], Y = y[i];
        else
          X = y[i], Y = x[i];
        ans = max(ans, bas);
        bas -= 1000000;
        int ix = M[X][fmx[i].se];
        int in = M[X][fmn[i].se];
        if (fmx[ix].se == fmx[in].se && fmx[ix].se != Y && fmx[ix].se != 0) {
          int Z = fmx[ix].se;
          if (M[X].count(Z))
            ans = max(ans, bas + fx[ix] + fx[in] - z[M[X][Z]]);
        }
        if (fmx[ix].se == fmn[in].se && fmx[ix].se != Y && fmx[ix].se != 0) {
          int Z = fmx[ix].se;
          if (M[X].count(Z))
            ans = max(ans, bas + fx[ix] + fn[in] - z[M[X][Z]]);
        }
        if (fmn[ix].se == fmx[in].se && fmn[ix].se != Y && fmn[ix].se != 0) {
          int Z = fmn[ix].se;
          if (M[X].count(Z))
            ans = max(ans, bas + fn[ix] + fx[in] - z[M[X][Z]]);
        }
        if (fmn[ix].se == fmn[in].se && fmn[ix].se != Y && fmn[ix].se != 0) {
          int Z = fmn[ix].se;
          if (M[X].count(Z))
            ans = max(ans, bas + fn[ix] + fn[in] - z[M[X][Z]]);
        }
      }
    }
  cout << ans << '\n';
  return 0;
}


// https://github.com/VaHiX/CodeForces/