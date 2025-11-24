// Problem: CF 1779 F - Xorcerer's Stones
// https://codeforces.com/contest/1779/problem/F

// Purpose: This code solves the problem of removing all stones from a rooted tree by performing spells.
//          Each spell selects a node and sets all values in its subtree to the XOR of the original values in that subtree.
//          The approach uses dynamic programming to track possible XOR results and determine valid operations.
//
// Algorithms/Techniques: Dynamic Programming on Trees, XOR properties, Bit manipulation
// Time Complexity: O(32 * n) where n is the number of nodes
// Space Complexity: O(n * 32) for storing the DP and lookup tables

#include <cstdio>
#include <cstring>
unsigned dp[200001];
int a[200001], c[200001], f[200001], l[200001][32], v[200001];
int main() {
  int n, i, x, y, p = 0;
  unsigned t;
  scanf("%d", &n);
  memset(l, -1, sizeof(l)); // Initialize lookup table to -1
  for (i = 1; i <= n; i++)
    scanf("%d", a + i), dp[i] = 1 << a[i], c[i] = 1; // Initialize dp with bit representation of a[i]
  for (i = 2; i <= n; i++)
    scanf("%d", f + i); // Read parent of each node
  for (i = n; i; i--) {
    c[f[i]] += c[i]; // Count total nodes in subtree
    if (~c[i] & 1)   // If subtree size is even
      dp[i] |= 1;    // Set least significant bit to indicate even subtree
    t = 0;
    for (x = 0; x < 32; x++) // For each bit position
      if (dp[f[i]] & (1 << x)) // If this bit is set in parent's dp
        for (y = 0; y < 32; y++) // For each bit position in current subtree
          if (dp[i] & (1 << y)) { // If this bit is set in current subtree
            t |= 1 << (x ^ y);   // Combine using XOR
            l[i][x ^ y] = x;     // Store which bit from parent led to this result
          }
    dp[f[i]] = t; // Update parent's dp value
  }
  if (!(dp[1] & 1)) // If root cannot produce 0, impossible to solve
    return puts("-1"), 0;
  dp[1] = 1, v[p++] = 1; // Start with root operation
  for (i = 2; i <= n; i++) {
    x = __builtin_ctz(dp[f[i]]), t = 0; // Find least significant set bit of parent's dp
    if (x < 32 && ~l[i][x]) {          // If valid bit and mapping exists
      dp[f[i]] = 1 << l[i][x];         // Set parent's dp
      t = 1 << (x ^ l[i][x]);          // Calculate new xor value
    }
    if (t == 1 && (~c[i] & 1))         // If operation produces 0 and subtree is even
      t = 0, v[p++] = i;               // Mark operation on this node
    dp[i] = t;                         // Store result for next iteration
  }
  printf("%d\n", p * 2); // Output number of operations (double it as per requirement)
  while (p--)
    printf("%d %d%c", v[p], v[p], " \n"[!p]); // Print operations
}


// https://github.com/VaHiX/CodeForces/