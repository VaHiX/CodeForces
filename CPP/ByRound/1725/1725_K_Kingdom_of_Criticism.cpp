/*
 * Problem URL : https://codeforces.com/contest/1725/problem/K
 * Submit Date : 2025-09-08
 */

#include <bits/stdc++.h>

using namespace std;
const int MAXN = 400400;
int n, a[2 * MAXN], actual[2 * MAXN], q, cnt;

int uf[2 * MAXN];
int find(int x) { return uf[x] ? uf[x] = find(uf[x]) : x; }
void join(int x, int y) {
  if ((x = find(x)) == (y = find(y)))
    return;
  uf[y] = x;
}

void mapAll(vector<int> &v, int x, map<int, int> &m) {
  if (v.empty())
    return;
  auto it = m.lower_bound(x);
  if (it == m.end() || it->first != x) {
    int rep = v.back();
    it = m.insert(it, make_pair(x, rep));
    a[rep] = x;
  }
  for (const int &x : v)
    join(it->second, x);
}

void upd(int i, map<int, int> &m) {
  auto it = m.lower_bound(a[i]);
  if (it == m.end() || it->first != a[i])
    it = m.insert(it, make_pair(a[i], i));
  join(it->second, i);
}

int main() {
  scanf("%d", &n);
  map<int, int> m;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]), actual[i] = i;
    upd(i, m);
  }
  cnt = n;

  for (scanf("%d", &q); q--;) {
    int op, l, r, k, w;
    scanf("%d", &op);
    if (op == 1) {
      scanf("%d %d", &k, &w);
      actual[k] = ++cnt;
      a[actual[k]] = w;
      upd(actual[k], m);
    } else if (op == 2) {
      scanf("%d", &k);
      printf("%d\n", a[find(actual[k])]);
    } else if (op == 3) {
      scanf("%d %d", &l, &r);
      vector<int> aa, bb;
      for (auto it = m.lower_bound(l); it != m.upper_bound(r); ++it)
        (it->first * 2 < (l + r) ? aa : bb).push_back(it->second);
      m.erase(m.lower_bound(l), m.upper_bound(r));

      mapAll(aa, l - 1, m);
      mapAll(bb, r + 1, m);
    }
  }
}
