// Problem: CF 1496 F - BFS Trees
// https://codeforces.com/contest/1496/problem/F

/*
F. BFS Trees
time limit per test
2.5 seconds
memory limit per test
512 megabytes
input
standard input
output
standard output

We define a spanning tree of a graph to be a BFS tree 
rooted at
 vertex $$$s$$$ if and only if for every node $$$t$$$ the shortest distance between $$$s$$$ and $$$t$$$ in the graph is equal to the shortest distance between $$$s$$$ and $$$t$$$ in the spanning tree. 
Given a graph, we define $$$f(x,y)$$$ to be the number of spanning trees of that graph that are BFS trees rooted at vertices $$$x$$$ and $$$y$$$ at the same time.
You are given an undirected connected graph with $$$n$$$ vertices and $$$m$$$ edges. Calculate $$$f(i,j)$$$ for all $$$i$$$, $$$j$$$ by modulo $$$998\,244\,353$$$.

Algorithms/Techniques:
- BFS to compute shortest distances
- Preprocessing parent relationships in BFS tree
- Dynamic counting of valid spanning trees using adjacency and distance checks

Time Complexity: O(n^3)
Space Complexity: O(n^2)

*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int MAXN = 500, MOD = 998244353;
int n, m, dis[MAXN][MAXN];
long long answer[MAXN][MAXN];
vector<int> adj[MAXN], par[MAXN][MAXN];
queue<int> q;

// Function to compute all-pairs shortest distances and parent relationships
void dist() {
  for (int i = 1; i <= n; i++) {
    q.push(i);
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (auto u : adj[v]) {
        // If not visited, mark and push to queue
        if (u != i && dis[i][u] == 0) {
          q.push(u);
          dis[i][u] = dis[i][v] + 1;
        }
        // If this is a valid parent in BFS tree, add to par array
        if (dis[i][u] == dis[i][v] + 1)
          par[i][u].push_back(v);
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  while (m--) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dist(); // Compute all distances and parent relationships

  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      int sp = 0;
      // Count how many intermediate nodes satisfy the triangle inequality
      for (int k = 1; k <= n; k++) {
        if (dis[i][k] + dis[k][j] == dis[i][j] && k != i && k != j)
          sp++;
      }
      long long ans = 1;
      // If too many intermediate nodes, no valid tree exists
      if (sp > dis[i][j] - 1 && i != j)
        ans = 0;
      
      for (int k = 1; k <= n; k++) {
        if (ans == 0) break; // Early termination
        // If k lies on the shortest path between i and j, update answer
        if (dis[i][j] != dis[i][k] + dis[j][k]) {
          int t = 0;
          for (auto u : par[i][k]) {
            // Count how many parents u of k have a shorter distance to j
            if (dis[j][k] == dis[j][u] + 1)
              t++;
          }
          ans = ans * t % MOD; // Multiply by number of valid choices
        }
      }
      answer[i][j] = answer[j][i] = ans;
    }
  }
  
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++)
      cout << answer[i][j] << ' ';
    cout << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/