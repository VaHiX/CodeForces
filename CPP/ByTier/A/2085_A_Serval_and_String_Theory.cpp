// Problem: CF 2085 A - Serval and String Theory
// https://codeforces.com/contest/2085/problem/A

/*
 * Problem: Serval and String Theory
 * Algorithm/Techniques: String manipulation, lexicographical comparison, greedy swap strategy
 *
 * Time Complexity: O(n) per test case, where n is the length of the string s.
 * Space Complexity: O(n) due to the reversed string t and the input string s.
 *
 * Description:
 * A string r is universal if it is lexicographically smaller than its reverse.
 * Given a string s and at most k swaps, determine if we can make s universal.
 * 
 * Key Idea:
 * - If s is already smaller than its reverse, return YES.
 * - Otherwise, check for possible swaps that can fix the prefix to make s < reverse(s).
 * - If k > 0 and there exists at least one differing adjacent pair, then a swap may help.
 */

#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n, k;
    std::cin >> n >> k;
    std::string s;
    std::cin >> s;

    // Create a reversed version of the string for comparison
    std::string t(s);
    std::reverse(t.begin(), t.end());

    // Check if s is already universal (s < reverse(s))
    bool res(s < t);

    // Flag to track if there's any difference between adjacent characters
    bool diff(false);

    // Loop through the string to find if it has at least one differing adjacent pair
    for (size_t p = 1; !res && k && !diff && p < s.size(); p++) {
      if (s[p - 1] != s[p]) {
        diff = true;
      }
    }

    // If we have at least one swap and there are differing adjacent characters,
    // then it's possible to make the string universal by a single swap
    if (k && diff) {
      res = true;
    }

    std::cout << (res ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/