// Problem: CF 1893 D - Colorful Constructive
// https://codeforces.com/contest/1893/problem/D

/*
Purpose:
This code solves a problem where we need to distribute colored cubes onto shelves such that each shelf meets a minimum colorfulness requirement. 
The colorfulness of a shelf is defined as the minimum distance between two cubes of the same color on that shelf.
If all cubes on the shelf have different colors, the colorfulness is the size of the shelf.

Approach:
1. Count occurrences of each color.
2. Use a priority queue to always pick the most frequent color first.
3. For each shelf, greedily place colors ensuring the minimum required colorfulness is achieved.
4. Maintain a sliding window of size (d[i] - 1) to ensure no two same-colored cubes are closer than d[i].

Time Complexity: O(n log n) per test case due to priority queue operations and linear traversal.
Space Complexity: O(n) for storing counts, priority queue, and output.

Algorithms/Techniques:
- Greedy approach with priority queue
- Sliding window technique to enforce minimum colorfulness constraint
*/
#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
typedef pair<int, int> pii;
int main() {
  ios::sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), s(m), d(m);
    priority_queue<pii> q;
    // Count frequency of each color
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      a[x - 1]++;
    }
    // Push all non-zero frequencies into priority queue
    for (int i = 0; i < n; i++)
      if (a[i])
        q.emplace(a[i], i);
    for (auto &i : s)
      cin >> i;
    for (auto &i : d)
      cin >> i;
    bool f = true;
    vector<vector<int>> r(m);
    // Distribute cubes to shelves
    for (int i = 0; i < m && f; i++)
      for (int j = 0; j < s[i] + d[i] - 1; j++) {
        // Place a cube if there's space
        if (j < s[i]) {
          if (q.empty()) {
            f = false;
            break;
          }
          r[i].emplace_back(q.top().second), q.pop();
        }
        // Re-add color to queue after removing it from sliding window
        if (j >= d[i] - 1) {
          int x = r[i][j - d[i] + 1];
          if (--a[x])
            q.emplace(a[x], x);
        }
      }
    if (f)
      for (auto i : r) {
        for (int j : i)
          cout << j + 1 << ' ';
        cout << '\n';
      }
    else
      cout << "-1\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/