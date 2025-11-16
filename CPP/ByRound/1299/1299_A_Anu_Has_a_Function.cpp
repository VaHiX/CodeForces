// Problem: CF 1299 A - Anu Has a Function
// https://codeforces.com/contest/1299/problem/A

/*
Purpose: This program reorders an array of integers to maximize the value of the function f(f(...f(a1, a2), a3)..., an) where f(x, y) = (x | y) - y.
The algorithm identifies the highest bit position where exactly one number in the array has a '1' bit, and places that number first to maximize the result.

Algorithms/Techniques:
- Bit manipulation to find the most significant bit where exactly one number has a '1'
- Greedy approach to position the element with unique high bit first
- Sorting by bit positions using bit checks

Time Complexity: O(n * log(max_value)) where n is the number of elements and max_value is up to 10^9
Space Complexity: O(n) for storing the array

*/

#include <stdio.h>
int a[100010];
int main() {
  int n, i, j, cnt, k, t;
  scanf("%d", &n);
  for (i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  // Loop from the highest bit (30) down to 0 to find the first bit position 
  // where exactly one number in the array has a '1' in that position
  for (j = 30; j >= 0; j--) {
    cnt = 0;
    for (i = 1; i <= n; i++)
      if ((a[i] >> j) & 1)  // Check if bit j is set in a[i]
        cnt++, k = i;       // Count such numbers and remember the index
    if (cnt == 1)           // If exactly one number has '1' at bit j, stop
      break;
  }
  // If we found such a unique bit, swap the first element with the element having that bit
  if (cnt == 1)
    t = a[1], a[1] = a[k], a[k] = t;
  // Print the reordered array
  printf("%d", a[1]);
  for (i = 2; i <= n; i++)
    printf(" %d", a[i]);
  printf("\n");
}


// https://github.com/VaHiX/CodeForces/