// Problem: CF 451 D - Count Good Substrings
// https://codeforces.com/contest/451/problem/D

/*
Purpose: Count good substrings of even and odd length in a string of 'a' and 'b'.
         A good substring becomes a palindrome after merging consecutive equal characters.
Algorithm: Sliding window technique with prefix counting.
           - For each character, we maintain a count of previous characters at even/odd positions.
           - When processing a character, we lookup how many valid substrings end at this position.
Time Complexity: O(n) - single pass through the string
Space Complexity: O(1) - fixed size arrays of size 2x2 and 2
*/
#include <cstdio>
#include <iostream>
#include <string>

int main() {
  // parity[c][p%2] stores count of characters c seen at positions with remainder p%2
  long long parity[2][2] = {{0, 0}, {0, 0}};
  long long output[2] = {0, 0};  // output[0] for even length, output[1] for odd length
  std::string s;
  getline(std::cin, s);
  for (long p = 0; p < s.size(); p++) {
    int c = s[p] - 'a';  // Convert character to 0 or 1 (a -> 0, b -> 1)
    ++parity[c][p % 2];  // Increment count of character c at even/odd position
    output[0] += parity[c][(p + 1) % 2];  // Add count of matching characters at opposite parity for even-length substrings
    output[1] += parity[c][p % 2];       // Add count of matching characters at same parity for odd-length substrings
  }
  printf("%lld %lld\n", output[0], output[1]);
  return 0;
}


// https://github.com/VaHiX/CodeForces/