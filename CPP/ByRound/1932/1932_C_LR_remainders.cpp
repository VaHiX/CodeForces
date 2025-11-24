// Problem: CF 1932 C - LR-remainders
// https://codeforces.com/contest/1932/problem/C

/*
C. LR-remainders
Algorithm: Process commands from left to right, assigning each element its "weight" based on when it was removed.
Time Complexity: O(n log n) due to sorting, where n is the length of the array.
Space Complexity: O(n) for storing the array and intermediate results.

The key idea is to assign each element a "rank" based on the order in which it gets removed.
We then compute postfix products with modular arithmetic to avoid overflow.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <utility>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, m;
    std::cin >> n >> m;
    std::vector<std::pair<long, long>> v(n); // Store {rank, value} pairs
    for (long p = 0; p < n; p++) {
      std::cin >> v[p].second; // Read the values of the array
    }
    std::string s;
    std::cin >> s;
    long left(0), right(n - 1);
    // Assign ranks based on removal order: first removed gets highest rank
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == 'L') {
        v[left++].first = n - p; // Leftmost element gets rank (n - p)
      } else {
        v[right--].first = n - p; // Rightmost element gets rank (n - p)
      }
    }
    sort(v.begin(), v.end()); // Sort by rank to get final order
    
    std::vector<long> w(n);
    long cur(1);
    // Compute postfix products with modulos
    for (long p = 0; p < n; p++) {
      cur *= v[p].second;
      cur %= m;
      w[n - 1 - p] = cur;
    }
    for (long p = 0; p < n; p++) {
      printf("%ld ", w[p]);
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/