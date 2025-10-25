/*
 * Problem URL : https://codeforces.com/problemset/problem/2/B
 * Submit Date : 2025-08-09
 */

#include <bits/stdc++.h>

#include <iostream>
#define tfseet                                                                 \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(NULL);                                                               \
  cout.tie(NULL)
#define pp push_back
#define ff first
#define ss second
#define ret return
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define ll long long
#define ull unsigned long long
#define ld long double
#define uld unsigned long double
using namespace std;
void printendl(ll t) {
  if (t)
    cout << "\n";
  ret;
}

int G2[1002][1002], G5[1002][1002];
pair<int, int> par[1002][1002];

int main() {
  tfseet;
  int n, xz, yz;
  bool ok = 0;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      int x;
      cin >> x;
      if (x == 0) {
        ok = 1;
        xz = i;
        yz = j;
        continue;
      }
      while (x % 2 == 0) {
        G2[i][j]++;
        x /= 2;
      }
      while (x % 5 == 0) {
        G5[i][j]++;
        x /= 5;
      }
    }
  }
  for (int i = 2; i <= n; i++) {
    G2[1][i] += G2[1][i - 1];
    G5[1][i] += G5[1][i - 1];
    G2[i][1] += G2[i - 1][1];
    G5[i][1] += G5[i - 1][1];
    par[1][i] = {1, i - 1};
    par[i][1] = {i - 1, 1};
  }
  for (int i = 2; i <= n; i++) {
    for (int j = 2; j <= n; j++) {
      int f1 = 0, f2 = 0, s1 = 0, s2 = 0;
      f1 = G2[i][j] + G2[i][j - 1];
      f2 = G2[i][j] + G2[i - 1][j];
      s1 = G5[i][j] + G5[i][j - 1];
      s2 = G5[i][j] + G5[i - 1][j];
      G2[i][j] = min(f1, f2);
      G5[i][j] = min(s1, s2);
    }
  }
  int a = G2[n][n], b = G5[n][n];
  if (min(a, b) > 1 && ok) {
    cout << 1 << endl;
    for (int i = 1; i < xz; i++)
      cout << 'D';
    for (int j = 1; j < yz; j++)
      cout << 'R';
    for (int i = xz; i < n; i++)
      cout << 'D';
    for (int j = yz; j < n; j++)
      cout << 'R';
    ret 0;
  }
  if (a <= b) {
    for (int i = 2; i <= n; i++) {
      for (int j = 2; j <= n; j++) {
        int f1 = 0, f2 = 0;
        f1 = G2[i][j] + G2[i][j - 1];
        f2 = G2[i][j] + G2[i - 1][j];
        if (f1 <= f2)
          par[i][j] = {i, j - 1};
        else
          par[i][j] = {i - 1, j};
      }
    }
  } else {
    for (int i = 2; i <= n; i++) {
      for (int j = 2; j <= n; j++) {
        int s1 = 0, s2 = 0;
        s1 = G5[i][j] + G5[i][j - 1];
        s2 = G5[i][j] + G5[i - 1][j];
        if (s1 <= s2)
          par[i][j] = {i, j - 1};
        else
          par[i][j] = {i - 1, j};
      }
    }
  }

  vector<char> v;
  int x = n, y = n;
  while (x != 1 || y != 1) {
    int tx = par[x][y].first, ty = par[x][y].second;
    if (x - tx < 0)
      v.pp('U');
    else if (x - tx > 0)
      v.pp('D');
    else if (y - ty > 0)
      v.pp('R');
    else if (y - ty < 0)
      v.pp('L');
    x = tx;
    y = ty;
  }
  cout << min(a, b) << endl;
  reverse(all(v));
  for (auto x : v)
    cout << x;
  return 0;
}
