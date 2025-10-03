/*
 * Problem URL : https://codeforces.com/contest/790/problem/A
 * Submit Date : 2025-09-04
 */

#include <iostream>
using namespace std;

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, k;
  cin >> n >> k;
  string ans[n];
  for (int i = 0; i < n; i++) {
    ans[i] = "00";
    ans[i][0] = i / 26 + 'A';
    ans[i][1] = i % 26 + 'a';
  }
  string s;
  for (int i = 0; i <= n - k; i++) {
    cin >> s;
    if (s == "NO")
      ans[i + k - 1] = ans[i];
  }
  for (string i : ans)
    cout << i << ' ';
  return 0;
}