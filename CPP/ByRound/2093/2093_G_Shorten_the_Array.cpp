/*
 * Problem URL : https://codeforces.com/problemset/problem/2093/G
 * Submit Date : 2025-08-21
 */

#include <algorithm>
#include <cstdio>
using namespace std;
int a[200005];
int nxt[6000005][2], id;
int val[6000005];
void ins(int x, int p) {
  int now = 0;
  for (int i = 29; i >= 0; i--) {
    int t = ((x >> i) & 1);
    if (!nxt[now][t])
      nxt[now][t] = ++id;
    now = nxt[now][t];
    val[now] = p;
  }
}
int query(int x, int k) {
  int now = 0, ret = 0;
  for (int i = 29; i >= 0; i--) {
    int t = ((x >> i) & 1);
    if (!(k & (1 << i))) {
      ret = max(ret, val[nxt[now][t ^ 1]]);
      now = nxt[now][t];
    } else
      now = nxt[now][t ^ 1];
    if (!now)
      return ret;
  }
  return max(ret, val[now]);
}
int main() {
  int t, n, k, l, ans;
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]);
    ans = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++) {
      ins(a[i], i);
      l = query(a[i], k);
      if (l)
        ans = min(ans, i - l + 1);
    }
    if (ans == 0x3f3f3f3f)
      ans = -1;
    printf("%d\n", ans);
    for (int i = 0; i <= id; i++) {
      nxt[i][0] = 0;
      nxt[i][1] = 0;
      val[i] = 0;
    }
    id = 0;
  }
  return 0;
}
