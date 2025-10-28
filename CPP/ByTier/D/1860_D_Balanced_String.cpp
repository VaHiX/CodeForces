// Problem: CF 1860 D - Balanced String
// https://codeforces.com/contest/1860/problem/D

/*
 * Code Purpose: 
 * This code finds the minimum number of swaps required to make a binary string balanced.
 * A balanced string has an equal number of subsequences 01 and 10.
 * 
 * Algorithm:
 * 1. Count initial 01 and 10 subsequences.
 * 2. If already balanced, return 0.
 * 3. If not, make the 01 count fewer than 10, by flipping the entire string if needed.
 * 4. Separate indices of 0s and 1s.
 * 5. Use dynamic programming with bitsets to calculate possible sums of distances
 *    from swapping 0s and 1s.
 * 6. Find minimum k such that we can adjust the difference by swapping k pairs of indices.
 * 
 * Time Complexity: O(n^2) where n is length of string, due to nested loops in bitset DP.
 * Space Complexity: O(n^2) for the bitset arrays f[2][maxn].
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <bitset>
#include <utility>
#include <vector>

using namespace std;
const int maxn = 105;
const int maxv = 7005;
char str[maxn];
int a[maxn], c[maxn];
bitset<maxv> f[2][maxn];
int main() {
  scanf("%s", str);
  int n = strlen(str);
  for (int i = 0; i < n; ++i)
    a[i] = str[i] - '0';
  for (int i = 0; i < n; ++i)
    c[i + 1] = c[i] + (a[i] == 0); // Prefix sum of 0s
  int cx[2] = {0, 0}; // cx[0] = count of 01, cx[1] = count of 10
  for (int i = 0; i < n; ++i) {
    if (a[i] == 0)
      continue;
    cx[0] += c[i]; // Count of 01: number of 0s before current 1
    cx[1] += c[n] - c[i]; // Count of 10: number of 0s after current 1
  }
  if (cx[0] == cx[1]) { // Already balanced
    puts("0");
    return 0;
  }
  if (cx[1] < cx[0]) { // Ensure cx[0] is smaller for simplicity
    for (int i = 0; i < n; ++i)
      a[i] ^= 1; // Flip all bits
    swap(cx[0], cx[1]); // Swap counts
  }
  vector<int> S[2]; // Stores indices of 0s and 1s
  for (int i = 0; i < n; ++i)
    S[a[i]].push_back(i);
  int m[2];
  m[0] = S[0].size(); // Size of 0s
  m[1] = S[1].size(); // Size of 1s
  // Initialize bitsets for DP
  for (int t = 0; t < 2; ++t) {
    f[t][0].set(0); // Base case: no elements selected, sum = 0
    for (int i = 0; i < m[t]; ++i) {
      for (int j = i; j >= 0; --j)
        f[t][j + 1] |= (f[t][j] << S[t][i]); // DP transition: update bitset
    }
  }
  int d = (cx[1] - cx[0]) / 2; // Half the difference to balance
  const int V = 7000;
  for (int k = 0; k <= n; ++k) { // Try k swaps
    for (int v = 0; v <= V; ++v) {
      int p = v + d;
      if (p < 0 || p > V)
        continue;
      if (f[0][k][p] && f[1][k][v]) { // Check if k swaps can balance
        printf("%d\n", k);
        return 0;
      }
    }
  }
  abort(); // Should not reach here due to constraint that string is convertible
  return 0;
}


// https://github.com/VaHiX/CodeForces/