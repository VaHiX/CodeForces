// Problem: CF 1684 F - Diverse Segments
// https://codeforces.com/contest/1684/problem/F

/*
Algorithm: 
This problem involves finding the minimum length of a segment to modify such that all given subsegments contain distinct elements.
The approach uses:
1. Preprocessing to store positions of each element in the array.
2. Traversing from right to left to determine the minimum starting point (st) for each position.
3. For each valid segment, compute the minimum length needed to make all subsegments distinct.

Time Complexity: O(n log n + m), where n is the array size and m is the number of segments.
Space Complexity: O(n), for storing the positions of elements and auxiliary arrays.
*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;
int t, n, m;
map<int, vector<int>> h;
void solve() {
  scanf("%d%d", &n, &m);
  vector<int> a(n + 1), l(n + 1, n + 1), mxl(n + 1, n + 1);
  int x, y, ans = n, st = n + 1, en = 0, minL = n + 1;
  h.clear();
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    h[a[i]].push_back(i);
  }
  for (int i = 0; i < m; i++) {
    scanf("%d%d", &x, &y);
    l[y] = min(l[y], x);
  }
  for (int i = n; i > 0; i--) {
    minL = min(minL, l[i]);
    vector<int> *tmp = &h[a[i]];
    tmp->pop_back();
    int len = tmp->size();
    if (minL < i) {
      int la = len ? tmp->at(len - 1) : -1;
      if (minL <= la) {
        en = max(la, en);
        vector<int>::iterator it = lower_bound(tmp->begin(), tmp->end(), minL);
        mxl[i - 1] = *it;
        ++it;
        st = min(st, (*it ? *it : i));
      }
    }
  }
  for (int i = n; i >= en; i--) {
    st = min(st, mxl[i]);
    ans = min(ans, max(0, i - st + 1));
  }
  cout << ans << endl;
}
int main() {
  scanf("%d", &t);
  while (t) {
    t--;
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/