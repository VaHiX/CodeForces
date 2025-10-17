/*
 * Problem URL : https://codeforces.com/contest/39/problem/K
 * Submit Date : 2025-09-09
 */

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;
long long output;
int n, m, i, j, k, x, y, l, r, P[220], vc, ss, u, d;
char ar[1010][1010];
int get(int x) { return lower_bound(P + 1, P + ss + 1, x) - P; }
struct sss {
  int x1, x2, y1, y2;
  void make_pair(int p1, int p2, int q1, int q2) {
    x1 = p1;
    x2 = p2;
    y1 = q1;
    y2 = q2;
  }
} a[120];

int main() {
  scanf("%d%d%d", &n, &m, &k);

  for (i = 1; i <= n; ++i)
    scanf("%s", ar[i] + 1);
  for (i = 1; i <= n; ++i)
    for (j = 1; j <= m; ++j)
      if (ar[i][j] == '*') {
        k = j;
        while (ar[i][k] == '*')
          k++;
        k--;
        l = i;
        while (ar[l][j] == '*')
          l++;
        l--;
        for (x = i; x <= l; ++x)
          for (y = j; y <= k; ++y)
            ar[x][y] = '.';
        a[++vc].make_pair(i, l, j, k);
        P[++ss] = i;
        P[++ss] = l;
      }
  P[++ss] = 0;
  P[++ss] = n + 1;
  sort(P + 1, P + ss + 1);
  ss = unique(P + 1, P + ss + 1) - P - 1;
  for (i = 1; i <= vc; ++i)
    a[i].x1 = get(a[i].x1), a[i].x2 = get(a[i].x2);
  for (u = 2; u < ss; ++u) {
    for (d = u; d < ss; ++d) {
      long long tmp = 0;
      vector<pair<int, int>> vec;
      for (i = 1; i <= vc; ++i) {
        if (a[i].x2 < u || a[i].x1 > d)
          continue;
        if (a[i].x1 >= u && a[i].x2 <= d)
          vec.push_back(make_pair(a[i].y1, -1)),
              vec.push_back(make_pair(a[i].y2, 1));
        else
          vec.push_back(make_pair(a[i].y1, -100)),
              vec.push_back(make_pair(a[i].y2, 100));
      }
      sort(vec.begin(), vec.end());
      int num = vec.size(), C, suml, sumr, cc;
      vec.push_back(make_pair(m + 1, 0));
      for (int C = 1; C <= 3; ++C) {
        suml = sumr = 0;
        cc = 0;
        for (l = 0, r = 0; r < num; ++r) {
          sumr += vec[r].second;
          cc += max(0, vec[r].second);
          if (!sumr) {
            while (suml || cc > C) {
              suml -= vec[l].second;
              cc -= max(0, vec[l].second);
              l++;
            }
            if (!suml && cc == C)
              tmp += (vec[r + 1].first - vec[r].first) *
                     (vec[l].first - (!l ? 0 : vec[l - 1].first));
          }
        }
      }
      output += tmp * (P[u] - P[u - 1]) * (P[d + 1] - P[d]);
    }
  }
  printf("%I64d\n", output);

  return 0;
} /*1694762527.2786834*/