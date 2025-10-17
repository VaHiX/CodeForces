/*
 * Problem URL : https://codeforces.com/problemset/problem/2066/D1
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e4 + 5;
const int MOD = 1e9 + 7;

int fact[MAX], ifact[MAX];

inline int mul(int x, int y) { return (long long)x * y % MOD; }

void init() {
  ifact[1] = 1;
  for (int i = 2; i < MAX; i++)
    ifact[i] = MOD - mul(MOD / i, ifact[MOD % i]);
  fact[0] = ifact[0] = 1;
  for (int i = 1; i < MAX; i++) {
    fact[i] = mul(fact[i - 1], i);
    ifact[i] = mul(ifact[i - 1], ifact[i]);
  }
}

int main() {
  init();
  int tc;
  scanf("%d", &tc);
  while (tc--) {
    int N, C, M;
    scanf("%d%d%d", &N, &C, &M);
    printf("%d\n", mul(fact[C * (N - 1)], mul(ifact[M - C], ifact[C * N - M])));
    while (M--)
      scanf("%*d");
  }
  return 0;
}