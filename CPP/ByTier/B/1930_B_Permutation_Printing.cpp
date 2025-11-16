// Problem: CF 1930 B - Permutation Printing
// https://codeforces.com/contest/1930/problem/B

/*
Algorithm: Greedy Construction
Approach:
- We construct the permutation by alternating between the smallest available number (from left) 
  and the largest available number (from right).
- This ensures that no two adjacent elements in the permutation have a divisibility relationship 
  that would violate the condition.
- For even positions (0-indexed), we take from the left (small numbers).
- For odd positions (0-indexed), we take from the right (large numbers).

Time Complexity: O(n) per test case
Space Complexity: O(1) extra space (not counting input/output)

This method works because placing smaller numbers at even indices and larger at odd indices 
avoids creating pairs where one element divides another in consecutive positions.
*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long left(1), right(n);                // left starts at 1, right starts at n
    for (long p = 0; p < n; p++) {
      printf("%ld ", (p % 2) ? (right--) : (left++)); // if p is odd, use right; else use left
    }
    puts("");                              // print newline after each permutation
  }
}


// https://github.com/VaHiX/CodeForces/