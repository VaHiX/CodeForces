/*
 * Problem URL : https://codeforces.com/problemset/problem/863/C
 * Submit Date : 2025-08-19
 */

#include <bits\stdc++.h>
using namespace std;
typedef long long int LL;
const int INF = 1e9;
LL k, x, y, i, l, a[179], b[179];
pair<LL, LL> d[3][3], p[179], *q, f;
int main() {
  cin >> k >> x >> y;
  x--;
  y--;
  p[0] = {x, y};
  a[1] = (3 + x - y) % 3 == 1;
  b[1] = (3 + x - y) % 3 == 2;
  for (i = 0; i < 9; i++) {
    cin >> x;
    d[i / 3][i % 3].first = x - 1;
  }
  for (i = 0; i < 9; i++) {
    cin >> x;
    d[i / 3][i % 3].second = x - 1;
  }
  for (i = 1;
       q = find(p, p + i, f = d[p[i - 1].first][p[i - 1].second]), q == p + i;
       i++) {
    a[i + 1] = a[i] + ((3 + f.first - f.second) % 3 == 1);
    b[i + 1] = b[i] + ((3 + f.first - f.second) % 3 == 2);
    p[i] = f;
  }
  l = q - p;
  if (k <= i) {
    cout << a[k] << " " << b[k];
    return 0;
  }
  k -= l;
  x = k / (i - l);
  cout << x * (a[i] - a[l]) + a[l + k % (i - l)] << " "
       << x * (b[i] - b[l]) + b[l + k % (i - l)] << endl;
}
