// Problem: CF 1829 A - Love Story
// https://codeforces.com/contest/1829/problem/A

/*
A. Love Story
time limit per test1 second
memory limit per test256 megabytes

Problem Description:
Timur has a string of exactly 10 lowercase Latin letters. He wants to find how many indices 
this string differs from the string "codeforces". This is essentially counting the number 
of positions where two strings differ.

Algorithms/Techniques:
- String comparison by character-by-character iteration
- Linear scan approach

Time Complexity: O(t * n) where t is number of test cases and n is string length (10 in this case)
Space Complexity: O(1) - only using fixed amount of extra space regardless of input size

*/

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  const std::string w = "codeforces";  // Target string to compare against
  while (t--) {
    std::string s;
    std::cin >> s;
    long res(0);  // Initialize result counter for differences
    for (long p = 0; p < w.size() && p < s.size(); p++) {  // Compare up to minimum length
      res += (w[p] != s[p]);  // Increment if characters at position p are different
    }
    std::cout << res << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/