// Problem: CF 1722 A - Spell Check
// https://codeforces.com/contest/1722/problem/A

/*
 * Purpose: Check if a given string is a valid spelling of "Timur".
 *          A valid spelling is any permutation of the letters in "Timur",
 *          with exactly one 'T' (uppercase) and four other letters (lowercase).
 *
 * Algorithms/Techniques:
 *   - Sorting strings to compare their character compositions.
 *   - For each test case, sort both the target ("Timur") and input string,
 *     then check for equality.
 *
 * Time Complexity: O(t * n * log(n)) where t is number of test cases and n is string length.
 *                  Sorting takes O(n * log(n)) per string.
 *
 * Space Complexity: O(n) for storing input strings and temporary sorted copies.
 */

#include <algorithm>
#include <iostream>
#include <string>

int main() {
  std::string target = "Timur";
  sort(target.begin(), target.end()); // Sort the target string to prepare for comparison
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    sort(s.begin(), s.end()); // Sort the input string for comparison
    std::cout << ((s == target) ? "YES" : "NO") << std::endl; // Output result based on equality
  }
}


// https://github.com/VaHiX/codeForces/