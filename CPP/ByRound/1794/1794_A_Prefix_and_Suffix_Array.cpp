// Problem: CF 1794 A - Prefix and Suffix Array
// https://codeforces.com/contest/1794/problem/A

/*
Problem: Determine if a string s is a palindrome given all its non-empty prefixes and suffixes (excluding s itself).

Algorithms/Techniques:
- Prefix and Suffix Array

Time Complexity: O(n^2) per test case due to string operations and sorting of prefixes/suffixes.
Space Complexity: O(n^2) for storing the input strings.

Input Format:
Each test case contains:
- n (length of the string s)
- 2n - 2 strings representing all non-empty prefixes and suffixes of s (excluding s)

Output Format:
"YES" if s is a palindrome, "NO" otherwise.
*/

#include <algorithm>
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string x(""), y("");
    for (long p = 0; p < 2 * n - 2; p++) {
      std::string cur;
      std::cin >> cur;
      if (cur.size() == n - 1) { // Check if current string is a prefix/suffix of length n-1
        if (x.size() == 0) {
          x = cur;
        } else {
          y = cur;
        }
      }
    }
    std::reverse(x.begin(), x.end()); // Reverse one of the strings to check palindrome property
    std::cout << (x == y ? "YES" : "NO") << std::endl; // If reversed x equals y, then s is palindrome
  }
}


// https://github.com/VaHiX/codeForces/