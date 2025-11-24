// Problem: CF 1606 E - Arena
// https://codeforces.com/contest/1606/problem/E

/*
Algorithm: Dynamic Programming with Combinatorics
Time Complexity: O(n^3)
Space Complexity: O(n^2)

This solution uses dynamic programming with combinatorial mathematics to count the number of ways
to assign initial health points to heroes such that no single hero survives all rounds.

The key insight is to work backwards from the final state where no hero remains alive,
tracking how many heroes could have started with each health value.
We use combinatorics to track combinations and modular arithmetic throughout.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>

#define LL long long
#define mod 998244353
using namespace std;
const int N = 509;
int n, x;
LL ans;
LL c[N][N], dp[N][N];

int main() {
  cin >> n >> x;
  // Precompute binomial coefficients C(i,j) for all i,j up to n
  for (int i = 0; i <= n; i++) {
    c[i][0] = c[i][i] = 1ll;
    for (int j = 1; j < i; j++)
      c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
  }
  
  // Initialize base case: 1 way to have 0 heroes alive with 0 health points
  dp[n][0] = 1ll;
  
  // Work backwards from n heroes to 1 hero (eliminating one hero each round)
  for (int i = n; i > 1; i--)
    for (int j = 0; j < x; j++) {
      // Calculate the new maximum health value for the next round
      int nj = min(x, j + i - 1);
      LL pw = 1ll;
      // For each possible number of remaining heroes (k) in the next round
      for (int k = i; k >= 0; k--) {
        // Update dp[k][nj] by adding contribution from dp[i][j]
        // Using combinatorial coefficient C(i,k) and power term (nj-j)^k
        dp[k][nj] = (dp[k][nj] + dp[i][j] * (c[i][k] * pw % mod) % mod) % mod;
        pw = pw * (LL)(nj - j) % mod;
      }
    }
  
  // Sum up all possible configurations where no hero wins (all have 0 heroes left)
  for (int i = 0; i <= x; i++)
    ans = (ans + dp[0][i]) % mod;
  
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/