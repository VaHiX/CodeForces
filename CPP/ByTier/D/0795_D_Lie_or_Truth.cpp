/*
 * Problem URL : https://codeforces.com/contest/795/problem/D
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;

signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int a, l, r;
  cin >> a >> l >> r;
  vector<int> v(a);
  vector<int> v1(a);
  for (int i = 0; i < a; i++) {
    cin >> v[i];
  }
  for (int i = 0; i < a; i++) {
    cin >> v1[i];
  }
  for (int i = 0; i < a; i++) {
    if (i < l - 1 || i > r - 1) {
      if (v[i] != v1[i]) {
        cout << "LIE";
        return 0;
      }
    }
  }
  cout << "TRUTH";
}
