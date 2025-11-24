// Problem: CF 1852 F - Panda Meetups
// https://codeforces.com/contest/1852/problem/F

/*
 * Problem: F. Panda Meetups
 * 
 * Purpose:
 * This code efficiently handles a dynamic problem involving red and blue pandas meeting at positions on a number line.
 * The algorithm uses a combination of priority queues and treap-like data structures to maintain and update 
 * information about possible panda meetings in optimal time.
 * 
 * Key Techniques:
 * - Treap data structure for maintaining intervals with efficient merge/split operations.
 * - Priority queue to manage active red pandas.
 * - Offline processing of updates to optimize meeting assignments.
 * 
 * Time Complexity: O(q * log q)
 * Space Complexity: O(q)
 * 
 * The main idea:
 * - As new blue pandas arrive, we remove them from the system and try to create friendships with red pandas.
 * - Red pandas can move towards blue pandas, so we track their possible paths.
 * - The priority queue helps find the best red pandas to form friendships with.
 * 
 * Input: q updates of (position, time, count)
 * Output: maximum number of friendships after each update
 */

#include <stdio.h>
#include <sys/time.h>
#define Q 200000
#define N (Q + 1)
int min(int a, int b) { return a < b ? a : b; }
unsigned int Z;
void srand_() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  Z = tv.tv_sec ^ tv.tv_usec | 1;
}
int rand_() { return (Z *= 3) >> 1; }
int x_;
long long xx[N];
int vv[N], pq[N];
int iq[N + 1], cnt;
int lt(int i, int j) { return xx[i] < xx[j]; }
int p2(int p) {
  return (p *= 2) > cnt ? 0 : (p < cnt && lt(iq[p + 1], iq[p]) ? p + 1 : p);
}
void pq_up(int i) {
  int p, q, j;
  for (p = pq[i]; (q = p / 2) && lt(i, j = iq[q]); p = q)
    iq[pq[j] = p] = j;
  iq[pq[i] = p] = i;
}
void pq_dn(int i) {
  int p, q, j;
  for (p = pq[i]; (q = p2(p)) && lt(j = iq[q], i); p = q)
    iq[pq[j] = p] = j;
  iq[pq[i] = p] = i;
}
void pq_add(int i) { pq[i] = ++cnt, pq_up(i); }
void pq_remove(int i) {
  int j = iq[cnt--];
  if (j != i)
    pq[j] = pq[i], pq_up(j), pq_dn(j);
  pq[i] = 0;
}
int pq_first() { return iq[1]; }
int zz[N], ll[N], rr[N], yy[N], dd[N], ss[N], pp[N], u_, l_, r_;
int node(int y, int d) {
  static int _ = 1;
  zz[_] = rand_();
  yy[_] = y;
  ss[_] = dd[_] = d, pp[_] = min(d, 0);
  return _++;
}
void pul(int u) {
  int l = ll[u], r = rr[u];
  ss[u] = ss[l] + dd[u] + ss[r];
  pp[u] = min(pp[l], ss[l] + min(0, dd[u] + pp[r]));
}
void tr_split(int u, int y) {
  int y_;
  if (u == 0) {
    u_ = l_ = r_ = 0;
    return;
  }
  y_ = yy[u] + x_ * (dd[u] > 0 ? 1 : -1);
  if (y_ < y) {
    tr_split(rr[u], y);
    rr[u] = l_, l_ = u;
  } else if (y_ > y) {
    tr_split(ll[u], y);
    ll[u] = r_, r_ = u;
  } else {
    u_ = u, l_ = ll[u], r_ = rr[u];
    ll[u] = rr[u] = 0;
  }
  pul(u);
}
int tr_merge(int u, int v) {
  if (u == 0)
    return v;
  if (v == 0)
    return u;
  if (zz[u] < zz[v]) {
    rr[u] = tr_merge(rr[u], v), pul(u);
    return u;
  } else {
    ll[v] = tr_merge(u, ll[v]), pul(v);
    return v;
  }
}
int first(int u) { return ll[u] == 0 ? u : first(ll[u]); }
int last(int u) { return rr[u] == 0 ? u : last(rr[u]); }
void add(int u, int v) {
  if (u == 0 || v == 0 || dd[u] < 0 || dd[v] > 0)
    return;
  vv[u] = v, xx[u] = (long long)yy[vv[u]] - yy[u], pq_add(u);
}
void remove_(int u) {
  if (pq[u])
    pq_remove(u);
}
void merge(int u, int v) {
  int l1, r1, l, r;
  tr_split(u_, yy[u] + x_), l1 = l_;
  tr_split(r_, yy[v] - x_), r1 = r_;
  if (dd[u] + dd[v] > 0) {
    ss[u] = dd[u] += dd[v], pp[u] = min(dd[u], 0);
    r = first(r1);
    remove_(u), remove_(v), add(u, r);
    u_ = tr_merge(tr_merge(l1, u), r1);
  } else if (dd[u] + dd[v] < 0) {
    ss[v] = dd[v] += dd[u], pp[v] = min(dd[v], 0);
    l = last(l1);
    remove_(l), remove_(u), add(l, v);
    u_ = tr_merge(tr_merge(l1, v), r1);
  } else {
    l = last(l1), r = first(r1);
    remove_(l), remove_(u), remove_(v), add(l, r);
    u_ = tr_merge(l1, r1);
  }
}
void tr_add(int y, int d) {
  int l, r;
  if (d == 0)
    return;
  tr_split(u_, y);
  l = last(l_), r = first(r_);
  u_ = node(y - x_ * (d > 0 ? 1 : -1), d);
  remove_(l), add(l, u_), add(u_, r);
  u_ = tr_merge(tr_merge(l_, u_), r_);
}
int tr_remove(int y) {
  int d, l, r;
  tr_split(u_, y);
  if (u_) {
    d = dd[u_];
    l = last(l_), r = first(r_);
    remove_(l), remove_(u_), add(l, r);
  } else
    d = 0;
  u_ = tr_merge(l_, r_);
  return d;
}
int main() {
  int q, b;
  srand_();
  scanf("%d", &q);
  x_ = -1, b = 0;
  while (q--) {
    int x, y, c, d, u;
    scanf("%d%d%d", &x, &y, &c);
    if (x_ < x) {
      // Process all red pandas until x * 2 to make possible matches
      while (cnt && xx[u = pq_first()] <= x * 2)
        merge(u, vv[u]);
      x_ = x;
    }
    d = tr_remove(y);
    if (c > 0)
      b += c;
    tr_add(y, d - c);
    printf("%d\n", b + pp[u_]);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/