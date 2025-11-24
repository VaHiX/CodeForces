// Problem: CF 1891 F - A Growing Tree
// https://codeforces.com/contest/1891/problem/F

/*
 * Problem: F. A Growing Tree
 * Algorithms/Techniques: 
 *   - Tree DFS traversal with Euler tour technique
 *   - Binary Indexed Tree (Fenwick Tree) for range updates and point queries
 *   - Offline processing of queries
 *   
 * Time Complexity: O(Q log Q) per test case, where Q is the number of queries.
 * Space Complexity: O(Q) for storing the tree structure and modification events.
 *
 * The solution uses Euler tour to convert subtree updates into range updates,
 * then applies a Binary Indexed Tree (Fenwick Tree) for efficient range updates
 * and point queries.
 */

#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

template <class T> inline int qlog(T a) {
  double x = a;
  return ((*(long long *)&x) >> 52 & 2047) - 1023;
}
#define fopen LilyWhite
void fopen(const char *s) {
  static char filename[32];
  sprintf(filename, "%s.in", s);
  freopen(filename, "r", stdin);
  sprintf(filename, "%s.out", s);
  freopen(filename, "w", stdout);
}
typedef unsigned int u32;
typedef long long ll;
typedef unsigned long long u64;
#define Please return
#define AC 0
#define cin Mizuhashi
#define cout Parsee
#define endl '\n'
class Reader {
private:
  static const int BUF_SIZE = 1 << 22;
  char BUF_R[BUF_SIZE], *csy1, *csy2;
#ifndef _LOCAL_RUNNING
#define GC                                                                     \
  (csy1 == csy2 && (csy2 = (csy1 = BUF_R) + fread(BUF_R, 1, BUF_SIZE, stdin),  \
                    csy1 == csy2)                                              \
       ? EOF                                                                   \
       : *csy1++)
#else
  char cur;
#define GC (cur = getchar())
#endif
#define IL inline
public:
  IL bool eof() {
#ifndef _LOCAL_RUNNING
    return csy1 == csy2 &&
           (csy2 = (csy1 = BUF_R) + fread(BUF_R, 1, BUF_SIZE, stdin),
            csy1 == csy2);
#else
    return cur == EOF;
#endif
  }
  template <class Ty> IL Reader &operator>>(Ty &t) {
    int u = 0;
    char c = GC;
    for (t = 0; c < 48 || c > 57; c = GC)
      if (c == EOF)
        break;
      else if (c == '-')
        u = 1;
    for (; c > 47 && c < 58; c = GC)
      t = t * 10 + (c ^ 48);
    t = u ? -t : t;
    return *this;
  }
  IL Reader &operator>>(double &t) {
    int tmp, u = 0;
    char c = GC;
    for (tmp = 0; c < 48 || c > 57; c = GC)
      if (c == EOF)
        break;
      else if (c == '-')
        u = 1;
    for (; c > 47 && c < 58; c = GC)
      tmp = tmp * 10 + (c ^ 48);
    t = (tmp = u ? -tmp : tmp);
    if (c == '.') {
      double x = 1;
      for (c = GC; c > 47 && c < 58; c = GC)
        t += (x /= 10) * (c ^ 48);
    }
    return *this;
  }
  IL Reader &operator>>(char *s) {
    char c = GC;
    for (*s = 0; c < 33; c = GC)
      if (c == EOF)
        return *this;
    for (; c > 32; c = GC)
      *s++ = c;
    *s = 0;
    return *this;
  }
  IL Reader &operator>>(char &c) {
    for (c = GC; c < 33; c = GC)
      if (c == EOF)
        return *this;
    return *this;
  }
} cin;
class Writer {
private:
  static const int BUF_SIZE = 1 << 22;
  char BUF_W[BUF_SIZE], *csy;
#define IL inline
  inline void WC(const char c) {
    if (csy - BUF_W == BUF_SIZE)
      fwrite(BUF_W, 1, BUF_SIZE, stdout), csy = BUF_W;
    *csy++ = c;
  }

public:
  Writer() : csy(BUF_W) {}
  ~Writer() { fwrite(BUF_W, 1, csy - BUF_W, stdout); }
  IL void flush() {
    fwrite(BUF_W, 1, csy - BUF_W, stdout);
    csy = BUF_W;
  }
  template <class Ty> IL Writer &operator<<(Ty x) {
    static int sta[32], top;
    if (x < 0) {
      WC('-');
      do
        sta[top++] = -(x % 10);
      while (x /= 10);
    } else
      do
        sta[top++] = x % 10;
      while (x /= 10);
    while (top)
      WC(sta[--top] ^ 48);
    return *this;
  }
  IL Writer &operator<<(const char &c) {
    WC(c);
    return *this;
  }
  IL Writer &operator<<(const char *s) {
    while (*s)
      WC(*s++);
    return *this;
  }
} cout;
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int MAX_N = 500000 + 5;
const int MAX_M = 1 << 20;
int N, M, Q, son[MAX_N], bro[MAX_N], dfsn[MAX_N][2], idfsn[MAX_N], Tm;
struct Modify {
  int u, val, ti;
} mdf[MAX_N];
ll c[MAX_N], ans[MAX_N];
vector<pii> mdf1[MAX_N], mdf2[MAX_N];
void modify(int l, int r, int v) {
  r++;
  while (l < r) {
    c[l] += v;
    l += l & -l;
  }
  while (r <= Q && r < l) {
    c[r] -= v;
    r += r & -r;
  }
}
ll query(int x) {
  ll res = 0;
  for (int i = x; i > 0; i -= i & -i)
    res += c[i];
  return res;
}
void dfs(int u) {
  dfsn[u][0] = ++Tm;
  idfsn[Tm] = u;
  for (int v = son[u]; v; v = bro[v]) {
    dfs(v);
  }
  dfsn[u][1] = Tm;
}
void solve() {
  N = 1;
  M = 0;
  son[1] = 0;
  Tm = 0;
  cin >> Q;
  for (int i = 1; i <= Q; i++) {
    int ty, u, x;
    cin >> ty >> u;
    if (ty == 1) {
      son[++N] = 0;
      bro[N] = son[u];
      son[u] = N;
    } else {
      cin >> x;
      mdf[++M] = {u, x, N};
    }
  }
  dfs(1);
  for (int i = 1; i <= N; i++) {
    mdf1[i].clear();
    mdf2[i].clear();
  }
  for (int i = 1; i <= M; i++) {
    mdf1[dfsn[mdf[i].u][0]].emplace_back(mdf[i].val, mdf[i].ti);
    mdf2[dfsn[mdf[i].u][1]].emplace_back(mdf[i].val, mdf[i].ti);
  }
  for (int i = 1; i <= N; i++) {
    for (auto [val, ti] : mdf1[i])
      modify(1, ti, val);
    ans[idfsn[i]] = query(idfsn[i]);
    for (auto [val, ti] : mdf2[i])
      modify(1, ti, -val);
  }
  for (int i = 1; i <= N; i++)
    cout << ans[i] << "\n "[i < N];
}
int main() {
  int T = 1;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/