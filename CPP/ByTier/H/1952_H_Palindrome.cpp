// Problem: CF 1952 H - Palindrome
// https://codeforces.com/contest/1952/problem/H

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

/*
H. Palindrome
Time Complexity: O(n*m) where n is the number of strings and m is the average string length
Space Complexity: O(n*m) for storing the input strings

Algorithms/Techniques:
- String manipulation
- Palindrome checking using string reversal
- Character-by-character processing

The code processes multiple strings and checks if each character-by-character diagonal 
of the input strings forms a palindrome.
*/
int main() {
  std::ios_base::sync_with_stdio(false);
  long n;
  std::cin >> n;
  std::vector<std::string> v(n);
  for (long p = 0; p < n; p++) {
    std::cin >> v[p]; // Read each string into the vector
  }
  for (long idx = 0; idx < n; idx++) {
    std::string s(""); // Create a string to build the diagonal
    for (long row = 0; row < n; row++) {
      if (idx >= v[row].size()) {
        continue; // Skip if index exceeds string length
      }
      s += v[row][idx]; // Add character at position idx from row-th string
    }
    std::string u(s); // Create a copy of the diagonal string
    std::reverse(u.begin(), u.end()); // Reverse the copy
    std::cout << (s == u ? "YES" : "NO") << std::endl; // Check if original equals reversed
  }
}

// https://github.com/VaHiX/codeForces/