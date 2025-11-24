// Problem: CF 666 A - Reberland Linguistics
// https://codeforces.com/contest/666/problem/A

/*
 * Problem: Reberland Linguistics
 * 
 * Purpose: 
 *   Given a string s, find all distinct suffixes of length 2 or 3 that could have been used 
 *   to construct the word according to Reberland language rules. The root must be longer than 4 characters,
 *   and no two consecutive suffixes can be the same.
 * 
 * Approach:
 *   - Use dynamic programming to determine valid suffix positions.
 *   - For each position p in the string (from right to left), check if a suffix of length 2 or 3
 *     can be placed at that position, under the constraint that it doesn't match the immediately
 *     following suffix.
 *   - Store valid suffixes in a set to ensure uniqueness and sort them lexicographically.
 * 
 * Time Complexity: O(n^2 * L) where n is the length of the string and L is the average length of substrings considered.
 * Space Complexity: O(n * L) for storing the DP table and suffix set.
 * 
 * Techniques:
 *   - Dynamic Programming
 *   - String Matching
 *   - Set for Unique Sorting
 * 
 * Note:
 *   This solution uses a backward DP approach, checking suffix validity from right to left.
 *   It handles edge cases like strings of length <= 5 where no valid suffixes exist.
 */

#include <iostream>
#include <set>
#include <vector>
#include <string>

int main() {
  std::set<std::string> suf;  // Set to store unique suffixes in lexicographical order
  std::string s;
  std::cin >> s;
  long sz = s.size();
  // dp[i][len] indicates whether a suffix of length 'len' can end at position i
  std::vector<std::vector<bool>> dp(s.size() + 10, std::vector<bool>(4, 0));
  dp[sz][2] = dp[sz][3] = true;  // Base case: end of string allows both lengths
  s += "##";  // Padding to avoid out-of-bounds access
  for (long p = sz - 2; p > 4; p--) {  // Loop from second last possible suffix position down to 5
    for (long len = 2; len <= 3; len++) {
      // Check if placing a suffix of length 'len' at position 'p' is valid
      dp[p][len] =
          ((dp[p + len][len] && s.substr(p, len) != s.substr(p + len, len)) ||
           dp[p + len][5 - len]);
      if (dp[p][len]) {
        // If valid, insert the suffix into the set
        suf.insert(s.substr(p, len));
      }
    }
  }
  std::cout << suf.size() << std::endl;
  for (std::set<std::string>::iterator it = suf.begin(); it != suf.end();
       it++) {
    std::cout << (*it) << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/