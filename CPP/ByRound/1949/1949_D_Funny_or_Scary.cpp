// Problem: CF 1949 D - Funny or Scary?
// https://codeforces.com/contest/1949/problem/D

/*
Purpose: This code solves the problem of assigning "funny" or "scary" labels to transition videos 
         between game scenarios such that no more than ⌈3n/4⌉ videos of the same type appear consecutively 
         in any order of playing scenarios.

Algorithm: The solution uses a brute-force approach over all possible assignments of F/S to the '?' entries,
           and checks if they satisfy the constraint for all possible permutations. A key optimization 
           is to fix a "cute" type (either F or S) as representing "funny" and "scary" as the other, 
           which reduces the number of cases to check.

Time Complexity: O(2^n * n^2) where n <= 24. In the worst case, we iterate through 2^n possible masks,
                 and for each mask, we do O(n^2) checks to validate constraints.

Space Complexity: O(n^2) for storing the grid of transition videos.

Techniques:
- Bitmask enumeration to represent assignment of F/S to transitions
- Constraint checking for valid assignment
- Backtracking with early pruning to reduce search space
*/

#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<string> grid(n);
  for (int i = 0; i < n; i++) {
    cin >> grid[i];
  }
  int target = (3 * n - 1) / 4 + 1;  // Calculate maximum allowed consecutive same type transitions
  for (char cute : string("FS")) {  // Iterate over both possibilities for 'cute'
    char funny = 'F' ^ 'S' ^ cute;   // Determine the other type (XOR gives the different character)
    for (int msk = 0; msk < (1 << n); msk++) {  // Enumerate all possible assignments (bitmask)
      int cnt = __builtin_popcount(msk);  // Count number of '1's in mask (representing F)
      // Check constraints: too many F or too many S
      if (n - cnt - 1 <= target && 2 * cnt <= target) {
        bool ok = true;
        for (int i = 0; i < n && ok; i++) {
          for (int j = i + 1; j < n && ok; j++) {
            int bi = msk >> i & 1, bj = msk >> j & 1;
            // If the assignment leads to contradiction with existing choices
            if (bi != bj && grid[i][j] == cute) {
              ok = false;
            } else if (bi == bj && bi == 1 && grid[i][j] == funny) {
              ok = false;
            }
          }
        }
        if (ok) {  // If valid assignment found, fill the grid
          for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
              int bi = msk >> i & 1, bj = msk >> j & 1;
              char to_fill = (bi == bj ? cute : funny);
              if (grid[i][j] == '?') {
                grid[i][j] = grid[j][i] = to_fill;  // Fill both symmetric positions
              }
            }
          }
          for (int i = 0; i < n; i++) {
            cout << grid[i] << '\n';
          }
          return 0;
        }
      }
    }
  }
  assert(false);  // No valid solution found (should not happen per problem constraints)
}


// https://github.com/VaHiX/CodeForces/