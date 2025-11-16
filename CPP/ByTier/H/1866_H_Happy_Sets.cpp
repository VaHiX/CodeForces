// Problem: CF 1866 H - Happy Sets
// https://codeforces.com/contest/1866/problem/H

/*
 * Problem: H. Happy Sets
 * 
 * Purpose: Count the number of arrays of N sets, where each set contains integers from 1 to K,
 * such that the sets can be rearranged in a sequence where each set is a child of the next.
 * A set A is a child of set B if for every element x in A, there exists an element x+1 in B.
 * 
 * Algorithm: 
 * - Dynamic Programming with inclusion-exclusion principle
 * - f[i] represents the number of valid "chains" of length i satisfying the child condition
 * - Use precomputed factorials and modular inverse for combinations
 * - For each i, compute f[i] using recurrence relation and cumulative sum
 * - Final answer is computed by summing over all possible chain lengths using combinations
 * 
 * Time Complexity: O(N + K)
 * Space Complexity: O(N + K)
 * 
 * Techniques:
 * - Modular arithmetic
 * - Precomputed factorials and inverse factorials
 * - Fast exponentiation
 * - Inclusion-exclusion principle
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define ff first
#define ss second
typedef long long ll;
typedef long double ld;
const ll mod = 998244353;
const ll maxn = 2e5 + 5;

// Fast modular exponentiation
ll modpow(ll b, ll e) {
  ll ans = 1;
  for (; e; b = b * b % mod, e /= 2) {
    if (e & 1)
      ans = ans * b % mod;
  }
  return ans;
}

// Modular inverse using Fermat's little theorem
ll inv(ll x) { return modpow(x, mod - 2); }

// Ensure result is in [0, mod)
ll fix(ll i) {
  i %= mod;
  if (i < 0)
    i += mod;
  return i;
}

// Precomputed factorials and inverse factorials
ll fac[maxn];
ll ifac[maxn];

// Combination C(i, j) = i! / (j! * (i-j)!)
ll ncr(ll i, ll j) {
  if (i < j)
    return 0;
  return fac[i] * ifac[j] % mod * ifac[i - j] % mod;
}

// Initialize factorial arrays
void initfac() {
  fac[0] = 1;
  rep(x, 1, maxn) fac[x] = fac[x - 1] * x % mod;
  ifac[maxn - 1] = inv(fac[maxn - 1]);
  for (int x = maxn - 1; x >= 1; x--) {
    ifac[x - 1] = ifac[x] * x % mod;
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  initfac();
  
  ll n, k;
  cin >> n >> k;
  
  // f[i] stores the count of valid sequences for length i
  vector<ll> f(n + 1);
  f[0] = 1;
  ll cursum = 1;
  
  // Compute f[i] for i from 1 to n
  for (int i = 1; i <= n; i++) {
    if (k - i + 1 < 0)
      break;
    // f[i] = i! * (i+1)^(k-i+1) - cumulative sum of previous values
    f[i] = fac[i] * modpow(i + 1, k - i + 1) % mod;
    f[i] = (f[i] - cursum + mod) % mod;
    cursum = (cursum + f[i]) % mod;
  }
  
  // Final answer: sum over all sizes of valid chain structures
  ll ans = 1;
  for (int i = 1; i <= n; i++) {
    ans = (ans + f[i] * fac[n] % mod * ifac[n - i] % mod) % mod;
  }
  
  cout << ans << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/