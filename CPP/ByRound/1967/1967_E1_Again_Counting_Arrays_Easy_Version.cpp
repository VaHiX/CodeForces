// Problem: CF 1967 E1 - Again Counting Arrays (Easy Version)
// https://codeforces.com/contest/1967/problem/E1

/*
 * Purpose: This code solves the problem of counting valid arrays `a` of length `n` 
 *          such that there exists a non-negative continuous array `b` starting with 
 *          `b0` and satisfying `a[i] != b[i]` for all i.
 * 
 * Algorithm:
 * - The solution uses dynamic programming with inclusion-exclusion principle.
 * - It calculates forbidden configurations where no valid continuous `b` can be constructed.
 * - The key insight is to model transitions in the continuous array using the constraint that |b[i] - b[i-1]| = 1.
 * - The result is computed modulo 998244353.
 * 
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 * 
 * Techniques:
 * - Modular arithmetic
 * - Fast exponentiation
 * - Polynomial convolution using FFT-like methods (in this case simplified)
 * - Preprocessing factorials and inverse factorials
 * 
 * Input:
 * - t: number of test cases
 * - For each test case: n, m, b0
 * 
 * Output:
 * - Number of valid arrays `a` modulo 998244353
 */
#include <algorithm>
#include <iostream>
#include <random>

using ull = unsigned long long;
using ll = long long;
const int Mod = 998244353;
void add(int &x, int y) {
  if ((x += y) >= Mod)
    x -= Mod;
}
void sub(int &x, int y) {
  if ((x -= y) < 0)
    x += Mod;
}
int norm(int x) { return x >= Mod ? x - Mod : x; }
int reduce(int x) { return x < 0 ? x + Mod : x; }
int mpow(int x, int y) {
  int ret = 1;
  for (; y; y >>= 1, x = (ull)x * x % Mod)
    if (y & 1)
      ret = (ull)ret * x % Mod;
  return ret;
}
void fam(int &x, int y, int z) { x = (x + (ull)y * z) % Mod; }
const int _ = 200015;
int fac[_], ifac[_];
void pre(int N) {
  fac[0] = 1;
  for (int i = 1; i <= N; ++i)
    fac[i] = (ull)fac[i - 1] * i % Mod;
  ifac[N] = mpow(fac[N], Mod - 2);
  for (int i = N; i; --i)
    ifac[i - 1] = (ull)ifac[i] * i % Mod;
}
int coeff[_ * 2], coeff2[_ * 2];
int tmp[_ * 2];
int solve(int N, int M, int b0) {
  if (b0 >= M || b0 >= N)
    return mpow(M, N);
  if (M == 1) {
    if (b0 == 0)
      return 0;
    return 1;
  }
  int *p = coeff + _;
  std::fill(p - N, p + N + 1, 0);
  {
    int per = 2 * (M + 1);
    for (int i = -b0 + per; i <= N; i += per)
      p[i] = 1;
    for (int i = -b0; i >= -N; i -= per)
      p[i] = 1;
    for (int i = -2 - b0; i >= -N; i -= per)
      p[i] = Mod - 1;
    for (int i = -2 - b0 + per; i <= N; i += per)
      p[i] = Mod - 1;
  }
  int fact = 1;
  if ((N - b0 - 1) & 1)
    fact = M;
  std::cerr << "fact " << M << '\n';
  int res = 0;
  int K = (N - b0 - 1) / 2;
  int *q = coeff2 + _;
  std::fill(q - N - 5, q + N + 6, 0);
  auto addBinom = [&](int o, int c) {
    for (int i = 0; i <= o; ++i) {
      fam(q[i * 2 - o], (ull)fac[o] * ifac[i] % Mod * ifac[o - i] % Mod, c);
    }
  };
  addBinom(K * 2 + 2 + b0, mpow(M - 1, K + 1));
  addBinom(b0, Mod - mpow(M, K * 2 + 2));
  int nv = mpow(M - 1, Mod - 2);
  for (int i = -N - 1; i <= N + 1; ++i)
    q[i] = (ull)q[i] * nv % Mod;
  int val = M * (ull)M % Mod * nv % Mod;
  val = reduce(2 - val);
  for (int i = -N - 1; i <= N + 1; ++i) {
    fam(q[i], q[i - 2], Mod - val);
    sub(q[i], q[i - 4]);
  }
  q = coeff2 + _ - 2;
  for (int i = -N; i <= N + 2; ++i) {
    fam(res, q[i], p[i]);
  }
  res = res * (ull)fact % Mod;
  int ret = reduce(mpow(M, N) - res);
  return ret;
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  pre(200005);
  int T;
  std::cin >> T;
  while (T--) {
    int N, M, b0;
    std::cin >> N >> M >> b0;
    std::cout << solve(N, M, b0) << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/