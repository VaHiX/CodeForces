// Problem: CF 1443 B - Saving the City
// https://codeforces.com/contest/1443/problem/B

/*
B. Saving the City

Approach:
- The problem involves minimizing the cost to neutralize all mines in a city represented as a binary string.
- Mines can be activated (cost a per mine) or new mines can be placed (cost b per mine).
- When a mine is activated, it triggers adjacent mines in the same connected segment.
- Strategy: For each continuous segment of '1's:
  - If the segment has length 1, we must activate it directly (cost a).
  - Otherwise, calculate the cost of activating all mines in the segment vs placing a new mine at one end and activating it.
- We only need to handle segments that start from a '1', and process gaps between them.

Time Complexity: O(n) where n is the length of the string
Space Complexity: O(k) where k is the number of gaps between non-overlapping segments of mines

Algorithms/Techniques:
- Greedy approach
- Segment processing
- String traversal
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  long t;
  std::cin >> t;
  while (t--) {
    long a, b;
    std::cin >> a >> b;
    std::string s;
    std::cin >> s;
    std::vector<long> g; // Stores the count of consecutive zeros between segments of ones
    long cnt(0), flag(false); // cnt counts zeros, flag tracks if we have seen at least one '1'
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == '1') { // Found a mine
        if (!flag) {
          flag = true; // First mine encountered
        } else if (p > 0 && s[p - 1] == '0') {
          // If previous character was '0', this marks start of new segment after gap
          g.push_back(cnt);
        }
        cnt = 0; // Reset zero counter after encountering a '1'
      } else if (s[p] == '0') { // Found empty space
        ++cnt; // Increment count of consecutive zeros
      }
    }
    long res(a * flag); // If there were any mines, we must pay at least 'a' for first mine activation
    for (long p = 0; p < g.size(); p++) {
      long cur = g[p] * b; // Cost of placing new mines for this gap
      cur = (cur < a) ? cur : a; // Choose cheaper option: place mines or activate existing one
      res += cur;
    }
    std::cout << res << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/