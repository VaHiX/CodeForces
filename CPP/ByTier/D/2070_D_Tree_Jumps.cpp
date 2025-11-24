// Problem: CF 2070 D - Tree Jumps
// https://codeforces.com/contest/2070/problem/D

/*
D. Tree Jumps

Purpose:
This code solves the problem of counting valid vertex sequences in a rooted tree under specific movement rules.
The chip starts at the root and can only move to children (i.e., vertices at distance d_v + 1), except when 
it's on a non-root vertex, where it cannot move to its direct neighbor (parent or child).

Algorithms/Techniques:
- Tree traversal using parent relationships.
- Dynamic programming based on depth levels.
- Modular arithmetic for large numbers.

Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const long long M = 998244353;

void solve(int n, vector<int> &p) {
  // d[i] stores the depth of vertex i
  vector<int> d(n + 1, 0);
  for (int i = 2; i <= n; i++)
    d[i] = d[p[i - 2]] + 1;  // Calculate depth based on parent's depth

  // Find maximum depth
  int m = 0;
  for (int i = 2; i <= n; i++)
    m = max(m, d[i]);

  // a[i] stores count of vertices at depth i
  vector<long long> a(m + 1, 0);
  for (int i = 2; i <= n; i++)
    a[d[i]]++;

  // s[i] stores the number of valid sequences ending at depth i or deeper
  vector<long long> s(m + 1, 0);
  s[m] = a[m] % M;  // Base case: last level contributes directly

  // Fill s from bottom to top using dynamic programming
  for (int i = m - 1; i >= 1; i--)
    s[i] = (a[i] + (a[i] - 1 + M) % M * s[i + 1]) % M;

  // Answer is number of valid sequences starting from root
  cout << (1 + s[1]) % M << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> p(n - 1);
    for (int &i : p)
      cin >> i;
    solve(n, p);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/