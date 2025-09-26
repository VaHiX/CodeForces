/*
 * Problem URL : https://codeforces.com/contest/1261/problem/A
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define per(i, a, b) for (int i = (b) - 1; i >= (a); --i)
#define pii pair<int, int>
using namespace std;
const int N = 2009;
char s[N];
pii ans[N];
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, k;
    scanf("%d%d", &n, &k);
    scanf("%s", s + 1);
    int l = 1, r = n, cnt = 0;
    while (l <= r) {
      while (s[l] == '(')
        ++l;
      while (s[r] == ')')
        --r;
      if (l > r)
        break;
      reverse(s + l, s + r + 1);
      ans[cnt++] = {l, r};
    }
    printf("%d\n", cnt + k - 1);
    rep(i, 0, cnt) { printf("%d %d\n", ans[i].first, ans[i].second); }
    rep(i, 1, k) printf("%d %d\n", 2 * i, n / 2 + i);
  }
}