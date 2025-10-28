// Problem: CF 1492 B - Card Deck
// https://codeforces.com/contest/1492/problem/B

/*
 * Problem: B. Card Deck
 * Purpose: Reorder a deck of cards to maximize the "order" value defined as sum of n^(n-i) * p_i.
 * Algorithm: 
 *   - Identify positions where elements are in decreasing order from left to right (maxima).
 *   - Use these maxima to determine how many cards to take in each step.
 *   - Process the sequence in reverse, printing segments between maxima in reverse order.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing vector and auxiliary array
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n), f; // v stores input deck, f stores indices of peaks
    long mx(0);                // tracks maximum value seen so far
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
      if (v[p] > mx) {         // if current element is greater than max so far
        mx = v[p];
        f.push_back(p);        // record index of new maximum
      }
    }
    f.push_back(n);            // add end marker to simplify loop logic
    
    // Process from right to left, printing segments between peaks in reverse
    for (long p = f.size() - 2; p >= 0; p--) {
      long start = f[p];
      long end = f[p + 1];
      for (long q = start; q < end; q++) {
        printf("%ld ", v[q]);
      }
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/