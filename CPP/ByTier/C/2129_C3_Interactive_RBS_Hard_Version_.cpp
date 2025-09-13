/*
 * Problem URL : https://codeforces.com/problemset/problem/2129/C3
 * Submit Date : 2025-08-08
 */

#include <bits/stdc++.h>
using namespace std;
int t, n, f[1005],
    sz[15] = {0, 3, 8, 15, 26, 41, 62, 93, 136, 197, 284, 407, 582, 829},
    ln[15] = {0, 1, 2, 3, 5, 7, 10, 15, 21, 30, 43, 61, 87, 123}, x, l, r, mid,
    p, L, F;
vector<int> q;
void query(vector<int> a) {
  int L = a.size(), S = 0;
  cout << "? " << sz[L] << " ";
  for (int i = 0; i < L; i++) {
    cout << p << " ";
    for (int j = 0; j < ln[i + 1]; j++)
      cout << p << " " << a[i] << " ";
  }
  cout << endl;
  cin >> x;
  for (int i = L - 1; i >= 0; i--) {
    if (x >= ln[i + 1] * (ln[i + 1] + 1) / 2) {
      f[a[i]] = 1;
      x -= ln[i + 1] * (ln[i + 1] + 1) / 2;
    } else
      f[a[i]] = 0;
  }
}
signed main() {
  cin >> t;
  while (t--) {
    cin >> n;
    F = 0;
    cout << "? " << n << " ";
    for (int i = 1; i <= n; i++)
      cout << i << " ";
    cout << endl;
    cin >> x;
    if (x == 0)
      p = n;
    else {
      l = 1, r = n;
      while (l <= r) {
        mid = (l + r) >> 1;
        cout << "? " << mid << " ";
        for (int i = 1; i <= mid; i++)
          cout << i << " ";
        cout << endl;
        cin >> x;
        if (x == 0)
          l = mid + 1;
        else {
          p = mid;
          r = mid - 1;
        }
      }
      p--;
    }
    for (int i = 1; i <= n; i += 13) {
      q.clear();
      for (int j = i; j <= min(i + 12, n); j++)
        q.push_back(j);
      query(q);
    }
    cout << "! ";
    for (int i = 1; i <= n; i++) {
      if (f[i] == 0)
        cout << "(";
      else
        cout << ")";
    }
    cout << endl;
  }
  return 0;
}