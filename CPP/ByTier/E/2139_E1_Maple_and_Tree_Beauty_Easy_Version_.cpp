/*
 * Problem URL : https://codeforces.com/contest/2139/problem/E1
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;
int ans, dep[1005], hashh[1005];
vector<int> son[1005];
void dfs(int u) {
  for (auto v : son[u]) {
    dep[v] = dep[u] + 1;
    dfs(v);
  }
  if (son[u].empty())
    ans = min(ans, dep[u]);
  hashh[dep[u]]++;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T, n, k, cnt, flag;
  cin >> T;
  while (T--) {
    bitset<1005> dp;
    dp.set(0);
    cin >> n >> k;
    ans = n;
    cnt = 0;
    flag = 0;
    for (int i = 0; i <= n; i++)
      hashh[i] = 0;
    for (int i = 2, s; i <= n; i++)
      cin >> s, son[s].push_back(i);
    dfs(1);
    for (int i = 0; i <= n; i++) {
      if (dep[i] > ans)
        cnt++;
      if (i <= ans && hashh[i])
        dp |= dp << hashh[i];
    }
    for (int i = 0; !flag && i <= n; i++) {
      if (dp.test(i) && k - i <= cnt && k - i >= 0)
        flag = 1;
    }
    cout << (flag ? ans + 1 : ans) << "\n";
    for (int i = 1; i <= n; i++)
      son[i].clear();
  }
  return 0;
}