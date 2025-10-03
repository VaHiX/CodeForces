// Problem: CF 2122 D - Traffic Lights
// https://codeforces.com/contest/2122/problem/D

/*
D. Traffic Lights
Algorithm: Shortest Path with a twist - The graph is traversed using a state transition where each node has a specific edge to traverse based on the current time step modulo the number of edges of that node.
Time Complexity: O((n + m) * T) where T is the maximum possible time (up to 1e9 in worst case), but optimized by early exit condition. In practice, this is small due to graph structure and early termination.
Space Complexity: O(n + m) for storing the adjacency list.

The problem involves a token moving through a graph with special movement rules:
- At each second t, you can either wait or move along a specific edge determined by (t mod deg(u) + 1).
- Movement takes 1 second.
We are to find the minimum total time and also minimize waiting time under that constraint.

The solution uses BFS-like approach with states tracking min cost to reach node i at time T:
- At each step, we try moving from all nodes using their edge in order (indexed by current time modulo edge count).
- A state is tracked as f[i] = minimum time to reach node i with no waiting.
- g[i] is a temporary array for next time step states.
- Early termination: when f[n] < f[0], it means we've found the minimum path, break the loop.
*/

#include <string.h>
#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <string>

using namespace std;
#define ll long long
using vi = basic_string<int>;
const ll N = 5000;
int i, j, k, n, m, t, f[N + 50], g[N + 50];
vi v[5005];
void solve() {
  fill(f, f + n + 1, int(1e9)); // Initialize all distances to infinity
  f[1] = 0;                     // Start from node 1 with time 0
  for (int T = 0;; T++) {
    if (f[n] < f[0]) {          // If destination is reachable faster than starting point, exit
      cout << T << ' ' << f[n] << '\n';
      break;
    }
    for (i = 1; i <= n; i++)
      g[i] = f[i] + 1;         // Assume waiting one second from each node
    for (i = 1; i <= n; i++) {
      k = v[i][T % v[i].size()]; // Get the next edge index using time modulo edge count
      g[k] = min(g[k], f[i]);   // Move to adjacent node without waiting, update state
    }
    memcpy(f, g, n * 4 + 50);   // Copy next states to current, with some padding
    f[0] = 1e9;                 // Reset the initial node for comparison check
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> t;
  while (t--) {
    cin >> n >> m;
    while (m--) {
      cin >> i >> j;
      v[i] += j;   // Build adjacency list for node i
      v[j] += i;   // Add reverse edge since undirected graph
    }
    solve();
    for (i = 1; i <= n; i++)
      v[i] = {};   // Clear adjacency lists after each test case
  }
}


// https://github.com/VaHiX/codeForces/