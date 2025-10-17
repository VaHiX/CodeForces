// Problem: CF 2052 M - Managing Cluster
// https://codeforces.com/contest/2052/problem/M

/*
 * Code Purpose: Solves the cluster manager optimization problem where we aim to maximize
 *               the number of services with replicas on directly connected machines via swaps.
 *
 * Algorithms/Techniques:
 *   - Tree DP for computing maximum matching in tree structure
 *   - DFS traversal and backtracking to find swap operations
 *   - Greedy pairing logic for service replica assignment
 *
 * Time Complexity: O(n) per test case, due to linear processing of nodes and edges.
 * Space Complexity: O(n) for storing graph structure and auxiliary arrays.
 */

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <string.h>
#include <utility>
#include <vector>
using namespace std;
#define rep(i, l, r) for (int i = l, _ = r; i <= _; ++i)
#define per(i, r, l) for (int i = r, _ = l; i >= _; --i)
#define iter(x, v) for (int _p = head[x], v; v = ver[_p], _p; _p = nxt[_p])
#define ll long long
#define lowbit(x) ((x) & -(x))
template <typename T> inline void chkmin(T &x, T y) { x = x < y ? x : y; }
template <typename T> inline void chkmax(T &x, T y) { x = x > y ? x : y; }

int t, n, bro[200010], pre[200010], ver[400010], nxt[400010], head[200010], num,
    a[200010], f[200010][2];
bool all[200010];
vector<pair<int, int>> ans, out;
vector<int> mp[200010];

// dfs computes the maximum number of matched pairs for each subtree
void dfs(int x, int fa) {
  int sum0 = 0;
  iter(x, v) if (v != fa) dfs(v, x), sum0 += max(f[v][0], f[v][1]);
  f[x][0] = sum0;
  iter(x, v) if (v != fa) {
    int now = sum0 - max(f[v][0], f[v][1]) + f[v][0] + 1; // calculate gain from choosing current edge
    if (now > f[x][1])
      f[x][1] = now, pre[x] = v;
  }
}

// dfs2 identifies which edges to use for swapping based on computed matching
void dfs2(int x, int fa, int id) {
  if (!id || f[x][0] > f[x][1]) {
    iter(x, v) if (v != fa) dfs2(v, x, 1);
    return;
  }
  if (~pre[x])
    bro[x] = pre[x], bro[pre[x]] = x, ans.push_back(make_pair(x, pre[x])),
    dfs2(pre[x], x, 0);
  iter(x, v) if (v != fa && v != pre[x]) dfs2(v, x, 1);
}

// Function to add an edge to the adjacency list
inline void add(int x, int y) {
  ver[++num] = y, nxt[num] = head[x], head[x] = num;
}

int main() {
  ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    ans.clear(), out.clear(), num = 0;
    // Initialize all arrays for this test case
    cin >> n, memset(head, 0, (2 * n + 1) << 2),
        memset(pre, 255, (2 * n + 1) << 2);
    memset(all, 0, 2 * n + 1), memset(bro, 0, (2 * n + 1) << 2);
    rep(i, 1, n) mp[i].clear();
    rep(i, 1, 2 * n) cin >> a[i], mp[a[i]].push_back(i); // Map service to positions
    rep(i, 1, 2 * n - 1) {
      int x, y;
      cin >> x >> y;
      add(x, y), add(y, x); // Add bidirectional edges to adjacency list
    }
    rep(i, 1, 2 * n) f[i][0] = f[i][1] = 0; // Reset DP values
    dfs(1, 0), dfs2(1, 0, 1); // Compute matching and backtracking info

    // Process first type of uncovered paths (not forming bridges)
    rep(i, 1, n) if (!all[i]) {
      if ((!bro[mp[i][0]] && !bro[mp[i][1]]) ||
          (bro[mp[i][0]] && bro[mp[i][1]]))
        continue;
      vector<int> S;
      S.clear();
      int X = mp[i][0];
      if (!bro[X])
        X = mp[i][1];
      while (true) {
        all[a[X]] = true;
        int nxtx = bro[X];
        S.push_back(X);
        int anox = mp[a[nxtx]][0] + mp[a[nxtx]][1] - nxtx; // Get the other end of same service
        if (a[nxtx] == i)
          break;
        S.push_back(nxtx);
        if (!bro[anox]) {
          all[a[nxtx]] = true, S.push_back(anox);
          break;
        }
        assert(!all[a[nxtx]]);
        X = anox;
      }
      int siz = S.size();
      rep(i, 0, siz / 2 - 1) out.push_back(make_pair(S[i], S[siz - i - 1]));
    }

    // Process second type of uncovered paths (forming bridges)
    rep(i, 1, n) if (!all[i]) {
      if (!bro[mp[i][0]] || !bro[mp[i][1]])
        continue;
      vector<int> S;
      S.clear();
      int X = mp[i][0];
      if (!bro[X])
        X = mp[i][1];
      while (true) {
        all[a[X]] = true;
        int nxtx = bro[X];
        S.push_back(X);
        int anox = mp[a[nxtx]][0] + mp[a[nxtx]][1] - nxtx; // Calculate corresponding node
        if (a[nxtx] == i)
          break;
        S.push_back(nxtx);
        if (!bro[anox]) {
          all[a[nxtx]] = true, S.push_back(anox);
          break;
        }
        assert(!all[a[nxtx]]);
        X = anox;
      }
      int siz = S.size();
      rep(i, 0, siz / 2 - 1) out.push_back(make_pair(S[i], S[siz - i - 1]));
    }

    cout << out.size() << '\n';
    for (auto &p : out)
      cout << p.first << ' ' << p.second << '\n';
  }
  cout << flush;
  return 0;
}


// https://github.com/VaHiX/codeForces/