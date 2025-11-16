// Problem: CF 2045 L - Buggy DFS
// https://codeforces.com/contest/2045/problem/L

/*
 * Purpose: This code solves the problem of constructing a graph such that the buggy DFS (BDFS) returns a specific value K.
 *          The BDFS algorithm counts the number of iterations in the inner loop, which corresponds to the number of edges
 *          traversed during a modified DFS traversal. The task is to build a graph that makes BDFS return exactly K.
 *
 * Algorithms:
 * - Graph construction technique using triangular and linear components.
 * - Greedy decomposition of K into components that correspond to graph structures.
 *
 * Time Complexity: O(N^2) in worst case due to graph construction and sorting.
 * Space Complexity: O(N) for storing the graph and auxiliary arrays.
 *
 * Techniques:
 * - Decomposition of K into sum of triangular numbers and small values.
 * - Constructing graphs using triangles and linear chains.
 * - Using stack-based DFS simulation for verification.
 */

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;
using ll = long long;
const ll N = 32768;
vector<ll> g[N + 1]; // Adjacency list for the graph
bool f[N + 1];       // FLAG array to track visited nodes
ll x, np = 1, bp = 0, sum = 0, vc = 0, ec = 0; // Variables for graph construction and tracking

// Function to simulate BDFS on constructed graph to verify result
ll ch() {
  ll re = 0;
  stack<int> s;
  s.emplace(1);
  while (!s.empty()) {
    auto nn = s.top();
    s.pop();
    f[nn] = 1;       // Mark as visited
    for (auto e : g[nn]) {
      re++;          // Increment counter for each edge considered
      if (!f[e])
        s.emplace(e); // Push unvisited neighbor
    }
  }
  return re;
}

// Function to add a triangular graph component starting from 'st' with 'n' nodes
void add(ll n, ll st) {
  for (int i = st; i < st + n; i++) {
    if (i == st + 1)
      continue;  // Skip connecting first node to itself
    g[st + 1].emplace_back(i); // Connect first node to current node
    g[i].emplace_back(st + 1);
    if (i != st && i != st + n - 1) {  // Connect current node to next node
      g[i].emplace_back(i + 1);
      g[i + 1].emplace_back(i);
    }
  }
  g[st].emplace_back(st + 2);    // Add extra edges
  g[st + 2].emplace_back(st);
  g[st].emplace_back(st + n - 1);
  g[st + n - 1].emplace_back(st);
  sum += n * n + n + 1;  // Accumulate sum for tracking K value
  ec += (n - 1) * 2;     // Update edge count
  vc += n;               // Update vertex count
  np += n;               // Move next node pointer
  bp = st;               // Update base pointer
}

// Function to add a specific 4-node structure of 11 operations (for remaining odd parts)
void add11(ll st) {
  g[st].emplace_back(st + 1);    // Connect nodes to make a structure of 11 steps
  g[st + 1].emplace_back(st);
  g[st].emplace_back(st + 3);
  g[st + 3].emplace_back(st);
  g[st + 1].emplace_back(st + 3);
  g[st + 3].emplace_back(st + 1);
  g[st + 1].emplace_back(st + 2);
  g[st + 2].emplace_back(st + 1);
  bp = st;
  np = st + 4;   // Move the node pointer
  sum += 11;
  ec += 4;
  vc += 4;
}

// Function to compute triangular number: n^2 + n + 1
ll cal(ll n) { return n * n + n + 1; }

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> x;
  for (ll i = 31623; i > 3; i--) {  // Try to find components that fit x
    ll nv = cal(i);
    if (bp) {
      nv += 2;     // Adjust for additional edges
    }
    if (x >= nv && (((x - nv) & 1 && x - nv >= 13) || !((x - nv) & 1))) {
      if (bp) {
        g[bp].emplace_back(np);   // Connect previous part to new part
        g[np].emplace_back(bp);
        sum += 2;
        ec++;
      }
      add(i, np);  // Add triangular graph part
      x -= nv;
    }
  }
  
  // Handle remaining odd values
  if (x & 1) {
    if (bp) {
      g[bp].emplace_back(np);
      g[np].emplace_back(bp);
      sum += 2;
      ec++;
      x -= 2;
    }
    add11(np);   // Add 4-node structure
    x -= 11;
  }
  
  // Check for impossible cases
  if (x < 0) {
    cout << "-1 -1";
    return 0;
  }

  // Final adjustments to make x zero
  while (x) {
    if (!bp) {   // First edge if not already started
      bp = 1;
      np = 2;
      vc++;
    }
    g[bp].emplace_back(np);  // Add edge between bp and np
    g[np].emplace_back(bp);
    bp = np;
    np = np + 1;
    sum += 2;
    ec++;
    vc++;
    x -= 2;    // Reduce x by 2 for each edge added
  }
  
  cout << vc << ' ' << ec << '\n';
  for (int i = 1; i < np; i++) {
    sort(g[i].begin(), g[i].end());   // Sort adjacency list
    for (auto e : g[i])
      if (i < e)  // Prevent duplicate edges
        cout << i << ' ' << e << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/