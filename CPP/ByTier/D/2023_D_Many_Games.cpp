// Problem: CF 2023 D - Many Games
// https://codeforces.com/contest/2023/problem/D

/*
 * Problem: D. Many Games
 * 
 * Purpose:
 *   This program computes the maximum expected value of winnings from playing a subset of games
 *   in a casino, where each game has a win probability and a prize amount. The optimal choice of
 *   games is determined using dynamic programming with bucketing based on probabilities.
 * 
 * Approach:
 *   1. Games with 100% probability are simply added to the total sum since they always win.
 *   2. For games with less than 100% probability, they are grouped by their probability values.
 *   3. For each probability group, we use a greedy-like approach to fill a DP array, considering
 *      how many times each game can be included in combinations.
 *   4. Finally, we compute the maximum expected value by combining all possible subsets and
 *      their probabilities with the sum of winnings.
 * 
 * Algorithms/Techniques:
 *   - Dynamic Programming with bucketing (0/1 knapsack style optimization)
 *   - Priority queues for grouping games by probability
 *   - Greedy inclusion of items in DP transitions
 * 
 * Time Complexity: O(n * 100 * 200000) where n is the number of games
 * Space Complexity: O(200000) for the DP array and auxiliary structures
 */

#include <stdio.h>
#include <algorithm>
#include <queue>

#define int long long
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;

// Fast input function
inline int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = (x << 1) + (x << 3) + (ch ^ 48);
    ch = getchar();
  }
  return x * f;
}

int n, sum;
double ans, f[200010]; // f[i] stores the maximum probability of achieving sum i
int w[200010], p[200010]; 
priority_queue<int> q[110]; // q[i] stores all games with probability i (bucketing)

signed main() {
#ifdef LOCAL
  freopen("in", "r", stdin);
  freopen("out", "w", stdout);
#endif

  n = read();
  f[0] = 1; // Base case for DP: probability of getting 0 sum is 1 (empty set)

  for (int i = 1; i <= n; i++) {
    p[i] = read(), w[i] = read();
    if (p[i] == 100) // Games that always win; they contribute directly to the fixed sum
      sum += w[i];
    else
      q[p[i]].push(w[i]); // Group games by their probabilities
  }

  // Process each probability group from 1 to 99
  for (int i = 1; i <= 99; i++) {
    // Determine number of times we can take each item (bounded by 100/i, which is the limit on combinations)
    for (int j = 100 / (100 - i); j && !q[i].empty(); j--) {
      int x = q[i].top();
      q[i].pop();
      // Apply DP transition in reverse order (to avoid using updated values)
      for (int k = 200000; k >= x; k--) {
        f[k] = max(f[k], 1.0 * f[k - x] * i / 100); // Update probability of achieving sum k
      }
    }
  }

  // Compute the maximum expected value
  for (int i = 0; i <= 200000; i++)
    ans = max(ans, (i + sum) * f[i]);
  
  printf("%.10lf", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/