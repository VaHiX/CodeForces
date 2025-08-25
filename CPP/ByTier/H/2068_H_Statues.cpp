/*
 * Problem URL : https://codeforces.com/problemset/problem/2068/H
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, a, b, d[51];
signed main() {
  cin >> n >> a >> b;
  int sum = a + b;
  for (int i = 1; i < n; i++)
    cin >> d[i], sum += d[i];
  if (sum & 1)
    puts("NO"), exit(0);
  if (sum - a - b < a + b)
    puts("NO"), exit(0);
  for (int i = 1; i < n; i++)
    if (sum - d[i] < d[i])
      puts("NO"), exit(0);
  puts("YES");
  cout << 0 << " " << 0 << endl;
  int tot = sum / 2 - a - b, x = 0, y = 0;
  for (int i = 1; i < n; i++) {
    if (d[i] <= tot) {
      tot -= d[i];
      y -= d[i];
    } else if (tot) {
      if (d[i] - tot > a) {
        x = tot + a;
        y += d[i] - tot - a;
      } else {
        x += d[i] - tot;
        y -= tot;
      }
      tot = 0;
    } else {
      if (x > a) {
        if (x - d[i] < a) {
          y += d[i] - (x - a);
          x = a;
        } else {
          x -= d[i];
        }
      } else if (x < a) {
        if (x + d[i] > a) {
          y += d[i] - (a - x);
          x = a;
        } else {
          x += d[i];
        }
      } else
        y += d[i];
    }
    cout << x << " " << y << endl;
  }
  return 0;
}