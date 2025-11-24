// Problem: CF 2153 D - Not Alone
// https://codeforces.com/contest/2153/problem/D

/*
D. Not Alone
Task: Given a circular array, find minimum operations to make it "nice" where each element must have at least one adjacent equal element.

Algorithms/Techniques:
- Dynamic Programming with states representing the last 3 elements in the sequence
- Brute-force over all possible initial states (3 permutations) of first 3 elements to explore all valid patterns
- Modular arithmetic and precomputed factorials for additional mathematical operations

Time Complexity: O(n) per test case, where n is the array length. This includes O(1) DP transitions and constant-time rotation.
Space Complexity: O(n) due to storing arrays and memoization for intermediate results.

*/

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <bits/std_abs.h>
#include <stddef.h>
#include <ext/pb_ds/tag_and_trait.hpp>
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

using namespace __gnu_pbds;
using namespace std;
template <class T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
typedef long long ll;
#define f first
#define s second
#define forn(n) for (ll i = 0; i < ll(n); i++)
#define ivec(n, vec)                                                           \
  for (ll i = 0; i < (ll)(n); i++)                                             \
    cin >> (vec)[i];
#define sortv(vec) sort((vec).begin(), (vec).end())
#define sumv(vec) accumulate((vec).begin(), (vec).end(), 0LL)
#define allv(vec) vec.begin(), vec.end()
#define allrv(vec) vec.rbegin(), vec.rend()
#define pb push_back
const ll M = 1e9 + 7;
const ll mod = 998244353;
const ll inf = 1e18;
const int MAXN = 5 * 1e5 + 5;
ll fact[MAXN], invFact[MAXN];
ll modpow(ll a, ll b) {
  ll res = 1;
  while (b > 0) {
    if (b & 1)
      res = (res * a) % mod;
    a = (a * a) % mod;
    b >>= 1;
  }
  return res;
}
void precompute() {
  fact[0] = 1;
  for (int i = 1; i < MAXN; i++)
    fact[i] = (fact[i - 1] * i) % mod;
  invFact[MAXN - 1] = modpow(fact[MAXN - 1], mod - 2);
  for (int i = MAXN - 2; i >= 0; i--)
    invFact[i] = (invFact[i + 1] * (i + 1)) % mod;
}
ll nCr(ll n, ll r) {
  if (r < 0 || r > n)
    return 0;
  return ((fact[n] * invFact[r]) % mod * invFact[n - r]) % mod;
}
ll gcd(ll x, ll y) {
  if (x == 0)
    return y;
  else
    return gcd(y % x, x);
}
vector<ll> getFactors(ll n) {
  vector<ll> factors;
  for (ll i = 2; i <= sqrt(n); i++) {
    if (n % i == 0) {
      factors.push_back(i);
      if (i != n / i)
        factors.push_back(n / i);
    }
  }
  if (n > 1)
    factors.push_back(n);
  sort(factors.begin(), factors.end());
  return factors;
}
ll binpow(ll a, ll n) {
  ll res = 1;
  while (n) {
    if (n & 1) {
      res *= a;
      res %= M;
    }
    a *= a;
    a %= M;
    n >>= 1;
  }
  return res;
}
vector<ll> sieve(ll limit) {
  vector<bool> is_prime(limit + 1, true);
  is_prime[0] = is_prime[1] = false;
  for (ll i = 2; i * i <= limit; ++i) {
    if (is_prime[i]) {
      for (ll j = i * i; j <= limit; j += i)
        is_prime[j] = false;
    }
  }
  vector<ll> primes;
  for (ll i = 2; i <= limit; ++i)
    if (is_prime[i])
      primes.push_back(i);
  return primes;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  ll t;
  cin >> t;
  while (t--) {
    ll n;
    cin >> n;
    vector<ll> a(n);
    forn(n) cin >> a[i];
    ll ans = inf;
    for (int i = 0; i < 3; i++) {
      vector<ll> dp(n);
      dp[0] = inf;
      dp[1] = abs(a[0] - a[1]);
      dp[2] = min(abs(a[0] - a[1]) + abs(a[0] - a[2]),
                  min(abs(a[0] - a[1]) + abs(a[1] - a[2]),
                      abs(a[2] - a[1]) + abs(a[0] - a[2])));
      for (int j = 3; j < n; j++) {
        // DP recurrence: minimum cost considering all valid transitions from last 3 elements
        dp[j] = min(abs(a[j] - a[j - 1]) + dp[j - 2],
                    min(abs(a[j] - a[j - 1]) + abs(a[j] - a[j - 2]),
                        min(abs(a[j] - a[j - 1]) + abs(a[j - 1] - a[j - 2]),
                            abs(a[j - 2] - a[j - 1]) + abs(a[j] - a[j - 2]))) +
                        dp[j - 3]);
      }
      ans = min(ans, dp[n - 1]);
      // Rotate the array to explore different starting permutations (3 cases)
      for (int j = 1; j < n; j++)
        swap(a[j], a[j - 1]);
    }
    cout << ans << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/