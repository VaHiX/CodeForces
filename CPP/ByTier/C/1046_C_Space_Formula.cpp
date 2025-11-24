// Problem: CF 1046 C - Space Formula
// https://codeforces.com/contest/1046/problem/C

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n, d;
  scanf("%ld %ld", &n, &d);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  std::vector<long> b(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &b[p]);
  }
  sort(b.rbegin(), b.rend()); // Sort point awards in descending order
  long score = a[d - 1] + b[0]; // Maximum possible score for the astronaut at position D
  long idx(0), ans(d); // idx tracks current index in b, ans stores best rank found
  for (long p = d - 2; p >= 0; p--) { // Iterate from position D-2 down to 0
    ++idx;
    while (idx < n && a[p] + b[idx] > score) { // Find next valid b[idx] such that a[p]+b[idx] <= score
      ++idx;
    }
    if (idx >= n || a[p] + b[idx] > score) {
      break; // No valid b[idx] found, stop searching
    }
    ans = p + 1; // Update answer to current position
  }
  printf("%ld\n", ans);
  return 0;
}

// https://github.com/VaHiX/codeForces/