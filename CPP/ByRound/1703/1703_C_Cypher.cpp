// Problem: CF 1703 C - Cypher
// https://codeforces.com/contest/1703/problem/C

/*
C. Cypher
Algorithms/Techniques: Simulation with modular arithmetic
Time Complexity: O(n * m) where n is the number of wheels and m is the average number of moves per wheel
Space Complexity: O(n) for storing the vector of wheels

Luca has a cypher made up of a sequence of n wheels, each with a digit a_i written on it. On the i-th wheel,
he made b_i moves. Each move is one of two types:
up move (denoted by 'U'): it increases the i-th digit by 1. After applying the up move on 9, it becomes 0.
down move (denoted by 'D'): it decreases the i-th digit by 1. After applying the down move on 0, it becomes 9.

The task is to find the original sequence before any moves were made.
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::vector<int> v(n);
    for (long p = 0; p < n; p++) {
      std::cin >> v[p];
    }
    for (long p = 0; p < n; p++) {
      long x;
      std::cin >> x;
      std::string s;
      std::cin >> s;
      long cnt(0);
      for (long q = 0; q < s.size(); q++) {
        if (s[q] == 'D') {
          ++cnt; // Count down moves
        } else if (s[q] == 'U') {
          --cnt; // Count up moves (as negative)
        }
      }
      // Adjust for modular arithmetic: convert net effect to positive mod 10
      cnt = ((cnt % 10) + 10) % 10;
      v[p] += cnt; // Apply the net effect on current digit
      v[p] = (v[p] + 10) % 10; // Ensure result wraps correctly in range [0,9]
    }
    for (long p = 0; p < n; p++) {
      std::cout << v[p] << " ";
    }
    std::cout << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/