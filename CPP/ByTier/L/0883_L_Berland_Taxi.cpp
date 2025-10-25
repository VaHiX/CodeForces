/*
 * Problem URL : https://codeforces.com/contest/883/problem/L
 * Submit Date : 2025-09-08
 */

#include <bits/stdc++.h>
using namespace std;
int n, k, m;
inline int lowbit(int x) { return x & (-x); }
class C1 {
public:
  int id;
  long long tim;
  bool operator<(const C1 &c) const {
    if (tim != c.tim)
      return tim > c.tim;
    return id > c.id;
  }
};
class C2 {
public:
  int id, des;
  long long tim;
  bool operator<(const C2 &c) const { return tim > c.tim; }
};
priority_queue<C1> q[200010];
priority_queue<C2> run;
class tree {
public:
  int dat[200010];
  inline void modify(int p, int v) {
    for (; p <= n; p += lowbit(p))
      dat[p] += v;
  }
  inline int query(int r) {
    int out = 0;
    for (; r; r -= lowbit(r))
      out += dat[r];
    return out;
  }
  inline int query(int l, int r) { return query(r) - query(l - 1); }
} T;
inline int getlft(int pos) {
  int L = 1, R = pos, out = 0;
  while (L <= R) {
    int mid = (L + R) >> 1;
    if (T.query(mid, pos))
      out = mid, L = mid + 1;
    else
      R = mid - 1;
  }
  return out;
}
inline int getrgt(int pos) {
  int L = pos, R = n, out = 0;
  while (L <= R) {
    int mid = (L + R) >> 1;
    if (T.query(pos, mid))
      out = mid, R = mid - 1;
    else
      L = mid + 1;
  }
  return out;
}
long long tim;
int a, b;
int main() {
  long long now = 0;
  scanf("%d%d%d", &n, &k, &m);
  for (int i = 1, ti; i <= k; i++) {
    scanf("%d", &ti);
    T.modify(ti, 1);
    q[ti].push((C1){i, 0});
  }
  while (m--) {
    scanf("%lld%d%d", &tim, &a, &b);
    now = max(now, tim);
    while (!run.empty() && run.top().tim <= now) {
      C2 tmp = run.top();
      run.pop();
      T.modify(tmp.des, 1);
      q[tmp.des].push((C1){tmp.id, tmp.tim});
    }
    if (run.size() == k) {
      now = max(now, run.top().tim);
      while (!run.empty() && run.top().tim <= now) {
        C2 tmp = run.top();
        run.pop();
        T.modify(tmp.des, 1);
        q[tmp.des].push((C1){tmp.id, tmp.tim});
      }
    }
    int L = getlft(a), R = getrgt(a);
    C1 tmp;
    if (L) {
      if (R) {
        if (a - L < R - a || (a - L == R - a && q[R].top() < q[L].top())) {
          T.modify(L, -1);
          tmp = q[L].top();
          q[L].pop();
          printf("%d %lld\n", tmp.id, now + a - L - tim);
          run.push((C2){tmp.id, b, now + a - L + abs(b - a)});
        } else {
          T.modify(R, -1);
          tmp = q[R].top();
          q[R].pop();
          printf("%d %lld\n", tmp.id, now + R - a - tim);
          run.push((C2){tmp.id, b, now + R - a + abs(b - a)});
        }
      } else {
        T.modify(L, -1);
        tmp = q[L].top();
        q[L].pop();
        printf("%d %lld\n", tmp.id, now + a - L - tim);
        run.push((C2){tmp.id, b, now + a - L + abs(b - a)});
      }
    } else {
      T.modify(R, -1);
      tmp = q[R].top();
      q[R].pop();
      printf("%d %lld\n", tmp.id, now + R - a - tim);
      run.push((C2){tmp.id, b, now + R - a + abs(b - a)});
    }
  }
  return 0;
}