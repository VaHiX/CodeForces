// Problem: CF 1864 H - Asterism Stream
// https://codeforces.com/contest/1864/problem/H

/*
 * Code Purpose: Solve the expected number of moves to reach or exceed a value n,
 *               where each move either increments x by 1 or multiplies x by 2,
 *               both with equal probability (1/2).
 *
 * Algorithm/Techniques:
 *   - Dynamic Programming with Matrix Exponentiation
 *   - Linear Recurrence Modeling
 *   - Fast Matrix Exponentiation for large n (up to 10^18)
 *   - Modular arithmetic and modular inverse for fraction handling
 *
 * Time Complexity: O(log^3(n)) per test case due to matrix multiplication and
 *                  fast exponentiation
 * Space Complexity: O(N^2) where N = 60, which is constant, used for matrix storage
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;
using ui = unsigned int;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdi = pair<double, int>;
using ull = unsigned long long;
using vint = vector<int>;
using vll = vector<ll>;
#define ppc(x) __builtin_popcount(x)
#define clz(x) __builtin_clz(x)
bool Mbe;
mt19937 rnd(20060130);
int rd(int l, int r) { return rnd() % (r - l + 1) + l; }
constexpr int mod = 998244353;
constexpr int iv = mod + 1 >> 1; // modular inverse of 2
void addt(int &x, int y) { x += y, x >= mod && (x -= mod); }
int add(int x, int y) { return x += y, x >= mod && (x -= mod), x; }
int ksm(int a, int b) {
  int s = 1;
  while (b) {
    if (b & 1)
      s = 1ll * s * a % mod;
    a = 1ll * a * a % mod, b >>= 1;
  }
  return s;
}
char buf[1 << 20], *p1 = buf, *p2 = buf;
#define getc()                                                                 \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2)     \
       ? EOF                                                                   \
       : *p1++)
inline int read() {
  int x = 0;
  char s = getc();
  while (!isdigit(s))
    s = getc();
  while (isdigit(s))
    x = x * 10 + s - '0', s = getc();
  return x;
}
#define putc(x) putchar(x)
inline void print(ui x) {
  if (x >= 10)
    print(x / 10);
  putc(x % 10 + '0');
}
constexpr int N = 60;
struct mat {            // Matrix class for matrix operations
  ull a[N + 1][N + 1];  // Matrix elements
  void init() { memset(a, 0, sizeof(a)); }  // Initialize to zero
  mat operator*(const mat &x) const {
    mat y;
    y.init();
    for (int i = 0; i <= N; i++) {
      for (int k = 0; k <= i; k++) {
        for (int j = 0; j <= k; j++)
          y.a[i][j] += a[i][k] * x.a[k][j];  // Matrix multiplication
        if ((k & 15) == 15 || k == i) {        // Modular reduction every 16 iterations
          for (int j = 0; j <= i; j++)
            y.a[i][j] %= mod;
        }
      }
    }
    return y;
  }
  mat operator/(const mat &x) const {
    mat y;
    y.init();
    for (int k = 0; k <= N; k++) {
      for (int j = 0; j <= k; j++)
        y.a[0][j] += a[0][k] * x.a[k][j];  // Special multiplication for vector result
      if ((k & 15) == 15 || k == N) {        // Modular reduction every 16 iterations
        for (int j = 0; j <= N; j++)
          y.a[0][j] %= mod;
      }
    }
    return y;
  }
} f[N], g[N], h[N], I;
ll n;
void mian() {
  cin >> n;
  mat ans = I / h[__lg(n)];  // Use matrix exponentiation for final result
  for (int i = __lg(n) - 1; ~i; i--) {
    if (n >> i & 1)
      ans = ans / h[i];  // If bit is set, apply transformation
  }
  cout << (ans.a[0][0] + mod - 2) % mod << "\n";  // Adjust by adding -2 mod
}
bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (int i = 0; i < N; i++) {
    f[i].a[0][0] = 1;
    f[i].a[1][0] = 1;
    for (int j = 0; j <= i; j++) {
      int coef = iv;
      for (int k = j; k < i; k++) {
        f[i].a[k + 1][j + 1] = coef;
        coef = 1ll * coef * iv % mod;  // Update coefficient using modular inverse
      }
      f[i].a[i + 1][j + 1] = coef;
    }
    for (int j = i + 1; j < N; j++) {
      f[i].a[j + 1][j + 1] = 1;  // Identity for remaining elements
    }
  }
  h[0] = g[0] = f[0];  // Initialize base cases
  for (int i = 1; i < N; i++) {
    h[i] = g[i - 1] * f[i];  // Compute h[i] using previously computed values
    g[i] = h[i] * g[i - 1];
  }
  for (int i = 1; i <= N; i++)
    I.a[0][i] = 2;  // Initialize identity matrix coefficients
  int T = 1;
  cin >> T;
  while (T--)
    mian();
  fprintf(stderr, "%d ms\n", int(1e3 * clock() / CLOCKS_PER_SEC));
  return 0;
}


// https://github.com/VaHiX/CodeForces/