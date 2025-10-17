/*
 * Problem URL : https://codeforces.com/contest/528/problem/A
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
using namespace std;
multiset<int> sh, sv;
set<int> hz, vt;
set<int>::iterator it1, it2;
multiset<int>::iterator itm;
int main() {
  int w, h, n;
  scanf("%d %d %d", &w, &h, &n);
  hz.insert(0);
  hz.insert(h);
  sh.insert(h);
  vt.insert(0);
  vt.insert(w);
  sv.insert(w);
  for (int i = 0; i < n; i++) {
    char c;
    int a;
    scanf(" %c %d", &c, &a);
    long long int mxv, mxh;
    if (c == 'H') {
      mxv = (*(--sv.end()));
      it1 = hz.lower_bound(a);
      it2 = it1;
      it2--;
      int b = (*it1) - (*it2), d1 = (*it1) - a, d2 = a - (*it2);
      itm = sh.lower_bound(b);
      sh.erase(itm);
      hz.insert(a);
      sh.insert(d1);
      sh.insert(d2);
      mxh = (*(--sh.end()));
    } else {
      mxh = (*(--sh.end()));
      it1 = vt.lower_bound(a);
      it2 = it1;
      it2--;
      int b = (*it1) - (*it2), d1 = (*it1) - a, d2 = a - (*it2);
      itm = sv.lower_bound(b);
      sv.erase(itm);
      vt.insert(a);
      sv.insert(d1);
      sv.insert(d2);
      mxv = (*(--sv.end()));
    }
    printf("%lld\n", mxv * mxh);
  }
  return 0;
}
