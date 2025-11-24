// Problem: CF 533 A - Berland Miners
// https://codeforces.com/contest/533/problem/A

/*
 * Problem: Berland Miners
 * 
 * Algorithm: 
 * - The problem involves distributing miners into caves of a tree structure such that 
 *   each miner can stand comfortably (miner height <= cave ceiling) and no miner has to stoop 
 *   on their path from entrance (node 1) to their assigned cave.
 * - Key insight: For a path from root to a node, a miner must be able to stand 
 *   in every cave along the path. That means we must ensure that in a path from root to 
 *   the node, each node's ceiling is >= miner's height.
 * - The tree is traversed using DFS. During DFS, we track the minimum ceiling (mi) 
 *   and second minimum ceiling (cmi) for each node considering its subtree.
 * - Then we sort nodes by min ceiling to determine possible assignments.
 * - Using a two-pointer technique, we determine if one cave's ceiling can be raised 
 *   to make all miners happy.
 * 
 * Time Complexity: O(n log n + m log m) where n is number of caves, m is number of miners.
 * Space Complexity: O(n + m) for storing graph, miner heights, and DFS info.
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <functional>
#include <iostream>
#include <utility>

using namespace std;
typedef long long lint;
typedef long double louble;
template <typename T1, typename T2> inline T1 max(T1 a, T2 b) {
  return a < b ? b : a;
}
template <typename T1, typename T2> inline T1 min(T1 a, T2 b) {
  return a < b ? a : b;
}
const char lf = '\n';
namespace ae86 {
const int bufl = 1 << 15;
char buf[bufl], *s = buf, *t = buf;
inline int fetch() {
  if (s == t) {
    t = (s = buf) + fread(buf, 1, bufl, stdin);
    if (s == t)
      return EOF;
  }
  return *s++;
}
inline int ty() {
  int a = 0;
  int b = 1, c = fetch();
  while (!isdigit(c))
    b ^= c == '-', c = fetch();
  while (isdigit(c))
    a = a * 10 + c - 48, c = fetch();
  return b ? a : -a;
}
} // namespace ae86
using ae86::ty;
const int _ = 500007, __ = _ << 1;
int to[__], ne[__], he[_] = {0}, ecnt = 1;
inline void adde(int a, int b) {
  to[++ecnt] = b, ne[ecnt] = he[a], he[a] = ecnt;
}
inline void addde(int a, int b) { adde(a, b), adde(b, a); }
int n, m, hig[_], lim[_];
pair<int, int> fk[_];
void dfs(int x, int ff, int mi, int cmi) {
  if (lim[x] < lim[mi])
    cmi = mi, mi = x;
  else if (lim[x] < lim[cmi])
    cmi = x;
  fk[x] = make_pair(mi, cmi);
  for (int i = he[x]; i; i = ne[i]) {
    int b = to[i];
    if (b == ff)
      continue;
    dfs(b, x, mi, cmi);
  }
}
int ps[_] = {0}, lps = 0;
void finding(int l, int r, int now) {
  int ans = 0;
  for (int i = 1; i <= r - l + 1; i++) {
    int temp = 0;
    if (i <= lps)
      temp = ps[i];
    else if (now + i - lps - 1 <= m)
      temp = hig[now + i - lps - 1];
    ans = max(ans, temp - lim[fk[l + i - 1].first]);
    if (temp > lim[fk[l + i - 1].second])
      return;
  }
  cout << ans << lf;
  exit(0);
}
int main() {
  ios::sync_with_stdio(0), cout.tie(nullptr);
  n = ty();
  for (int i = 1; i <= n; i++)
    lim[i] = ty();
  for (int i = 1, a, b; i < n; i++)
    a = ty(), b = ty(), addde(a, b);
  m = ty();
  for (int i = 1; i <= m; i++)
    hig[i] = ty();
  sort(hig + 1, hig + m + 1, greater<int>());
  lim[0] = 2e9, dfs(1, 0, 0, 0);
  sort(fk + 1, fk + n + 1, [](pair<int, int> a, pair<int, int> b) {
    if (lim[a.first] != lim[b.first])
      return lim[a.first] > lim[b.first];
    if (a.first != b.first)
      return a.first < b.first;
    return lim[a.second] > lim[b.second];
  });
  int las = 0;
  for (int i = 1; i <= m; i++)
    if (lim[fk[i].first] < hig[i])
      las = i;
  for (int i = 1, j = 1, now = 1; i <= n; i = j + 1) {
    j = i;
    while (j < n && fk[j + 1].first == fk[i].first)
      j++;
    if (lps <= j - i + 1 && j >= las)
      finding(i, j, now);
    for (int k = i; k <= j; k++) {
      while (now <= m && hig[now] > lim[fk[k].first])
        ps[++lps] = hig[now], now++;
      now++;
    }
  }
  cout << -1 << lf;
  return 0;
}


// https://github.com/VaHiX/CodeForces/