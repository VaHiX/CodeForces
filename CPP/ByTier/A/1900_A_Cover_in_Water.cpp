// Problem: CF 1900 A - Cover in Water
// https://codeforces.com/contest/1900/problem/A

/*
 * Problem: A. Cover in Water
 * Purpose: Determine the minimum number of times action 1 (placing water)
 *          is needed to fill all empty cells with water based on the rule:
 *          if a cell is between two cells with water, it gets filled.
 * 
 * Algorithm/Techniques: Greedy approach with scanning and grouping.
 * 
 * Time Complexity: O(n) where n is the length of string s. Each character
 *                   is processed exactly once per test case.
 * 
 * Space Complexity: O(1) not counting input storage; only a few variables used.
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
    s.push_back('#'); // Append a sentinel to simplify loop logic
    bool two(false); // Tracks if any gap > 2 exists
    long prev(-1), cnt(0); // prev: previous water source index, cnt: count of actions
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == '.') {
        ++cnt; // Count empty cell
        continue;
      }
      // Calculate gap between current and previous water source
      long diff = p - prev - 1;
      if (diff > 2) {
        two = true; // Gap larger than 2 implies we need more than one action in this segment
      }
      prev = p; // Update previous water source position
    }
    if (two) {
      cnt = 2; // If a gap > 2 exists, only 2 actions needed to fill the entire sequence
    }
    std::cout << cnt << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/