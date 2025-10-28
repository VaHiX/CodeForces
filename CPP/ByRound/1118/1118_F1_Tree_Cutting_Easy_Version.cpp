// Problem: CF 1118 F1 - Tree Cutting (Easy Version)
// https://codeforces.com/contest/1118/problem/F1

/*
F1. Tree Cutting (Easy Version)
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

Task: Count the number of "nice" edges in a tree, where an edge is nice if removing it splits the tree into two components such that each component contains only one color (red or blue).

Algorithms/Techniques:
- Tree DFS traversal
- Subtree coloring counts
- Edge cut validation by checking subtree color distributions

Time Complexity: O(n)
Space Complexity: O(n)

*/

#include <stdio.h>
#include <iosfwd>

using namespace std;
const int N = 300002;
struct node {
  int to, ne;
} e[N << 1]; // adjacency list for tree edges
int n, i, sum1, sum2, s1[N], s2[N], x, y, h[N], a[N], ans, tot;

// Add an edge to the adjacency list
void add(int x, int y) { e[++tot] = (node){y, h[x]}, h[x] = tot; }

// DFS traversal to compute subtree color counts and count nice edges
void dfs(int u, int fa) {
  s1[u] = a[u] == 1, s2[u] = a[u] == 2; // initialize with own color count
  for (int i = h[u], v; i; i = e[i].ne)
    if ((v = e[i].to) != fa) {
      dfs(v, u), s1[u] += s1[v], s2[u] += s2[v]; // accumulate child counts
      
      // Check if the edge from u to v is nice
      if (s1[v] == sum1 && !s2[v] || s2[v] == sum2 && !s1[v])
        ans++;
    }
}

int main() {
  scanf("%d", &n);
  for (i = 1; i <= n; i++)
    scanf("%d", &a[i]), sum1 += a[i] == 1, sum2 += a[i] == 2;
  for (i = 1; i < n; i++)
    scanf("%d%d", &x, &y), add(x, y), add(y, x); // build the tree
  dfs(1, 0);
  printf("%d", ans);
}


// https://github.com/VaHiX/codeForces/