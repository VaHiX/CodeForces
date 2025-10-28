// Problem: CF 1906 J - Count BFS Graph
// https://codeforces.com/contest/1906/problem/J

/*
J. Count BFS Graph
time limit per test1 second
memory limit per test1024 megabytes

Algorithm: Dynamic Programming with Prefix Sums
Time Complexity: O(N^2)
Space Complexity: O(N^2)

This problem asks us to count the number of undirected simple graphs such that a given BFS traversal order is produced.
We use dynamic programming where f[i][j] represents the number of ways to assign edges to the first i nodes, where node j is the last visited node in the current BFS level.

The recurrence considers:
- If the current node a[i] > a[i - 1], it means we are continuing in the same BFS level, so we can connect with all previous unvisited nodes.
- Otherwise, we are moving to a new level, which affects how many edges could have been added from previous levels.

We use prefix sums for efficiency during computation.
*/

#include <stdio.h>
#include <iosfwd>

using namespace std;
const int N = 5010, mod = 998244353;
int f[N][N], a[N], P[N];

int main() {
  int n;
  scanf("%d", &n);
  P[0] = 1;
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    P[i] = 2 * P[i - 1] % mod; // Precompute powers of 2 modulo mod
  }
  f[2][1] = f[2][2] = 1; // Base cases for 2 nodes
  for (int i = 3; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      if (a[i] > a[i - 1])
        f[i][j] = 1ll * P[i - j - 1] * f[i - 1][j] % mod; // Continue in same level
      else
        f[i][j] = 1ll * P[i - j - 1] * f[i - 1][j - 1] % mod; // Move to new level
    }
    for (int j = 1; j <= i; j++)
      f[i][j] = (f[i][j] + f[i][j - 1]) % mod; // Prefix sum to support range queries
  }
  printf("%d\n", f[n][n]);
  return 0;
}


// https://github.com/VaHiX/codeForces/