/*
 * Problem URL : https://codeforces.com/problemset/problem/2068/E
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
using namespace std;
int n = 0, m = 0, cnt = 0, tot = 0;
array<int, 200100> head, dis, vis, up, del, fa, num;
struct Node {
  int to;
  int nxt;
};
struct Item {
  int val;
  int x;
  int y;
};
struct Point {
  int id;
  int path;
};
array<Node, 400100> edge;
array<pair<int, int>, 400100> line;
array<Item, 400100> tmp;
void new_line(int a, int b) {
  edge[++cnt].to = b;
  edge[cnt].nxt = head[a];
  head[a] = cnt;
  return;
}
bool operator<(const Point &x, const Point &y) { return x.path < y.path; }
bool operator>(const Point &x, const Point &y) { return x.path > y.path; }
priority_queue<Point, vector<Point>, greater<Point>> q;
int find(int x) {
  if (x == fa[x])
    return x;
  return fa[x] = find(fa[x]);
}
void merge(int x, int y) {
  fa[find(y)] = find(x);
  return;
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    fa[i] = i;
  for (int i = 1; i <= m; ++i) {
    int x = 0, y = 0;
    cin >> x >> y;
    new_line(x, y);
    new_line(y, x);
    line[i] = {x, y};
  }
  dis.fill(1e9);
  dis[n] = 0;
  q.push({n, 0});
  while (!q.empty()) {
    int x = q.top().id;
    q.pop();
    if (vis[x])
      continue;
    vis[x] = true;
    for (int e = head[x]; e; e = edge[e].nxt) {
      int to = edge[e].to;
      if (dis[to] > dis[x] + 1) {
        dis[to] = dis[x] + 1;
        up[to] = x;
        q.push({to, dis[to]});
      }
    }
  }
  for (int i = 1; i <= m; ++i) {
    int x = line[i].first, y = line[i].second;
    if (up[x] != y && up[y] != x)
      tmp[++tot] = {dis[x] + dis[y] + 1, x, y};
  }
  num.fill(-1e9);
  stable_sort(tmp.data() + 1, tmp.data() + tot + 1,
              [&](Item x, Item y) { return x.val < y.val; });
  for (int i = 1; i <= tot; ++i) {
    while (1) {
      tmp[i].x = find(tmp[i].x), tmp[i].y = find(tmp[i].y);
      if (tmp[i].x == tmp[i].y)
        break;
      if (dis[tmp[i].x] > dis[tmp[i].y]) {
        num[tmp[i].x] = tmp[i].val - dis[tmp[i].x];
        merge(up[tmp[i].x], tmp[i].x);
      } else {
        num[tmp[i].y] = tmp[i].val - dis[tmp[i].y];
        merge(up[tmp[i].y], tmp[i].y);
      }
    }
  }
  vis.fill(0);
  dis.fill(1e9);
  dis[n] = 0;
  q.push({n, 0});
  while (!q.empty()) {
    int x = q.top().id, d = q.top().path;
    q.pop();
    if (d != dis[x])
      continue;
    if (vis[x])
      continue;
    vis[x] = true;
    for (int e = head[x]; e; e = edge[e].nxt) {
      int to = edge[e].to;
      if (num[to] != -1e9 && dis[to] > max(d + 1, num[to])) {
        dis[to] = max(d + 1, num[to]);
        q.push({to, dis[to]});
      }
    }
  }
  if (dis[1] == 1e9) {
    cout << "-1" << endl;
    return 0;
  }
  cout << dis[1] << endl;
  return 0;
}
