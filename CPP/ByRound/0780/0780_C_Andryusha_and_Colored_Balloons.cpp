// Problem: CF 780 C - Andryusha and Colored Balloons
// https://codeforces.com/contest/780/problem/C

/*
Purpose: This code solves the problem of coloring the nodes of a tree such that for any three nodes forming a path (a-b-c), all three have distinct colors. The goal is to minimize the number of colors used.

Approach:
- The algorithm constructs a tree from input edges.
- It determines the minimum number of colors required as the maximum degree of any node + 1.
- Using DFS traversal, it assigns colors to nodes such that adjacent nodes and their ancestors do not conflict.
- The DFS ensures each node gets a color different from its neighbors, satisfying the constraint for any path of length 2.

Time Complexity: O(n) where n is the number of nodes. Each node and edge is visited a constant number of times.
Space Complexity: O(n) for storing adjacency list, visited flags, and color array.
*/

#include <stdio.h>
#include <algorithm>
#include <stack>
#include <vector>

typedef long long int ll;
#define dbg printf("in\n");
#define nl printf("\n");
#define pp pair<int, int>
#define N 200010
using namespace std;

int color[N], tc; // color array to store the color of each node, tc stores max color count needed
bool vis[N]; // visited array to track visited nodes during DFS
vector<int> adj[N]; // adjacency list representation of the tree

// DFS function to assign colors to nodes
void dfs(int s, int p, int gp) {
  stack<int> ss; // stack to hold available colors
  vis[s] = 1; // mark current node as visited

  // Push all colors except parent and grandparent into the stack
  for (int i = 1; i <= tc; i++) {
    if (i != p && i != gp)
      ss.push(i);
    if (ss.size() == adj[s].size()) // early exit if stack has enough colors
      break;
  }

  // Traverse neighbors and assign colors
  for (int i : adj[s]) {
    if (!vis[i]) { // if neighbor is not visited
      color[i] = ss.top(); // assign top color from stack
      ss.pop(); // remove the assigned color from stack
      dfs(i, color[i], color[s]); // recursive DFS call with new parent color
    }
  }
}

int main() {
  int i, j, k;
  int n, m;
  int u, v;

  scanf("%d", &n); // read number of nodes

  // Read edges and build adjacency list
  for (i = 1; i < n; i++) {
    scanf("%d%d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  tc = 0; // initialize maximum color count

  // Find maximum degree in the tree and set tc to max degree + 1
  for (i = 1; i <= n; i++) {
    k = adj[i].size();
    tc = max(tc, k + 1);
  }

  color[1] = 1; // assign first color to root node
  dfs(1, 1, 0); // perform DFS starting from root

  printf("%d\n", tc); // print minimum number of colors needed

  // Print color of each node
  for (i = 1; i <= n; i++)
    printf("%d ", color[i]);

  return 0;
}


// https://github.com/VaHiX/CodeForces/