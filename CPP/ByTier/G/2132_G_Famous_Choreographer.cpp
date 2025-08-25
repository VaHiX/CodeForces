/*
 * Problem URL : https://codeforces.com/problemset/problem/2132/G
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  std::mt19937_64 rng((unsigned)chrono::high_resolution_clock::now()
                          .time_since_epoch()
                          .count());
  int T;
  if (!(cin >> T))
    return 0;
  while (T--) {
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for (int i = 0; i < n; i++)
      cin >> g[i];
    ull br1 = (ull)rng() | 1000003ULL;
    ull bc1 = (ull)rng() | 1000033ULL;
    ull br2 = (ull)rng() | 10007ULL;
    ull bc2 = (ull)rng() | 10009ULL;
    vector<ull> powBr1(n + 1), powBr2(n + 1), powBc1(m + 1), powBc2(m + 1);
    powBr1[0] = 1;
    powBr2[0] = 1;
    for (int i = 1; i <= n; i++) {
      powBr1[i] = powBr1[i - 1] * br1;
      powBr2[i] = powBr2[i - 1] * br2;
    }
    powBc1[0] = 1;
    powBc2[0] = 1;
    for (int j = 1; j <= m; j++) {
      powBc1[j] = powBc1[j - 1] * bc1;
      powBc2[j] = powBc2[j - 1] * bc2;
    }
    int W = m + 1;
    vector<ull> H1((n + 1) * (m + 1));
    vector<ull> H2((n + 1) * (m + 1));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        ull val = (ull)(g[i][j] - 'a' + 1);
        ull A1 = H1[i * (W) + (j + 1)];
        ull B1 = H1[(i + 1) * (W) + j];
        ull C1 = H1[i * (W) + j];
        ull res1 = A1 * br1;
        res1 += B1 * bc1;
        res1 -= C1 * (br1 * bc1);
        res1 += val;
        H1[(i + 1) * (W) + (j + 1)] = res1;
        ull A2 = H2[i * (W) + (j + 1)];
        ull B2 = H2[(i + 1) * (W) + j];
        ull C2 = H2[i * (W) + j];
        ull res2 = A2 * br2;
        res2 += B2 * bc2;
        res2 -= C2 * (br2 * bc2);
        res2 += val;
        H2[(i + 1) * (W) + (j + 1)] = res2;
      }
    }
    vector<string> Rg(n, string(m, 'a'));
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        Rg[i][j] = g[n - 1 - i][m - 1 - j];
    vector<ull> HR1((n + 1) * (m + 1));
    vector<ull> HR2((n + 1) * (m + 1));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        ull val = (ull)(Rg[i][j] - 'a' + 1);
        ull A1 = HR1[i * (W) + (j + 1)];
        ull B1 = HR1[(i + 1) * (W) + j];
        ull C1 = HR1[i * (W) + j];
        ull res1 = A1 * br1;
        res1 += B1 * bc1;
        res1 -= C1 * (br1 * bc1);
        res1 += val;
        HR1[(i + 1) * (W) + (j + 1)] = res1;
        ull A2 = HR2[i * (W) + (j + 1)];
        ull B2 = HR2[(i + 1) * (W) + j];
        ull C2 = HR2[i * (W) + j];
        ull res2 = A2 * br2;
        res2 += B2 * bc2;
        res2 -= C2 * (br2 * bc2);
        res2 += val;
        HR2[(i + 1) * (W) + (j + 1)] = res2;
      }
    }
    auto getHash = [&](const vector<ull> &HH, const vector<ull> &pBr,
                       const vector<ull> &pBc, int x1, int x2, int y1,
                       int y2) -> ull {
      int lenx = x2 - x1 + 1;
      int leny = y2 - y1 + 1;
      ull A = HH[(x2 + 1) * (W) + (y2 + 1)];
      ull B = HH[(x1) * (W) + (y2 + 1)];
      ull C = HH[(x2 + 1) * (W) + (y1)];
      ull D = HH[(x1) * (W) + (y1)];
      ull t1 = B * pBr[lenx];
      ull t2 = C * pBc[leny];
      ull t3 = D * (pBr[lenx] * pBc[leny]);
      ull res = A - t1 - t2 + t3;
      return res;
    };
    long long best = LLONG_MAX;
    for (int si = -(n - 1); si <= (n - 1); ++si) {
      int rowsOverlap = n - abs(si);
      if (rowsOverlap <= 0)
        continue;
      int x1 = max(0, si);
      int x2 = x1 + rowsOverlap - 1;
      int u1 = x1 - si;
      int u2 = u1 + rowsOverlap - 1;
      for (int sj = -(m - 1); sj <= (m - 1); ++sj) {
        int colsOverlap = m - abs(sj);
        if (colsOverlap <= 0)
          continue;
        int y1 = max(0, sj);
        int y2 = y1 + colsOverlap - 1;
        int v1 = y1 - sj;
        int v2 = v1 + colsOverlap - 1;
        ull hA1 = getHash(H1, powBr1, powBc1, x1, x2, y1, y2);
        ull hR1 = getHash(HR1, powBr1, powBc1, u1, u2, v1, v2);
        if (hA1 != hR1)
          continue;
        ull hA2 = getHash(H2, powBr2, powBc2, x1, x2, y1, y2);
        ull hR2 = getHash(HR2, powBr2, powBc2, u1, u2, v1, v2);
        if (hA2 != hR2)
          continue;
        long long X = n + llabs(si);
        long long Y = m + llabs(sj);
        long long invited = X * Y - 1LL * n * m;
        if (invited < best)
          best = invited;
      }
    }
    if (best == LLONG_MAX)
      cout << -1 << "\n";
    else
      cout << best << "\n";
  }
  return 0;
}