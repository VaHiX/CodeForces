// Problem: CF 1196 D1 - RGB Substring (easy version)
// https://codeforces.com/contest/1196/problem/D1

/*
 * Purpose: Find the minimum number of character changes needed in a string
 *          to form a substring of length k that matches a cyclic pattern "RGB".
 *          The algorithm uses a sliding window approach over three possible
 *          rotations of the pattern "RGB".
 *
 * Algorithms/Techniques:
 *   - Sliding window technique
 *   - Cyclic pattern matching
 *   - Three rotations of pattern "RGB" (starting at indices 0, 1, 2)
 *
 * Time Complexity: O(n * k) where n is the length of string s and k is the length of substring.
 *                  For each of the 3 rotations, we slide a window of size k across the string,
 *                  taking O(n) time for each rotation, thus O(3 * n) = O(n) per query.
 *                  But in the worst case, for sum of n over all queries <= 2000, it's acceptable.
 *
 * Space Complexity: O(1) - only using fixed extra variables regardless of input size.
 */
#include <iostream>
#include <string>

int main() {
  const std::string templ = "RGB";  // The base cyclic pattern to match against
  long q;
  std::cin >> q;
  while (q--) {
    long n, k;
    std::cin >> n >> k;
    std::string s;
    std::cin >> s;
    long mn(1e9);  // Minimum changes needed - initialize to large value
    
    // Try each of the three starting positions of the pattern "RGB"
    for (long d = 0; d < 3; d++) {
      long cnt(0), mind(1e9);  // cnt: number of mismatches in current window, mind: min mismatches seen
      for (long p = 0; p < n; p++) {
        // If current character doesn't match the expected character in the pattern
        if (s[p] != templ[(d + p) % 3]) {
          ++cnt;
        }
        // If the window has moved past the first element, adjust count
        if (p >= k && s[p - k] != templ[(d + p - k) % 3]) {
          --cnt;
        }
        // When we have a full window of size k, record the minimum mismatches
        if (p >= k - 1) {
          mind = (mind < cnt) ? mind : cnt;
        }
      }
      // Update global minimum mismatches
      mn = (mn < mind) ? mn : mind;
    }
    std::cout << mn << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/