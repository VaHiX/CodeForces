// Problem: CF 1875 C - Jellyfish and Green Apple
// https://codeforces.com/contest/1875/problem/C

/*
C. Jellyfish and Green Apple

Algorithm: 
- The problem reduces to determining if we can distribute n apple pieces among m people such that each person gets equal weight.
- Each operation splits a piece of weight w into two pieces of weight w/2.
- This is equivalent to checking whether after some operations, the total number of apple pieces (n') can be divided evenly among m people.
- The key insight is: we must have n * 2^k ≡ 0 (mod m), where k is the number of operations.
- Let n' = n * 2^k and total weight W = n'.
- Each person gets W/m weight.
- So, the process involves:
  - Reducing n modulo m first to simplify.
  - Then determining the minimum number of operations to make m a power of 2.
  - If not possible (m is not a power of 2), output -1.

Time Complexity: O(log(max(n,m))) per test case due to GCD and bit operations.
Space Complexity: O(1) – constant extra space.

*/
#include <cstdio>
typedef long long ll;

// Compute GCD of two numbers
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, m;
    scanf("%lld %lld", &n, &m);
    n %= m; // Reduce n modulo m
    ll g = gcd(n, m); // Find GCD to simplify fraction
    n /= g;  // Simplify numerator
    m /= g;  // Simplify denominator
    
    // If m is not a power of 2, it's impossible to achieve equal division using the knife
    if (m & (m - 1)) {
      puts("-1");
      continue;
    }
    
    ll res(0); // Count operations needed
    
    // While n doesn't evenly divide m, perform operations:
    while (n % m) {
      if (n > m) {
        n %= m; // If n > m, reduce it mod m
      }
      res += n;  // Accumulate steps
      n *= 2;    // Split all current pieces in half
    }
    
    printf("%lld\n", g * res); // Multiply by GCD to get final result
  }
}


// https://github.com/VaHiX/codeForces/