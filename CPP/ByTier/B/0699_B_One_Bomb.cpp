// Problem: CF 699 B - One Bomb
// https://codeforces.com/contest/699/problem/B

/*
 * Problem: B. One Bomb
 * Purpose: Determine if it's possible to clear all walls ('*') in a grid by placing one bomb at some cell (x, y),
 *          which clears all walls in row x and column y.
 *
 * Algorithm:
 * 1. For each wall encountered, we maintain a candidate set of positions where the bomb can be placed.
 * 2. On first wall, we add all cells in its row and column to candidate set.
 * 3. For subsequent walls, we filter out candidates that don't satisfy the condition (i.e., they must intersect both
 *    the row of current wall and the column of current wall).
 *
 * Time Complexity: O(n * m) - Each cell is visited once and operations on set are logarithmic.
 * Space Complexity: O(n + m) - In worst case, the candidate set contains all rows and columns.
 */

#include <cstdio>
#include <iostream>
#include <set>
#include <string>
#include <utility>

int main() {
  int n, m;
  std::cin >> n >> m;
  std::set<std::pair<int, int>> cand; // Store candidate bomb positions
  bool noneSoFar(true); // Flag to check if any wall has been encountered yet
  for (int row = 1; row <= n; row++) {
    std::string s;
    std::cin >> s;
    for (int col = 1; col <= s.size(); col++) {
      if (s[col - 1] != '*') // Skip empty cells
        continue;
      if (noneSoFar) { // On encountering the first wall
        noneSoFar = false;
        // Add all positions in row 'row' to candidates
        for (int p = 1; p <= m; p++) {
          cand.insert(std::make_pair(row, p));
        }
        // Add all positions in column 'col' to candidates
        for (int p = 1; p <= n; p++) {
          cand.insert(std::make_pair(p, col));
        }
      } else {
        // Remove candidates that don't lie on both the row and column of current wall
        std::set<std::pair<int, int>> toRemove;
        for (std::set<std::pair<int, int>>::iterator setIter = cand.begin();
             setIter != cand.end(); setIter++) {
          std::pair<int, int> current = *setIter;
          if (current.first != row && current.second != col) {
            toRemove.insert(current);
          }
        }
        for (std::set<std::pair<int, int>>::iterator setIter = toRemove.begin();
             setIter != toRemove.end(); setIter++) {
          cand.erase(*setIter);
        }
      }
    }
  }
  if (noneSoFar) { // If no walls at all
    puts("YES\n 1 1\n");
  } else if (cand.size() > 0) { // If there's a valid candidate left
    puts("YES");
    printf("%d %d\n", (*cand.begin()).first, (*cand.begin()).second);
  } else {
    puts("NO"); // No valid placement found
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/