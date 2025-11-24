// Problem: CF 1864 A - Increasing and Decreasing
// https://codeforces.com/contest/1864/problem/A

/*
 * Problem: Construct an array with strictly increasing values and a strictly decreasing difference array.
 * 
 * Algorithm:
 * - Given x, y, n: start with a[0] = x and a[n-1] = y.
 * - Fill the array from right to left using the formula:
 *   a[i] = a[i+1] - (n - 1 - i)
 * - This ensures that differences between consecutive elements form a strictly decreasing sequence.
 * - Finally, verify if the constructed array satisfies the strictly increasing condition.
 * 
 * Time Complexity: O(n) per test case, as we iterate through the array twice.
 * Space Complexity: O(n) for storing the array a.
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y, n;
    scanf("%ld %ld %ld", &x, &y, &n);
    std::vector<long> a(n);
    a[0] = x;
    a[n - 1] = y;
    // Fill the array from right to left to ensure decreasing differences
    for (long p = n - 2; p > 0; p--) {
      a[p] = a[p + 1] - (n - 1 - p);
    }
    // Check if the sequence is valid (strictly increasing)
    if (a[1] < n - 1 + a[0]) {
      puts("-1");
      continue;
    } else {
      for (long p = 0; p < n; p++) {
        printf("%ld ", a[p]);
      }
      puts("");
    }
  }
}


// https://github.com/VaHiX/CodeForces/