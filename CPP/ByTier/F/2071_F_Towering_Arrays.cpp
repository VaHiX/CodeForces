/*
 * Problem URL : https://codeforces.com/problemset/problem/2071/F
 * Submit Date : 2025-08-22
 */

#include <sys/time.h>

#include <algorithm>
#include <iostream>

using namespace std;

const int N = 200000;
const int N_ = N * 2 + 1;

unsigned int RNG;

void srand() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  RNG = tv.tv_sec ^ tv.tv_usec | 1;
}

int rand() { return (RNG *= 3) >> 1; }

int aa[N], ii[N], pp[N];
int zz[N_], ll[N_], rr[N_], bb[N_], sz[N_];
int _, l_, r_;

int node(int a) {
  zz[_] = rand();
  ll[_] = rr[_] = 0;
  bb[_] = a;
  sz[_] = 1;
  return _++;
}

void pul(int u) { sz[u] = sz[ll[u]] + 1 + sz[rr[u]]; }

void split(int u, int a) {
  if (u == 0) {
    l_ = r_ = 0;
    return;
  }
  if (bb[u] < a) {
    split(rr[u], a);
    rr[u] = l_, l_ = u;
  } else if (bb[u] > a) {
    split(ll[u], a);
    ll[u] = r_, r_ = u;
  } else {
    l_ = ll[u], r_ = rr[u];
    ll[u] = rr[u] = 0;
  }
  pul(u);
}

void split_(int u, int a) {
  if (u == 0) {
    l_ = r_ = 0;
    return;
  }
  int d = bb[u] - (a - sz[rr[u]]);
  if (d < 0) {
    split_(rr[u], a);
    rr[u] = l_, l_ = u;
  } else {
    split_(ll[u], a - sz[rr[u]] - 1);
    ll[u] = r_, r_ = u;
  }
  pul(u);
}

int merge(int u, int v) {
  if (u == 0)
    return v;
  if (v == 0)
    return u;
  if (zz[u] > zz[v]) {
    rr[u] = merge(rr[u], v);
    pul(u);
    return u;
  } else {
    ll[v] = merge(u, ll[v]);
    pul(v);
    return v;
  }
}

int query(int u, int a) {
  int s = 0;
  while (u)
    if (bb[u] >= a - s - sz[rr[u]])
      s += sz[rr[u]] + 1, u = ll[u];
    else
      u = rr[u];
  return s;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(NULL);
  srand();
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m, m = n - m;
    for (int i = 0; i < n; i++)
      cin >> aa[ii[i] = i];
    sort(ii, ii + n, [](int i, int j) { return aa[i] < aa[j]; });
    int a_ = aa[ii[n - m]], up = 0;
    _ = 1;
    for (int i = 0; i < n; i++) {
      split_(up, aa[i]);
      pp[i] = aa[i] - sz[r_];
      up = merge(merge(l_, node(pp[i])), r_);
    }
    for (int uq = 0, i = n - 1; i >= 0; i--) {
      split_(uq, aa[i]);
      int q = aa[i] - sz[r_];
      uq = merge(merge(l_, node(q)), r_);
      while (aa[i] > a_ && query(up, a_ + 1) + query(uq, a_ + 1) > m)
        a_++;
      split(up, pp[i]);
      up = merge(l_, r_);
    }
    cout << a_ << '\n';
  }
  return 0;
}
