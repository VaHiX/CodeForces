// Problem: CF 1833 B - Restore the Weather
// https://codeforces.com/contest/1833/problem/B

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

/*
Algorithm: Greedy Matching with Sorting
Approach:
1. For each test case, we sort the forecast array 'a' by temperature value while keeping track of original indices.
2. We sort the actual temperatures 'b'.
3. We greedily assign the smallest available temperature in 'b' to the earliest (in sorted order) forecast day.
4. The result is reconstructed by placing each assigned value at the original index from 'a'.

Time Complexity: O(n log n) per test case due to sorting operations
Space Complexity: O(n) for storing arrays and temporary structures

Techniques:
- Sorting with pair to maintain index tracking
- Greedy assignment to minimize difference
*/

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<std::pair<long, long>> a(n); // Store (temperature, original_index)
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      a[p] = std::make_pair(x, p); // Store original index along with temperature
    }
    sort(a.begin(), a.end()); // Sort by temperature values
    std::vector<long> b(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &b[p]);
    }
    sort(b.begin(), b.end()); // Sort actual temperatures
    std::vector<long> c(n);
    for (long p = 0; p < n; p++) {
      c[a[p].second] = b[p]; // Assign sorted b[p] to correct original index
    }
    for (long p = 0; p < n; p++) {
      printf("%ld ", c[p]);
    }
    puts(""); // Print newline after each test case
  }
}

// https://github.com/VaHiX/CodeForces/