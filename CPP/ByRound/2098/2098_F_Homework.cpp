/*
 * Problem URL : https://codeforces.com/problemset/problem/2098/F
 * Submit Date : 2025-08-20
 */

// b2b3d1ff-5887-42aa-a51a-a9d383281a03
#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  if (!(cin >> T))
    return 0;
  while (T--) {
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    int k = __builtin_ctz(n);
    int L = 1 << k;
    int m = n / L;
    // Case: no operations possible
    if (L == 1) {
      // must be equal
      cout << (s == t ? "Yes\n" : "No\n");
      continue;
    }
    // Leaves size 1: only zero/nonzero invariant
    if (m == 1) {
      bool any_s = false, any_t = false;
      for (char c : s)
        if (c == '1') {
          any_s = true;
          break;
        }
      for (char c : t)
        if (c == '1') {
          any_t = true;
          break;
        }
      cout << ((any_s == any_t) ? "Yes\n" : "No\n");
      continue;
    }
    // General case: blocks of size m > 1, block count L > 1
    int W = (m + 63) >> 6; // words per block vector

    // Build basis for S
    vector<pair<int, vector<ull>>> basisS;
    basisS.reserve(m); // at most m
    for (int bi = 0; bi < L; bi++) {
      // load block bi of s
      vector<ull> vec(W, 0ULL);
      int off = bi * m;
      for (int j = 0; j < m; j++) {
        if (s[off + j] == '1') {
          int w = j >> 6, b = j & 63;
          vec[w] |= (1ULL << b);
        }
      }
      // eliminate
      for (auto &bp : basisS) {
        int piv = bp.first;
        int w = piv >> 6, b = piv & 63;
        if (vec[w] & (1ULL << b)) {
          // xor
          auto &bv = bp.second;
          for (int ww = 0; ww < W; ww++)
            vec[ww] ^= bv[ww];
        }
      }
      // find pivot
      int piv = -1;
      for (int w = W - 1; w >= 0; w--) {
        if (vec[w]) {
          // highest bit
          int bit = 63 - __builtin_clzll(vec[w]);
          piv = (w << 6) + bit;
          break;
        }
      }
      if (piv >= 0) {
        basisS.emplace_back(piv, std::move(vec));
      }
    }
    int ds = (int)basisS.size();

    // Build basis for T
    vector<pair<int, vector<ull>>> basisT;
    basisT.reserve(m);
    for (int bi = 0; bi < L; bi++) {
      vector<ull> vec(W, 0ULL);
      int off = bi * m;
      for (int j = 0; j < m; j++) {
        if (t[off + j] == '1') {
          int w = j >> 6, b = j & 63;
          vec[w] |= (1ULL << b);
        }
      }
      // eliminate within T basis
      for (auto &bp : basisT) {
        int piv = bp.first;
        int w = piv >> 6, b = piv & 63;
        if (vec[w] & (1ULL << b)) {
          auto &bv = bp.second;
          for (int ww = 0; ww < W; ww++)
            vec[ww] ^= bv[ww];
        }
      }
      int piv = -1;
      for (int w = W - 1; w >= 0; w--) {
        if (vec[w]) {
          int bit = 63 - __builtin_clzll(vec[w]);
          piv = (w << 6) + bit;
          break;
        }
      }
      if (piv >= 0) {
        basisT.emplace_back(piv, std::move(vec));
      }
    }
    int dt = (int)basisT.size();

    bool ok = true;
    if (ds != dt) {
      ok = false;
    } else {
      // check T_basis subset of S_span
      for (auto &bp : basisT) {
        auto vec = bp.second; // copy
        // reduce by S basis
        for (auto &sp : basisS) {
          int piv = sp.first;
          int w = piv >> 6, b = piv & 63;
          if (vec[w] & (1ULL << b)) {
            auto &sv = sp.second;
            for (int ww = 0; ww < W; ww++)
              vec[ww] ^= sv[ww];
          }
        }
        // if any bit remains, not in span
        bool nonz = false;
        for (int ww = 0; ww < W; ww++) {
          if (vec[ww]) {
            nonz = true;
            break;
          }
        }
        if (nonz) {
          ok = false;
          break;
        }
      }
    }
    cout << (ok ? "Yes\n" : "No\n");
  }
  return 0;
}