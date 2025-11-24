// Problem: CF 1182 A - Filling Shapes
// https://codeforces.com/contest/1182/problem/A

/*
A. Filling Shapes
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output
You have a given integer n. Find the number of ways to fill all 3 × n tiles with the shape described in the picture below. Upon filling, no empty spaces are allowed. Shapes cannot overlap.

This picture describes when n = 4. The left one is the shape and the right one is 3 × n tiles.

Algorithm: Dynamic Programming
Time Complexity: O(1) - constant time due to bit manipulation optimization
Space Complexity: O(1) - constant space usage

The problem can be solved using dynamic programming where we observe that:
- For odd n, it's impossible to fill the grid (return 0)
- For even n, the number of ways follows the pattern: 2^(n/2) 
- This is optimized using bit shifting: (1 << (n/2))
*/

#include <cstdio>
int main() {
  int n;
  scanf("%d", &n);
  long long ans = (n % 2) ? 0 : (1 << (n / 2));  // If n is odd, return 0; otherwise calculate 2^(n/2) using bit shift
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/codeForces/