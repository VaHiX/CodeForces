// Problem: CF 1936 C - Pokémon Arena
// https://codeforces.com/contest/1936/problem/C

/*
 * Problem: Pokémon Arena
 * 
 * Description:
 * You start with the first Pokémon in the arena and want to end up with the n-th Pokémon.
 * You can either:
 * 1. Increase an attribute of a Pokémon by k (cost k)
 * 2. Duel with a Pokémon using a specific attribute (cost the Pokémon's hiring cost)
 * 
 * Goal: Find the minimum total cost to get the n-th Pokémon standing in the arena.
 * 
 * Approach:
 * This is a shortest path problem on a graph. We model it using:
 * - A node for each attribute (n * m nodes)
 * - A super-source node (nm + 1)
 * - A super-sink node (nm + n)
 * 
 * Edges are added to represent:
 * 1. Attribute upgrades (intra-Pokémon relationships)
 * 2. Hiring costs (from attribute nodes to Pokémon nodes)
 * 3. Dueling logic (costs depend on attribute values)
 * 
 * We use Dijkstra's algorithm to find the shortest path from the super-source to the super-sink.
 * 
 * Time Complexity: O((n * m * log(n * m) + n * m))
 * Space Complexity: O(n * m)
 */

#include <stdio.h>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;
int T, n, m, nm, c[400005], a[400005];
int cnt, p[800005], nxt[2000005], to[2000005], w[2000005];
long long dis[800005];
bool inq[800005];
struct node {
  int id, val;
  node() {}
  node(int _id, int _val) : id(_id), val(_val) {}
} rk[400005];
bool cmp(node &u, node &v) { return u.val < v.val; }
struct cmpq {
  bool operator()(int &u, int &v) { return dis[u] > dis[v]; }
};
priority_queue<int, vector<int>, cmpq> q;

// Add an edge to the graph
void addedge(int x, int y, int val) {
  to[++cnt] = y, w[cnt] = val, nxt[cnt] = p[x], p[x] = cnt;
}

// Convert 2D index (i,j) to 1D node ID
int getid(int x, int y) { return (x - 1) * m + y; }

// Process a single test case
void work() {
  scanf("%d%d", &n, &m);
  nm = n * m;
  for (int i = 1; i <= n * (m + 1); i++)
    p[i] = -1, dis[i] = 1e17, inq[i] = false;
  for (int i = 1; i <= n; i++)
    scanf("%d", c + i);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      scanf("%d", &a[getid(i, j)]);
  cnt = 0;
  
  // Build edges based on attribute values
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++)
      rk[j] = node(getid(j, i), a[getid(j, i)]);
    sort(rk + 1, rk + n + 1, cmp);
    for (int j = 1; j < n; j++)
      addedge(rk[j].id, rk[j + 1].id, 0),
          addedge(rk[j + 1].id, rk[j].id, rk[j + 1].val - rk[j].val);
  }
  
  // Connect attribute nodes to Pokémon hiring cost nodes
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      addedge(nm + i, getid(i, j), 0), addedge(getid(i, j), nm + i, c[i]);
  
  // Initialize distance from super-source
  dis[nm + 1] = 0;
  inq[nm + 1] = true;
  q.push(nm + 1);
  int x, y;
  
  // Run Dijkstra
  while (q.size()) {
    x = q.top(), q.pop();
    for (int i = p[x]; i != -1; i = nxt[i])
      if (dis[y = to[i]] > dis[x] + w[i]) {
        dis[y] = dis[x] + w[i];
        if (!inq[y]) {
          inq[y] = true;
          q.push(y);
        }
      }
    inq[x] = false;
  }
  
  printf("%lld\n", dis[nm + n]);
}

int main() {
  scanf("%d", &T);
  while (T--)
    work();
  return 0;
}


// https://github.com/VaHiX/CodeForces/