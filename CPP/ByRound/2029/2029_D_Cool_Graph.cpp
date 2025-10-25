/*
 * Problem URL : https://codeforces.com/contest/2029/problem/D
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;
int n, m, t[100005];
vector<array<int, 3>> ans;
void op(int x, int y, int z) { ans.push_back({x, y, z}); }
void doing() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    t[i] = 0;
  for (int i = 1, j, k; i <= m; i++) {
    scanf("%d %d", &j, &k);
    if (j > k)
      swap(j, k);
    if (j > 1)
      op(1, j, k);
    t[j] ^= 1, t[k] ^= 1;
  }
  int p = 0;
  for (int i = 2; i <= n; i++)
    if (t[i])
      p = i;
  if (p)
    for (int i = 2; i <= n; i++)
      if (!t[i])
        op(1, p, i), p = i;
  cout << ans.size() << "\n";
  for (auto i : ans)
    printf("%d %d %d\n", i[0], i[1], i[2]);
  ans.clear();
}
int main() {
  int T;
  cin >> T;
  while (T--)
    doing();
}