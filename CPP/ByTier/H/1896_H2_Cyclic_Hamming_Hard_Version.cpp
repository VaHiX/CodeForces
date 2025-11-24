/*
 * Problem: 1896 H2 - Cyclic Hamming (Hard Version)
 * https://codeforces.com/contest/1896/problem/H2
 *
 * Summary:
 * This implementation computes a cyclic Hamming-like convolution between two
 * binary strings using divide-and-conquer convolution (with NTT for large
 * blocks and naive multiplication for small blocks). The problem reduces to
 * evaluating many convolutions in a structured recursive manner; the code
 * performs pairwise polynomial products and pointwise products, combining
 * results across levels to produce the final frequency arrays F and G and
 * then computes the sum of matched coefficients.
 *
 * Complexity:
 * - Let n = 2^{k+1} be the string length. The algorithm performs O(n log n)
 *   total work of polynomial multiplies (using NTT for large sizes), plus
 *   small-constant overhead per level. NTT operations incur O(n log n)
 *   complexity when used.
 *
 * Space:
 * - Arrays sized up to n_MAX storing polynomials and buffers for NTT.
 *
 * Key parts:
 * - Number theoretic transform (NTT) with iterative in-place implementation
 * - multiply(): chooses naive convolution for small sizes and NTT for large
 * - Solve(): recursively divides the input string to construct structured
 *   polynomial products and dot-products used to count matches at shifts
 * - Main: runs Solve for both strings and computes the final dot product
 *
 */

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define For_down(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;

// Maximum size (power-of-two buffer) and modulus (NTT-friendly prime)
constexpr int n_MAX = ((1 << 13) | 5), mod = 998244353;

// Modular arithmetic helpers
inline int norm(const int x) { return ((x >= mod) ? (x - mod) : x); }
inline void add(int &x, const int y) { (((x += y) >= mod) && (x -= mod)); }
inline void sub(int &x, const int y) { (((x -= y) < 0) && (x += mod)); }
inline int mul(const int x, const int y) { return (((long long)x * y) % mod); }
// fast exponentiation modulo mod
inline int pow(int x, int z) {
  int y = 1;
  while (z) {
    if (z & 1)
      y = mul(y, x);
    x = mul(x, x), z >>= 1;
  }
  return y;
}
inline int inv(const int x) { return pow(x, mod - 2); }
int n, k;
char s[n_MAX], t[n_MAX];
int F[n_MAX], G[n_MAX];
vector<vector<int>> P[n_MAX], Q[n_MAX];

// pointwise multiplication (Hadamard product) of two equal-length
// vectors a and b; result written to c and returned.
vector<int> dot(const vector<int> &a, const vector<int> &b, vector<int> &c) {
  const int n = (a.size() - 1);
  c = (vector<int>(n + 1));
  For(i, 0, n) c[i] = mul(a[i], b[i]);
  return c;
}
int rev[n_MAX], pw[n_MAX];

// Iterative Number Theoretic Transform (in-place). If flag==false,
// computes the forward NTT; if flag==true, computes the inverse NTT
// and scales by 1/n. This implementation assumes n is a power of two
// and uses primitive root 3 for mod=998244353.
void NTT(vector<int> &a, const bool flag = false) {
  const int n = a.size();
  // bit-reversal permutation precomputation
  For(i, 0, n - 1) {
    rev[i] = (rev[i >> 1] >> 1);
    if (i & 1)
      rev[i] |= (n >> 1);
  }
  For(i, 0, n - 1) if (i < rev[i]) swap(a[i], a[rev[i]]);
  // Cooley-Tukey iterative NTT
  for (int m = 1; m <= (n >> 1); m <<= 1) {
    // compute root of unity (forward or inverse depending on flag)
    const int w = (flag ? pow(3, (mod - 1) - ((mod - 1) / (m << 1)))
                        : pow(3, (mod - 1) / (m << 1)));
    pw[0] = 1;
    For(i, 1, m - 1) pw[i] = mul(pw[i - 1], w);
    for (int i = 0; i != n; i += (m << 1))
      For(j, i, i | (m - 1)) {
        int &x = a[j], &y = a[j | m];
        const int z = mul(y, pw[j & (m - 1)]);
        // butterfly: x' = x + z, y' = x - z (mod mod)
        y = norm(x + (mod - z)), add(x, z);
      }
  }
  if (flag) {
    // scale by inverse of n for inverse transform
    const int w = inv(n);
    For(i, 0, n - 1) a[i] = mul(a[i], w);
  }
}
unsigned long long tmp[n_MAX];

// Multiply two polynomials a and b. For small degrees (n <= 64) uses
// safe 128-bit-accumulation in tmp and naive O(n^2). For larger sizes
// it uses NTT: resize to 2n, forward NTT, pointwise multiply, inverse NTT.
// The function returns polynomial c of degree up to 2n.
vector<int> multiply(vector<int> &a, vector<int> &b, vector<int> &c) {
  const int n = (a.size() - 1);
  if (n <= 64) {
    c = (vector<int>(n << 1 | 1));
    For(i, 0, n) For(j, 0, n) {
      tmp[i + j] += ((unsigned long long)a[i] * b[j]);
      if ((i & 15) == 15)
        tmp[i + j] %= mod;
    }
    For(i, 0, n << 1) c[i] = (tmp[i] % mod), tmp[i] = 0;
    return c;
  } else {
    // special handling of c[0] using a[0]*b[0] to avoid overwriting
    const int mem = mul(a[0], b[0]);
    a.resize(n << 1), NTT(a);
    b.resize(n << 1), NTT(b);
    c = (vector<int>(n << 1));
    For(i, 0, (n << 1) - 1) c[i] = mul(a[i], b[i]);
    NTT(c, true);
    // restore c[0] and append last coefficient: this balances how sizes
    // are encoded in this problem-specific representation
    c.push_back(norm(c[0] + (mod - mem)));
    c[0] = mem;
    return c;
  }
}
void Solve(const char s[], int F[]) {
  // Build base-level polynomials for each position u from string s.
  // Each P[0][u] is a small polynomial encoding whether s[u] equals '0'/'1'.
  P[0].resize(n);
  For(u, 0, n - 1) P[0][u] = {s[u] != '1', s[u] != '0'};

  // Iteratively combine blocks: at level i we have block-size m = n>>i.
  // We compute two types of combinations for each segment S and position u:
  // - Q[S<<1|1][u] stores pointwise (dot) products of pairs of polynomials
  // - Q[S<<1][u] stores full polynomial multiplications of the pairs
  // After computing Q, we swap P and Q to move to next level.
  For(i, 0, k) {
    const int m = (n >> i);
    // prepare containers for next level
    For(S, 0, (2 << i) - 1) Q[S].resize(m >> 1);
    // compute pointwise products for odd child index
    For(S, 0, (1 << i) - 1) For(u, 0, (m >> 1) - 1)
        dot(P[S][u], P[S][u | (m >> 1)], Q[S << 1 | 1][u]);
    // compute convolution products for even child index
    For(S, 0, (1 << i) - 1) For(u, 0, (m >> 1) - 1)
        multiply(P[S][u], P[S][u | (m >> 1)], Q[S << 1][u]);
    // move to next level
    For(S, 0, (2 << i) - 1) swap(P[S], Q[S]);
  }

  // Extract the central coefficient for each shift S to build F[S]
  For(S, 0, n - 2) F[S] = P[S][0][P[S][0].size() >> 1];
}
int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  // read k and compute n = 2^{k+1}
  cin >> k, n = (2 << k), cin >> s >> t;

  // Solve builds frequency arrays F and G for all cyclic shifts
  Solve(s, F);
  Solve(t, G);

  // Inclusion-exclusion style adjustment across bit-dimensions
  For(i, 0, k) For(S, 0, n - 1) if (!(S & (1 << i))) sub(F[S], F[S | (1 << i)]);

  // Final convolution: sum over shifts of F[S] * G[n-S-1]
  int ans = 0;
  For(S, 0, n - 1) add(ans, mul(F[S], G[n - S - 1]));
  cout << ans << '\n';
  return 0;
}

// https://github.com/VaHiX/CodeForces/