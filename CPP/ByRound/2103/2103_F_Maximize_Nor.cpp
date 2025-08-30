/*
 * Problem URL : https://codeforces.com/problemset/problem/2103/F
 * Submit Date : 2025-08-18
 */

#include <bits/stdc++.h>
using namespace std;
#define lowbit(x) (x & -x)
#define endl '\n'

const int Maxn = 17;
const int maxn = 1e5 + 10;
int t, n, k;
int a[maxn];
int ans[maxn];
bool flag[maxn], use[maxn];
int maxx[maxn];

void dfs(int l, int r) {
  if (l == r) {
    ans[l] = max(ans[l], a[l]);
    return;
  }
  int mid = l + r >> 1;
  for (int i = mid; i >= l; i--) {
    bool fflag = false;
    for (int j = 0; j < k; j++) {
      if ((a[i] >> j & 1) && !flag[j]) {
        flag[j] = true;
        fflag = true;
      }
    }
    if (i == mid || fflag) {
      use[i] = true;
    }
  }
  for (int i = mid; i >= l; i--) {
    if (!use[i] && !use[i + 1] && !use[i + 2]) {
      maxx[i] = maxx[i + 2];
    } else {
      int p = a[i];
      for (int j = i + 1; j <= r; j++) {
        p = ((1 << k) - 1) ^ (p | a[j]);
        if (j > mid) {
          maxx[i] = max(maxx[i], p);
          maxx[j] = max(maxx[j], p);
        }
      }
    }
  }
  for (int i = r - 1; i > mid; i--) {
    maxx[i] = max(maxx[i], maxx[i + 1]);
  }
  for (int i = l + 1; i <= mid; i++) {
    maxx[i] = max(maxx[i], maxx[i - 1]);
  }
  for (int i = l; i <= r; i++) {
    ans[i] = max(ans[i], maxx[i]);
    use[i] = false;
    maxx[i] = 0;
  }
  for (int i = 0; i < k; i++) {
    flag[i] = false;
  }
  dfs(l, mid);
  dfs(mid + 1, r);
}

signed main() {
  //	freopen(".in","r",stdin);
  //	freopen(".out","w",stdout);
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      ans[i] = 0;
    }
    dfs(1, n);
    for (int i = 1; i <= n; i++) {
      cout << ans[i] << " \n"[i == n];
    }
  }
  return 0;
}
/*

*/