/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 5010;
int n, a[2][N], sum, Max;

int main() {
  int T;
  cin >> T;
  while (T--) {
    cin >> n;
    Max = -1000000, sum = 0;
    for (int i = 1; i <= n; i++) {
      cin >> a[0][i];
    }
    for (int i = 1; i <= n; i++) {
      cin >> a[1][i];
      sum += max(a[0][i], a[1][i]);
      Max = max(Max, min(a[0][i], a[1][i]));
    }
    cout << sum + Max << "\n";
  }
}