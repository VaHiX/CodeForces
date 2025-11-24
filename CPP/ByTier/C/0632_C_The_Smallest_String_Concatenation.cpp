// Problem: CF 632 C - The Smallest String Concatenation
// https://codeforces.com/contest/632/problem/C

/*
 * Problem: C. The Smallest String Concatenation
 * 
 * Algorithm/Technique: Custom Sorting
 * 
 * Time Complexity: O(n log n * L), where n is the number of strings and L is the average length of strings.
 * Space Complexity: O(n * L), for storing the strings.
 * 
 * The problem requires arranging a list of strings such that their concatenation forms the lexicographically smallest string.
 * This is a classic application of custom sorting. Instead of comparing strings directly,
 * we compare two strings s and t by checking whether s+t < t+s lexicographically.
 * This ensures that when we sort the strings using this comparator, the final concatenation is minimized.
 * 
 * Example:
 *   For strings "abba" and "abacaba", we check:
 *   "abba" + "abacaba" = "abbaabacaba"
 *   "abacaba" + "abba" = "abacababba"
 *   Since "abacababba" < "abbaabacaba", we place "abacaba" before "abba".
 */

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

// Custom comparator: returns true if s+t is lexicographically smaller than t+s
bool cmp(std::string s, std::string t) { return (s + t) < (t + s); }

int main() {
  std::ios_base::sync_with_stdio(false);  // Optimize I/O speed
  long n;
  std::cin >> n;
  std::vector<std::string> a(n);
  for (long p = 0; p < n; p++) {
    std::cin >> a[p];  // Read all strings into vector
  }
  sort(a.begin(), a.end(), cmp);  // Sort strings using custom comparator
  for (long p = 0; p < n; p++) {
    std::cout << a[p];  // Output concatenated result
  }
  std::cout << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/