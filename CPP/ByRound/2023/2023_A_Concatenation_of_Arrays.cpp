/*
 * Problem URL : https://codeforces.com/problemset/problem/2023/A
 * Submit Date : 2025-08-20
 */

#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);

    for (auto &[i, j] : a)
      cin >> i >> j;

    sort(a.begin(), a.end(), [](auto x, auto y) {
      return x.first + x.second < y.first + y.second;
    });

    for (auto [i, j] : a)
      cout << i << " " << j << " ";
    cout << endl;
  }
}
