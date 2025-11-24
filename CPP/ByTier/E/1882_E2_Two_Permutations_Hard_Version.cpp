// Problem: CF 1882 E2 - Two Permutations (Hard Version)
// https://codeforces.com/contest/1882/problem/E2

/*
Algorithm/Techniques: 
This code solves the problem of transforming two permutations into sorted order using a specific operation that involves pivoting and swapping parts of the permutations. 

The key components are:
1. Calc() function computes a cost measure for a permutation (likely related to cycle decomposition)
2. CalcMinv() finds optimal pivot positions for minimizing operations on each permutation
3. CalcOP() generates the actual sequence of operations to sort a permutation with a given pivot
4. The main solve() function coordinates the whole process, choosing optimal pivots and balancing operation counts

Time Complexity: O(n^3 + m^3) where n and m are the lengths of the permutations
Space Complexity: O(n^2 + m^2) for storing intermediate arrays and permutations
*/

#include <limits.h>
#include <algorithm>
#include <array>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
// Calculate a cost measure for a permutation based on cycle structure
int Calc(vector<int> &a) {
  int n = a.size();
  vector<bool> visited(n, false);
  int ans = 0;
  {
    int c = 1;
    for (int i = a[0]; i != 0; i = a[i]) {
      ans += 1;
      visited[i] = true;
    }
    ans += c - 1;
  }
  for (int j = 1; j < n; ++j) {
    if (visited[j])
      continue;
    int c = 1;
    for (int i = a[j]; i != j; i = a[i]) {
      c += 1;
      visited[i] = true;
    }
    if (c > 1)
      ans += c + 1;
  }
  return ans;
}
// Find minimal cost pivot positions for both even and odd parity
array<int, 4> CalcMinv(vector<int> &a) {
  int n = a.size();
  vector<int> b(a.size());
  array<int, 2> mint = {INT_MAX / 4, INT_MAX / 4};
  array<int, 2> mini = {-1, -1};
  for (int i = 0; i < n; ++i) {
    int k = 0;
    for (int j = i; j < n; ++j) {
      b[k++] = a[j];
    }
    for (int j = 0; j < i; ++j) {
      b[k++] = a[j];
    }
    int t = Calc(b);
    if (t < mint[t & 1]) {
      mint[t & 1] = t;
      mini[t & 1] = i;
    }
  }
  return {mint[0], mint[1], mini[0], mini[1]};
}
// Generate operation sequence to sort permutation a using given start index
vector<int> CalcOP(vector<int> &a, int starti) {
  int n = a.size();
  vector<int> b(n);
  {
    int k = 0;
    for (int i = starti; i < n; ++i) {
      b[i] = k++;
    }
    for (int i = 0; i < starti; ++i) {
      b[i] = k++;
    }
  }
  vector<int> ans;
  vector<int> ai(n);
  for (int i = 0; i < n; ++i) {
    ai[a[i]] = i;
  }
  // Perform swaps to sort positions
  while (b[ai[0]] != 0) {
    int x = b[ai[0]];
    ans.push_back((ai[x] - ai[0] + n) % n);
    swap(a[ai[0]], a[ai[x]]);
    swap(ai[0], ai[x]);
  }
  for (int i = 1; i < n; ++i) {
    if (b[ai[i]] == i)
      continue;
    ans.push_back((ai[i] - ai[0] + n) % n);
    swap(a[ai[0]], a[ai[i]]);
    swap(ai[0], ai[i]);
    while (b[ai[0]] != 0) {
      int x = b[ai[0]];
      ans.push_back((ai[x] - ai[0] + n) % n);
      swap(a[ai[0]], a[ai[x]]);
      swap(ai[0], ai[x]);
    }
  }
  return ans;
}
// Main solving function
void solve() {
  int n, m;
  cin >> n >> m;
  vector<int> a(n + 1, 0), b(m + 1, 0);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= m; ++i) {
    cin >> b[i];
  }
  // Find optimal pivot positions for both permutations
  array<int, 4> ansa = CalcMinv(a);
  array<int, 4> ansb = CalcMinv(b);
  int starta = -1, startb = -1;
  // Choose the pivot pair that minimizes total operations
  if (max(ansa[0], ansb[0]) <= max(ansa[1], ansb[1])) {
    starta = ansa[2];
    startb = ansb[2];
  } else {
    starta = ansa[3];
    startb = ansb[3];
  }
  if (starta < 0 || startb < 0) {
    cout << "-1\n";
    return;
  }
  // Generate operation sequences
  vector<int> opa = CalcOP(a, starta);
  vector<int> opb = CalcOP(b, startb);
  // Balance the operation sequences if needed
  if (opa.size() <= opb.size()) {
    for (int i = opb.size() - opa.size(); i > 0; i -= 2) {
      opa.push_back(1);
      opa.push_back(n);
    }
  } else {
    for (int i = opa.size() - opb.size(); i > 0; i -= 2) {
      opb.push_back(1);
      opb.push_back(m);
    }
  }
  cout << opa.size() << '\n';
  for (int i = 0; i < (int)opa.size(); ++i) {
    cout << opa[i] << ' ' << opb[i] << '\n';
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T = 1;
  for (; T != 0; --T) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/