// Problem: CF 1936 E - Yet Yet Another Permutation Problem
// https://codeforces.com/contest/1936/problem/E

/*
Algorithm: FFT-based convolution and divide and conquer approach to count permutations satisfying given constraints.

Time Complexity: O(n log^2 n) per test case due to FFT and recursive calls.
Space Complexity: O(n) for storing arrays and auxiliary data structures.

Techniques:
- Fast Fourier Transform (FFT) for efficient polynomial multiplication
- Divide and conquer with recursive splitting and convolution
- Modular arithmetic and precomputed factorials for combinatorics
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
const int N = 1 << 19, P = 998244353;
int T, n, p[N], a[N], m, f[N], fac[N], inv[N], ans;
int lim, w[N], A[N], B[N], C[N];

// Fast exponentiation
int ksm(int x, int y) {
  int res = 1;
  for (; y; y >>= 1, x = 1ll * x * x % P)
    if (y & 1)
      res = 1ll * res * x % P;
  return res;
}

// Precompute factorials and inverse factorials
void init() {
  fac[0] = fac[1] = inv[0] = inv[1] = 1;
  for (int i = 2; i < N; ++i)
    fac[i] = 1ll * fac[i - 1] * i % P,
    inv[i] = 1ll * (P - P / i) * inv[P % i] % P;
  for (int i = 2; i < N; ++i)
    inv[i] = 1ll * inv[i - 1] * inv[i] % P;
  // Precompute roots of unity for FFT
  for (int mid = 1, j, wn; mid < N; mid <<= 1)
    for (w[j = mid] = 1, wn = ksm(3, (P - 1) / (mid << 1)), ++j; j < mid << 1;
         ++j)
      w[j] = 1ll * w[j - 1] * wn % P;
}

// Compute next power of 2 >= n
void up(int n) {
  lim = 1;
  while (lim <= n)
    lim <<= 1;
}

// Reset array
void cle(int *A) {
  for (int i = 0; i < lim; ++i)
    A[i] = 0;
}

// Modular addition
inline int md(int x) { return x >= P ? x - P : x; }

// Fast Fourier Transform
void DFT(int *A) {
  for (int mid = lim >> 1, R, j, k, *W, *a, *b, Y; mid; mid >>= 1)
    for (R = mid << 1, j = 0; j < lim; j += R)
      for (k = 0, W = w + mid, a = A + j, b = a + mid; k < mid;
           ++k, ++a, ++b, ++W)
        *b = 1ll * (*a + P - (Y = *b)) * *W % P, *a = md(*a + Y);
}

// Inverse Fast Fourier Transform
void IDFT(int *A) {
  for (int mid = 1, R, j, k, *W, *a, *b, Y; mid < lim; mid <<= 1)
    for (R = mid << 1, j = 0; j < lim; j += R)
      for (k = 0, W = w + mid, a = A + j, b = a + mid; k < mid;
           ++k, ++a, ++b, ++W)
        Y = 1ll * *b * *W % P, *b = md(*a + P - Y), *a = md(*a + Y);
  reverse(A + 1, A + lim);
  for (int in = ksm(lim, P - 2), i = 0; i < lim; ++i)
    A[i] = 1ll * A[i] * in % P;
}

// Process range [l, r] and update f and answer
void Solve(int l, int r) {
  for (int i = l, s = 0; i <= r; ++i) {
    f[i] = md(f[i] + s);
    f[i] = (f[i] + 1ll * fac[p[i] - 1] % P * i) % P;
    f[i] = 1ll * f[i] * inv[p[i] - i] % P;
    ans = (ans + 1ll * (P - f[i]) * fac[n - i]) % P;
    s = (s + 1ll * (P - f[i]) * fac[p[i] - i]) % P;
  }
}

// Recursive solver using divide and conquer with FFT
void solve(int l, int r) {
  if (l == r) {
    Solve(a[l], a[l + 1] - 1);
    return;
  }
  int mid = l + r >> 1;
  solve(l, mid);
  int L = a[l], R = a[r + 1] - 1, M = a[mid + 1] - 1, t = p[M + 1] - M - 1;
  up(p[R] - p[M + 1] + M - L + M - L);
  cle(A), cle(B), cle(C);
  for (int i = L; i <= M; ++i)
    A[i - L] = P - f[i], B[i - L] = 1ll * i * f[i] % P;
  for (int i = p[M + 1] - M - 1; i <= p[R] - L - 1; ++i)
    C[i - t] = fac[i];
  DFT(A), DFT(B), DFT(C);
  for (int i = 0; i < lim; ++i)
    A[i] = 1ll * A[i] * C[i] % P, B[i] = 1ll * B[i] * C[i] % P;
  IDFT(A), IDFT(B);
  for (int j = M + 1; j <= R; ++j)
    f[j] = (f[j] + 1ll * j * A[p[j] - p[M + 1] + M - L] +
            B[p[j] - p[M + 1] + M - L]) %
           P;
  solve(mid + 1, r);
}

// Parse input and process for current test case
void solve() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &p[i]);
  for (int i = 1; i <= n; ++i)
    p[i] = max(p[i], p[i - 1]), f[i] = 0;
  m = 0, ans = fac[n];
  for (int i = 1; i < n; ++i)
    if (p[i] != p[i - 1])
      a[++m] = i;
  a[m + 1] = n, solve(1, m);
  printf("%d\n", ans);
}

// Main function
int main() {
  init();
  scanf("%d", &T);
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/