// Problem: CF 2120 G - Eulerian Line Graph
// https://codeforces.com/contest/2120/problem/G

/*
G. Eulerian Line Graph

Purpose:
This code determines whether the k-th iterated line graph L^k(G) of a given simple connected graph G has an Eulerian trail.
An Eulerian trail exists in a graph if and only if:
- The graph is connected
- Every vertex has even degree (cycle), OR
- Exactly two vertices have odd degree (path).

Line graph properties used:
- L(G) is a graph where each vertex corresponds to an edge of G.
- An edge in L(G) connects two vertices if the corresponding edges in G share a vertex.
- For L^k(G), we compute iteratively applying line graph transformation.
- The key insight is that L^k(G) has an Eulerian trail iff the original graph G satisfies certain conditions related to degrees.

Algorithms:
1. Graph representation using adjacency lists.
2. Detection of Eulerian path in graph G and its line graphs using degree parity checks.
3. For k > 1, special handling based on properties of L^k(G).

Time Complexity:
O(n + m) per test case for preprocessing and checking each condition.

Space Complexity:
O(n + m) for storing the graph and auxiliary arrays.
*/

#include <stdint.h>
#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
int xx = 0;

void solve() {
  xx++;
  int n, m, k;
  cin >> n >> m >> k;
  vector<vector<int>> arr(n);
  vector<array<int, 2>> edges(m);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    --a;
    --b;
    arr[a].push_back(b); // Add edge to adjacency list
    arr[b].push_back(a);
    edges[i] = {a, b};
  }
  
  function<bool()> cyc = [&]() {
    int odd = 0; // Count of vertices with odd degree
    for (int i = 0; i < n; i++) {
      odd += arr[i].size() % 2;
    }
    if (odd == 0)
      return true;
    // If all degrees are even -> Eulerian cycle exists
    for (int i = 0; i < n; i++) {
      for (int x : arr[i]) {
        // Check condition for special case involving neighbor's degree difference
        if ((arr[i].size() - 1) % 2 == (arr[x].size() - 1) % 2) {
          return false;
        }
      }
    }
    if (k >= 2)
      return true; // For k>=2, L^k(G) is Eulerian unless forbidden configuration encountered
    return false;
  };

  function<bool()> oth = [&]() {
    int f, s;
    f = s = -1;
    for (int i = 0; i < n; i++) {
      if (arr[i].size() % 2) { // Find first and second vertex with odd degree
        s = (f != -1 ? i : s);
        f = (f == -1 ? i : f);
      }
    }
    int a1, a2;
    a1 = a2 = 0;
    function<int(int u, int p)> calc = [&](int u, int p) {
      if (arr[u].size() > 2)
        return 0; // Non-simple tree check
      return 1 + (arr[u][0] == p ? calc(arr[u][1], u) : calc(arr[u][0], u)); // DFS to get length of chain
    };
    a1 = calc(f, -1);
    a2 = calc(s, -1);

    if (a1 > a2) {
      swap(a1, a2);
      swap(f, s);
    }
    if (a1 >= k)
      return true;
    // Special long chain check
    if (a1 > 0)
      return false;
    
    // Case: short chains ending in 3-degree node
    if (a2 == 1 && arr[s].size() == 3 && arr[f][0] == s) {
      return k == 1;
    }

    // Handle remaining small cases
    if (k >= 3 || k == 1)
      return false;
    
    ll cnt = 0;
    vector<array<int, 2>> val(n);
    for (int i = 0; i < m; i++) {
      // Count pairs of edges with same parity in neighbor degree counts
      val[edges[i][0]][arr[edges[i][1]].size() % 2]++;
      val[edges[i][1]][arr[edges[i][0]].size() % 2]++;
    }
    for (int i = 0; i < n; i++)
      cnt += (1ll * val[i][0] * val[i][1]); // Multiply matching degrees
    
    return cnt == 2; // Special check from the problem
  };

  cout << (cyc() || oth() ? "YES\n" : "NO\n");
}

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/codeForces/