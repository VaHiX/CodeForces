// Problem: CF 1609 B - William the Vigilant
// https://codeforces.com/contest/1609/problem/B

/*
 * Problem: B. William the Vigilant
 * Purpose: Efficiently maintain count of "abc" substrings in a string under character updates.
 * Algorithm:
 *   - Precompute initial count of "abc" patterns in string.
 *   - For each update query:
 *     - Adjust count based on changes around updated position.
 *     - Update character and output new count.
 *
 * Time Complexity: O(n + q) where n is string length and q is number of queries.
 * Space Complexity: O(n) for storing the string.
 */
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long n, q;
  std::cin >> n >> q;
  std::string s;
  std::cin >> s;
  long cnt(0);
  // Count initial occurrences of "abc"
  for (long p = 2; p < s.size(); p++) {
    cnt += (s[p - 2] == 'a' && s[p - 1] == 'b' && s[p] == 'c');
  }
  while (q--) {
    long w;
    char c;
    std::cin >> w >> c;
    --w; // Convert to 0-based indexing
    if (s[w] != c && c == 'a') { // Replacing with 'a'
      // Check and decrement counter for patterns that end at position w
      if (w >= 2 && s[w - 2] == 'a' && s[w - 1] == 'b' && s[w] == 'c') {
        --cnt;
      }
      // Check and decrement counter for patterns containing position w
      if (w >= 1 && s[w - 1] == 'a' && s[w] == 'b' && w + 1 < s.size() &&
          s[w + 1] == 'c') {
        --cnt;
      }
      s[w] = c; // Update character
      // Check and increment counter for new patterns starting at position w
      if (w + 2 < s.size() && s[w + 1] == 'b' && s[w + 2] == 'c') {
        ++cnt;
      }
    } else if (s[w] != c && c == 'b') { // Replacing with 'b'
      // Check and decrement counter for patterns that end at position w
      if (w >= 2 && s[w - 2] == 'a' && s[w - 1] == 'b' && s[w] == 'c') {
        --cnt;
      }
      // Check and decrement counter for patterns containing position w
      if (w + 2 < s.size() && s[w] == 'a' && s[w + 1] == 'b' &&
          s[w + 2] == 'c') {
        --cnt;
      }
      s[w] = c; // Update character
      // Check and increment counter for new patterns starting at position w
      if (w >= 1 && s[w - 1] == 'a' && s[w] == 'b' && w + 1 < s.size() &&
          s[w + 1] == 'c') {
        ++cnt;
      }
    } else if (s[w] != c && c == 'c') { // Replacing with 'c'
      // Check and decrement counter for patterns that end at position w
      if (w + 2 < s.size() && s[w] == 'a' && s[w + 1] == 'b' &&
          s[w + 2] == 'c') {
        --cnt;
      }
      // Check and decrement counter for patterns containing position w
      if (w >= 1 && s[w - 1] == 'a' && s[w] == 'b' && w + 1 < s.size() &&
          s[w + 1] == 'c') {
        --cnt;
      }
      s[w] = c; // Update character
      // Check and increment counter for new patterns starting at position w
      if (w >= 2 && s[w - 2] == 'a' && s[w - 1] == 'b' && s[w] == 'c') {
        ++cnt;
      }
    }
    std::cout << cnt << std::endl; // Output current count of "abc" substrings
  }
}


// https://github.com/VaHiX/codeForces/