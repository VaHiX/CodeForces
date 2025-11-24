// Problem: CF 1529 B - Sifid and Strange Subsequences
// https://codeforces.com/contest/1529/problem/B

/*
B. Sifid and Strange Subsequences
Algorithm: Greedy approach with sorting
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing negative numbers

A sequence is strange if the absolute difference between any pair of its elements 
is greater than or equal to the maximum element in the sequence.
The strategy is to:
1. Separate positive and non-positive numbers
2. For non-positive numbers, sort them and check constraints
3. If there are positive numbers, we may include at most one of them,
   if it's large enough to satisfy the strange condition with respect 
   to the smallest negative number.
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
    std::vector<long> neg; // Store all non-positive numbers
    long mn(1e9 + 7);      // Track the smallest positive number encountered
    bool extra(false);     // Indicates whether we can include a positive number
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x <= 0) {
        neg.push_back(x); // Add non-positive numbers to neg vector
      } else if (x < mn) {
        extra = true;     // We can potentially include this positive number
        mn = x;           // Update the minimum positive number seen so far
      }
    }
    sort(neg.begin(), neg.end()); // Sort negative numbers in ascending order
    for (long p = 1; p < neg.size(); p++) {
      if (neg[p] - neg[p - 1] < mn) { // Check if the difference between consecutive 
        extra = false;                // negatives is less than the smallest positive
        break;
      }
    }
    printf("%ld\n", neg.size() + extra); // Output total size of strange subsequence
  }
}


// https://github.com/VaHiX/codeForces/