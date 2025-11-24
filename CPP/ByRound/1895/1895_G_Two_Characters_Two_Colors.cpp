// Problem: CF 1895 G - Two Characters, Two Colors
// https://codeforces.com/contest/1895/problem/G

/*
Algorithm: Treap-based Dynamic Programming with Greedy Strategy
Time Complexity: O(n log n) per test case, where n is the length of the string
Space Complexity: O(n) for the treap structure and auxiliary arrays

This solution uses a treap (tree-based data structure) to maintain a dynamic set of
values and efficiently perform operations like insertion, deletion, and queries.

The problem is approached greedily:
- For each character, decide whether to paint it red or blue to maximize profit.
- When painting a character blue, we gain b[i] coins but may create inversions.
- When painting a character red, we gain r[i] coins.
- Inversion counting is done after removing blue characters and involves counting
  pairs where 1 appears before 0 in the final string.
- The key insight is to process characters from left to right and manage a treap
  to track how many inversions each blue choice introduces.
*/

#include <time.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <string>

#define ll long long
#define pb push_back
#define inf 0x3f3f3f3f3f3f3f3f
#define fi first
#define se second
using namespace std;
const int N = 4e5 + 5;
int T, n, tot, rt;
ll r[N], b[N];
string str;
mt19937 gen(time(0));
struct node {
  int fix, l, r, sz;
  ll tag, val;
} t[N];
void pushup(int p) { t[p].sz = t[t[p].l].sz + t[t[p].r].sz + 1; }
int newnode(ll val) {
  tot++;
  t[tot].fix = gen(), t[tot].l = t[tot].r = t[tot].tag = 0, t[tot].sz = 1,
  t[tot].val = val;
  return tot;
}
void add(int p, ll x) {
  if (!p)
    return;
  t[p].val += x, t[p].tag += x;
}
void pushdown(int p) {
  if (t[p].tag)
    add(t[p].l, t[p].tag), add(t[p].r, t[p].tag), t[p].tag = 0;
}
int merge(int x, int y) {
  if (!x || !y)
    return x + y;
  if (t[x].fix > t[y].fix) {
    pushdown(x);
    t[x].r = merge(t[x].r, y);
    pushup(x);
    return x;
  } else {
    pushdown(y);
    t[y].l = merge(x, t[y].l);
    pushup(y);
    return y;
  }
}
void split0(int rt, int &x, int &y, ll val) {
  if (!rt) {
    x = y = 0;
    return;
  }
  pushdown(rt);
  if (t[rt].val >= val) {
    x = rt;
    split0(t[x].r, t[x].r, y, val);
    pushup(x);
  } else {
    y = rt;
    split0(t[y].l, x, t[y].l, val);
    pushup(y);
  }
}
void split1(int rt, int &x, int &y, int val) {
  if (!rt) {
    x = y = 0;
    return;
  }
  pushdown(rt);
  if (t[t[rt].l].sz + 1 <= val) {
    x = rt;
    split1(t[x].r, t[x].r, y, val - t[t[rt].l].sz - 1);
    pushup(x);
  } else {
    y = rt;
    split1(t[y].l, x, t[y].l, val);
    pushup(y);
  }
}
int rs(int x) {
  while (t[x].r)
    x = t[x].r;
  return x;
}
int ls(int x) {
  while (t[x].l)
    x = t[x].l;
  return x;
}
int cnt;
ll c[N];
void dfs(int x) {
  pushdown(x);
  if (t[x].l)
    dfs(t[x].l);
  c[++cnt] = t[x].val;
  if (t[x].r)
    dfs(t[x].r);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--) {
    cin >> n >> str;
    for (int i = 1; i <= n; i++)
      cin >> r[i];
    for (int i = 1; i <= n; i++)
      cin >> b[i];
    rt = tot = 0;
    ll sm = 0;
    int c1 = 0;
    for (int i = 1; i <= n; i++) {
      if (r[i] <= b[i]) {
        sm += b[i];
        continue;
      } else if (str[i - 1] == '1') {
        c1++, sm += b[i];
        int x, y;
        split0(rt, x, y, r[i] - b[i]);
        rt = merge(x, merge(newnode(r[i] - b[i]), y));
      } else {
        sm += r[i];
        int x, y;
        split1(rt, x, y, min(1ll * c1, r[i] - b[i]));
        if (!x || !y) {
          add(x, -1);
          rt = x + y;
        } else {
          int _x = rs(x), _y = ls(y);
          if (t[_x].val == t[_y].val) {
            ll val = t[_x].val;
            int a, b, c, d;
            split0(x, a, b, val + 1);
            split0(y, c, d, val);
            add(a, -1), add(b, -1);
            rt = merge(merge(a, c), merge(b, d));
          } else {
            add(x, -1);
            rt = merge(x, y);
          }
        }
      }
    }
    cnt = 0, dfs(rt);
    ll res = sm;
    for (int i = 1; i <= c1; i++) {
      sm += c[i], res = max(res, sm);
    }
    cout << res << "\n";
  }
}


// https://github.com/VaHiX/CodeForces/