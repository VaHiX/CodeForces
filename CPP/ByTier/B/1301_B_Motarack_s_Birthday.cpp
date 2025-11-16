// Problem: CF 1301 B - Motarack's Birthday
// https://codeforces.com/contest/1301/problem/B

/*
Code Purpose:
This program finds the minimum possible maximum absolute difference between adjacent elements in an array 
where some elements are missing (-1). It fills the missing elements with a single value k to minimize this 
maximum difference.

Algorithm:
1. For each test case, find the range of known values in the array.
2. Calculate a candidate value for k as the average of the maximum and minimum known values.
3. Fill all missing elements with this k value.
4. Compute the maximum absolute difference between adjacent elements and output it along with k.

Time Complexity: O(n) per test case. We make a constant number of passes through the array.
Space Complexity: O(n) for storing the array elements.

Techniques:
- Greedy approach to select k as mid-point of known values' range.
- Two-pass algorithm: first to find bounds, second to compute result.
*/

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, i, j, k, a[200001], mx = -2e9, mn = 2e9;
    cin >> n;
    for (i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }
    a[n] = 100; // Sentinel value to avoid boundary checks
    for (i = 0; i < n; i++) {
      // If current element is known and one of its neighbors is missing,
      // update max and min of known elements
      if ((i > 0 && a[i - 1] == -1 || a[i + 1] == -1) && a[i] != -1) {
        mx = max(mx, a[i]);
        mn = min(mn, a[i]);
      }
    }
    int u = (mx + mn) / 2, dif = -2e9;
    for (i = 1; i < n; i++) {
      // Fill missing elements with the candidate value u
      if (a[i - 1] == -1)
        a[i - 1] = u;
      if (a[i] == -1)
        a[i] = u;
      // Compute maximum difference after filling
      dif = max(dif, abs(a[i] - a[i - 1]));
    }
    cout << dif << ' ' << u << endl;
  }
}


// https://github.com/VaHiX/CodeForces/