/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
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

const int N = 2e5 + 5;
int n, m;
int a[N], x[N];

struct Trie {
  int ch[N << 5][2], tot, sz[N << 5];
  void ins(int x) {
    int p = 0;
    for (int i = 29; i >= 0; --i) {
      int c = (x >> i) & 1;
      if (!ch[p][c]) {
        ch[p][c] = ++tot;
      }
      p = ch[p][c];
      ++sz[p];
    }
    // cout << sz[p] << '\n';
  }
  int qry(int x, int lim) {
    int p = 0, res = 0;
    for (int i = 29; i >= 0; --i) {
      int l = (lim >> i) & 1;
      int c = (x >> i) & 1;
      if (l == 0) {
        p = ch[p][c];
      } else {
        res += sz[ch[p][c]];
        p = ch[p][c ^ 1];
      }
      if (p == 0) {
        return res;
      }
      // cout << l << ' ' << c << '\n';
    }
    // cout << p << '\n';
    return res + sz[p];
  }
} tr;

int main() {
#ifndef ONLINE_JUDGE
  assert(freopen("test.in", "r", stdin));
  assert(freopen("test.out", "w", stdout));
#endif

  n = read(), m = read();
  for (int i = 1; i <= n; ++i) {
    a[i] = read();
  }
  for (int i = 1; i <= m; ++i) {
    x[i] = read();
  }
  sort(a + 1, a + n + 1);
  int mn = a[1] ^ a[2];
  for (int i = 2; i < n; ++i) {
    mn = min(mn, a[i] ^ a[i + 1]);
  }
  ll ans = 0;
  for (int i = 1; i <= m; ++i) {
    ans += tr.qry(x[i], mn);
    tr.ins(x[i]);
  }
  write(ans);

  return 0;
}