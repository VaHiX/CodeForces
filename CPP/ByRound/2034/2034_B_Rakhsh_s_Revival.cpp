// Problem: CF 2034 B - Rakhsh's Revival
// https://codeforces.com/contest/2034/problem/B

/*
B. Rakhsh's Revival
Algorithm: Greedy approach to cover all segments of consecutive '0's with minimal operations.
Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(1), only using a few variables for tracking.

Rostam wants to ensure no interval of m consecutive spots is entirely weak (all '0's).
Using Timar, he can strengthen any segment of k consecutive spots in one operation.
The approach is greedy: whenever we encounter a '0' that isn't already covered by a previous operation,
we trigger a new operation starting from this position to cover up to k positions ahead.
This ensures minimal use of operations and optimal coverage.
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, m, k;
    std::cin >> n >> m >> k;
    std::string s;
    std::cin >> s;
    long z(0), cnt(0), cov(-1); // z: current count of consecutive '0's, cnt: number of operations, cov: last covered index
    for (long p = 0; p < n; p++) {
      if (s[p] == '1' || p <= cov) { // if spot is strong or already covered
        z = 0; // reset consecutive '0' counter
        continue;
      }
      ++z; // increment consecutive '0' counter
      if (z >= m) { // if we've found a segment of m consecutive '0's
        ++cnt; // increment operation count
        cov = p + k - 1; // mark all positions from current to p+k-1 as covered
        z = 0; // reset counter since we've fixed it with an operation
      }
    }
    std::cout << cnt << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/