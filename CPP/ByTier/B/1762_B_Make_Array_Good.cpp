// Problem: CF 1762 B - Make Array Good
// https://codeforces.com/contest/1762/problem/B

/*
Code Purpose:
This code solves the problem of making an array "good" by performing at most n operations.
Each operation allows us to increase a selected element by some value x, such that the resulting array satisfies the condition that for any two elements, their maximum is divisible by their minimum.
The approach is to process each element in order and set it to the smallest power of 2 that is greater than or equal to the current value.
This ensures that all elements will be powers of 2 and hence any two elements will satisfy the divisibility condition.

Algorithms/Techniques:
- For each element, compute the smallest power of 2 >= current value
- This is done by repeatedly multiplying by 2 until the value is reached

Time Complexity: O(n log(max(a_i))) where n is the number of elements and max(a_i) is the maximum element in the array.
Space Complexity: O(1) - only using a constant amount of extra space.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    printf("%ld\n", n);
    for (long p = 1; p <= n; p++) {
      long x;
      scanf("%ld", &x);
      long y(1);
      while (y < x) {
        y *= 2;
      }
      printf("%ld %ld\n", p, y - x);
    }
  }
}


// https://github.com/VaHiX/CodeForces/