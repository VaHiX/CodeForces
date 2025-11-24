// Problem: CF 2052 D - DAG Serialization
// https://codeforces.com/contest/2052/problem/D

/*
D. DAG Serialization
Algorithms/Techniques: Topological sorting, DAG processing with constraints.
Time Complexity: O(n + m), where n is the number of operations and m is the number of dependencies.
Space Complexity: O(n + m), for storing the graph and auxiliary arrays.

Task:
Consider a simple single-bit boolean register that supports two operations:
set — sets the register to true if it was false, and returns true; otherwise, it returns false;
unset — sets the register to false if it was true, and returns true; otherwise, it returns false.
The initial state of the register is false. Suppose there were
n
operations
o
p
i
(for
1≤i≤n
) where at most two operations returned true. Also, we are given the partial order of operations as a directed acyclic graph (DAG): an edge
i→j
means that
o
p
i
happened before
o
p
j
. You are asked whether it is possible to put these operations in some linear sequential order that satisfies the given partial order and such that if operations are applied to the register in that order, their results are the same as given.
Input
In the first line, you are given an integer
n
— the number of operations (
1≤n≤
10
5
). In the following
n
lines, you are given operations in the format "type result", where type is either "set" or "unset" and result is either "true" or "false". It is guaranteed that at most two operations have "true" results.
In the next line, you are given an integer
m
— the number of arcs of the DAG (
0≤m≤
10
5
). In the following
m
lines, you are given arcs — pairs of integers
a
and
b
(
1≤a,b≤n
;
a≠b
). Each arc indicates that operation
o
p
a
happened before operation
o
p
b
.
Output
Print any linear order of operations that satisfies the DAG constraints and ensures the results of the operations match the ones given in the input. If a correct operation order does not exist, print
−1
.
*/
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;
const int N = 1e5 + 10;
int n, m, ans;
int type[N], tg[2]; // type[i] stores operation type (0=set, 1=unset), tg tracks positions of operations returning true
vector<int> e[N];
int ind[N]; // in-degree array for topological sorting
queue<int> q;
bool vis[N]; // visited flag to mark processed nodes
vector<int> ord; // final order of operations

void work(bool tp) {
  // Process all nodes of type 'tp' with in-degree zero that haven't been visited yet
  for (int i = 1; i <= n; ++i)
    if (type[i] == tp && !vis[i] && !ind[i]) { // Check type, unvisited, in-degree is 0
      vis[i] = 1;
      q.push(i);
    }
  while (!q.empty()) {
    int u = q.front();
    ord.push_back(u); // Add to result order
    q.pop();
    for (int v : e[u]) { // Traverse neighbors
      --ind[v]; // Reduce in-degree
      if (type[v] == tp && !ind[v]) { // If neighbor matches type and in-degree now zero
        vis[v] = 1; // Mark as visited
        q.push(v); // Add to queue
      }
    }
  }
  return;
}

void add(int x) {
  // Check if node already has remaining in-degrees => impossible to proceed
  if (ind[x]) {
    cout << -1;
    exit(0);
  }
  vis[x] = 1; // Mark as visited
  ord.push_back(x); // Add to order
  for (int v : e[x]) // Decrease in-degree of adjacent nodes
    --ind[v];
  return;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    string s, t;
    bool op, v;
    cin >> s >> t;
    op = (s == "set"); // 0 for set, 1 for unset
    v = (t == "true"); // true if operation returned true
    if (v) {
      if (tg[op]) { 
        // More than one operation of same type returning true => contradiction
        cout << -1;
        return 0;
      }
      tg[op] = i; // Track index of operation that returned true for this type
      type[i] = 2 + op; // assign special value to denote this is a "return true" operation
    } else
      type[i] = op; // regular operation
  }
  cin >> m;
  for (int i = 1; i <= m; ++i) {
    int x, y;
    cin >> x >> y;
    e[x].push_back(y); // Add edge from x to y
    ++ind[y]; // Increase in-degree of y
  }
  if (tg[0] && !tg[1]) {
    // There was a set returning true but unset did not -> invalid scenario
    cout << -1;
    return 0;
  }
  work(0); // Process all set operations
  if (tg[1]) {
    add(tg[1]); // Add the actual "unset returns true" operation to order
    work(1); // Process all unset operations 
    if (tg[0]) {
      add(tg[0]); // Add the actual "set returns true" operation
      work(0); // Now process remaining set operations
    }
  }
  if (ord.size() < n) {
    // Not all operations were processed -> cycle or inconsistent input
    cout << -1;
    return 0;
  }
  for (int t : ord)
    cout << t << ' ';
  return 0;
}


// https://github.com/VaHiX/codeForces/