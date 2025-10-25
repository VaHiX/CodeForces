/*
 * Problem URL : https://codeforces.com/contest/852/problem/B
 * Submit Date : 2025-09-13
 */

#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;
#define maxn 110
typedef long long ll;
const ll mod = (1e9) + 7;
int m;
struct mxt {
  ll M[maxn];
  mxt() { memset(M, 0, sizeof(mxt)); }
  void init() { M[0] = 1; }
};
mxt mutil(mxt x1, mxt x2) {
  mxt x3;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      int cnt = (i + j) % m;
      x3.M[cnt] += x1.M[i] * x2.M[j];
      x3.M[cnt] %= mod;
    }
  }
  return x3;
}
mxt mxt_fpow(mxt x, ll p) {
  mxt ans;
  ans.init();
  while (p) {
    if (p % 2 == 1) {
      ans = mutil(ans, x);
    }
    x = mutil(x, x);
    p /= 2;
  }
  return ans;
}
int a[1000010];
int main() {
  int n, l;
  scanf("%d%d%d", &n, &l, &m);
  mxt st, md, ed;
  for (int i = 1; i <= n; i++) {
    int x;
    scanf("%d", &x);
    st.M[(x % m)]++;
  }
  for (int i = 1; i <= n; i++) {
    int x;
    scanf("%d", &x);
    md.M[(x % m)]++;
    a[i] = x;
  }
  for (int i = 1; i <= n; i++) {
    int x;
    scanf("%d", &x);
    ed.M[(a[i] + x) % m]++;
  }
  mxt ans;
  if (l > 2) {
    ans = mxt_fpow(md, l - 2);
    ans = mutil(ans, st);
    ans = mutil(ans, ed);
  } else {
    ans = mutil(st, ed);
  }
  ll Ans = ans.M[0];
  printf("%lld\n", Ans);
  return 0;
}