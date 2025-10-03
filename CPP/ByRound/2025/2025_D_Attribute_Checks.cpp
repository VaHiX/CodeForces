/*
 * Problem URL : https://codeforces.com/contest/2025/problem/D
 * Submit Date : 2025-09-10
 */

#include <bits/stdc++.h>
using namespace std;

int n, m, sum;
int c[2000001], f[2000001];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> m;
  for (int j = 1; j <= n; j++) {
    int x;
    cin >> x;
    if (x > 0 && sum >= x)
      c[x]++, c[sum + 1]--;
    if (x < 0 && sum >= -x)
      c[0]++, c[sum + x + 1]--;
    if (x == 0) {
      sum++;
      for (int i = 0; i <= sum; i++) {
        if (i != 0)
          c[i] += c[i - 1];
        f[i] += c[i];
      }
      for (int i = sum; i >= 1; i--)
        f[i] = max(f[i], f[i - 1]);
      for (int i = 0; i <= sum; i++)
        c[i] = 0;
    }
  }
  for (int i = 0; i <= sum; i++) {
    if (i != 0)
      c[i] += c[i - 1];
    if (i == 0)
      f[i] += c[i];
    else
      f[i] = max(f[i - 1], f[i] + c[i]);
  }
  cout << f[sum] << "\n";
}