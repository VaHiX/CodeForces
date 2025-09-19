/*
 * Problem URL : https://codeforces.com/contest/811/problem/B
 * Submit Date : 2025-09-01
 */

#include "bits/stdc++.h"

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, p;
  cin >> n >> m;
  vector<int> pgs;
  while (n--) {
    cin >> p;
    pgs.push_back(p);
  }

  int l, r, x, xa, v;
  while (m--) {
    cin >> l >> r >> x;
    l--;
    xa = 0;
    v = pgs[x - 1];
    for (int i = l; i < r; i++)
      if (pgs[i] < v)
        xa++;
    if (v == pgs[l + xa])
      cout << "Yes\n";
    else
      cout << "No\n";
  }

  return 0;
}
