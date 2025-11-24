// Problem: CF 540 C - Ice Cave
// https://codeforces.com/contest/540/problem/C

/*
C. Ice Cave
Purpose: Determine if a path exists from a starting cracked cell to a destination cracked cell,
         where moving to an intact cell (.) causes it to crack and become traversable.
         The problem uses depth-first search (DFS) to explore all possible paths.

Algorithms/Techniques:
- Depth-First Search (DFS)
- Graph traversal with state modification (ice cracking)

Time Complexity: O(n * m), where n is number of rows and m is number of columns.
Space Complexity: O(n * m), for the recursion stack and grid storage.

Input Format:
- First line: n, m (dimensions of the cave)
- Next n lines: grid representation of the cave ('.' = intact ice, 'X' = cracked ice)
- Next line: r1, c1 (starting position)
- Next line: r2, c2 (destination position)

Output Format:
- "YES" if path exists, "NO" otherwise
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

bool dfs(long r, long c, std::vector<std::string> &a, const long &tr,
         const long &tc) {
  // Check bounds
  if (r < 0 || r >= a.size()) {
    return false;
  }
  if (c < 0 || c >= a[0].size()) {
    return false;
  }
  // If current cell is cracked ice, check if we've reached the target
  if (a[r][c] == 'X') {
    return ((r == tr) && (c == tc));
  }
  // Mark current cell as cracked (ice cracks after being stepped on)
  a[r][c] = 'X';
  // Explore all 4 adjacent cells (up, down, left, right)
  if (dfs(r - 1, c, a, tr, tc)) {
    return true;
  }
  if (dfs(r + 1, c, a, tr, tc)) {
    return true;
  }
  if (dfs(r, c - 1, a, tr, tc)) {
    return true;
  }
  if (dfs(r, c + 1, a, tr, tc)) {
    return true;
  }
  return false;
}

int main() {
  long n, m;
  std::cin >> n >> m;
  std::vector<std::string> a(n);
  for (long p = 0; p < n; p++) {
    std::cin >> a[p];
  }
  long r1, c1, r2, c2;
  std::cin >> r1 >> c1 >> r2 >> c2;
  --r1;
  --c1;
  --r2;
  --c2;
  // Start position must be cracked (as per problem statement)
  a[r1][c1] = '.';
  bool res = dfs(r1, c1, a, r2, c2);
  puts(res ? "YES" : "NO");
  return 0;
}


// https://github.com/VaHiX/codeForces/