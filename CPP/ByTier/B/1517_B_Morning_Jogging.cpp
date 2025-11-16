// Problem: CF 1517 B - Morning Jogging
// https://codeforces.com/contest/1517/problem/B

/*
Algorithm: Greedy + Sorting
Approach:
1. Read all the path lengths into a 2D array 'a' and also flatten them into a 1D vector 'v'.
2. Sort vector 'v' to identify the minimum elements across all paths.
3. For each runner (0 to m-1), assign a path from the sorted list to each checkpoint (0 to n-1) 
   such that:
   - Each path between adjacent checkpoints is traversed exactly once.
   - When a path is assigned to a runner, mark it as used by setting it to -1.
4. Remaining unused paths are assigned greedily to ensure each runner gets a valid path.
5. Output the final grid, where grid[j][i] represents the length of the path that runner j chooses 
   for checkpoint i.

Time Complexity: O(n * m * log(n * m)) due to sorting; the rest of the operations are linear.
Space Complexity: O(n * m) for storing the grid and path data.

Techniques: Greedy assignment with sorting to minimize maximum path in each runner's path.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::vector<std::vector<long>> a(n, std::vector<long>(m));
    std::vector<long> v(n * m);
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < m; col++) {
        scanf("%ld", &a[row][col]);
        v[row * m + col] = a[row][col];
      }
    }
    sort(v.begin(), v.end());
    std::vector<std::vector<long>> grid(m, std::vector<long>(n, -1));
    for (long p = 0; p < m; p++) {
      long val(v[p]);
      bool done(0);
      for (long row = 0; !done && row < n; row++) {
        for (long col = 0; !done && col < m; col++) {
          if (a[row][col] != val) {
            continue;
          }
          grid[p][row] = val;
          a[row][col] = -1;
          done = true;
        }
      }
    }
    std::vector<std::vector<long>> remn(n);
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < m; col++) {
        if (a[row][col] > 0) {
          remn[row].push_back(a[row][col]);
        }
      }
    }
    for (long row = 0; row < m; row++) {
      for (long col = 0; col < n; col++) {
        if (grid[row][col] == -1) {
          grid[row][col] = remn[col].back();
          remn[col].pop_back();
        }
      }
    }
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < m; col++) {
        printf("%ld ", grid[col][row]);
      }
      puts("");
    }
  }
}


// https://github.com/VaHiX/CodeForces/