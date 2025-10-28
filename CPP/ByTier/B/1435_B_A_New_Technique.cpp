// Problem: CF 1435 B - A New Technique
// https://codeforces.com/contest/1435/problem/B

/*
B. A New Technique
Algorithm: Restore a table given rows and columns in arbitrary order.
Techniques: Hashing, mapping, simulation.

Time Complexity: O(n * m)
Space Complexity: O(n * m)

All techniques in the ninja world consist of hand seals. At the moment Naruto is learning a new technique, which consists of n·m different seals, denoted by distinct numbers. All of them were written in an n×m table.
The table is lost now. Naruto managed to remember elements of each row from left to right, and elements of each column from top to bottom, but he doesn't remember the order of rows and columns. Please restore the table consistent with this data so that Naruto will be able to learn the new technique.
*/
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::vector<std::vector<long>> ans(n + 1, std::vector<long>(m + 1, 0)); // Result table
    std::vector<long> maps(n * m + 1, 0); // Maps value to its column index in original table
    for (long p = 1; p <= n; p++) { // For each row
      for (long q = 1; q <= m; q++) {
        long k;
        scanf("%ld", &k);
        maps[k] = q; // Store the column position of value k
      }
    }
    for (long p = 1; p <= m; p++) { // For each column
      for (long q = 1; q <= n; q++) {
        long k;
        scanf("%ld", &k);
        ans[q][maps[k]] = k; // Place value k at row q, column maps[k]
      }
    }
    for (long p = 1; p <= n; p++) { // Print result table
      for (long q = 1; q <= m; q++) {
        printf("%ld ", ans[p][q]);
      };
      puts(""); // New line after each row
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/