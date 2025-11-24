// Problem: CF 1860 A - Not a Substring
// https://codeforces.com/contest/1860/problem/A

/*
 * Problem: Not a Substring
 * 
 * Algorithm/Technique:
 * - The goal is to find a regular bracket sequence t of length 2n such that s does not occur as a contiguous substring.
 * - A regular bracket sequence has equal numbers of '(' and ')', and at no point in the sequence do the number of ')' exceed the number of '('.
 * - We construct two candidate sequences:
 *   1. x = "((...))" (n opening then n closing brackets)
 *   2. y = "()()()..." (alternating pairs)
 * - For each sequence, we check if s is a substring.
 * - If x is valid (doesn't contain s), we output x.
 * - Else if y is valid, we output y.
 * - Otherwise, it's impossible.
 * 
 * Time Complexity: O(n^2) per test case (due to substring search)
 * Space Complexity: O(n) for storing the constructed strings
 */

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    // Construct x as all opening brackets followed by all closing brackets
    std::string x = std::string(s.size(), '(') + std::string(s.size(), ')');
    // Construct y as alternating pairs of "()"
    std::string y("");
    for (long p = 0; p < s.size(); p++) {
      y += "()";
    }
    // Check if s is not a substring of x
    if (x.find(s) == std::string::npos) {
      std::cout << "YES\n" << x << std::endl;
    } 
    // Check if s is not a substring of y
    else if (y.find(s) == std::string::npos) {
      std::cout << "YES\n" << y << std::endl;
    } 
    // If both x and y contain s, then no solution exists
    else {
      std::cout << "NO" << std::endl;
    }
  }
}


// https://github.com/VaHiX/CodeForces/