// Problem: CF 2171 H - Shiori Miyagi and Maximum Array Score
// https://codeforces.com/contest/2171/problem/H

/*
 * Problem: H. Shiori Miyagi and Maximum Array Score
 * 
 * Purpose: 
 *   This solution computes the maximum value of the sum of v(i, a_i) for i from 2 to n,
 *   where v(b, x) is defined as the maximum k such that b^k divides x.
 *   The goal is to construct a strictly increasing array a of length n with elements in [1, m]
 *   that maximizes this sum.
 *   
 * Algorithm:
 *   - Use dynamic programming with bucketing to track the best positions for each power base.
 *   - For each base i starting from 3, calculate the optimal placement of elements to maximize
 *     contribution to the sum.
 *   - Use a map to store the latest valid positions for each exponent level.
 *   
 * Time Complexity: O(n * log(m) * log(m)) in the worst case due to nested loops and 
 *                   logarithmic base operations.
 * Space Complexity: O(n * log(m)) for storing the mapping of exponents to positions.
 */

#include <algorithm>
#include <iostream>
#include <map>

using namespace std;
long long cap = 1e7;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  for (int _ = 0; _ < t; _++) {
    int n, m;
    cin >> n >> m;
    int low = 0;
    int high = 0;
    map<int, int> prev;
    int bit = 1;
    // Precompute powers of 2 up to m
    while ((1 << bit) <= m) {
      prev[bit] = (1 << bit);
      high = bit;
      bit++;
    }
    // Process bases from 3 to n
    for (int i = 3; i <= n; i++) {
      low = i - 2;
      map<int, int> curr;
      int n_h = 0;
      // Initialize current values based on previous state
      for (int j = low; j <= high; j++) {
        curr[j] = prev[j] + 1;
        if (curr[j] <= m) {
          n_h = j;
        }
      }
      // Expand using powers of i
      for (int j = low; j <= high; j++) {
        int count = 1;
        long long p = i;
        while (p < cap) {
          if (p <= m) {
            int diff = prev[j] / p;
            int val = (diff + 1) * p;
            if (val > m) {
              break;
            }
            if (curr[j + count] == 0 || val < curr[j + count]) {
              n_h = max(j + count, n_h);
              curr[j + count] = val;
            }
          }
          p *= i;
          count += 1;
        }
      }
      prev = curr;
      high = n_h;
    }
    cout << high << "\n";
  }
}


// https://github.com/VaHiX/CodeForces/