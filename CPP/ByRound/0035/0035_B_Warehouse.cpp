/*
 * Problem URL : https://codeforces.com/problemset/problem/35/B
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  ifstream cin("input.txt");
  ofstream cout("output.txt");
  int n, m, k;
  cin >> n >> m >> k;
  vector<string> a(n * m, "");
  while (k--) {
    string s;
    cin >> s;
    string z;
    if (s == "+1") {
      int i, j;
      cin >> i >> j >> z;
      i--;
      j--;
      for (int l = i * m + j; l < n * m; l++) {
        if (a[l] == "") {
          a[l] = z;
          break;
        }
      }
    } else {
      cin >> z;
      int l = -1;
      for (int i = 0; i < n * m; i++) {
        if (a[i] == z)
          l = i, a[i] = "";
      }
      if (l >= 0)
        cout << l / m + 1 << " " << l % m + 1 << "\n";
      else
        cout << "-1 -1\n";
    }
  }
  cin.close();
  cout.close();
}