/*
 * Problem URL : https://codeforces.com/contest/2034/problem/H
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef pair<int, vector<int>> pivi;

const int MAX = 1e5 + 1;
const int ROOT = 46;

int prime[MAX];
vector<pivi> combs;
vector<pii> adj[MAX], out[MAX];
vector<int> pws[MAX], divs[MAX];
vector<int> nodes;
int label[MAX];
int mult[MAX];

void init() {
  for (int i = 2; i < MAX; i++)
    if (!prime[i])
      for (int j = i; j < MAX; j += i)
        if (!prime[j])
          prime[j] = i;
  for (int i = 2; i < MAX; i++) {
    int j = i / prime[i];
    pws[i] = pws[j];
    if (j % prime[i])
      pws[i].push_back(1);
    pws[i].back() *= prime[i];
  }
  for (int i = 1; i < MAX; i++)
    sort(pws[i].begin(), pws[i].end(), greater<int>());
  for (int i = 1; i < MAX; i++)
    for (int j = i; j < MAX; j += i)
      divs[j].push_back(i);
  for (int i = 2; i < MAX; i++)
    for (int j = 1; j < ROOT && j < pws[i].back(); j++)
      if (pws[j].size() == 1 && i % prime[j]) {
        vector<int> tmp = pws[i];
        tmp.push_back(j);
        int prod = i * j;
        for (auto &it : tmp)
          it = prod / it;
        combs.push_back({prod, tmp});
      }
}

void give(int u, int v, int w) {
  if (adj[u].empty())
    nodes.push_back(u);
  adj[u].push_back({v, w});
}

void add_edge(int u, int v, int w) {
  give(u, v, w);
  give(v, u, w);
}

void solve() {
  int N;
  scanf("%d", &N);
  vector<int> a(N);
  for (auto &it : a)
    scanf("%d", &it);
  sort(a.begin(), a.end());
  vector<int> ans;
  for (auto it1 : a)
    for (auto it2 : divs[it1])
      mult[it2]++;
  pivi opt;
  for (const auto &it : combs)
    if (it.second.size() > opt.second.size()) {
      bool ok = true;
      for (auto elem : it.second)
        if (mult[elem] == (it.first < MAX ? mult[it.first] : 0)) {
          ok = false;
          break;
        }
      if (ok)
        opt = it;
    }
  for (auto it : opt.second)
    for (auto elem : a)
      if (elem % opt.first && !(elem % it)) {
        ans.push_back(elem);
        break;
      }
  for (auto it1 : a)
    for (auto it2 : divs[it1])
      mult[it2]--;
  if (ans.size() < 3) {
    for (auto it : a)
      if (pws[it].size() >= 2 && pws[it][1] > ROOT)
        add_edge(prime[pws[it][0]], prime[pws[it][1]], it);
    for (auto it1 : nodes)
      for (auto it2 : adj[it1])
        if (pii(adj[it1].size(), it1) < pii(adj[it2.first].size(), it2.first))
          out[it1].push_back(it2);
    for (auto it1 : nodes) {
      for (auto it2 : out[it1])
        label[it2.first] = it2.second;
      for (auto it2 : out[it1])
        for (auto it3 : out[it2.first])
          if (label[it3.first])
            ans = {it2.second, it3.second, label[it3.first]};
      for (auto it2 : out[it1])
        label[it2.first] = 0;
    }
    for (auto it : nodes) {
      adj[it].clear();
      out[it].clear();
    }
    nodes.clear();
  }
  if (ans.size() < 2) {
    ans = {a[0]};
    for (int i = 1; i < N; i++)
      if (a[i] % a[i - 1]) {
        ans = {a[i], a[i - 1]};
        break;
      }
  }
  printf("%d\n", ans.size());
  for (auto it : ans)
    printf("%d ", it);
  puts("");
}

int main() {
  init();
  int tc;
  scanf("%d", &tc);
  while (tc--)
    solve();
  return 0;
}