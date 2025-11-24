// Problem: CF 1876 G - Clubstep
// https://codeforces.com/contest/1876/problem/G

/*
Algorithm/Techniques: 
- Coordinate compression and offline processing of queries
- Using a monotonic stack to determine the range of influence for each query
- Union-find with path compression to efficiently manage and query cumulative values
- Binary lifting / Segment tree like operations to track min required time
- Preprocessing step to determine which queries are affected by which parts

Time Complexity: O(n * log(n) + q * log(n))
Space Complexity: O(n + q)
*/

#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;
namespace FastRead {
char buf[1000005], *s = buf, *t = buf;
#define gc()                                                                   \
  s == t && (t = (s = buf) + fread(buf, 1, 1000000, stdin), s == t) ? EOF : *s++
template <typename T> inline void Read(T &x) {
  x = 0;
  int f = 0;
  char ch = gc();
  while (ch < '0' || ch > '9')
    f = ch == '-', ch = gc();
  while ('0' <= ch && ch <= '9')
    x = x * 10 + ch - 48, ch = gc();
  f && (x = -x);
}
inline void Read(char *str) {
  char ch = gc();
  while (ch < 32 || ch > 126)
    ch = gc();
  while (32 <= ch && ch <= 126)
    *(str++) = ch, ch = gc();
}
}; // namespace FastRead
using FastRead::Read;
typedef long long LL;
const int N = 3e5 + 5;
int n, m;
int a[N];
vector<pair<pair<int, int>, int>> q0[N];
int sta[N], tt;
vector<int> ql[N];
vector<pair<int, int>> qr[N];
int l[N], r[N], x[N];
int fa[N];
LL ans0[N], dis[N];
LL ans[N];
inline void Work0() {
  for (int i = 1; i <= n; i++) {
    while (tt && a[sta[tt]] >= a[i])
      tt--;
    sta[++tt] = i;
    for (auto &j : q0[i]) {
      int L = 0, R = tt, Mid;
      while (L < R) {
        Mid = (L + R + 1) >> 1;
        if (a[sta[Mid]] >= j.first.second)
          R = Mid - 1;
        else
          L = Mid;
      }
      int p = sta[L];
      if (p < j.first.first)
        continue;
      ql[j.first.first].emplace_back(j.second);
      qr[p].emplace_back(j.first.second, j.second);
    }
  }
}
inline int gfa(int i) {
  if (i == fa[i])
    return i;
  int j = gfa(fa[i]);
  dis[i] += dis[fa[i]];
  return fa[i] = j;
}
inline LL Query(int i) {
  gfa(i);
  return ans0[fa[i]] + dis[i];
}
inline void Add(int i, int j) {
  l[j] = i, r[j] = r[i];
  r[i] = l[r[j]] = j;
}
inline void Remove(int i) {
  l[r[i]] = l[i];
  r[l[i]] = r[i];
}
inline void Merge(int i) {
  dis[i] = ans0[i] - ans0[l[i]];
  fa[i] = l[i];
  Remove(i);
}
inline void Insert(int i) {
  sort(qr[i].begin(), qr[i].end());
  for (int j = l[m + 1], k = (int)qr[i].size() - 1; k >= 0; j = l[j]) {
    while (k >= 0 && x[j] <= qr[i][k].first)
      Add(j, qr[i][k--].second);
  }
}
inline void Modify(LL t, int d) {
  for (int i = l[m + 1], j = m + 1; x[i] > d; j = i, i = l[i]) {
    ans0[i] += (x[i] - d + 1) / 2 * t;
    x[i] = (x[i] + d) / 2;
    if (j <= m && x[i] == x[j])
      Merge(j);
  }
}
inline void Work1() {
  r[0] = r[m + 1] = m + 1;
  for (int i = 0; i <= m + 1; i++)
    fa[i] = i;
  for (int i = n; i >= 1; i--) {
    Insert(i);
    Modify(i, a[i]);
    for (int j : ql[i])
      ans[j] = Query(j);
  }
}
int main() {
  Read(n);
  for (int i = 1; i <= n; i++)
    Read(a[i]);
  Read(m);
  for (int i = 1; i <= m; i++) {
    int l, r;
    Read(l), Read(r), Read(x[i]);
    q0[r].emplace_back(make_pair(l, x[i]), i);
  }
  Work0();
  Work1();
  for (int i = 1; i <= m; i++)
    printf("%lld\n", ans[i]);
  return 0;
}


// https://github.com/VaHiX/CodeForces/