// Problem: CF 1245 B - Restricted RPS
// https://codeforces.com/contest/1245/problem/B

/*
 * Problem: B. Restricted RPS
 * Purpose: Determine if Alice can win a rock-paper-scissors game against Bob
 *          given constraints on her moves and Bob's sequence of plays.
 *
 * Algorithm:
 *   - Greedily match Bob's moves with winning moves (R vs S, P vs R, S vs P)
 *   - If no such move available, use any remaining valid move to fill gaps
 *   - Check if Alice wins at least ceil(n/2) rounds
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the output string
 */

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    long a, b, c;
    std::cin >> a >> b >> c;
    std::string g;
    std::cin >> g;
    long cnt(0);
    std::string h(g); // Copy of Bob's moves for output
    for (long p = 0; p < g.size(); p++) {
      if (g[p] == 'R') {          // Bob plays rock
        if (b > 0) {              // Alice has paper
          ++cnt;                  // Alice wins
          --b;                    // Use one paper
          h[p] = 'P';             // Alice plays paper
        } else {
          h[p] = '_';             // No winning move, mark for replacement
        }
      } else if (g[p] == 'P') {   // Bob plays paper
        if (c > 0) {              // Alice has scissors
          ++cnt;                  // Alice wins
          --c;                    // Use one scissors
          h[p] = 'S';             // Alice plays scissors
        } else {
          h[p] = '_';             // No winning move, mark for replacement
        }
      } else if (g[p] == 'S') {   // Bob plays scissors
        if (a > 0) {              // Alice has rock
          ++cnt;                  // Alice wins
          --a;                    // Use one rock
          h[p] = 'R';             // Alice plays rock
        } else {
          h[p] = '_';             // No winning move, mark for replacement
        }
      }
    }
    // Fill in remaining blanks with any valid moves that are left
    for (long p = 0; p < h.size(); p++) {
      if (h[p] != '_') {         // Already assigned
        continue;
      }
      if (a > 0) {               // Use rock if available
        h[p] = 'R';
        --a;
      } else if (b > 0) {        // Use paper if available
        h[p] = 'P';
        --b;
      } else if (c > 0) {        // Use scissors if available
        h[p] = 'S';
        --c;
      }
    }
    // Alice wins at least ceil(n/2) rounds
    if (2 * cnt >= n) {
      std::cout << "YES" << std::endl << h << std::endl;
    } else {
      std::cout << "NO" << std::endl;
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/