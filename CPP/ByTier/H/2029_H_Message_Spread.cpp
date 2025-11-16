// Problem: CF 2029 H - Message Spread
// https://codeforces.com/contest/2029/problem/H

/*
 * Overview
 * --------
 * This is an implementation of a solution for "Message Spread" using subset
 * DP together with the Fast Walsh-Hadamard Transform (FWT) to accelerate
 * subset convolutions. The code computes a modular value (under Mod =
 * 998244353) that corresponds to the required probabilistic/counting
 * expression derived from inclusion-exclusion over subsets.
 *
 * Key ideas:
 * - Represent states as bitmasks over n vertices (we reduce n by 1 in the
 *   implementation so masks are over n-1 vertices for convenience).
 * - Precompute multiplicative contributions P and inverse contributions iP for
 *   each subset using the per-edge probabilities.
 * - Use FWT/IFWT to perform fast subset convolutions required by the DP.
 * - Maintain arrays f, g, h, th, tp to gather intermediate DP values and
 *   assemble the final answer with inclusion-exclusion.
 *
 * Complexity
 * - Time: roughly O(n * 2^n) operations (dominant cost: FWT/IFWT transforms)
 * - Space: O(2^n) for the major arrays; arrays have been sized for n up to 21
 *
 * Notes / implementation details
 * - Mod = 998244353 is used for all modular arithmetic.
 * - The implementation uses custom fast I/O (read/write) for integers.
 * - The code intentionally uses bitmasks and low-level loops for speed.
 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <time.h>

// Type aliases
// NOTE: 'll' is defined as int intentionally (fits within problem limits and
// mirrors original code choices). For modular arithmetic we keep values in 32
// bit signed ints but use long long when multiplication with larger ranges is
// needed (explicit casts are used in-place below as required).
typedef int ll;
typedef long double ld;
typedef unsigned long long ull;

// Convenience macros for loops and pairs
#define pii pair<ll, ll>
#define rep(i, a, b) for (ll i = (a); i <= (b); ++i)
#define per(i, a, b) for (ll i = (a); i >= (b); --i)

using namespace std;

// Fast integer input / output helpers
// These are tuned for speed in tight loops on large inputs.
bool Mbe;
ll read() {
  ll x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}

// Write integer to stdout (recursive)
void write(ll x) {
  if (x < 0)
    putchar('-'), x = -x;
  if (x > 9)
    write(x / 10);
  putchar(x % 10 + '0');
}
const ll Mod = 998244353; // prime modulus used throughout

// Problem parameters and helper matrices
ll n, m;

// w: multiplicative (1 - p) values between vertices
// iw: modular inverses of those values (for dividing out contributions)
// sized for up to 21 vertices (safety margin)
ll w[22][22], iw[22][22];

// Main arrays (sized for masks up to 2^21)
// P: multiplicative product for a subset
// iP: product of inverses for subset (used for divisions / modular inverses)
// f, g, h, tmp: DP and temporary arrays used during transforms
// pc: popcount precomputation
ll P[(1 << 21) + 9], iP[(1 << 21) + 9], f[(1 << 20) + 9], g[(1 << 20) + 9],
    h[(1 << 20) + 9], tmp[(1 << 20) + 9], pc[(1 << 21) + 9];

// th, tp: intermediate 2D arrays used to accumulate convolution results per
// subset size. coef1: correction coefficients used in the final inclusion step.
// Note: dimensions are chosen to avoid dynamic allocation in this performance
// sensitive code.
ll th[22][(1 << 20) + 9], tp[22][(1 << 20) + 9], coef1[(1 << 20) + 9];

// Fast modular exponentiation
ll pw(ll x, ll p) {
  ll res = 1;
  while (p) {
    if (p & 1)
      res = 1ll * res * x % Mod;
    x = 1ll * x * x % Mod, p >>= 1;
  }
  return res;
}

// Safe modular add / subtract helpers (ensure result in [0, Mod))
void Add(ll &x, ll y) {
  x += y;
  if (x >= Mod)
    x -= Mod;
}
void Dec(ll &x, ll y) {
  x -= y;
  if (x < 0)
    x += Mod;
}

// Fast Walsh-Hadamard Transform (FWHT variant for subset convolution)
// This implementation performs the in-place transform used to convert
// subsetwise multiplication into pointwise multiplication across masks.
// The chosen variant adds the lower half into the upper half; the inverse
// transform subtracts correspondingly.
void FWT(ll *f, ll n) {
  for (ll i = 1; i < (1 << n); i <<= 1) {
    for (ll j = 0; j < (1 << n); j += (i << 1)) {
      rep(k, 0, i - 1) Add(f[j + k + i], f[j + k]);
    }
  }
}

// Inverse FWT for the same transform implemented above (uses subtraction)
void IFWT(ll *f, ll n) {
  for (ll i = 1; i < (1 << n); i <<= 1) {
    for (ll j = 0; j < (1 << n); j += (i << 1)) {
      rep(k, 0, i - 1) Dec(f[j + k + i], f[j + k]);
    }
  }
}
bool Med;
int main() {
  cerr << fabs(&Med - &Mbe) / 1048576.0 << "MB\n";
  n = read(), m = read();
  rep(i, 0, n - 1) { rep(j, 0, n - 1) w[i][j] = iw[i][j] = 1; }
  while (m--) {
    ll x = read() - 1, y = read() - 1, p = read(), q = read();
    p = 1ll * p * pw(q, Mod - 2) % Mod;
    w[x][y] = w[y][x] = (1 - p + Mod) % Mod;
    iw[x][y] = iw[y][x] = pw(1 - p + Mod, Mod - 2);
  }
  // Precompute popcounts for masks up to (1<<n)-1
  rep(i, 1, (1 << n) - 1) pc[i] = pc[i ^ (i & (-i))] + 1;
  P[0] = 1, iP[0] = 1;
  rep(i, 1, (1 << n) - 1) {
    P[i] = P[i ^ (i & (-i))], iP[i] = iP[i ^ (i & (-i))];
    ll x = __lg(i & (-i));
    rep(j, 0, n - 1) {
      if (((i >> j) & 1))
        P[i] = 1ll * P[i] * w[x][j] % Mod, iP[i] = 1ll * iP[i] * iw[x][j] % Mod;
    }
  }
  // Build array g for odd masks (used later in inclusion-exclusion)
  rep(i, 1, (1 << n) - 2) {
    if (!(i & 1))
      continue;
    ll pb = 1ll * P[(1 << n) - 1] * iP[i] % Mod * iP[((1 << n) - 1) ^ i] % Mod;
    g[i >> 1] = pw(1 - pb + Mod, Mod - 2);
  }
  n--;
  // Precompute coef1: correction coefficients for subsets on reduced n
  rep(i, 0, (1 << n) - 1) coef1[i] = iP[(((1 << n) - 1) ^ i) << 1];
  f[0] = 1;
  // For each subset size i we prepare tp[i] as the FWT of contributions from
  // subsets of size i (used to accumulate convolution results by size)
  rep(i, 0, n) {
    rep(j, 0, (1 << n) - 1) {
      if (pc[j] == i)
        tp[i][j] = P[(((1 << n) - 1) ^ j) << 1 | 1];
    }
    FWT(tp[i], n);
  }
  rep(i, 0, n - 1) {
    memset(tmp, 0, sizeof(tmp));
    rep(j, 0, (1 << n) - 1) {
      if (pc[j] == i) {
        tmp[j] = 1ll * iP[j << 1 | 1] * f[j] % Mod * g[j] % Mod;
        h[j] = (h[j] + 1ll * tmp[j] * P[(1 << (n + 1)) - 1]) % Mod;
      }
    }
    FWT(tmp, n);
    rep(j, 1, n - i) {
      rep(k, 0, (1 << n) - 1) {
        th[i + j][k] = (th[i + j][k] + 1ll * tmp[k] * tp[j][k]) % Mod;
      }
    }
    IFWT(th[i + 1], n);
    rep(j, 0, (1 << n) - 1) {
      if (pc[j] == i + 1)
        h[j] = th[i + 1][j];
    }
    memcpy(tmp, h, sizeof(h));
    rep(j, 0, (1 << n) - 1) tmp[j] = 1ll * tmp[j] * coef1[j] % Mod;
    rep(j, 0, n - 1) {
      per(k, (1 << n) - 1, 0) {
        if ((k >> j) & 1)
          Dec(tmp[k], tmp[k ^ (1 << j)]);
      }
    }
    rep(j, 0, (1 << n) - 1) {
      if (pc[j] == i + 1)
        f[j] = tmp[j];
    }
  }
  // Aggregate final answer using inclusion-exclusion style sum over masks
  ll ans = 0;
  rep(i, 0, (1 << n) - 1) ans = (ans + 1ll * f[i] * g[i]) % Mod;
  write(ans), putchar('\n');
  cerr << "\n" << clock() * 1.0 / CLOCKS_PER_SEC * 1000 << "ms\n";
  return 0;
}

// https://github.com/VaHiX/CodeForces/