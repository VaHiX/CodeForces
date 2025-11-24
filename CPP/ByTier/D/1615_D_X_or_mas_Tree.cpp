// Problem: CF 1615 D - X(or)-mas Tree
// https://codeforces.com/contest/1615/problem/D

/*
Algorithm: 
This problem involves determining if a set of XOR constraints on paths in a tree can be satisfied by assigning values to edges that are not known. 
The approach uses Union-Find (Disjoint Set Union) to model the XOR constraints as a system of equations over GF(2) (binary field).
Each node and its "negation" are represented as two separate nodes in the Union-Find structure (node i and node i+n). 
The XOR constraints between two nodes are modeled as linking node i to node j+n or vice versa.

Time Complexity: O(n * α(n) + m * α(n)) where α is the inverse Ackermann function, nearly constant.
Space Complexity: O(n)

Flow of Logic:
1. For each known edge (v != -1), compute its parity and union corresponding nodes.
2. For each query (elf), union accordingly based on parity (0 means same parity, 1 means different).
3. If any node is connected to its negation, no solution exists.
4. Assign values to unknown edges such that constraints are satisfied.

Techniques:
- Union-Find with path compression
- XOR parity checking
- Graph representation via edges
*/

#include <stdio.h>
#include <iostream>

using namespace std;
const int M = 200005, N = M * 2;
int t, n, m, u[N], v[N], w[N], f[N], d[N];  // f = Union-Find, d = assignment flags

// Find with path compression
int fd(int x) { return f[x] == x ? x : f[x] = fd(f[x]); }

// Union two sets
void add(int x, int y) { f[fd(x)] = fd(y); }

// Links nodes based on the expected XOR parity (0 = same, 1 = different)
void link(int x, int y, int z) {
  if (z == 0) // same parity
    add(x, y), add(x + n, y + n);
  if (z == 1) // different parity
    add(x, y + n), add(x + n, y);
}

// Count number of set bits (parity)
int bt(int k) {
  int s = 0;
  for (int i = 0; i < 30; i++)
    s ^= k >> i & 1;
  return s;
}

// Output the solution if consistent
void print() {
  for (int i = 1; i <= n; i++)
    if (fd(i) == fd(i + n)) { // Check for contradiction
      puts("NO");
      return;
    } else
      d[i] = fd(i) > n ? d[i] = 1 : d[i] = 0; // Assign values to nodes
  puts("YES");
  for (int i = 1; i < n; i++)
    // Output the value of edges, using the computed node assignments for unknown edges
    cout << u[i] << ' ' << v[i] << ' ' << (~w[i] ? w[i] : d[u[i]] ^ d[v[i]])
         << '\n';
}

int main() {
  int x, y, z;
  for (cin >> t; t; t--) {
    cin >> n >> m;
    for (int i = 1; i <= n * 2; i++)
      f[i] = i, d[i] = 0; // Reset Union-Find and assignment array
    for (int i = 1; i < n; i++) {
      scanf("%d%d%d", &x, &y, &z);
      u[i] = x;
      v[i] = y;
      w[i] = z;
      if (~z) // If edge weight is known
        link(x, y, bt(z)); // Process known edge constraint
    }
    while (m--) { // Process all queries
      scanf("%d%d%d", &x, &y, &z);
      link(x, y, z); // Apply query constraint
    }
    print(); // Print result
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/