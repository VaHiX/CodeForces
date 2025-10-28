// Problem: CF 2051 D - Counting Pairs
// https://codeforces.com/contest/2051/problem/D

/*
D. Counting Pairs
Algorithms/Techniques: Two-pointer technique with binary search (lower_bound and upper_bound)

Time Complexity: O(n^2 * log n) per test case due to sorting and nested loop with binary search operations.
Space Complexity: O(n) for the array storage.

Task:
You are given a sequence a, consisting of n integers. You are also given two integers x and y (x ≤ y).
A pair of integers (i,j) is considered interesting if:
1. 1 ≤ i < j ≤ n
2. If you simultaneously remove the elements at positions i and j from the sequence a,
   the sum of the remaining elements is at least x and at most y.

Your task is to determine the number of interesting pairs of integers for the given sequence a.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
long long T, n, x, y, a[200005], h, t, s, ans;

int main() {
  for (cin >> T; T--; ans = 0, s = 0) { // Read number of test cases and reset variables
    cin >> n >> x >> y;                   // Read n, x, y for current test case
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]), s += a[i];      // Read array elements and calculate total sum
    sort(a + 1, a + n + 1);               // Sort the array to enable binary search
    
    for (int i = 1; i <= n; i++) {        // For each element in the array
      int h = lower_bound(a + 1 + i, a + 1 + n, s - a[i] - y) - a; // Find the leftmost index where the remaining sum is >= x
      int t = upper_bound(a + 1 + i, a + 1 + n, s - a[i] - x) - a; // Find the rightmost index where the remaining sum is <= y
      ans += t - h;                       // Add count of valid pairs for current i
    }
    
    cout << ans << endl;                  // Output answer for this test case
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/