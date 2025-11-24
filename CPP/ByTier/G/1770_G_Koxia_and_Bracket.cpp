// Problem: CF 1770 G - Koxia and Bracket
// https://codeforces.com/contest/1770/problem/G

/*
Purpose: This code solves the problem of counting the number of ways to remove k characters from a bracket sequence to make it balanced.
The solution uses dynamic programming with NTT (Number Theoretic Transform) for efficient polynomial multiplication.
Algorithms/Techniques: 
- Dynamic Programming with Segment Tree approach for bracket balancing
- Number Theoretic Transform (NTT) for polynomial multiplication
- Modular arithmetic and combinatorics for counting
Time Complexity: O(n log²n) where n is the length of the string
Space Complexity: O(n) for storing arrays and vectors
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
const int o = 1.2e6, MOD = 998244353;
inline int fix(int x) { return x + (x >> 31 & MOD); }
inline int qp(int b, int f) {
  int res = 1;
  for (; f; f >>= 1, b = b * 1ll * b % MOD)
    if (f & 1)
      res = res * 1ll * b % MOD;
  return res;
}
int n, cnt, fac[o], inv[o], rev[o], w[o], bt, sp[o], ans;
char s[o];
inline void init() {
  bt = 20;
  w[1 << (bt - 1)] = 1;
  for (int i = (1 << (bt - 1)) + 1, j = qp(3, (MOD - 1) / (1 << bt));
       i < (1 << bt); ++i)
    w[i] = w[i - 1] * 1ll * j % MOD;
  for (int i = (1 << (bt - 1)); --i;)
    w[i] = w[i << 1];
  for (int i = 1; i < (1 << bt); ++i)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bt - 1));
}
inline void ntt(vector<int> &a, int n, bool inv) {
  for (int i = 1; i < n; ++i)
    if (rev[i] < i)
      swap(a[i], a[rev[i]]);
  for (int md = 1; md < n; md <<= 1)
    for (int i = 0; i < n; i += md << 1)
      for (int j = 0, x, y; j < md; ++j)
        x = a[i + j], y = a[i + j + md] * 1ll * w[j + md] % MOD,
        a[i + j] = fix(x + y - MOD), a[i + j + md] = fix(x - y);
  if (inv)
    for (int i = 1, j = n - 1; i < j; swap(a[i++], a[j--]))
      ;
}
vector<int> mult(vector<int> a, vector<int> b) {
  int sz = a.size() + b.size() - 1;
  for (bt = 0; (1 << bt) < sz; ++bt)
    ;
  if ((1 << bt) <= 32) {
    vector<int> res(sz);
    for (int i = a.size(); i--;)
      for (int j = b.size(); j--;)
        res[i + j] = (res[i + j] + a[i] * 1ll * b[j]) % MOD;
    return res;
  }
  for (int i = 1; i < (1 << bt); ++i)
    rev[i] = ((rev[i >> 1] >> 1) | ((i & 1) << (bt - 1)));
  a.resize(1 << bt);
  ntt(a, 1 << bt, 0);
  b.resize(1 << bt);
  ntt(b, 1 << bt, 0);
  for (int i = 0; i < (1 << bt); ++i)
    a[i] = a[i] * 1ll * b[i] % MOD;
  ntt(a, 1 << bt, 1);
  for (int i = 0, j = qp(1 << bt, MOD - 2); i < (1 << bt); ++i)
    a[i] = a[i] * 1ll * j % MOD;
  a.resize(sz);
  return a;
}
inline int C(int x, int y) {
  return fac[x] * 1ll * inv[y] % MOD * inv[x - y] % MOD;
}
vector<int> slv(int l, int r, vector<int> F) {
  if (F.empty())
    return F;
  if (l + 1 == r) {
    vector<int> res = F;
    if (sp[r] ^ sp[r - 1])
      for (int i = F.size(); --i;)
        res[i - 1] = fix(res[i - 1] + F[i] - MOD);
    else {
      res.push_back(F.back());
      for (int i = F.size(); --i;)
        res[i] = fix(res[i] + F[i - 1] - MOD);
    }
    return res;
  }
  int md = l + r >> 1, c = sp[r] - sp[l];
  vector<int> t(min(c, (int)F.size())), t2, res;
  for (int i = t.size(); i--;)
    t[i] = F[i];
  res = slv(md, r, slv(l, md, t));
  if ((int)F.size() > c) {
    t.resize(F.size() - c);
    t2.resize(r - l + 1);
    for (int i = t.size(); i--;)
      t[i] = F[i + c];
    for (int i = 0; i <= r - l; ++i)
      t2[i] = C(r - l, i);
    t = mult(t, t2);
    res.resize(max(res.size(), t.size()));
    for (int i = t.size(); i--;)
      res[i] = fix(res[i] + t[i] - MOD);
  }
  return res;
}
inline int calc() {
  cnt = 0;
  for (int i = 1, mn = 0, j = 0; i <= n; ++i) {
    if (s[i] == '(')
      ++j;
    else if (mn > --j)
      mn = j, sp[++cnt] = 1;
    else
      sp[++cnt] = 0;
  }
  if (!cnt)
    return 1;
  for (int i = 1; i <= cnt; ++i)
    sp[i] += sp[i - 1];
  return slv(0, cnt, vector<int>(1, 1))[0];
}
int main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  init();
  inv[1] = 1;
  for (int i = 2; i <= n; ++i)
    inv[i] = MOD - MOD / i * 1ll * inv[MOD % i] % MOD;
  for (int i = fac[0] = inv[0] = 1; i <= n; ++i)
    fac[i] = fac[i - 1] * 1ll * i % MOD,
    inv[i] = inv[i - 1] * 1ll * inv[i] % MOD;
  ans = calc();
  for (int i = 1; i <= n; ++i)
    s[i] = '(' + ')' - s[i];
  for (int i = 1, j = n; i < j; swap(s[i++], s[j--]))
    ;
  printf("%lld", ans * 1ll * calc() % MOD);
  return 0;
}


// https://github.com/VaHiX/CodeForces/