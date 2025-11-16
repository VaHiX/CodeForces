// Problem: CF 1270 I - Xor on Figures
// https://codeforces.com/contest/1270/problem/I

/*
I. Xor on Figures
time limit per test
5 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output
There is given an integer k and a grid 2^k × 2^k with some numbers written in its cells, cell (i, j) initially contains number a_ij. Grid is considered to be a torus, that is, the cell to the right of (i, 2^k) is (i, 1), the cell below the (2^k, i) is (1, i). There is also given a lattice figure F, consisting of t cells, where t is odd. F doesn't have to be connected.
We can perform the following operation: place F at some position on the grid. (Only translations are allowed, rotations and reflections are prohibited). Now choose any nonnegative integer p. After that, for each cell (i, j), covered by F, replace a_ij by a_ij ⊕ p, where ⊕ denotes the bitwise XOR operation.
More formally, let F be given by cells (x_1, y_1), (x_2, y_2), ..., (x_t, y_t). Then you can do the following operation: choose any x, y with 1 ≤ x, y ≤ 2^k, any nonnegative integer p, and for every i from 1 to n replace number in the cell (((x + x_i - 1) mod 2^k) + 1, ((y + y_i - 1) mod 2^k) + 1) with a_((x + x_i - 1) mod 2^k) + 1, ((y + y_i - 1) mod 2^k) + 1 ⊕ p.
Our goal is to make all the numbers equal to 0. Can we achieve it? If we can, find the smallest number of operations in which it is possible to do this.

Algorithms/Techniques:
- The code simulates a process where operations are applied multiple times on a torus grid, using XOR properties.
- It uses a fast simulation technique with bit manipulation and shift operations, reducing redundant computation.
- Key insight is that XOR operations can be reversed or accumulated in a systematic way across a toroidal space.

Time Complexity: O(k * t * 2^(2k))  
Space Complexity: O(2^(2k))
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using ll = unsigned long long;

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int k;
  cin >> k;
  int n = (1 << k); // Grid size 2^k x 2^k
  vector<vector<ll>> a(n, vector<ll>(n, 0));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cin >> a[i][j];
  int t;
  cin >> t;
  vector<pair<int, int>> shape(t);
  for (int i = 0; i < t; i++)
    cin >> shape[i].first >> shape[i].second;

  // Simulate the process of applying operations in log(n) steps
  for (int r = 0; r < k; r++) {
    vector<vector<ll>> b(n, vector<ll>(n, 0)); // Result grid after applying this step
    for (int c = 0; c < t; c++) { // For each cell in the shape
      for (int i = 0; i < n; i++) { // Traverse the entire grid
        for (int j = 0; j < n; j++) {
          // Apply XOR to result grid with coordinate wrapping using bitwise AND and modulo
          b[(i + shape[c].first) & ((1 << k) - 1)]
           [(j + shape[c].second) & ((1 << k) - 1)] ^= a[i][j];
        }
      }
    }
    a = b; // Update the grid after this step
    
    // Double all coordinates in the shape for next iteration (simulate scaling)
    for (int c = 0; c < t; c++) {
      shape[c].first = (shape[c].first * 2) % n;
      shape[c].second = (shape[c].second * 2) % n;
    }
  }

  // Count how many cells in the final grid have value > 0
  int ans = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (a[i][j])
        ans++;

  cout << ans << '\n';
}


// https://github.com/VaHiX/codeForces/