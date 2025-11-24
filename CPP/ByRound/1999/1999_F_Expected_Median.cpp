// Problem: CF 1999 F - Expected Median
// https://codeforces.com/contest/1999/problem/F

/*
F. Expected Median
time limit per test3 seconds
memory limit per test256 megabytes

Task: Given a binary array of length n and an odd integer k,
find the sum of medians over all subsequences of length k.
Answer modulo 10^9 + 7.

Algorithms/Techniques:
- Combinatorics using precomputed factorials and inverse factorials
- Fast exponentiation for modular inverse
- Counting based on the contribution of each element (0 or 1) to the median

Time Complexity: O(N + T * N), where N = 2*10^5, T is number of test cases.
Space Complexity: O(N)

*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
const int mod = 1e9 + 7, N = 2e5 + 7;

// Fast modular exponentiation
ll fpow(ll a, ll b) {
  ll r = 1;
  while (b) {
    if (b & 1)
      r = (r * a) % mod;
    a = (a * a) % mod;
    b >>= 1;
  }
  return r;
}

// Precomputed factorials and inverse factorials
ll fac[N], ifac[N];

// Compute combination C(n, k)
ll C(ll n, ll k) {
  if (k < 0 || n < 0 || k > n)
    return 0ll;
  return fac[n] * ifac[k] % mod * ifac[n - k] % mod;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  
  // Precompute factorials
  fac[0] = 1;
  for (ll i = 1; i < N; i++)
    fac[i] = (fac[i - 1] * i) % mod;

  // Precompute inverse factorials using backward iteration
  ifac[N - 1] = fpow(fac[N - 1], mod - 2);
  for (ll i = N - 2; i >= 0; i--)
    ifac[i] = (ifac[i + 1] * (i + 1)) % mod;

  int tt = 1;
  cin >> tt;
  while (tt--) {
    ll n, k, c = 0;
    cin >> n >> k;
    vector<ll> a(n);
    for (ll &i : a)
      cin >> i, c += i; // Count of 1s in the array

    ll ans = 0;
    // For each possible median value 't' in [1, n] such that t >= (k+1)/2
    for (ll t = (k + 1) / 2; t <= n; t++) {
      // C(c, t) = number of ways to choose t ones from c ones
      // C(n - c, k - t) = number of ways to choose (k-t) zeros from (n-c) zeros
      ans += (C(c, t) * C(n - c, k - t)) % mod;
    }
    ans %= mod;
    cout << ans << endl;
  }
}


// https://github.com/VaHiX/codeForces/