// Problem: CF 527 D - Clique Problem
// https://codeforces.com/contest/527/problem/D

/*
D. Clique Problem
Algorithms/Techniques: Interval scheduling / Greedy algorithm on sorted intervals
Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing intervals

The problem reduces to finding a maximum set of non-overlapping intervals,
where each point forms an interval [x_i - w_i, x_i + w_i]. 
We sort intervals by their right endpoint and use a greedy approach:
for each interval, if its left endpoint is not less than the rightmost
endpoint of previous selected interval, we select it.

The algorithm works because:
1. Sorting by right endpoint ensures that if we can include an interval,
   we want to leave as much room as possible for later intervals.
2. Greedy selection maximizes the number of non-overlapping intervals.

This is equivalent to the "Activity Selection Problem" or "Interval Scheduling"
with the difference that we're selecting maximum non-overlapping intervals
instead of maximum overlapping ones.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

bool rightSort(std::pair<long, long> a, std::pair<long, long> b) {
  if (a.second < b.second) {     // Sort by right endpoint ascending
    return true;
  } else if (a.second == b.second) {
    return a.first < b.first;    // If same right endpoint, sort by left endpoint ascending
  } else {
    return false;
  }
}
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<std::pair<long, long>> a(n);
  for (long p = 0; p < n; p++) {
    long x, w;
    scanf("%ld %ld", &x, &w);
    a[p] = std::make_pair(x - w, x + w);  // Convert point to interval [left, right]
  }
  sort(a.begin(), a.end(), rightSort);     // Sort intervals by right endpoint
  long last(-2e9);                         // Initialize last selected interval's right endpoint
  long count(0);
  for (long p = 0; p < n; p++) {
    if (a[p].first < last) {               // If current interval overlaps with last selected
      continue;
    }
    ++count;                               // Select the interval
    last = a[p].second;                    // Update last selected interval's right endpoint
  }
  printf("%ld\n", count);
  return 0;
}


// https://github.com/VaHiX/codeForces/