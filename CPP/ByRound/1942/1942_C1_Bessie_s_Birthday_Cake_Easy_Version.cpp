// Problem: CF 1942 C1 - Bessie's Birthday Cake (Easy Version)
// https://codeforces.com/contest/1942/problem/C1

/*
Algorithm/Technique: 
The problem is about maximizing the number of non-intersecting triangles formed by choosing vertices of a polygon and drawing diagonals. 
The idea is to count the number of "gaps" of size 2 between selected vertices, as each such gap contributes to forming an additional triangle.
The sorting helps to determine contiguous segments and the gaps between consecutive selected vertices.
Time Complexity: O(x log x) due to sorting, where x is the number of preselected vertices.
Space Complexity: O(x) for storing the selected vertices and gaps.

*/
#include <algorithm>
#include <stdio.h>
using namespace std;
int kk[200010];  // Array to store the selected vertices
int fl[200010];  // Array to store the gaps between consecutive selected vertices
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, x, y;
    scanf("%d%d%d", &n, &x, &y);
    for (int i = 1; i <= x; i++) {
      scanf("%d", &kk[i]);
    }
    int sum = 0;
    sort(kk + 1, kk + 1 + x);  // Sort the selected vertices
    // Check if the polygon wraps around (1 and n-1, or 2 and n are both selected)
    if (kk[1] == 1 && kk[x] == n - 1)
      sum++;
    if (kk[1] == 2 && kk[x] == n)
      sum++;
    // Compute gaps between consecutive selected vertices
    for (int i = 2; i <= x; i++) {
      fl[i] = kk[i] - kk[i - 1];
      if (fl[i] == 2)
        sum++;  // A gap of 2 means we can form an extra triangle
    }
    // Output total number of triangles: (x - 2) for triangulation + extra triangles from gaps
    printf("%d\n", x - 2 + sum);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/