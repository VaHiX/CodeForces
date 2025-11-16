// Problem: CF 1042 C - Array Product
// https://codeforces.com/contest/1042/problem/C

/*
Purpose: 
This code solves the problem of maximizing the final value in an array after performing exactly n-1 operations. 
The operations allow multiplying two elements and replacing one with the product, or removing an element.
The algorithm tries to strategically use zeros to eliminate negative values and maximize the product, 
and handles special cases like arrays with only zeros or with an odd number of negatives.

Time Complexity: O(n) - Single pass through the array to find key elements and perform operations.
Space Complexity: O(n) - The array 'a' stores the input elements.
*/

#include <stdio.h>
#include <iostream>

using namespace std;
int a[200010];
int main() {
  int n, f = 0, p = 0, x = 0, y = 0;
  a[0] = -1e9; // Initialize with a value lower than minimum possible to avoid indexing issues
  cin >> n;
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]), f ^= a[i] < 0, a[i] < 0 && a[i] >= a[p] ? p = i : p; // Toggle f for each negative, store index of largest negative
  if (f)
    a[p] = 0; // If there are negative numbers, set the largest (closest to zero) to zero to reduce impact
  for (int i = 1; i <= n; i++) {
    if (!a[i]) {
      if (x)
        printf("%d %d %d\n", 1, x, i); // When a zero is found and x is already assigned, multiply x with i
      x = i; // Mark this as first zero (x)
    } else {
      if (y)
        printf("%d %d %d\n", 1, y, i); // When a non-zero is found and y is assigned, multiply y with i
      y = i; // Mark this as first non-zero (y)
    }
  }
  if (x && y)
    cout << 2 << " " << x; // If we have both a zero and a non-zero, perform operation 2 on the zero position
}


// https://github.com/VaHiX/CodeForces/