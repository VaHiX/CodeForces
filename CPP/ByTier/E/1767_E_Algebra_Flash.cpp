// Problem: CF 1767 E - Algebra Flash
// https://codeforces.com/contest/1767/problem/E

/*
Code Purpose:
This solution solves the "Colored Platforms" problem using a bitmask dynamic programming approach combined with a greedy strategy.
The problem requires finding the minimum cost to activate platforms such that one can traverse from platform 1 to platform n using jumps of size 1 or 2, where all platforms in the path must be activated.

The key idea is to:
1. Identify which colors are required at the start and end.
2. For adjacent platforms, we track which colors can reach each other (i.e., if platform i and i+1 have different colors, then they create a connectivity constraint).
3. Use a recursive function with memoization to determine the maximum number of colors that can be avoided (i.e., not activated) by choosing optimal subsets of colors to activate.
4. Subtract the maximum number of colors not activated from the total cost to get the minimal cost.

Algorithms/Techniques:
- Bitmask Dynamic Programming
- Memoization (via f array)
- Greedy optimization via recursive approach

Time Complexity: O(3^m * m + n), where m is the number of colors and n is the number of platforms.
Space Complexity: O(2^m + m), for storing the memoization table and auxiliary arrays.
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
int n, m;
int c[300020];
int x[50];
int v[50];
long long e[50];
int f[1048577]; // Memoization table for bitmask DP

// Recursive function with memoization to compute the maximum number of colors that can be avoided
int F(long long s) {
  // If already computed, return memoized value
  if (s < 1 << 20 && f[s] != -1) {
    return f[s];
  }
  
  // Find the highest color index that is still active in the set
  int p = 63 - __builtin_clzll(s);
  
  // Recursively process without this color
  int r = F(s ^ (1LL << p));
  
  // If this color is not forced to be activated (v[p] == 0),
  // consider activating it and removing all its incompatible neighbors
  if (v[p] == 0) {
    r = max(r, F((s ^ (1LL << p)) & ~e[p]) + x[p]);
  }
  
  // Memoize the result
  if (s < 1 << 20) {
    f[s] = r;
  }
  return r;
}

int main() {
  scanf("%d%d", &n, &m);
  
  // Read platform colors (convert to 0-based indexing)
  for (int i = 1; i <= n; i++) {
    scanf("%d", &c[i]);
    c[i]--;
  }
  
  // Read activation costs
  int z = 0;
  for (int i = 0; i < m; i++) {
    scanf("%d", &x[i]);
    z += x[i]; // Total possible cost
  }
  
  // Mark the colors of start and end platforms as required
  v[c[1]] = 1;
  v[c[n]] = 1;
  
  // Build edge connections between colors of adjacent platforms
  for (int i = 1; i < n; i++) {
    if (c[i] == c[i + 1]) {
      // Same color, mark as required (forced)
      v[c[i]] = 1;
    } else {
      // Different colors, add constraint that they cannot both be inactive
      e[c[i]] |= 1LL << c[i + 1];
      e[c[i + 1]] |= 1LL << c[i];
    }
  }
  
  // Initialize memoization table
  memset(f, -1, sizeof f);
  f[0] = 0; // Base case: no colors selected, max avoided = 0
  
  // Output: Total cost minus maximum number of colors avoided
  printf("%d\n", z - F((1LL << m) - 1));
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/