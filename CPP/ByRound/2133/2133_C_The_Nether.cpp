/*
 * Problem URL : https://codeforces.com/contest/2133/problem/C
 * Submit Date : 2025-08-30
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int n;
vector<int> a[N], res;

void work() {
  scanf("%d", &n);
  string p = "";
  res.clear();
  for (int i = 1; i <= n; i++)
    a[i].clear(), p += to_string(i), p += ' ';
  int mx = 0;
  for (int i = 1, t; i <= n; i++) {
    cout << '?' << ' ' << i << ' ' << n << ' ' << p << endl;
    fflush(stdout);
    scanf("%d", &t);
    a[t].push_back(i);
    mx = max(mx, t);
  }

  res.push_back(a[mx][0]);

  for (int i = mx - 1; i; i--) {
    int t = res.back(), p;
    for (auto j : a[i]) {
      cout << '?' << ' ' << t << ' ' << 2 << ' ' << t << ' ' << j << endl;
      fflush(stdout);
      scanf("%d", &p);
      if (p != 1) {
        res.push_back(j);
        break;
      }
    }
  }

  printf("! %d ", mx);
  for (auto i : res)
    printf("%d ", i);
  cout << endl, fflush(stdout);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--)
    work();
  return 0;
}