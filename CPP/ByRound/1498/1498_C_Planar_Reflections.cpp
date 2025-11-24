// Problem: CF 1498 C - Planar Reflections
// https://codeforces.com/contest/1498/problem/C

/*
Code Purpose:
This program calculates the number of particles in the final multiset after a particle with decay age k is shot at n consecutive 2D planes.
Each plane produces a copy of the particle with decay age k-1 going in the opposite direction, unless the decay age is 1.
The solution uses dynamic programming where a[i][j] represents the number of particles with decay age i reaching the j-th plane from the left.

Algorithms/Techniques:
- Dynamic Programming
- Recurrence relation derived from the problem constraints

Time Complexity: O(k * n)
Space Complexity: O(k * n)
*/

#include <stdio.h>
#include <stdlib.h>
#include <iosfwd>

using namespace std;
int t, n, k, i, j, a[1008][1008];
int main() {
  for (scanf("%d", &t); t--; printf("%d\n", a[k][n]))
    for (scanf("%d%d", &n, &k), i = 0; i++ != k;)
      for (j = 0; j <= n;
           a[i][j] = (j ? a[i][j - 1] + a[i - 1][n - j] : 1) % 1000000007, ++j)
        ;
  exit(0);
}


// https://github.com/VaHiX/CodeForces/