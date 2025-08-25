/*
 * Problem URL : https://codeforces.com/problemset/problem/509/E
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;

const string VW = "IEAOUY";
bool is_vw[256];

signed main() {
  for (int i = 0; i < VW.size(); ++i) {
    is_vw[VW[i]] = true;
  }
  ios::sync_with_stdio(false);
  string S;
  cin >> S;
  vector<int> pvw(S.size() + 1);
  for (int i = 0; i < S.size(); ++i) {
    pvw[i + 1] = pvw[i] + is_vw[S[i]];
  }
  double ans = 0;
  int64_t sum = 0;
  for (int l = 1; l <= S.size(); ++l) {
    sum += pvw[S.size() - l + 1] - pvw[l - 1];
    ans += 1.0 * sum / l;
  }
  cout << fixed << setprecision(9) << ans << endl;
  return 0;
}
