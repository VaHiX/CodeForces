// Problem: CF 2020 F - Count Leaves
// https://codeforces.com/contest/2020/problem/F

/*
F. Count Leaves

Algorithms/Techniques: 
- Dirichlet convolution + Mobius inversion + Number theoretical function calculation
- Sieve of Euler (prime sieve algorithm) for primes up to sqrt(n)
- Memoization using segmented sieve idea with precomputed values
- Fast exponentiation and modular arithmetic
- Preprocessing factorials and their modular inverses

Time Complexity: O(n^(2/3) * log(n)) per query, amortized due to preprocessing.
Space Complexity: O(n^(2/3) + log(n))

Problem:
Given integers n, k, d, compute sum_{i=1}^n f(i^k, d), where f(n, d) is the number of leaves in the divisor tree T_{n,d}.
The divisor tree T_{n,d} is built recursively: each node at layer i has children marked with all proper divisors of its value.
*/

#include <algorithm>
#include <bitset>
#include <cmath>
#include <iostream>

using namespace std;
#define il inline
#define ll long long
const int N = 3e6 + 1e5 + 5, M = 3.2e4, K = 35, Mod = 1e9 + 7;
int T, S, n, k, d, cnt, tot;
int p[M], id1[M], id2[M], g[M << 1], val[M << 1];
ll fac[N], inv[N], f[K];
bitset<M> isp;

il int mod(int x, int p) { return x - x / p * p; }

il ll C(int n, int m) { return fac[n] * inv[m] % Mod * inv[n - m] % Mod; }

il int get(int v) { return v <= S ? id1[v] : id2[n / v]; }

il void Euler(int S) {
  for (int i = 2; i <= S; i++) {
    if (!isp[i])
      p[++cnt] = i;
    for (int j = 1, P; (P = p[j]) <= S / i; j++) {
      isp[i * P] = 1;
      if (!mod(i, P))
        break;
    }
  }
  return;
}

il ll QuickPow(ll a, int b = Mod - 2) {
  ll res = 1;
  while (b) {
    if (b & 1)
      res = res * a % Mod;
    a = a * a % Mod;
    b >>= 1;
  }
  return res;
}

il void Init() {
  Euler(31622); // Sieve primes up to √n for large n
  int N = 3e6 + 1e5;
  fac[0] = 1;
  for (int i = 1; i <= N; i++)
    fac[i] = fac[i - 1] * i % Mod;
  inv[N] = QuickPow(fac[N]); // Precompute modular inverse of factorial
  for (int i = N - 1; ~i; i--)
    inv[i] = inv[i + 1] * (i + 1) % Mod;
  return;
}

il ll SumF(int n, int b) {
  int id = get(n); // Get segment index based on n/v
  ll res = (g[id] - b) * f[1] % Mod; // Base term from segmented sieve values

  // Loop through primes to build sum recursively
  for (int i = b + 1, P = p[i], pk = P; i <= cnt && P <= n / P;
       pk = P = p[++i]) {
    for (int j = 1; pk <= n / P; j++, pk *= P) {
      res = (res + f[j] * SumF(n / pk, i) + f[j + 1]) % Mod; // Recurse with powers of prime
    }
  }
  return res;
}

il void Build() {
  cin >> n >> k >> d;
  int l = __lg(n); // Calculate log2(n)
  // Compute C(k*i + d, d) for all i up to l (for multinomial coefficients use in expansion)
  for (int i = 1, p = k; i <= l; i++, p += k)
    f[i] = C(p + d, d);

  S = sqrt(n), tot = 0;
  // Segment the values of n/i to avoid recomputation
  for (int l = 1, r, v; l <= n; l = r + 1) {
    r = n / (v = n / l);
    if (v <= S)
      id1[v] = ++tot;
    else
      id2[n / v] = ++tot;
    val[tot] = v, g[tot] = v - 1; // Initialize sieve array values
  }

  // Sieve to compute prefix sums of g in segmented manner
  for (int j = 1, P = 2; j <= cnt && P <= S; P = p[++j]) {
    for (int i = 1, v; i <= tot && P <= (v = val[i] / P); i++)
      g[i] -= g[get(v)] - j + 1;
  }

  cout << (SumF(n, 0) + 1) % Mod << "\n"; // Add 1 for base case
  return;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  Init(); // Preprocess required data structures once
  cin >> T;
  while (T--)
    Build();
  return 0;
}


// https://github.com/VaHiX/codeForces/