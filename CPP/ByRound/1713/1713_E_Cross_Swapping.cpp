// Problem: CF 1713 E - Cross Swapping
// https://codeforces.com/contest/1713/problem/E

/*
 * Problem: E. Cross Swapping
 * Algorithm: Union-Find with path compression and edge weighting to determine connected components,
 *            then process each component to find minimum lexicographical configuration.
 * Time Complexity: O(n^2 * α(n)) where α is the inverse Ackermann function, effectively constant for practical purposes.
 * Space Complexity: O(n^2) for storing matrix and Union-Find structures.
 */

#include <stdio.h>

const int N = 1000;
inline char nc() {
  static char buf[99999], *l, *r;
  return l == r && (r = (l = buf) + fread(buf, 1, 99999, stdin), l == r) ? EOF
                                                                         : *l++;
}
inline void read(int &x) {
  char c = nc();
  for (; c < '0' || '9' < c; c = nc())
    ;
  for (x = 0; '0' <= c && c <= '9';
       x = (x << 3) + (x << 1) + (c ^ 48), c = nc())
    ;
}
int t, n, a[N][N], f[N], ff[N];
inline int find(const int &x) {
  if (x == f[x])
    return x;
  int tmp = find(f[x]);        // Find root with path compression
  ff[x] ^= ff[f[x]];           // Propagate parity (0 or 1)
  return f[x] = tmp;           // Update parent to root
}
int main() {
  for (read(t); t--;) {
    read(n);
    for (int i = 0; i < n; f[i] = i, ff[i++] = 0)     // Initialize Union-Find structure
      for (int j = 0; j < n; read(a[i][j++]))        // Read matrix values
        ;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        if (i ^ j)                                    // Skip diagonal elements
          if (find(i) ^ find(j)) {                    // If not in same component
            if (a[i][j] < a[j][i]) {                  // Swap according to smaller value
              ff[f[i]] = ff[i] ^ ff[j];
              f[f[i]] = f[j];
            }
            if (a[i][j] > a[j][i]) {                  // Another case for swapping
              ff[f[i]] = ff[i] ^ ff[j] ^ 1;
              f[f[i]] = f[j];
            }
          }
    for (int i = 0; i < n; ++i)
      if (find(i), ff[i])                           // If root has odd parity, swap rows/columns
        for (int j = 0; j < n; ++j)
          if (i ^ j)
            a[i][j] ^= a[j][i] ^= a[i][j] ^= a[j][i]; // Swap elements
    for (int i = 0; i < n; putchar('\n'), ++i)
      for (int j = 0; j < n; printf("%d ", a[i][j++]))
        ;
  }
}


// https://github.com/VaHiX/codeForces/