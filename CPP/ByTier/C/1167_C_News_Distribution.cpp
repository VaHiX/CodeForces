// Problem: CF 1167 C - News Distribution
// https://codeforces.com/contest/1167/problem/C

/*
C. News Distribution
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

Algorithm: Union-Find (Disjoint Set Union)
Purpose: To find the connected component size for each node in a graph where nodes are connected if they belong to the same group.

Time Complexity: O(N * α(N) + M * K) where α is the inverse Ackermann function, nearly constant.
Space Complexity: O(N)

The problem models groups of friends as connected components. For each user,
we want to know how many users will receive the news if that user starts it.
This is equivalent to finding the size of the connected component containing that user.

*/

#include <cstdio>
const int N = 5e5 + 50;
int n, m, k, x, y, fa[N], siz[N];

// Find root with path compression
int fd(int u) { return fa[u] = (fa[u] == u ? u : fd(fa[u])); }

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++)
    fa[i] = i; // Initialize each node as its own parent
  
  for (int i = 1; i <= m; i++) {
    scanf("%d", &k); // Read number of users in current group
    if (k) {
      scanf("%d", &x); // Read first user in group
      x = fd(x); // Find root of first user
      for (int j = 1; j < k; j++) {
        scanf("%d", &y); // Read next user in group
        y = fd(y); // Find root of next user
        fa[y] = x; // Union: make root of y point to root of x
      }
    }
  }
  
  // Count size of each connected component
  for (int i = 1; i <= n; i++)
    siz[fd(i)]++; // Increment count for the root of component containing i
  
  // Output the size of component each node belongs to
  for (int i = 1; i <= n; i++)
    printf("%d ", siz[fa[i]]); // Print size of component for user i
    
  return 0;
}


// https://github.com/VaHiX/codeForces/