// Problem: CF 1658 B - Marin and Anti-coprime Permutation
// https://codeforces.com/contest/1658/problem/B

/*
B. Marin and Anti-coprime Permutation
Algorithm: 
    - For a permutation to be beautiful, the GCD of products (i * p[i]) must be > 1.
    - If n is odd, no such permutation exists because we can't pair all elements to make all products share a common factor > 1.
    - If n is even:
        - We need to count valid permutations where each product i * p[i] shares a common factor > 1 with at least one other product.
        - This reduces to counting arrangements where we can form pairs that have shared factors.
        - The key insight is that for n even, the number of valid permutations is (h!)^2 where h = n/2.
          This reflects arranging pairs such that their products are not coprime.
Time Complexity: O(n^2) per test case due to factorial computation
Space Complexity: O(1) additional space
*/

#include <cstdio>
typedef long long ll;
int main() {
  const ll MOD = 998244353;
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    if (n % 2) { // If n is odd, no beautiful permutation exists
      puts("0");
      continue;
    }
    ll h = n / 2; // Half the size for pairing logic
    ll res(1);
    for (ll p = 2; p <= h; p++) { // Compute factorial of h
      res *= p;
      res %= MOD;
    }
    printf("%lld\n", (res * res % MOD)); // Square the result to get final count
  }
}


// https://github.com/VaHiX/codeForces/