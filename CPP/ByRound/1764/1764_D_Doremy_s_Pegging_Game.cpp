// Problem: CF 1764 D - Doremy's Pegging Game
// https://codeforces.com/contest/1764/problem/D

/*
Algorithm: Dynamic Programming with Combinatorics
Purpose: Calculate the number of different arrays that can be produced by removing pegs in a specific order
Time Complexity: O(n^2)
Space Complexity: O(n^2)

The problem involves a game where we remove red pegs from a regular n-sided polygon until a blue peg in the center is touched.
We use dynamic programming and combinatorics to compute the number of valid sequences.

The approach:
1. Precompute factorials and binomial coefficients
2. Use dynamic programming to calculate valid configurations
3. Sum up all valid outcomes and multiply by n to account for rotation

Key observations:
- The rubber band touches the blue peg when exactly half the pegs have been removed (rounded up)
- The state transition considers which pegs can be removed at each step
- Binomial coefficients are used to count combinations of removal orders
*/

#include <algorithm>
#include <iostream>

using namespace std;
long long n, p, jc[5005], dp[5005][5005], sum = 0;
int main() {
  cin >> n >> p;
  jc[0] = 1;
  for (long long i = 1; i <= 5000; i++) {
    jc[i] = jc[i - 1] * i % p;
  }
  for (long long i = 0; i <= 5000; i++) {
    dp[i][0] = 1;
    for (long long j = 1; j <= i; j++) {
      dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % p;
    }
  }
  long long ls = n / 2;
  for (long long i = ls; i <= n; i++) {
    for (long long j = 0; j <= max(0LL, n - i - 2); j++) {
      if (ls * 2 > i) {
        sum = (sum +
               (ls * 2 - i) * dp[max(0LL, n - i - 2)][j] % p * jc[i + j - 1]) %
              p;
      }
    }
  }
  cout << sum * n % p;
  return 0;
}


// https://github.com/VaHiX/CodeForces/