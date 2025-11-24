// Problem: CF 1696 H - Maximum Product?
// https://codeforces.com/contest/1696/problem/H

/*
Algorithm: Dynamic Programming with inclusion-exclusion principle
Time Complexity: O(n^2 * m) where n is the number of elements and m is k
Space Complexity: O(n^2) for the DP tables

This code computes the sum of f(B) over all subsets B of A, where f(S) is the maximum product of k elements from S.
The approach uses dynamic programming to count contributions from each element being included or not in the optimal subset.
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <utility>

using namespace std;
const int N = 605, P = 1e9 + 7;
int n, m, pw[N], f[N][N][2], s[N][N][2], ans, g[N], h[N], H[N][N];
pair<int, int> a[N];
inline int md(int x) { return x >= P ? x - P : x; }
inline void Add(int &x, int y) {
  if ((x += y) >= P)
    x -= P;
}
int main() {
  scanf("%d%d", &n, &m);
  pw[0] = 1;
  for (int i = 1; i <= n; ++i)
    pw[i] = md(2 * pw[i - 1]); // Precompute powers of 2
  for (int i = 1, x; i <= n; ++i) {
    scanf("%d", &x);
    if (x > 0)
      a[i] = {x, 0}; // Positive numbers
    else
      a[i] = {-x, 1}; // Negative numbers (store absolute value for sorting)
  }
  sort(a + 1, a + n + 1);
  reverse(a + 1, a + n + 1); // Sort in descending order
  s[0][0][0] = 1; // Base case for DP
  for (int i = 1; i <= n; ++i) {
    int v = a[i].first, t = a[i].second; // v is absolute value, t indicates if number was negative
    f[i][1][t] = v, s[i][0][0] = 1; // Initialize f and s for 1 element
    for (int k = 2; k <= m; ++k) // Fill f table for more than 1 element
      for (int o = 0; o < 2; ++o)
        f[i][k][o] = 1ll * s[i - 1][k - 1][o ^ t] * v % P; // Compute products with previous elements
    for (int k = 1; k <= m; ++k) // Update s table
      for (int o = 0; o < 2; ++o)
        s[i][k][o] = md(s[i - 1][k][o] + f[i][k][o]);
    Add(ans, 1ll * f[i][m][0] * pw[n - i] % P); // Add positive cases
    Add(ans, P - f[i][m][1]); // Subtract negative cases
    if (m < 2)
      continue; // Skip further processing if m < 2
    for (int k = 0; k <= m - 2; ++k) { // Update g based on t (0 or 1)
      if (t)
        g[k] = s[i - 1][k][0];
      else
        g[k] = s[i - 1][k][m - k & 1];
    }
    for (int j = i + 1; j <= n; ++j) // Process other elements
      if (a[j].second != t) { // If current element has different sign than previous
        H[i][j] = 1ll * g[m - 2] * a[j].first % P; // Compute contribution of this pair
        for (int k = m - 3; ~k; --k) // Update g recursively
          Add(g[k + 1], 1ll * g[k] * a[j].first % P);
      }
    for (int j = 1; j <= m - 1; ++j) { // Update g from f again
      if (t)
        g[j] = f[i][j][1];
      else
        g[j] = f[i][j][m - 1 - j & 1];
    }
    for (int j = i + 1; j <= n; ++j) {
      h[j] = g[m - 1]; // Store g[m-1] which represents the case of selecting m-1 elements
      if (a[j].second != t) { // If different sign
        for (int k = m - 2; k > 0; --k) // Update g recursively
          Add(g[k + 1], 1ll * g[k] * a[j].first % P);
        continue;
      }
      int ct = 0;
      for (int k = j + 1; k <= n; ++k) // Count elements of same sign after j
        if (a[k].second == t)
          ++ct;
      for (int k = 1, l = n; k < j; ++k) // Double loop for pairing elements
        if (a[k].second != t) { // If opposite sign
          while (l > k &&
                 (a[l].second == t || // If l is same sign
                  1ll * a[l].first * a[k].first < 1ll * v * a[j].first || // Check inequality
                  l > j &&
                      1ll * a[l].first * a[k].first == 1ll * v * a[j].first)) {
            if (a[l].second != t)
              ++ct;
            --l;
          }
          if (k > l)
            --ct;
          if (k > i)
            Add(ans, 1ll * h[k] * pw[ct] % P * a[j].first % P); // Add contribution
          else
            Add(ans, 1ll * H[k][i] * pw[ct] % P * a[j].first % P);
        }
    }
  }
  if (m & 1) { // Handle special case when m is odd
    memset(g, 0, sizeof(g));
    g[0] = 1;
    for (int i = n; i; --i)
      if (a[i].second) // If negative, update g
        for (int j = n; ~j; --j)
          if (g[j]) {
            if (j < m)
              Add(g[j + 1], 1ll * g[j] * a[i].first % P);
            else
              Add(g[j + 1], g[j]);
          }
    for (int i = m + 1; i <= n; ++i)
      if (g[i])
        Add(ans, P - g[i]); // Subtract the result
    memset(g, 0, sizeof(g));
    g[0] = 1;
    for (int i = 1; i <= n; ++i) {
      if (a[i].second) { // Handle case with negative signs
        for (int j = n; ~j; --j)
          if (g[j]) {
            if (j < m - 1)
              Add(g[j + 1], 1ll * g[j] * a[i].first % P);
            else
              Add(g[j + 1], g[j]);
          }
      } else { // If is positive
        for (int j = m; j <= n; ++j)
          if (g[j])
            Add(ans, 1ll * g[j] * pw[n - i] % P * a[i].first % P); // Add contribution
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/