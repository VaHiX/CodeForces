/*
 * Problem URL : https://codeforces.com/problemset/problem/219/E
 * Submit Date : 2025-08-13
 */

#include <algorithm>
#include <bitset>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <stdlib.h>
#include <string>
#include <vector>
typedef long long ll;
#define MAX 200005
using namespace std;
#define INF 2147483647
#define inf 1 << 30
#define MOD 1000000007
#define EPS 1e-9
#define G 9.8
#define PI acos(-1)
#define REP(i, n) for (int(i) = 0; (i) < (int)(n); (i)++)
bool debug = false;
int n, m, k;
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

struct seg {
  int l, r;
  int len, tar;
  seg() {}
  seg(int l, int r, int len, int tar) : l(l), r(r), len(len), tar(tar) {}
  bool operator<(const seg &o) const {
    if (len == o.len) {
      return tar < o.tar;
    }
    return len > o.len;
  }
};
set<seg> s;
int L[MAX], R[MAX];
const int NMAX = 1000005;
int pos[NMAX];
seg gg(int a, int b) {
  if (a == 0 && b == n + 1) {
    return {0, n + 1, n, 1};
  }
  if (a == 0) {
    if (b == 1)
      return seg(a, b, -1, -1);
    return seg(0, b, b - 1, 1);
  }
  if (b == n + 1) {
    if (a == n)
      return seg(a, b, -1, -1);
    return seg(a, n + 1, n - a, n);
  }
  int tar = (b - a) / 2 + a;
  if (tar > a && tar < b) {
    return seg(a, b, min(tar - a, b - tar), tar);
  } else {
    return seg(a, b, -1, -1);
  }
}
int main() {
  scanf("%d%d", &n, &m);
  int t, id;
  s.insert({0, n + 1, n, 1});
  R[0] = n + 1;
  L[n + 1] = 0;
  while (m--) {
    scanf("%d%d", &t, &id);
    if (t == 1) {
      seg x = *s.begin();
      printf("%d\n", x.tar);
      L[x.tar] = x.l;
      R[x.tar] = x.r;
      R[x.l] = x.tar;
      L[x.r] = x.tar;

      pos[id] = x.tar;
      s.insert(gg(x.l, pos[id]));
      s.insert(gg(pos[id], x.r));
      s.erase(s.begin());
    } else {
      int tar = pos[id];
      int l = L[tar], r = R[tar];
      s.erase(gg(l, tar));
      s.erase(gg(tar, r));
      s.insert(gg(l, r));
      R[l] = r;
      L[r] = l;
    }
  }
  return 0;
}
