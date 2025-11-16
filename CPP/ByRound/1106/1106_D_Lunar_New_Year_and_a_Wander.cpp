// Problem: CF 1106 D - Lunar New Year and a Wander
// https://codeforces.com/contest/1106/problem/D

/*
 * Problem: D. Lunar New Year and a Wander
 * Algorithm: BFS with priority queue (min-heap) to ensure lexicographically smallest traversal
 * Time Complexity: O((n + m) log n) - Each node is pushed and popped from the priority queue once, 
 *                    and each edge is processed once.
 * Space Complexity: O(n + m) - For adjacency list representation of graph and auxiliary arrays.
 */

#include <stdio.h>
#include <algorithm>
#include <functional>
#include <queue>
#include <vector>

using namespace std;
int n, m;
bool inq[100005]; // Tracks visited nodes
vector<int> g[100005]; // Adjacency list representation of the graph

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, u, v; i <= m; i++) {
    scanf("%d%d", &u, &v);
    g[u].push_back(v), g[v].push_back(u); // Build bidirectional graph
  }
  priority_queue<int, vector<int>, greater<int>> q; // Min-heap to always pick smallest unvisited node
  q.push(1), inq[1] = true; // Start from node 1
  for (int i = 1; i <= n; i++) {
    int x = q.top(); // Get the smallest unvisited node
    q.pop();
    printf("%d ", x);
    for (int v : g[x]) // For each neighbor
      if (!inq[v]) // If not visited yet
        q.push(v), inq[v] = true; // Add to queue and mark as visited
  }
}


// https://github.com/VaHiX/codeForces/