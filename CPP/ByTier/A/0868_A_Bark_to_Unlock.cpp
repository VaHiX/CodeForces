// Problem: CF 868 A - Bark to Unlock
// https://codeforces.com/contest/868/problem/A

/*
 * Problem: Bark to Unlock
 * 
 * Purpose: Determine if a given password (two lowercase letters) can be formed 
 *          as a substring by concatenating two words from a known set of words.
 * 
 * Algorithm: 
 *   - Try all combinations of two words from the list (with repetition allowed).
 *   - Concatenate each pair and check if the password appears as a substring.
 *   - If found, output "YES", otherwise "NO".
 * 
 * Time Complexity: O(n^2 * m), where n is the number of words and m is the average 
 *                  length of the concatenated string (which is 4 since each word is 2 chars).
 * 
 * Space Complexity: O(n), for storing the list of words.
 * 
 * Techniques:
 *   - Brute-force approach with nested loops over all possible word pairs.
 *   - String concatenation and substring search.
 */

#include <iostream>
#include <string>
#include <vector>
int main() {
  std::string pw;
  std::cin >> pw;
  int n;
  std::cin >> n;
  std::vector<std::string> v(n);
  for (long p = 0; p < n; p++) {
    std::cin >> v[p];
  }
  bool found(false);
  for (long a = 0; a < n; a++) {
    if (found) {
      break;
    }
    for (long b = 0; b < n; b++) {
      std::string s = v[a] + v[b]; // Concatenate two words
      if (s.find(pw) != std::string::npos) { // Check if password is substring
        found = true;
        break;
      }
    }
  }
  std::cout << (found ? "YES" : "NO") << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/