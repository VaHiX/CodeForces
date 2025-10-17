/*
 * Problem URL : https://codeforces.com/problemset/problem/341/E
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>
using namespace std;
inline int lowbit(int x) { return x & -x; }
int lb[1000010];
struct Number {
  int x, ind;
  bool operator<(const Number &ano) const { return lb[x] > lb[ano.x]; }
} a[1010], nw[5];
int sz = 0;
priority_queue<Number> pq;
vector<pair<int, int>> ans;
inline void Work(Number &u, Number &v) {
  if (u.x > v.x)
    swap(u, v);
  ans.push_back({u.ind, v.ind});
  v.x -= u.x, u.x += u.x;
}
inline void Merge(Number &u, Number &v, Number &w) {
  int l = lb[v.x];
  while (lb[u.x] != l && lb[w.x] != l)
    Work(u, w);
  if (lb[w.x] != l)
    swap(u, w);
  Work(v, w);
}
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= 1000000; i++)
    lb[i] = lowbit(i);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i].x), a[i].ind = i;
  random_shuffle(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++)
    pq.push(a[i]);
  while (!pq.empty()) {
    Number u = pq.top();
    pq.pop();
    if (u.x == 0)
      continue;
    if (sz <= 1)
      nw[++sz] = u;
    else {
      Number v = nw[2];
      Merge(nw[1], v, u);
      pq.push(u), pq.push(v);
      sz--;
    }
  }
  if (sz <= 1) {
    printf("-1\n");
    return 0;
  }
  printf("%d\n", ans.size());
  for (auto p : ans)
    printf("%d %d\n", p.first, p.second);
  return 0;
}
