// Problem: CF 1400 A - String Similarity
// https://codeforces.com/contest/1400/problem/A

/*
Code Purpose:
This code solves the problem of constructing a binary string `w` of length `n` that is similar to all substrings of `s` of length `n` starting at positions 1, 2, ..., n. 
The approach is to select the last character of the string `s` and replicate it `n` times to form the result string `w`. This ensures that `w` will match at least one character with each substring of `s` of length `n`, since `w` will share the same character at the last position with all substrings.

Algorithms/Techniques:
- Greedy approach: Selecting the last character of `s` ensures that `w` will be similar to all substrings since each substring contains this character at position `n`.

Time Complexity: O(n) per test case
Space Complexity: O(n) for the output string `w`
*/

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    // Create a string of length n filled with the last character of s
    std::string h(n, s[n - 1]);
    std::cout << h << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/