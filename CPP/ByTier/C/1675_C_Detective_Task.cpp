// Problem: CF 1675 C - Detective Task
// https://codeforces.com/contest/1675/problem/C

/*
C. Detective Task
Time Complexity: O(n) where n is the length of the string s
Space Complexity: O(1) - only using a few variables for tracking indices

Algorithm:
- For each test case, we determine how many friends could have stolen the painting.
- The painting starts at position 0 (before any friend visits), and ends up missing.
- A friend is a suspect if their answer is inconsistent with the painting's state when they entered.
- The approach is to find the earliest "0" (indicating no picture) and last "1" (indicating yes picture).
- All friends between those critical points are suspects, unless they said "?", in which case they may or may not be the thief.

The algorithm works by:
1. Finding the index of the first '0' (if exists), call it z.
2. Finding the index of the last '1' (if exists), call it a.
3. If no '0' exists, then all friends are suspects; if no '1' exists, then only those in the beginning can be suspects.
4. Otherwise, all friends from a to z inclusive are suspects.

*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long z(s.size() - 1), a(0); // Initialize z to last index, a to first index
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == '0' && p < z) { // Update z to the earliest '0'
        z = p;
      } else if (s[p] == '1') {   // Update a to the latest '1'
        a = p;
      }
    }
    std::cout << (z - a + 1) << std::endl; // Number of potential thieves
  }
}


// https://github.com/VaHiX/codeForces/