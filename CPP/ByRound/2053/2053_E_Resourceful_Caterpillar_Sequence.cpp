/*
 * Problem URL : https://codeforces.com/problemset/problem/2053/E
 * Submit Date : 2025-08-24
 */

#include <stdio.h>
#include <vector>
using namespace std;
typedef long long ll;

vector<int> edge[200002];
int d[200002], b[200002];

ll solve(int n) {
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
    d[u]++, d[v]++;
  }
  int leaf = 0, bleaf = 0;
  for (int i = 1; i <= n; i++)
    if (d[i] == 1) {
      leaf++;
      int y = edge[i].front();
      if (d[y] != 1) {
        if (!b[y])
          bleaf++;
        b[y]++;
      }
    }
  ll ans = 1ll * leaf * (n - leaf);
  for (int i = 1; i <= n; i++)
    if (b[i])
      ans += 1ll * (n - leaf - bleaf) * (d[i] - b[i] - 1);
  return ans;
}

int main() {
  int _;
  scanf("%d", &_);
  while (_--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      edge[i].clear();
      d[i] = b[i] = 0;
    }
    printf("%lld\n", solve(n));
  }
}