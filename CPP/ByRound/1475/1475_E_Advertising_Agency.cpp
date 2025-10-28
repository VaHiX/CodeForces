// Problem: CF 1475 E - Advertising Agency
// https://codeforces.com/contest/1475/problem/E

/*
E. Advertising Agency
Algorithms/Techniques: Sorting, Combinatorics, Modular Arithmetic

Time Complexity: O(N^2 + T*N) where N is max n across all test cases and T is number of test cases
Space Complexity: O(N^2) for precomputed factorials and inverse factorials

This solution uses the following approach:
1. Sort bloggers in descending order of followers to easily identify maximum sum selection
2. Identify the boundary elements that are part of the optimal k-bloggers selection
3. Count how many ways we can choose exactly k bloggers from the available candidates such that their total follows is maximized

The key idea is that to maximize the sum, we should take the top k bloggers.
We calculate how many valid combinations there are by counting how many choices exist for 
the boundary elements where a tie might occur (i.e., when a[k] == a[i] for some i in range [0,k])

Preprocessing: Calculate factorials and inverse factorials modulo 10^9+7 to compute combinations efficiently
*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

// Fast exponentiation to compute modular inverse using Fermat's little theorem
ll fastexp(ll base, ll x, ll mod) {
  base %= mod;
  ll res(1);
  while (x) {
    if (x % 2) {            // If x is odd, multiply result by current base
      res *= base;
      res %= mod;
      --x;
    } else {                // If x is even, square the base and halve x
      base = base * base;
      base %= mod;
      x /= 2;
    }
  }
  return res;
}

// Compute combination C(a,b) modulo mod using precomputed factorials
ll moduloChoose(ll a, ll b, ll mod, const std::vector<ll> &fact,
                const std::vector<ll> &invFact) {
  if (a < b) {              // If choosing more than available
    return 0;
  } else if (a == b) {      // If choosing all
    return 1;
  }
  // C(a,b) = fact[a] * invFact[b] * invFact[a-b]
  return (fact[a] % mod *
          (((invFact[b] % mod) * (invFact[a - b] % mod)) % mod)) %
         mod;
}

int main() {
  const ll MOD = 1e9 + 7;   // Modulo value
  const ll N = 1017;        // Max size for precomputation
  std::vector<ll> fact(N, 1), invFact(N, 1);  // Precomputed factorials and inverses

  // Compute factorials
  for (long p = 1; p < N; p++) {
    fact[p] = fact[p - 1] * p;
    fact[p] %= MOD;
  }

  // Compute inverse factorials using Fermat's little theorem
  for (long p = 1; p < N; p++) {
    invFact[p] = fastexp(fact[p], MOD - 2, MOD);
  }

  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);

    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }

    // Append sentinel values to simplify boundary checks
    a.push_back(1e6);
    a.push_back(-1);

    // Sort in descending order to get optimal selection first
    sort(a.rbegin(), a.rend());

    // Count how many candidates are strictly less than the k-th element (to find left boundary)
    ll left(k);
    while (a[left] == a[k]) {
      --left;
    }

    // Count how many candidates are exactly equal to the k-th element (to find right boundary)
    ll right(k);
    while (a[right] == a[k]) {
      ++right;
    }

    // Compute combinations: number of ways to select (k - left) elements from (right - left - 1)
    ll ans = moduloChoose(right - left - 1, k - left, MOD, fact, invFact);
    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/