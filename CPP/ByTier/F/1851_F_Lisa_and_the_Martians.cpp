// Problem: CF 1851 F - Lisa and the Martians
// https://codeforces.com/contest/1851/problem/F

/*
Code Purpose:
This code solves the problem of finding the maximum value of (a[i] ⊕ x) & (a[j]
⊕ x) for given martian numbers. The approach uses sorting and a greedy strategy
to determine optimal values for i, j, and x. The solution leverages the fact
that the maximum value of the bitwise AND of two XOR results can be achieved by
selecting numbers that differ in as few bits as possible.

Algorithms/Techniques:
- Sorting of martian numbers
- Greedy selection of pair with minimal XOR
- Bit manipulation: using all 1s mask to compute optimal x

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the vector of pairs
*/

using namespace std;
#define pb push_back
#define mp make_pair
#define ll long long
#include <algorithm>
#include <functional>
#include <iostream>
#include <limits.h>
#include <stdio.h>
#include <utility>
#include <vector>

#define fast_io()                                                              \
  ios::sync_with_stdio(0);                                                     \
  cin.tie(0)
void solve() {
  int n, k;
  cin >> n >> k;
  vector<pair<int, int>> v(n); // Store number and its index
  for (int i = 0; i < n; i++) {
    int next;
    cin >> next;
    v[i] = {next, i};
  }
  sort(v.begin(), v.end()); // Sort based on the numbers

  int pos = -1;
  int xo = INT_MAX;
  // Find the pair of numbers with minimum XOR
  for (int i = 1; i < n; i++) {
    int curr = v[i].first ^ v[i - 1].first;
    if (curr < xo) {
      xo = curr;
      pos = i;
    }
  }

  // Create a mask with all bits set (all 1s)
  int allmax = 1 << k;
  allmax--;

  // Choose x such that it maximizes (a[i] ^ x) & (a[j] ^ x)
  // This happens when x is such that it brings both numbers close to each other
  // in bits
  int x = allmax ^ v[pos].first;

  // Determine indices i and j (1-indexed)
  int i = min(v[pos].second, v[pos - 1].second);
  i++;
  int j = max(v[pos].second, v[pos - 1].second);
  j++;

  cout << i << " " << j << " " << x << endl;
}
int main() {
  fast_io();
  int t = 1;
  cin >> t;
  int T = t;
  while (t--) {
    solve();
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/