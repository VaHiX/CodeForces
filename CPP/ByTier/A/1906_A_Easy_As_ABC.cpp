// Problem: CF 1906 A - Easy As ABC
// https://codeforces.com/contest/1906/problem/A

/*
 * Problem: A. Easy As ABC
 * Purpose: Find the lexicographically smallest 3-letter word that can be formed by traversing adjacent cells in a 3x3 grid.
 *          Adjacent means sharing an edge or corner (8-directional).
 * Algorithm:
 *   - Try all combinations of 3 different positions (p, q, r) out of 9.
 *   - For each combination:
 *     - Check if the three cells are adjacent in sequence (p->q and q->r).
 *     - If valid, construct the word and update the result with the lexicographically smaller one.
 * Time Complexity: O(1) since there are only 9*8*7 = 504 combinations (constant), and each check takes O(1).
 * Space Complexity: O(1) as we use fixed-size data structures and no recursion or auxiliary space dependent on input size.
 */

#include <bits/std_abs.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::vector<std::string> v(3); // Read the 3x3 grid
  std::cin >> v[0] >> v[1] >> v[2];
  std::string res("CCC"); // Initialize result with a lexicographically large string
  for (int p = 0; p < 9; p++) { // Iterate over all possible first positions
    for (int q = 0; q < 9; q++) { // Iterate over all possible second positions
      for (int r = 0; r < 9; r++) { // Iterate over all possible third positions
        if (p == q || p == r || q == r) {
          continue; // Skip if any two positions are the same
        }
        int rowa(p / 3), cola(p % 3);     // Convert flat index to row/column for first cell
        int rowb(q / 3), colb(q % 3);     // Convert flat index to row/column for second cell
        int rowc(r / 3), colc(r % 3);     // Convert flat index to row/column for third cell
        if (std::abs(rowa - rowb) > 1 || std::abs(cola - colb) > 1) {
          continue; // Skip if first and second are not adjacent
        }
        if (std::abs(rowb - rowc) > 1 || std::abs(colb - colc) > 1) {
          continue; // Skip if second and third are not adjacent
        }
        std::string x;
        x += v[rowa][cola];    // Build the word from three cells
        x += v[rowb][colb];
        x += v[rowc][colc];
        res = (res < x ? res : x); // Keep the lexicographically smaller result
      }
    }
  }
  std::cout << res << std::endl;
}


// https://github.com/VaHiX/codeForces/