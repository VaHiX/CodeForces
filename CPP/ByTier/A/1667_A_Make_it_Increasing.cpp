// Problem: CF 1667 A - Make it Increasing
// https://codeforces.com/contest/1667/problem/A

/*
 * Problem: A. Make it Increasing
 * Purpose: Given an array of positive integers, find the minimum number of moves
 *          to make a derived array b strictly increasing, where each element
 *          in b is manipulated by adding or subtracting values from array a.
 *
 * Algorithm:
 *  - For each possible starting index p, simulate building a strictly increasing
 *    sequence by processing elements to the left and right of p.
 *  - For left side: Each element must be at least as large as the previous one,
 *    so compute how many operations are needed to maintain this condition.
 *  - For right side: Same logic is applied in reverse.
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(n)
 */
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  ll mncnt(1e18); // Initialize minimum count to a large value
  for (ll p = 0; p < n; p++) { // Try each index as a potential start point
    ll cnt(0), prev(0); // cnt: total moves, prev: previous value in sequence
    
    // Process elements to the left of p
    for (ll q = p - 1; q >= 0; q--) {
      ll mult = 1 + (prev / a[q]); // Compute multiplier needed to ensure increasing order
      prev = mult * a[q];          // Update prev to reflect new value in sequence
      cnt += mult;                 // Add operations used
    }
    
    prev = 0; // Reset prev for right side processing
    
    // Process elements to the right of p
    for (ll q = p + 1; q < n; q++) {
      ll mult = 1 + (prev / a[q]); // Compute multiplier needed to maintain increasing property
      prev = mult * a[q];          // Update prev with new value
      cnt += mult;                 // Accumulate total moves
    }
    
    mncnt = (mncnt < cnt ? mncnt : cnt); // Keep track of minimum operations
  }
  printf("%lld\n", mncnt);
}


// https://github.com/VaHiX/codeForces/