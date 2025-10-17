// Problem: CF 1882 A - Increasing Sequence
// https://codeforces.com/contest/1882/problem/A

/*
 * Problem: Minimum Last Element of a Good Sequence
 *
 * Description:
 * Given a sequence a1, a2, ..., an, find the minimum possible value of bn
 * among all "good" sequences b1, b2, ..., bn such that:
 *   1. Each bi is a positive integer
 *   2. bi != ai for all i
 *   3. b1 < b2 < ... < bn
 *
 * Algorithm/Approach:
 * - Greedily construct the sequence b from left to right.
 * - For each position i, choose the smallest valid value for bi such that:
 *   - bi > bi-1 (to maintain strict increasing order)
 *   - bi != ai (to satisfy the constraint)
 * - Use a variable 'b' to track the current value being assigned.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the input array
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    long b(0); // Start with b = 0, will be incremented as we build the sequence
    for (long p = 0; p < n; p++) {
      ++b; // Increment b to try next available value
      if (b == a[p]) {
        // If current b equals a[p], skip it and increment again
        ++b;
      }
    }
    printf("%ld\n", b);
  }
}


// https://github.com/VaHiX/codeForces/