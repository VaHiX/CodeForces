// Problem: CF 1713 B - Optimal Reduction
// https://codeforces.com/contest/1713/problem/B

/*
B. Optimal Reduction
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

Task:
Determine if for all permutations b of array a, f(a) <= f(b) is true.
f(a) is the minimum number of operations to reduce array a to zeros.
Each operation decreases a contiguous subarray by 1.

Algorithm:
The key insight is that the minimum number of operations equals the number of "peaks" 
in the array where elements are strictly increasing followed by strictly decreasing.
This can be computed by scanning the array and counting transitions from increasing to decreasing.

Time Complexity: O(n) per test case
Space Complexity: O(n) for the input array

*/

#include <stdio.h>
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n;
    scanf("%d", &n);
    int arr[n]; // Array to store input elements
    for (int i = 0; i < n; i++) {
      scanf("%d", &arr[i]); // Read array elements
    }
    int i = 0;
    // Traverse while strictly increasing
    while (i + 1 < n && arr[i + 1] >= arr[i])
      i++;
    // Traverse while strictly decreasing
    while (i + 1 < n && arr[i + 1] <= arr[i])
      i++;
    // If we reached the end, it's a valid sequence
    if (i + 1 == n)
      printf("YES\n");
    else
      printf("NO\n");
  }
}


// https://github.com/VaHiX/codeForces/