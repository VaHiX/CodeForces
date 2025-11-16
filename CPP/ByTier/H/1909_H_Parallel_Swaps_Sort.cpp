// Problem: CF 1909 H - Parallel Swaps Sort
// https://codeforces.com/contest/1909/problem/H

/*
 * Problem: H. Parallel Swaps Sort
 * Algorithm: Use a two-phase approach to sort the permutation using parallel swaps.
 *            The key idea is to find cycles in the permutation and use a series of
 *            operations to fix these cycles.
 * 
 * Time Complexity: O(n^2) worst case due to nested loops when handling cycles
 * Space Complexity: O(n) for storing auxiliary arrays and result operations
 * 
 * Techniques:
 * -Cycle detection and fixing using inversion technique
 * -Two-phase processing to handle both forward and reversed permutations
 * -Bit manipulation for efficient turn calculation
 * -Vector-based operation tracking and output
 */

#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> p(n);
  for (int i = 0; i < n; i++) {
    cin >> p[i];
    p[i]--;
  }
  vector<array<int, 2>> out;
  vector<int> first(n), second(n);
  iota(first.begin(), first.end(), 0);
  vector<int> invp(n);
  for (int i = 0; i < n; i++) {
    invp[p[i]] = i;
  }
  // Detect and fix cycles in the permutation
  for (int i = 0; i < n; i++) {
    int j = i;
    while (p[p[j]] != j) {
      swap(invp[p[j]], invp[p[p[p[j]]]]);
      swap(first[j], first[p[p[j]]]);
      swap(p[j], p[p[p[j]]]);
      j = invp[j];
    }
  }
  second = p;
  // Function to process permutations and generate swap operations
  auto work = [&](auto f, int t) {
    vector<vector<int>> vec(n);
    for (int i = 0; i < n; i++) {
      if (f[i] != i) {
        int x = i, y = f[i];
        if (t == 1) {
          x = n - 1 - x;
          y = n - 1 - y;
        }
        if (x > y) {
          swap(x, y);
        }
        int turn = 0, pos = 0;
        if ((y - x) % 2 == 1) {
          turn = (y - x + 1) / 2;
        } else {
          turn = (2 * n - y - x) / 2;
        }
        if (x % 2 == 1) {
          turn = n + 1 - turn;
        }
        pos = turn;
        if (x % 2 == 0) {
          pos += x;
        } else {
          pos -= x + 1;
        }
        vec[turn - 1].push_back(pos - 1);
        swap(f[i], f[f[i]]);
      }
    }
    for (int i = 0; i < n; i++) {
      int l = i % 2;
      int r = n;
      if ((r - l) % 2) {
        r--;
      }
      if (l < r) {
        out.push_back({l, r});
      }
      for (auto j : vec[i]) {
        out.push_back({j, j + 2});
      }
    }
  };
  // Process both normal and reversed permutations
  work(first, 0);
  work(second, 1);
  cout << out.size() << "\n";
  for (auto [l, r] : out) {
    cout << l + 1 << " " << r << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/