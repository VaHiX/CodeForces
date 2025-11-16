// Problem: CF 853 A - Planning
// https://codeforces.com/contest/853/problem/A

/*
Algorithm: Greedy with Priority Set (Multiset)
Approach:
- We use a greedy strategy to assign departure times to flights.
- At each step, we maintain a set of flights sorted by their cost (c[i]) in descending order.
- For each minute t from 1 to n+k:
  - Add the cost of current delay to total.
  - If we haven't processed all flights yet (p < n):
    - Insert the flight (cost, index) into the set.
    - Increase rate by the flight's cost.
  - If we have passed the initial delay period (p >= k):
    - Take the flight with highest cost (last element in set).
    - Assign it a departure time of t.
    - Remove from set and decrease rate.
Time Complexity: O(n log n) due to set operations.
Space Complexity: O(n) for storing data structures.
*/

#include <stdint.h>
#include <cstdio>
#include <set>
#include <vector>
#include <utility>

int main() {
  int64_t n, k;
  scanf("%lld %lld", &n, &k);
  std::vector<int64_t> c(n);
  for (int64_t p = 0; p < n; p++) {
    scanf("%lld", &c[p]);
  }
  std::set<std::pair<int64_t, int64_t>> s;  // Multiset storing (cost, index)
  std::vector<int64_t> d(n, 0);             // Departure times for each flight
  int64_t rate(0);                          // Running total of costs in the set
  int64_t total(0);                         // Total cost of delay
  for (int64_t p = 0; p < n + k; p++) {
    total += rate;  // Accumulate delay cost
    if (p < n) {
      s.insert(std::make_pair(c[p], p));  // Insert flight into multiset
      rate += c[p];                       // Update rate
    }
    if (p >= k) {
      std::pair<int64_t, int64_t> f = *(--(s.end()));  // Get flight with max cost
      rate -= f.first;                                  // Decrease rate
      d[f.second] = p;                                  // Assign departure time
      s.erase(--(s.end()));                             // Remove from multiset
    }
  }
  printf("%lld\n", total);
  for (int64_t p = 0; p < n; p++) {
    printf("%lld ", 1 + d[p]);  // Output departure times (1-indexed)
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/