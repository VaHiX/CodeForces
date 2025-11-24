// Problem: CF 1272 E - Nearest Opposite Parity
// https://codeforces.com/contest/1272/problem/E

/*
E. Nearest Opposite Parity
Algorithms/Techniques: BFS on a graph built from jump rules, parity checking
Time Complexity: O(n)
Space Complexity: O(n)

The problem asks for the minimum number of moves to reach a position with opposite parity.
We build a directed graph where each node points to nodes reachable in one move (i-a[i] or i+a[i]).
Then we perform BFS starting from all nodes that can directly reach an opposite parity node,
with distance 1. Then we propagate distances using BFS.

*/
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
vector<int> g[200001]; // adjacency list for the graph
int a[200001], d[200001]; // array values and distances
int main() {
  ios::sync_with_stdio(false);
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    d[i] = -1;
    // Add edges to the graph: from i-a[i] to i and from i+a[i] to i
    if (i > a[i])
      g[i - a[i]].emplace_back(i);
    if (i + a[i] <= n)
      g[i + a[i]].emplace_back(i);
  }
  queue<int> q;
  // Initialize BFS with nodes that can directly reach opposite parity nodes
  for (int i = 1; i <= n; i++)
    for (int j : g[i])
      if ((a[i] ^ a[j]) & 1) // check if parity is different using XOR
        q.emplace(j), d[j] = 1;
  while (!q.empty()) {
    int t = q.front();
    q.pop();
    // BFS propagation
    for (int i : g[t])
      if (d[i] == -1)
        d[i] = d[t] + 1, q.emplace(i);
  }
  for (int i = 1; i <= n; i++)
    cout << d[i] << ' ';
  cout << endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/