// Problem: CF 1851 B - Parity Sort
// https://codeforces.com/contest/1851/problem/B

/*
B. Parity Sort
Algorithms/Techniques: Greedy, Sorting, Two-pointer technique
Time Complexity: O(n log n) per test case due to sorting operations
Space Complexity: O(n) for storing the arrays u and v

Given an array of integers, determine if it's possible to sort the array by swapping elements 
only if they have the same parity (both even or both odd). The solution separates odd and even 
numbers, sorts them individually, then greedily assigns them back in order to check if the result is sorted.
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
    std::vector<long> a, u, v; // a: original parity info, u: odds, v: evens
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      a.push_back(x % 2); // Store parity (0 for even, 1 for odd)
      if (x % 2) {        // If odd
        u.push_back(x);
      } else {            // If even
        v.push_back(x);
      }
    }
    sort(u.begin(), u.end()); // Sort odds in ascending order
    sort(v.begin(), v.end()); // Sort evens in ascending order
    bool res(true);
    long idxa(0), idxb(0);    // Pointers for u and v arrays
    for (long p = 0; res && p < n; p++) {
      if (a[p]) {             // If current element should be odd
        a[p] = u[idxa++];     // Assign next smallest odd
      } else {                // If current element should be even
        a[p] = v[idxb++];     // Assign next smallest even
      }
      if (p > 0 && a[p - 1] > a[p]) { // Check if sorted
        res = false;
      }
    }
    puts(res ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/