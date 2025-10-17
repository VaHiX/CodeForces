/*
 * Problem URL : https://codeforces.com/contest/590/problem/A
 * Submit Date : 2025-09-04
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  ll n;
  cin >> n;
  string at(n, '-'), ax(n, '-');
  for (auto &c : at)
    cin >> c;
  ax[0] = at[0];
  ax.back() = at.back();
  for (ll i = 1; i < n; i++)
    if (at[i - 1] == at[i])
      ax[i - 1] = ax[i] = at[i];
  vector<vector<ll>> rg;
  for (ll i = 0; i < n; i++) {
    if (ax[i] != '-') {
      ll j = i;
      while (j < n - 1 && ax[j + 1] != '-')
        j++;
      rg.push_back({i, j});
      i = j;
    }
  }
  ll re = 0;
  for (ll i = 0; i < rg.size() - 1; i++) {
    re = max(re, (rg[i + 1][0] - rg[i][1]) / 2);
    for (ll j = rg[i][1] + 1; j < rg[i + 1][0]; j++)
      if (j < (rg[i + 1][0] - rg[i][1] + 1) / 2 + rg[i][1])
        ax[j] = ax[rg[i][1]];
      else
        ax[j] = ax[rg[i + 1][0]];
  }
  cout << re << "\n";
  for (auto c : ax)
    cout << c << " ";
}