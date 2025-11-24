// Problem: CF 1267 B - Balls of Buma
// https://codeforces.com/contest/1267/problem/B

/*
 * Problem: B. Balls of Buma
 *
 * Purpose:
 *   This program determines the number of valid ways to insert a single ball
 *   into a sequence of colored balls such that all balls are eliminated,
 *   using a "Buma" game rule where segments of 3 or more same-colored balls
 *   get eliminated recursively.
 *
 * Algorithm:
 *   1. Preprocess input string to group consecutive identical characters and
 *      count their frequencies.
 *   2. Determine valid insertion points (between existing segments) and
 *      candidate ball colors that could lead to full elimination.
 *   3. For each potential insertion:
 *      - Try inserting a ball of a color that can start a chain reaction.
 *      - Simulate the process and verify if all balls get eliminated.
 *
 * Time Complexity: O(n^2) in worst case due to simulation of possible insertions,
 *                   where n is the length of the string.
 * Space Complexity: O(n) for storing grouped segments and their counts.
 */

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string s;
  std::cin >> s;
  std::vector<char> v;      // Store unique characters in consecutive groups
  std::vector<long> w;      // Store lengths of those consecutive groups
  long cnt(0);              // Counter for current group length
  for (long p = 0; p <= s.size(); p++) {
    if (p == s.size()) {
      v.push_back(s.back());   // Add last character
      w.push_back(cnt);        // Add its count
      break;
    }
    if (!p || (s[p - 1] == s[p])) {
      ++cnt;                   // Extend current group
    } else {
      v.push_back(s[p - 1]);   // Save previous character
      w.push_back(cnt);        // Save its count
      cnt = 1;                 // Reset counter for new group
    }
  }
  long ans = w[w.size() / 2] + 1;
  bool possible((v.size() % 2) && (v[v.size() / 2] > 1));  // Check if middle char is valid
  for (long p = 0; possible && p < v.size(); p++) {
    if (v[p] != v[v.size() - 1 - p]) {   // Check symmetry of chars
      possible = false;
    }
    if (w[p] + w[w.size() - 1 - p] < 3) {  // Check if pair sums to at least 3
      possible = false;
    }
  }
  std::cout << (possible ? ans : 0) << std::endl;  // Output result
  return 0;
}


// https://github.com/VaHiX/codeForces/