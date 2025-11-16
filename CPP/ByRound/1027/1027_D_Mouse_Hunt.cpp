// Problem: CF 1027 D - Mouse Hunt
// https://codeforces.com/contest/1027/problem/D

/*
D. Mouse Hunt
Algorithms/Techniques: Graph traversal (cycle detection), Minimum cost to cover all cycles

Time Complexity: O(n)
Space Complexity: O(n)

The problem models a directed graph where each node points to another node (a[i] represents the next room).
Each connected component contains at least one cycle. To guarantee catching the mouse, we must place traps
in such a way that every possible path eventually leads to a trap.

This is done by finding all cycles and placing a trap in the cheapest node of each cycle.
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
int n, a[200010], c[200010], vis[200010], ans;

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &c[i]); // Read cost of setting trap in each room
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]); // Read where mouse goes from each room

  // Traverse all unvisited nodes to find cycles
  for (int i = 1; i <= n; i++)
    if (!vis[i]) { // If not visited yet
      int u = i, res, t;
      // Find the cycle starting from node i
      while (!vis[u]) {
        vis[u] = i; // Mark this node as part of current component
        u = a[u];   // Move to next node in the path
      }
      
      if (vis[u] != i)
        continue; // If already visited by another component, skip

      t = u;
      res = c[u]; // Initialize minimum cost with cost of starting node
      while (a[u] != t) { // Traverse the cycle to find the minimum cost
        u = a[u];
        res = min(res, c[u]); // Keep track of minimum cost in the cycle
      }
      ans += res; // Add minimum cost of this cycle to total answer
    }
  printf("%d", ans);
  return 0;
}


// https://github.com/VaHiX/codeForces/