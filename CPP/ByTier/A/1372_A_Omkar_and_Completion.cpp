// Problem: CF 1372 A - Omkar and Completion
// https://codeforces.com/contest/1372/problem/A

/*
Code Purpose:
This code solves the problem of generating a "complete" array of length n, where:
- All elements are positive integers between 1 and 1000.
- For any three indices x, y, z, the sum of elements at x and y is not equal to the element at z.
The solution uses a simple strategy: if all elements are 1, then the sum of any two elements is 2, 
which is never equal to any element (since all elements are 1).

Algorithms/Techniques:
- Greedy approach: Fill the array with all 1s.
- Mathematical property: Since all elements are 1, all pairwise sums are 2 and there's no element 2, so constraint is satisfied.

Time Complexity: O(n) per test case, as we simply output n ones.
Space Complexity: O(1) extra space, not counting input/output.

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    for (long p = 0; p < n; p++) {
      printf("1 "); // Output 1 for each position in the array
    }
    puts(""); // Print newline after each test case
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/