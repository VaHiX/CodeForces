/*
 * Problem URL : https://codeforces.com/problemset/problem/1995/E1
 * Submit Date : 2025-08-13
 */

#include <bits/stdc++.h>
using namespace std;
#define N 200010
typedef long long ll;
int n, a[N];
struct Matrix {
  bool g[2][2];
  friend Matrix operator*(const Matrix &a, const Matrix &b) {
    return (Matrix){{{a.g[0][0] && b.g[0][0] || a.g[0][1] && b.g[1][0],
                      a.g[0][0] && b.g[0][1] || a.g[0][1] && b.g[1][1]},
                     {a.g[1][0] && b.g[0][0] || a.g[1][1] && b.g[1][0],
                      a.g[1][0] && b.g[0][1] || a.g[1][1] && b.g[1][1]}}};
  }
} t[N << 2];
#define ls u << 1
#define rs u << 1 | 1
struct State {
  int p, w, x, y;
};
inline void update(int u) { t[u] = t[ls] * t[rs]; }
void _modify(int u, int L, int R, int p, State z) {
  if (L == R) {
    t[u].g[z.x][z.y] ^= 1;
    return;
  }
  int mid = (L + R) >> 1;
  p <= mid ? _modify(ls, L, mid, p, z) : _modify(rs, mid + 1, R, p, z);
  update(u);
}
void Modify(int p, State z) { _modify(1, 1, n, p, z); }
bool OK() { return t[1].g[0][0] | t[1].g[1][1]; }
void Solve() {
  cin >> n;
  for (int i = 1; i <= n * 2; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= n << 2; ++i) {
    memset(t[i].g, 0, sizeof(t[i].g));
  }
  if (n % 2 == 0) {
    int mx = 0, mn = INT_MAX;
    for (int i = 1; i <= n; i += 2) {
      int x = min(a[i], a[i + n]) + max(a[i + 1], a[i + n + 1]);
      int y = max(a[i], a[i + n]) + min(a[i + 1], a[i + n + 1]);
      mx = max(mx, max(x, y));
      mn = min(mn, min(x, y));
    }
    cout << mx - mn << '\n';
    return;
  }
  vector<State> c;
  for (int i = 1; i <= n; ++i) {
    if (i & 1) {
      if (i == n) {
        c.push_back({i, a[i] + a[i + 1], 0, 0});
        c.push_back({i, a[i + n] + a[i + 1], 1, 0});
        c.push_back({i, a[i] + a[1], 0, 1});
        c.push_back({i, a[i + n] + a[1], 1, 1});
      } else {
        c.push_back({i, a[i] + a[i + 1], 0, 0});
        c.push_back({i, a[i + n] + a[i + 1], 1, 0});
        c.push_back({i, a[i] + a[i + n + 1], 0, 1});
        c.push_back({i, a[i + n] + a[i + n + 1], 1, 1});
      }
    } else {
      c.push_back({i, a[i] + a[i + 1], 1, 1});
      c.push_back({i, a[i + n] + a[i + 1], 0, 1});
      c.push_back({i, a[i] + a[i + n + 1], 1, 0});
      c.push_back({i, a[i + n] + a[i + n + 1], 0, 0});
    }
  }
  sort(c.begin(), c.end(), [&](State a, State b) { return a.w < b.w; });
  int ans = INT_MAX;
  for (int i = 0, j = 0; i < (int)c.size(); ++i) {
    while (j < (int)c.size() && !OK()) {
      Modify(c[j].p, c[j]);
      ++j;
    }
    if (!OK())
      break;
    ans = min(ans, c[j - 1].w - c[i].w);
    Modify(c[i].p, c[i]);
  }
  cout << ans << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--)
    Solve();
  return 0;
}
