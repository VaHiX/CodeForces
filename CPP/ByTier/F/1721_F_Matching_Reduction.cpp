// Problem: CF 1721 F - Matching Reduction
// https://codeforces.com/contest/1721/problem/F

/*
 * Problem: F. Matching Reduction
 * 
 * Purpose: This code solves an online problem on bipartite graph matching.
 *          It maintains a maximum matching and allows two types of queries:
 *          1. Remove minimum vertices to reduce matching size by 1, then
 *             output the vertices removed and sum of edge indices in new matching.
 *          2. Output the actual edges forming the current maximum matching.
 * 
 * Algorithms:
 * - Dinic's algorithm for maximum flow (used to compute maximum matching)
 * - Bipartite matching using flow network construction
 * - Vertex removal strategy based on augmenting paths and labeling
 * 
 * Time Complexity: O(V^2 * E) for Dinic's algorithm where V = n1 + n2 + 2, E = m
 * Space Complexity: O(V + E) for storing the flow network
 * 
 * Key Techniques:
 * - Flow network transformation: Convert bipartite matching to max flow by
 *   adding source and sink nodes
 * - Tracking matched edges using residual graph
 * - Using BFS/DFS to find augmenting paths
 * - Online processing where each query is answered before reading next
 */

#include <stdio.h>
#include <algorithm>
#include <queue>

using namespace std;
typedef long long ll;
const int N = 4e5 + 5, INF = 1e9;
int n1, n2, m, q, h[N], u[N], v[N], now[N], tot = 1, s, t, f[N], sum, match[N],
                                            S[N], top, op;
ll ans;
struct edge {
  int to, val, nxt;
} e[N << 2];
void add(int u, int v, int w) {
  e[++tot] = {v, w, h[u]};
  h[u] = tot;
}
void Add(int u, int v, int w) {
  add(u, v, w);
  add(v, u, 0);
}
bool bfs() {
  queue<int> q;
  for (int i = 1; i <= t; i++)
    f[i] = 0;
  f[s] = 1, q.push(s);
  now[s] = h[s];
  while (q.size()) {
    int u = q.front();
    q.pop();
    for (int i = h[u]; i; i = e[i].nxt) {
      int v = e[i].to, val = e[i].val;
      if (f[v] || !val)
        continue;
      f[v] = f[u] + 1;
      now[v] = h[v];
      q.push(v);
      if (v == t)
        return 1;
    }
  }
  return 0;
}
int dinic(int u, int flow) {
  if (u == t)
    return flow;
  int rest = flow;
  for (int &i = now[u]; i && rest; i = e[i].nxt) {
    int v = e[i].to, val = e[i].val;
    if (f[v] != f[u] + 1 || !val)
      continue;
    int out = dinic(v, min(rest, val));
    if (!out)
      f[v] = 0;
    e[i].val -= out;
    e[i ^ 1].val += out;
    rest -= out;
  }
  return flow - rest;
}
int main() {
  scanf("%d%d%d%d", &n1, &n2, &m, &q);
  s = n1 + n2 + 1, t = s + 1;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &u[i], &v[i]);
    Add(u[i], v[i] + n1, 1);
  }
  for (int i = 1; i <= n1 + n2; i++) {
    if (i <= n1)
      Add(s, i, 1);
    else
      Add(i, t, 1);
  }
  while (bfs())
    sum += dinic(s, INF);
  // Find all matched edges by examining residual graph
  for (int i = 1; i <= m; i++) {
    if (e[i + i].val == 0) { // Edge is matched
      match[e[i + i].to] = i;  // Store which edge connects to node
      match[e[i + i + 1].to] = i; 
      ans += i;
    }
  }
  // Find vertices that are exposed (not part of matching) in the initial matching
  for (int i = 1; i <= n1; i++)
    if (!f[i])
      S[++top] = i;
  for (int i = n1 + 1; i <= n1 + n2; i++)
    if (f[i])
      S[++top] = i;
  while (q--) {
    scanf("%d", &op);
    if (op == 1) {
      int u = S[top--], i = match[u]; // Pick vertex from the set of exposed vertices
      ans -= i, e[i + i].val = 1; // Undo this edge from matching, mark as available
      sum--;
      printf("1\n%d\n%lld\n", u <= n1 ? u : -(u - n1), ans); // Output vertex and sum
    } else {
      printf("%d\n", sum);
      for (int i = 1; i <= m; i++)
        if (e[i + i].val == 0) // Print matched edges
          printf("%d ", i);
      printf("\n");
    }
    fflush(stdout);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/