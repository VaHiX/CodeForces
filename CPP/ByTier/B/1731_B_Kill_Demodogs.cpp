// Problem: CF 1731 B - Kill Demodogs
// https://codeforces.com/contest/1731/problem/B

/*
B. Kill Demodogs
Purpose: Calculate the maximum number of Demodogs that can be killed on a path from (1,1) to (n,n) in an n×n grid,
         where each cell (i,j) contains i·j Demodogs. The result is multiplied by 2022 and taken modulo 10^9 + 7.

Algorithms/Techniques: Mathematical formula derivation for sum of products along all paths in grid.
                       Efficient computation using modular arithmetic and precomputed constants.

Time Complexity: O(1) per test case
Space Complexity: O(1)

The problem reduces to computing the sum of i*j over all cells (i,j) on any path from (1,1) to (n,n).
This leads to a closed-form formula which we compute directly for efficiency.
*/

#include <cstdio>
typedef long long ll;
int main() {
  const ll MOD = 1e9 + 7;
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll res(337);           // Precomputed constant for formula
    res *= n;              // Multiply by n
    res %= MOD;            // Apply modulo
    res *= (n + 1);        // Multiply by (n + 1)
    res %= MOD;            // Apply modulo
    res *= (4 * n - 1);    // Multiply by (4n - 1)
    res %= MOD;            // Apply modulo
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/