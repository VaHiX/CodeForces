// Problem: CF 1992 D - Test of Love
// https://codeforces.com/contest/1992/problem/D

/*
D. Test of Love

Algorithm:
Greedy approach with preprocessing of log positions.

Time Complexity: O(n) per test case, where n is the length of the river.
Space Complexity: O(n) for storing the log positions and the extended string.

Problem Description:
ErnKor must swim from position 0 to position n+1 (left bank to right bank). 
He can only move forward by at most m meters if on land/log, or swim one meter at a time.
He can swim at most k meters total. Crocodiles ('C') block landing. Logs ('L') allow jumping.
Water ('W') allows swimming.

Approach:
1. Preprocess log positions (add sentinel 'L' at start and end).
2. For each consecutive pair of logs, simulate jump + check if crocodile is in path.
3. If not enough swimming distance, mark impossible.
4. Ensure no crocodiles in the water section traversed.
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, m, k;
    std::cin >> n >> m >> k;
    std::string s;
    std::cin >> s;
    // Add sentinel 'L' at both ends to simplify boundary conditions
    s = "L" + s + "L";
    std::vector<long> v;
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == 'L') {
        v.push_back(p); // Store positions of logs
      }
    }
    bool possible(true);
    for (long p = 0; possible && p + 1 < v.size(); p++) {
      // Check if we can directly jump from current log to next one
      if (v[p] + m >= v[p + 1]) {
        continue; // Can jump without swimming
      }
      long cur = v[p] + m;       // Position where jump ends
      long nxt = v[p + 1];       // Next log position
      long dist = nxt - cur;     // Water distance between log and next log
      if (dist <= k) {
        k -= dist;               // Deduct swimming distance
      } else {
        possible = false;        // Not enough swimming capacity
        break;
      }
      // Ensure no crocodiles in the water path
      for (long u = cur; u < nxt; u++) {
        if (s[u] == 'C') {
          possible = false;
          break;
        }
      }
    }
    std::cout << (possible ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/