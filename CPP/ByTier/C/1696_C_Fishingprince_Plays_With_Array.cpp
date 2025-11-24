// Problem: CF 1696 C - Fishingprince Plays With Array
// https://codeforces.com/contest/1696/problem/C

/*
Algorithm/Techniques:
- Normalize arrays by decomposing elements into base and power of m.
- For each element, repeatedly divide by m until it's no longer divisible,
  storing the number of divisions (power) and the remaining value (base).
- After normalization, merge adjacent same elements into one with updated power.
- Two arrays are equivalent if their normalized representations are identical.

Time Complexity: O(n + k) where n and k are the sizes of input arrays.
Space Complexity: O(n + k) for storing the normalized arrays.
*/

#include <stdio.h>

// Structure to store base value and power of m
struct st {
  int x;       // base value after dividing by m repeatedly
  long long d; // power of m (number of divisions)
} a[50003], b[50003];

int f, t, n, m, j, k, i;
int g(st c[], int n) {
  // Process each element in the array
  for (i = 0; i < n; ++i) {
    // Read the value
    for (scanf("%d", &c[i].x), c[i].d = 1; c[i].x % m == 0;
         c[i].x /= m, c[i].d *= m)
      ;
    // Merge adjacent elements with same base value
    if (i && c[i].x == c[i - 1].x)
      c[i - 1].d += c[i].d, --i, --n;
  }
  return n;
}
int main() {
  // Read number of test cases
  for (scanf("%d", &t); t; printf("%s\n", f ? "Yes" : "No"), --t) {
    // Read array a
    scanf("%d%d", &n, &m);
    n = g(a, n);
    // Read array b
    scanf("%d", &k);
    k = g(b, k);
    // Compare normalized arrays
    for (f = n == k, i = 0; i < n && f; ++i)
      f = a[i].x == b[i].x && a[i].d == b[i].d;
  }
}

// https://github.com/VaHiX/CodeForces/