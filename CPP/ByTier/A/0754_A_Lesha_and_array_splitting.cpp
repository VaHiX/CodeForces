// Problem: CF 754 A - Lesha and array splitting
// https://codeforces.com/contest/754/problem/A

/*
 * Problem: Lesha and array splitting
 * Purpose: Split an array into subarrays such that the sum of each subarray is not zero.
 * Algorithm: 
 *   - Calculate the total sum of the array.
 *   - If the total sum is non-zero, we can take the whole array as one part.
 *   - If the total sum is zero, we look for the first non-zero element from the left.
 *     We split the array into two parts: from start to this element, and from next element to end.
 *     This ensures both parts have non-zero sums if the first part is not empty.
 * Time Complexity: O(n), where n is the number of elements in the array.
 * Space Complexity: O(1), only using a few variables regardless of input size.
 */

#include <stdio.h>
#include <iostream>

int main() {
  int n, m, s = 0, f = 0, a;
  std::cin >> n, m = n;
  for (; m--;) {
    std::cin >> a;
    s += a;
    if (a)
      f = n - m - 1;  // Track index of the first non-zero element from the left
  }
  if (s)  // If total sum is non-zero, one part is sufficient
    printf("YES\n1\n1 %d", n);
  else if (f > 0)  // If total sum is zero and there's a non-zero element, split at first non-zero
    printf("YES\n2\n1 %d\n%d %d", f, f + 1, n);
  else  // If all elements are zero, impossible to split
    printf("NO");
}


// https://github.com/VaHiX/CodeForces/