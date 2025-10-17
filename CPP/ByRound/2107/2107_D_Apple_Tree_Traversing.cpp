// Problem: CF 2107 D - Apple Tree Traversing
// https://codeforces.com/contest/2107/problem/D

/*
D. Apple Tree Traversing

Algorithms/Techniques:
- Tree diameter finding using two DFS traversals
- Greedy strategy to maximize lexicographically: always select the longest valid path first
- DFS-based decomposition of tree into components, processing each subtree recursively
- Path selection is done greedily by choosing the heaviest possible edge path that starts from a leaf towards the center

Time Complexity: O(n log n) per test case due to sorting (ans vector is at most 3*n, so sort dominates)
Space Complexity: O(n) for adjacency list, visited flags, and recursion stack

This solves a greedy problem on trees where we want to decompose a tree into paths such that
the lexicographically largest sequence of (path_length, start_node, end_node) is obtained.
*/
#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <array>
#include <functional>
#include <utility>
#include <vector>

using namespace std;
typedef pair<int, int> PII;
inline int read() {
  int x = 0, f = 1;
  char c = 0;
  while (!isdigit(c)) {
    if (c == '-')
      f = -1;
    c = getchar();
  }
  while (isdigit(c)) {
    x = (x << 3) + (x << 1) + (c - '0');
    c = getchar();
  }
  return x * f;
}
const int N = 3e5 + 10;
int n;
int ne[N], e[N], h[N], idx;        // adjacency list for tree
int to[N];                         // stores parent in path during DFS
bool st[N];                        // marks nodes as processed (used in path marking)
vector<array<int, 3>> ans;         // stores results as [diameter, max_node, min_node]
inline void add(int a, int b) {
  ne[idx] = h[a];
  e[idx] = b;
  h[a] = idx++;
}
PII dfs(int u, int pre) {
  PII res = {0, u};              // {max_depth_so_far, node_at_max_depth}
  to[u] = 0;                     // reset parent tracking for current subtree
  for (int i = h[u]; ~i; i = ne[i]) {
    int v = e[i];
    if (v != pre && !st[v]) {    // skip parent and already processed nodes
      PII w = dfs(v, u);         // explore deeper
      if (w > res)
        res = w, to[u] = v;      // update max depth and record parent in path
    }
  }
  return {res.first + 1, res.second}; // return updated depth+1 for upward propagation
}
void work(int u) {
  auto t = dfs(u, u);            // find one end of diameter starting from u  
  int S = t.second;
  t = dfs(S, S);                 // find other end of diameter with known start (S)
  int dia = t.first, T = t.second; // get the diameter and corresponding terminal node
  ans.push_back({dia, max(S, T), min(S, T)}); // record this diameter along with endpoints

  for (int now = S; now; now = to[now]) // mark all nodes in path as processed
    st[now] = true;

  for (int now = S; now; now = to[now]) {  // recurse over each unvisited neighbor of marked path nodes
    for (int i = h[now]; ~i; i = ne[i]) {
      int v = e[i];
      if (!st[v])
        work(v);
    }
  }
}
inline void solve() {
  ans.clear();
  n = read();                    // read number of nodes

  for (int i = 1; i <= n; i++)
    h[i] = -1, st[i] = false;    // initialize adjacency & visited arrays

  idx = 0;
  for (int i = 1; i < n; i++) {  // read edges and build undirected tree
    int a = read(), b = read();
    add(a, b);
    add(b, a);
  }

  work(1);                       // begin DFS walk from root node

  sort(ans.begin(), ans.end(), greater<>()); // sort by lexicographic order descending to find max sequence
  for (auto [a, b, c] : ans)
    printf("%d %d %d ", a, b, c);
  puts("");
}
int main() {
  int t = read();
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/