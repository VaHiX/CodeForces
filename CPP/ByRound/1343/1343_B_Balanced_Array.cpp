// Problem: CF 1343 B - Balanced Array
// https://codeforces.com/contest/1343/problem/B

/*
B. Balanced Array
Purpose: Construct an array of length n (n is even) such that:
- First n/2 elements are even numbers
- Second n/2 elements are odd numbers
- All elements are distinct and positive
- Sum of first half equals sum of second half

Algorithm:
1. For n = 2, it's impossible to satisfy the conditions (only two elements: one even, one odd, cannot have equal sums)
2. For n >= 4:
   - First half: use first n/2 even numbers starting from 2
   - Second half: use first n/2-1 odd numbers starting from 1
   - Adjust the last element of the second half to make sums equal

Time Complexity: O(n) per test case, because we iterate through roughly n elements.
Space Complexity: O(n), for storing the output array (excluding input/output).

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n % 4) { // If n is not divisible by 4, it's impossible for certain conditions
      puts("NO");
      continue;
    }
    puts("YES");
    for (long p = 1; 2 * p <= n; p++) { // Print first n/2 even numbers: 2, 4, 6, ...
      printf("%ld ", 2 * p);
    }
    for (long p = 0; p + 1 < n / 2; p++) { // Print first n/2-1 odd numbers: 1, 3, 5, ...
      printf("%ld ", 2 * p + 1);
    }
    printf("%ld\n", 3 * n / 2 - 1); // Adjust last element to balance the sums
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/