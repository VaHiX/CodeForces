// Problem: CF 1946 B - Maximum Sum
// https://codeforces.com/contest/1946/problem/B

/*
B. Maximum Sum

Algorithm:
- This problem uses a variation of Kadane's algorithm to find the maximum subarray sum (maximum contiguous sum).
- The idea is that we can maximize the sum by selecting the best contiguous subarray and inserting its sum multiple times.
- After finding the maximum subarray sum (mx), the total sum of original array minus this max subarray gives us a base value.
- Then multiplying mx by 2^k gives us the contribution of all k operations, since each operation can double the subarray sum.

Time Complexity: O(n) for each test case
Space Complexity: O(1)

*/
#include <cstdio>

typedef long long ll;
int main() {
  const ll MOD = 1e9 + 7;
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    ll cur(0), mx(0), total(0);
    for (long p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      total += x;
      cur += x;
      if (cur < 0) {
        cur = 0;
      }
      mx = (mx > cur ? mx : cur); // Keep track of maximum subarray sum using Kadane's algorithm
    }
    total -= mx; // Subtract the maximum subarray from total to get base sum
    total = (total % MOD + MOD) % MOD;
    while (k--) {
      mx *= 2;
      mx %= MOD; // Multiply mx by 2^k, taking mod each time to prevent overflow
    }
    printf("%lld\n", (total + mx + MOD) % MOD); // Add total and mx, adjust modulo
  }
}


// https://github.com/VaHiX/codeForces/