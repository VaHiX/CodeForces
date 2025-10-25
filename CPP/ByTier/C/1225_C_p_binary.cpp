// Problem: CF 1225 C - p-binary
// https://codeforces.com/contest/1225/problem/C

/*
C. p-binary
Purpose: Find the minimum number of p-binary numbers (numbers of the form 2^x + p) needed to represent a given positive integer n as their sum.
Algorithms/Techniques: Brute-force search over possible counts of terms, using bit counting to validate representations.
Time Complexity: O(log n * log n) where log n is due to the loop over 'a' and bitcount computation.
Space Complexity: O(1) - only using a few variables regardless of input size.

*/
#include <cstdio>
long bitcount(long x) {
  long cnt(0);
  while (x > 0) {
    cnt += x % 2; // Count the number of 1-bits in x
    x /= 2;       // Remove the lowest set bit
  }
  return cnt;
}
int main() {
  long n, p;
  scanf("%ld %ld", &n, &p);
  long res(-1);
  for (long a = 0; a < 32; a++) { // Try up to 32 terms (enough for any reasonable n)
    long tmp = n - a * p;         // Calculate what remaining sum would be if we use 'a' copies of p
    if (bitcount(tmp) <= a && a <= tmp) {  // If tmp has at most a bits set and is non-negative
      res = a;
      break;
    }
  }
  printf("%ld\n", res);
  return 0;
}


// https://github.com/VaHiX/codeForces/