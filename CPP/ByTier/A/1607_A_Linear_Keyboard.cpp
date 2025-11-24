// Problem: CF 1607 A - Linear Keyboard
// https://codeforces.com/contest/1607/problem/A

/*
 * Problem: A. Linear Keyboard
 * Purpose: Determine the minimum time to type a word on a given keyboard layout.
 * Algorithm: 
 *   - For each test case, precompute the position of each letter in the keyboard.
 *   - Then iterate through the word, calculating the absolute difference between consecutive letters' positions.
 *   - Sum these differences to get total typing time.
 * 
 * Time Complexity: O(n + m) where n is length of keyboard (26) and m is length of word.
 * Space Complexity: O(1) since we use a fixed-size vector of 26 elements.
 */

#include <iostream>
#include <vector>
#include <string>

int main() {
  const int L = 26;
  long t;
  std::cin >> t;
  while (t--) {
    std::string keyboard;
    std::cin >> keyboard;
    // v[i] stores the position of character 'a' + i in the keyboard
    std::vector<long> v(L, 0);
    for (long p = 0; p < L; p++) {
      v[keyboard[p] - 'a'] = p;
    }
    std::string s;
    std::cin >> s;
    // Start position is the index of first character in the keyboard
    long pos = v[s[0] - 'a'];
    long dist(0);
    // Iterate over the rest of the characters in the word
    for (long p = 1; p < s.size(); p++) {
      long nextPos = v[s[p] - 'a'];
      long diff = nextPos - pos;
      dist += (diff > 0) ? diff : -diff;
      pos = nextPos;
    }
    std::cout << dist << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/