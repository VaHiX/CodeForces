// Problem: CF 1509 D - Binary Literature
// https://codeforces.com/contest/1509/problem/D

/*
 * Problem: Binary Literature
 * 
 * Purpose: Given three binary strings of length 2n each, construct a binary string of length at most 3n
 *          that contains at least two of the three input strings as subsequences.
 * 
 * Algorithm:
 * - Try to interleave characters from two strings at a time, prioritizing common characters.
 * - When no common character is found between two strings, append the rest of the remaining string.
 * 
 * Time Complexity: O(n) per test case, where n is the length of each input string.
 * Space Complexity: O(n) for storing the constructed result string.
 * 
 * Techniques:
 * - Two-pointer technique for interleaving.
 * - Greedy selection of characters to form a valid subsequence.
 */

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string a, b, c;
    std::cin >> a >> b >> c;
    long x(0), y(0), z(0); // Pointers for strings a, b, c
    std::string t(""); // Result string
    // Try to merge characters from a, b, and c greedily
    for (long p = 0; p < 3 * n && x < a.size() && y < b.size() && z < c.size();
         p++) {
      if (a[x] == b[y]) {
        t += a[x];
        ++x;
        ++y;
      } else if (a[x] == c[z]) {
        t += a[x];
        ++x;
        ++z;
      } else if (b[y] == c[z]) {
        t += b[y];
        ++y;
        ++z;
      }
    }
    // Append remaining characters based on which strings are exhausted
    if (x == a.size() && y <= z) {
      for (long p = z; p < c.size(); p++) {
        t += c[p];
      }
    } else if (x == a.size() && z <= y) {
      for (long p = y; p < b.size(); p++) {
        t += b[p];
      }
    } else if (y == b.size() && x <= z) {
      for (long p = z; p < c.size(); p++) {
        t += c[p];
      }
    } else if (y == b.size() && z <= x) {
      for (long p = x; p < a.size(); p++) {
        t += a[p];
      }
    } else if (z == c.size() && x <= y) {
      for (long p = y; p < b.size(); p++) {
        t += b[p];
      }
    } else if (z == c.size() && y <= x) {
      for (long p = x; p < a.size(); p++) {
        t += a[p];
      }
    }
    std::cout << t << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/