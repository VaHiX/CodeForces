// Problem: CF 1143 C - Queen
// https://codeforces.com/contest/1143/problem/C

/*
C. Queen
Algorithms/Techniques: Tree traversal, simulation with deletion criteria.
Time Complexity: O(n)
Space Complexity: O(n)

The problem involves a rooted tree where each vertex either respects or doesn't respect its ancestors.
We simulate the deletion process by repeatedly finding the smallest indexed vertex that:
1. Does not respect its parent (c[i] == 0)
2. None of its children respect it
When a vertex is deleted, its children are connected to its parent.

The algorithm uses a marking approach to track which vertices can be deleted in each step.
*/

#include <stdio.h>
#include <string.h>
#include <iosfwd>

using namespace std;
int a[100009]; // Array to mark vertices that can be deleted (1) or not (0)
int main() {
  int n, i, j, k;
  scanf("%d", &n), memset(a, 1, sizeof a); // Initialize all vertices as potentially deletable
  for (i = 1; i <= n; ++i) {
    scanf("%d%d", &j, &k);
    if (j == -1)
      j = 0; // Root's parent is represented as 0
    if (!k) {
      a[i] = a[j] = 0; // Mark vertex i and its parent j as not deletable
    }
  }
  k = 0;
  for (i = 1; i <= n; ++i)
    if (a[i])
      printf("%d ", i), k = 1; // Print all vertices marked as deletable
  if (!k)
    puts("-1"); // No deletable vertices found
  return 0;
}


// https://github.com/VaHiX/codeForces/