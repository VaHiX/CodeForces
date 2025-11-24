// Problem: CF 1894 A - Secret Sport
// https://codeforces.com/contest/1894/problem/A

/*
 * Problem: Secret Sport
 * Purpose: Determine the winner of a game between two players A and B,
 *          given the sequence of play results. The game is played in sets
 *          with parameters X (wins needed per set) and Y (sets needed to win).
 * 
 * Algorithm:
 * - For each possible value of X (from 1 to n), simulate the game to see
 *   if there exists a valid Y such that the outcome can be determined.
 * - For a given X, iterate through the string to count consecutive wins,
 *   and determine set winners based on reaching X wins in a row.
 * - Track final set counts for A and B.
 * - Validate outcomes against rules: both players must reach 0 remaining
 *   wins at end of last set, and the last player to win a set must have
 *   won their set.
 * 
 * Time Complexity: O(n^3) where n is the number of plays (max 20)
 * Space Complexity: O(1) - only using fixed-size variables
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    bool a(0), b(0); // Flags to indicate if A or B can be guaranteed winner
    for (long x = 1; x <= n; x++) { // Try all possible X values (wins per set)
      bool valid(true);
      long wa(0), wb(0), sa(0), sb(0); // wa: A's current run, wb: B's current run,
                                        // sa: A's set count, sb: B's set count
      char last = 'N'; // Last player to win a set
      for (long p = 0; p < n; p++) {
        if (s[p] == 'A') {
          ++wa;
          if (wa == x) { // A reaches X wins in this set
            ++sa;
            wa = 0; // Reset A's run
            wb = 0; // Reset B's run
            last = 'A';
          }
        } else if (s[p] == 'B') {
          ++wb;
          if (wb == x) { // B reaches X wins in this set
            ++sb;
            wa = 0; // Reset A's run
            wb = 0; // Reset B's run
            last = 'B';
          }
        }
      }
      if (wa > 0 || wb > 0) {
        valid = false; // Game incomplete - not all sets ended
      }
      if (sb == sa) {
        valid = false; // Equal set counts make result ambiguous
      }
      if (sa > sb && last != 'A') {
        valid = false; // A won more sets, but last set was not won by A
      }
      if (sb > sa && last != 'B') {
        valid = false; // B won more sets, but last set was not won by B
      }
      if (valid) {
        if (sa > sb) {
          a = true; // Player A can be guaranteed the winner
        } else {
          b = true; // Player B can be guaranteed the winner
        }
      }
    }
    char res('?');
    if (a && !b) {
      res = 'A';
    } else if (!a && b) {
      res = 'B';
    }
    std::cout << res << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/