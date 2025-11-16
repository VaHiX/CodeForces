// Problem: CF 1913 E - Matrix Problem
// https://codeforces.com/contest/1913/problem/E

/*
 * Problem: Matrix Problem
 * Algorithm: Minimum Cost Maximum Flow (MinCost MaxFlow)
 * Time Complexity: O((n + m)^2 * (n + m + nm))
 * Space Complexity: O(n + m + nm)
 *
 * This solution uses a minimum cost flow approach to determine the minimum number
 * of operations needed to transform a binary matrix to satisfy given row and column
 * constraints. The approach models the problem as a flow network where:
 * - Each row is connected to each column with an edge of capacity 1 and cost.
 * - Source connects to rows with capacity equal to required ones in that row.
 * - Columns connect to sink with capacity equal to required ones in that column.
 * - Each cell (i,j) has a cost associated with converting 0 to 1 or 1 to 0.
 * 
 * Flow is computed to find minimum cost to achieve the required distribution.
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>

#define rep(i, x, y) for (int i = x; i <= y; i++)
#define dwn(i, x, y) for (int i = x; i >= y; i--)
#define ll long long
using namespace std;
template <typename T> inline void qr(T &x) {
  x = 0;
  int f = 0;
  char s = getchar();
  while (!isdigit(s))
    f |= s == '-', s = getchar();
  while (isdigit(s))
    x = x * 10 + s - 48, s = getchar();
  x = f ? -x : x;
}
int cc = 0, buf[31];
template <typename T> inline void qw(T x) {
  if (x < 0)
    putchar('-'), x = -x;
  do {
    buf[++cc] = int(x % 10);
    x /= 10;
  } while (x);
  while (cc)
    putchar(buf[cc--] + '0');
}
const int N = 110, M = 7e3 + 10;
const int inf = 1e9;
int n, m, a[N][N], hang[N], lie[N];
int tot = 1, hd[N], cur[N], ver[M], nxt[M], w[M], val[M];
int d[N];
bool v[N];
int S, T;
int ans, cost;
void add(int x, int y, int z, int l) {
  tot++;
  w[tot] = z, val[tot] = l;
  ver[tot] = y;
  nxt[tot] = hd[x];
  hd[x] = tot;
}
bool spfa() {
  rep(i, 1, T) d[i] = inf;
  d[T] = 0;
  queue<int> q;
  q.push(T);
  while (q.size()) {
    int x = q.front();
    q.pop();
    v[x] = 0;
    for (int i = hd[x]; i; i = nxt[i]) {
      int y = ver[i];
      if (w[i ^ 1] && d[y] > d[x] - val[i]) {
        d[y] = d[x] - val[i];
        if (!v[y])
          v[y] = 1, q.push(y);
      }
    }
  }
  return d[S] != inf;
}
int findflow(int x, int f) {
  if (x == T)
    return f;
  v[x] = 1;
  int res = f, tt;
  for (int &i = cur[x]; i; i = nxt[i]) {
    int y = ver[i];
    if (!v[y] && w[i] && d[x] == d[y] + val[i]) {
      tt = findflow(y, min(res, w[i]));
      w[i] -= tt, w[i ^ 1] += tt;
      cost += tt * val[i];
      res -= tt;
      if (!res)
        break;
    }
  }
  v[x] = 0;
  return f - res;
}
void solve() {
  qr(n), qr(m);
  rep(i, 1, n) rep(j, 1, m) qr(a[i][j]);
  int t1 = 0, t2 = 0;
  rep(i, 1, n) qr(hang[i]), t1 += hang[i];
  rep(i, 1, m) qr(lie[i]), t2 += lie[i];
  if (t1 != t2) {
    puts("-1");
    return;
  }
  S = n + m + 1, T = S + 1;
  rep(i, 1, n) {
    add(S, i, hang[i], 0);
    add(i, S, 0, 0);
  }
  rep(i, 1, m) {
    add(n + i, T, lie[i], 0);
    add(T, n + i, 0, 0);
  }
  rep(i, 1, n) rep(j, 1, m) {
    if (a[i][j]) {
      cost++;
      add(i, j + n, 1, 0);
      add(j + n, i, 0, 0);
    } else {
      add(i, j + n, 1, 2);
      add(j + n, i, 0, -2);
    }
  }
  while (spfa()) {
    memcpy(cur, hd, sizeof(cur));
    ans += findflow(S, t1);
  }
  if (ans != t1)
    puts("-1");
  else
    qw(cost - ans);
}
int main() {
  int tt;
  tt = 1;
  while (tt--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/