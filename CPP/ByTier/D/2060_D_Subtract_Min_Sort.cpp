// Problem: CF 2060 D - Subtract Min Sort
// https://codeforces.com/contest/2060/problem/D

/*
D. Subtract Min Sort
Algorithm: Greedy simulation with prefix operations
Time Complexity: O(n) per test case
Space Complexity: O(n) for the vector storage

The problem asks whether we can make a sequence non-decreasing by repeatedly
subtracting the minimum of two adjacent elements from both of them.
The key insight is that we process the array from left to right and for each
pair of adjacent elements, we subtract the smaller one from both. This operation
does not change the relative order in a way that would prevent us from achieving 
a non-decreasing sequence if it's possible.

We simulate this by iterating through the array once and applying the operation.
Then we check whether the resulting array is non-decreasing.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
    }
    // Process adjacent pairs and subtract min from both
    for (long p = 1; p < n; p++) {
      long x = (v[p - 1] < v[p] ? v[p - 1] : v[p]);  // Find the smaller value
      v[p - 1] -= x;  // Subtract x from previous element
      v[p] -= x;      // Subtract x from current element
    }
    // Check if array is now non-decreasing
    bool res(true);
    for (long p = 1; res && p < n; p++) {
      if (v[p - 1] > v[p]) {  // If any element is greater than next
        res = false;
      }
    }
    puts(res ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/