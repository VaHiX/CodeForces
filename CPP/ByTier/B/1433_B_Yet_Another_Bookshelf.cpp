// Problem: CF 1433 B - Yet Another Bookshelf
// https://codeforces.com/contest/1433/problem/B

/*
 * Problem: B. Yet Another Bookshelf
 *
 * Purpose: Given a bookshelf represented as a binary array where 1 means a book exists,
 *          find the minimum number of moves to gather all books into a contiguous segment.
 *
 * Algorithm:
 *   - For each test case, identify all groups of consecutive books (segments of 1s).
 *   - Compute the minimum moves needed by counting the gaps between such segments
 *     and determining how many shifts are required to align them contiguously.
 *   - The approach uses a single pass through the array to count 'gaps' which represent
 *     necessary shifts.
 *
 * Time Complexity: O(n) where n is the size of the array (each element visited once)
 * Space Complexity: O(1) constant extra space used
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long inside(0), cur(0), cnt(0); // inside: tracks if we are within a book segment; cur: counts books before current gap; cnt: accumulates moves
    for (long p = 0; p < n; p++) {
      long a;
      scanf("%ld", &a);
      if (a) { // If we hit a book
        inside = 1; // Now we are inside a book segment
        cnt += cur; // Add the number of books before this book to our move count
        cur = 0; // Reset counter for next segment
      } else { // If it's an empty spot
        cur += inside; // Only increment if we were previously in a book segment (i.e., there was a book before this gap)
      }
    }
    printf("%ld\n", cnt);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/