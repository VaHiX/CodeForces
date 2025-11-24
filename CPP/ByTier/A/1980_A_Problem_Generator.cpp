// Problem: CF 1980 A - Problem Generator
// https://codeforces.com/contest/1980/problem/A

/* 
 * Problem: Minimum Additional Problems for Rounds
 * Purpose: Given a set of problems with difficulty levels from 'A' to 'G', 
 * determine the minimum number of additional problems needed to hold m rounds, 
 * each requiring one problem of each difficulty level.
 * 
 * Algorithm:
 * 1. For each test case, count how many problems exist for each difficulty level (A-G).
 * 2. For each difficulty level, calculate how many more problems are needed to reach 'm' instances.
 * 3. Sum up the deficits across all levels to get the total number of additional problems required.
 * 
 * Time Complexity: O(n + 7) = O(n), where n is the length of the input string.
 * Space Complexity: O(1), since we use a fixed-size array of size 7.
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false); // Disable sync with C stdio for faster I/O
  long t;
  std::cin >> t;
  while (t--) {
    long n, m;
    std::cin >> n >> m;
    std::string s;
    std::cin >> s;
    long v[7] = {0}; // Array to store count of each difficulty level (A to G)
    for (long p = 0; p < s.size(); p++) {
      ++v[s[p] - 'A']; // Increment count for the corresponding difficulty level
    }
    long cnt(0);
    for (long p = 0; p < 7; p++) {
      long diff = m - v[p]; // Calculate how many more problems needed for this level
      cnt += (diff > 0) * diff; // Add to total if positive
    }
    std::cout << cnt << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/