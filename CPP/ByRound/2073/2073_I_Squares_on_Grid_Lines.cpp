/*
 * Problem URL : https://codeforces.com/contest/2073/problem/I
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 9000013;
ll pf[N], del[N], ban[N];
void solve() {
  int n, q;
  cin >> n >> q;
  for (int i = 0; i < n; i++)
    for (int j = 0; j + i < n; j++)
      ban[2 * (i * i + j * j)] = 1;
  for (int cnt, j = 2; j <= n; j += 2)
    cnt = (n - j + 1) * (n - j + 1), pf[(j - 2) * (j - 2)] += cnt,
    pf[j * j] -= cnt;
  for (int i = 1; i <= n; i++)
    for (int j = i; j <= n; j += 2) {
      int cnt = (n - j + 1) * (n - j + 1);
      if (j == i)
        pf[j * j] += cnt * 2, del[j * j] += cnt, pf[j * j * 2] -= cnt * 2,
            del[j * j * 2] -= cnt;
      else
        pf[(j - 2) * (j - 2) + i * i] += cnt * 2, pf[j * j + i * i] -= cnt * 2,
            del[(j - 2) * (j - 2) + i * i] += cnt * 2;
    }
  for (int i = 1; i < N; i++)
    pf[i] += pf[i - 1];
  while (q--) {
    string s;
    cin >> s;
    int p = floor((stod(s) + 0.001) * 2);
    if (s[s.size() - 1] == '0' &&
        (s[s.size() - 2] == '5' || (s[s.size() - 2]) == '0')) {
      if (ban[p])
        cout << -1 << '\n';
      else
        cout << pf[p] - del[p] << '\n';
    } else
      cout << pf[p] << '\n';
  }
}

int main() {
  ios::sync_with_stdio(false);
  solve();
}