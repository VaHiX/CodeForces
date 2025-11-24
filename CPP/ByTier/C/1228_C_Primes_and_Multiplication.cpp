// Problem: CF 1228 C - Primes and Multiplication
// https://codeforces.com/contest/1228/problem/C

/*
C. Primes and Multiplication
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

Let's introduce some definitions that will be needed later.
Let prime(x) be the set of prime divisors of x. For example, prime(140) = { 2, 5, 7 }, prime(169) = { 13 }.
Let g(x, p) be the maximum possible integer p^k where k is an integer such that x is divisible by p^k. For example:
 
 g(45, 3) = 9 (45 is divisible by 3^2=9 but not divisible by 3^3=27), 
 g(63, 7) = 7 (63 is divisible by 7^1=7 but not divisible by 7^2=49). 
Let f(x, y) be the product of g(y, p) for all p in prime(x). For example:
 
 f(30, 70) = g(70, 2) * g(70, 3) * g(70, 5) = 2^1 * 3^0 * 5^1 = 10, 
 f(525, 63) = g(63, 3) * g(63, 5) * g(63, 7) = 3^2 * 5^0 * 7^1 = 63. 
You have integers x and n. Calculate f(x, 1) * f(x, 2) * ... * f(x, n) mod (10^9 + 7).

Algorithm:
- For each prime factor p of x, compute how many times p appears in the product over all f(x,i) for i from 1 to n.
- For a fixed prime p and a value i, g(i,p) = p^(max_k such that p^k divides i)
- Sum up contributions efficiently using exponentiation and properties of divisors.
- The algorithm uses fast exponentiation (binary exponentiation) for modular arithmetic.
  
Time Complexity: O(sqrt(x) * log(n)) due to prime factorization and loop over powers.
Space Complexity: O(1) - only a few variables stored.
*/

#include <cstdio>
typedef long long ll;
const ll MOD = 1e9 + 7;

// Fast modular exponentiation function
ll power(ll x, ll y) {
  ll res(1);
  for (; y; y >>= 1, x = ((x % MOD) * (x % MOD)) % MOD) { // Square x and halve y each iteration
    if (y & 1) { // If y is odd, multiply result by current x
      res *= (x % MOD);
      res %= MOD;
    }
  }
  return res;
}

int main() {
  ll x, n;
  scanf("%lld %lld", &x, &n);
  ll ans(1);
  
  // Iterate over all possible prime factors up to sqrt(x)
  for (ll p = 2; p * p <= x; p++) {
    if (x % p) { // Skip if not a factor
      continue;
    }
    
    // Remove all occurrences of p from x
    while (x % p == 0) {
      x /= p;
    }
    
    // For each power of p up to n, calculate contribution and multiply result
    for (ll q = p; q <= n; q *= p) {
      ans *= (power(p, n / q) % MOD); // Multiply by power of p raised to number of multiples
      ans %= MOD;
      if (1.0L * q * p > n) { // Break when overflow expected
        break;
      }
    }
  }
  
  // Handle remaining prime factor > sqrt(x)
  if (x > 1) {
    for (ll q = x; q <= n; q *= x) {
      ans *= power(x, n / q) % MOD; // Similar calculation as for smaller primes
      ans %= MOD;
      if (1.0L * q * x > n) { // Break when overflow expected
        break;
      }
    }
  }
  
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/codeForces/