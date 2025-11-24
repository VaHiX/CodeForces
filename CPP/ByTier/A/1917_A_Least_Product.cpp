// Problem: CF 1917 A - Least Product
// https://codeforces.com/contest/1917/problem/A

/*
 * Purpose: Solve the "Least Product" problem where we must find the minimum
 *          product of an array after performing operations to change elements
 *          to values within [0, a[i]] if a[i] >= 0 or [a[i], 0] if a[i] < 0.
 *          We also need to find the minimum number of operations to achieve this.
 *
 * Algorithm: 
 *   - If there is any zero in the array, the product can be made 0 with 0 operations.
 *   - If there are no zeros:
 *     - If the count of negative numbers is even, the product is already positive.
 *       So we must make one element 0 to minimize the product to 0 (1 operation).
 *     - If the count of negative numbers is odd, the product is negative.
 *       We can keep it negative but minimize it by making one element 0 (0 operations).
 *
 * Time Complexity: O(n) per test case, where n is the size of the array.
 * Space Complexity: O(1), only using a few variables for computation.
 */
#include <cstdio>

void work() {
  int n, x, t = 0, f = 0;  // t counts negatives, f tracks presence of zero
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &x);
    if (x < 0)
      t ^= 1;  // XOR toggles between even/odd count of negatives
    if (x == 0)
      f = 1;   // flag set if any zero exists
  }
  if (f || t)
    puts("0");       // if there's a zero or odd number of negatives, 0 operations needed
  else
    printf("1\n1 0\n"); // otherwise, one operation to make first element 0
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--)
    work();
}


// https://github.com/VaHiX/CodeForces/