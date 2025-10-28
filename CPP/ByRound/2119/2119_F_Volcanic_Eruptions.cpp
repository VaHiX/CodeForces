// Problem: CF 2119 F - Volcanic Eruptions
// https://codeforces.com/contest/2119/problem/F

/*
F. Volcanic Eruptions
Algorithms/Techniques: BFS, DFS, Tree traversal, Shortest path computation

Time Complexity: O(N) per test case
Space Complexity: O(N) 

The problem involves finding the maximum number of moves a person can make in a tree 
starting from a given vertex, where each node has a value of 1 or -1. An eruption floods 
the tree from root over time, and the person dies if their life (sum of visited node weights)
becomes 0 or they are at a flooded node.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for (auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for (auto Ti = (Ta); Ti >= (Tb); Ti--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx), end(Tx)
const int N = 5e5 + 5, INF = 1e9;
int n, st, w[N];
int dist[N], tim[N]; // dist: distance from root node; tim: minimum time to reach a node with different value
int h[N], e[N * 2], ne[N * 2], idx; // adjacency list representation

void add(int a, int b) { 
    e[idx] = b, ne[idx] = h[a], h[a] = idx++; 
}

// Compute distances from root node 1 using BFS
void get_dist(int x, int fa) {
  for (int i = h[x]; ~i; i = ne[i]) {
    int j = e[i];
    if (j == fa)
      continue;
    dist[j] = dist[x] + 1;
    get_dist(j, x);
  }
}

int ans = 0;

// DFS to find maximum moves
void dfs(int x, int fa, int height, int k, int Tim, int dst, bool f) {
  // If we fall below height 0, compute max time that can be spent before dying
  if (height < 0)
    Tim = max(Tim, (-height + 1) / 2 * 2 + k * 2 + dst);
  
  // If we're already at a flooded node, stop
  if (Tim <= dist[x])
    ans = max(ans, dist[x]);
  else
    return;

  for (int i = h[x]; ~i; i = ne[i]) {
    int j = e[i];
    if (j == fa)
      continue;
    
    // If we can switch to a different state and transition is valid
    if (f && w[j] != w[x])
      dfs(j, x, height + w[j], min(k, tim[j]), Tim + 1, dst + 1, 1);
    else
      dfs(j, x, height + w[j], k, Tim + 1, dst + 1, 0);
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T = 1;
  cin >> T;
  while (T--) {
    cin >> n >> st;
    idx = 0;
    For(i, 1, n) h[i] = -1, tim[i] = 1e9;
    For(i, 1, n) cin >> w[i];
    For(i, 1, n - 1) {
      int a, b;
      cin >> a >> b;
      add(a, b), add(b, a);
    }
    
    // Precompute distances from root node
    get_dist(1, 0);
    
    queue<int> q;
    For(x, 1, n) {
      if (w[x] != 1)
        continue;
      for (int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if (w[j] == 1) {
          q.push(x);
          tim[x] = 0;
          break;
        }
      }
    }
    
    // BFS to find minimum time to reach each node with different value
    while (q.size()) {
      int t = q.front();
      q.pop();
      for (int i = h[t]; ~i; i = ne[i]) {
        int j = e[i];
        if (tim[j] == INF && w[j] != w[t]) {
          tim[j] = tim[t] + 1;
          q.push(j);
        }
      }
    }
    
    ans = 0;
    dfs(st, 0, w[st], tim[st], 1, 1, 1);
    cout << ans + (dist[st] & 1) - 1 << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/