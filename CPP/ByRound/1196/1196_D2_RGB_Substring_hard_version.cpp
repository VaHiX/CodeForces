// Problem: CF 1196 D2 - RGB Substring (hard version)
// https://codeforces.com/contest/1196/problem/D2

/*
Purpose: 
This code solves the problem of finding the minimum number of character changes required in a string of 'R', 'G', 'B' to form a substring of length k that matches a repeating pattern "RGBRGBRGB...".
It uses a sliding window technique to compare the input string against all possible rotations of the pattern "RGB".

Algorithms/Techniques:
- Sliding window technique
- Modular arithmetic to cycle through the pattern "RGB"
- Optimization to check all three starting positions of the pattern

Time Complexity: O(n) where n is the length of the string s, since each character is visited a constant number of times.
Space Complexity: O(1) as only a few variables are used regardless of input size.
*/

#include <iostream>
#include <string>

int main() {
  const std::string templ = "RGB"; // Template pattern to match against
  long q;
  std::cin >> q;
  while (q--) {
    long n, k;
    std::cin >> n >> k;
    std::string s;
    std::cin >> s;
    long mn(1e9); // Initialize minimum changes needed to a large value
    for (long d = 0; d < 3; d++) { // Try each of the 3 starting positions of the pattern
      long cnt(0), mind(1e9); // cnt counts mismatches in current window, mind tracks min in window
      for (long p = 0; p < n; p++) {
        // If current character doesn't match the pattern at position (d + p) % 3, increment mismatch count
        if (s[p] != templ[(d + p) % 3]) {
          ++cnt;
        }
        // If we've moved beyond the window size, decrement the count for the character leaving the window
        if (p >= k && s[p - k] != templ[(d + p - k) % 3]) {
          --cnt;
        }
        // Once we have a full window of size k, update the minimum mismatch count
        if (p >= k - 1) {
          mind = (mind < cnt) ? mind : cnt;
        }
      }
      mn = (mn < mind) ? mn : mind; // Update global minimum
    }
    std::cout << mn << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/