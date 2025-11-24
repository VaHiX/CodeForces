// Problem: CF 1790 F - Timofey and Black-White Tree
// https://codeforces.com/contest/1790/problem/F

/*
Purpose: Solve the problem of finding the minimum distance between pairs of black vertices after each operation of coloring a white vertex black in a tree.

Algorithm: 
- For each query, we maintain the minimum distances from each vertex to the set of previously colored black vertices.
- For each new black vertex, we traverse up the tree (using parent array) to update distances and find the current minimum distance between any two black vertices.
- We track the minimum distance encountered during traversal and update it accordingly.

Time Complexity: O(n) per test case, as each node is visited at most once during all operations combined.
Space Complexity: O(n), for storing the tree, parent information, and distance array.
*/

#include <stddef.h>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
#define endl '\n'
#define all(v) v.begin(), v.end()
#define rep(i, s, n) for (int i = s; i <= n; i++)
#define rev(i, n, s) for (int i = n; i >= s; i--)
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<vector<int>> vii;
const int inf = 1e9;
vii g;
vector<int> parent;

// DFS to compute parent of each node in the tree
void dfs(int u, int p = -1) {
  parent[u] = p;
  for (int v : g[u]) {
    if (v == p)
      continue;
    dfs(v, u);
  }
}

void solve_problem() {
  int n, c;
  cin >> n >> c;
  g.resize(n + 1);
  parent.resize(n + 1);
  for (int i = 0; i <= n; i++) {
    g[i].clear();
    parent[i] = -1;
  }
  vector<int> a(n - 1);
  for (int i = 0; i < n - 1; i++)
    cin >> a[i];
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(c); // Build parent array using DFS

  int ans = inf;
  vector<int> minD(n + 1, inf); // minD[i] stores the minimum distance from black vertices to vertex i
  minD[c] = 0; // distance from starting black vertex to itself is 0

  for (int i = 0; i < n - 1; i++) {
    int u = a[i]; // current white vertex to color black
    int dist = 0;
    // Traverse up the tree from u to update distances and compute current minimum distance between black vertices
    while (u != -1 && dist < ans) {
      ans = min(ans, dist + minD[u]); // update answer with distance between current vertex and closest black vertex
      minD[u] = min(minD[u], dist); // update minimum distance to this vertex
      dist += 1;
      u = parent[u]; // go to parent
    }
    cout << ans << " ";
  }
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  cout << fixed << showpoint;
  cout << setprecision(15);
  int test = 1;
  cin >> test;
  while (test--)
    solve_problem();
  return 0;
}


// https://github.com/VaHiX/CodeForces/