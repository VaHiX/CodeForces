// Problem: CF 1029 A - Many Equal Substrings
// https://codeforces.com/contest/1029/problem/A

/*
 * Problem: A. Many Equal Substrings
 * Purpose: Given a string t of length n and an integer k, construct a string s of minimum possible length such that there are exactly k occurrences of t as a substring in s.
 * Algorithm:
 *   - First, find the shortest prefix of t that can be repeated to form a pattern where t appears exactly k times.
 *   - Use a sliding window approach to identify the minimum overlapping portion of the string.
 *   - Concatenate this pattern k times to construct the final result.
 * Time Complexity: O(n^2) in worst case due to nested loops for pattern matching
 * Space Complexity: O(n) for storing the input string
 */

#include <iostream>
#include <string>

int main() {
  long n, k;
  std::cin >> n >> k;
  std::string s;
  std::cin >> s;
  long start(0);
  // Loop through possible distances to find the minimum overlap
  for (long dist = 1; dist < s.size(); dist++) {
    long g(dist);
    // Check if substring from position 0 to dist-1 matches with current position
    while (g < s.size()) {
      if (s[g - dist] != s[g]) {
        break;
      }
      ++g;
    }
    // If full match was found, set start point and break
    if (g == s.size()) {
      start = s.size() - dist;
      break;
    }
  }
  std::cout << s;
  // Append the pattern starting from 'start' index k-1 times more
  for (long p = 1; p < k; p++) {
    std::cout << s.substr(start);
  }
  std::cout << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/