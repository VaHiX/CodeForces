// Problem: CF 1678 A - Tokitsukaze and All Zero Sequence
// https://codeforces.com/contest/1678/problem/A

/*
Problem: A. Tokitsukaze and All Zero Sequence
Algorithm: Greedy with set-based logic
Time Complexity: O(n log n) per test case due to set operations
Space Complexity: O(n) for storing the set and auxiliary variables

The problem involves reducing all elements of a sequence to 0 using specific operations:
- If two elements are equal, one can be changed to 0.
- Otherwise, both are changed to the minimum of the two.

Key observations:
1. If there are zeros in the sequence, we can reduce all non-zero elements to zero by pairing them with zeros.
2. If there are duplicate numbers (besides zeros), we must make at least one more operation to resolve duplicates.
3. If there are no zeros and all numbers are distinct, we need n+1 operations.

In each iteration:
- Count occurrences of 0s
- Track if there are any repeated values using a set
- Based on conditions, compute minimum operations needed
*/
#include <cstdio>
#include <set>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    bool same(false);           // Flag to check if any duplicates exist
    long zero(0);               // Count of zeros in the sequence
    std::set<long> s;           // Set to keep track of seen elements for detecting duplicates
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x == 0) {
        ++zero;                  // Increment zero counter
      }
      if (s.count(x)) {          // If element already exists in set
        same = true;             // Mark that duplicates are present
      }
      s.insert(x);               // Insert element into set
    }
    long ans(0);
    if (zero > 0) {
      ans = n - zero;            // All non-zero elements can be paired with zeros
    } else if (same) {
      ans = n;                   // If duplicates, we need to resolve them (n operations)
    } else {
      ans = n + 1;               // No zeros and no duplicates: extra operation needed
    }
    printf("%ld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/