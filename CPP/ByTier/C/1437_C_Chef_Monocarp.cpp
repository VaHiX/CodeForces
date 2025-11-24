// Problem: CF 1437 C - Chef Monocarp
// https://codeforces.com/contest/1437/problem/C

/*
 * Problem: Chef Monocarp
 * Description:
 *   Chef has n dishes, each with an optimal cooking time t_i. 
 *   At any integer minute T, he can remove at most one dish from the oven.
 *   The unpleasant value of removing a dish at minute T is |T - t_i|.
 *   Goal: minimize total unpleasant value over all dishes.
 *
 * Algorithm:
 *   This problem uses dynamic programming. We sort the cooking times first,
 *   then use DP table f[p][w] = minimum cost to place first p dishes,
 *   where w represents time slot used (up to 2*n).
 *   
 *   State transition:
 *     f[p][w] = min(f[p-1][w-1] + penalty, f[p][w-1])
 *     Where penalty = |t[p] - w|
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(n^2)
 */

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long q;
  scanf("%ld", &q);
  while (q--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> t(n + 1); // Cooking times for dishes (1-indexed)
    for (long p = 1; p <= n; p++) {
      scanf("%ld", &t[p]);
    }
    sort(t.begin(), t.end()); // Sort optimal cooking times
    
    // DP table: f[p][w] = min cost to place first p dishes at time slots up to w
    std::vector<std::vector<long>> f(n + 1, std::vector<long>(2 * n + 1, 0));
    
    // Initialize first row of DP table (no dishes placed yet)
    for (long p = 1; p <= n; p++) {
      f[p][0] = 1e9; // Impossible to place p dishes at time 0
    }
    
    // Fill DP table
    for (long p = 1; p <= n; p++) {
      for (long w = 1; w <= 2 * n; w++) {
        long penalty = t[p] - w; // Penalty when placing dish p at time w
        if (penalty < 0) {
          penalty = -penalty;
        }
        
        // Two choices:
        // 1. Place dish p at time w (use previous state f[p-1][w-1])
        long act = f[p - 1][w - 1] + penalty;
        
        // 2. Skip placing dish p at time w, take best from same time slot
        long idle = f[p][w - 1];
        
        // Choose minimum among both options
        f[p][w] = (idle < act) ? idle : act;
      }
    }
    
    printf("%ld\n", f[n][2 * n]); // Result is minimum cost to place all dishes
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/