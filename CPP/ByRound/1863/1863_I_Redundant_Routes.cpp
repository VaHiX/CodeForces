/*
 * Problem URL : https://codeforces.com/contest/1863/problem/I
 * Submit Date : 2025-09-07
 */

#pragma GCC target("avx")
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stdint.h>
#include <unordered_map>
#include <vector>
using namespace std;
const int maxn = 3005;
int n, rt, vis[maxn * maxn], hj[maxn * maxn][2];
vector<int> tree[maxn], ntr[maxn * maxn];
struct bcj {
  int fa[maxn * maxn], siz[maxn * maxn];
  void clear() {
    for (int i = 1; i <= n * n; ++i)
      fa[i] = i, siz[i] = 1;
  }
  int getf(int x) {
    if (fa[x] == x)
      return x;
    return fa[x] = getf(fa[x]);
  }
  void Merge(int x, int y) {
    x = getf(x);
    y = getf(y);
    if (x != y) {
      if (siz[x] > siz[y])
        swap(x, y);
      fa[x] = y;
      siz[y] += siz[x];
      siz[x] = 0;
    }
  }
} t1;
int gid(int x, int y) {
  if (x > y)
    swap(x, y);
  return (x - 1) * n + y;
}
void dfs(int root, int s, int fa) {
  if (s != root && fa != root) {
    int t1 = gid(root, s), t2 = gid(root, fa);
    if (hj[t1][0])
      hj[t1][1] = t2;
    else
      hj[t1][0] = t2;
  }
  for (int j = 0; j < tree[s].size(); ++j) {
    int s_ = tree[s][j];
    if (s_ != fa)
      dfs(root, s_, s);
  }
}
int dfs_(int s) {
  vis[s] = 1;
  int res = 0;
  for (int j = 0; j < ntr[s].size(); ++j) {
    int s_ = ntr[s][j];
    if (!vis[s_])
      res += dfs_(s_);
  }
  res = max(res, t1.siz[s]);
  return res;
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n;
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    rt = gid(u, v);
    tree[u].push_back(v);
    tree[v].push_back(u);
  }
  t1.clear();
  for (int i = 1; i <= n; ++i)
    dfs(i, i, 0);
  for (int i = 1; i <= n; ++i)
    for (int j = i + 1; j <= n; ++j) {
      int id = (i - 1) * n + j;
      if (hj[id][0])
        t1.Merge(hj[id][0], hj[id][1]);
    }
  for (int i = 1; i <= n; ++i)
    for (int j = i + 1; j <= n; ++j) {
      int id = (i - 1) * n + j;
      if (t1.fa[id] == id && hj[id][0])
        ntr[t1.getf(hj[id][0])].push_back(id);
    }
  rt = t1.getf(rt);
  cout << dfs_(rt);
  return 0;
}