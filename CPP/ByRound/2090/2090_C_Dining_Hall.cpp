/*
 * Problem URL : https://codeforces.com/problemset/problem/2090/C
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
using namespace std;
#define PII pair<int, int>
#define PIP pair<int, PII>
const int N = 5e4 + 5;
int T, n, p;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T;
  while (T--) {
    cin >> n;
    priority_queue<PIP, vector<PIP>, greater<PIP>> q;
    int x = 1, y = 1, dis = 2;
    for (int i = 1; i <= n; i++) {
      cin >> p;
      if (p == 1 && !q.empty() && q.top().first < dis) {
        cout << q.top().second.first << " " << q.top().second.second << "\n";
        q.pop();
      } else {
        cout << x << " " << y << "\n";
        q.push({x + y + 1, {x, y + 1}});
        q.push({x + y + 1, {x + 1, y}});
        q.push({x + y + 4, {x + 1, y + 1}});
        if (y == 1) {
          swap(x, y);
          y += 3;
        } else
          x += 3, y -= 3;
        dis = x + y;
      }
    }
  }
  return 0;
}
