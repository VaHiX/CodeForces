// Problem: CF 1569 B - Chess Tournament
// https://codeforces.com/contest/1569/problem/B

/*
Purpose: 
This code solves a chess tournament scheduling problem where each player has a specific expectation:
- Type 1: Player wants not to lose any game (zero losses)
- Type 2: Player wants to win at least one game

The algorithm determines if there exists a valid tournament outcome that satisfies all players' expectations.

Algorithms/Techniques:
1. Group players of type 2 into a circular chain
2. If there's exactly 1 or 2 players of type 2, it's impossible to satisfy all expectations
3. For type 2 players, assign wins/losses in a circular pattern to satisfy their needs
4. Type 1 players (who want no losses) are assigned draws with others to avoid losses

Time Complexity: O(n^2)
Space Complexity: O(n^2)

*/
#include <iostream>
#include <vector>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    std::vector<long> next(n);
    long idx(-1), first(-1);
    long twos(0);
    for (long p = 0; p < s.size(); p++) {
      if (s[p] != '2') {
        continue;
      }
      ++twos;
      if (idx < 0) {
        idx = p;
        first = p;
      } else {
        next[idx] = p;
        idx = p;
      }
    }
    if (first >= 0) {
      next[idx] = first;
    }
    if (twos == 1 || twos == 2) {
      std::cout << "NO" << std::endl;
      continue;
    }
    std::vector<std::string> res(n, std::string(n, ' '));
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < n; col++) {
        char cur('=');
        if (row == col) {
          cur = 'X';
        } else if (s[row] == '2' && s[col] == '2' && next[row] == col) {
          cur = '+';
        } else if (s[row] == '2' && s[col] == '2' && next[col] == row) {
          cur = '-';
        }
        res[row][col] = cur;
      }
    }
    std::cout << "YES" << std::endl;
    for (long p = 0; p < n; p++) {
      std::cout << res[p] << std::endl;
    }
  }
}


// https://github.com/VaHiX/CodeForces/