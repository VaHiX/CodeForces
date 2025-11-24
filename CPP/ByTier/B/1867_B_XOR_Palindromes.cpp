// Problem: CF 1867 B - XOR Palindromes
// https://codeforces.com/contest/1867/problem/B

/*
B. XOR Palindromes
Algorithms/Techniques: String manipulation, XOR operation, palindrome checking, counting mismatches.
Time Complexity: O(n) per test case, where n is the length of the string s.
Space Complexity: O(n), for storing the result string res.

The problem asks us to determine which numbers x (from 0 to n) are "good".
A number x is good if there exists a binary string l of length n with exactly x ones,
such that when we XOR s with l, the resulting string becomes a palindrome.

Key observations:
- To make a string palindrome after XOR, we need to ensure that s[i] ^ l[i] == s[n-1-i] ^ l[n-1-i]
- By rearranging: s[i] ^ s[n-1-i] == l[i] ^ l[n-1-i]
- This means that if s[i] != s[n-1-i], then l[i] must differ from l[n-1-i].
- The number of mismatches in the first half determines how many such pairs there are.
- We calculate how many valid values of x can result in a palindrome.

The core idea:
- Count the number of mismatched character pairs in the first half of s.
- For a palindrome after XOR, we must flip the same number of bits from each such pair.
- The total number of 1s in l is constrained by how many bit flips we perform and the positions.
- Use mathematical constraints to determine for which x values it works.
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    long cnt(0);
    // Count number of mismatched pairs in the first half
    for (long p = 0; p < n - 1 - p; p++) {
      cnt += (s[p] != s[n - 1 - p]);
    }
    std::string res(n + 1, '0');
    // Mark positions where x is good
    for (long p = cnt; p + cnt <= n; p++) {
      if ((n % 2) || ((p - cnt) % 2 == 0)) {
        res[p] = '1';
      }
    }
    std::cout << res << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/