// Problem: CF 702 C - Cellular Network
// https://codeforces.com/contest/702/problem/C

/*
Algorithm: Binary Search + Two Pointers
Time Complexity: O(n + m)
Space Complexity: O(1)

The problem is to assign each city to the nearest cellular tower such that the maximum radius r required is minimized.
We use a two-pointer approach to efficiently determine the minimal radius needed:
1. For each city, we find the closest tower using a pointer that moves forward.
2. We calculate the minimum distance from the current city to either the current or previous tower.
3. The maximum of these minimum distances across all cities is the answer.
*/

#include <cstdio>
#include <vector>
long abs(long x) { return (x > 0) ? x : (-x); }
long min(long x, long y) { return (x < y) ? x : y; }
long max(long x, long y) { return (x > y) ? x : y; }
int main() {
  long n, m;
  scanf("%ld %ld\n", &n, &m);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  std::vector<long> b(m);
  for (long p = 0; p < m; p++) {
    scanf("%ld", &b[p]);
  }
  long r(0);
  for (long p = 0, u = 0; p < n; p++) {
    // Move the tower pointer to the leftmost tower that is >= current city
    while (u < m - 1 && b[u] < a[p]) {
      ++u;
    }
    // Compute the minimum distance to either the current or the previous tower
    r = max(r, min(abs(b[u] - a[p]), abs(b[((u > 0) ? (u - 1) : u)] - a[p])));
  }
  printf("%ld\n", r);
  return 0;
}


// https://github.com/VaHiX/CodeForces/