/*
 * Problem URL : https://codeforces.com/problemset/problem/2084/C
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2e5 + 3;
int T, n, a[N], b[N], f, p[N], k;
void jh(int x, int y) {
  swap(p[a[x]], p[a[y]]);
  swap(a[x], a[y]);
  swap(b[x], b[y]);
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      p[a[i]] = i;
    }
    f = 0;
    for (int i = 1; i <= n; i++) {
      cin >> b[i];
      if (a[i] == b[i])
        f++, k = i;
    }
    for (int i = 1; i <= n; i++) {
      if (b[p[b[i]]] != a[i]) {
        f = 114514;
        break;
      }
    }
    if (f != n % 2) {
      cout << "-1\n";
      continue;
    }
    vector<pair<int, int>> s;
    if (f && k != n / 2 + 1) {
      s.push_back({k, n / 2 + 1});
      jh(k, n / 2 + 1);
    }
    for (int i = 1; i <= n / 2; i++) {
      if (a[i] != b[n - i + 1]) {
        s.push_back({p[b[i]], n - i + 1});
        jh(p[b[i]], n - i + 1);
      }
    }
    cout << s.size() << '\n';
    for (auto i : s)
      cout << i.first << ' ' << i.second << '\n';
  }
}