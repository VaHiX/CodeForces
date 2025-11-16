// Problem: CF 1942 G - Bessie and Cards
// https://codeforces.com/contest/1942/problem/G

/*
Algorithm/Technique:
- Preprocessing factorials and modular inverses using sieve-like method for combinatorics.
- Using inclusion-exclusion and stars and bars for counting valid sequences.
- Combinatorial mathematics with modular arithmetic.
- Time complexity: O(1) per query after preprocessing (O(n) for preprocessing where n is max constraint)
- Space complexity: O(n) for precomputed arrays

*/

#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;
typedef long long ll;
typedef pair<ll, int> pii;
const int maxn = 2e5 + 5;
const ll mod = 998244353;
const ll inf = 1e18;

// Fast exponentiation function for modular exponentiation
ll fpow(ll a, ll b) {
  ll ans = 1;
  while (b) {
    if (b & 1)
      ans = ans * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return ans;
}

// Precompute factorials and inverse factorials
ll fac[maxn * 3], inv[maxn * 3];
void precalc(int x) {
  fac[0] = inv[0] = inv[1] = 1;
  for (int i = 1; i <= x; i++)
    fac[i] = fac[i - 1] * i % mod;
  for (int i = 2; i <= x; i++)
    inv[i] = inv[mod % i] * (mod - mod / i) % mod;
  for (int i = 2; i <= x; i++)
    (inv[i] *= inv[i - 1]) %= mod;
}

// Combination function C(n, m)
ll C(int n, int m) {
  return n < m ? 0 : fac[n] * inv[m] % mod * inv[n - m] % mod;
}

// Function F(m, n) = C(m + n - 1, n) - C(m + n - 1, m)
ll F(int m, int n) { return (C(m + n - 1, n) + mod - C(m + n - 1, m)) % mod; }

// Main calculation function
void work() {
  int a, b, c;
  cin >> c >> b >> a; // Note: input order is c, b, a due to how it's read in code
  ll ans = fac[a] * fac[c] % mod * fac[5] % mod * inv[a + c + 5] % mod, res = 0;
  // Loop over possible draw configurations that could get all 5 special cards
  for (int i = 5; i <= 2 * min(a, c) + 5; i += 2) {
    int x = (i + 5) / 2, y = (i - 5) / 2;
    (res += C(x, 5) * F(x, y) % mod * C(a + c + 5 - i, a - y)) %= mod;
  }
  // Special case when a >= c
  if (a >= c)
    (res += C(c + 5, 5) * (C(a + c + 5, a) + mod - C(a + c + 5, c))) %= mod;
  cout << res * ans % mod << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  precalc(600000); // Precompute up to 600000!
  int T;
  cin >> T;
  while (T--)
    work();
  return 0;
}


// https://github.com/VaHiX/CodeForces/