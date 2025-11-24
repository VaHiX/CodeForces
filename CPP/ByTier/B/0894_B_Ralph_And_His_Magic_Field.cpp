// Problem: CF 894 B - Ralph And His Magic Field
// https://codeforces.com/contest/894/problem/B

/*
Code Purpose:
This program calculates the number of ways to fill an n x m grid with integers such that the product of integers in each row and column equals k (either 1 or -1). The solution uses mathematical properties and modular exponentiation to compute the result efficiently.

Algorithms/Techniques:
- Modular exponentiation (fast exponentiation)
- Mathematical reasoning for parity and grid constraints

Time Complexity: O(log(n) + log(m)) due to fast exponentiation
Space Complexity: O(1) - only using a constant amount of extra space
*/

#include <cstdio>
typedef long long ll;

// Fast exponentiation function to compute (base^x) % MOD
ll qexp(ll base, ll x, ll MOD) {
  if (x == 0) {
    return 1;
  }
  base %= MOD;
  ll r = qexp(base, x / 2, MOD); // Recursive call with half the power
  ll res = (((r * r) % MOD) * ((x & 1) ? (base % MOD) : 1)) % MOD; // Combine results
  return res;
}

int main() {
  const ll MOD = 1000000007;
  ll n, m, k;
  scanf("%lld %lld %lld", &n, &m, &k);
  
  // If k is -1 and the dimensions have different parity, the problem is impossible
  if ((k < 0) && ((n & 1) ^ (m & 1))) {
    puts("0");
  } else {
    // Compute the result using fast exponentiation
    // The number of valid configurations is (2^(m-1))^(n-1)
    ll res = qexp(qexp(2, m - 1, MOD), n - 1, MOD);
    res %= MOD;
    printf("%lld\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/