/*
 * Problem URL : https://codeforces.com/contest/2036/problem/D
 * Submit Date : 2025-09-06
 */

#include <cstdio>
#include <string>
#include <vector>
using namespace std;
int t, n, m, i, j, k, l, x, y, c;
char s[1000005], a[1005][1005];
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &m);
    for (i = 0; i < n; i++)
      scanf("%s", a[i]);
    c = 0;
    for (l = 0; l < min(n, m) / 2; l++) {
      vector<char> v;
      int u = n - 1 - l, w = m - 1 - l;
      for (j = l; j <= w; j++)
        v.push_back(a[l][j]);
      for (i = l + 1; i <= u; i++)
        v.push_back(a[i][w]);
      if (u > l)
        for (j = w - 1; j >= l; j--)
          v.push_back(a[u][j]);
      if (w > l)
        for (i = u - 1; i > l; i--)
          v.push_back(a[i][l]);
      int sz = v.size();
      string s(v.begin(), v.end());
      for (k = 0; k < sz; k++) {
        if (s[k] == '1' && s[(k + 1) % sz] == '5' && s[(k + 2) % sz] == '4' &&
            s[(k + 3) % sz] == '3')
          c++;
      }
    }
    printf("%d\n", c);
  }
}
