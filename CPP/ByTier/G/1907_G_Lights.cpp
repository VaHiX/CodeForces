// Problem: CF 1907 G - Lights
// https://codeforces.com/contest/1907/problem/G

/*
Algorithm: Graph processing with topological sort and cycle detection
Approach:
1. Build a directed graph where each node i points to a[i] (switch i affects light a[i])
2. Use topological sort to process lights with no incoming edges
3. For remaining lights in cycles, determine if it's possible to turn them off
4. If a cycle has an odd number of '1's, it's impossible to turn all lights off

Time Complexity: O(n) - Each node and edge processed at most once
Space Complexity: O(n) - For storing graph, in-degrees, and result
*/

#include <ctype.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;
typedef long long ll;
#define rep(i, j, k) for (int i = j; i < k; ++i)
ll input() {
  char ch = cin.get();
  ll x = 0, y = 1;
  for (; !isdigit(ch); ch = cin.get())
    if (ch == '-')
      y = -1;
  for (; isdigit(ch); ch = cin.get())
    x = (x << 1) + (x << 3) + (ch ^ '0');
  return x * y;
}
void solve() {
  int n;
  cin >> n;
  string s;
  cin >> s;
  vector<int> a(n), in(n);
  rep(i, 0, n) {
    a[i] = input();
    a[i]--;
    in[a[i]]++;
  }
  queue<int> q;
  vector<int> ans;
  rep(i, 0, n) if (!in[i]) q.push(i);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    if (s[u] == '1') {
      s[u] = '0';
      s[a[u]] ^= 1;     // Toggle the state of light a[u] using XOR
      ans.push_back(u);
    }
    if (!(--in[a[u]]))   // Decrease in-degree of a[u], if 0 push to queue
      q.push(a[u]);
  }
  rep(i, 0, n) {
    if (in[i]) {
      int j = i, len = 0, t = 0, res = 0;
      while (in[j]) {
        if (s[j] == '1')
          t ^= 1;
        res += t;
        len++;
        in[j] = 0;
        j = a[j];    // Traverse the cycle
      }
      if (t) {
        cout << -1 << '\n';
        return;
      } else {
        rep(k, 0, len) {
          if (s[j] == '1')
            t ^= 1;
          if (t == (res < len - res)) {
            ans.push_back(j);
          }
          j = a[j];
        }
      }
    }
  }
  cout << ans.size() << '\n';
  for (auto x : ans) {
    cout << x + 1 << " \n"[x == ans.back()];
  }
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/