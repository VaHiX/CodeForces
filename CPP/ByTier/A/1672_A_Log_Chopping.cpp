// Problem: CF 1672 A - Log Chopping
// https://codeforces.com/contest/1672/problem/A

/*
 * Problem: Log Chopping Game
 * 
 * Algorithms/Techniques: Game Theory, Nim-like Strategy
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 * 
 * Description:
 * Two players (errorgorn and maomao90) play a game on logs of various lengths.
 * Each player can chop a log into two positive integer-length pieces.
 * The player who cannot make a move loses.
 * 
 * Strategy:
 * The key insight is to count the total number of "chops" needed to reduce all logs
 * to length 1. For a log of length x, exactly (x - 1) chops are required to split it
 * into x pieces of length 1. Therefore, the total number of chops across all logs
 * is sum(a_i - 1).
 * 
 * If this total is odd, errorgorn (who starts first) makes the last move and wins.
 * If even, maomao90 makes the last move and wins.
 * 
 * Sample Input:
 * 2
 * 4
 * 2 4 2 1
 * 1
 * 1
 * 
 * Sample Output:
 * errorgorn
 * maomao90
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long s(0); // Initialize sum of (x - 1) for all logs
    while (n--) {
      long x;
      scanf("%ld", &x);
      s += x - 1; // Accumulate total number of chops needed
    }
    puts(s % 2 ? "errorgorn" : "maomao90"); // If odd, errorgorn wins; else maomao90 wins
  }
}


// https://github.com/VaHiX/codeForces/