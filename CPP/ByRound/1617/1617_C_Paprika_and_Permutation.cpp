// Problem: CF 1617 C - Paprika and Permutation
// https://codeforces.com/contest/1617/problem/C

/*
C. Paprika and Permutation
Problem Description:
Given an array of n integers, we want to make it a permutation of 1 to n using modulo operations.
Each operation allows us to choose an index i and a positive integer x, then replace a[i] with a[i] % x.
Goal: Find minimum number of such operations, or -1 if impossible.

Algorithms/Techniques:
- Use a set to track which numbers from 1 to n are already present in the array
- For numbers not in the range [1, n], store them in a vector and sort them
- Greedily match smaller unused numbers with larger values that can become them via modulo
- Time complexity: O(n log n) per test case due to sorting (but amortized across all test cases is acceptable)
- Space complexity: O(n)

*/

#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v;           // Store numbers outside [1, n] or duplicates
    std::set<long> s;              // Store unique valid numbers between 1 and n
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if ((x <= n) && (!s.count(x))) {
        s.insert(x);               // Insert valid number not yet seen
      } else {
        v.push_back(x);            // Store invalid or duplicate numbers
      }
    }
    sort(v.begin(), v.end());      // Sort the invalid numbers to process from smallest to largest
    long cnt(v.size()), idx(0);   // cnt = initial count of invalid elements, idx = pointer for v
    for (long p = 1; p <= n; p++) {
      if (s.count(p)) {
        continue;                  // Skip if p is already in the set
      }
      if (v[idx] <= 2 * p) {       // If smallest unused number can be reduced to p by a modulo operation
        cnt = -1;                  // Impossible: cannot generate p from v[idx] using modulo
        break;
      }
      ++idx;                       // Move pointer forward to next element in v
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/