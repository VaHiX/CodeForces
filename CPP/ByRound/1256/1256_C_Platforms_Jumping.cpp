// Problem: CF 1256 C - Platforms Jumping
// https://codeforces.com/contest/1256/problem/C

/*
C. Platforms Jumping
Algorithm: Greedy placement of platforms to ensure jumpability
Time Complexity: O(n)
Space Complexity: O(n)

The problem involves placing m platforms of given lengths on a river of width n,
to allow jumping from 0 to n+1 with maximum jump distance d.
We first check if it's possible to place all platforms such that we can reach the end,
and then construct an arrangement of platforms that satisfies the conditions.
*/
#include <cstdio>
#include <vector>
int main() {
  long n, m, d;
  scanf("%ld %ld %ld", &n, &m, &d);
  std::vector<long> c(m + 1); // Store platform lengths (1-indexed)
  for (long p = 1; p <= m; p++) {
    scanf("%ld", &c[p]); // Read each platform length
    n -= c[p]; // Reduce available space by current platform length
  }
  long r(d - 1), s(m + 1); // r = max gap between platforms, s = total number of gaps (m+1)
  if (n > s * r) { // If remaining space is too large to fill with gaps, impossible
    puts("NO");
  } else {
    puts("YES");
    long q, k;
    for (long p = 0; p <= m; p++) { // Loop through platforms (including virtual platform 0)
      for (q = 0; q < c[p]; q++) { // Print each cell of current platform
        printf("%ld ", p);
      }
      for (k = (n < r) ? n : r, n -= k, q = 0; q < k; q++) { // Place gaps (0s) between platforms
        printf("0 ");
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/