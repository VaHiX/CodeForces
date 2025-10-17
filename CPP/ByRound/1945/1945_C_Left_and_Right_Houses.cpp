// Problem: CF 1945 C - Left and Right Houses
// https://codeforces.com/contest/1945/problem/C

/*
C. Left and Right Houses
Algorithm: Prefix Sums + Two Pointers/Brute Force with Optimization

Purpose:
This code determines the optimal position for a road that splits a village into left and right sides such that at least half of the residents on each side are satisfied with their assignment. The solution minimizes the distance from the middle of the village.

Time Complexity: O(n) per test case, where n is the length of the string s.
Space Complexity: O(n) for storing prefix sums.

Approach:
1. Precompute prefix sums for zeros (vl) and suffix sums for ones (vr).
2. For each possible road position i (from 0 to n), check if the left side satisfies the constraint (at least ⌈i/2⌉ zeros)
   and the right side satisfies the constraint (at least ⌈(n-i)/2⌉ ones).
3. Among valid positions, select the one closest to the middle of the village.

The code uses prefix/suffix sums for quick evaluation of constraints.
*/
#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    std::vector<long> vl(n + 1, 0), vr(n + 1, 0);
    // Compute prefix sum of zeros
    for (long p = 1; p <= n; p++) {
      vl[p] = vl[p - 1] + (s[p - 1] == '0');
    }
    // Compute suffix sum of ones
    for (long p = n - 1; p >= 0; p--) {
      vr[p] = vr[p + 1] + (s[p] == '1');
    }
    long idx(-1);
    float mindist(n + 7);
    // Try all possible positions for the road
    for (long p = 0; p <= n; p++) {
      // Check if left side has enough zeros (at least ceil(p/2))
      if (2 * vl[p] < p) {
        continue;
      }
      // Check if right side has enough ones (at least ceil((n-p)/2))
      if (2 * vr[p] < (n - p)) {
        continue;
      }
      float dist = 0.5 * n - p;
      if (dist < 0) {
        dist = -dist + 0.1; // Adjust for negative distance
      }
      if (dist < mindist) {
        mindist = dist;
        idx = p;
      }
    }
    std::cout << idx << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/