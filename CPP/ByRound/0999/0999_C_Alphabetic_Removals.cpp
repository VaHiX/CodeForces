// Problem: CF 999 C - Alphabetic Removals
// https://codeforces.com/contest/999/problem/C

/*
 * Problem: C. Alphabetic Removals
 * Algorithm: Greedily remove characters in lexicographical order
 * Time Complexity: O(n * 26) = O(n) since 26 is constant
 * Space Complexity: O(n) for the string storage
 *
 * The algorithm works by iterating through letters 'a' to 'z' and for each letter,
 * removing the leftmost occurrence until k characters are removed.
 * We use a placeholder '_' to mark removed characters and then output the rest.
 */

#include <iostream>
#include <string>

int main() {
  const int N = 26; // Number of lowercase letters
  std::ios_base::sync_with_stdio(false); // Faster I/O
  long n, k;
  std::cin >> n >> k;
  std::string s;
  std::cin >> s;
  long rem(k); // Number of characters left to remove
  
  // Iterate through each letter from 'a' to 'z'
  for (long u = 0; u < N; u++) {
    char c = 'a' + u; // Current character to remove
    if (rem <= 0) {
      break; // No more characters to remove
    }
    // Traverse the string to find and remove leftmost occurrences
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == c) {
        s[p] = '_'; // Mark character as removed
        --rem; // Decrease remaining count
        if (rem <= 0) {
          break; // Stop once we've removed enough
        }
      }
    }
  }
  
  // Output the resulting string (excluding marked removed characters)
  for (long p = 0; p < s.size(); p++) {
    if (s[p] == '_') {
      continue; // Skip removed characters
    }
    std::cout << s[p];
  }
  std::cout << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/