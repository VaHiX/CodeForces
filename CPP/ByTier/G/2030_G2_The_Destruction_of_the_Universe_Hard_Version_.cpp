/*
 * Problem URL : https://codeforces.com/contest/2030/problem/G2
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

inline void inc(int &x, int y) {
  x += y;
  if (x >= MOD)
    x -= MOD;
  else if (x < 0)
    x += MOD;
}

inline int add(int x, int y) {
  inc(x, y);
  return x;
}

inline int mul(int x, int y) { return (long long)x * y % MOD; }

int pot(int x, int y) {
  int r = 1;
  for (; y; y /= 2) {
    if (y % 2)
      r = mul(r, x);
    x = mul(x, x);
  }
  return r;
}

int solve() {
  int N;
  scanf("%d", &N);
  vector<int> pref(N + 1), suff(N + 1);
  for (int i = 0; i < N; i++) {
    int l, r;
    scanf("%d%d", &l, &r);
    pref[r]++;
    suff[l]++;
  }
  vector<int> pw2(N + 1);
  pw2[0] = 1;
  for (int i = 1; i <= N; i++)
    pw2[i] = mul(pw2[i - 1], 2);
  vector<int> fact(N + 1), ifact(N + 1);
  fact[0] = 1;
  for (int i = 1; i <= N; i++)
    fact[i] = mul(fact[i - 1], i);
  ifact[N] = pot(fact[N], MOD - 2);
  for (int i = N - 1; i >= 0; i--)
    ifact[i] = mul(ifact[i + 1], i + 1);
  int sol = 0, lft = 0, rig = N;
  int curr = 0, small = pw2[N] - 1, big = 0;
  for (int i = 1; i < N; i++) {
    auto up = [&](int &x, int y) { inc(x, add(x, y)); };
    auto down = [&](int &x, int y) {
      inc(x, y);
      if (x % 2)
        x += MOD;
      x /= 2;
    };
    auto choose = [&](int n, int k) {
      return k < 0 || k > n ? 0 : mul(fact[n], mul(ifact[k], ifact[n - k]));
    };
    for (; suff[i]--; rig--) {
      down(small, -choose(lft + rig - 1, lft));
      down(big, choose(lft + rig - 1, rig));
      down(curr, -big);
    }
    for (; pref[i]--; lft++) {
      up(curr, small);
      up(small, -choose(lft + rig, rig - 1));
      up(big, choose(lft + rig, lft));
    }
    inc(sol, mul(curr, pw2[N - lft - rig]));
  }
  return sol;
}

int main() {
  int tc;
  scanf("%d", &tc);
  while (tc--)
    printf("%d\n", solve());
  return 0;
}