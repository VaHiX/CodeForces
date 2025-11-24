// Problem: CF 1806 B - Mex Master
// https://codeforces.com/contest/1806/problem/B

/*
B. Mex Master
Purpose: Given an array of integers, find the minimum possible MEX of the sums of adjacent pairs after optimally rearranging the array.

Algorithm:
- For each test case, count occurrences of 0s, 1s, and larger values.
- If number of zeros exceeds (n+1)/2:
  - If there are no 1s or there are large numbers, result is 1
  - Otherwise, result is 2
- Otherwise, if number of zeros <= (n+1)/2:
  - If there is at least one 1, then we can make a valid sequence starting from 0 that includes 0,1,2,... up to some point
  - The minimum score will be 0 in that case.
Time Complexity: O(n) per test case
Space Complexity: O(1)
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long z(0); // Count of zeros
    bool one(false), large(false); // Flags for presence of 1 and numbers > 1
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x == 0) {
        ++z;
      } else if (x == 1) {
        one = true;
      } else if (x > 1) {
        large = true;
      }
    }
    long res(0); // Result to be printed
    if (z > (n + 1) / 2) { // If zeros are more than half
      if (!one || large) { // If no 1s or there is a large number
        res = 1; // Minimum MEX will be 1
      } else {
        res = 2; // Otherwise it's 2 as we can form 0,1 but not 2
      }
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/