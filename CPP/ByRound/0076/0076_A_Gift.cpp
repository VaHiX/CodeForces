/*
 * Problem URL : https://codeforces.com/problemset/problem/76/A
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
#define ll long long
#define N 210
#define M 50010
using namespace std;
const ll inf = 0x7fffffffffffffffll;
int n, m, x, y;
int top, stk[M], dad[N];
ll G, S, g, s, fin = inf;
struct nd {
  int x, y;
  ll g, s;
} e[M];
inline bool cmp(const nd &a, const nd &b) { return a.g < b.g; }
inline int find(int x) { return x == dad[x] ? x : dad[x] = find(dad[x]); }
inline void Sort() {
  for (int i = top; i > 1; i--)
    if (e[stk[i]].s < e[stk[i - 1]].s)
      swap(stk[i], stk[i - 1]);
}
inline void Krus(int now) {
  int cnt = 0;
  ll ans = 0;
  for (int i = 1; i <= n; i++)
    dad[i] = i;
  for (int i = 1; i <= top; i++) {
    int x = e[stk[i]].x, y = e[stk[i]].y;
    ll s = e[stk[i]].s;
    x = find(x), y = find(y);
    if (x != y)
      ans = max(ans, s), dad[x] = y, stk[++cnt] = stk[i];
    if (cnt == n - 1) {
      fin = min(fin, G * e[now].g + S * ans);
      break;
    }
  }
  top = cnt;
}
int main() {
  scanf("%d %d %lld %lld", &n, &m, &G, &S);
  for (int i = 1; i <= m; i++)
    scanf("%d %d %lld %lld", &x, &y, &g, &s), e[i] = {x, y, g, s};
  sort(e + 1, e + 1 + m, cmp);
  for (int i = 1; i <= m; i++) {
    stk[++top] = i, Sort();
    Krus(i);
  }
  printf("%lld\n", fin == inf ? -1 : fin);
  return 0;
}
