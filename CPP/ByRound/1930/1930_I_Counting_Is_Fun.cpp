/*
 * Problem URL : https://codeforces.com/contest/1930/problem/I
 * Submit Date : 2025-09-07
 */

#include <cstdio>
#include <cstring>

#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <vector>

#define LOG(FMT...) fprintf(stderr, FMT)

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int P = 998244353, R = 3;
const int BRUTE_N2_LIMIT = 50;

int mpow(int x, int k, int p = P) {
  int ret = 1;
  while (k) {
    if (k & 1)
      ret = ret * (ll)x % p;
    x = x * (ll)x % p;
    k >>= 1;
  }
  return ret;
}

int norm(int x) { return x >= P ? x - P : x; }

int reduce(int x) { return x < 0 ? x + P : x; }

void add(int &x, int y) {
  if ((x += y) >= P)
    x -= P;
}

void sub(int &x, int y) {
  if ((x -= y) < 0)
    x += P;
}

void fam(int &x, int y, int z) { x = (x + y * (ull)z) % P; }

struct NumberTheory {

  NumberTheory() {}

  void _exGcd(int a, int b, int &x, int &y) {
    if (!b) {
      x = 1;
      y = 0;
      return;
    }
    _exGcd(b, a % b, y, x);
    y -= a / b * x;
  }

  int inv(int a, int p = P) {
    int x, y;
    _exGcd(a, p, x, y);
    if (x < 0)
      x += p;
    return x;
  }

} nt;

struct Simple {
  int n;
  vector<int> fac, ifac, inv;

  void build(int n) {
    this->n = n;
    fac.resize(n + 1);
    ifac.resize(n + 1);
    inv.resize(n + 1);
    fac[0] = 1;
    for (int x = 1; x <= n; ++x)
      fac[x] = fac[x - 1] * (ll)x % P;
    inv[1] = 1;
    for (int x = 2; x <= n; ++x)
      inv[x] = -(P / x) * (ll)inv[P % x] % P + P;
    ifac[0] = 1;
    for (int x = 1; x <= n; ++x)
      ifac[x] = ifac[x - 1] * (ll)inv[x] % P;
  }

  Simple() { build(1); }

  void check(int k) {
    int nn = n;
    if (k > nn) {
      while (k > nn)
        nn <<= 1;
      build(nn);
    }
  }

  int gfac(int k) {
    check(k);
    return fac[k];
  }

  int gifac(int k) {
    check(k);
    return ifac[k];
  }

  int ginv(int k) {
    check(k);
    return inv[k];
  }

  int binom(int n, int m) {
    if (m < 0 || m > n)
      return 0;
    return gfac(n) * (ll)gifac(m) % P * gifac(n - m) % P;
  }
} simp;

const int L2 = 11;

struct NTT {
  int L;
  vector<int> root;

  NTT() : L(-1) {}

  void prepRoot(int l) {
    L = l;
    root.resize((1 << L) + 1);
    int i, n = 1 << L;
    int *w2 = root.data();
    *w2 = 1;
    w2[1 << l] = mpow(31, 1 << (21 - l));

    for (i = l; i; --i)
      w2[1 << (i - 1)] = (ull)w2[1 << i] * w2[1 << i] % P;

    for (i = 1; i < n; ++i)
      w2[i] = (ull)w2[i & (i - 1)] * w2[i & -i] % P;
  }

  void DIF(int *a, int l) {
    int *j, *k, n = 1 << l, len = n >> 1, r, *o;

    for (; len; len >>= 1)
      for (j = a, o = root.data(); j != a + n; j += len << 1, ++o)
        for (k = j; k != j + len; ++k) {
          r = (ull)*o * k[len] % P;
          k[len] = reduce(*k - r);
          add(*k, r);
        }
  }

  void DIT(int *a, int l) {
    int *j, *k, n = 1 << l, len = 1, r, *o;

    for (; len != n; len <<= 1)
      for (j = a, o = root.data(); j != a + n; j += len << 1, ++o)
        for (k = j; k != j + len; ++k) {
          r = reduce(*k + k[len] - P);
          k[len] = ull(*k - k[len] + P) * *o % P;
          *k = r;
        }
  }

  void fft(int *a, int lgn, int d = 1) {
    if (L < lgn)
      prepRoot(lgn);
    int n = 1 << lgn;
    if (d == 1)
      DIF(a, lgn);
    else {
      DIT(a, lgn);
      reverse(a + 1, a + n);
      ull nv = P - (P - 1) / n;
      for (int i = 0; i < n; ++i)
        a[i] = a[i] * nv % P;
    }
  }
} ntt;

struct Poly {
  vector<int> a;

  Poly(int v = 0) : a(1) {
    if ((v %= P) < 0)
      v += P;
    a[0] = v;
  }

  Poly(const vector<int> &a) : a(a) {}

  Poly(initializer_list<int> init) : a(init) {}

  // Helps
  int operator[](int k) const { return k < a.size() ? a[k] : 0; }

  int &operator[](int k) {
    if (k >= a.size())
      a.resize(k + 1);
    return a[k];
  }

  int deg() const { return a.size() - 1; }

  void redeg(int d) { a.resize(d + 1); }

  Poly slice(int d) const {
    if (d < a.size())
      return vector<int>(a.begin(), a.begin() + d + 1);
    vector<int> res(a);
    res.resize(d + 1);
    return res;
  }

  int *base() { return a.data(); }

  const int *base() const { return a.data(); }

  Poly println(FILE *fp) const {
    fprintf(fp, "%d", a[0]);
    for (int i = 1; i < a.size(); ++i)
      fprintf(fp, " %d", a[i]);
    fputc('\n', fp);
    return *this;
  }

  // Calculations
  Poly operator+(const Poly &rhs) const {
    vector<int> res(max(a.size(), rhs.a.size()));
    for (int i = 0; i < res.size(); ++i)
      if ((res[i] = operator[](i) + rhs[i]) >= P)
        res[i] -= P;
    return res;
  }

  Poly operator-() const {
    Poly ret(a);
    for (int i = 0; i < a.size(); ++i)
      if (ret[i])
        ret[i] = P - ret[i];
    return ret;
  }

  Poly operator-(const Poly &rhs) const { return operator+(-rhs); }

  Poly operator*(const Poly &rhs) const;
};

Poly zeroes(int deg) { return vector<int>(deg + 1); }

struct SemiRelaxedConvolution {

  template <class Function>
  void run(const vector<int> &a, vector<int> &b, const Function &relax) {
    int n = a.size() - 1;
    function<void(int, int)> divideConquer = [&](int l, int r) {
      if (r - l <= BRUTE_N2_LIMIT) {
        for (int i = l; i <= r; ++i) {
          for (int j = l; j < i; ++j)
            b[i] = (b[i] + b[j] * (ll)a[i - j]) % P;
          relax(i);
        }
        return;
      }
      int lg = 31 - __builtin_clz(r - l) + 1;
      int d = (r - l) / lg + 1;
      int lgd = 0;
      while ((1 << lgd) < d)
        ++lgd;
      ++lgd;

      vector<int> top((lg << (lgd + 1)));
      for (int i = 0; i < lg; ++i) {
        copy(a.begin() + i * d, a.begin() + min((i + 2) * d, n + 1),
             top.begin() + (i << lgd));
        ntt.fft(top.data() + (i << lgd), lgd, 1);
      }
      for (int i = 0; i < lg; ++i) {
        if (i)
          ntt.fft(top.data() + ((lg + i) << lgd), lgd, -1);
        for (int j = 0; j < min(d, r - l - i * d + 1); ++j)
          b[l + i * d + j] =
              norm(b[l + i * d + j] + top[((lg + i) << lgd) + d + j]);
        divideConquer(l + i * d, min(l + (i + 1) * d - 1, r));
        if (i + 1 < lg) {
          copy(b.begin() + l + i * d, b.begin() + min(l + (i + 1) * d, n + 1),
               top.begin() + ((lg + i) << lgd));
          fill(top.data() + ((lg + i) << lgd) + d,
               top.data() + ((lg + i + 1) << lgd), 0);
          ntt.fft(top.data() + ((lg + i) << lgd), lgd, 1);
        }
        for (int j = i + 1; j < lg; ++j) {
          for (int k = 0; k < (1 << lgd); ++k)
            top[((lg + j) << lgd) + k] = (top[((lg + j) << lgd) + k] +
                                          top[((j - i - 1) << lgd) + k] *
                                              (ll)top[((lg + i) << lgd) + k]) %
                                         P;
        }
      }
    };
    divideConquer(0, n);
  }
} src;

struct Transposition {

  vector<int> _mul(int l, vector<int> res, const Poly &b) {
    vector<int> tmp(1 << l);
    memcpy(tmp.data(), b.a.data(), sizeof(int) * (b.deg() + 1));
    reverse(tmp.begin() + 1, tmp.end());
    ntt.fft(tmp.data(), l, 1);
    for (int i = 0; i < (1 << l); ++i)
      res[i] = res[i] * (ll)tmp[i] % P;
    ntt.fft(res.data(), l, -1);
    return res;
  }

  Poly bfMul(const Poly &a, const Poly &b) {
    int n = a.deg(), m = b.deg();
    Poly ret = zeroes(n - m);
    for (int i = 0; i <= n - m; ++i)
      for (int j = 0; j <= m; ++j)
        ret[i] = (ret[i] + a[i + j] * (ll)b[j]) % P;
    return ret;
  }

  Poly mul(const Poly &a, const Poly &b) {
    if (a.deg() < b.deg())
      return 0;
    if (a.deg() <= BRUTE_N2_LIMIT)
      return bfMul(a, b);
    int l = 0;
    while ((1 << l) <= a.deg())
      ++l;
    vector<int> res(1 << l);
    memcpy(res.data(), a.a.data(), sizeof(int) * (a.deg() + 1));
    ntt.fft(res.data(), l, 1);
    res = _mul(l, res, b);
    res.resize(a.deg() - b.deg() + 1);
    return res;
  }

  pair<Poly, Poly> mul2(const Poly &a, const Poly &b1, const Poly &b2) {
    if (a.deg() <= BRUTE_N2_LIMIT)
      return make_pair(bfMul(a, b1), bfMul(a, b2));
    int l = 0;
    while ((1 << l) <= a.deg())
      ++l;
    vector<int> fa(1 << l);
    memcpy(fa.data(), a.a.data(), sizeof(int) * (a.deg() + 1));
    ntt.fft(fa.data(), l, 1);
    vector<int> res1 = _mul(l, fa, b1), res2 = _mul(l, fa, b2);
    res1.resize(a.deg() - b1.deg() + 1);
    res2.resize(a.deg() - b2.deg() + 1);
    return make_pair(res1, res2);
  }

  vector<int> ls, rs, pos;
  vector<Poly> p, q;

  void _build(int n) {
    ls.assign(n * 2 - 1, 0);
    rs.assign(n * 2 - 1, 0);
    p.assign(n * 2 - 1, 0);
    q.assign(n * 2 - 1, 0);
    pos.resize(n);
    int cnt = 0;
    function<int(int, int)> dfs = [&](int l, int r) {
      if (l == r) {
        pos[l] = cnt;
        return cnt++;
      }
      int ret = cnt++;
      int mid = (l + r) >> 1;
      ls[ret] = dfs(l, mid);
      rs[ret] = dfs(mid + 1, r);
      return ret;
    };
    dfs(0, n - 1);
  }
} tp;

Poly operator"" _z(unsigned long long a) { return {0, (int)a}; }

Poly operator+(int v, const Poly &rhs) { return Poly(v) + rhs; }

Poly Poly::operator*(const Poly &rhs) const {
  int n = deg(), m = rhs.deg();
  if (n <= 10 || m <= 10 || n + m <= BRUTE_N2_LIMIT) {
    Poly ret = zeroes(n + m);
    for (int i = 0; i <= n; ++i)
      for (int j = 0; j <= m; ++j)
        ret[i + j] = (ret[i + j] + a[i] * (ll)rhs[j]) % P;
    return ret;
  }
  n += m;
  int l = 0;
  while ((1 << l) <= n)
    ++l;
  vector<int> res(1 << l), tmp(1 << l);
  memcpy(res.data(), base(), a.size() * sizeof(int));
  ntt.fft(res.data(), l, 1);
  memcpy(tmp.data(), rhs.base(), rhs.a.size() * sizeof(int));
  ntt.fft(tmp.data(), l, 1);
  for (int i = 0; i < (1 << l); ++i)
    res[i] = res[i] * (ll)tmp[i] % P;
  ntt.fft(res.data(), l, -1);
  res.resize(n + 1);
  return res;
}

const int _ = 100005;

int f[_], g[_];
char s[_];

void solve(int l, int r, Poly vec) {
  if (l == r) {
    f[l] = vec[0];
    return;
  }
  int mid = (l + r) / 2, len = mid - l;
  Poly middle = zeroes((len + 1) * 2);
  for (int i = 0; i <= len + 1; ++i)
    middle[i * 2] = simp.binom(len + 1, i);
  solve(mid + 1, r, tp.mul(vec, middle));
  middle.redeg(len * 2);
  for (int i = -len; i <= len; ++i)
    middle[i + len] = vec[i + (r - l)];
  solve(l, mid, middle);
}

void calcf(int N) {
  Poly refl = zeroes(N * 2);
  for (int i = 0; i <= N; ++i) {
    int per = (i + 2) * 2;
    for (int j = i; j <= N; j += per)
      add(refl[j + N], 1);
    for (int j = i - per; j >= -N; j -= per)
      add(refl[j + N], 1);
    for (int j = i + 2; j <= N; j += per)
      sub(refl[j + N], 1);
    for (int j = -i - 2; j >= -N; j -= per)
      sub(refl[j + N], 1);
  }

  solve(0, N, refl);
}
// https://oeis.org/A001405
void calcg(int N) {
  for (int i = 0; i <= N; ++i)
    g[i] = simp.binom(i, i / 2);
}

bool flag[_];

int calc(int N) {
  int ans = 0;
  std::vector<int> arrf(f, f + N - 1), conv(N);
  arrf.insert(arrf.begin(), 0);
  src.run(arrf, conv, [&](int i) {
    if (!flag[i + 1]) {
      conv[i] = 0;
      return;
    }
    conv[i] = reduce(g[i] - conv[i]);
    fam(ans, conv[i], g[N - i - 1]);
  });
  return ans;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  // int T; std::cin >> T;
  int T = 1;

  while (T--) {
    int N;
    std::cin >> N >> (s + 1);
    calcf(N);
    calcg(N);

    int ans = mpow(2, N);

    for (int i = 1; i <= N; ++i)
      flag[i] = s[i] == '0';
    sub(ans, calc(N));

    for (int i = 1; i <= N; ++i)
      flag[i] = s[i] == '1';
    sub(ans, calc(N));

    std::cout << ans << '\n';
  }

  return 0;
}
