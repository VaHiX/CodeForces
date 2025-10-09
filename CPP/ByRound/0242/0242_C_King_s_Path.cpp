/*
 * Problem URL : https://codeforces.com/problemset/problem/242/C
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pr;
int n, x, y, x1, y1, r, a, b, dx[] = {-1, -1, -1, 0, 1, 1, 1, 0},
                              dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};
queue<pr> q;
map<pr, int> mp;
int main() {
  scanf("%d%d%d%d%d", &x, &y, &x1, &y1, &n);
  while (n--) {
    scanf("%d%d%d", &r, &a, &b);
    for (int i = a; i <= b; i++)
      mp[pr(r, i)] = -1;
  }
  mp[{x, y}] = 0; // mp[{x1,y1}]=-1;
  q.push({x, y});
  while (q.size()) {
    pr u = q.front();
    q.pop();
    for (int i = 0; i < 8; i++) {
      pr v = pr(u.first + dx[i], u.second + dy[i]);
      if (mp[v] == -1)
        mp[v] = mp[u] + 1, q.push(v);
    }
  }
  printf("%d", mp[{x1, y1}]);
  return 0;
}
