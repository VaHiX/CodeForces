// Problem: CF 645 C - Enduring Exodus
// https://codeforces.com/contest/645/problem/C

/*
Purpose: 
This code solves the problem of finding the minimum possible maximum distance 
between Farmer John's room and his farthest cow when booking k+1 unoccupied rooms 
in a hotel with n rooms. It uses a sliding window approach combined with binary 
search logic to optimize the placement of rooms.

Algorithms/Techniques:
- Two-pointer technique with sliding window to find optimal placement of k+1 rooms.
- Preprocessing to collect indices of all free rooms ('0').
- Optimization to minimize the maximum distance between Farmer John and his cows.

Time Complexity: O(n)
Space Complexity: O(n)

The algorithm first collects all indices of free rooms, then uses a sliding window 
to check every possible group of k+1 consecutive free rooms. For each such group, 
it computes the optimal placement of Farmer John (in the middle) to minimize 
the maximum distance to any cow.

*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long n, k;
  std::cin >> n >> k;
  std::string s;
  std::cin >> s;
  std::vector<long> v;
  for (long p = 0; p < s.size(); p++) {
    if (s[p] == '0') {
      v.push_back(p);
    }
  }
  long m(0), dist(2 * s.size());
  for (long p = k; p < v.size(); ++p) {
    long b = p - k;
    // Adjust m to find the optimal position for John (middle of the window)
    while (v[m] - v[b] <= v[p] - v[m]) {
      ++m;
    }
    // Compute distances from John to leftmost and rightmost cow in current window
    long left(v[m] - v[b]), right(v[p] - v[m]);
    long mx = (left > right) ? left : right;
    dist = (dist < mx) ? dist : mx;
    // Also consider the previous candidate for John's position
    left = v[m - 1] - v[b];
    right = v[p] - v[m - 1];
    mx = (left > right) ? left : right;
    dist = (dist < mx) ? dist : mx;
  }
  std::cout << dist << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/