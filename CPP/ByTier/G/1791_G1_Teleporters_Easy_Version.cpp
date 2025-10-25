// Problem: CF 1791 G1 - Teleporters (Easy Version)
// https://codeforces.com/contest/1791/problem/G1

/*
G1. Teleporters (Easy Version)
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for the vector storage

Algorithm:
- For each teleporter at point i, the cost to reach it and use it is:
  - Move from 0 to i: i steps, each costing 1 coin → i coins
  - Use teleporter at i: a[i] coins
  - Total cost = i + 1 + a[i]
- We sort these total costs and greedily select the cheapest ones until coins run out.

Techniques:
- Greedy algorithm with sorting
- Prefix sum concept implicitly used in cost calculation
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, b;
    scanf("%ld %ld", &n, &b);
    std::vector<long> v(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
      v[p] += p + 1;  // Add cost to reach teleporter at position p+1 and use it
    }
    sort(v.begin(), v.end());  // Sort by total cost to apply greedy selection
    long cnt(0);
    for (long p = 0; p < n; p++) {
      if (v[p] <= b) {
        b -= v[p];  // Use teleporter and subtract its cost
        ++cnt;
      } else {
        break;  // Cannot afford next teleporter, so stop
      }
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/