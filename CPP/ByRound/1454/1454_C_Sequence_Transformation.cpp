// Problem: CF 1454 C - Sequence Transformation
// https://codeforces.com/contest/1454/problem/C

/*
C. Sequence Transformation
Algorithm: Greedy with Map
Time Complexity: O(n log n) per test case due to map operations.
Space Complexity: O(n) for storing the map and input.

The problem requires transforming a sequence into all equal elements by removing segments that do not contain a chosen value x.
We select x as one of the values present in the array. Then we count how many times each other element appears in the sequence,
which tells us how many operations are needed to remove them (the minimum number of operations we can achieve is minimized by choosing x appropriately).
*/

#include <cstdio>
#include <map>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::map<long, long> cm; // Map to count occurrences of each element except the last one
    long prev(0);
    scanf("%ld", &prev);
    cm[prev] = 0; // Initialize with first element's count as 0 (it's the first element)
    long x(prev); // Store the initial value
    for (long p = 1; p < n; p++) {
      scanf("%ld", &x);
      if (x != prev) {
        ++cm[x]; // Increment count if the current element is different from previous
      }
      prev = x; // Update previous to current
    }
    long mn(n + 1); // Initialize minimum operations with large value
    for (std::map<long, long>::iterator it = cm.begin(); it != cm.end(); it++) {
      long num = (it->second) + (it->first != x); // Calculate number of operations needed
      mn = (mn < num) ? mn : num; // Update minimum
    }
    printf("%ld\n", mn);
  }
}


// https://github.com/VaHiX/codeForces/