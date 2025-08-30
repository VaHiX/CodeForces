/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;

int ipow(int a, int X) {
  int b = 1;
  while (X--)
    b *= a;
  return b;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  int R, C, X;
  cin >> R >> C >> X;
  vector<string> S(R);
  for (int i = 0; i < R; i++) {
    cin >> S[i];
  }
  using ll = int64_t;
  vector<vector<ll>> p(R, vector<ll>(C));
  for (int i = 0; i < R; i++) {
    if (i + 1 < R) {
      p[i + 1][0] = p[i][0] + ipow(int(S[i + 1][0]) - int(S[i][0]), X);
    }
    for (int j = 0; j + 1 < C; j++) {
      p[i][j + 1] = p[i][j] + ipow(int(S[i][j + 1]) - int(S[i][j]), X);
    }
  }
  int bad = 0;
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      if (i + 1 < R) {
        if (p[i + 1][j] != p[i][j] + ipow(int(S[i + 1][j]) - int(S[i][j]), X)) {
          bad = 1;
        }
      }
    }
  }
  int Q;
  cin >> Q;
  while (Q--) {
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    r1--;
    c1--;
    r2--;
    c2--;
    if (bad) {
      cout << "INVALID" << '\n';
    } else {
      cout << (-p[r2][c2] + p[r1][c1]) << '\n';
    }
  }
}
