/*
 * Problem URL : https://codeforces.com/contest/1938/problem/M
 * Submit Date : 2025-09-07
 */

#include <cstdio>
#include <iostream>
const int N = 300000;
const int M = 1048576;
const int K = 20;
const int g = 3;
const int mod = 998244353;
using namespace std;
int read() {
  char c = 0;
  int sum = 0;
  while (c < '0' || c > '9')
    c = getchar();
  while ('0' <= c && c <= '9') {
    sum = sum * 10 + c - '0';
    c = getchar();
  }
  return sum;
}
int fast_pow(int a, int b) {
  int res = 1, mul = a;
  while (b) {
    if (b & 1)
      res = 1ll * res * mul % mod;
    mul = 1ll * mul * mul % mod;
    b >>= 1;
  }
  return res;
}
int MD(int x) { return x >= mod ? x - mod : x; }
int MD2(int x) { return x < 0 ? x + mod : x; }
void Adder(int &x, int d) {
  x = x + d >= mod ? x + d - mod : x + d;
  return;
}
void Adder2(int &x, int d) {
  x = x + d < 0 ? x + d + mod : x + d;
  return;
}
int T, n, num[M + 1], length, dp[N + 1], F[N + 1], G[N + 1], H[N + 1],
    DP[N + 1], DP2[N + 1], DP3[N + 1], delta[N + 1], delta2[N + 1], rev[M + 1],
    A[M + 1], B[M + 1], C[M + 1], wn[K + 1][M + 1], wn2[K + 1][M + 1];
long long S[N + 1];
void NTT(int limit, int *s, int type) {
  int s1, s2;
  for (int i = 1; i < limit; ++i)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? limit >> 1 : 0);
  for (int i = 0; i < limit; ++i)
    if (rev[i] > i)
      swap(s[i], s[rev[i]]);
  if (type == 1) {
    for (int i = 2; i <= limit; i <<= 1)
      for (int j = 0; j + i - 1 < limit; j += i)
        for (int k = j; k < j + (i >> 1); ++k) {
          s1 = s[k];
          s2 = 1ll * s[k + (i >> 1)] * wn[num[i]][k - j] % mod;
          s[k] = MD(s1 + s2), s[k + (i >> 1)] = MD2(s1 - s2);
        }
  } else {
    for (int i = 2; i <= limit; i <<= 1)
      for (int j = 0; j + i - 1 < limit; j += i)
        for (int k = j; k < j + (i >> 1); ++k) {
          s1 = s[k];
          s2 = 1ll * s[k + (i >> 1)] * wn2[num[i]][k - j] % mod;
          s[k] = MD(s1 + s2), s[k + (i >> 1)] = MD2(s1 - s2);
        }
    s1 = fast_pow(limit, mod - 2);
    for (int i = 0; i <= limit; ++i)
      s[i] = 1ll * s[i] * s1 % mod;
  }
  return;
}
void get_inv(int len, int *s, int *t) {
  if (len == 1) {
    t[0] = fast_pow(s[0], mod - 2);
    return;
  }
  int limit = 1;
  while (limit <= (len << 1))
    limit <<= 1;
  int s1[limit + 1], s2[limit + 1];
  get_inv((len + 1) >> 1, s, s1);
  for (int i = 0; i <= limit; ++i) {
    s1[i] = (i < ((len + 1) >> 1)) ? s1[i] : 0;
    s2[i] = (i < len) ? s[i] : 0;
  }
  NTT(limit, s1, 1);
  NTT(limit, s2, 1);
  for (int i = 0; i <= limit; ++i)
    s1[i] = MD2(2ll * s1[i] % mod - 1ll * s1[i] * s1[i] % mod * s2[i] % mod);
  NTT(limit, s1, -1);
  for (int i = 0; i < len; ++i)
    t[i] = s1[i];
  return;
}
int main() {
  int limit = 1;
  for (int i = 2, w; i <= M; i <<= 1) {
    num[i] = ++length;
    w = fast_pow(g, (mod - 1) / i);
    for (int j = 0, res = 1; j < (i >> 1); ++j, res = 1ll * res * w % mod)
      wn[num[i]][j] = res;
    w = fast_pow(g, (mod - 1) / i * (i - 1));
    for (int j = 0, res = 1; j < (i >> 1); ++j, res = 1ll * res * w % mod)
      wn2[num[i]][j] = res;
  }
  while (limit <= (N << 1))
    limit <<= 1;
  S[1] = 1;
  for (int i = 2; i <= N; ++i)
    S[i] = S[i - 2] + i;
  dp[0] = 1;
  for (int i = 1; S[i] <= N; ++i) {
    for (int j = i; j <= N; ++j)
      Adder(dp[j], dp[j - i]);
    if (!(i & 1)) {
      for (int j = S[i] + (i >> 1); j <= N; ++j) {
        if ((i >> 1) & 1)
          Adder(F[j], dp[j - S[i] - (i >> 1)]);
        else
          Adder2(F[j], -dp[j - S[i] - (i >> 1)]);
      }
    } else {
      for (int j = S[i]; j <= N; ++j) {
        if (((i + 1) >> 1) & 1)
          Adder(G[j], dp[j - S[i]]);
        else
          Adder2(G[j], -dp[j - S[i]]);
      }
      for (int j = S[i] + (i >> 1); j <= N; ++j) {
        if (((i + 1) >> 1) & 1)
          Adder(H[j], dp[j - S[i] - (i >> 1)]);
        else
          Adder2(H[j], -dp[j - S[i] - (i >> 1)]);
      }
    }
  }
  delta[0] = 1;
  for (int i = 1; i <= N; ++i)
    delta[i] = MD2(-F[i]);
  get_inv(N + 1, delta, delta2);
  for (int i = 1; i <= N; ++i)
    DP[i] = delta2[i];
  for (int i = 0; i <= N; ++i) {
    A[i] = delta2[i];
    B[i] = G[i], C[i] = H[i];
  }
  NTT(limit, A, 1);
  NTT(limit, B, 1);
  NTT(limit, C, 1);
  for (int i = 0; i <= limit; ++i) {
    B[i] = 1ll * A[i] * B[i] % mod;
    C[i] = 1ll * A[i] * C[i] % mod;
  }
  NTT(limit, B, -1);
  NTT(limit, C, -1);
  for (int i = 1; i <= N; ++i) {
    DP2[i] = B[i];
    DP3[i] = C[i];
  }
  T = read();
  while (T--) {
    n = read();
    cout << MD2(MD(MD(2ll * DP[n] % mod + DP2[n]) + DP3[n]) - 1) << '\n';
  }
  return 0;
}
