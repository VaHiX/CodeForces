/*
 * Problem URL : https://codeforces.com/contest/2027/problem/E2
 * Submit Date : 2025-09-09
 */

#include <stdio.h>
#include <string.h>

#define N 10000
#define B 10000
#define L 30
#define C 32
#define MD 1000000007

int vv[L + 1], ff[L + 1], gg[L + 1];

void init() {
  int i;

  ff[0] = gg[0] = 1;
  for (i = 1; i <= L; i++) {
    vv[i] = i == 1 ? 1 : (long long)vv[i - MD % i] * (MD / i + 1) % MD;
    ff[i] = (long long)ff[i - 1] * i % MD;
    gg[i] = (long long)gg[i - 1] * vv[i] % MD;
  }
}

int choose(int n, int k) {
  return k < 0 || k > n ? 0 : (long long)ff[n] * gg[k] % MD * gg[n - k] % MD;
}

void brute(int a, int b) {
  static int dp[B + 1], used[B + 1], kk[B + 1];
  int c, d;

  for (c = 0; c <= b; c++) {
    memset(used, 0, (b + 1) * sizeof *used);
    for (d = 1; d <= c && d <= a; d++)
      if ((c & d) == d)
        used[dp[c ^ d]] = 1;
    dp[c] = 0;
    while (used[dp[c]])
      dp[c]++;
    kk[c] = c == 0 ? 0 : kk[c & c - 1] + 1;
    if (dp[c] != 0 && dp[c] != kk[c] && dp[c] != kk[c] - 2)
      printf("%d %d %d: expected %d, found %d\n", a, b, c, kk[c], dp[c]);
  }
}

void solve_(int *kk, int l, int a, int b) {
  int h, h_, c, c_, x;

  memset(kk, 0, C * sizeof *kk);
  c_ = 0;
  for (h = l - 1; h >= 0; h--)
    if ((b & 1 << h) != 0) {
      for (c = 0; c <= h; c++)
        kk[c_ + c] = (kk[c_ + c] + choose(h, c)) % MD;
      c_++;
    }
  kk[c_] = (kk[c_] + 1) % MD;
  h_ = l - 1;
  while (h_ > 0 && (a & 1 << h_ - 1) == 0)
    h_--;
  if (b >= 1 << l - 1) {
    c_ = 1;
    for (h = l - 2; h >= h_; h--)
      if ((b & 1 << h) != 0) {
        for (c = c_ % 2; c <= h - h_; c += 2) {
          x = choose(h - h_, c);
          kk[c_ + c] = (kk[c_ + c] - x + MD) % MD,
                  kk[c_ + c - 2] = (kk[c_ + c - 2] + x) % MD;
        }
        c_++;
      }
    if (c_ % 2 == 0)
      kk[c_] = (kk[c_] - 1 + MD) % MD, kk[c_ - 2] = (kk[c_ - 2] + 1) % MD;
  }
  for (a++; a <= b; a = (a | a - 1) + 1) {
    c = 0;
    for (h = 0; h < l; h++)
      if ((a & 1 << h) != 0)
        c++;
    if (c % 2 == 0 && (a & (1 << h_) - 1) == 0)
      c -= 2;
    kk[c] = (kk[c] - 1 + MD) % MD, kk[0] = (kk[0] + 1) % MD;
  }
}

void solve(int *kk, int a, int b) {
  static int kk_[C];
  int l, c;

  l = 0;
  while (1 << l <= a)
    l++;
  solve_(kk, l, a, b % (1 << l));
  if ((b >>= l) > 0) {
    solve_(kk_, l, a, (1 << l) - 1);
    for (c = 0; c <= l; c++)
      kk[c] = (kk[c] + (long long)kk_[c] * b) % MD;
  }
  kk[0] = (kk[0] - 1 + MD) % MD;
}

int main() {
#if 0
	int a;

	for (a = 2048; a <= 4095; a++)
		brute(a, 4095);
#else
  int t;

  init();
  scanf("%d", &t);
  while (t--) {
    static int aa[N], bb[N], kk[C], dp[C], dq[C];
    int n, i, x, c;

    scanf("%d", &n);
    for (i = 0; i < n; i++)
      scanf("%d", &aa[i]);
    for (i = 0; i < n; i++)
      scanf("%d", &bb[i]);
    memset(dp, 0, C * sizeof *dp), dp[0] = 1;
    for (i = 0; i < n; i++) {
      solve(kk, aa[i], bb[i]);
      memset(dq, 0, C * sizeof *dq);
      for (x = 0; x < C; x++)
        for (c = 0; c < C; c++)
          dq[x ^ c] = (dq[x ^ c] + (long long)dp[x] * kk[c]) % MD;
      memcpy(dp, dq, C * sizeof *dq);
    }
    printf("%d\n", dp[0]);
  }
#endif
  return 0;
}
