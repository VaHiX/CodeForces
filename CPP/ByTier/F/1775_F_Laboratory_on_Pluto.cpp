// Problem: CF 1775 F - Laboratory on Pluto
// https://codeforces.com/contest/1775/problem/F

/*
 * Problem: F. Laboratory on Pluto
 * 
 * Purpose: This program solves two related problems for building a laboratory on Pluto:
 * 1. For u=1, it finds one optimal layout of n blocks that minimizes the outside wall count.
 * 2. For u=2, it computes the number of ways to build an optimal lab (minimum perimeter) modulo a prime m.
 * 
 * Algorithms/Techniques:
 * - For u=1: Greedy approach - place blocks in a rectangle as close to square as possible, then remove some from top-left.
 * - For u=2: Dynamic programming on partitioning problem, using generating function approach.
 * 
 * Time Complexity: 
 *   - u=1: O(n) per test case (sqrt(n) for finding dimensions, and printing rows)
 *   - u=2: O(4 * 650 * 650) for preprocessing dp array, then O(sqrt(n)) for each query
 * Space Complexity: O(650) for dp array and O(1) for other variables
 */

#include <stdio.h>
#include <cmath>

using namespace std;
typedef long long ll;

// Modulo for u=2 case
int mod = 1e9 + 7;

// dp[i] stores number of ways to partition i blocks (used in u=2 case)
ll dp[655] = {1};

int main() {
  int t, _;
  scanf("%d%d", &t, &_);
  
  // If u == 1, we are asked to return a valid layout
  if (_ == 1) {
    while (t--) {
      int n;
      scanf("%d", &n);
      
      // Find dimensions of rectangle that fits n blocks, closest to square
      int l = sqrt(n), r = l;
      while (l * r < n) {
        l++;
        if (l * r < n)
          r++;
      }
      
      // Amount of space to leave blank (top-left corner)
      int m = l * r - n;
      printf("%d %d\n", r, l);
      
      // Print first row (with m blanks at the top-left)
      for (int i = 1; i <= l; i++)
        if (i <= m)
          printf(".");
        else
          printf("#");
      puts("");
      
      // Print remaining rows (all filled)
      for (int i = 2; i <= r; i++, puts(""))
        for (int j = 1; j <= l; j++)
          printf("#");
    }
    return 0;
  }
  
  // If u == 2, compute number of layouts (modulo prime)
  scanf("%d", &mod);
  
  // Precompute partitions using dynamic programming (subset sum DP technique)
  for (int i = 1; i <= 4; i++)
    for (int j = 1; j <= 650; j++)
      for (int k = j; k <= 650; k++)
        dp[k] = (dp[k] + dp[k - j]) % mod;
  
  // Process each test case
  while (t--) {
    int n;
    scanf("%d", &n);
    
    // Find optimal rectangle dimensions
    int l = sqrt(n), r = l;
    while (l * r < n) {
      l++;
      if (l * r < n)
        r++;
    }
    
    ll ans = 0;
    
    // Enumerate over valid rectangle dimensions that could be optimal
    while (l * r >= n) {
      // Count number of missing blocks
      int diff = l * r - n;
      
      // Add to answer depending on symmetry (equal sides vs. different sides)
      if (l == r)
        ans += dp[diff];
      else
        ans += 2 * dp[diff];
      
      l++, r--;
    }
    
    // Output perimeter and number of arrangements
    printf("%d %lld\n", 2 * (l + r), ans % mod);
  }
}


// https://github.com/VaHiX/CodeForces/