// Problem: CF 1253 D - Harmonious Graph
// https://codeforces.com/contest/1253/problem/D

/* 
D. Harmonious Graph
Algorithms/Techniques: Union-Find (Disjoint Set Union), Greedy
Time Complexity: O(n + m * α(n)) where α is the inverse Ackermann function
Space Complexity: O(n)

The problem asks to find the minimum number of edges to add so that for any triple (l, m, r) with l < m < r,
if there's a path from l to r, then there must also be a path from l to m.
This property can be checked by ensuring that in each connected component, all nodes between any two nodes
in the component are also reachable.

The solution uses Union-Find to manage connected components:
1. First union all existing edges to form components.
2. Then iterate through nodes and ensure that for every node, 
   all intermediate nodes can be reached from the start of the current component.
3. Count required edges to make this property true.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
const int N = 2e5 + 10;
int n, m, res, f[N], j = 1;
int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); } // Find root with path compression
void merge(int x, int y) {
  x = find(x);
  y = find(y);
  f[min(x, y)] = max(x, y); // Merge smaller root into larger one
}
signed main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    f[i] = i; // Initialize each node as its own parent
  for (int i = 1, a, b; i <= m; i++)
    scanf("%d %d", &a, &b), merge(a, b); // Union all existing edges
  for (int i = 1; i < n; i++) {
    int r = find(i);
    for (; j <= r; j++) { // Iterate from current pointer to end of component
      if (find(j) != find(i)) // If current node is not in same component
        merge(j, r), res++; // Merge and increment edge count
    }
    if (j < r + 1) // Adjust pointer if needed
      j = r + 1;
  }
  cout << res << endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/