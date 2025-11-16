// Problem: CF 1817 C - Similar Polynomials
// https://codeforces.com/contest/1817/problem/C

/*
 * Purpose: Solve the problem of finding an integer 's' such that B(x) ≡ A(x + s) (mod 10^9 + 7)
 *          for two similar polynomials A(x) and B(x) given their values at points 0, 1, ..., d.
 *
 * Algorithm:
 *   - Uses Newton interpolation and properties of finite differences to compute the shift 's'.
 *   - Calculates coefficients using factorial precomputations and modular inverse.
 *   - Applies a derived formula involving sums of polynomial evaluations to determine 's'.
 *
 * Time Complexity: O(n log n) due to modular exponentiation and preprocessing of factorials.
 * Space Complexity: O(n) for storing precomputed factorials and inverses.
 */

#include <iostream>

using namespace std;
const int N = 2500005, mod = 1e9 + 7;
int n, a[N], b[N], fac[N], ifac[N], inv[N];

// Fast modular exponentiation
int qpow(int x, int p) {
  int ans = 1;
  while (p) {
    if (p & 1)
      ans = 1ll * ans * x % mod;
    p /= 2, x = 1ll * x * x % mod;
  }
  return ans;
}

// Precomputed prefix and suffix values used in formula derivation
int pre[N], suc[N];
int An, An1, Bn1, Z = 0;

int main() {
  ios ::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n;
  fac[0] = 1;
  for (int i = 1; i <= n + 1; i++) {
    fac[i] = 1ll * fac[i - 1] * i % mod;
  }
  ifac[n + 1] = qpow(fac[n + 1], mod - 2);
  for (int i = n + 1; i; i--) {
    ifac[i - 1] = 1ll * ifac[i] * i % mod;
  }
  for (int i = 1; i <= n + 1; i++)
    inv[i] = 1ll * ifac[i] * fac[i - 1] % mod;
  
  // Read coefficients for A(x)
  for (int i = 0; i <= n; i++)
    cin >> a[i];
  
  // Read coefficients for B(x)
  for (int i = 0; i <= n; i++)
    cin >> b[i];
  
  // Compute Z as sum of (mod - i) for i in 0..n
  for (int i = 0; i <= n; i++)
    Z = (Z - i + mod) % mod;

  // Iterate through all points to calculate relevant sums using Newton's interpolation
  for (int i = 0; i <= n; i++) {
    int k1 = 1ll * a[i] * ifac[i] % mod * ifac[n - i] % mod;
    if (n - i & 1)
      k1 = (mod - k1) % mod;
    An = (An + k1) % mod;
    int T = (Z + i) % mod;
    An1 = (1ll * An1 + 1ll * k1 * T) % mod;

    int k2 = 1ll * b[i] * ifac[i] % mod * ifac[n - i] % mod;
    if (n - i & 1)
      k2 = (mod - k2) % mod;
    Bn1 = (1ll * Bn1 + 1ll * k2 * T) % mod;
  }

  // Compute K = Bn1 - An1 mod mod
  int K = (Bn1 - An1 + mod) % mod;

  // Output final result using modular inverse of An and n
  cout << 1ll * K * qpow(n, mod - 2) % mod * qpow(An, mod - 2) % mod << '\n';
  return 0;
}


// https://github.com/VaHiX/CodeForces/