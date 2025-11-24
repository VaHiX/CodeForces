// Problem: CF 1843 F2 - Omsk Metro (hard version)
// https://codeforces.com/contest/1843/problem/F2

/*
 * Problem: Omsk Metro (hard version)
 * 
 * Purpose: 
 * This code handles queries on a dynamic tree where each node has a weight of -1 or 1.
 * For each query, we need to determine if there exists a path between two nodes such that the sum of weights along that path equals a target value k.
 * 
 * Approach:
 * - Uses Heavy-Light Decomposition (HLD) with segment tree-like operations for range queries
 * - Each node is processed in the context of its parent, and a jump array is maintained for efficient LCA computation
 * - For each node, we maintain a structure (T) that tracks minimum and maximum prefix sums and the total sum from the root to that node
 * - When querying for a path between u and v, we compute results from u to LCA(u,v) and v to LCA(u,v), then combine them
 * 
 * Time Complexity: O(n * log^2(n)) per test case
 * Space Complexity: O(n * log(n)) for storage of jump and dp arrays
 */

#include <stddef.h>
#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

using namespace std;
#define f first
#define s second
#define ll long long
#define pii pair<int, int>
#define pli pair<ll, int>
#define pll pair<ll, ll>
#define tiii tuple<int, int, int>
#define tiiii tuple<int, int, int, int>
#define pb push_back
#define eb emplace_back
#define emp emplace
#define mkp make_pair
#define mkt make_tuple
#define vctr vector
#define arr array
#define all(x) x.begin(), x.end()
#define FILL(a, n, x) fill(a + 1, a + n + 1, x);
#define FILL0(a, n, x) fill(a, a + n, x);
#define amin(a, b) a = min(a, b)
#define amax(a, b) a = max(a, b)
#define brick(x) cout << #x << " = " << x << " | ";

const int MOD = 1e9 + 7;
int a[200005];            // weight of each node
int jump[200005];         // jump array for HLD
int pa[200005];           // parent array
int d[200005];            // depth of each node
using T = arr<int, 7>;    // structure to track prefix mins/maxs and total
T dp[200005];             // dp array for HLD
T merge(T l, T r) {
  T res;
  res[0] = min(r[0], r[6] + l[0]);
  res[1] = min({l[1], r[1], l[0] + r[2]});
  res[2] = min(l[2], l[6] + r[2]);
  res[3] = max(r[3], r[6] + l[3]);
  res[4] = max({l[4], r[4], l[3] + r[5]});
  res[5] = max(l[5], l[6] + r[5]);
  res[6] = l[6] + r[6];
  return res;
}
T init(int x) {
  T res;
  res[0] = res[1] = res[2] = min(0, a[x]);
  res[3] = res[4] = res[5] = max(0, a[x]);
  res[6] = a[x];
  return res;
}
int lca(int u, int v) {
  if (d[u] < d[v])
    swap(u, v);
  int cnt = 0;
  while (d[u] > d[v]) {
    if (d[jump[u]] >= d[v])
      u = jump[u];
    else
      u = pa[u];
  }
  while (u != v) {
    if (jump[u] == jump[v]) {
      u = pa[u];
      v = pa[v];
    } else {
      u = jump[u];
      v = jump[v];
    }
  }
  return u;
}
T qry(int u, int v) {
  T res = {{0, 0, 0, 0, 0, 0, 0}};
  while (d[u] > d[v]) {
    if (d[jump[u]] >= d[v]) {
      res = merge(res, dp[u]);
      u = jump[u];
    } else {
      res = merge(res, init(u));
      u = pa[u];
    }
  }
  return res;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int tt;
  cin >> tt;
  while (tt--) {
    int q;
    cin >> q;
    vctr<arr<int, 3>> vc;
    int n = 1;
    a[n] = 1;
    jump[1] = 1;
    while (q--) {
      char c;
      cin >> c;
      if (c == '+') {
        ++n;
        cin >> pa[n] >> a[n];
        d[n] = d[pa[n]] + 1;
        int z[3];
        z[0] = pa[n];
        z[1] = jump[z[0]];
        z[2] = jump[z[1]];
        dp[n] = init(n);
        if (d[z[2]] - d[z[1]] == d[z[1]] - d[z[0]]) {
          jump[n] = z[2];
          dp[n] = merge(dp[n], merge(dp[z[0]], dp[z[1]]));
        } else {
          jump[n] = z[0];
        }
      } else {
        int u, v, k;
        cin >> u >> v >> k;
        int x = lca(u, v);
        T res1 = qry(u, x);
        T res2 = qry(v, x);
        int min1 = min({res1[1], res2[1], res1[0] + res2[0] + a[x]});
        int max1 = max({res1[4], res2[4], res1[3] + res2[3] + a[x]});
        cout << ((min1 <= k && k <= max1) ? "YES" : "NO") << '\n';
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/