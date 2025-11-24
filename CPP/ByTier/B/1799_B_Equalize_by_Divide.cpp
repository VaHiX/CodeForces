// Problem: CF 1799 B - Equalize by Divide
// https://codeforces.com/contest/1799/problem/B

/*
Purpose: This code determines if it's possible to make all elements of an array equal 
         using a specific operation: choosing two indices i and j, and setting a[i] = ceil(a[i]/a[j]).
         It uses a greedy approach by always operating on the largest and smallest elements.

Algorithms/Techniques:
- Greedy strategy with a set to maintain array elements and their indices.
- The operation is applied to reduce the difference between max and min elements.
- Time complexity is effectively O(n log n) per test case due to set operations.
- Space complexity is O(n) for storing elements and operations.

Time Complexity: O(n log n) per test case due to set operations; overall is O(30 * n * log n) for all test cases.
Space Complexity: O(n) for storing elements and operations.
*/

#include <cstdio>
#include <set>
#include <vector>
#include <iterator>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::set<std::pair<long, long>> s; // Set to store {value, index} pairs, sorted by value
    for (long p = 1; p <= n; p++) {
      long x;
      scanf("%ld", &x);
      s.insert(std::make_pair(x, p)); // Insert element with its index
    }
    // If the smallest element is 1 and the largest is greater than 1, impossible to make all equal
    if (s.begin()->first <= 1 && s.rbegin()->first > 1) {
      puts("-1");
      continue;
    }
    std::vector<std::pair<long, long>> v; // Vector to store the sequence of operations
    for (long p = 0; p < 30 * n; p++) {
      long num = s.rbegin()->first;     // Get the largest element
      long idxl = s.rbegin()->second;   // Index of the largest element
      long den = s.begin()->first;      // Get the smallest element
      long idxs = s.begin()->second;    // Index of the smallest element
      if (num == den) {                 // If all elements are equal, stop
        break;
      }
      v.push_back(std::make_pair(idxl, idxs)); // Record operation: set idxl = ceil(num / den)
      s.erase(*s.rbegin()); // Remove the largest element
      // Insert the result of operation: ceil(num / den) at index idxl
      s.insert(std::make_pair((num + den - 1) / den, idxl));
    }
    printf("%ld\n", v.size()); // Output number of operations
    for (long p = 0; p < v.size(); p++) {
      printf("%ld %ld\n", v[p].first, v[p].second); // Output each operation
    }
  }
}


// https://github.com/VaHiX/CodeForces/