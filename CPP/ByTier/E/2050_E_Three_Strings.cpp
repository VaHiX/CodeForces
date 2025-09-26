/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
char a[N], b[N], c[N * 2];
int f[N][N];
int main() {
  int t;
  cin >> t;
  while (t--) {
    cin >> a + 1 >> b + 1 >> c + 1;
    int la = strlen(a + 1), lb = strlen(b + 1), mx = 0;
    for (int i = 1; i <= la + lb; i++) {
      for (int j = max(0, i - lb); j <= la && j <= i; j++) {
        f[j][i - j] = 0;
        if (j > 0)
          f[j][i - j] = max(f[j][i - j], f[j - 1][i - j] + (a[j] == c[i]));
        if (i - j > 0)
          f[j][i - j] = max(f[j][i - j], f[j][i - j - 1] + (b[i - j] == c[i]));
      }
    }
    cout << la + lb - f[la][lb] << endl;
  }
  return 0;
}