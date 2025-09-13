/*
 * Problem URL : https://codeforces.com/contest/2036/problem/E
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
using namespace std;
vector<int> a[100000];
string s;
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int n, k, q, i, j, vl, r, m, cl, cr;
  cin >> n >> k >> q;
  for (i = 0; i < n; i++) {
    for (j = 0; j < k; j++) {
      cin >> vl;
      a[j].push_back(vl);
    }
  }
  for (i = 1; i < n; i++) {
    for (j = 0; j < k; j++)
      a[j][i] |= a[j][i - 1];
  }
  for (; q > 0; q--) {
    cin >> m;
    cl = 0;
    cr = n;
    for (i = 0; i < m; i++) {
      cin >> r >> s >> vl;
      r--;
      if (s[0] == '<')
        cr = min(cr, (int)(lower_bound(a[r].begin(), a[r].end(), vl) -
                           a[r].begin()));
      else
        cl = max(cl, (int)(upper_bound(a[r].begin(), a[r].end(), vl) -
                           a[r].begin()));
    }
    if (cl < cr)
      cout << cl + 1 << '\n';
    else
      cout << "-1\n";
  }
}