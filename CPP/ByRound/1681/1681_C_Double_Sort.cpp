// Problem: CF 1681 C - Double Sort
// https://codeforces.com/contest/1681/problem/C

/*
Code Purpose:
This program attempts to sort two arrays 'a' and 'b' simultaneously using at most 10^4 swaps,
where each swap involves swapping elements at the same indices in both arrays.
The approach is to use a bubble-sort-like strategy, but we only perform swaps if either array is not sorted at that position.
It checks if the arrays can be made sorted in at most 10^4 steps; if not, it outputs -1.

Algorithms/Techniques:
- Bubble sort technique applied to two arrays simultaneously
- Simulated swapping of elements at same positions in both arrays
- Checking if both arrays are sorted after applying swaps

Time Complexity: O(n^3) in worst case due to nested loops (n^2) and checking sorted status (n)
Space Complexity: O(n^2) in worst case for storing swap operations (up to n^2 swaps for n elements)
*/
#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n), b(n);
    std::vector<std::pair<long, long>> v;
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    for (long p = 0; p < n; p++) {
      scanf("%ld", &b[p]);
    }
    for (long p = 0; p < n; p++) {
      for (long q = 0; q < n - 1; q++) {
        // If either array is not sorted at current pair of indices, perform swap
        if (a[q] > a[q + 1] || b[q] > b[q + 1]) {
          std::swap(a[q], a[q + 1]);  // Swap elements in array 'a'
          std::swap(b[q], b[q + 1]);  // Swap elements in array 'b'
          v.push_back(std::make_pair(q, q + 1));  // Record the move
        }
      }
    }
    // Check if both arrays are sorted
    if (std::is_sorted(a.begin(), a.end()) && std::is_sorted(b.begin(), b.end())) {
      printf("%ld\n", v.size());
      for (long p = 0; p < v.size(); p++) {
        printf("%ld %ld\n", 1 + v[p].first, 1 + v[p].second);  // Print moves (1-indexed)
      }
    } else {
      puts("-1");  // Output -1 if sorting not possible
    }
  }
}


// https://github.com/VaHiX/CodeForces/