// Problem: CF 1572 A - Book
// https://codeforces.com/contest/1572/problem/A

/*
 * Task: Determine how many reads of a book are needed to understand all chapters,
 *       or return -1 if it's impossible.
 *
 * Algorithms/Techniques:
 *   - Topological sorting using Kahn's algorithm with BFS
 *   - Dynamic programming on DAG to track maximum depth/final reading order
 *
 * Time Complexity: O(n + sum(k_i)) where n is number of chapters and sum(k_i) is total prerequisites
 * Space Complexity: O(n) for adjacency list, degree array, and queue storage
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <queue>
#include <vector>

using namespace std;

void solve() {
  int n, ans = 0;
  cin >> n;
  vector<int> d(n), f(n, 1);           // d: in-degrees, f: max depth to understand chapter
  vector<vector<int>> e(n);            // e: adjacency list (predecessors -> successors)
  queue<int> q;                        // queue for topological BFS
  for (int i = 0; i < n; i++) {
    cin >> d[i];                       // read number of prerequisites for chapter i
    for (int j = 0, x; j < d[i]; j++)
      cin >> x, e[x - 1].push_back(i); // build reverse adjacency list: prerequisite -> dependent
    if (!d[i])                         // if no prerequisites, add to queue
      q.push(i);
  }
  while (!q.empty()) {
    int x = q.front();                 // get current chapter with all prerequisites met
    q.pop();
    ans = max(ans, f[x]);              // update answer with depth of this chapter
    for (int y : e[x]) {               // iterate over dependent chapters
      f[y] = max(f[y], f[x] + (x > y)); // compute new depth, add 1 if x > y for order constraint
      if (!--d[y])                     // decrement in-degree
        q.push(y);                     // if in-degree becomes zero, add to queue
    }
  }
  if (count(begin(d), end(d), 0) != n) // if not all nodes are processed, cycle exists
    cout << "-1\n";
  else
    cout << ans << "\n";
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/