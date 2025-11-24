// Problem: CF 992 C - Nastya and a Wardrobe
// https://codeforces.com/contest/992/problem/C

/*
 * Problem: Nastya and a Wardrobe
 * 
 * Algorithm: Mathematical expectation calculation using recurrence and modular exponentiation
 * 
 * Time Complexity: O(log k) due to fast exponentiation
 * Space Complexity: O(log k) due to recursion stack in power function
 * 
 * Approach:
 * - Each month, the number of dresses doubles and then decreases by 1 with 50% probability
 * - For k+1 months, we compute the expected value via the formula derived from linearity of expectation
 * - The formula is: E(X_{k+1}) = 2^{k+1} * x - 2^k + 1
 * - We use modular exponentiation to compute powers modulo 10^9 + 7
 */

#include <cstdio>
typedef long long ll;

// Fast modular exponentiation function
ll pow(ll b, ll x, ll m) {
  if (x <= 0) {
    return 1;
  }
  ll prev = pow(b, x / 2, m);  // Recursive call to compute power
  ll res = (prev * prev) % m;  // Square the result
  if (x % 2) {                 // If exponent is odd, multiply by base
    res *= b;
    res %= m;
  }
  return res;
}

int main() {
  const ll MOD = 1e9 + 7;  // Modulo constant
  ll x, k;
  scanf("%lld %lld", &x, &k);
  
  // Compute expected value using derived formula
  ll ans = pow(2, k + 1, MOD) * (x % MOD) - pow(2, k, MOD) + 1;
  ans = (ans + MOD) % MOD;  // Ensure result is positive modulo
  printf("%lld\n", (x > 0) ? ans : 0);  // Special case when x=0
  return 0;
}


// https://github.com/VaHiX/CodeForces/