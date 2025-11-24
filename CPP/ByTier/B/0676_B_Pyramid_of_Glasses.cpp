// Problem: CF 676 B - Pyramid of Glasses
// https://codeforces.com/contest/676/problem/B

#include <cstdio>
#include <vector>
// Problem: B. Pyramid of Glasses
// Purpose: Simulate champagne flowing through a pyramid of glasses for t seconds,
//          and count how many glasses are completely full at the end.
// Algorithm:
//   - Use a 2D vector to represent the pyramid levels.
//   - Each second, pour one unit of champagne into the top glass (g[0][0]).
//   - For each level and glass, if it has more than 1 unit (full), overflow
//     equally distributes the excess to the two glasses below it.
//   - Count full glasses at the end.
//
// Time Complexity: O(n * t) where n is the height of pyramid (at most 10),
//                  and each second we process up to n^2 glasses in worst case.
// Space Complexity: O(n^2) for storing the champagne in the pyramid.
int main() {
  int n, t;
  scanf("%d %d\n", &n, &t);
  std::vector<std::vector<double>> g(n + 1, std::vector<double>(n + 1, 0));
  g[0][0] = t; // Pour 't' units of champagne into the top glass
  int total(0); // Counter for full glasses
  for (int level = 0; level < n; level++) {
    for (int col = 0; col <= level; col++) {
      if (g[level][col] < 1.0) {
        continue; // Skip if glass isn't full yet
      }
      ++total;
      double rem = g[level][col] - 1; // Calculate overflow
      g[level + 1][col] += rem / 2;   // Distribute to left child
      g[level + 1][col + 1] += rem / 2; // Distribute to right child
    }
  }
  printf("%d\n", total);
  return 0;
}

// https://github.com/VaHiX/codeForces/