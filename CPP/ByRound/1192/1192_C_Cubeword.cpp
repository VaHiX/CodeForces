/*
 * Problem URL : https://codeforces.com/contest/1192/problem/C
 * Submit Date : 2025-09-02
 */

#include <algorithm>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

const int kMaxN = 1e5 + 1, kMaxM = 62, kMaxL = 11, kMod = 998244353;
int n, m, r[256];
LL ans, f[kMaxM][kMaxM], g[kMaxM][kMaxM][kMaxM];
vector<string> l[kMaxL];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (char c = 'a'; c <= 'z'; c++) {
    r[c] = m++;
  }
  for (char c = 'A'; c <= 'Z'; c++) {
    r[c] = m++;
  }
  for (char c = '0'; c <= '9'; c++) {
    r[c] = m++;
  }
  cin >> n;
  for (int i = 1; i <= n; i++) {
    static string s;
    cin >> s, l[s.size()].push_back(s);
  }
  for (int i = 3; i < kMaxL; i++) {
    fill(&f[0][0], &f[kMaxM][0], 0);
    fill(&g[0][0][0], &g[kMaxM][0][0], 0);
    sort(l[i].begin(), l[i].end());
    for (string s : l[i]) {
      string t = s;
      reverse(t.begin(), t.end());
      auto p = lower_bound(l[i].begin(), l[i].end(), t);
      if (s <= t || p == l[i].end() || *p != t) {
        f[r[s.front()]][r[s.back()]]++;
        if (s != t) {
          f[r[s.back()]][r[s.front()]]++;
        }
      }
    }
    for (int a = 0; a < m; a++) {
      for (int b = 0; b < m; b++) {
        for (int c = b; c < m; c++) {
          for (int d = c; d < m; d++) {
            LL w = f[a][b] * f[a][c] % kMod * f[a][d];
            g[b][c][d] = (g[b][c][d] + w) % kMod;
          }
        }
      }
    }
    for (int a = 0; a < m; a++) {
      for (int b = a; b < m; b++) {
        for (int c = b; c < m; c++) {
          for (int d = c; d < m; d++) {
            LL w = g[a][b][c] * g[a][b][d] % kMod * g[a][c][d] % kMod * g[b][c][d] % kMod;
            if (a == d) {
              ans = (ans + w) % kMod;
            } else if (a == c || b == d) {
              ans = (ans + w * 4) % kMod;
            } else if (a == b && c == d) {
              ans = (ans + w * 6) % kMod;
            } else if (a == b || b == c || c == d) {
              ans = (ans + w * 12) % kMod;
            } else {
              ans = (ans + w * 24) % kMod;
            }
          }
        }
      }
    }
  }
  cout << ans << '\n';
  return 0;
}
