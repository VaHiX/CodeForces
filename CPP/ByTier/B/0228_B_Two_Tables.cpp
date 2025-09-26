/*
 * Problem URL : https://codeforces.com/problemset/problem/228/B
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  int na, ma, nb, mb;
  cin >> na >> ma;
  int a[na][ma];
  for (int i = 0; i < na; i++)
    for (int j = 0; j < ma; j++) {
      char z;
      cin >> z;
      a[i][j] = z - '0';
    }
  cin >> nb >> mb;
  int b[nb][mb];
  for (int i = 0; i < nb; i++)
    for (int j = 0; j < mb; j++) {
      char z;
      cin >> z;
      b[i][j] = z - '0';
    }
  int x = 0;
  int y = 0;
  int v = 0;
  for (int xi = -50; xi <= 50; xi++)
    for (int yj = -50; yj <= 50; yj++) {
      int tv = 0;
      for (int i = (xi < 0 ? -xi : 0); i < na && i + xi < nb; i++) {
        for (int j = (yj < 0 ? -yj : 0); j < ma && j + yj < mb; j++)
          tv += a[i][j] * b[i + xi][j + yj];
      }
      if (tv > v) {
        x = xi;
        y = yj;
        v = tv;
      }
    }
  cout << x << " " << y << endl;
  return 0;
}
