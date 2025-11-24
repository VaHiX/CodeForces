// Problem: CF 1407 A - Ahahahahahahahaha
// https://codeforces.com/contest/1407/problem/A

/*
Algorithm: Greedy approach
- Count the number of 1s in the array.
- If the count of 1s is less than or equal to n/2, output n/2 zeros.
- Otherwise, output as many 1s as possible such that the count is even and 
  the alternating sum becomes 0. Specifically, output (countOf1s - (countOf1s % 2)) 1s.

Time Complexity: O(n) - We scan the array once to count 1s.
Space Complexity: O(1) - Only using a few variables, no extra space needed.

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long cnt(0); // Count of 1s in the array
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      cnt += x; // Increment count if current element is 1
    }
    if (cnt <= n / 2) {
      // If number of 1s is less than or equal to n/2,
      // we can just output n/2 zeros
      printf("%ld\n", n / 2);
      for (long p = 0; p < n / 2; p++) {
        printf("0 ");
      };
    } else {
      // Otherwise, we reduce the count of 1s to make it even,
      // and output that many 1s
      cnt -= (cnt % 2); // Make cnt even
      printf("%ld\n", cnt);
      for (long p = 0; p < cnt; p++) {
        printf("1 ");
      };
    }
    puts(""); // Print a newline after each test case
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/