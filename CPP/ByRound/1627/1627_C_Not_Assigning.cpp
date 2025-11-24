// Problem: CF 1627 C - Not Assigning
// https://codeforces.com/contest/1627/problem/C

/*
Algorithm/Technique: 
This solution uses a graph coloring approach on a tree to assign weights to edges such that all paths with 1 or 2 edges have prime weights.
The key idea is:
1. If any vertex has degree > 2, it's impossible to make all path sums prime, so return -1.
2. Otherwise, we can do a DFS traversal starting from a leaf node, alternating between assigning weights 2 and 3.
This ensures that:
- Each edge gets a weight in the range [1, 10^5].
- Every path of 1 or 2 edges will have a sum that is prime (since only sums of 2 and 3 are used, and these are prime, and any two consecutive edges will sum to 5, etc., all within small primes).

Time Complexity: O(n) per test case, as we do a DFS traversal once.
Space Complexity: O(n) for storing the adjacency list and recursion stack.
*/

#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
#define N 100005
#define pb push_back
int T, n, a[N];
struct Edge {
  int id, v;
};
vector<Edge> e[N];

// DFS function to traverse the tree and assign weights
// u: current node
// f: parent node
// fl: flag to decide whether to assign 2 or 3
void dfs(int u, int f, bool fl) {
  for (auto i : e[u])
    if (i.v != f)
      a[i.id] = fl ? 2 : 3, dfs(i.v, u, !fl); // assign weight and recurse
}

void slv() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    e[i].clear(); // Clear adjacency list for current test case
  
  // Read edges and build adjacency list
  for (int i = 1, u, v; i < n; ++i)
    scanf("%d %d", &u, &v), e[u].pb((Edge){i, v}), e[v].pb((Edge){i, u});
  
  // Check if any vertex has degree > 2
  for (int i = 1; i <= n; ++i)
    if (e[i].size() > 2) {
      puts("-1");
      return;
    }
  
  // Find a leaf node (degree 1) and start DFS from there
  for (int i = 1; i <= n; ++i)
    if (e[i].size() < 2) {
      dfs(i, 0, 0); // Start DFS from leaf with initial flag = 0
      break;
    }
  
  // Print all edge weights
  for (int i = 1; i < n; ++i)
    printf("%d ", a[i]);
  puts("");
}

int main() {
  scanf("%d", &T);
  while (T--)
    slv();
}


// https://github.com/VaHiX/CodeForces/