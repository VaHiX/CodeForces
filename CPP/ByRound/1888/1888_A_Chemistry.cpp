/*
 * Problem URL : https://codeforces.com/problemset/problem/1888/A
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
  int k;
  cin >> k;
  while (k--) {
    int n, q;
    cin >> n >> q;
    string a;
    cin >> a;
    int cnt = 0;
    if (n - q == 1) {
      cout << "YES" << endl;
      continue;
    }
    map<char, int> mp;
    for (int i = 0; i < n; i++)
      mp[a[i]]++;
    for (auto it : mp) {
      if (it.second % 2 != 0)
        cnt++;
    }
    if (cnt <= q + 1)
      cout << "YES" << endl;
    else
      cout << "NO" << endl;
  }
  return 0;
}