// Problem: CF 1775 A1 - Gardener and the Capybaras (easy version)
// https://codeforces.com/contest/1775/problem/A1

/*
 * Code Purpose: 
 * This code solves the problem of splitting a given string of 'a' and 'b' characters into three parts (a, b, c) 
 * such that either a <= b and c <= b OR b <= a and b <= c (lexicographically), satisfying the capybara name property.
 * 
 * Approach:
 * The key insight is to try different ways to split the string and check the lexicographical conditions.
 * The code tries to split the string into three parts in a way that ensures that one of the two conditions is met.
 * A simple heuristic is used:
 * 1. If first and last characters are same, the first part is the first character, middle part is the rest except last, and the last part is the last character.
 * 2. If the second character is 'a', split the string in a way that the second character is a single unit.
 * 3. Otherwise, use a default split approach.
 * 
 * Time Complexity: O(n) where n is the length of the string — each operation is linear.
 * Space Complexity: O(n) — due to storing substrings, which in worst case can be of size n.
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    std::string x(""), y(""), z("");
    
    // Check if first and last characters are the same
    if (s[0] == s.back()) {
      x = s[0]; // First part is the first character
      y = s.substr(1, s.size() - 2); // Middle part is from index 1 to second-to-last
      z = s.back(); // Third part is the last character
    } else if (s[1] == 'a') {
      // If the second character is 'a', try the specific split
      x = s[0]; // First part is first character
      y = s[1]; // Second part is second character
      z = s.substr(2, s.size() - 2); // Third part is from index 2 to end
    } else {
      // Otherwise, use default split strategy
      x = s[0]; // First part is first character
      y = s.substr(1, s.size() - 2); // Middle part is from index 1 to second-to-last
      z = s.back(); // Third part is last character
    }
    
    std::cout << x << " " << y << " " << z << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/