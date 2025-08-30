/*
 * Problem URL : https://codeforces.com/problemset/problem/2066/E
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int offset = 1 << 20;
const int INF = 1e9;

struct Node {
  ll sum;
  int mini, lft, rig;
  Node(ll sum, int mini, int lft, int rig)
      : sum(sum), mini(mini), lft(lft), rig(rig) {}
  Node() : sum(0), mini(INF), lft(INF), rig(-INF) {}
};

Node tour[2 * offset];

Node merge(Node lhs, Node rhs) {
  return Node(lhs.sum + rhs.sum,
              min(min(lhs.mini, rhs.mini), rhs.lft - lhs.rig),
              min(lhs.lft, rhs.lft), max(lhs.rig, rhs.rig));
}

void update(int x, int val) {
  int pos = x + offset;
  tour[pos].sum += val * x;
  tour[pos].mini = tour[pos].sum > x ? 0 : INF;
  if (tour[pos].sum)
    tour[pos].lft = tour[pos].rig = x;
  else {
    tour[pos].lft = INF;
    tour[pos].rig = -INF;
  }
  for (pos /= 2; pos; pos /= 2)
    tour[pos] = merge(tour[2 * pos], tour[2 * pos + 1]);
}

Node query(int x, int lo, int hi, int from, int to) {
  if (lo >= to || hi <= from)
    return Node();
  if (lo >= from && hi <= to)
    return tour[x];
  int mid = (lo + hi) / 2;
  return merge(query(2 * x, lo, mid, from, to),
               query(2 * x + 1, mid, hi, from, to));
}

Node query(int from, int to) { return query(1, 0, offset, from, to); }

void answer() {
  for (int curr = 1; curr < offset; curr++) {
    int x = 1;
    ll pref = 0;
    while (x < offset) {
      x *= 2;
      if (tour[x].rig < curr)
        pref += tour[x++].sum;
    }
    curr = x - offset;
    if (pref < curr) {
      int gap = query(1, 0, offset, curr, offset).mini;
      if (gap < offset && gap > pref) {
        puts("No");
        return;
      }
    } else
      curr = min(pref, (ll)offset);
  }
  puts("Yes");
}

int main() {
  int N, Q;
  scanf("%d%d", &N, &Q);
  while (N--) {
    int x;
    scanf("%d", &x);
    update(x, 1);
  }
  answer();
  while (Q--) {
    char c;
    int x;
    scanf(" %c%d", &c, &x);
    update(x, c == '+' ? 1 : -1);
    answer();
  }
  return 0;
}