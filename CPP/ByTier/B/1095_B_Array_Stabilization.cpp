// Problem: CF 1095 B - Array Stabilization
// https://codeforces.com/contest/1095/problem/B

/*
B. Array Stabilization

Purpose:
This program finds the minimum possible instability (difference between max and min elements) 
after removing exactly one element from the array.

Algorithm:
1. Sort the array to easily access min and max elements.
2. Try two cases:
   - Remove the largest element (last in sorted array)
   - Remove the smallest element (first in sorted array)
3. Compute instability for both cases and return the minimum.

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the array

Input:
- First line: n (size of array)
- Second line: n integers representing array elements

Output:
- Minimum possible instability after removing exactly one element
*/

#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  int i, n;
  cin >> n;
  int a[n]; // Array to store input elements
  for (i = 0; i < n; i++)
    cin >> a[i]; // Read array elements
  sort(a, a + n); // Sort the array to easily access min and max
  // Calculate instability by removing either first or last element
  cout << min(a[n - 1] - a[1], a[n - 2] - a[0]);
}


// https://github.com/VaHiX/codeForces/