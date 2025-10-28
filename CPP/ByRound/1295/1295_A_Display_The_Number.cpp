// Problem: CF 1295 A - Display The Number
// https://codeforces.com/contest/1295/problem/A

/*
 * Problem: Display The Number
 * Algorithm: Greedy approach to maximize the number by selecting optimal digits.
 *            - For odd n: use '7' (requires 3 segments) and then fill remaining with '1's (2 segments each).
 *            - For even n: fill all with '1's (2 segments each).
 * Time Complexity: O(n) per test case, since we iterate at most n/2 times for printing '1's.
 * Space Complexity: O(1) excluding output storage.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n & 1) {        // If n is odd, start with '7' which uses 3 segments
      printf("7");
      n -= 3;           // Reduce n by 3 since we've used 3 segments for '7'
    }
    for (long p = 0; p < (n / 2); p++) {  // Fill remaining with '1's (each uses 2 segments)
      printf("1");
    };
    puts("");           // Print new line after each result
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/