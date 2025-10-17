// Problem: CF 2004 D - Colored Portals
// https://codeforces.com/contest/2004/problem/D

/*
D. Colored Portals
Algorithms/Techniques: Preprocessing with left and right arrays to calculate maximum consecutive segments of same or complementary colors.
Time Complexity: O(n + q) per test case, where n is number of cities and q is number of queries.
Space Complexity: O(n) for storing color mappings and auxiliary arrays.

Each city has two portals of different colors. Movement is allowed between cities if they share a common color.
The minimum cost to move from x to y is the distance |x - y| unless we can use a chain of same/complementary color portals
which would offer shorter paths in special cases.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>

using namespace std;
const int _ = 2e5 + 5;
int n, m;
int z[_], l[_], r[_]; // z stores color codes, l[i] max consecutive left same/compl., r[i] max consecutive right
map<string, int> to;  // Maps portal color combinations to unique integers

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  // Mapping of portal types to integer codes for fast comparison
  to["BG"] = 1, to["RY"] = 6, to["BR"] = 2, to["GY"] = 5, to["BY"] = 3,
  to["GR"] = 4;

  int T;
  cin >> T;
  while (T--) {
    cin >> n >> m;
    
    // Read portal types and map to integers
    for (int i = 1; i <= n; i++) {
      string p;
      cin >> p;
      z[i] = to[p];
    }
    z[n + 1] = 0; // Sentinel value for boundary condition

    // Compute l[i]: longest prefix ending at i where colors match or are complementary
    for (int i = 1; i <= n; i++)
      l[i] = z[i - 1] == z[i] || z[i - 1] + z[i] == 7 ? l[i - 1] + 1 : 1;

    // Compute r[i]: longest suffix starting at i where colors match or are complementary
    for (int i = n; i >= 1; i--)
      r[i] = z[i + 1] == z[i] || z[i + 1] + z[i] == 7 ? r[i + 1] + 1 : 1;

    // Process queries
    while (m--) {
      int x, y;
      cin >> x >> y;
      
      // Ensure x <= y for simplification
      if (x > y)
        swap(x, y);

      // If we can't move directly due to incompatible colors or gap too large
      if (z[x] + z[y] != 7 || x + r[x] < y)
        printf("%d\n", y - x);
      else {
        // Special case handling:
        // Both ends are not the start or end of a segment with same color
        if (l[x] == x && y + r[y] == n + 1)
          printf("-1\n"); // Impossible to move via connected paths
        else {
          if (l[x] == x)
            printf("%d\n", 2 * r[y] + y - x); // Start is segment beginning, end is not
          if (y + r[y] == n + 1)
            printf("%d\n", 2 * l[x] + y - x); // End is segment ending, start is not
          if (l[x] != x && y + r[y] != n + 1)
            printf("%d\n", 2 * min(l[x], r[y]) + y - x); // Neither is edge of segment
        }
      }
    }
  }
}


// https://github.com/VaHiX/codeForces/