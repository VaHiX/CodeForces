// Problem: CF 1251 B - Binary Palindromes
// https://codeforces.com/contest/1251/problem/B

/*
B. Binary Palindromes
Algorithms/Techniques: Greedy, String manipulation, Bit manipulation
Time Complexity: O(Q * N * L) where Q is number of test cases, N is number of strings, and L is average string length
Space Complexity: O(1) - only using a few variables for counting
*/

#include <iostream>
#include <string>

int main() {
  long q;
  std::cin >> q;
  while (q--) {
    long n;
    std::cin >> n;
    int z(0), f(0); // z: count of zeros mod 2, f: flag for odd-length strings
    for (long p = 0; p < n; p++) {
      std::string s;
      std::cin >> s;
      f |= (s.size() % 2); // if any string has odd length, set f = 1
      for (long u = 0; u < s.size(); u++) {
        z += (s[u] == '0'); // count zeros
      }
      z %= 2; // keep only parity of zero count
    }
    std::cout << (n - 1 + (f || !z)) << std::endl; // compute max palindromes possible
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/