// Problem: CF 1774 C - Ice and Fire
// https://codeforces.com/contest/1774/problem/C

/*
C. Ice and Fire

Purpose:
This code solves a tournament simulation problem where players with different temperatures fight in environments described by a binary string. For each number of participating players from 2 to n, it determines how many players have a chance to win the tournament.

Algorithms/Techniques:
- Simulation approach with careful tracking of player elimination
- Linear scan of the environment string to determine battle outcomes
- Efficient counting using a sliding window technique

Time Complexity: O(n) per test case
Space Complexity: O(1) extra space (excluding input/output)

*/
#include <stdio.h>
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
    char prev('_'); // Initialize previous character to a sentinel value
    long cnt(0);    // Counter for consecutive same characters
    for (long p = 0; p < n - 1; p++) {
      if (s[p] == prev) {
        ++cnt; // Increment counter if current char matches previous
      } else {
        prev = s[p]; // Update previous character
        cnt = 1;     // Reset counter
      }
      printf("%ld ", p - cnt + 2); // Print the index calculation result
    }
    puts(""); // Newline after each test case output
  }
}


// https://github.com/VaHiX/codeForces/