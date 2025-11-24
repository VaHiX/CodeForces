// Problem: CF 873 B - Balanced Substring
// https://codeforces.com/contest/873/problem/B

/*
 * Problem: Balanced Substring
 * 
 * Algorithm: Prefix Sum with Hash Map
 * 
 * Approach:
 * - Convert the string into a running sum where '1' contributes +1 and '0' contributes -1.
 * - A balanced substring corresponds to a point where the running sum returns to a previously seen value.
 * - The difference in indices gives the length of the balanced substring.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * 
 * Techniques:
 * - Prefix sum technique
 * - Hash map for storing first occurrence of each prefix sum
 */

#include <stdio.h>
#include <iostream>
#include <map>
#include <string>

int main() {
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  std::map<long, long> m; // Map to store first occurrence of each prefix sum
  m[0] = -1; // Initialize with 0 sum at index -1 (before start)
  long total(0), maxLength(0);
  for (long p = 0; p < s.size(); p++) {
    // Update total: +1 for '1', -1 for '0'
    total += (s[p] == '1') ? 1 : -1;
    long length(0);
    // If current total was seen before, we found a balanced substring
    if (m.count(total)) {
      length = p - m[total]; // Length is difference in indices
    } else {
      m[total] = p; // Store first occurrence of this total
    }
    maxLength = (maxLength > length) ? maxLength : length; // Keep track of max length
  }
  printf("%ld\n", maxLength);
  return 0;
}


// https://github.com/VaHiX/CodeForces/