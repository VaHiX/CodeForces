/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;
#define fastcin                                                                \
  ios::sync_with_stdio(0);                                                     \
  cin.tie(0);
const int N = 2e5 + 5;
using bs = bitset<N>;
int main() {
  fastcin;
  int t, n;
  string s;
  cin >> t;
  while (t--) {
    cin >> n >> s;
    int l = 0;
    bool valid = true;
    while (l < n - 1 - l && (s[l] != 'R' || s[n - 1 - l] != 'L'))
      l++;
    if (l >= n - 1 - l) {
      cout << "1\n";
      continue;
    }
    for (int i = 0; i < l; i++)
      if (s[i] != 'L' || s[n - 1 - i] != 'R')
        valid = false;
    if (!valid) {
      cout << "0\n";
      continue;
    }
    s = string(s.begin() + l, s.end() - l);
    int m = s.size(), a = 0;
    vector<int> nl(m, m), nr(m, m), pl(m, -1), pr(m, -1);
    for (int i = m - 1; ~i; i--)
      nl[i] = s[i] == 'L' ? i : (i + 1 < m ? nl[i + 1] : m),
      nr[i] = s[i] == 'R' ? i : (i + 1 < m ? nr[i + 1] : m);
    for (int i = 0; i < m; i++)
      pl[i] = s[i] == 'L' ? i : (i ? pl[i - 1] : -1),
      pr[i] = s[i] == 'R' ? i : (i ? pr[i - 1] : -1);
    vector<vector<int>> q(m);
    for (int x = -1, y = m; x < y; x = nl[x + 1], y = pr[y - 1], a++) {
      for (int i = nr[x + 1]; i < nl[x + 1] && i <= pr[y - 1]; i = nr[i + 1])
        q[pr[y - 1]].push_back(i);
      for (int i = pl[y - 1]; i > pr[y - 1] && i >= nl[x + 1]; i = pl[i - 1])
        q[i].push_back(nl[x + 1]);
    }
    bs r, b;
    for (int i = 0; i < m - 1; i++) {
      if (s[i] == 'R')
        r[i] = 1;
      else
        b |= r;
      for (int j : q[i])
        if (j && !b[j])
          a++;
      b >>= 1;
    }
    cout << a << '\n';
  }
}
