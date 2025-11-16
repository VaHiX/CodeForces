// Problem: CF 1879 F - Last Man Standing
// https://codeforces.com/contest/1879/problem/F

/*
 * Problem: F. Last Man Standing
 * Purpose: Find the maximum points each hero can earn by choosing optimal damage value x
 *          for different game scenarios where heroes die based on health and armor.
 *
 * Algorithm:
 * - For each possible damage value x from 1 to infinity:
 *   - Simulate the game with x damage per round
 *   - Track which heroes are alive and when they die
 *   - Calculate the points based on the last hero standing alone in a round
 * - Optimization using Sparse Table for range maximum queries
 * - Preprocessing to group heroes by their armor values
 * - Time Complexity: O(n log n + V * (n/V) * log n) where V is maximum armor value
 * - Space Complexity: O(n * log n)
 *
 * Techniques:
 * - Sparse Table for Range Maximum Query (RMQ)
 * - Preprocessing by armor values
 * - Binary search ideas using sorted groups
 */

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <array>
#include <string>

#define arr(x) array<ll, x>
#define INF 0x3f3f3f3f
#define scanf(...) assert(scanf(__VA_ARGS__))
using namespace std;
using ll = long long;
namespace FastIO {
static char buf[100000], *p1 = buf, *p2 = buf;
#define gc                                                                     \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2)      \
       ? EOF                                                                   \
       : *p1++)
inline ll read() {
  ll res = 0;
  int w = 0, c = gc;
  for (; !isdigit(c); c = gc) {
    ((c == '-') && (w = 1));
  }
  for (; isdigit(c); c = gc) {
    res = (res << 1) + (res << 3) + (c ^ 48);
  }
  return (w ? -res : res);
}
inline char readC() {
  int c = gc;
  while (c == '\n' || c == '\r' || c == ' ') {
    c = gc;
  }
  return c;
}
inline string readS() {
  string res = "";
  int w = 0;
  char c = gc;
  for (; (c == '\n' || c == '\r' || c == ' ' || c == EOF); c = gc)
    ;
  for (; !(c == '\n' || c == '\r' || c == ' ' || c == EOF); c = gc) {
    res += c;
  }
  return res;
}
inline double readF() {
  double res = 0, tmp = 0.1;
  int w = 0;
  char c = gc;
  for (; !isdigit(c); c = gc) {
    ((c == '-') && (w = 1));
  }
  for (; isdigit(c); c = gc) {
    res = (res * 10) + (c ^ 48);
  }
  if (c == '.') {
    c = gc;
    for (; isdigit(c); c = gc) {
      res = res + tmp * (c ^ 48);
      tmp *= 0.1;
    }
  }
  return (w ? -res : res);
}
inline void write(ll x, char c = '\n') {
  ((x < 0) && (putchar('-'), x *= -1));
  static int sta[50], top = 0;
  do {
    sta[top++] = x % 10, x /= 10;
  } while (x);
  while (top) {
    putchar(sta[--top] + 48);
  }
  putchar(c);
}
}; // namespace FastIO
using namespace FastIO;
const int N = 2e5 + 5, M = 20;
int n, V;
struct node {
  int x, y, id;
} a[N];
ll ans[N];
int nxt[N], c[N], b[N];
struct Data {
  int x, y;
  Data(int X = 0, int Y = 0) { x = X, y = Y; }
  Data operator+(Data b) {
    if (a[x].x > a[b.x].x) {
      return Data(x, max(a[b.x].x, y));
    }
    if (a[x].x == a[b.x].x) {
      return Data(x, max(b.y, y));
    }
    return Data(b.x, max(a[x].x, b.y));
  }
} st[M][N];
void init() {
  for (int i = 1; i <= n; ++i) {
    st[0][i] = Data(i, 0);
  }
  for (int i = 1; i < M; ++i) {
    for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
      st[i][j] = st[i - 1][j] + st[i - 1][j + (1 << i - 1)];
    }
  }
}
Data qry(int l, int r) {
  int t = __lg(r - l + 1);
  return st[t][l] + st[t][r - (1 << t) + 1];
}
arr(3) merge(arr(3) x, arr(3) y) {
  if (x[0] > y[0]) {
    return {x[0], max(y[0], x[1]), x[2]};
  }
  return {y[0], max(x[0], y[1]), y[2]};
}
void solve() {
  n = read(), V = 0;
  for (int i = 1; i <= n; ++i) {
    a[i].x = read(), a[i].id = i;
    ans[i] = 0;
    c[a[i].x] = n + 1;
  }
  for (int i = 1; i <= n; ++i) {
    a[i].y = read();
    V = max(a[i].y, V);
  }
  memset(b, 0, sizeof(b));
  sort(a + 1, a + n + 1, [](node x, node y) { return (x.y < y.y); });
  init();
  for (int i = n; i >= 1; --i) {
    ++b[a[i].y];
    nxt[i] = c[a[i].x];
    c[a[i].x] = i;
  }
  for (int i = 1; i <= V; ++i) {
    b[i] += b[i - 1];
  }
  for (int i = 1; i <= V; ++i) {
    int lst = 1, cur = 1;
    arr(3) res = {-1, -1, 0};
    for (int j = 0; j * i <= V; ++j) {
      cur = b[min(V, (j + 1) * i)] + 1;
      if (lst < cur) {
        Data tmp = qry(lst, cur - 1);
        int pos = tmp.x, v = tmp.y;
        if (nxt[pos] < cur) {
          res =
              merge(res, {(ll)a[pos].x * (j + 1), (ll)a[pos].x * (j + 1), pos});
        } else {
          res = merge(res, {(ll)a[pos].x * (j + 1), (ll)v * (j + 1), pos});
        }
        lst = cur;
      }
    }
    ans[a[res[2]].id] = max(ans[a[res[2]].id], res[0] - res[1]);
  }
  for (int i = 1; i <= n; ++i) {
    write(ans[i], ' ');
  }
  puts("");
}
int main() {
#ifdef LOCAL
  assert(freopen("test.in", "r", stdin));
  assert(freopen("test.out", "w", stdout));
#endif
  int T = read();
  while (T--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/