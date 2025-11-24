// Problem: CF 1765 A - Access Levels
// https://codeforces.com/contest/1765/problem/A

/*
Algorithm: This solution uses a maximum flow approach to find the minimum number of access groups.
It models the problem as a bipartite graph where developers are on one side and documents on the other.
Each developer is connected to documents they need access to.
The goal is to find a minimum vertex cover to determine group assignments.
Time Complexity: O(n^2 * m + n^3) where n is number of developers, m is number of documents
Space Complexity: O(n^2 + m) for storing the graph and related data structures.

The key idea is:
1. For each document, we know which developers need access to it.
2. We treat developers who need access to the same documents as "compatible" and want to assign them to the same group.
3. We use a bipartite matching approach with max flow to determine groupings.
4. We then extract the group assignments from the flow result.
*/

#include <stdio.h>
#include <algorithm>
#include <bitset>
#include <queue>

using namespace std;
const int N = 1005, B = 300005, INF = 1e9;
char a[N][N];
bitset<N> b[N];
int n, m, id[N], c[N], h[N], tot = 1, s, t, cur[N], d[N], ans, to[N], cc[N],
                             num, be[N], f[N][N];
bool vis[N];
struct edge {
  int to, val, nxt;
} e[B];
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
    d[i] = 0;
  q.push(s);
  d[s] = 1;
  cur[s] = h[s];
  while (q.size()) {
    int u = q.front();
    q.pop();
    for (int i = h[u]; i; i = e[i].nxt) {
      int v = e[i].to, val = e[i].val;
      if (val == 0 || d[v])
        continue;
      d[v] = d[u] + 1;
      cur[v] = h[v];
      q.push(v);
      if (v == t)
        return 1;
    }
  }
  return 0;
}
int dinic(int u, int sum) {
  if (u == t)
    return sum;
  int res = sum;
  for (int &i = cur[u]; i && res; i = e[i].nxt) {
    int v = e[i].to, val = e[i].val;
    if (val == 0 || d[v] != d[u] + 1)
      continue;
    int k = dinic(v, min(res, val));
    if (!k)
      d[v] = 0;
    res -= k;
    e[i].val -= k, e[i ^ 1].val += k;
  }
  return sum - res;
}
int main() {
  scanf("%d%d", &m, &n); // Read number of documents and developers
  for (int i = 1; i <= m; i++)
    scanf("%s", a[i] + 1); // Read access matrix
  for (int j = 1; j <= n; j++) {
    id[j] = j; // Initialize developer IDs
    for (int i = 1; i <= m; i++) {
      if (a[i][j] == '1') { // If developer j needs access to document i
        c[j]++; // Increment count for developer
        b[j][i] = 1; // Mark document in bitset for developer
      }
    }
  }
  sort(id + 1, id + n + 1, [](int i, int j) { return c[i] < c[j]; }); // Sort by access count
  s = n + n + 1, t = s + 1; // Set source and sink nodes
  for (int i = 1; i <= n; i++) {
    Add(s, id[i], 1); // Connect source to each developer
    Add(id[i] + n, t, 1); // Connect each developer to sink
    for (int j = i + 1; j <= n; j++) {
      // If all documents that developer i needs are also needed by developer j
      if ((b[id[i]] & b[id[j]]) == b[id[i]])
        Add(id[j], id[i] + n, 1); // Connect them in the bipartite graph
    }
  }
  while (bfs()) // Run Dinic's algorithm until no augmenting path exists
    ans += dinic(s, INF);
  for (int u = 1; u <= n; u++) {
    for (int i = h[u]; i; i = e[i].nxt) {
      int v = e[i].to, val = e[i].val;
      if (v != s && val == 0) { // If edge is saturated and not to source
        to[u] = v - n; // Record the mapping
        vis[v - n] = 1; // Mark as visited
      }
    }
  }
  for (int u = 1; u <= n; u++) {
    if (!vis[u]) { // If not visited, start new group
      int v = u, cnt = 0;
      num++; // Increment group number
      while (v) {
        be[v] = num; // Assign group number to developer
        cc[v] = ++cnt; // Assign count within group
        for (int i = 1; i <= m; i++)
          if (b[v][i])
            f[i][num]++; // Update document group assignment matrix
        v = to[v]; // Move to next developer
      }
    }
  }
  printf("%d\n", num); // Print number of groups
  for (int i = 1; i <= n; i++)
    printf("%d ", be[i]); // Print group assignments for developers
  printf("\n");
  for (int i = 1; i <= n; i++)
    printf("%d ", cc[i] + 1); // Print access levels for developers
  printf("\n");
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= num; j++)
      printf("%d ", f[i][j] + 1); // Print document assignments
    printf("\n");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/