// Problem: CF 1976 F - Remove Bridges
// https://codeforces.com/contest/1976/problem/F

/*
  Problem: F. Remove Bridges
  Purpose: Optimally add k edges to a tree to minimize the number of bridges for each k from 1 to n-1.
  
  Algorithm:
  1. Process the tree using DFS to compute the "depth" information for each node.
  2. For each node, sort the depths of its children in descending order.
  3. The maximum depth among all children determines the number of bridges from this node.
  4. Store the depths of children in a separate array.
  5. After DFS, sort all child depths and greedily assign edges to minimize the number of bridges.

  Time Complexity: O(n log n) per test case due to sorting operations.
  Space Complexity: O(n) for storing the tree structure and auxiliary arrays.

  Techniques:
  - DFS traversal on tree
  - Greedy assignment of edges
  - Sorting for optimal assignment
*/

#include <stdio.h>
#include <algorithm>

#define up(i, l, r) for (int i = l, END##i = r; i <= END##i; i++)
#define dn(i, l, r) for (int i = l, END##i = r; i >= END##i; i--)
typedef long long i64;
typedef unsigned long long u64;
typedef double db;
using namespace std;
const int INF = 0x3f3f3f3f, N = 3e5 + 7;

struct e {
  int nxt, to;
} a[N << 1];  // Edge list to store the tree
int head[N], tot;  // Head of adjacency list and edge counter

// Function to add an edge to the adjacency list
void add(int x, int y) { a[++tot].to = y, a[tot].nxt = head[x], head[x] = tot; }

int n, m, o[N], f[N], t[N];  // Variables for DFS processing

// DFS to calculate depth information and update bridge counts
void dfs(int x, int fa) {
  for (int i = head[x], to; i; i = a[i].nxt)
    if ((to = a[i].to) != fa)
      dfs(to, x);
  int p = 0;
  for (int i = head[x], to; i; i = a[i].nxt)
    if ((to = a[i].to) != fa)
      t[++p] = f[to] + 1;  // Store depths of children (+1 to account for current node)
  sort(t + 1, t + p + 1, [](int x, int y) { return x > y; });  // Sort depths in descending order
  if (x == 1) {
    o[++m] = t[1];  // For root, store the first value for output
    return;
  }
  if (!p) {
    f[x] = 0;  // No children, so no bridges from this node
    return;
  }
  f[x] = t[1];  // Maximum depth among children determines the number of bridges
  up(i, 2, p) o[++m] = t[i];  // Store remaining depths for later processing
}

namespace sol {
i64 read() {
  i64 f = 0, x = 0;
  char c = getchar();
  while (c < '0' || c > '9')
    f |= c == '-', c = getchar();
  while (c >= '0' && c <= '9')
    x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
  return f ? -x : x;
}
void write(i64 x) {
  if (x < 0)
    putchar('-'), x = -x;
  if (x > 9)
    write(x / 10);
  putchar(x % 10 + '0');
}

// Main solution function
void Dianaqaq() {
  n = read(), m = 0;
  up(i, 2, n) {
    int x = read(), y = read();
    add(x, y), add(y, x);  // Add bidirectional edges to the tree
  }
  dfs(1, 0);  // Start DFS from root
  sort(o + 1, o + m + 1, [](int x, int y) { return x > y; });  // Sort all child depths
  int nw = n - 1;  // Initially, all edges are bridges
  up(i, 1, n * 2 - 3) {
    if (i <= m)
      nw -= o[i];  // Remove edges that are no longer bridges due to added edges
    if (i & 1)  // Only print odd values of i (k from 1 to n-1)
      write(nw), putchar(' ');
  }
  puts("");  // Print newline
  up(i, 1, tot) a[i].nxt = a[i].to = 0;  // Clear edge list
  up(i, 1, n) head[i] = 0;  // Clear adjacency list
  tot = 0;
}
} // namespace sol

using namespace sol;

// Main function to read test cases and solve them
signed main() {
  int T = read();
  while (T--)
    Dianaqaq();
  return 0;
}


// https://github.com/VaHiX/CodeForces/