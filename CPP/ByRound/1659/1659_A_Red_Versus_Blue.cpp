// Problem: CF 1659 A - Red Versus Blue
// https://codeforces.com/contest/1659/problem/A

/*
 * Problem: A. Red Versus Blue
 * Purpose: Generate a string of length n with r 'R's and b 'B's such that the maximum 
 *          consecutive wins by either team is minimized.
 * Algorithm: Greedily distribute red flowers (R) as evenly as possible among blue segments (B),
 *            placing one extra R in the first m segments to balance the distribution.
 * Time Complexity: O(n) per test case, since we iterate through n characters once.
 * Space Complexity: O(1) additional space (excluding output string).
 */

#include <iostream>
int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, r, b;
    std::cin >> n >> r >> b;
    long d = r / (b + 1);  // Base number of R's per segment
    long m = r % (b + 1);  // Extra R's to be distributed one each in first m segments
    for (long p = 0; p <= b; p++) {  // For each of the (b+1) segments
      for (long u = 0; u < d + (p < m); u++) {  // Add required R's to current segment
        std::cout << "R";
      }
      if (p < b) {  // Place a B only between segments, not after the last one
        std::cout << "B";
      }
    }
    std::cout << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/