// Problem: CF 1919 H - Tree Diameter
// https://codeforces.com/contest/1919/problem/H

/*
 * Problem: H. Tree Diameter
 * Algorithm: Tree reconstruction using distance queries and edge connectivity queries
 * Time Complexity: O(n^2) - Each node is processed with at most n queries
 * Space Complexity: O(n^2) - Storing adjacency list and auxiliary arrays
 * 
 * The solution uses two types of queries:
 * 1. Query 1: Set weights of edges and get diameter of the tree
 * 2. Query 2: Get number of edges between two edges in the tree
 * 
 * Approach:
 * - First, we determine the level of each node by querying distances between nodes
 * - Then, we reconstruct the tree by iteratively adding nodes and connecting them
 * - We use level information and query results to determine the correct parent-child relationships
 * - The algorithm handles isomorphic structures by maintaining proper parent-child relationships
 */

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
#define maxx 1000
#define inf 1000000000
int n, lvl[maxx + 1], pe[maxx + 1];
vector<int> ch[maxx + 1];
long long int query(vector<int> a) {
  cout << "? 1";
  for (int i = 1; i < n; i++) {
    cout << " " << a[i];
  }
  cout << endl;
  long long int res;
  cin >> res;
  return res;
}
int query(int a, int b) {
  cout << "? 2 " << a << " " << b << endl;
  int res;
  cin >> res;
  return res;
}
int main() {
  cin >> n;
  for (int i = 2; i < n; i++) {
    lvl[i] = query(1, i);
  }
  int ptr = 3;
  pe[1] = 1;
  pe[2] = 1;
  vector<int> base = {1, 2};
  bool iso = 1;
  int piv = -1;
  for (int l = 0; l < n; l++) {
    vector<int> a(n, 1);
    int m = base.size();
    for (int i = 0; i < m; i++) {
      a[pe[base[i]]] = min(i + 1, m - iso) * maxx;
    }
    if (iso == 0) {
      a[pe[piv]] = inf;
    }
    bool ciso = 0;
    for (int u = 2; u < n; u++) {
      if (lvl[u] != l) {
        continue;
      }
      a[u] = inf;
      long long int res = query(a) - inf;
      a[u] = 1;
      if (iso == 0 || ciso != 0) {
        res = res - inf;
      }
      int id = res / maxx;
      if (iso != 0 && l != 0) {
        id = id - (m - 1);
      }
      int v = ptr++;
      pe[v] = u;
      if (ciso != 0) {
        if ((l == 0 && id == 0) || id == -(m - 1)) {
          ch[base[m - 2]].push_back(v);
        } else if (id == m - 1) {
          ch[base[m - 1]].push_back(v);
        } else {
          ch[base[id - 1]].push_back(v);
        }
      } else if (iso != 0 && id == m - 1) {
        ch[base[m - 2]].push_back(v);
        ciso = 1;
        a[u] = inf;
      } else {
        ch[base[id - 1]].push_back(v);
      }
    }
    if (m >= 2 && ch[base[m - 2]].size() > ch[base[m - 1]].size()) {
      swap(base[m - 2], base[m - 1]);
    }
    vector<int> nbase;
    for (int i = 0; i < m; i++) {
      for (int j : ch[base[i]]) {
        nbase.push_back(j);
      }
    }
    if (iso == 0 || ch[base[m - 1]].size() >= 2 ||
        ch[base[m - 2]].size() == 1) {
      base = nbase;
      continue;
    }
    if (ch[base[m - 1]].empty()) {
      piv = base[m - 1];
    } else {
      long long int res = query(pe[ch[base[m - 1]][0]], pe[base[m - 1]]);
      if (res != 0) {
        swap(base[m - 2], base[m - 1]);
        swap(ch[base[m - 2]], ch[base[m - 1]]);
      }
      piv = base[m - 2];
    }
    base = nbase;
    iso = 0;
  }
  cout << "!" << endl;
  cout << "1 2" << endl;
  for (int i = 1; i <= n; i++) {
    for (int j : ch[i]) {
      cout << i << " " << j << endl;
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/