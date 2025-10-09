// Problem: CF 2007 E - Iris and the Tree
// https://codeforces.com/contest/2007/problem/E

/*
E. Iris and the Tree

Algorithms/Techniques: 
- Tree traversal and parent-child relationships
- Stack-based computation of subtree structures
- Efficient update and query processing using precomputed counts and accumulations

Time Complexity: O(n) per test case, where n is the number of vertices.
Space Complexity: O(n), for storing tree structure and auxiliary arrays.

The problem involves a rooted tree with special numbering (DFS order), where edge weights must sum to w.
We process events where certain edge weights are fixed. After each event, we compute the maximum possible
sum of distances between consecutive vertices in a cycle (1 to n, then back to 1).

Key concepts:
- Each node's subtree consists of consecutive numbers due to DFS traversal order.
- For any node i, p[i] is its parent in the tree.
- The algorithm uses a stack to determine which nodes form subtrees and processes updates efficiently.

*/
#include <algorithm>
#include <iostream>
#include <stack>
using namespace std;
typedef long long ll;
constexpr int MAXN = 200000;
int p[MAXN + 5];    // Parent array: p[i] represents parent of node i
int pid[MAXN + 5];  // pid[i] stores the index of first child in subtree rooted at i
int cnt[MAXN + 5];  // cnt[i] counts how many nodes are in subtree rooted at i

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  stack<int> st;   // Stack for processing tree structure using DFS-like logic
  st.push(1);      // Start with root node (node 1)
  while (t--) {
    int n;
    ll w;
    cin >> n >> w;
    for (int i = 2; i <= n; i++)
      cin >> p[i];
    fill(pid, pid + n + 2, 0);     // Initialize parent ID array
    fill(cnt, cnt + n + 2, 1);     // Initialize count of nodes in subtree at each node (start with 1 for each node)
    cnt[n + 1] = 0;                // Mark end as non-existent
    p[n + 1] = 1;                  // Set parent of dummy node to root
    for (int i = 2; i <= n + 1; i++) {
      while (st.top() != p[i]) {   // While the top of stack is not the current node's parent
        cnt[i]++;                  // Increase count for this node
        pid[st.top()] = i;         // Set the first child ID of the popped node to i
        st.pop();                  // Pop from stack
      }
      st.push(i);                  // Push the current node onto stack
    }
    st.pop();                      // Clean up stack after loop

    ll acc = 0;                    // Accumulated weight so far (used in calculating max distance)
    int u1 = n;                    // Number of nodes in the tree, initially all nodes (n)
    for (int i = 0; i < n - 1; i++) {
      int x;
      ll y;
      cin >> x >> y;
      acc += y;                    // Add new weight to accumulated sum
      cnt[x]--;                    // Decrease count in subtree rooted at x because one edge is now fixed
      if (cnt[x] == 0)             // If no more nodes in subtree of x, decrease node counter
        --u1;
      if (pid[x]) {                // If there's a parent node associated with this fixed edge
        acc += y;                  // Add to accumulated weight for calculation purposes
        cnt[pid[x]]--;             // Decrease child count
        if (cnt[pid[x]] == 0)      // If no more children, decrease global node counter
          --u1;
      }
      w -= y;                      // Reduce remaining total weight w
      ll ans = w * u1 + acc;       // Compute final sum using formula derived for maximum distances
      cout << ans << ' ';
    }
    cout << '\n';
  }
}


// https://github.com/VaHiX/codeForces/