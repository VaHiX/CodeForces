/*
 * Problem URL : https://codeforces.com/contest/838/problem/A
 * Submit Date : 2025-09-04
 */

#include <bits/stdc++.h>
using namespace std;
constexpr int Maxn = 2505;
int n, m;
char arr[Maxn][Maxn];
int S[Maxn][Maxn];
int res = Maxn * Maxn;
int Get(int r1, int c1, int r2, int c2) {
  r2 = min(r2, n), c2 = min(c2, m);
  return S[r2][c2] - S[r1 - 1][c2] - S[r2][c1 - 1] + S[r1 - 1][c1 - 1];
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(__null);
  scanf("%d%d", &n, &m);

  for (int i = 1; i <= n; ++i)
    scanf("%s", arr[i] + 1);

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      S[i][j] = S[i - 1][j] + S[i][j - 1] - (S[i - 1][j - 1]) +
                (int)(arr[i][j] == '1');

  for (int i = 2; i <= n || i <= m; ++i) {
    int sum = 0;
    for (int j = 1; j <= n; j += i)
      for (int k = 1; k <= m; k += i) {
        int g = Get(j, k, j + i - 1, k + i - 1);
        sum += min(g, i * i - g);
      }
    res = min(res, sum);
  }
  cout << res << endl;
  return 0;
}