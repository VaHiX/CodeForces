// Problem: CF 1787 D - Game on Axis
// https://codeforces.com/contest/1787/problem/D

/*
 * Problem: Game on Axis
 * 
 * Algorithm: 
 * - Identify the main path (cycle or path ending in out-of-bounds)
 * - For each point, determine where it leads (to out-of-bounds or into a cycle)
 * - Count valid (x, y) pairs such that after assigning y to a[x], the game ends
 * 
 * Time Complexity: O(n) amortized per test case due to each node visited at most once
 * Space Complexity: O(n) for storing path, visited array, and auxiliary arrays
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>
#include <type_traits>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define MAXN 1000000
using namespace std;

template <typename F> struct y_combinator_result {
  F f;
  template <typename T>
  explicit y_combinator_result(T &&f) : f(forward<T>(f)) {}
  template <typename... Args> decltype(auto) operator()(Args &&...args) {
    return f(ref(*this), forward<Args>(args)...);
  }
};
template <typename F> decltype(auto) y_combinator(F &&f) {
  return y_combinator_result<decay_t<F>>(forward<F>(f));
}

void solve() {
  int n;
  cin >> n;
  vector<int> step(n);
  for (int i = 0; i < n; i++) {
    cin >> step[i];
  }
  
  // Track the main path and order of visited nodes
  vector<bool> main_path(n);
  vector<int> main_ord;
  int cur = 0;
  bool self_loop = false;
  
  // Find the path from start (index 0) until we hit out-of-bounds or loop
  while (true) {
    main_path[cur] = true;
    main_ord.push_back(cur);
    cur += step[cur];
    if (cur < 0 || cur >= n) {
      break; // Game ends if out of bounds
    } else if (main_path[cur]) {
      self_loop = true; // We detected a cycle
      break;
    }
  }

  // Initialize arrays for tracking escape destinations
  vector<int> leads_to(n + 1); // leads_to[i] = where i leads to, or n if out of bounds
  vector<bool> vis(n); // Track visited nodes for escape computation

  // This recursive function determines where each position leads
  auto get_escape = y_combinator([&](auto self, int x) -> int {
    if (!vis[x]) {
      vis[x] = true;
      leads_to[x] = -1; // Mark as being processed
      auto nxt = x + step[x];
      if (nxt < 0 || nxt >= n) {
        leads_to[x] = n; // Out of bounds
      } else if (main_path[nxt]) {
        leads_to[x] = nxt; // Leads to the main path
      } else {
        leads_to[x] = self(nxt); // Recurse to the next node
      }
    }
    return leads_to[x];
  });

  // Count how many nodes lead to each destination
  vector<int> count_leads_to(n + 1);
  for (int i = 0; i < n; i++) {
    auto dst = get_escape(i);
    if (dst != -1) {
      count_leads_to[dst]++;
    }
  }

  if (self_loop) {
    // If there's a loop, count how many valid (x,y) pairs end the game
    
    // num_go: number of valid y choices that can be assigned to any x
    int num_go = n + 1 + count(leads_to.begin(), leads_to.end(), n);
    int on_main_path = count(main_path.begin(), main_path.end(), true);
    
    // Calculate total pairs: (nodes on main path) * (valid values for y)  
    cout << (ll)on_main_path * num_go << '\n';
  } else {
    // No loop, all paths lead to out-of-bounds
    int on_main_path = count(main_path.begin(), main_path.end(), true);
    
    // Initial result from non-main-path nodes and y value range
    ll ans = (ll)(n - on_main_path) * (2 * n + 1);
    
    int sz = main_ord.size();
    int swap_to = n + 1 + count_leads_to[n];
    
    // Iterate backwards through the main path to accumulate counts
    for (int i = sz - 1; i >= 0; i--) {
      ans += swap_to - 1; // Add number of valid y values for this x
      swap_to += count_leads_to[main_ord[i]];
    }
    cout << ans << '\n';
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/