// Problem: CF 2050 F - Maximum modulo equality
// https://codeforces.com/contest/2050/problem/F

/*
F. Maximum modulo equality
Algorithm: Sparse Table + GCD + Difference Array
Time Complexity: O(n * log n + q * log n) per test case
Space Complexity: O(n * log n)

This code solves the problem of finding the maximum possible m such that all elements 
in a given range [l, r] are equal modulo m. It uses:
1. Difference array to compute adjacent differences.
2. Sparse Table (ST) for efficient range GCD queries.
3. For each query, we find the GCD of differences in the range,
   which gives us the maximum valid modulo value.
*/

#include <stdlib.h>
#include <algorithm>
#include <iostream>

using namespace std;
int T, n, q, a[200200], b[200200], st[20][200200];

// Build Sparse Table for GCD queries
void f() {
  for (int i = 1, k = 1; i <= 20 && k <= n; i++, k <<= 1) { // Iterate through powers of 2
    for (int j = 1; j + k <= n; j++) { // For each interval of size k
      st[i][j] = __gcd(st[i - 1][j], st[i - 1][j + k]); // Build ST using previous level
    }
  }
}

// Query GCD in range [l, r] using Sparse Table
int g(int l, int r) {
  int d = __lg(r - l + 1), k = 1 << d; // Find largest power of 2 <= (r - l + 1)
  return __gcd(st[d][l], st[d][r - k + 1]); // Use two overlapping segments
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  while (T--) {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      b[i] = abs(a[i] - a[i - 1]); // Compute differences between adjacent elements
      st[0][i] = b[i]; // Initialize ST with differences
    }
    f(); // Build Sparse Table
    while (q--) {
      int l, r;
      cin >> l >> r;
      if (l == r) { // If query range is single element
        cout << "0 ";
        continue;
      }
      l++; // Adjust for 1-based indexing
      int gg = g(l, r); // Get GCD of differences in range
      cout << gg << " ";
    }
    cout << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/