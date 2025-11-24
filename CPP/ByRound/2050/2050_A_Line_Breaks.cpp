// Problem: CF 2050 A - Line Breaks
// https://codeforces.com/contest/2050/problem/A

/*
 * Problem: Maximize number of words that fit on first strip
 * Algorithm: Greedily accumulate words until the total length exceeds m.
 * Time Complexity: O(n * L) where n is number of words and L is average word length
 * Space Complexity: O(1) excluding input storage
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, m;
    std::cin >> n >> m;
    long x(0);                             // x stores the maximum number of words that fit
    for (long p = 0; p < n; p++) {         // Iterate through each word
      std::string s;
      std::cin >> s;
      if (s.size() <= m) {                 // If current word fits in remaining space
        x = p + 1;                         // Update max words count
        m -= s.size();                     // Deduct word length from available space
      } else {
        m = 0;                             // Word doesn't fit, so no more words can be added
      }
    }
    std::cout << x << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/