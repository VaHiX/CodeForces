// Problem: CF 1856 E2 - PermuTree (hard version)
// https://codeforces.com/contest/1856/problem/E2

/*
Code Purpose:
This code solves the problem of finding the maximum number of pairs of vertices (u, v) in a tree such that 
a[u] < a[lca(u,v)] < a[v] for some permutation a of 1..n. 
The algorithm uses a tree DP approach, where for each node, it calculates the optimal value of pairs 
that can be formed with its children. It utilizes subset sum optimization and bitset techniques to 
efficiently compute the result.

Time Complexity: O(n log n) - The dfs traversal is O(n), and the subset sum calculation is effectively 
O(n) due to the bitset-based optimization and careful handling of elements.
Space Complexity: O(n) - Storage for adjacency list, subtree sizes, and auxiliary arrays.
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <algorithm>
#include <bitset>
#include <utility>
#include <vector>

#define ll long long
#define debug(x) printf(" " #x ":%d\n", x);
using namespace std;
const int MAXN = 1e6 + 5;
const int inf = 0x3f3f3f3f;
const int mod = 998244353;
typedef pair<int, int> pii;
char buf[1 << 21], *p1 = buf, *p2 = buf, obuf[1 << 21], *o = obuf, of[35];
#define gc()                                                                   \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2)     \
       ? EOF                                                                   \
       : *p1++)
inline ll qpow(ll a, ll n) {
  ll res = 1;
  while (n) {
    if (n & 1)
      res = res * a % mod;
    n >>= 1;
    a = a * a % mod;
  }
  return res;
}
inline int read() {
  int s = 0, f = 1;
  char c = gc();
  for (; !isdigit(c); c = gc())
    if (c == '-')
      f = -1;
  for (; isdigit(c); c = gc())
    s = s * 10 + c - '0';
  return s * f;
}
int n, m, q;
struct EG {
  int to, nxt;
} e[MAXN << 1];
int head[MAXN], tot;
int siz[MAXN];
inline void add(int u, int v) {
  e[tot] = EG{v, head[u]};
  head[u] = tot++;
}
ll ans;
vector<ll> b;
ll closest;
template <int len = 1> void subset_sum(int n) {
  if (n >= len) {
    subset_sum<min(len * 2, MAXN)>(n);
    return;
  }
  bitset<len> dp;
  dp[0] = 1;
  for (ll x : b)
    dp = dp | (dp << x);
  ll cv = n;
  closest = 0;
  for (int i = 0; i <= n; ++i)
    if (dp[i] && abs(i - (n - i)) < cv) {
      closest = i;
      cv = abs(i - (n - i));
    }
}
ll solve(vector<ll> &a) {
  if (a.empty())
    return 0;
  sort(a.rbegin(), a.rend());
  ll cs = 0;
  for (ll x : a)
    cs += x;
  if (a[0] * 2 >= cs)
    return a[0];
  int n = a.size();
  a.push_back(0);
  b.clear();
  int pi = 0;
  for (int i = 1; i <= n; ++i)
    if (a[i] ^ a[i - 1]) {
      ll cnt = i - pi;
      ll x = a[i - 1];
      ll j = 1;
      while (j < cnt) {
        b.push_back(x * j);
        cnt -= j;
        j *= 2;
      }
      b.push_back(x * cnt);
      pi = i;
    }
  subset_sum(cs);
  return closest;
}
void dfs(int cur, int fat) {
  siz[cur] = 1;
  vector<ll> a;
  for (int i = head[cur]; ~i; i = e[i].nxt) {
    if (e[i].to == fat)
      continue;
    dfs(e[i].to, cur);
    siz[cur] += siz[e[i].to];
    a.push_back(siz[e[i].to]);
  }
  ll x = solve(a);
  ans += x * (siz[cur] - 1 - x);
  a.clear();
}
signed main(signed argc, char const *argv[]) {
  clock_t c1 = clock();
#ifdef LOCAL
  freopen("in.in", "r", stdin);
  freopen("out.out", "w", stdout);
#endif
  memset(head, -1, sizeof(head));
  n = read();
  for (int i = 2; i <= n; ++i) {
    int u = read();
    add(i, u), add(u, i);
  }
  dfs(1, -1);
  printf("%lld\n", ans);
#ifdef LOCAL
end:
  cout << "Time Used:" << clock() - c1 << "ms" << endl;
#endif
  return 0;
}


// https://github.com/VaHiX/CodeForces/