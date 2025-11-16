// Problem: CF 2001 E2 - Deterministic Heap (Hard Version)
// https://codeforces.com/contest/2001/problem/E2

/*
E2. Deterministic Heap (Hard Version)
Time Complexity: O(n * m^3), where n is the height of the tree and m is the number of operations.
Space Complexity: O(n * m^2), due to the 3D array for storing intermediate states.

Algorithms/Techniques:
- Dynamic Programming with memoization
- Fast modular arithmetic
- Bitmasking techniques for binary tree traversal and heap properties
- Prefix sums for optimization in calculations

This problem involves counting the number of deterministic max-heaps formed by applying `add` operations on a perfect binary tree.
Each operation increments values along a path from root to a chosen node, and we count how many of these configurations result in deterministic pop sequences.
The solution uses a recursive DP approach to compute contributions from each layer of the tree, building up intermediate values and combining them.
*/
#include <string.h>
#include <iostream>

using namespace std;
int n, m, P;
int a[104][504], b[104][504], c[104][504][504], s[504][504];

// Adds y to x modulo P
void add(int &x, int y) {
  x += y;
  if (x >= P)
    x -= P;
}

// Main function that solves for one test case
void sol() {
  cin >> n >> m >> P;
  // Initialize base cases: a[1][i] = b[1][i] = 1 for all i <= m
  for (int i = 0; i <= m; i++)
    a[1][i] = b[1][i] = 1;
  
  // Loop through all levels from 2 to n
  for (int i = 2; i <= n; i++) {
    // Clear memory for current level variables
    memset(a[i], 0, sizeof(a[i]));
    memset(b[i], 0, sizeof(b[i]));
    memset(c[i], 0, sizeof(c[i]));
    memset(s, 0, sizeof(s));

    // Compute transitions based on earlier levels
    for (int j = 0; j + j <= m; j++)
      for (int k = j; j + k <= m; k++) {
        // Add transition from a[i-1] to a[i]
        add(a[i][j + k], (j ^ k ? 2ll : 1ll) * a[i - 1][j] * a[i - 1][k] % P);
        
        // Update b[i] and s arrays if j < k
        if (j < k)
          add(b[i][j + k], 2ll * a[i - 1][j] * b[i - 1][k] % P),
              add(s[j + k][k], 2ll * a[i - 2][j] * b[i - 2][k] % P);
      }

    // Update prefix sum in s
    for (int j = 2; j <= m; j++)
      for (int k = 1; k < j; k++)
        add(s[j][k], s[j - 1][k]);

    // Compute c[i][j][k] using prefix sums and previous values
    for (int j = 1; j <= m; j++) {
      int sm = 0;
      // First inner loop computes cumulative sum using c[i-1]
      for (int k = j - 1; ~k; k--) {
        add(sm, c[i - 1][j][k + 1]);
        if (j + k <= m)
          add(c[i][j + k][j], 2ll * a[i - 1][k] * sm % P);
      }
      
      sm = 0;
      // Update c using s for b terms when i > 2
      if (i > 2)
        for (int k = 1; k < j && j + k <= m; k++)
          add(sm, s[j][k - 1]), add(c[i][j + k][j], 2ll * b[i - 1][k] * sm % P);
      else
        for (int k = 0; k < j && j + k <= m; k++)
          add(c[i][j + k][j], b[i - 1][k]), add(c[i][j + k][j], b[i - 1][k]);
    }
    
    // Compute prefix sums for a, b and c
    for (int j = 1; j <= m; j++) {
      add(a[i][j], a[i][j - 1]);     // Prefix sum a
      add(b[i][j], b[i][j - 1]);     // Prefix sum b
      for (int k = 0; k < j; k++)
        add(c[i][j][k], c[i][j - 1][k]); // Prefix sum c
    }
  }

  long long ans = 0;
  // Sum up final values stored in c[n][m][i]
  for (int i = 0; i <= m; i++)
    ans += c[n][m][i];
  
  cout << ans % P << '\n';
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int tc;
  cin >> tc;
  while (tc--)
    sol();
}


// https://github.com/VaHiX/codeForces/