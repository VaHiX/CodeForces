// Problem: CF 1611 G - Robot and Candies
// https://codeforces.com/contest/1611/problem/G

/*
Code Purpose:
This code solves the problem of finding the minimum number of times a robot must be placed 
on the topmost row of a grid to collect all candies. The robot moves diagonally down-left 
or down-right and collects candies in its path. The key idea is to use a greedy approach 
by grouping cells according to their diagonal (i + j) and simulating the movement of 
the robot through these diagonals.

Algorithms/Techniques:
- Diagonal grouping: Cells (i,j) are grouped by their diagonal coordinate (i + j)
- Greedy simulation: For each diagonal, we determine if we need to place the robot
  at a specific position and simulate its path
- Set operations: Use sets to maintain which rows are covered by each diagonal

Time Complexity: O(n * m)
Space Complexity: O(n * m)

*/
#include <stdio.h>
#include <iterator>
#include <set>

using namespace std;
int i, j, k, n, m, T, x, ans;
set<int> a[1000100]; // Array of sets to group rows by diagonal sum (i + j)
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &m);
    ans = 0; // Initialize answer to zero
    // Clear all sets for new test case
    for (i = 1; i <= n + m; i++)
      a[i].clear();
    // Read grid and group cells by diagonal
    for (i = 1; i <= n; i++)
      for (j = 1; j <= m; j++) {
        scanf("%1d", &x);
        if (x)
          a[i + j].insert(i); // Group row i by diagonal (i + j)
      }
    // Process each diagonal to determine robot placements
    for (i = 1; i < n + m; i++) {
      if (a[i + 1].size()) { // If there are rows in the next diagonal
        ans++; // Increment robot placements
        // Simulate robot movement from this diagonal
        for (k = i + 1, j = 1; j <= n; j++, k++) {
          a[k].erase(j); // Remove current row from k-th diagonal
          // Adjust movement based on remaining elements in the set
          k += (a[k].begin() != a[k].end() && *a[k].rbegin() > j) ? -1 : 1;
        }
      }
    }
    printf("%d\n", ans); // Print minimum number of robot placements
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/