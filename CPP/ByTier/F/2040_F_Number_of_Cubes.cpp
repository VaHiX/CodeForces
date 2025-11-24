// Problem: CF 2040 F - Number of Cubes
// https://codeforces.com/contest/2040/problem/F

/*
Algorithm: Burnside's lemma + Moebius inversion + factorization + CRT
Time Complexity: O(N log N) where N is the maximum of a,b,c
Space Complexity: O(N)
*/

#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;
static const int MOD = 998244353;
static const int MAXN = 3000005;
int spf[MAXN];
int64_t fac[MAXN], ifac[MAXN];
int64_t modpow(int64_t a, int64_t e) {
  int64_t r = 1;
  while (e) {
    if (e & 1)
      r = (r * a) % MOD;
    a = (a * a) % MOD;
    e >>= 1;
  }
  return r;
}
void init() {
  for (int i = 2; i < MAXN; i++) {
    if (!spf[i]) {
      for (int64_t j = i; j < MAXN; j += i) {
        if (!spf[j])
          spf[j] = i;
      }
    }
  }
  fac[0] = 1;
  for (int i = 1; i < MAXN; i++)
    fac[i] = fac[i - 1] * i % MOD;
  ifac[MAXN - 1] = modpow(fac[MAXN - 1], MOD - 2);
  for (int i = MAXN - 1; i > 0; i--) {
    ifac[i - 1] = ifac[i] * i % MOD;
  }
}
vector<pair<int, int>> factorize(int n) {
  vector<pair<int, int>> res;
  while (n > 1) {
    int p = spf[n], c = 0;
    while (n % p == 0) {
      n /= p;
      c++;
    }
    res.emplace_back(p, c);
  }
  return res;
}
void gen_divs(const vector<pair<int, int>> &facs, int idx, int64_t curD,
              int64_t curPhi, vector<pair<int, int>> &out) {
  if (idx == (int)facs.size()) {
    out.emplace_back((int)curD, (int)curPhi);
    return;
  }
  auto [p, e] = facs[idx];
  gen_divs(facs, idx + 1, curD, curPhi, out);
  int64_t d = curD, ph = curPhi;
  for (int i = 1; i <= e; i++) {
    d *= p;
    if (i == 1)
      ph *= (p - 1);
    else
      ph *= p;
    gen_divs(facs, idx + 1, d, ph, out);
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  init();
  int T;
  cin >> T;
  while (T--) {
    int a, b, c, k;
    cin >> a >> b >> c >> k;
    int64_t N = int64_t(a) * b * c;
    vector<int> d(k);
    for (int i = 0; i < k; i++)
      cin >> d[i];
    sort(d.begin(), d.end());
    int g = d[0];
    for (int i = 1; i < k; i++)
      g = gcd(g, d[i]);
    vector<pair<int, int>> freq;
    {
      int i = 0;
      while (i < k) {
        int v = d[i], cnt = 0;
        while (i < k && d[i] == v) {
          i++;
          cnt++;
        }
        freq.emplace_back(v, cnt);
      }
    }
    auto Fa = factorize(a);
    auto Fb = factorize(b);
    auto Fc = factorize(c);
    vector<pair<int, int>> Da, Db, Dc;
    gen_divs(Fa, 0, 1, 1, Da);
    gen_divs(Fb, 0, 1, 1, Db);
    gen_divs(Fc, 0, 1, 1, Dc);
    sort(Da.begin(), Da.end());
    sort(Db.begin(), Db.end());
    sort(Dc.begin(), Dc.end());
    auto lookup_phi = [&](const vector<pair<int, int>> &D, int x) {
      int lo = 0, hi = (int)D.size() - 1;
      while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (D[mid].first < x)
          lo = mid + 1;
        else
          hi = mid;
      }
      return D[lo].second;
    };
    vector<int> wA(Da.size()), wB(Db.size()), wC(Dc.size());
    for (int i = 0; i < (int)Da.size(); i++) {
      int g1 = Da[i].first;
      int v = a / g1;
      wA[i] = lookup_phi(Da, v);
    }
    for (int i = 0; i < (int)Db.size(); i++) {
      int g2 = Db[i].first;
      int v = b / g2;
      wB[i] = lookup_phi(Db, v);
    }
    for (int i = 0; i < (int)Dc.size(); i++) {
      int g3 = Dc[i].first;
      int v = c / g3;
      wC[i] = lookup_phi(Dc, v);
    }
    auto Fg = factorize(g);
    vector<pair<int, int>> Dg;
    gen_divs(Fg, 0, 1, 1, Dg);
    vector<int> gdivs;
    gdivs.reserve(Dg.size());
    for (auto &pp : Dg)
      gdivs.push_back(pp.first);
    sort(gdivs.begin(), gdivs.end());
    vector<int64_t> fL(gdivs.size(), 0LL);
    for (int i = 0; i < (int)Da.size(); i++) {
      int g1 = Da[i].first;
      int x1 = a / g1;
      for (int j = 0; j < (int)Db.size(); j++) {
        int g2 = Db[j].first;
        int x2 = b / g2;
        int64_t l12 = int64_t(x1) / gcd(x1, x2) * x2;
        for (int r = 0; r < (int)Dc.size(); r++) {
          int g3 = Dc[r].first;
          int x3 = c / g3;
          int64_t L = l12 / gcd((int)l12, x3) * x3;
          if (L > g || (g % L) != 0)
            continue;
          int idx = int(lower_bound(gdivs.begin(), gdivs.end(), (int)L) -
                        gdivs.begin());
          int64_t w = (int64_t)wA[i] * wB[j] % MOD * wC[r] % MOD;
          fL[idx] = (fL[idx] + w) % MOD;
        }
      }
    }
    int64_t answer = 0;
    for (int i = 0; i < (int)gdivs.size(); i++) {
      int L = gdivs[i];
      if (fL[i] == 0)
        continue;
      int64_t M = N / L;
      int64_t ways = fac[M];
      for (auto &vf : freq) {
        int v = vf.first;
        int cnt = vf.second;
        int t = v / L;
        ways = ways * modpow(ifac[t], cnt) % MOD;
      }
      answer = (answer + ways * fL[i]) % MOD;
    }
    answer = answer * modpow(N % MOD, MOD - 2) % MOD;
    cout << answer << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/