// Problem: CF 2046 E2 - Cheops and a Contest (Hard Version)
// https://codeforces.com/contest/2046/problem/E2

/*
Code Purpose:
This code solves a complex competitive programming problem where Cheops wants to set up challenges for participants from different cities such that each city's participants solve strictly more problems than the previous city. The approach uses a technique of generating and filtering intervals for each city's capabilities to construct a valid set of problems.

Algorithms/Techniques:
- Problem modeling using intervals and coordinate compression.
- Sorting and searching for valid problem configurations.
- Greedy interval intersection logic.
- Binary search and coordinate compression.

Time Complexity: O(n log n + m log m)
Space Complexity: O(n + m)

*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

using namespace std;
const int N = 3e5 + 5;
typedef pair<int, int> pii;
int T, n, m, a[N], b[N], s[N], sc, ori[N], k[N], mn[N], mx[N], cnt, l[N], r[N],
    now, tot, d[N << 2], t[N << 2];
map<int, int> id;
pii v[N];
vector<int> q[N];
vector<pii> e[N];
int c[N];
void add(int v, int s = -1) {
  if (!~s) {
    now++;
    while (id.find(now) != id.end())
      now++;
    s = now;
  }
  d[++tot] = v, t[tot] = s;
}
int main() {
  cin >> T;
  while (T--) {
    scanf("%d%d", &n, &m);
    sc = cnt = tot = 0, now = -1;
    map<int, int> em;
    swap(em, id);
    for (int i = 1; i <= n; i++) {
      scanf("%d%d%d", &a[i], &b[i], &s[i]);
      if (!id[s[i]])
        id[s[i]] = ++sc, ori[sc] = s[i];
      s[i] = id[s[i]];
    }
    for (int i = 1; i <= sc; i++)
      l[i] = -1, r[i] = 2e9, e[i].clear();
    for (int i = 1; i <= m; i++) {
      scanf("%d", &k[i]), q[i].resize(k[i]);
      mn[i] = 2e9, mx[i] = -1;
      for (int j = 0; j < k[i]; j++)
        scanf("%d", &q[i][j]), mn[i] = min(mn[i], a[q[i][j]]),
                               mx[i] = max(mx[i], a[q[i][j]]);
    }
    for (int i = m, now = -1; i; i--) {
      if (i > 1 && mn[i] < mn[i - 1])
        add(mn[i]);
      if (mx[i] > now)
        add(mx[i] + 1), now = mx[i];
      if (i > 2 && now >= mn[i - 2])
        goto E;
    }
    add(mn[1]);
    for (int i = m; i > 1; i--)
      if (mx[i] >= mn[i - 1]) {
        if (mn[i - 1] < mx[i])
          v[++cnt] = pii(mn[i - 1] + 1, mx[i]);
        for (int j : q[i])
          if (a[j] >= mn[i - 1])
            e[s[j]].push_back(pii(mn[i - 1], 1)),
                e[s[j]].push_back(pii(b[j], -1));
        for (int j : q[i - 1])
          if (a[j] <= mx[i])
            l[s[j]] = max(l[s[j]], mx[i]), r[s[j]] = min(r[s[j]], b[j]);
      }
    v[0] = pii(-1, -1);
    for (int i = 1; i <= sc; i++)
      if (l[i] > r[i])
        goto E;
      else if (~l[i]) {
        e[i].push_back(pii(l[i], -1)), e[i].push_back(pii(r[i], 1));
        sort(e[i].begin(), e[i].end());
        int now = 0, ok = 0;
        pii lst = pii(-1, 1);
        for (pii p : e[i]) {
          now += lst.second;
          if (!now && lst.first < p.first) {
            int j =
                upper_bound(v + 1, v + cnt + 1, pii(lst.first + 1, (int)2e9)) -
                v - 1;
            if (v[j].second < p.first) {
              add(max(v[j].second, lst.first) + 1, ori[i]);
              ok = 1;
              break;
            }
          }
          lst = p;
        }
        if (!ok)
          goto E;
      }
    printf("%d\n", tot);
    for (int i = 1; i <= tot; i++)
      printf("%d %d\n", d[i], t[i]);
    continue;
  E:
    puts("-1");
  }
}


// https://github.com/VaHiX/CodeForces/