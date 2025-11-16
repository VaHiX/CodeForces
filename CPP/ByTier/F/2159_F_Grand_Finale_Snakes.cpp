// Problem: CF 2159 F - Grand Finale: Snakes
// https://codeforces.com/contest/2159/problem/F

/*
Code Purpose:
This code solves the interactive problem "F. Grand Finale: Snakes" where we are given an n×n grid and need to determine
the m smallest values of f(l, T) - the maximum number covered by a snake of length l at time T.
The snakes move from (1,1) to (n,n) using only down and right moves, with the first move always being down.
We use binary search and priority queue techniques to efficiently query the grid and find the required values.

Algorithms/Techniques:
- Binary search to find optimal positions for snakes
- Priority queue to maintain minimum values
- Efficient traversal of snake paths using grid coordinates

Time Complexity:
O(n^2 * log(n) + m * log(n)) where n^2 for processing each snake length, and log(n) for binary search operations

Space Complexity:
O(n^2 + m) for storing grid information and priority queue elements
*/

#include <stdio.h>
#include <algorithm>
#include <functional>
#include <queue>
#include <utility>
#include <vector>

#define fi first
#define se second
#define pb push_back
#define fr(i, a, b) for (int i = (a); i <= (b); ++i)
#define fd(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
template <typename T> void chmin(T &x, T y) { x = min(x, y); }
template <typename T> void chmax(T &x, T y) { x = max(x, y); }
constexpr int N = 500;
int T, n, m;
int a[N + 5][N + 5];
pii p[N * N + 5];
int qry(int l, int t) {
  printf("? %d %d\n", l, t);
  fflush(stdout);
  int res;
  scanf("%d", &res);
  return res;
}
priority_queue<pair<pii, pii>, vector<pair<pii, pii>>, greater<>> que;
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    fr(i, 1, n) fr(j, 1, n) scanf("%d", &a[i][j]), p[a[i][j]] = {i, j};
    fr(l, 1, n) {
      for (int s = 1; s <= 2 * n - 1; s += l) {
        int L = s, R = min(2 * n - 1, s + l - 1), res = R + 1;
        while (L <= R) {
          int mid = (L + R) >> 1;
          int val = qry(l, mid);
          auto [x, y] = p[val];
          if (x == 1 || x + y - 1 < s)
            L = mid + 1;
          else
            res = mid, R = mid - 1;
        }
        L = s, R = min(2 * n - 1, s + l - 1);
        if (res > L)
          que.push({{qry(l, res - 1), l}, {res - 1, L}});
        if (res <= R)
          que.push({{qry(l, res), l}, {res, R}});
      }
    }
    vector<int> ans;
    while (m--) {
      auto [A, B] = que.top();
      auto [val, l] = A;
      auto [x, y] = B;
      que.pop();
      ans.pb(val);
      if (x < y)
        que.push({{qry(l, x + 1), l}, {x + 1, y}});
      else if (x > y)
        que.push({{qry(l, x - 1), l}, {x - 1, y}});
    }
    printf("! ");
    for (int x : ans)
      printf("%d ", x);
    puts("");
    fflush(stdout);
    while (que.size())
      que.pop();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/