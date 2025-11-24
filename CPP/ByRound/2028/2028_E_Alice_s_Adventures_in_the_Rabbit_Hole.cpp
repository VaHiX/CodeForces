// Problem: CF 2028 E - Alice's Adventures in the Rabbit Hole
// https://codeforces.com/contest/2028/problem/E

/*
E. Alice's Adventures in the Rabbit Hole
Algorithms/Techniques: Tree Dynamic Programming, DFS, Modular Arithmetic, Inverse Elements

Time Complexity: O(n) per test case due to tree traversal and modular exponentiation
Space Complexity: O(n) for storing tree structure and DP arrays

Given a tree with root at vertex 1, Alice starts at a random vertex and must avoid leaf nodes.
Each turn, a coin flip decides whether Alice or the Queen moves. 
The goal is to compute escape probabilities for all starting positions.

This solution uses two DFS traversals:
1. First DFS (dfs1) computes distances from leaves to each node
2. Second DFS (dfs2) propagates probabilities using dynamic programming
*/

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <string>

using namespace std;
typedef long long ll;
#define N 400000
#define M 998244353
ll i, j, k, n, m, t;
ll f[N + 50], dis[N + 50]; // f: probabilities; dis: distances/degrees
basic_string<int> v[N + 50]; // adjacency list

// Fast exponentiation: computes a^p mod M
ll ksm(ll a, ll p) {
  ll res = 1;
  while (p) {
    if (p & 1) { // if p is odd
      res = res * a % M; // multiply result by a
    }
    a = a * a % M; // square base
    p >>= 1; // divide p by 2
  }
  return res;
}

// First DFS: compute distance from leaves to each node (dis[x] = min distance to any leaf)
void dfs1(int x, int fa) {
  dis[x] = 1e9; // set distance to large value
  for (auto i : v[x]) // for each neighbor
    if (i != fa) { // avoid going back to parent
      dfs1(i, x); // recurse
      dis[x] = min(dis[x], dis[i] + 1); // update minimum dist
    }
  if (dis[x] > 1e8) // if distance was never updated => node is a leaf
    dis[x] = 0;
}

// Second DFS: compute the probability of escaping from each node using dynamic programming
void dfs2(int x, int fa) {
  if (x > 1) { // root has no parent
    // Propagate probability: f[x] = f[fa] * dis[x] / (dis[x] + 1)
    // Here, dis[x] represents branching factor or expected nodes from current position.
    f[x] = f[fa] * dis[x] % M * ksm(dis[x] + 1, M - 2) % M;
  }
  for (auto i : v[x]) // for each neighbor
    if (i != fa) {
      dfs2(i, x); // recurse for child
    }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (i = 1; i < n; i++) { // read edges
      cin >> j >> k;
      v[j] += k; // build adjacency list
      v[k] += j;
    }
    fill(f, f + n + 1, 0); // reset probabilities
    f[1] = 1; // root starts with probability 1
    dfs1(1, 0); // compute distances from leaves
    dfs2(1, 0); // compute probabilities
    for (i = 1; i <= n; i++) {
      cout << f[i] << ' '; // output result
      v[i] = {}; // clear adjacency list
    }
    cout << '\n';
  }
}


// https://github.com/VaHiX/codeForces/