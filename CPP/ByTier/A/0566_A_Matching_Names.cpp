/*
 * Problem URL : https://codeforces.com/contest/566/problem/A
 * Submit Date : 2025-09-05
 */

#include <bits/stdc++.h>

const int N = 800005;

int n, nxt[N][26], dep[N], idx, ans;
std::string s;

std::vector<int> L[N], R[N];
std::vector<std::pair<int, int>> ret;

int insert(const std::string &s) {
  int now = 0;
  for (char ch : s) {
    if (!nxt[now][ch - 'a']) {
      nxt[now][ch - 'a'] = ++idx;
      dep[idx] = dep[now] + 1;
    }
    now = nxt[now][ch - 'a'];
  }
  return now;
}
void dfs(int x) {
  for (int i = 0; i < 26; ++i)
    if (nxt[x][i])
      dfs(nxt[x][i]);
  for (int i = 0; i < 26; ++i)
    if (nxt[x][i]) {
      if (L[nxt[x][i]].size() > L[x].size())
        std::swap(L[x], L[nxt[x][i]]);
      if (R[nxt[x][i]].size() > R[x].size())
        std::swap(R[x], R[nxt[x][i]]);
    }
  for (int i = 0; i < 26; ++i)
    if (nxt[x][i]) {
      L[x].insert(L[x].end(), L[nxt[x][i]].begin(), L[nxt[x][i]].end());
      L[nxt[x][i]].clear();
      R[x].insert(R[x].end(), R[nxt[x][i]].begin(), R[nxt[x][i]].end());
      R[nxt[x][i]].clear();
    }
  ans += std::min(L[x].size(), R[x].size()) * dep[x];
  while (L[x].size() && R[x].size()) {
    ret.emplace_back(L[x].back(), R[x].back());
    L[x].pop_back(), R[x].pop_back();
  }
}

int main() {
  std::ios::sync_with_stdio(0), std::cin.tie(0);
  std::cin >> n;
  for (int i = 1; i <= n; ++i)
    std::cin >> s, L[insert(s)].emplace_back(i);
  for (int i = 1; i <= n; ++i)
    std::cin >> s, R[insert(s)].emplace_back(i);
  dfs(0);
  std::cout << ans << '\n';
  for (auto p : ret)
    std::cout << p.first << ' ' << p.second << '\n';
  return 0;
}
