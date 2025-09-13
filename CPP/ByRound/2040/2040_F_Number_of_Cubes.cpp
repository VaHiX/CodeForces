/*
 * Problem URL : https://codeforces.com/contest/2040/problem/F
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
namespace Limie {
#define x first
#define y second
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
typedef unsigned long long ULL;
} // namespace Limie
using namespace Limie;
const int mod = 998244353;
int a, b, c, n;
int d[1000010], ans[3000010], infact[3000010];
int phi[3000010], fact[3000010], p[3000010], t;
bool st[3000010];
int qmi(int a, int b = mod - 2) {
  int s = 1;
  while (b) {
    if (b & 1)
      s = 1ll * s * a % mod;
    a = 1ll * a * a % mod;
    b >>= 1;
  }
  return s;
}
inline int __gcd(int a, int b) {
  register int x = __builtin_ctz(a), y = __builtin_ctz(b), z = min(x, y), diff;
  b >>= y;
  while (a) {
    a >>= x, diff = b - a;
    x = __builtin_ctz(diff);
    if (a < b)
      b = a;
    a = abs(diff);
  }
  return b << z;
}
inline int lcm(int a, int b) { return a * b / __gcd(a, b); }
void get_prime(int n) {
  fact[0] = fact[1] = phi[1] = 1;
  for (int i = 2; i <= n; i++) {
    fact[i] = 1ll * fact[i - 1] * i % mod;
    if (!st[i])
      p[++t] = i, phi[i] = i - 1;
    for (int j = 1; p[j] * i <= n; j++) {
      st[p[j] * i] = 1;
      if (i % p[j] == 0) {
        phi[i * p[j]] = phi[i] * p[j];
        break;
      }
      phi[i * p[j]] = phi[i] * (p[j] - 1);
    }
  }
  infact[n] = qmi(fact[n]);
  for (int i = n; i; i--)
    infact[i - 1] = 1ll * infact[i] * i % mod;
}
void calc(vector<int> &d, int n) {
  for (int i = 1; i * i <= n; i++) {
    if (n % i)
      continue;
    d.push_back(i);
    if (i * i != n)
      d.push_back(n / i);
  }
}
void solve() {
  int i;
  cin >> a >> b >> c >> n;
  int g = 0, sum = 0;
  for (i = 1; i <= n; i++)
    cin >> d[i], g = __gcd(g, d[i]);
  for (i = 1; i <= n; i++)
    d[i] /= g, sum += d[i];
  vector<int> A, B, C, D;
  calc(A, __gcd(g, a));
  calc(B, __gcd(g, b));
  calc(C, __gcd(g, c));
  calc(D, g);
  for (int x : D) {
    int &s = ans[g / x];
    s = 1;
    for (i = 1; i <= n; i++)
      s = 1ll * s * infact[d[i] * x] % mod;
    s = 1ll * s * fact[sum * x] % mod;
  }
  sum = 0;
  for (int x : A)
    for (int y : B)
      for (int z : C)
        sum = (1ll * phi[x] * phi[y] * phi[z] * ans[lcm(lcm(x, y), z)] + sum) %
              mod;
  cout << 1ll * sum * qmi(a * b * c) % mod << '\n';
}
signed main() {
  int _;
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  get_prime(3e6);
  cin >> _;
  while (_--)
    solve();
}