// Problem: CF 1979 E - Manhattan Triangle
// https://codeforces.com/contest/1979/problem/E

/*
 * Problem: Manhattan Triangle
 * 
 * Purpose: Find three points from a given set that form a Manhattan triangle, 
 *          where all pairwise Manhattan distances are equal to a given even value d.
 * 
 * Algorithm:
 * - The key insight is that in Manhattan space, a triangle with equal side lengths 
 *   can be represented by rotating coordinates in a specific way.
 * - For a valid Manhattan triangle with side length d, the coordinates of the 
 *   three points will have specific relationships.
 * - This solution tries two rotated coordinate systems to find valid triplets.
 * 
 * Time Complexity: O(n * log(n)) per test case due to sorting and binary search operations.
 * Space Complexity: O(n) for storing the points and intermediate arrays.
 * 
 * Techniques:
 * - Coordinate transformation using rotation (x, y) -> (x+y, x-y) or similar
 * - Binary search (lower_bound) for efficient lookup
 * - Sorting to allow binary search on preprocessed points
 */

#include <algorithm>
#include <array>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;

void solve() {
  int n, d;
  cin >> n >> d;
  d /= 2;  // Half the distance for simplification in coordinate transformation
  vector<array<int, 3>> a(n);  // Array to hold (s, x, ind) for each point
  for (auto &[x, y, _] : a) {
    cin >> x >> y;
  }
  // Transform coordinates: (x, y) -> (x+y, x-y) and store index
  for (int i = 0; i < n; ++i) {
    auto &[s, x, ind] = a[i];
    ind = i;
    swap(s, x);  // x becomes s, y becomes x
    s += x;      // s = x + y
  }
  
  int I = 0, J = 0, K = 0;  // Indices of the three points forming triangle
  
  // Lambda function to search for valid triplets in current coordinate system
  auto work = [&]() {
    sort(a.begin(), a.end());  // Sort based on s, x, and index
    vector<array<int, 4>> b;   // Will store valid pairs of points
    
    // First pass: Find pairs of points such that their s-diff is d
    for (auto [s, x, i] : a) {
      auto it = lower_bound(a.begin(), a.end(), array{s, x + d, 0});
      if (it == a.end())
        continue;
      auto [s1, x1, j] = *it;
      if (s1 == s and x1 == x + d) {
        b.push_back({s, x, i, j});
      }
    }
    
    // Second pass: For each valid s, look for a matching triplet using b
    for (auto [s, x, i] : a) {
      auto it = lower_bound(b.begin(), b.end(), array{s + 2 * d, x, 0, 0});
      if (it != b.end()) {
        auto [s1, x1, j, k] = *it;
        if (s1 == s + 2 * d and x1 <= x + d) {
          I = i + 1;
          J = j + 1;
          K = k + 1;
          return;
        }
      }
      it = lower_bound(b.begin(), b.end(), array{s - 2 * d, x - 2 * d, 0, 0});
      if (it != b.end()) {
        auto [s1, x1, j, k] = *it;
        if (s1 == s - 2 * d and x1 <= x - d) {
          I = i + 1;
          J = j + 1;
          K = k + 1;
          return;
        }
      }
    }
  };
  
  // Try first coordinate system
  work();
  if (I == 0) {
    // If no triangle found, transform coordinates and try again  
    for (auto &[s, x, i] : a) {
      s -= 2 * x;
      x = -x;
    }
    work();
  }
  cout << I << ' ' << J << ' ' << K;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t = 1;
  std::cin >> t;
  for (int i = 1; i <= t; ++i) {
    solve();
    std::cout << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/