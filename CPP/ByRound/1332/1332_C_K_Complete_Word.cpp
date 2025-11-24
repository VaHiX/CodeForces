// Problem: CF 1332 C - K-Complete Word
// https://codeforces.com/contest/1332/problem/C

/*
C. K-Complete Word
=================================
Problem: Convert a given string to a k-complete word with minimum changes.
A k-complete word is both a palindrome and has period k.
Algorithm:
  - For each group of positions that must be equal due to periodicity and palindrome properties,
    count frequency of characters in that group.
  - To minimize changes, choose the most frequent character in each group as the target.
  - The number of changes for a group = total elements in group - max frequency.
Time Complexity: O(n * log(n)) per test case due to map usage, where n is length of string.
Space Complexity: O(k) for storing character counts in maps.
=================================
*/

#include <iostream>
#include <map>
#include <string>
#include <utility>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, k;
    std::cin >> n >> k;
    std::string s;
    std::cin >> s;
    long chg(0);
    for (long p = 0; 2 * p < k; p++) { // Iterate through mirror groups
      std::map<char, long> tally;       // Count frequency of characters in current group
      for (long u = p; u < n; u += k) { // Go through all positions in this group
        ++tally[s[u]];                  // Add character to count
      }
      long sz(n / k);                   // Size of this group (before mirror)
      if (2 * p < k - 1) {              // If not on the middle of the string
        for (long u = k - 1 - p; u < n; u += k) { // Add mirrored positions
          ++tally[s[u]];
        }
        sz *= 2;                        // Double size since we include mirror
      }
      long mx(0);                       // Find the maximum frequency in this group
      for (std::map<char, long>::iterator it = tally.begin(); it != tally.end();
           it++) {
        mx = (mx > (it->second)) ? mx : (it->second);
      }
      chg += (sz - mx);                 // Add number of changes needed for this group
    }
    std::cout << chg << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/