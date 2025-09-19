/*
 * Problem URL : https://codeforces.com/problemset/problem/1784/B
 * Submit Date : 2025-08-21
 */

// LUOGU_RID: 151818717
#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
int cnt[3];
vector<int> edge[3][3];
int check(char ch) {
  if (ch == 'w')
    return 0;
  if (ch == 'i')
    return 1;
  if (ch == 'n')
    return 2;
}
char solve(int ch) {
  if (ch == 0)
    return 'w';
  if (ch == 1)
    return 'i';
  if (ch == 2)
    return 'n';
}
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int m;
    scanf("%d", &m);
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        edge[i][j].clear();
    for (int i = 1; i <= m; i++) {
      char str[5];
      scanf("%s", str);
      cnt[0] = cnt[1] = cnt[2] = 0;
      cnt[check(str[0])]++;
      cnt[check(str[1])]++;
      cnt[check(str[2])]++;
      for (int j = 0; j < 3; j++)
        for (int k = 0; k < 3; k++) {
          if (cnt[j] > 1 && cnt[k] < 1) {
            edge[j][k].push_back(i);
          }
        }
    }
    vector<array<int, (int)4>> ans;
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++) {
        while (edge[i][j].size() && edge[j][i].size()) {
          int p = edge[i][j].back();
          edge[i][j].pop_back();
          int q = edge[j][i].back();
          edge[j][i].pop_back();
          ans.push_back({p, i, q, j});
        }
      }
    for (int i = 0; i < edge[0][1].size(); i++) {
      int p1 = edge[0][1][i];
      int p2 = edge[1][2][i];
      int p3 = edge[2][0][i];
      ans.push_back({p1, 0, p2, 1});
      ans.push_back({p2, 0, p3, 2});
    }
    for (int i = 0; i < edge[1][0].size(); i++) {
      int p1 = edge[1][0][i];
      int p2 = edge[0][2][i];
      int p3 = edge[2][1][i];
      ans.push_back({p1, 1, p2, 0});
      ans.push_back({p2, 1, p3, 2});
    }
    printf("%d\n", ans.size());
    for (int i = 0; i < ans.size(); i++) {
      array<int, (int)4> cur = ans[i];
      printf("%d %c ", cur[0], solve((int)cur[1]));
      printf("%d %c\n", cur[2], solve((int)cur[3]));
    }
  }
  return 0;
}