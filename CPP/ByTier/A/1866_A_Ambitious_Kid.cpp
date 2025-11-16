// Problem: CF 1866 A - Ambitious Kid
// https://codeforces.com/contest/1866/problem/A

/*
Problem: Make the product of an array equal to 0 with minimum operations.
Each operation allows increasing or decreasing any element by 1.

Algorithm:
- To make the product zero, at least one element must be 0.
- For each element, calculate how many operations are needed to make it 0.
- Find the minimum among all such values and return it.

Time Complexity: O(n), where n is the number of elements in the array.
Space Complexity: O(1), only using a constant amount of extra space.

Techniques:
- Greedy approach: minimize the number of operations by choosing the element closest to 0.
*/

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long ans(1e5 + 7); // Initialize with a large value to find minimum
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    x = (x < 0) ? -x : x; // Take absolute value of x to compute distance from 0
    ans = (ans < x) ? ans : x; // Keep track of the minimum distance to 0
  }
  printf("%ld\n", ans);
}


// https://github.com/VaHiX/codeForces/