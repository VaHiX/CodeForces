// Problem: CF 2032 D - Genokraken
// https://codeforces.com/contest/2032/problem/D

/*
 * Problem: D. Genokraken
 * 
 * Approach:
 * This solution reconstructs the tree structure by using binary search
 * to find parent-child relationships. The key insight is that we can
 * determine the parent of a node by querying paths involving the root.
 * 
 * Algorithm:
 * 1. Use binary search on the parent assignments.
 * 2. For each query, check if the path between two nodes includes the root.
 * 3. Based on the result, assign parents and adjust the search space.
 * 
 * Time Complexity: O(n log n) - due to binary search and multiple queries
 * Space Complexity: O(n) - for storing parent information
 *
 * The tree is structured such that removing the root breaks it into paths,
 * and node 1 has exactly two adjacent nodes (including root).
 */
#include <stdio.h>
#include <iosfwd>

using namespace std;
int a[1000010], p[1000010];
signed main() {
  int t, n;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    int l = n - 2, r = n - 1, o;
    for (int i = 1; i <= n; i++)
      p[i] = 0;
    while (l) {
      printf("? %d %d\n", l, r);
      fflush(stdout);
      scanf("%d", &o);
      if (o == 0)
        p[r] = l, r--;
      l--;
    }
    printf("! ");
    for (int i = 1; i <= n - 1; i++)
      printf("%d ", p[i]);
    printf("\n");
    fflush(stdout);
  }
}


// https://github.com/VaHiX/CodeForces/