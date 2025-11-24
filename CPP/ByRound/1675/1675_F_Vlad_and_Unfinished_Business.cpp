// Problem: CF 1675 F - Vlad and Unfinished Business
// https://codeforces.com/contest/1675/problem/F
 
/*
Code Purpose:
This program solves the problem of finding the minimum time Vlad needs to complete all his tasks and visit Nastya in a tree-like city. The key idea is to find the shortest path visiting specific nodes (tasks) and then going to Nastya's house, using DFS to build a tree structure and mark nodes that need to be visited.
 
Algorithms/Techniques:
- Tree traversal using DFS to build parent relationships.
- Greedy marking of nodes to minimize redundant paths.
- Path compression through parent tracking to determine which edges are needed.
 
Time Complexity: O(n + k)
Space Complexity: O(n)
 
*/
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
 
using namespace std;
const int N = 2e5 + 2;
int b[N], f[N]; // b: marks nodes that need to be visited; f: parent array for DFS
vector<int> e[N]; // adjacency list for the tree
 
void dfs(int u) {
  // DFS to build parent relationships in the tree
  for (int v : e[u])
    if (v != f[u]) // avoid going back to parent
      f[v] = u, dfs(v); // set parent and recurse
}
 
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n, m, i, j, x, y;
    cin >> n >> m >> x >> y; // n: houses, m: tasks, x: Vlad's house, y: Nastya's house
    fill_n(b + 1, n, 0); // reset the marking array
    fill_n(f + 1, n, 0); // reset the parent array
    for (i = 1; i <= n; i++)
      e[i].clear(); // clear adjacency list
    vector<int> a(m); // store task locations
    for (int &u : a)
      cin >> u;
    for (i = 1; i < n; i++) {
      int u, v;
      cin >> u >> v;
      e[u].push_back(v);
      e[v].push_back(u);
    }
    dfs(x); // build the tree starting from Vlad's house
    
    // Mark tasks that are not already on the path to Vlad's house
    for (int u : a)
      while (u != x && !b[u]) // if not visited and not in the path to Vlad's house
        b[u] = 2, u = f[u]; // mark as needed and move to parent
    
    // Mark path to Nastya's house
    while (y != x)
      b[y] = 1, y = f[y]; // mark path nodes
    
    // Sum up all marked nodes, each marked means 1 edge traversal
    cout << accumulate(b + 1, b + n + 1, 0) << '\n';
  }
}
 
 
// https://github.com/VaHiX/CodeForces/