/*
 * Problem URL : https://codeforces.com/contest/2148/problem/F
 * Submit Date : 2025-09-13
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int n, L = 0;
    cin >> n;
    vector<vector<int>> a(n);
    for (int i = 0; i < n; i++) {
      int k;
      cin >> k;
      a[i].resize(k);
      for (int j = 0; j < k; j++)
        cin >> a[i][j];
      L = max(L, k);
    }

    vector<int> b;
    int cur = 0;
    while (cur < L) {
      int best = -1;
      for (int i = 0; i < n; i++) {
        if (a[i].size() <= cur)
          continue;
        if (best == -1 ||
            lexicographical_compare(a[i].begin() + cur, a[i].end(),
                                    a[best].begin() + cur, a[best].end()))
          best = i;
      }
      for (int k = cur; k < a[best].size(); k++)
        b.push_back(a[best][k]);
      cur = a[best].size();
    }

    for (int i = 0; i < b.size(); i++) {
      cout << b[i] << " ";
    }
    cout << "\n";
  }
}
