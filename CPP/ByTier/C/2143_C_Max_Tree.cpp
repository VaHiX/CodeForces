// Problem: CF 2143 C - Max Tree
// https://codeforces.com/contest/2143/problem/C

/*
C. Max Tree
Algorithms/Techniques: Topological sorting with greedy assignment based on edge weights.

Time Complexity: O(n) per test case, where n is the number of vertices.
Space Complexity: O(n) for storing adjacency list and auxiliary arrays.

This solution uses a topological sort approach on the tree. For each edge (u, v),
we orient it from u to v if w1 >= w2, otherwise from v to u. This ensures that
the higher weight is preferentially assigned to the node that will have a larger
value in the permutation. We then perform topological sorting and assign values
in order of the topological sequence to maximize contribution.
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
vector<int> Map[200005]; // Adjacency list for the tree
int du[200005], ans[200005]; // In-degree array and answer array
queue<int> que; // Queue for topological sort

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T, n, t;
  cin >> T;
  while (T--) {
    cin >> n;
    t = 0;
    for (int i = 1; i <= n; i++)
      du[i] = 0; // Reset in-degrees
    for (int i = 1, a, b, w1, w2; i < n; i++) {
      cin >> a >> b >> w1 >> w2;
      if (w1 < w2)
        swap(a, b); // Direct edge from higher weight to lower
      du[a]++; // Increment in-degree of parent node
      Map[b].push_back(a); // Add child to adjacency list
    }
    for (int i = 1; i <= n; i++)
      if (!du[i]) // If in-degree is zero, it's a leaf node
        ans[i] = ++t, que.push(i); // Assign rank and push to queue
    
    while (!que.empty()) {
      int u = que.front();
      que.pop();
      for (auto v : Map[u]) { // For each predecessor of u
        du[v]--; // Decrement in-degree
        if (!du[v]) // If in-degree becomes zero
          ans[v] = ++t, que.push(v); // Assign rank and push to queue
      }
    }
    for (int i = 1; i <= n; i++)
      cout << ans[i] << " ", Map[i].clear(); // Output result and clear adjacency list
    cout << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/