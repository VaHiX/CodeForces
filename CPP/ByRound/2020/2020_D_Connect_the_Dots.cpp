// Problem: CF 2020 D - Connect the Dots
// https://codeforces.com/contest/2020/problem/D

/*
D. Connect the Dots
Time Complexity: O(n * log n + m * 10)
Space Complexity: O(n * 10)

Algorithms/Techniques:
- Union-Find (Disjoint Set Union) with path compression
- Graph connectivity problem
- Simulation of operations on segments

The code simulates connecting points in segments based on operations.
Each operation connects a sequence of points (a_i, a_i + d_i, ..., a_i + k_i * d_i) 
and updates the union-find structure accordingly. It uses path compression to
efficiently track connected components.

*/
#include <string.h>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;
#define N 300000
int i, j, k, n, m, t, fa[N + 50], f[N + 50][12], res;

// Find function with path compression for Union-Find
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (i = 1; i <= n; i++) {
      memset(f[i], 0, sizeof(f[i])); // Initialize segment values for point i
      fa[i] = i;                    // Each node is its own parent initially
    }
    while (m--) {
      cin >> i >> j >> k;
      f[i][j] = max(f[i][j], k); // Store maximum k for operation starting at i with step j
    }
    for (i = 1; i <= n; i++) {
      for (j = 1; j <= 10 && i + j <= n; j++)
        if (f[i][j]) {
          fa[find(i)] = find(i + j); // Union current point with point at i+j
          f[i + j][j] = max(f[i + j][j], f[i][j] - 1); // Propagate decrement
        }
    }
    res = 0;
    for (i = 1; i <= n; i++)
      res += (i == find(i)); // Count root nodes (components)
    cout << res << '\n';
  }
}


// https://github.com/VaHiX/codeForces/