/*
 * Problem URL : https://codeforces.com/problemset/problem/2069/E
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
using namespace std;
int T, n, a, b, c, d, cnta, cntb, cnt, trn, l, tmp;
char s[600000];
vector<int> vc, vd;
int main() {
  cin >> T;
  while (T--) {
    scanf("%s%d%d%d%d", s + 1, &a, &b, &c, &d);
    vc.clear(), vd.clear(), cnta = cntb = cnt = 0, l = 1, n = strlen(s + 1);
    for (int i = 1; i <= n; i++) {
      if (s[i] == 'A')
        cnta++;
      else
        cntb++;
    }
    trn = max(cnta - a, cntb - b);
    for (int i = 1; i <= n; i++) {
      if (i == n || s[i] == s[i + 1]) {
        tmp = (i - l + 1) / 2;
        if (tmp) {
          if (s[l] == s[i])
            cnt += tmp;
          else if (s[l] == 'A')
            vc.push_back(tmp);
          else
            vd.push_back(tmp);
        }
        l = i + 1;
      }
    }
    sort(vc.begin(), vc.end());
    sort(vd.begin(), vd.end());
    for (auto i : vc) {
      if (c < i)
        cnt += i - 1;
      else
        trn -= i, c -= i;
    }
    for (auto i : vd) {
      if (d < i)
        trn -= d, i -= d, d = 0, cnt += i - 1;
      else
        trn -= i, d -= i;
    }
    if (trn <= min(c + d, cnt))
      cout << "YES\n";
    else
      cout << "NO\n";
  }
  return 0;
}