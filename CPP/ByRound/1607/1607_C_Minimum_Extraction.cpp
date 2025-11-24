// Problem: CF 1607 C - Minimum Extraction
// https://codeforces.com/contest/1607/problem/C

/*
C. Minimum Extraction
Algorithms/Techniques: Sorting, Greedy

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the array

The problem asks to maximize the minimum element in the array after applying
"minimum extraction" operations as many times as possible. Each operation:
1. Finds the minimum element m in the array
2. Removes m from the array
3. Subtracts m from all remaining elements
4. The final minimum of remaining elements is what we want to maximize

Key insight:
- After sorting, we can process elements greedily.
- For each consecutive pair of sorted elements, the difference represents 
  a potential minimum value that can be achieved by performing operations.
- The maximum of these differences (or the first element if it's the only one) 
  gives the answer.

*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n); // Read the array
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    sort(a.begin(), a.end()); // Sort to process elements in increasing order
    long res(a[0]); // Initialize result with first element
    for (long p = 1; p < a.size(); p++) {
      long diff = a[p] - a[p - 1]; // Calculate difference between consecutive elements
      res = (res > diff) ? res : diff; // Keep the maximum of differences
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/