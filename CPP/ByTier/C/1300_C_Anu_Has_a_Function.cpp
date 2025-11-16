// Problem: CF 1300 C - Anu Has a Function
// https://codeforces.com/contest/1300/problem/C

/*
Purpose: 
This code reorders an array to maximize the value of the function f applied sequentially to all elements.
The function f(x, y) = (x | y) - y is used, where | denotes bitwise OR.
The approach uses prefix and suffix bitwise AND operations to determine the optimal element to place at the beginning of the array,
which maximizes the final result of the function chain.

Algorithm:
1. Compute bitwise NOT of all elements to transform the problem into a bitwise AND optimization.
2. Compute prefix and suffix arrays of bitwise AND of NOT values.
3. For each position (except first and last), compute the contribution of placing that element at the front.
4. Select the element that gives the maximum contribution.
5. Reorder the array to place that element at the front and print the result.

Time Complexity: O(n)
Space Complexity: O(n)

*/

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n), b(n); // a stores input, b stores bitwise NOT of a
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
    b[p] = ~a[p]; // bitwise NOT of a[p]
  }
  std::vector<long> left(n), right(n); // left[i] = AND of b[0] to b[i], right[i] = AND of b[i] to b[n-1]
  left[0] = b[0];
  for (long p = 1; p < n; p++) {
    left[p] = left[p - 1] & b[p]; // prefix AND
  }
  right[n - 1] = b[n - 1];
  for (long p = n - 2; p >= 0; p--) {
    right[p] = right[p + 1] & b[p]; // suffix AND
  }
  long ans = a[0] & right[1]; // initial maximum value (placing a[0] at front)
  long pos = 0; // position of best element to place at front
  if ((a[n - 1] & left[n - 2]) > ans) { // check last element
    ans = a[n - 1] & left[n - 2];
    pos = n - 1;
  }
  for (long p = 1; p < n - 1; p++) {
    long tmp = left[p - 1] & a[p] & right[p + 1]; // contribution of placing a[p] at front
    if (tmp > ans) {
      ans = tmp;
      pos = p;
    }
  }
  long tmp = a[0]; // swap the best element to front
  a[0] = a[pos];
  a[pos] = tmp;
  for (long p = 0; p < n; p++) {
    printf("%ld ", a[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/