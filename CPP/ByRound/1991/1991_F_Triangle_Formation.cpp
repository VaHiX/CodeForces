// Problem: CF 1991 F - Triangle Formation
// https://codeforces.com/contest/1991/problem/F

/*
Purpose: This program determines whether it's possible to choose 6 distinct sticks from a given range [l, r] 
         to form 2 non-degenerate triangles. A non-degenerate triangle satisfies the triangle inequality:
         the sum of any two sides must be greater than the third side.

Algorithms/Techniques:
- Sorting: Sorts the subarray to efficiently test combinations.
- Brute-force checking for triangle combinations: Tries different groupings of sticks to form 2 triangles.
- Optimization for large ranges: For ranges larger than 48 elements, it's always possible to form 2 triangles (output "YES").

Time Complexity: O(n * log(n) + q * n) where n is the number of sticks and q is number of queries.
Space Complexity: O(n) for the array of sticks and auxiliary array for sorting.

Note: The brute-force approach is optimized by limiting the number of combinations checked and using the fact
      that for large enough ranges (more than 48 elements), it's always possible to form 2 triangles.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
int a[100005], c[50], tot;
inline bool check(int a, int b, int c) { return a + b > c; }
inline bool check(int a, int b, int c, int d, int e, int f) {
  return check(a, b, c) && check(d, e, f) || check(a, c, d) && check(b, e, f) ||
         check(a, d, e) && check(b, c, f) || check(a, d, f) && check(b, c, e) ||
         check(a, e, f) && check(b, c, d);
}
int main() {
  int n, q;
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  while (q--) {
    int l, r;
    scanf("%d%d", &l, &r);
    if (r - l + 1 < 48) {
      tot = 0;
      for (int i = l; i <= r; i++) {
        c[++tot] = a[i];
      }
      sort(c + 1, c + tot + 1);
      bool ok = false;
      for (int i = 1; i + 5 <= tot; i++) {
        ok |= check(c[i], c[i + 1], c[i + 2], c[i + 3], c[i + 4], c[i + 5]);
      }
      int l = -1, r;
      for (int i = 1; i + 2 <= tot; i++) {
        if (check(c[i], c[i + 1], c[i + 2])) {
          l = i;
          break;
        }
      }
      for (int i = tot - 2; i >= 1; i--) {
        if (check(c[i], c[i + 1], c[i + 2])) {
          r = i;
          break;
        }
      }
      ok |= (l != -1 && l + 2 < r);
      printf("%s\n", (ok ? "YES" : "NO"));
    } else {
      printf("YES\n");
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/