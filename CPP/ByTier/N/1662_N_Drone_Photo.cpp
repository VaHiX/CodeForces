/*
 * Problem URL : https://codeforces.com/contest/1662/problem/N
 * Submit Date : 2025-09-08
 */

#include <iostream>
using namespace std;
long long nrd, t, drp, drb;
int n, i, j, v[1501][1501];
struct pozitie {
  int l, c;
};
pozitie poz[2250001];
int l[1501], c[1501];
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cin >> n;
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      cin >> v[i][j];
      poz[v[i][j]] = {i, j};
    }
  }
  for (i = 1; i <= n * n; i++) {
    t += l[poz[i].l] * c[poz[i].c];
    l[poz[i].l]++;
    c[poz[i].c]++;
  }
  nrd = 1ll * n * n * (n - 1) * (n - 1) / 4;
  /// drb+drp=nrd
  /// 1*drb+2*drp=t => drb=t-2*drp => t-drp=nrd => t-nrd=drp
  /// drb=nrd-drp
  drp = t - nrd;
  drb = nrd - drp;
  cout << drb;
  return 0;
}
