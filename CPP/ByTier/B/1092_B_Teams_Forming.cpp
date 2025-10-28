// Problem: CF 1092 B - Teams Forming
// https://codeforces.com/contest/1092/problem/B

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  sort(a.begin(), a.end()); // Sort the skills to pair adjacent elements
  long s(0);
  for (long p = 0; p < n - 1; p += 2) {
    s += a[p + 1] - a[p]; // Difference in skill between pairs
  }
  printf("%ld\n", s);
  return 0;
}
/*
B. Teams Forming
Algorithm: Greedy approach after sorting
Time Complexity: O(n log n) due to sorting
Space Complexity: O(1) additional space (not counting input storage)
*/


// https://github.com/VaHiX/codeForces/