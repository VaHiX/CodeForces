// Problem: CF 2068 G - A Very Long Hike
// https://codeforces.com/contest/2068/problem/G

/*
Algorithm: The code computes the number of distinct positions reachable within 10^20 seconds using a combination of Dijkstra's algorithm on a repeated grid and convex hull area calculation.

Approach:
- First, a periodic grid of altitudes is constructed by repeating the input matrix.
- Then, for each starting point in the first row and column, run Dijkstra to find minimum time to reach all positions in a window.
- Collect these reachable positions and scale them according to their distances from origin.
- Finally, compute the area of convex hull from these scaled points and scale it up to approximate reachable area.

Time Complexity: O(n^4 * log(n^2)) due to Dijkstra calls and sorting operations
Space Complexity: O(n^4) for storing the grid and distance matrices
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <functional>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;
const int N = 22, M = N * N * 4;
const int INF = 0x3f3f3f3f;
int n;
int a[N][N], mp[M][M];
int dis[M][M], d[M][M], mark[M][M];
inline void Dijkstra(int x, int y) {
  memset(dis, 0x3f, sizeof dis);
  memset(mark, 0, sizeof mark);
  typedef tuple<int, int, int> T3;
  priority_queue<T3, vector<T3>, greater<T3>> pq;
  pq.push({0, x + n * n, y + n * n});
  dis[x + n * n][y + n * n] = 0;
  const int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
  while (pq.size()) {
    int x = get<1>(pq.top()), y = get<2>(pq.top());
    pq.pop();
    if (mark[x][y])
      continue;
    mark[x][y] = 1;
    for (int i = 0; i < 4; i++) {
      int p = x + dx[i], q = y + dy[i];
      if (abs(p - n * n) + abs(q - n * n) > n * n)
        continue;
      int w = dis[x][y] + abs(mp[p][q] - mp[x][y]) + 1;
      if (dis[p][q] > w) {
        dis[p][q] = w;
        pq.push({w, p, q});
      }
    }
  }
  for (int i = 0; i <= n * 2; i++)
    for (int j = 0; j <= n * 2; j++)
      d[i][j] = min(d[i][j], dis[x + i * n][y + j * n]);
}
const double eps = 1e-12;
template <typename T> int sgn(const T x) {
  return fabs(x) < eps ? 0 : x > 0 ? 1 : -1;
}
template <typename T> struct Point {
  T x, y;
  Point() {}
  Point(T _x, T _y) : x(_x), y(_y) {}
  inline Point operator+(const Point &p) const {
    return Point(x + p.x, y + p.y);
  }
  inline Point operator-(const Point &p) const {
    return Point(x - p.x, y - p.y);
  }
  inline Point operator*(const T &p) const { return Point(x * p, y * p); }
  inline Point operator/(const T &p) const { return Point(x / p, y / p); }
  inline T operator*(const Point &p) const { return x * p.y - y * p.x; }
  inline T operator&(const Point &p) const { return x * p.x + y * p.y; }
  inline T Len2() const { return x * x + y * y; }
  inline bool operator<(const Point &p) const {
    return sgn(operator*(p)) == 0 ? Len2() < p.Len2() : operator*(p) > 0;
  }
};
Point<double> p[M], sta[M];
int tot;
template <typename T> inline T Calc(Point<T> p[], int n) {
  Point<T> p0(1e20, 1e20);
  for (int i = 1; i <= n; i++)
    if (p[i].y < p0.y)
      p0 = p[i];
  for (int i = 1; i <= n; i++)
    p[i] = p[i] - p0;
  sort(p + 1, p + n + 1);
  int m = 0;
  for (int i = 1; i <= n; i++) {
    while (m > 1 && (sta[m] - sta[m - 1]) * (p[i] - sta[m]) < eps)
      m--;
    sta[++m] = p[i];
  }
  T res = 0;
  sta[m + 1] = sta[1];
  for (int i = 1; i <= n; i++)
    res += sta[i] * sta[i + 1];
  return fabs(res / 2);
}
int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      scanf("%d", &a[i][j]);
  for (int i = 0; i < n * (n * 2 + 1); i++)
    for (int j = 0; j < n * (n * 2 + 1); j++)
      mp[i][j] = a[i % n][j % n];
  memset(d, 0x3f, sizeof d);
  for (int i = 0; i < n; i++)
    Dijkstra(i, 0);
  for (int i = 1; i < n; i++)
    Dijkstra(0, i);
  for (int i = 0; i <= n * 2; i++)
    for (int j = 0; j <= n * 2; j++)
      if (d[i][j] && d[i][j] != INF) {
        p[++tot] = Point<double>(i - n, j - n);
        p[tot] = p[tot] * (1.0 * n / d[i][j]);
      }
  printf("%.12g\n", Calc(p, tot) * 1e40);
  return 0;
}


// https://github.com/VaHiX/CodeForces/