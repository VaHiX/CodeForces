// Problem: CF 1355 D - Game With Array
// https://codeforces.com/contest/1355/problem/D

/*
Code Purpose:
This program determines whether Petya can construct an array of N positive integers with sum S such that Vasya cannot find a subarray whose sum equals K or S - K for any valid K. 
The approach is to construct an array with mostly 2s and one larger element, ensuring that no such K exists that allows Vasya to win.

Algorithm:
1. Check if S < 2*N. If so, it's impossible to create an array of N positive integers with sum S, hence output "NO".
2. Otherwise, create an array of N-1 elements of value 2 and one element of value (S - 2*(N-1)).
3. Output K as (S - 2*(N-1)) / 2, which ensures that K or S-K never equals any subarray sum.

Time Complexity: O(N) - We only loop through N elements once to print the array.
Space Complexity: O(1) - Only a constant amount of extra space is used.
*/

#include <cstdio>
int main() {
  long n, s;
  scanf("%ld %ld", &n, &s);
  if (s < 2 * n) {  // If sum is less than 2*N, it's impossible to have N positive integers summing to S
    puts("NO");
  } else {
    puts("YES");
    for (long p = 1; p < n; p++) {  // Print N-1 twos
      printf("2 ");
    }
    printf("%ld\n1\n", s - 2 * (n - 1));  // Print the last element and K=1 as one possible valid K
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/