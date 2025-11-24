// Problem: CF 2041 I - Auto Complete
// https://codeforces.com/contest/2041/problem/I

/*
 * Task: Implement an auto-complete feature using a Trie data structure with dynamic updates.
 *
 * Algorithms/Techniques:
 * - Trie (Prefix Tree) for efficient prefix matching
 * - Priority Queue (min-heap) to maintain lexicographically sorted candidates per node
 * - Path tracking via 'fa' and current position 'now'
 * - Dynamic update of best match on each operation using 'pushup' recursion
 *
 * Time Complexity: O(n * m * log k), where n is number of operations, m is average string length, 
 *                  and k is number of patterns with matching prefix.
 * Space Complexity: O(total characters in all strings + n)
 */

#include <string.h>
#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <utility>
#include <vector>

#define maxn 2000010
using namespace std;
using ll = long long;
int tot = 0, fa[maxn];
map<int, int> son[maxn];
string s[maxn];
priority_queue<int, vector<int>, greater<int>> trie[maxn];
int res[maxn];
bool vis[maxn];

// Propagate updated best match up the tree from node x
void pushup(int x) {
  int mx = 0, id = -1;
  // Iterate through each child of node x to find best pattern
  for (auto [i, y] : son[x]) {
    if (res[y] != -1 && s[res[y]].size() > mx) {
      mx = s[res[y]].size();
      id = res[y];
    }
  }
  // If no match was found but there are patterns at this node, pick the smallest one
  if (id == -1 && trie[x].size())
    id = trie[x].top();
  // If better pattern than current is found, update and propagate upward
  if (id != res[x]) {
    res[x] = id;
    if (x)
      pushup(fa[x]); // Recurse to parent
  }
}

// Add a string t with ID to the trie structure
void add(string &t, int id) {
  int p = 0, len = t.size();
  for (int i = 0; i < len; i++) {
    char c = t[i] - 33;
    if (son[p].find(c) == son[p].end()) {
      son[p][c] = ++tot;
      fa[tot] = p;
    }
    p = son[p][c];
  }
  trie[p].push(id); // Record the ID in node's priority queue
  pushup(p);        // Update best match for this node and ancestors
}

// Delete a string t from the trie structure
void del(string &t) {
  int p = 0, len = t.size();
  for (int i = 0; i < len; i++) {
    char c = t[i] - 33;
    p = son[p][c];
  }
  // Remove deleted IDs from the priority queue
  while (!trie[p].empty() && vis[trie[p].top()])
    trie[p].pop();
  pushup(p); // Update best match for this node and ancestors
}

void solve() {
  int n;
  cin >> n;
  int now = 0;
  memset(res, -1, sizeof(res));
  while (n--) {
    string opt;
    cin >> opt;
    if (opt == "add") {
      int id;
      cin >> id;
      cin >> s[id];
      add(s[id], id);
    } else if (opt == "delete") {
      int id;
      cin >> id;
      vis[id] = 1; // Mark as deleted
      del(s[id]);
    } else if (opt == "append") {
      string t;
      cin >> t;
      for (auto c : t) {
        c -= 33;
        if (son[now].find(c) == son[now].end()) {
          son[now][c] = ++tot;
          fa[tot] = now;
        }
        now = son[now][c]; // Move to next node
      }
    } else if (opt == "backspace") {
      int t;
      cin >> t;
      while (now && t--)
        now = fa[now]; // Backtrack in the trie
    }
    cout << res[now] << '\n'; // Output best match at current position
  }
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T = 1;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/