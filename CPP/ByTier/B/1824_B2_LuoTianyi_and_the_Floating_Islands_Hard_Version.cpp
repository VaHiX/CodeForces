// Problem: CF 1824 B2 - LuoTianyi and the Floating Islands (Hard Version)
// https://codeforces.com/contest/1824/problem/B2

/*
 * Problem: LuoTianyi and the Floating Islands (Hard Version)
 * 
 * Purpose:
 *   - Given a tree with n nodes, and k people randomly placed on k different nodes,
 *     compute the expected number of "good" nodes. A node is good if its distance sum
 *     to all k people is minimal among all nodes.
 *
 * Techniques/Algorithms:
 *   - Tree DFS traversal (preprocessing and computation)
 *   - Combinatorial mathematics (binomial coefficients)
 *   - Modular inverse and exponentiation
 *   - Dynamic Programming on tree structure
 *
 * Time Complexity:
 *   - O(n) for preprocessing the tree and computing combinations.
 *   - O(n) for DFS traversals.
 *   - Overall time complexity: O(n)
 *
 * Space Complexity:
 *   - O(n) for storing tree structure, DFS counters, and factorials.
 *
 * Note:
 *   - Uses modular arithmetic throughout.
 *   - The solution uses a key insight: for any edge, the number of valid placement
 *     combinations where both sides of the edge have at least k people is counted.
 *   - Then, it adjusts the result using combinatorics to get the expected value.
 */
#include <cstdio>
#include <iosfwd>

using namespace std;
const int N = 2e5 + 1, p = 1e9 + 7;
int fpow(int base, int t = p - 2) {
  int ret = 1;
  while (t) {
    if (t & 1)
      ret = 1ll * ret * base % p;
    base = 1ll * base * base % p;
    t >>= 1;
  }
  return ret;
}
int n, k, fac[N] = {1}, facinv[N], head[N], nxt[N << 1], to[N << 1], eid = 1;
void addedge(int u, int v) {
  to[eid] = v;
  nxt[eid] = head[u];
  head[u] = eid++;
}
int C(int n, int m) { return 1ll * fac[n] * facinv[m] % p * facinv[n - m] % p; }
int cnt[N], ans;
void dfs0(int i, int pre) {
  cnt[i] = 1;
  for (int e = head[i]; e; e = nxt[e])
    if (to[e] != pre) {
      dfs0(to[e], i);
      cnt[i] += cnt[to[e]];
    }
}
void dfs1(int i, int pre) {
  for (int e = head[i]; e; e = nxt[e])
    if (to[e] != pre) {
      if (cnt[to[e]] >= k && cnt[1] - cnt[to[e]] >= k)
        ans = (ans + 1ll * C(cnt[to[e]], k) * C(cnt[1] - cnt[to[e]], k)) % p;
      dfs1(to[e], i);
    }
}
int main() {
  scanf("%d%d", &n, &k);
  if (k & 1) {
    putchar('1');
    return 0;
  }
  for (int i = 1; i <= n; i++)
    fac[i] = 1ll * fac[i - 1] * i % p;
  facinv[n] = fpow(fac[n]);
  for (int i = n; i > 0; i--)
    facinv[i - 1] = 1ll * facinv[i] * i % p;
  k >>= 1;
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    addedge(u, v);
    addedge(v, u);
  }
  dfs0(1, 0);
  dfs1(1, 0);
  ans = (1ll * ans * fpow(C(n, k << 1)) + 1) % p;
  printf("%d", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/