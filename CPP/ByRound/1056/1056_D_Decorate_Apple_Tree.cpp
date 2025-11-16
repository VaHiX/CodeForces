// Problem: CF 1056 D - Decorate Apple Tree
// https://codeforces.com/contest/1056/problem/D

/*
D. Decorate Apple Tree
Algorithms/Techniques: Tree traversal, DFS, sorting
Time complexity: O(n log n)
Space complexity: O(n)

This problem involves finding the minimum number of colors needed to ensure 
at least k junctions are happy for each k from 1 to n. A junction is happy if 
all light bulbs in its subtree have different colors. We use a reverse approach:
- Process nodes from bottom to top (leaves to root)
- For each node, compute how many unique colors are needed in its subtree
- Sort the results and output them
*/

#include <stdio.h>
#include <algorithm>

#define mn 1111111
using namespace std;
int n, i = 2, a[mn], z[mn];

int main() {
  for (scanf("%d", &n); i <= n; i++)
    scanf("%d", a + i); // Read parent of each node
  for (i = n; i; i--) { // Traverse from leaves to root
    if (!z[i])
      z[i]++; // If not visited, mark as 1 (base case)
    z[a[i]] += z[i]; // Accumulate child's contribution to parent
  }
  sort(z + 1, z + 1 + n); // Sort the results
  for (i = 1; i <= n; i++)
    printf("%d ", z[i]); // Print minimum colors needed for each k
}


// https://github.com/VaHiX/codeForces/