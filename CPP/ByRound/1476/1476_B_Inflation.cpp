// Problem: CF 1476 B - Inflation
// https://codeforces.com/contest/1476/problem/B

/*
B. Inflation
Algorithm: Greedy approach to minimize total changes while keeping inflation coefficients <= k%
Time Complexity: O(n) per test case
Space Complexity: O(1)

For each month, we compute the required increase in previous months' values such that 
the current inflation coefficient (p_i / sum of previous prices) does not exceed k/100.
We process prices left to right and accumulate the necessary changes.

Key idea:
- For each new price p_i, if it violates the constraint (p_i > (k/100) * cumulative_sum), 
  we adjust the cumulative sum by increasing previous values minimally.
- The required adjustment is calculated as: res = (100 * x - k * cs + (k - 1)) / k
- This ensures that new inflated ratio does not exceed k%

Sample Inputs:
2
4 1
20100 1 202 202
3 100
1 1 1

Sample Outputs:
99
0
*/

#include <cstdio>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    ll cs(0), res(0);
    scanf("%lld", &cs);
    for (ll p = 1; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      // Check if current price x violates the k% inflation constraint
      if (100 * x > k * (cs + res)) {
        // Calculate minimum adjustment needed to satisfy constraint
        res = (100 * x - k * cs + (k - 1)) / k;
      }
      cs += x;  // Add current price to cumulative sum
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/