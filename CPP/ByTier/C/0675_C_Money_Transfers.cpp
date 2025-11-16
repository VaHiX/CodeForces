// Problem: CF 675 C - Money Transfers
// https://codeforces.com/contest/675/problem/C

/*
C. Money Transfers
Algorithm: Greedy with prefix sums and map usage
Time Complexity: O(n log n) due to map operations
Space Complexity: O(n) for storing prefix sums in map

The problem is about minimizing the number of transfers to balance all banks to zero.
We use prefix sums to determine how much money needs to be moved between adjacent banks.
Each time a prefix sum repeats, it indicates a complete cycle that can be handled with one less operation.
*/

#include <stdint.h>
#include <iostream>
#include <map>
#include <utility>

int main() {
  std::ios_base::sync_with_stdio(false);
  int64_t n;
  std::cin >> n;
  std::map<int64_t, int64_t> m; // Map to store frequency of prefix sums
  int64_t cumTotal(0); // Running sum of balances
  for (int64_t p = 0; p < n; p++) {
    int64_t x;
    std::cin >> x;
    cumTotal += x; // Add current balance to cumulative total
    if (m.count(cumTotal) > 0) { // If prefix sum already exists
      ++m[cumTotal]; // Increment count
    } else {
      m[cumTotal] = 1; // Initialize count
    }
  }
  int64_t maxComponents = 0;
  for (std::map<int64_t, int64_t>::iterator it = m.begin(); it != m.end();
       it++) {
    maxComponents =
        (maxComponents > (it->second) ? maxComponents : (it->second)); // Find maximum frequency
  }
  std::cout << (n - maxComponents) << std::endl; // Minimum operations needed
  return 0;
}


// https://github.com/VaHiX/codeForces/