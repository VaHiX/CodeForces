// Problem: CF 1939 D - Big Persimmon
// https://codeforces.com/contest/1939/problem/D

/*
 * Problem: Big Persimmon
 * Purpose: Determine the optimal allocation of persimmon pieces between Alice and Bob,
 *          where both play optimally to maximize their own total eaten size.
 * 
 * Approach:
 *   - Dynamic Programming with memoization.
 *   - State representation: f(l, r, k, fl) represents the maximum difference in score
 *     between Alice and Bob when considering pieces from index l to r, where k is the
 *     current total time difference and fl is a flag indicating whose turn it is.
 *   - Transitions involve choosing either the left or right piece and updating the game state.
 *   - Optimization includes precomputing prefix sums and using pruning.
 *
 * Time Complexity: O(n^3), due to the DP states and transitions.
 * Space Complexity: O(n^3), for the memoization table.
 */

#include <stdio.h>
#include <string.h>
#include <algorithm>

#define N 2005
using namespace std;
int n, a[N], sm[N], sf[N], ps[20005], g[N][N * 12][2];
int f(int, int, int, int);
int main() {
  int i, nw = 0;
  scanf("%d", &n);
  memset(g, -1, sizeof(g)); // Initialize memoization table
  for (i = 1; i <= n; ++i)
    scanf("%d", &a[i]); // Read piece sizes
  for (i = 1; i <= n; ++i)
    sm[i] = sm[i - 1] + a[i]; // Prefix sum of sizes
  for (i = n; i; --i)
    sf[i] = sf[i + 1] + a[i]; // Suffix sum of sizes
  ps[0] = n + 1;
  for (i = n; i; --i) {
    nw += a[i];
    ps[nw] = i; // Precompute ps array for optimization
  }
  for (i = 1; i <= sm[n]; ++i)
    if (!ps[i])
      ps[i] = ps[i - 1]; // Fill remaining entries
  printf("%d %d\n", f(1, n, 0, 0), sm[n] - f(1, n, 0, 0)); // Print Alice's score and Bob's score
  return 0;
}
int f(int l, int r, int k, int fl) {
  if (l == r)
    return a[l]; // Base case: only one piece left
  if (g[l][sf[r + 1] - k + (n - r)][fl] != -1)
    return g[l][sf[r + 1] - k + (n - r)][fl]; // Memoization check

  int ans = 0;
  // Try picking the left piece
  if (a[l] <= k - fl)
    ans = max(ans, f(l + 1, r, k - a[l], fl) + a[l]);
  else
    ans = max(ans, sm[r] - sm[l] - f(l + 1, r, a[l] - k, fl ^ 1) + a[l]);
  // Try picking the right piece
  if (a[r] > k - fl)
    ans =
        max(ans, sm[r - 1] - sm[l - 1] - f(l, r - 1, a[r] - k, fl ^ 1) + a[r]);
  // Check for early pruning based on prefix sums
  int x = max(l + 1, ps[sf[r + 1] + k]);
  if (x != r + 1) {
    if (sm[r] - sm[x - 1] <= k - fl)
      ans = max(ans,
                f(l, x - 1, k - (sm[r] - sm[x - 1]), fl) + (sm[r] - sm[x - 1]));
    else
      ans = max(ans, sm[x - 1] - sm[l - 1] -
                         f(l, x - 1, (sm[r] - sm[x - 1]) - k, fl ^ 1) +
                         (sm[r] - sm[x - 1]));
  }
  return g[l][sf[r + 1] - k + (n - r)][fl] = ans; // Store result in memoization table
}


// https://github.com/VaHiX/CodeForces/