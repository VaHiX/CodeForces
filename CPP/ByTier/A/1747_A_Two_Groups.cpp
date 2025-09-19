/*
 * Problem URL : https://codeforces.com/problemset/problem/1747/A
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    int a;
    long long int c = 0;
    for (int i = 0; i < n; i++) {
      cin >> a;
      c += a;
    }
    cout << abs(c) << endl;
  }
}