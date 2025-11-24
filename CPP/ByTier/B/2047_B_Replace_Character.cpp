// Problem: CF 2047 B - Replace Character
// https://codeforces.com/contest/2047/problem/B

/*
B. Replace Character
Purpose:
  Given a string of lowercase English letters, perform exactly one operation:
  choose two indices i and j, set s[i] := s[j], to minimize the number of distinct permutations of the string.

Algorithm:
  - For each test case:
    1. Count frequency of each character.
    2. Find the character with minimum frequency (mnc) and maximum frequency (mxc).
    3. Replace the first occurrence of mnc with mxc to reduce distinct permutations.

Time Complexity: O(n), where n is the length of the string.
Space Complexity: O(1), since we use a fixed-size array of size 26 for character counts.

Techniques:
  - Frequency counting
  - Single pass over the string to find min/max characters
  - In-place replacement

*/

#include <iostream>
#include <string>

int main() {
  const int B = 26; // Number of lowercase English letters
  std::ios_base::sync_with_stdio(false); // Faster I/O
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    long v[B] = {0}; // Frequency array for characters 'a' to 'z'
    for (long p = 0; p < s.size(); p++) {
      ++v[s[p] - 'a']; // Count each character
    }
    long mn(s.size()), mx(0); // Initialize min and max frequencies
    char mnc(' '), mxc(' '); // Characters with min and max frequencies
    for (long p = 0; p < B; p++) {
      if (!v[p]) {
        continue; // Skip characters that don't appear
      }
      if (v[p] < mn) {
        mn = v[p];
        mnc = ('a' + p); // Update min frequency character
      }
      if (v[p] >= mx) {
        mx = v[p];
        mxc = ('a' + p); // Update max frequency character
      }
    }
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == mnc) {
        s[p] = mxc; // Replace first occurrence of min freq char with max freq char
        break;
      }
    }
    std::cout << s << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/