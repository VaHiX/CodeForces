/*
 * Problem URL : https://codeforces.com/problemset/problem/2066/A
 * Submit Date : 2025-08-20
 */

#include <bits/stdc++.h>
using namespace std;
// #define endl '\n'
typedef long long LL;
const int MAXN = 2e5 + 5;
int n, x[MAXN];
bool vis[MAXN];
signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; ++i)
      vis[i] = 0;
    for (int i = 1; i <= n; ++i) {
      cin >> x[i], vis[x[i]] = 1;
    }
    int a, b;
    for (int i = 1; i <= n; ++i) {
      if (!vis[i]) {
        cout << "? " << i << ' ' << (i == 1 ? 2 : 1) << endl;
        int res;
        cin >> res;
        if (res == 0)
          cout << "! A" << endl;
        else
          cout << "! B" << endl;
        goto end;
      }
    }
    for (int i = 1; i <= n; ++i) {
      if (x[i] == 1)
        a = i;
      if (x[i] == n)
        b = i;
    }
    cout << "? " << a << ' ' << b << endl;
    int A;
    cin >> A;
    cout << "? " << b << ' ' << a << endl;
    int B;
    cin >> B;
    if (A < n - 1 || B < n - 1)
      cout << "! A" << endl;
    else
      cout << "! B" << endl;
  end:;
  }
  return 0;
}