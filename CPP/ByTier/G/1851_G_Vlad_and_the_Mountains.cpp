// Problem: CF 1851 G - Vlad and the Mountains
// https://codeforces.com/contest/1851/problem/G

/*
Algorithm: Union-Find (Disjoint Set Union) with offline processing
Approach: 
1. For each query, we want to know if we can reach from node 'a' to 'b' with initial energy 'e'
2. The energy needed to go from node u to node v is h[v] - h[u]
3. We process edges in order of increasing max(h[u], h[v]) 
4. For each edge addition, we check all queries that could be satisfied by this edge
5. We use DSU to track connected components, and for queries we check if start and end nodes are in same component

Time Complexity: O(m log m + q log q + (m + q) * α(n)) where α is the inverse Ackermann function
Space Complexity: O(n + m + q)

The algorithm uses a clever offline processing technique where we:
- Sort edges by the maximum height of the two nodes they connect
- Sort queries by (initial_height + energy) to determine when we can potentially satisfy them
- As we add edges, we check which queries can now be satisfied
- This approach avoids the need to handle multiple possible paths explicitly
*/

#include <algorithm>
#include <cstdio>
#include <utility>
#include <vector>

using namespace std;
#define _int64 long long
#define mo 998244353
class dsu {
public:
  dsu(int n) {
    int i;
    this->n = n;
    p.clear();
    for (i = 0; i < n; i++)
      p.push_back(i);
    e.clear();
  }
  int get(int x) {
    if (x == p[x])
      return x;
    else {
      p[x] = get(p[x]);
      return p[x];
    }
  }
  void add(int x, int y, int w) {
    int xx, yy;
    xx = get(x);
    yy = get(y);
    if (xx != yy) {
      p[yy] = xx;
      e.push_back(make_pair(make_pair(x, y), w));
    }
  }
  vector<int> p;
  vector<pair<pair<int, int>, int>> e;
  int n;
};
int a[210000];
int qu[210000][3];
int ans[210000];
int h[210000];
int main() {
  int i, j, k, n, l, t, m, x, y, o, b1, ind, qq, now;
  vector<pair<int, int>> e;
  vector<pair<int, pair<int, int>>> ee;
  vector<pair<int, int>> q;
  scanf("%d", &t);
  for (l = 0; l < t; l++) {
    scanf("%d%d", &n, &m);
    for (i = 0; i < n; i++)
      scanf("%d", &h[i]);
    e.clear();
    ee.clear();
    for (i = 0; i < m; i++) {
      scanf("%d%d", &x, &y);
      x--;
      y--;
      e.push_back(make_pair(x, y));
      ee.push_back(make_pair(max(h[x], h[y]), make_pair(x, y)));
    }
    sort(ee.begin(), ee.end());
    scanf("%d", &qq);
    q.clear();
    for (o = 0; o < qq; o++) {
      scanf("%d%d%d", &qu[o][0], &qu[o][1], &qu[o][2]);
      qu[o][0]--;
      qu[o][1]--;
      ans[o] = 0;
      q.push_back(make_pair(h[qu[o][0]] + qu[o][2], o));
    }
    sort(q.begin(), q.end());
    dsu dsu1(n);
    now = 0;
    for (i = 0; i < ee.size(); i++) {
      while ((now < q.size()) && (q[now].first < ee[i].first)) {
        ind = q[now].second;
        x = qu[ind][0];
        y = qu[ind][1];
        if (dsu1.get(x) == dsu1.get(y))
          ans[ind] = 1;
        now++;
      }
      x = ee[i].second.first;
      y = ee[i].second.second;
      dsu1.add(x, y, 1);
    }
    while (now < q.size()) {
      ind = q[now].second;
      x = qu[ind][0];
      y = qu[ind][1];
      if (dsu1.get(x) == dsu1.get(y))
        ans[ind] = 1;
      now++;
    }
    for (i = 0; i < qq; i++)
      if (ans[i] == 1)
        printf("YES\n");
      else
        printf("NO\n");
  }
}


// https://github.com/VaHiX/CodeForces/