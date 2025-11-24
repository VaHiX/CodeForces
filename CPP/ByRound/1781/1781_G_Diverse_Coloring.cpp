// Problem: CF 1781 G - Diverse Coloring
// https://codeforces.com/contest/1781/problem/G

/*
 * Problem: G. Diverse Coloring
 * 
 * Purpose: This code solves the problem of finding the minimum disbalance of a diverse coloring
 *          for a rooted binary tree that is built incrementally. A diverse coloring ensures
 *          that every vertex has at least one neighbor (parent or child) of the opposite color.
 *          The disbalance is defined as the absolute difference between the number of white
 *          and blue vertices.
 * 
 * Approach:
 * - For each step of adding a vertex, we compute the minimum disbalance for the current tree.
 * - We use a greedy method and bitmasking for small remaining components.
 * - The tree is represented with adjacency lists, and we process leaves first.
 * 
 * Algorithms/Techniques:
 * - Greedy algorithm for coloring
 * - BFS/DFS for traversal
 * - Bitmasking for small components
 * - Priority queue for leaf nodes
 * 
 * Time Complexity: O(n * 2^k) where n is the number of vertices and k is the size of the small component (k <= 10)
 * Space Complexity: O(n) for storing the tree and auxiliary arrays
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

int n, a[200010], p[200010], d[200010], ans[200010], vis[200010];
vector<int> v[200010];

int main() {
  int T;
  cin >> T;
  while (T--) {
    priority_queue<pair<int, int>> q;
    int cnt = 0, tot;
    cin >> n;
    for (int i = 1; i <= n; i++)
      vis[i] = 0, v[i].clear();
    for (int i = 2; i <= n; i++)
      cin >> p[i];
    // Print initial disbalance values based on specific conditions
    for (int i = 2; i <= n; i++) {
      if (i == 4)
        cout << (p[3] == p[4]) * 2 << '\n';
      else if (i & 1)
        cout << 1 << '\n';
      else
        cout << 0 << '\n';
    }
    // Build tree structure
    for (int i = 2; i <= n; i++)
      v[p[i]].push_back(i), d[i] = d[p[i]] + 1;
    // Initialize queue with leaf nodes
    for (int i = 2; i <= n; i++)
      if (!v[i].size())
        q.push(make_pair(d[i], i));
    tot = n;
    // Process the tree by removing leaf nodes in a greedy fashion
    while (tot > 10) {
      int x = q.top().second;
      q.pop();
      if (vis[x])
        continue;
      if (v[p[x]].size() == 1) {
        ans[p[x]] = 1;
        ans[x] = 0;
        vis[x] = vis[p[x]] = 1;
        tot -= 2;
        int y = p[p[x]];
        v[y].erase(find(v[y].begin(), v[y].end(), p[x]));
        if (!v[y].size())
          q.push(make_pair(d[y], y));
      } else {
        a[++cnt] = p[x];
        vis[v[p[x]][0]] = vis[v[p[x]][1]] = vis[p[x]] = 1;
        tot -= 3;
        int y = p[p[x]];
        v[y].erase(find(v[y].begin(), v[y].end(), p[x]));
        if (!v[y].size())
          q.push(make_pair(d[y], y));
      }
    }
    // Handle the remaining small component with bitmasking
    vector<int> b;
    for (int i = 1; i <= n; i++)
      if (!vis[i])
        b.push_back(i);
    int anss = 1e9, id;
    for (int i = 0; i < (1 << tot); i++) {
      int k = 0;
      for (int j = 0; j < tot; j++) {
        ans[b[j]] = (i >> j) & 1;
        if (i & (1 << j))
          k++;
        else
          k--;
      }
      if (k < 0)
        continue;
      int f = 1;
      for (int j = 0; j < tot; j++) {
        int ff = 0;
        if (p[b[j]] && ans[p[b[j]]] != ans[b[j]])
          ff = 1;
        for (auto y : v[b[j]])
          if (ans[b[j]] != ans[y])
            ff = 1;
        f &= ff;
      }
      if (f && k < anss)
        anss = k, id = i;
    }
    for (int j = 0; j < tot; j++)
      ans[b[j]] = (id >> j) & 1;
    // Final coloring update for the greedy components
    for (int i = 1; i <= cnt; i++) {
      if (anss > 0)
        ans[a[i]] = 1, ans[v[a[i]][0]] = ans[v[a[i]][1]] = 0, anss--;
      else
        ans[a[i]] = 0, ans[v[a[i]][0]] = ans[v[a[i]][1]] = 1, anss++;
    }
    // Print the final coloring result
    for (int i = 1; i <= n; i++)
      cout << (ans[i] ? 'w' : 'b');
    cout << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/