// Problem: CF 1466 C - Canine poetry
// https://codeforces.com/contest/1466/problem/C

/*
C. Canine poetry
Time complexity: O(n) where n is the length of the string
Space complexity: O(1) additional space (not counting input/output)

Algorithm:
This solution uses a greedy approach to eliminate palindromes of length > 1.
We iterate through the string and whenever we find a character that creates
a palindrome of length 2 or 3 with its previous characters, we change it to 'X'
and increment our counter. This ensures no palindromic substrings of length > 1
exist in the final string.

The key insight is that we only need to check for palindromes of length 2 and 3,
since longer ones would necessarily contain shorter palindromic substrings.
By changing characters greedily from left to right, we ensure minimal operations.
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
    long cnt(0);
    if (s[1] == s[0]) { // Check for palindrome of length 2 at start
      ++cnt;
      s[1] = 'X'; // Change second character to break palindrome
    }
    for (long p = 2; p < s.size(); p++) {
      if (s[p - 1] == s[p]) { // Check for palindrome of length 2
        s[p] = 'X';
        ++cnt;
      } else if (s[p - 2] == s[p]) { // Check for palindrome of length 3
        s[p] = 'X';
        ++cnt;
      }
    }
    std::cout << cnt << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/