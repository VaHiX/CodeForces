// Problem: CF 1111 A - Superhero Transformation
// https://codeforces.com/contest/1111/problem/A

/*
Problem: Superhero Transformation
Purpose: Determine if two superhero names can be transformed into each other by replacing vowels with vowels and consonants with consonants.
Algorithm: 
    - For each character position, check if the characters in both strings belong to the same category (vowel or consonant).
    - If any position has a mismatch in category (one vowel, one consonant), transformation is not possible.
Time Complexity: O(n), where n is the length of the strings.
Space Complexity: O(1), since we use only a fixed-size string for vowels and a few variables.

Input:
    Two strings s and t of equal length, consisting of lowercase English letters.
Output:
    "Yes" if transformation is possible, "No" otherwise.

Examples:
    Input: a, u -> Output: Yes (both vowels)
    Input: abc, ukm -> Output: Yes (a->u, b->k, c->m; all vowels to vowels, consonants to consonants)
    Input: akm, ua -> Output: No (k is consonant, a is vowel)
*/
#include <iostream>
#include <string>
int main() {
  const std::string vw = "aeiou"; // String containing all vowels
  std::string s, t;               // Input strings
  std::cin >> s >> t;             // Read input strings
  if (s.size() != t.size()) {     // Check if lengths are unequal
    std::cout << "No" << std::endl;
    return 0;
  }
  std::string ans = "Yes";        // Initialize result as "Yes"
  for (long p = 0; p < s.size(); p++) { // Iterate through each character
    bool fs = (vw.find(s[p]) == std::string::npos); // Check if s[p] is consonant
    bool ft = (vw.find(t[p]) == std::string::npos); // Check if t[p] is consonant
    if (fs ^ ft) {                // If one is vowel and other is consonant
      ans = "No";                 // Transformation not possible
      break;
    }
  }
  std::cout << ans << std::endl;  // Output result
  return 0;
}


// https://github.com/VaHiX/codeForces/