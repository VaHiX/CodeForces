// Problem: CF 1845 A - Forbidden Integer
// https://codeforces.com/contest/1845/problem/A

/*
Algorithm/Techniques: Greedy approach
Time Complexity: O(n) per test case, where n is the value of n
Space Complexity: O(1) - only using a few variables and outputting the result

The problem is to determine whether we can form a sum 'n' using integers from 1 to k, excluding x.
We use a greedy strategy:
1. If x != 1, we can always use 1s to make up the sum, so it's always possible.
2. If x == 1, then we must avoid using 1, so we try to use 2s, and if that fails, we try to use 3s.
   - If k >= 2 and n is even, we can split n into 2s.
   - If k >= 3, we can use one 3 and rest 2s.
   - Else, it's impossible.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k, x;
    scanf("%ld %ld %ld", &n, &k, &x);
    if (x != 1) {
      // If x is not 1, we can always use 1s to make up the sum
      printf("YES\n%ld\n", n);
      for (long p = 0; p < n; p++) {
        // Print 1, n times
        printf("1 ");
      }
      puts("");  // Print newline
    } else if (k >= 2 && n % 2 == 0) {
      // If x is 1, we can't use 1s. If n is even and k >= 2, we can use 2s.
      printf("YES\n%ld\n", n / 2);
      for (long p = 0; p < n / 2; p++) {
        // Print 2, n/2 times
        printf("2 ");
      }
      puts("");  // Print newline
    } else if (k >= 3) {
      // If x is 1, k >= 3, and n is odd (or even but not dividable by 2 cleanly),
      // we can start with one 3, then fill the rest with 2s.
      printf("YES\n%ld\n3 ", (n / 2));
      for (long p = 1; p < n / 2; p++) {
        // Print 2s after the initial 3
        printf("2 ");
      }
      puts("");  // Print newline
    } else {
      // If none of the above conditions match, it's not possible
      puts("NO");
      continue;
    }
  }
}


// https://github.com/VaHiX/CodeForces/