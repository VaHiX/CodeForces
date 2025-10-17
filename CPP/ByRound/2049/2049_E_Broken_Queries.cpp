/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;

int qry(int l, int r, bool rev = 0, int n = 0) {
  if (rev) {
    int t = n - l;
    l = n - r;
    r = t;
  }
  cout << "? " << l + 1 << ' ' << r << endl;
  cin >> r;
  return r;
}

void solve() {
  int n;
  cin >> n;
  int a = qry(0, n / 4);
  int b = qry(n / 4, n / 2);
  bool kSmall = 1;
  bool firstHalf = 1;
  if (a == b)
    firstHalf = 0;
  int bs = 0;
  if (qry(0, n / 2, firstHalf, n) == 0)
    kSmall = 0;
  if (kSmall) {
    for (int k = n / 4; k; k /= 2)
      if (qry(0, bs + k, firstHalf, n) == 0)
        bs += k;
  } else {
    bs = n / 2 - 1;
    for (int k = n / 4; k; k /= 2)
      if (qry(0, bs + k, 1 - firstHalf, n) == 1)
        bs += k;
  }
  cout << "! " << bs + 1 << endl;
}

int main() {
  int T = 1;
  cin >> T;
  while (T--)
    solve();
  return 0;
}