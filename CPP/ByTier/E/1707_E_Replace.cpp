// Problem: CF 1707 E - Replace
// https://codeforces.com/contest/1707/problem/E

/*
 * Problem: E. Replace
 * 
 * Purpose: Given an array of integers and a set of queries, determine the minimum number of times
 *          to apply a "replace" function to transform a given range into [1, n], or return -1 if impossible.
 *          The "replace" function returns min and max values in the range.
 *          
 * Algorithm: 
 *   - Use a 2D sparse table to precompute range min/max queries in O(1) time.
 *   - Use binary lifting technique to find the minimum steps needed to reach [1, n] from a query range.
 *   - For each query, try to reduce the range using binary lifting by checking if it's feasible to go from current range to [1, n].
 *   
 * Time Complexity: O(n * log n + q * log^2 n)
 * Space Complexity: O(n * log n)
 */

#include <stdio.h>
#include <algorithm>
#include <utility>

#define x first
#define y second
using namespace std;
const int N = 1e5 + 7;
typedef pair<int, int> pa;
pa f[35][17][N], p;
int n, m, i, j, k, Log[N];

// Overload the + operator for pair to compute min/max of two pairs
pa operator+(pa a, pa b) { return pa(min(a.x, b.x), max(a.y, b.y)); }

// Function to compute range min/max using sparse table
pa F(pa x, int i) {
  int t = Log[x.y - x.x + 1];  // Find the highest power of 2 that fits the range
  return f[i][t][x.x] + f[i][t][x.y - (1 << t) + 1];  // Combine two segments
}

int main() {
  // Precompute Log[i] = floor(log2(i))
  for (Log[0] = -1, i = 1; i < N; ++i)
    Log[i] = Log[i >> 1] + 1;
  
  // Read input array and fill sparse table for level 0 (base case)
  for (scanf("%d%d", &n, &m), i = 1; i <= n; ++i)
    scanf("%d", &j), f[0][0][i] = pa(j, j);
  
  // Build sparse table for range min/max queries
  for (j = 1; j < 17; ++j)
    for (i = 1; i + (1 << j) - 1 <= n; ++i)
      f[0][j][i] = f[0][j - 1][i] + f[0][j - 1][i + (1 << j - 1)];
  
  // Extend to higher levels for binary lifting
  for (k = 1; k < 35; ++k)
    for (j = 0; j < 17; ++j)
      for (i = 1; i + (1 << j) - 1 <= n; ++i)
        f[k][j][i] = F(f[k - 1][j][i], k - 1);
  
  // Process queries
  while (m--) {
    scanf("%d%d", &p.x, &p.y);
    
    // Special case: if already at [1, n]
    if (p == pa(1, n)) {
      puts("0");
      continue;
    }
    
    // Try to reach [1, n] using binary lifting
    for (j = 0, i = 34; i >= 0; --i) {
      auto ret = F(p, i);  // Compute range min/max for current lifted step
      // If we cannot make progress toward [1, n], move to next step
      if (ret.x > 1 || ret.y < n)
        p = ret, j |= 1 << i;  // Update current range and accumulative steps
    }
    
    // Final step to check whether we're at [1, n]
    p = F(p, 0);
    j++;
    
    // Output result
    printf("%d\n", p == pa(1, n) ? j : -1);
  }
}


// https://github.com/VaHiX/CodeForces/