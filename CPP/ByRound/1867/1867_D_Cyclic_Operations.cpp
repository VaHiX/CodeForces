// Problem: CF 1867 D - Cyclic Operations
// https://codeforces.com/contest/1867/problem/D

/*
Algorithm: Graph Cycle Detection and Validation
Approach:
- This problem involves determining whether a target array can be generated using cyclic operations.
- Each operation selects a subsequence of length k and updates elements in a cyclic manner.
- The key insight is that such operations create cycles in the permutation induced by the target array.
- We check if the structure of the permutation allows valid generation with the given k.

Time Complexity: O(n) per test case, where n is the size of the array.
Space Complexity: O(n) for storing the array and auxiliary data structures.

Techniques:
- Permutation cycle detection using in-degree tracking
- BFS-based topological sorting and cycle detection
- Cyclic validation using the given k parameter
*/

#include <limits.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
#define ll long long
#define ppi pair<int, int>
#define ppl pair<ll, ll>
#define pb push_back
#define endl '\n'
#define all(v) v.begin(), v.end()
#define sz(v) (int)v.size()
const int mod = 1e9 + 7;
const ll inf = LONG_LONG_MAX;
const int modt = 998244353;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    bool ok = true;
    if (k == 1) {
      for (int i = 1; i <= n; i++)
        ok &= (a[i] == i);
      cout << (ok ? "YES" : "NO") << endl;
      continue;
    }
    for (int i = 1; i <= n; i++) {
      if (a[i] == i)
        ok = false;
    }
    if (!ok) {
      cout << "NO" << endl;
      continue;
    }
    vector<int> inDeg(n + 1);
    for (int i = 1; i <= n; i++)
      inDeg[a[i]]++;
    queue<int> qu;
    for (int i = 1; i <= n; i++) {
      if (!inDeg[i])
        qu.push(i);
    }
    while (qu.size() > 0) {
      int k = qu.front();
      qu.pop();
      inDeg[a[k]]--;
      if (!inDeg[a[k]])
        qu.push(a[k]);
    }
    for (int i = 1; i <= n; i++) {
      if (!inDeg[i])
        continue;
      int s = a[i], cnt = 1;
      inDeg[i] = 0;
      while (s != i) {
        inDeg[s] = 0;
        s = a[s];
        cnt++;
      }
      ok &= (cnt == k);
    }
    cout << (ok ? "YES" : "NO") << endl;
  }
}


// https://github.com/VaHiX/CodeForces/