// Problem: CF 2031 E - Penchick and Chloe's Trees
// https://codeforces.com/contest/2031/problem/E

/*
E. Penchick and Chloe's Trees
Algorithms/Techniques: Dynamic Programming on Tree, Greedy with Priority Queue
Time Complexity: O(n log n) per test case due to priority queue operations
Space Complexity: O(n) for storing tree structure and auxiliary arrays

This problem asks to find the minimum depth of a perfect binary tree that is isomorphic 
to the given rooted tree. The key idea is to compute for each node the "height" or "depth"
of the subtree rooted at that node under optimal operations (removing leaves and reattaching
children). The result for root node gives us the minimal depth required.
*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
const int N = 1e6 + 2;
int T, n, f[N]; // f[i] stores the computed value for node i
vector<int> e[N]; // adjacency list for children of each node
priority_queue<int, vector<int>, greater<int>> q; // min-heap to process subtree heights

int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (cin >> T; T--;) {
    cin >> n;
    for (int i = 2, x; i <= n; ++i)
      cin >> x, e[x].push_back(i); // build the tree from parent info
    
    for (int i = n; i; --i) {
      if (!e[i].size()) {
        f[i] = 0; // leaf nodes have depth 0
        continue;
      }
      // Process all children of node i and push their depths into heap
      for (int v : e[i])
        q.push(f[v]);
      
      // Greedily merge smallest depths to minimize total height
      for (int x; q.size() > 1;) {
        q.pop(); // remove the smallest
        x = q.top(), q.pop();
        q.push(x + 1); // add the updated value back, effectively merging two subtrees
      }
      
      // Assign f[i] based on merged result and whether node i has only one child
      f[i] = q.top() + (e[i].size() == 1), q.pop();
      e[i].clear(); // clear the edge list to save space
    }
    
    cout << f[1] << '\n'; // minimum depth of perfect binary tree isomorph to input
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/