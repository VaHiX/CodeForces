// Problem: CF 910 A - The Way to Home
// https://codeforces.com/contest/910/problem/A

#include <iostream>
#include <vector>
#include <string>

/*
 * Code Purpose:
 * This program finds the minimum number of jumps a frog needs to reach home
 * at point n starting from point 1, where the frog can only land on lilies
 * (represented by '1' in the string). The frog can jump at most 'd' units.
 *
 * Algorithms/Techniques:
 * - Dynamic Programming approach with precomputed lily positions.
 * - For each lily position, we compute the minimum jumps needed to reach it.
 *
 * Time Complexity: O(n^2) in worst case, where n is the length of the string.
 * Space Complexity: O(n) for storing lily positions and jump counts.
 */

int main() {
  long n, d;
  std::cin >> n >> d;
  std::string s;
  std::cin >> s;
  std::vector<long> v; // Stores positions of lilies
  for (long p = 0; p < s.size(); p++) {
    if (s[p] == '1') {
      v.push_back(p);
    }
  }
  std::vector<long> w(v.size(), n + 1); // w[i] stores min jumps to reach lily at v[i]
  w[0] = 0; // Starting position requires 0 jumps
  for (long from = 0; from < v.size(); from++) {
    for (long to = from + 1; to < v.size(); to++) {
      if (v[to] - v[from] <= d) {
        // If we can jump from 'from' to 'to' within distance d
        w[to] = (w[to] <= w[from] + 1) ? w[to] : (w[from] + 1);
        // Update minimum jumps to reach 'to'
      } else {
        // Since lilies are sorted, no further lilies can be reached within distance d
        break;
      }
    }
  }
  std::cout << ((w.back() <= n) ? w.back() : -1) << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/