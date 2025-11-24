// Problem: CF 1075 B - Taxi drivers and Lyft
// https://codeforces.com/contest/1075/problem/B

/*
B. Taxi drivers and Lyft
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

Problem Description:
Given n riders and m taxi drivers located on a coordinate line, determine how many riders would call each taxi driver if they were the first to order a taxi. Each rider calls the closest taxi driver. If two drivers are equally close, the one with the smaller coordinate is chosen.

Algorithms/Techniques:
- Sorting
- Binary search (implicit via two pointers)
- Two-pointer technique for assigning riders to nearest taxi drivers

Time Complexity: O((n + m) * log(n + m)) due to sorting operations.
Space Complexity: O(n + m) for storing vectors and auxiliary data structures.

*/
#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n, m;
  scanf("%ld %ld", &n, &m); // Read number of riders and taxi drivers
  std::vector<long> x(n + m);
  for (long p = 0; p < n + m; p++) {
    scanf("%ld", &x[p]); // Read all coordinates
  }
  std::vector<long> d, r, cnt(m, 0); // d: taxi drivers, r: riders, cnt: result array
  for (long p = 0; p < m + n; p++) {
    int y;
    scanf("%d", &y); // Read type: 1 for driver, 0 for rider
    if (y) {
      d.push_back(x[p]); // Add coordinate to drivers
    } else {
      r.push_back(x[p]); // Add coordinate to riders
    }
  }
  sort(r.begin(), r.end()); // Sort riders by coordinate
  sort(d.begin(), d.end()); // Sort drivers by coordinate
  
  long idx(0); // Pointer for current driver in the sorted list
  for (long p = 0; p < n; p++) { // For each rider
    if (r[p] < d[0]) {
      ++cnt[0]; // Rider is closer to first driver
    } else if (r[p] > d.back()) {
      ++cnt.back(); // Rider is closer to last driver
    } else {
      // Find the closest driver using two pointer approach
      while (idx + 1 < d.size() && r[p] > d[idx]) {
        ++idx;
      }
      // Compare distances to previous and current driver
      if (r[p] - d[idx - 1] <= d[idx] - r[p]) {
        ++cnt[idx - 1]; // Previous driver is closer or equal
      } else {
        ++cnt[idx]; // Current driver is closer
      }
    }
  }
  
  for (long p = 0; p < m; p++) {
    printf("%ld ", cnt[p]); // Output result for each driver
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/codeForces/