// Problem: CF 1769 B1 - Копирование файлов I
// https://codeforces.com/contest/1769/problem/B1

#include <cstdio>
#include <vector>
// Task: Find all percentages (0-100) where both progress bars show the same value at some point during file copy.
// Algorithm: For each file, iterate through all bytes copied so far and check for matching percentage values.
// Time Complexity: O(n * max_a), where max_a is maximum file size (up to 1000)
// Space Complexity: O(101) = O(1) - fixed size boolean vector
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  long sa(0);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
    sa += a[p];  // Total size of all files
  }
  std::vector<bool> v(101, 0);  // Track which percentages we've seen
  long tsf(0);  // Total size copied so far
  for (long p = 0; p < n; p++) {
    for (long x = 0; x <= a[p]; x++) {
      long fp = 100 * x / a[p];  // Current file progress percentage
      long tp = 100 * (tsf + x) / sa;  // Total progress percentage
      if (fp == tp) {
        v[fp] = 1;  // Mark this percentage as seen
      }
    }
    tsf += a[p];  // Update total size copied
  }
  for (long p = 0; p < v.size(); p++) {
    if (v[p]) {
      printf("%ld\n", p);
    }
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/