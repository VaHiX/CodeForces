// Problem: CF 1714 G - Path Prefixes
// https://codeforces.com/contest/1714/problem/G

/*
Purpose: 
This code solves the "Path Prefixes" problem on a rooted tree. For each node (except the root), 
it finds the maximum length of a prefix of the path from the root to that node such that the 
sum of edge 'b' values in the prefix does not exceed the sum of edge 'a' values in the prefix.

Algorithms/Techniques:
- DFS traversal of tree
- Binary search using upper_bound for efficient prefix sum queries
- Preprocessing edge information to build adjacency list

Time Complexity: O(n log n) per test case due to binary search in DFS traversal
Space Complexity: O(n) for storing tree structure and prefix sums

*/
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;

struct Edge {
  ll v, a, b;
};
vector<Edge> e[200005]; // Adjacency list for the tree
ll r[200005], s[200005], t, T;

// DFS function to traverse the tree and calculate prefix sums
void DFS(ll u, ll x) {
  // Find the maximum prefix length using binary search
  // upper_bound finds the first position where sum exceeds x
  // Subtracting 1 gives the length of the longest valid prefix
  r[u] = upper_bound(s + 1, s + t + 1, x) - s - 1;
  
  // Process each child of the current node
  for (Edge v : e[u]) {
    // Add the 'b' value of current edge to prefix sum array
    s[t + 1] = s[t] + v.b;
    t++; // Increment the index for the next element
    
    // Recursively call DFS on child node, adding 'a' value to the cumulative sum
    DFS(v.v, x + v.a);
    
    // Backtrack: decrement index to restore state for siblings
    t--;
  }
}

int main() {
  ll n, i, x, y, p;
  
  // Read number of test cases
  for (scanf("%lld", &T); T--; puts("")) {
    // Clear adjacency list for each test case
    for (scanf("%lld", &n), i = 1; i <= n; i++)
      e[i].clear();
    
    // Read edges and build the tree
    for (i = 2; i <= n; i++) {
      scanf("%lld%lld%lld", &p, &x, &y);
      e[p].push_back({i, x, y});
    }
    
    // Start DFS from root with initial sum of 'a' = 0
    DFS(1, 0);
    
    // Output the result for each node from 2 to n
    for (i = 2; i <= n; i++)
      printf("%lld ", r[i]);
  }
}


// https://github.com/VaHiX/CodeForces/