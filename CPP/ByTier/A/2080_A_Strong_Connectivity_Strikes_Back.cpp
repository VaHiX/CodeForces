/*
 * Problem URL : https://codeforces.com/problemset/problem/2080/A
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> gr;

vector<int> st;
vector<int> t;
int timer = 0;
int cc = 0;
vector<int> comp_color;
int banned_from = -1, banned_to = -1;

void dfs(int v) {
  int tin = timer++;
  t[v] = tin;
  st.push_back(v);
  for (auto to : gr[v]) {
    if (v == banned_from && to == banned_to)
      continue;
    if (t[to] == -1) {
      dfs(to);
      t[v] = min(t[v], t[to]);
    } else if (comp_color[to] == -1) {
      t[v] = min(t[v], t[to]);
    }
  }
  if (tin == t[v]) {
    while (st.back() != v) {
      comp_color[st.back()] = cc;
      st.pop_back();
    }
    comp_color[v] = cc;
    st.pop_back();
    cc++;
  }
}

void scc_colors() {
  st.clear();
  timer = 0;
  t.assign(gr.size(), -1);
  comp_color.assign(gr.size(), -1);
  for (int i = 0; i < gr.size(); ++i) {
    if (t[i] == -1) {
      dfs(i);
    }
  }
}

int ans = 0;
int cnt = 1;

const int MOD = 1e9 + 7;

int main() {
  int n, m, group;
  cin >> n >> m >> group;
  gr.resize(n);
  vector<pair<int, int>> edges(m);
  for (auto &[u, v] : edges) {
    cin >> u >> v;
    u--, v--;
    gr[u].push_back(v);
  }

  scc_colors();

  // solve for DAG
  {
    vector<vector<int>> comp_gr_cnt(cc, vector<int>(cc));
    vector<set<int>> comp_gr(cc);
    for (auto [u, v] : edges) {
      comp_gr_cnt[comp_color[u]][comp_color[v]]++;
      if (comp_color[u] != comp_color[v]) {
        comp_gr[comp_color[u]].insert(comp_color[v]);
      }
    }
    for (int u = 0; u < cc; ++u) {
      for (int v : comp_gr[u]) {
        vector<bool> used(cc);
        used[u] = true;
        deque<int> q = {u};
        while (!q.empty()) {
          int i = q.front();
          q.pop_front();
          for (auto to : comp_gr[i]) {
            if (used[to] || i == u && to == v)
              continue;
            used[to] = true;
            q.push_back(to);
          }
        }
        if (used[v]) {
          ans += comp_gr_cnt[u][v];
        } else {
          cnt = 1ll * cnt * comp_gr_cnt[u][v] % MOD;
          ans += comp_gr_cnt[u][v] - 1;
        }
      }
    }
  }

  auto initial_comp_color = comp_color;
  vector<vector<int>> comps(cc);
  for (int i = 0; i < n; ++i) {
    comps[comp_color[i]].push_back(i);
  }

  vector<vector<bool>> used_edges(n, vector<bool>(n));
  for (int color = 0; color < comps.size(); ++color) {
    const auto &comp = comps[color];
    vector<pair<int, int>> comp_edges;
    for (int u : comp) {
      for (int v : gr[u]) {
        if (initial_comp_color[v] != color)
          continue;
        comp_edges.emplace_back(u, v);
      }
    }
    vector<vector<pair<int, int>>> S(comp_edges.size());
    for (int i = 0; i < comp_edges.size(); ++i) {
      auto [u, v] = comp_edges[i];
      banned_from = u, banned_to = v;
      scc_colors();
      for (auto [u1, v1] : comp_edges) {
        if (comp_color[u1] != comp_color[v1]) {
          S[i].emplace_back(u1, v1);
        }
      }
      if (comp_color[u] == comp_color[v]) {
        S[i].emplace_back(u, v);
      }
      banned_from = -1, banned_to = -1;
    }
    sort(S.begin(), S.end(),
         [](auto &a, auto &b) { return a.size() < b.size(); });

    int minimal_count = 0;
    for (auto &S_e : S) {
      bool minimal = true;
      for (auto [u, v] : S_e) {
        if (used_edges[u][v]) {
          minimal = false;
          break;
        }
      }
      if (minimal) {
        minimal_count++;
        cnt = 1ll * cnt * S_e.size() % MOD;
        for (auto [u, v] : S_e) {
          used_edges[u][v] = true;
        }
      }
    }
    ans += comp_edges.size() - minimal_count;
  }

  cout << ans << '\n';
  cout << cnt << '\n';
}
