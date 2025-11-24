// Problem: CF 813 B - The Golden Age
// https://codeforces.com/contest/813/problem/B

/*
Purpose: 
  Find the maximum length of a "Golden Age" interval within [l, r], where a "Golden Age" is defined as an interval with no "unlucky" years.
  An unlucky year n can be represented as n = x^a + y^b, where a and b are non-negative integers.
  
  The approach:
    1. Generate all possible unlucky years within [l, r] by computing x^a + y^b for reasonable values of a and b.
    2. Sort these unlucky years along with the boundaries l-1 and r+1.
    3. Compute the maximum gap between consecutive elements in the sorted list, which corresponds to the longest "Golden Age" interval.

Algorithms:
  - Brute-force generation of x^a + y^b values within range
  - Sorting and linear scan to find maximum gap

Time Complexity: O(N^2 * log(N)) where N is around 60 (as x^a and y^b are bounded by 10^18)
Space Complexity: O(N^2) for storing the candidate unlucky years plus boundaries
*/
#include <stdint.h>
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

int main() {
  const int N = 60; // Upper bound for exponents (since values can be up to 10^18)
  int64_t x, y, l, r;
  std::cin >> x >> y >> l >> r;
  std::vector<int64_t> v;
  v.push_back(l - 1); // Add left boundary to simplify gap calculation
  v.push_back(r + 1); // Add right boundary to simplify gap calculation
  int64_t powx = 1;
  for (int a = 0; a < N; a++) {
    int64_t powy = 1;
    for (int b = 0; b < N; b++) {
      int64_t cand = powx + powy;
      if (l <= cand && cand <= r) {
        int64_t z = cand;
        v.push_back(z); // Add candidate unlucky year
      }
      if (powy > LLONG_MAX / y) {
        break; // Prevent overflow
      }
      powy *= y;
    }
    if (powx > LLONG_MAX / x) {
      break; // Prevent overflow
    }
    powx *= x;
  }
  sort(v.begin(), v.end()); // Sort all candidates
  int64_t golden(0);
  for (long p = 1; p < v.size(); p++) {
    int64_t diff = v[p] - v[p - 1] - 1; // Gap between two consecutive entries
    golden = (golden > diff) ? golden : diff; // Track maximum gap
  }
  std::cout << golden << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/