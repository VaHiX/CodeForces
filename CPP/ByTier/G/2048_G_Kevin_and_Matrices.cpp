/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e6 + 5;
const int MOD = 998244353;

inline int add(int x, int y) {
  x += y;
  if (x >= MOD)
    return x - MOD;
  if (x < 0)
    return x + MOD;
  return x;
}

inline int mul(int x, int y) { return (long long)x * y % MOD; }

int pot(int x, int y) {
  int res = 1;
  for (; y; y /= 2) {
    if (y % 2)
      res = mul(res, x);
    x = mul(x, x);
  }
  return res;
}

int inv[MAX];

int solve() {
  int N, M, V;
  scanf("%d%d%d", &N, &M, &V);
  vector<int> choose(N + 1);
  choose[0] = 1;
  for (int k = 1; k <= N; k++)
    choose[k] = mul(choose[k - 1], mul(N - k + 1, inv[k]));
  int sol = 0;
  for (int x = 1; x <= V; x++) {
    int a = pot(V, N);
    int b = pot(V - x + 1, N);
    for (int k = 1; k <= N; k++) {
      a = mul(a, mul(x, inv[V]));
      b = mul(b, inv[V - x + 1]);
      int tmp = mul(choose[k], add(pot(add(a, -b), M), -pot(a, M)));
      sol = add(sol, k % 2 ? -tmp : tmp);
    }
  }
  return sol;
}

int main() {
  inv[1] = 1;
  for (int i = 2; i < MAX; i++)
    inv[i] = MOD - mul(MOD / i, inv[MOD % i]);
  int tc;
  scanf("%d", &tc);
  while (tc--)
    printf("%d\n", solve());
  return 0;
}