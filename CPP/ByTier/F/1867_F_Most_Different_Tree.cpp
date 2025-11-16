// Problem: CF 1867 F - Most Different Tree
// https://codeforces.com/contest/1867/problem/F

/*
 * Purpose: This code solves the problem of finding a tree G' that minimizes the number of subtrees
 *          in P(G') that are isomorphic to any subtree in P(G), where G is a given rooted tree.
 *          The approach uses a hashing technique to compute subtree signatures and then tries
 *          different tree structures to minimize overlap in subtree signatures.
 *
 * Algorithms/Techniques:
 * - Tree hashing using polynomial rolling hash to uniquely identify subtree structures.
 * - Backtracking to generate candidate tree structures.
 * - Hash map to track already seen subtree signatures.
 *
 * Time Complexity: O(n^2 * log n) in the worst case due to backtracking over possible tree structures.
 * Space Complexity: O(n^2) for storing the tree adjacency lists and hash map.
 */
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

#pragma GCC optimize(2)
#define ll unsigned long long
#define For(i, a, n) for (int i = a; i <= n; i++)
#define rof(i, n, a) for (int i = n; i >= a; i--)
#define endl "\n"
using namespace std;
const int maxn = 1e6 + 5;
int T;
int n;
ll f[maxn];
vector<int> g[maxn];
unordered_map<ll, int> vis;

// Function to compute the hash of a subtree rooted at u
void dfs(int u, int cnt) {
  f[u] = 0x3f3f3f3f;
  auto h = [&](ll x) { return x * x * x * 1541141 + 1920817; };  // Hash function to compute hash of a value
  auto c = [&](ll x) { return h(x & 0x7fffffff) + h(x >> 31); }; // Combine low and high bits for better hash
  for (auto v : g[u]) {
    if (v != cnt) {
      dfs(v, u);
      f[u] += c(f[v]);  // Accumulate hash values from children
    }
  }
}

// Recursive backtracking function to try different tree structures
void v(int cur, int cnt, int las) {
  if (cur > cnt) {
    dfs(1, 0);
    if (vis.count(f[1]))
      return;
    For(i, 1, n - cnt) { cout << i << " " << i + 1 << endl; }
    For(i, 1, cnt) {
      for (auto j : g[i])
        cout << n - cnt + i << " " << n - cnt + j << endl;
    }
    exit(0);
  }
  For(i, las, cur - 1) {
    g[i].emplace_back(cur);
    v(cur + 1, cnt, i);
    g[i].pop_back();
  }
}

// Solves the input tree and generates the optimal tree G'
void solve() {
  cin >> n;
  For(i, 1, n - 1) {
    int u, v;
    cin >> u >> v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
  if (n == 2)
    cout << "1 2" << endl;
  else {
    dfs(1, 0);
    For(i, 1, n) vis[f[i]] = 1;
    For(i, 1, n) g[i].clear();
    For(i, 1, n) v(2, i, 1);
  }
  return;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  T = 1;
  For(I, 1, T) { solve(); }
  return 0;
}


// https://github.com/VaHiX/CodeForces/