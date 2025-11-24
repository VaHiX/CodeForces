// Problem: CF 2068 E - Porto Vs. Benfica
// https://codeforces.com/contest/2068/problem/E

/*
E. Porto Vs. Benfica

Algorithms/Techniques:
- BFS to compute shortest distances from destination (Porto)
- Edge-based enumeration and prioritized path analysis using a modified Dijkstra-style approach
- Union-Find with path compression for dynamic connectivity tracking
- Priority queue optimization

Time Complexity: O((n + m) * log(n))
Space Complexity: O(n + m)

Task:
Given an unweighted undirected graph representing roads in Portugal, where vertex 1 is Lisbon and n is Porto:
- The police block one road once to delay fans from reaching Porto
- Fans optimally reroute after blocking
- Determine the minimum number of edges required under optimal strategies

This implementation uses:
1. BFS to build shortest path tree from destination
2. Analyzes all edges for possible blocking points with potential detours
3. Applies union-find with merge strategy based on distance priorities
4. Final traversal to find updated shortest path after considering blocked roads.
*/

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
int n = 0, m = 0, cnt = 0, tot = 0;
array<int, 200100> head, dis, vis, up, del, fa, num;
struct Node {
  int to;
  int nxt;
};
struct Item {
  int val;
  int x;
  int y;
};
struct Point {
  int id;
  int path;
};
array<Node, 400100> edge;
array<pair<int, int>, 400100> line;
array<Item, 400100> tmp;

void new_line(int a, int b) {
  edge[++cnt].to = b;
  edge[cnt].nxt = head[a];
  head[a] = cnt;
  return;
}

bool operator<(const Point &x, const Point &y) { return x.path < y.path; }
bool operator>(const Point &x, const Point &y) { return x.path > y.path; }

priority_queue<Point, vector<Point>, greater<Point>> q;

int find(int x) {
  if (x == fa[x])
    return x;
  return fa[x] = find(fa[x]);
}

void merge(int x, int y) {
  fa[find(y)] = find(x);
  return;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    fa[i] = i;
  for (int i = 1; i <= m; ++i) {
    int x = 0, y = 0;
    cin >> x >> y;
    new_line(x, y);
    new_line(y, x);
    line[i] = {x, y};
  }

  dis.fill(1e9);
  dis[n] = 0;
  q.push({n, 0});
  while (!q.empty()) {
    int x = q.top().id;
    q.pop();
    if (vis[x])
      continue;
    vis[x] = true;
    for (int e = head[x]; e; e = edge[e].nxt) {
      int to = edge[e].to;
      if (dis[to] > dis[x] + 1) {
        dis[to] = dis[x] + 1;
        up[to] = x; // Store parent in BFS tree
        q.push({to, dis[to]});
      }
    }
  }

  // Enumerate all edges and evaluate detour costs if blocked
  for (int i = 1; i <= m; ++i) {
    int x = line[i].first, y = line[i].second;
    // If edge is not part of the shortest path from destination to source
    if (up[x] != y && up[y] != x)
      tmp[++tot] = {dis[x] + dis[y] + 1, x, y};
  }

  num.fill(-1e9); // Used for storing adjusted distances

  // Sort edges by detour cost
  stable_sort(tmp.data() + 1, tmp.data() + tot + 1,
              [&](Item x, Item y) { return x.val < y.val; });

  // Process each edge based on priority and union-find logic
  for (int i = 1; i <= tot; ++i) {
    while (1) {
      tmp[i].x = find(tmp[i].x), tmp[i].y = find(tmp[i].y);
      if (tmp[i].x == tmp[i].y)
        break;
      if (dis[tmp[i].x] > dis[tmp[i].y]) {
        num[tmp[i].x] = tmp[i].val - dis[tmp[i].x];
        merge(up[tmp[i].x], tmp[i].x);
      } else {
        num[tmp[i].y] = tmp[i].val - dis[tmp[i].y];
        merge(up[tmp[i].y], tmp[i].y);
      }
    }
  }

  vis.fill(0);
  dis.fill(1e9);
  dis[n] = 0;
  q.push({n, 0});
  while (!q.empty()) {
    int x = q.top().id, d = q.top().path;
    q.pop();
    if (d != dis[x])
      continue;
    if (vis[x])
      continue;
    vis[x] = true;
    for (int e = head[x]; e; e = edge[e].nxt) {
      int to = edge[e].to;
      if (num[to] != -1e9 && dis[to] > max(d + 1, num[to])) {
        dis[to] = max(d + 1, num[to]);
        q.push({to, dis[to]});
      }
    }
  }

  if (dis[1] == 1e9) {
    cout << "-1" << endl;
    return 0;
  }
  cout << dis[1] << endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/