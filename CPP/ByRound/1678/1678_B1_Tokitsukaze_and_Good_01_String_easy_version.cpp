// Problem: CF 1678 B1 - Tokitsukaze and Good 01-String (easy version)
// https://codeforces.com/contest/1678/problem/B1

/*
 * Problem: Tokitsukaze and Good 01-String (easy version)
 *
 * Purpose:
 *   Given a binary string of even length, determine the minimum number of operations
 *   to make the string "good". A string is good if it can be split into contiguous
 *   subsegments such that each subsegment has all identical characters and all
 *   subsegment lengths are even.
 *
 * Algorithm:
 *   - Iterate through the string in pairs of characters (positions 0,2,4,...).
 *   - For each pair, check if characters at positions p and p+1 are equal.
 *     If not equal, we need to make one of them equal to the other.
 *     This requires one operation.
 *   - Keep track of the number of such mismatches.
 *
 * Time Complexity: O(n) where n is the length of the string.
 * Space Complexity: O(1) - only using a constant amount of extra space.
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
    long cnt(0);
    for (long p = 0; p < s.size(); p += 2) { // Iterate in pairs
      if (s[p] != s[p + 1]) {                // If characters in pair are not equal
        ++cnt;                               // Increment operation count
        s[p + 1] = s[p];                     // Make second character same as first
      }
    }
    std::cout << cnt << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/