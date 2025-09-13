/*
 * Problem URL : https://codeforces.com/problemset/problem/2064/E
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define M 998244353
#define N 400000

int i, j, k, n, m, T, c[N + 50], pos[N + 50], l[N + 50], r[N + 50], sz[N + 50],
    fa[N + 50];
ll res;

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void fuck(int x) {
  int j, k = find(x);
  res = res * sz[k] % M;
  sz[k]--;
  r[l[x]] = r[x];
  l[r[x]] = l[x];
  if (!sz[k]) {
    j = l[x];
    k = r[x];
    if (c[j] == c[k]) {
      j = find(j);
      k = find(k);
      fa[k] = j;
      sz[j] += sz[k];
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> T;
  while (T--) {
    cin >> n;
    c[n + 1] = 0;
    for (i = 1; i <= n; i++) {
      cin >> k;
      pos[k] = i;
      l[i] = i - 1;
      r[i] = i + 1;
      fa[i] = i;
      sz[i] = 1;
    }
    for (i = 1; i <= n; i++)
      cin >> c[i];
    for (i = 2; i <= n; i++)
      if (c[i] == c[i - 1]) {
        fa[i] = find(i - 1);
        sz[find(i)]++;
      }
    res = 1;
    for (i = 1; i <= n; i++)
      fuck(pos[i]);
    cout << res << '\n';
  }
}