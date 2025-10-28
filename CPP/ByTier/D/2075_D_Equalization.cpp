// Problem: CF 2075 D - Equalization
// https://codeforces.com/contest/2075/problem/D

/*
D. Equalization
Algorithms/Techniques: Dynamic Programming with Bit Manipulation, Preprocessing
Time Complexity: O(N^2 * M + t) where N = 57 (number of bits), M = 15 (max k value), t = number of test cases
Space Complexity: O(N^2) for DP table

The problem involves making two numbers x and y equal by dividing them with powers of 2,
where each operation costs 2^k and each k can only be used once.

We precompute the minimum cost to make any pair of bit representations (x >> i, y >> j) equal.
This approach uses dynamic programming on bits, considering all possible operations (dividing x or y by 2^k).
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
typedef long long LL;
const int N = 57, M = 15; // N is number of bits for values up to 10^17, M is max k value
const int inf = 0x3f3f3f3f;
int t;
int dp[N + 1][N + 1]; // dp[i][j] stores min cost to equalize x>>i and y>>j
LL x, y;

void solve() {
  scanf("%lld%lld", &x, &y);
  int ans = inf;
  // Try all bit representations of x and y to find minimum cost to make them equal
  for (int i = 0; i <= N; i++)
    for (int j = 0; j <= N; j++)
      if ((x >> i) == (y >> j)) // If the bit-shifted versions are equal
        ans = min(ans, dp[i][j]); // Update answer with minimum cost
  printf("%d\n", ans);
}

int main() {
  memset(dp, 0x3f, sizeof(dp)); // Initialize dp with infinity
  dp[0][0] = 0; // Base case: no cost to equalize x>>0 and y>>0 (both are original values)
  
  // Preprocessing step: compute minimum cost to bring any two bit shifts to same value
  for (int i = 1; i <= M; i++) // For each possible k from 1 to 15
    for (int j = N; j >= 0; j--) // Traverse backwards to avoid recomputation
      for (int k = N; k >= 0; k--) {
        if (j >= i)
          dp[j][k] = min(dp[j][k], dp[j - i][k] + (1 << i)); // Update if dividing x reduces j
        if (k >= i)
          dp[j][k] = min(dp[j][k], dp[j][k - i] + (1 << i)); // Update if dividing y reduces k
      }
  
  scanf("%d", &t); // Read number of test cases
  while (t--)
    solve(); // Process each test case
  return 0;
}


// https://github.com/VaHiX/codeForces/