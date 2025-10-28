// Problem: CF 1899 G - Unusual Entertainment
// https://codeforces.com/contest/1899/problem/G

/*
Problem: Unusual Entertainment
Purpose: Given a tree with n vertices and a permutation p, answer queries about whether
         there exists a descendant of vertex x among vertices p[l], p[l+1], ..., p[r].

Algorithms/Techniques:
- Tree DFS traversal to compute entry/exit times for vertices
- Coordinate compression using BIT (Binary Indexed Tree)
- Offline processing of range queries using sweep line technique
- DFS on tree to find descendants

Time Complexity: O((n + q) * log(n)) per test case
Space Complexity: O(n + q) for storing the tree, queries, and auxiliary data structures

*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <utility>
#include <vector>

template <class T> inline int qlog(T a) {
  double x = a;
  return ((*(long long *)&x) >> 52 & 2047) - 1023;
}
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
      t = (t << 1) + (t << 3) + (c ^ 48);
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
      tmp = (tmp << 1) + (tmp << 3) + (c ^ 48);
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
  IL Writer &operator<<(char *s) {
    while (*s)
      WC(*s++);
    return *this;
  }
} cout;
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int MAX_N = 100000 + 5;
int N, Q, y[MAX_N], c[MAX_N];
struct Edge {
  int y, prev;
} e[MAX_N << 1];
int elast[MAX_N], ecnt;
int dfsn[MAX_N][2], Tm;
struct Query {
  int idx, l, r;
  Query(int a = 0, int b = 0, int c = 0) : idx(a), l(b), r(c) {}
};
vector<Query> qry[MAX_N];
int ans[MAX_N];
void Build(int x, int y) {
  ecnt++;
  e[ecnt].y = y;
  e[ecnt].prev = elast[x];
  elast[x] = ecnt;
}
void dfs(int u, int fa) {
  dfsn[u][0] = ++Tm;
  for (int i = elast[u]; i; i = e[i].prev) {
    int v = e[i].y;
    if (v != fa)
      dfs(v, u);
  }
  dfsn[u][1] = Tm;
}
void modify(int x) {
  for (int i = x; i <= N; i += i & -i)
    c[i]++;
}
int query(int l, int r) {
  l--;
  int res = 0;
  while (l < r) {
    res += c[r];
    r -= r & -r;
  }
  while (r < l) {
    res -= c[l];
    l -= l & -l;
  }
  return res;
}
void solve() {
  cin >> N >> Q;
  ecnt = 0;
  Tm = 0;
  memset(c, 0, sizeof(int) * (N + 1));
  memset(ans, 0, sizeof(int) * (Q + 1));
  memset(elast, 0, sizeof(int) * (N + 1));
  for (int i = 1; i < N; i++) {
    int u, v;
    cin >> u >> v;
    Build(u, v);
    Build(v, u);
  }
  dfs(1, 0);
  for (int i = 1; i <= N; i++) {
    qry[i].clear();
    int p;
    cin >> p;
    y[i] = dfsn[p][0];
  }
  for (int i = 1; i <= Q; i++) {
    int x, l, r;
    cin >> l >> r >> x;
    if (l > 1)
      qry[l - 1].emplace_back(-i, dfsn[x][0], dfsn[x][1]);
    qry[r].emplace_back(i, dfsn[x][0], dfsn[x][1]);
  }
  for (int i = 1; i <= N; i++) {
    modify(y[i]);
    for (auto [id, l, r] : qry[i]) {
      if (id < 0)
        ans[-id] -= query(l, r);
      else
        ans[id] += query(l, r);
    }
  }
  for (int i = 1; i <= Q; i++)
    cout << (ans[i] ? "YES\n" : "NO\n");
  cout << endl;
}
int main() {
  int T = 1;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/