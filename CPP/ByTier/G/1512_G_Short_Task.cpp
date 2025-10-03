/*
 * Problem URL : https://codeforces.com/contest/1512/problem/G
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;

const int Max = 1e7;
int t, n, yz[Max], ans[Max];

int main() {
  for (int i = 1; i <= Max; ++i) {
    for (int j = i; j <= Max; j += i)
      yz[j] += i;
    if (yz[i] <= Max && !ans[yz[i]])
      ans[yz[i]] = i;
  }
  cin >> t;
  while (t--) {
    cin >> n;
    cout << (ans[n] == 0 ? -1 : ans[n]) << endl;
  }
  return 0;
}