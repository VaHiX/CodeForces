// Problem: CF 1955 H - The Most Reckless Defense
// https://codeforces.com/contest/1955/problem/H

/*
 * Problem: H. The Most Reckless Defense
 * 
 * This problem involves finding the maximum base health 'h' for which an enemy can
 * pass through a path in a tower defense game without dying, considering that towers
 * can be upgraded with ranges that increase the enemy's health by 3^r units.
 * 
 * Algorithm/Techniques:
 * - Use Kuhn-Munkres (Hungarian) algorithm for maximum weight bipartite matching
 * - For each possible range r (1 to 12), calculate how many path cells each tower attacks
 * - Assign weights based on (damage * count_of_cells) - 3^r to optimize the health gain
 * - The maximum weight matching gives the optimal assignment of ranges to towers
 * 
 * Time Complexity: O(R^3 * k), where R is max range (12) and k is number of towers
 * Space Complexity: O(R * k), for storing the bipartite graph and matching
 */

#include <assert.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;
using db = double;
constexpr int mod = 998244353;
constexpr int N = 2e5 + 10;
struct KM {
  int n, m;
  vector<vector<ll>> a;
  vector<ll> lx, ly, mind;
  vector<int> px, py, pre;
  vector<bool> used;
  const ll inf = 1e18;
  KM(int _n, int _m) : n(_n), m(_m) {
    assert(n <= m);
    a = vector(n + 1, vector<ll>(m + 1));
    lx = vector<ll>(n + 1);
    ly = vector<ll>(m + 1);
    mind = vector<ll>(m + 1);
    px = vector<int>(n + 1, -1);
    py = vector<int>(m + 1, -1);
    pre = vector<int>(m + 1, -1);
    used = vector<bool>(m + 1);
  }
  void add_edge(int u, int v, ll w) { a[u][v] = max(a[u][v], w); }
  ll solve() {
    for (int i = 1; i <= n; i++) {
      fill(mind.begin(), mind.end(), inf);
      fill(used.begin(), used.end(), false);
      px[i] = 0;
      py[0] = i;
      int y = 0;
      while (true) {
        used[y] = true;
        int x = py[y];
        ll d = inf;
        int yy = -1;
        for (int j = 1; j <= m; j++) {
          if (used[j])
            continue;
          ll cur = lx[x] + ly[j] - a[x][j];
          if (mind[j] > cur) {
            mind[j] = cur;
            pre[j] = y;
          }
          if (d > mind[j])
            d = mind[j], yy = j;
        }
        for (int j = 0; j <= m; j++) {
          if (used[j])
            lx[py[j]] -= d, ly[j] += d;
          else
            mind[j] -= d;
        }
        y = yy;
        if (py[y] == -1)
          break;
      }
      for (; y; y = pre[y]) {
        py[y] = py[pre[y]];
        px[py[y]] = y;
      }
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
      if (px[i] != -1)
        ans += a[i][px[i]];
    }
    return ans;
  }
};
void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  vector enemy(n + 1, vector<bool>(m + 1));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      char ch;
      cin >> ch;
      if (ch == '#')
        enemy[i][j] = true;
    }
  }
  vector<int> p(k + 1);
  vector<pair<int, int>> tower(k + 1);
  for (int i = 1; i <= k; i++) {
    cin >> tower[i].first >> tower[i].second >> p[i];
  }
  constexpr int R = 12;
  KM km(R, max(k, R));
  ll pow3 = 1;
  for (int r = 1; r <= R; r++) {
    pow3 *= 3;
    for (int i = 1; i <= k; i++) {
      auto [x, y] = tower[i];
      int cnt = 0;
      for (int dx = -r; dx <= r; dx++) {
        for (int dy = -r; dy <= r; dy++) {
          if (dx * dx + dy * dy <= r * r) {
            int x2 = x + dx;
            int yy = y + dy;
            if (1 <= x2 && x2 <= n && 1 <= yy && yy <= m) {
              if (enemy[x2][yy])
                cnt++;
            }
          }
        }
      }
      km.add_edge(r, i, p[i] * cnt - pow3);
    }
  }
  cout << km.solve() << "\n";
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tt = 1;
  cin >> tt;
  while (tt--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/