// Problem: CF 844 A - Diversity
// https://codeforces.com/contest/844/problem/A

/*
 * Problem: A. Diversity
 * 
 * Purpose: Calculate the minimum number of character changes needed in a string
 *          to ensure it contains at least k different letters.
 * 
 * Approach:
 * - Count the number of unique characters in the string using a set.
 * - If k is greater than the string length or greater than 26 (total lowercase letters),
 *   it's impossible to achieve k distinct characters.
 * - Otherwise, the number of changes needed is max(0, k - number_of_unique_chars).
 * 
 * Time Complexity: O(n), where n is the length of the string (due to iteration through string and set operations)
 * Space Complexity: O(1), since the size of the set is bounded by 26 (constant number of lowercase letters)
 * 
 * Algorithms/Techniques:
 * - Set data structure to count unique characters
 * - Simple arithmetic to determine required changes
 */

#include <iostream>
#include <set>
#include <string>

int main() {
  const int N = 26;
  std::string s;
  std::cin >> s;
  int k;
  std::cin >> k;
  std::set<char> t; // Set to store unique characters
  for (int p = 0; p < s.size(); p++) {
    t.insert(s[p]); // Insert each character into the set to count unique ones
  }
  if (k > s.size() || k > N) {
    // Impossible case: k exceeds string length or total possible letters
    std::cout << "impossible" << std::endl;
  } else {
    // Calculate minimum changes needed
    std::cout << ((k > t.size()) ? (k - t.size()) : 0) << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/