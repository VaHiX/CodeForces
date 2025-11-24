// Problem: CF 1323 A - Even Subset Sum Problem
// https://codeforces.com/contest/1323/problem/A

/*
Problem: Even Subset Sum
Purpose: Given an array of positive integers, find a non-empty subset whose sum is even,
         or determine that no such subset exists.

Algorithms/Techniques: Greedy approach based on parity (odd/even) of numbers
Time Complexity: O(n) per test case, where n is the length of the array
Space Complexity: O(1), constant extra space

The solution works as follows:
- If n == 1: Only one element in array. If it's even, output index 1; if odd, output -1.
- If n > 1: 
    * Check first two elements: if both are odd, we can pick the first two elements (sum is even).
    * Otherwise, we can always pick one of the first two elements such that sum is even.

This greedy strategy is based on elementary number theory:
- Even + Even = Even
- Odd + Odd = Even  
- Even + Odd = Odd

So to get an even sum from at least 2 elements, we need to check whether we can form a pair of odd numbers.
If the first two elements aren't both odd, then we can always choose 1 element from beginning 
to make the subset sum even (if first is even, take it; if second is even, take it).
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n <= 1) {
      long x;
      scanf("%ld", &x);
      puts((x & 1) ? "-1" : "1\n1");
    } else {
      long a;
      scanf("%ld", &a);
      long b;
      scanf("%ld", &b);
      // Skip remaining elements since we only care about first two for the logic
      for (long p = 2; p < n; p++) {
        long x;
        scanf("%ld", &x);
      }
      // If both first two numbers are odd, their sum is even, so we choose them
      if ((a & 1) && (b & 1)) {
        printf("2\n1 2\n");
      } else {
        // Otherwise, at least one of the first two numbers is even,
        // so we can pick that one to make subset sum even
        printf("1\n%d\n", (a & 1) ? 2 : 1);
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/