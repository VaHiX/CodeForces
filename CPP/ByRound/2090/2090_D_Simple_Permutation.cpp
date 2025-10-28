// Problem: CF 2090 D - Simple Permutation
// https://codeforces.com/contest/2090/problem/D

/*
D. Simple Permutation
Purpose: Construct a permutation of length n such that at least floor(n/3) - 1 of the ceiling averages c_i are prime.
Algorithms/Techniques: 
    - Brute-force search for largest prime less than or equal to n/2
    - Use that prime as a base to generate a sequence where values are arranged in a specific pattern
    - Check primality of computed averages using a helper function
Time Complexity: O(n * sqrt(n)) per test case due to primality check inside loop
Space Complexity: O(1) excluding input/output

Input:
    Integer t (number of test cases)
    For each test case, integer n (size of permutation)
Output:
    Permutation satisfying the condition
*/

#include <stdio.h>
#include <iosfwd>

#define ll long long
using namespace std;

ll t, n;

// Checks if a number is prime
int isp(ll x) {
  if (x == 1)
    return 0;
  for (ll i = 2; i * i <= x; i++) {
    if (x % i == 0)
      return 0;
  }
  return 1;
}

int main() {
  scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    scanf("%d", &n);
    if (n == 2)
      printf("2 1\n"); // Special case for n=2
    else if (n == 3)
      printf("2 1 3\n"); // Special case for n=3
    else {
      for (int i = n / 2; i > 0; i--) {
        if (isp(i)) { // Find largest prime <= n/2
          printf("%d ", i); // Print the prime number
          for (int j = i - 1; j > 0; j--)
            printf("%d %d ", j, i - j + i); // Generate pattern based on prime value
          for (int j = i + i; j <= n; j++)
            printf("%d ", j); // Continue with remaining numbers
          printf("\n");
          break;
        }
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/