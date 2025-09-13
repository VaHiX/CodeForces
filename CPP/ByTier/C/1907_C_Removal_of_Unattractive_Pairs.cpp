/*
 * Problem URL : https://codeforces.com/problemset/problem/1907/C
 * Submit Date : 2025-08-15
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    string s;
    cin >> s;
    map<char, int> m;
    int mx = 0;
    for (auto x : s) {
      m[x]++;
      mx = max(mx, m[x]);
    }
    cout << max(n % 2, 2 * mx - n) << endl;
  }
}