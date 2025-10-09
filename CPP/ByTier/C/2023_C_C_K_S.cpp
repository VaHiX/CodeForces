// Problem: CF 2023 C - C+K+S
// https://codeforces.com/contest/2023/problem/C

/*
C. C+K+S
time limit per test3 seconds
memory limit per test256 megabytes

Problem Description:
We are given two strongly connected directed graphs, each with n vertices and possibly different numbers of edges. The length of any cycle in both graphs is divisible by k.
Each vertex belongs to one of two types: incoming (0) or outgoing (1). For each graph we know the vertex types.
We need to determine if exactly n directed edges can be drawn between the graphs such that:
1. Each edge connects a vertex from the first graph to a vertex in the second graph.
2. From each outgoing vertex in first graph, exactly one new edge originates.
3. Into each incoming vertex in second graph, exactly one new edge enters.
4. In resulting combined graph, any cycle length is divisible by k.

Algorithms/Techniques:
- BFS traversal of graphs to compute distances modulo k
- Use of a sliding window approach to match cycles with same pattern of types modulo k
- Matching condition checking based on frequency counts

Time Complexity: O(n + m1 + m2) per test case where m1 and m2 are edge counts.
Space Complexity: O(n + m1 + m2) for storing the graphs and auxiliary arrays.

*/

#include <cstdio>
#include <queue>

using namespace std;
int n, m, k;
struct G {
  int tot, to[500005], nxt[500005], lst[500005];
  int a[500005], vi[500005], dis[500005];
  int s[1000005][2], id, cnt;
  void init() {
    tot = cnt = 0;
    for (int i = 1; i <= n; i += 1)
      vi[i] = lst[i] = 0;
    return;
  }
  void add(int x, int y) {
    to[++tot] = y;
    nxt[tot] = lst[x];
    lst[x] = tot;
    return;
  }
  void work(int flag) {
    queue<int> q;
    int x, y;
    q.push(1);
    vi[1] = 1;
    while (!q.empty()) {
      x = q.front();
      q.pop();
      cnt += a[x]; // Accumulate count of outgoing vertices
      for (int i = lst[x]; i; i = nxt[i]) {
        if (vi[y = to[i]])
          continue;
        if ((dis[y] = dis[x] + 1) >= k)
          dis[y] -= k; // Distance mod k
        vi[y] = 1;
        q.push(y);
      }
    }
    // Reset s array for type frequency counting
    for (int i = 0; i < k; i += 1)
      s[i][0] = s[i][1] = 0;
    for (int i = 1; i <= n; i += 1)
      s[dis[i]][a[i] ^ flag] += 1; // Count based on type and dis mod k

    if (flag) {
      cnt = n - cnt; // For second graph, invert count
      for (int i = k + 1; i > 1; i -= 1) { // Rotate the array for correct comparison in second graph
        s[i][0] = s[i - 2][0];
      }
      s[1][0] = s[k + 1][0]; // Wraparound copy
      s[0][0] = s[k][0];
    }
    for (int i = 0; i < k; i += 1) { // Duplicate the array to allow rotation lookups without overflow
      s[i + k][0] = s[i][0];
      s[i + k][1] = s[i][1];
    }
    id = -1;
    for (int i = 0, j, l; i < 2 * k;) { // Try all rotations to find a matching start
      j = i;
      l = i + 1;
      while (s[j][0] < s[l][0] || (s[j][0] == s[l][0] && s[j][1] <= s[l][1])) {
        if (s[j][0] == s[l][0] && s[j][1] == s[l][1])
          j += 1, l += 1;
        else
          j = i, l += 1;
      }
      while (i <= j) { // Sliding window logic to advance index efficiently
        if (i + (l - j) >= k) {
          id = i;
          break;
        }
        i += l - j;
      }
      if (~id)
        break; // Match found, exit loop
    }
    return;
  }
} G[2];

void solve() {
  scanf("%d%d", &n, &k);
  for (int k = 0; k < 2; k += 1) { // Loop for graph 0 and graph 1
    for (int i = 1; i <= n; i += 1)
      scanf("%d", &G[k].a[i]); // Read vertex types
    scanf("%d", &m);
    G[k].init(); // Initialize graph structure
    for (int i = 1; i <= m; i += 1) {
      int x, y;
      scanf("%d%d", &x, &y);
      G[k].add(x, y); // Add edge to adjacency list
    }
    G[k].work(k); // Process graph and compute type counts with rotation
  }
  if (G[0].cnt == G[1].cnt) { // Check if same number of outgoing vertices in both graphs
    if (!G[0].cnt || G[0].cnt == n)
      printf("YES\n"); // All out/in or no constraints, always valid
    else {
      int flag = 1;
      for (int i = 0; i < k; i += 1) { // Match types modulo k across both graphs
        int p = G[0].id, q = G[1].id; // Get alignment indices from computed rotations
        if (G[0].s[p + i][0] != G[1].s[q + i][0])
          flag = 0;
        if (G[0].s[p + i][1] != G[1].s[q + i][1])
          flag = 0;
      }
      if (flag)
        printf("YES\n");
      else
        printf("NO\n");
    }
  } else
    printf("NO\n"); // Mismatch in number of outgoing vertices - constraint violated
  return;
}
int main() {
  int t;
  scanf("%d", &t);
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/