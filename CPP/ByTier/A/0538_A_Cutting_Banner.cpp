// Problem: CF 538 A - Cutting Banner
// https://codeforces.com/contest/538/problem/A

/*
Purpose: Determine if a given string can be transformed into "CODEFORCES" by cutting out one substring.
         A substring is cut out, and the remaining parts are glued back together without reordering.

Algorithms/Techniques: 
    - Brute Force: Try all possible substrings to cut out from the input string.
    - String Concatenation: For each pair of indices (p, q), concatenate the prefix (0 to p-1) 
      and suffix (q+1 to end) to check if it forms the target word.

Time Complexity: O(n^3) where n is the length of the input string.
    - Outer loop: O(n)
    - Inner loop: O(n)
    - String comparison: O(n) in worst case due to substr and concatenation
Space Complexity: O(n) for storing the input string and temporary substrings during comparison.

*/
#include <iostream>
#include <string>

int main() {
  const std::string target = "CODEFORCES"; // Target word to match
  std::string source;
  getline(std::cin, source); // Read the banner string
  std::string ans = "NO"; // Default answer

  // Try all possible substrings to cut out
  for (int p = 0; p < source.size(); p++) {
    for (int q = p; q < source.size(); q++) {
      // Create new string by removing substring from index p to q (inclusive)
      // Concatenate the prefix (0 to p-1) and suffix (q+1 to end)
      if (source.substr(0, p) + source.substr(q + 1) == target) {
        std::cout << "YES\n";
        return 0; // Found a valid cut, exit immediately
      }
    }
  }
  std::cout << "NO\n"; // No valid cut found
  return 0;
}


// https://github.com/VaHiX/CodeForces/