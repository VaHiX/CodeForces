// Problem: CF 1387 A - Graph
// https://codeforces.com/contest/1387/problem/A

/*
Algorithm: 
This problem is a system of linear equations with constraints on the sums of variables at endpoints of edges, 
and we want to minimize the sum of absolute values of the variables. 
We model it as a graph coloring problem:
- Each edge has a constraint: sum of endpoint values equals a target (1 for black, 2 for red)
- We assign signs to variables (coefficients) and solve for values that satisfy all equations.
- A DFS is used to traverse components and detect inconsistencies in the system.
- For each connected component, we determine the correct assignment using median trick for minimizing sum of absolute values.

Time Complexity: O(N + M) - Each node and edge processed once in DFS traversal.
Space Complexity: O(N + M) - For adjacency list and auxiliary arrays.
*/

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;
#define pii pair<int, int>
#define fi first
#define se second
#define rep(i, j, k) for (int i = (j); i <= (k); i++)
#define per(i, j, k) for (int i = (j); i >= (k); i--)
const int N = 114514;
vector<pii> e[N]; // Adjacency list to store edges with color encoded as 2*c
int n, m, a[N], k[N], g[N], v[N], s[N], as[N], fl, po, x, y, z, kx;

// DFS to traverse component and check consistency
void dfs(int x) {
  v[x] = 1; // Mark node as visited
  s[++po] = x; // Store node in current component
  int y;
  // Iterate over all neighbors of x
  for (pii w : e[x])
    if (v[y = w.fi]) { // If neighbor y is already visited
      // Check for inconsistency in constraint
      if (a[x] + a[y] == 0 && k[x] + k[y] != w.se)
        puts("NO"), exit(0);
      // If a[x] == a[y], we have linear dependency - compute common value
      if (a[x] == a[y]) {
        int nk = (w.se - k[x] - k[y]) / (a[x] + a[y]); // Compute consistent value
        if (fl && nk != kx) // If already set and inconsistent
          puts("NO"), exit(0);
        else
          fl = 1, kx = nk; // Set consistent value
      }
    } else { // If neighbor is not visited
      a[y] = -a[x]; // Assign opposite coefficient
      k[y] = w.se - k[x]; // Compute constant term
      dfs(y); // Recursive DFS
    }
}

int main() {
  scanf("%d%d", &n, &m);
  // Read edges and build adjacency list
  rep(i, 1, m) scanf("%d%d%d", &x, &y, &z), z *= 2, e[x].push_back({y, z}), e[y].push_back({x, z});
  
  // Process each connected component
  rep(i, 1, n) if (!v[i]) {
    a[i] = 1; // Start with coefficient 1
    kx = k[i] = fl = po = 0; // Initialize vars
    dfs(i); // Traverse component
    
    // If no fixed value determined yet (kx=0), compute it using median of g[] values
    if (!kx) {
      rep(i, 1, po) g[i] = -k[s[i]] / a[s[i]]; // Compute g values
      sort(g + 1, g + po + 1); // Sort to find median
      kx = g[(po + 1) / 2]; // Pick median
    }
    
    // Assign final values to variables
    rep(i, 1, po) as[s[i]] = kx * a[s[i]] + k[s[i]];
  }
  
  puts("YES");
  rep(i, 1, n) printf("%.2lf ", 0.5 * as[i]); // Print result with 2 decimal precision
}


// https://github.com/VaHiX/CodeForces/