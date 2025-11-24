// Problem: CF 2117 D - Retaliation
// https://codeforces.com/contest/2117/problem/D

/*
D. Retaliation
Purpose: Determine if an array can be reduced to all zeros using two types of operations:
         1. Decrease each element a[i] by i (1-indexed).
         2. Decrease each element a[i] by (n - i + 1).

Algorithm:
- For each test case, we try to find if there exists a valid sequence of operations.
- The key idea is to derive the coefficients x and y such that:
    a[i] = x * i + y * (n - i + 1) for all elements.
    This leads to solving equations based on first two elements.

Time Complexity: O(n) per test case, since we scan the array once after computing initial values.
Space Complexity: O(1), constant extra space used.

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long a, b;
    scanf("%ld %ld", &a, &b);
    // Compute coefficients x and y from first two elements
    long y = (2 * a - b) / (n + 1);
    long x = y + (b - a);
    bool possible(true);
    // Validate derived x and y against the first two elements
    if ((x < 0) || (y < 0) || (x + n * y != a) || (2 * x + (n - 1) * y != b)) {
      possible = false;
    }
    for (long p = 2; p < n; p++) {
      long u;
      scanf("%ld", &u);
      // Check if remaining elements follow the derived pattern
      if (u != (p + 1) * x + (n - p) * y) {
        possible = false;
      }
    }
    puts(possible ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/