// Problem: CF 891 A - Pride
// https://codeforces.com/contest/891/problem/A

/*
Algorithm: 
This problem involves making all elements of an array equal to 1 using operations where we replace one of two adjacent elements with their GCD.
Key observations:
1. If any element is already 1, we can propagate 1s through the array.
2. If GCD of entire array is not 1, it is impossible to make all elements 1.
3. If GCD of entire array is 1, we need to find minimum operations to create a 1, then use it to convert the rest.

Approach:
- If there are already 1s in the array, we need (n - count_of_1s) operations to propagate 1s.
- Otherwise, we try to find a subarray where we can create a 1 by taking GCDs of adjacent elements. 
  This requires at most n-1 operations to get a 1 in a subarray.
- Then, we can spread the 1 throughout the array in (n - 1) operations.

Time Complexity: O(n^2) due to nested loops for finding subarray GCD.
Space Complexity: O(1) as we only use a fixed-size array and variables.

*/

#include <algorithm>
#include <cstdio>
int n, r, i, j, a[2000];
int g() {
  if (r) // If there are already 1s in the array
    return n - r; // Return operations to spread 1s to the rest
  for (i = 1; i < n; ++i) // Try to find a subarray with GCD 1
    for (j = 0; j + i < n; ++j)
      if ((a[j] = std::__gcd(a[j], a[j + 1])) == 1) // Update a[j] to GCD of adjacent elements
        return i + n - 1; // Return operations: steps to create 1 + steps to spread it
  return -1; // If no 1 is found and GCD of the whole array is not 1, impossible
}
int main() {
  scanf("%d", &n);
  for (i = 0; i < n; ++i) {
    scanf("%d", a + i);
    if (a[i] == 1)
      ++r; // Count how many 1s are already present
  }
  printf("%d", g());
}


// https://github.com/VaHiX/CodeForces/