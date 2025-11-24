// Problem: CF 2172 M - Maximum Distance To Port
// https://codeforces.com/contest/2172/problem/M

/*
 * Problem: M. Maximum Distance To Port
 * 
 * Purpose: Given a graph of cities connected by roads, each city produces one of k agricultural products.
 *          Find the maximum shortest distance from any city producing a specific product type to the port city (city 1).
 * 
 * Algorithms/Techniques:
 *   - BFS (Breadth-First Search) to compute shortest distances from port (city 1) to all other cities
 *   - For each product type, track the maximum distance among all cities producing that product
 * 
 * Time Complexity: O(n + m) where n is number of cities and m is number of roads.
 * Space Complexity: O(n + m) for adjacency list and auxiliary arrays.
 * 
 * Input:
 *   - n: number of cities
 *   - m: number of roads
 *   - k: number of product types
 *   - arr[i]: product type of city i
 *   - m lines of u v representing bidirectional roads
 * 
 * Output:
 *   - k integers representing max shortest distance for each product type to port
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
const int N = 2e5 + 10;
int arr[N];
vector<int> g[N];
int n, m, k;
int ans[N];
int d[N];
queue<int> q;
bool st[N];

// BFS from city v to compute shortest distances to all reachable cities
void bfs(int v, int x) {
  q.push(v);
  st[v] = 1;
  d[v] = 0;
  while (q.size()) {
    int t = q.front();
    q.pop();
    for (int &i : g[t]) {
      if (st[i])
        continue;
      d[i] = d[t] + 1;
      q.push(i);
      st[i] = 1;
    }
  }
}

int main() {
  cin >> n >> m >> k;
  for (int i = 1; i <= n; i++)
    cin >> arr[i];
  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  bfs(1, 0); // Run BFS from the port (city 1)
  for (int i = 1; i <= n; i++)
    ans[arr[i]] = max(ans[arr[i]], d[i]); // Update max distance for product type
  for (int i = 1; i <= k; i++)
    cout << ans[i] << " ";
  return 0;
}


// https://github.com/VaHiX/CodeForces/