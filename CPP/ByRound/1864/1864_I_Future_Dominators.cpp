/*
 * Problem URL : https://codeforces.com/contest/1864/problem/I
 * Submit Date : 2025-09-07
 */

// LUOGU_RID: 150494114
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#pragma GCC optimize("Ofast,fast-math")
#pragma GCC target("avx,avx2")
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <algorithm>
#include <set>
#include <stdio.h>
#include <vector>
typedef long long lld;
using namespace std;
const int S = 1010;
const int N = 1100010;
int n, q;
int res[S][S], cur[S][S];
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
int fa[N];
inline int find(int x) {
  for (; x ^ fa[x]; x = fa[x] = fa[fa[x]])
    ;
  return x;
}
inline bool merge(int u, int v) {
  return ((u = find(u)) == (v = find(v))) ? 0 : (fa[v] = u, 1);
}
inline int idx(int x, int y) { return x * (n + 1) + y; }
int col[S][S], sz[N], cnt;
pair<int, int> up[N];
bool g[5][5];
pair<int, int> q1[N], q2[N];
int r1, r2;
int dfn[S][S], idfn;
inline int bfs(int x1, int y1, int x2, int y2) {
  ++idfn;
  q1[1] = make_pair(x1, y1), q2[1] = make_pair(x2, y2);
  r1 = 1, r2 = 1;
  dfn[x1][y1] = dfn[x2][y2] = idfn;
  for (int i = 1;; ++i) {
    if (i > r1 || i > r2)
      return i > r1 ? 2 : 1;
    int x = q1[i].first, y = q1[i].second;
    for (int d = 0; d < 4; ++d) {
      int nx = x + dx[d], ny = y + dy[d];
      if (col[nx][ny] != -1 && dfn[nx][ny] != idfn)
        dfn[nx][ny] = idfn, q1[++r1] = make_pair(nx, ny);
    }
    x = q2[i].first, y = q2[i].second;
    for (int d = 0; d < 4; ++d) {
      int nx = x + dx[d], ny = y + dy[d];
      if (col[nx][ny] != -1 && dfn[nx][ny] != idfn)
        dfn[nx][ny] = idfn, q2[++r2] = make_pair(nx, ny);
    }
  }
}
pair<int, int> pos;
inline bool diff(int u, int v) {
  if (u > v)
    swap(u, v);
  for (int i = 0; i < u; ++i)
    for (int j = u; j < v; ++j)
      if (g[i][j])
        return 1;
  for (int i = u; i < v; ++i)
    for (int j = v; j < 4; ++j)
      if (g[i][j])
        return 1;
  return 0;
};
inline bool check(int u, const vector<int> &o) {
  for (int x : o)
    if (!diff(x, u))
      return 0;
  return 1;
};
int main() {
  int T;
  scanf("%d", &T);
  for (; T--;) {
    scanf("%d%d", &n, &q);
    for (int i = (n + 1) * (n + 1); ~i; --i)
      fa[i] = i;
    for (int i = 0; i < n; ++i) {
      merge(idx(i, 0), idx(i + 1, 0));
      merge(idx(i, n), idx(i + 1, n));
      merge(idx(0, i), idx(0, i + 1));
      merge(idx(n, i), idx(n, i + 1));
    }
    sz[0] = n * n, cnt = 0, up[0] = make_pair(0, 0);
    for (int i = 0; i <= n + 1; ++i)
      for (int j = 0; j <= n + 1; ++j) {
        res[i][j] = 0;
        if (i >= 1 && i <= n && j >= 1 && j <= n)
          col[i][j] = 0;
        else
          col[i][j] = -1;
      }
    int lst = 0, x, y;
    for (; q--;) {
      scanf("%d%d", &x, &y);
      x ^= lst, y ^= lst;
      int c = col[x][y];
      --sz[c];
      col[x][y] = -1;
      vector<int> cx = {x, x - 1, x - 1, x};
      vector<int> cy = {y, y, y - 1, y - 1};
      for (int i = 0; i < 4; ++i)
        for (int j = i + 1; j < 4; ++j)
          g[i][j] = (find(idx(cx[i], cy[i])) == find(idx(cx[j], cy[j])));
      vector<int> o;
      for (int ii = 0; ii < 4; ++ii) {
        int nx = x + dx[ii], ny = y + dy[ii];
        if (col[nx][ny] != -1 && check(ii, o))
          o.push_back(ii);
      }
      vector<int> cols;
      cols.push_back(c);
      int mx = -1;
      for (int u : o) {
        if (mx == -1) {
          mx = u;
          continue;
        }
        int op = bfs(x + dx[u], y + dy[u], x + dx[mx], y + dy[mx]);
        vector<pair<int, int>> ops;
        if (op == 1)
          for (int i = 1; i <= r2; ++i)
            ops.push_back(q2[i]);
        else
          for (int i = 1; i <= r1; ++i)
            ops.push_back(q1[i]);
        ++cnt, up[cnt] = up[c];
        sz[c] -= ops.size();
        sz[cnt] = ops.size();
        for (int i = 0; i < ops.size(); ++i)
          col[ops[i].first][ops[i].second] = cnt;
        cols.push_back(cnt);
        mx = (op == 1 ? u : mx);
      }
      set<int> st;
      if (up[c] != make_pair(0, 0))
        for (int d = 0; d < 4; ++d) {
          int x = up[c].first + dx[d], y = up[c].second + dy[d];
          if (col[x][y] != -1)
            st.insert(col[x][y]);
        }
      int mxsz = 0, bad = 0;
      pair<int, int> upc = up[c];
      for (int u : cols) {
        if (!st.count(u))
          up[u] = make_pair(x, y), bad += sz[u];
        mxsz = max(mxsz, sz[u]);
      }
      if (upc == make_pair(0, 0)) {
        if (bad)
          pos = make_pair(x, y);
        res[x][y] = mxsz + 1, cur[x][y] = bad + 1;
      } else {
        cur[x][y] = cur[upc.first][upc.second];
        res[x][y] = cur[x][y] - bad;
        cur[upc.first][upc.second] -= bad + 1;
      }
      if (pos != make_pair(0, 0)) {
        int x = pos.first, y = pos.second;
        pair<int, int> mxp = make_pair(-1, -1), mxp2 = make_pair(-1, -1);
        for (int d = 0; d < 4; ++d) {
          int nx = x + dx[d], ny = y + dy[d], nc = col[nx][ny];
          if (nc != -1) {
            if (nc == mxp.second || nc == mxp2.second)
              continue;
            pair<int, int> tmp = make_pair(sz[nc], nc);
            if (tmp > mxp)
              mxp2 = mxp, mxp = tmp;
            else if (tmp > mxp2)
              mxp2 = tmp;
          }
        }
        if (mxp.second >= 0 && (mxp2.second < 0 || mxp2.first != mxp.first))
          up[mxp.second] = pos = make_pair(0, 0);
      }
      for (int i = 0; i < 4; ++i)
        merge(idx(x, y), idx(cx[i], cy[i]));
      lst = res[x][y];
      printf("%d ", lst);
    }
    puts("");
  }
}
