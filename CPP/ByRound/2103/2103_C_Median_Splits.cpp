// Problem: CF 2103 C - Median Splits
// https://codeforces.com/contest/2103/problem/C

/*
C. Median Splits
Algorithms/Techniques: Greedy, Two Pointers, Median Calculation

Time Complexity: O(n) per test case
Space Complexity: O(n) for the array a

The problem asks to determine if we can split an array into three contiguous subarrays 
such that the median of the medians of those subarrays is <= k.

Approach:
1. Transform the input array such that elements > k become 1, and others become -1.
2. Use two pointers to find the longest prefix and suffix where the cumulative sum remains positive.
3. If we have more than one element between l and r, it's a valid split.
4. Otherwise, check if there are at least two negative elements (in terms of transformation) 
   in prefix and suffix that can allow us to adjust the median condition.

*/

#include <iostream>

#define N 200005
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int t, n, k, i, a[N], l, r, s, fl, fr;
  cin >> t;
  while (t--) {
    cin >> n >> k;
    for (i = 0; i < n; i++)
      cin >> a[i];
    // Transform array: elements > k become 1, others become -1
    for (i = 0; i < n; i++)
      if (a[i] > k)
        a[i] = 1;
      else
        a[i] = -1;
    
    // Find the end of first valid prefix where cumulative sum never goes below zero
    s = 0;
    for (l = 0; l < n; l++) {
      s += a[l];
      if (s <= 0)
        break;
    }
    
    // Find the start of last valid suffix where cumulative sum never goes below zero
    s = 0;
    for (r = n - 1; r >= 0; r--) {
      s += a[r];
      if (s <= 0)
        break;
    }
    
    // If there's space between l and r, we can make three splits
    if (r - l > 1)
      cout << "YES\n";
    else {
      // Check number of negatives in prefix (before l)
      s = fl = 0;
      for (l = 0; l < n - 1; l++) {
        s += a[l];
        if (s <= 0 && a[l] == -1)
          fl++;
      }
      
      // Check number of negatives in suffix (after r)
      s = fr = 0;
      for (r = n - 1; r > 0; r--) {
        s += a[r];
        if (s <= 0 && a[r] == -1)
          fr++;
      }
      
      // If at least two negatives are found in either prefix/suffix, possible to construct valid split
      if (fl >= 2 || fr >= 2)
        cout << "YES\n";
      else
        cout << "NO\n";
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/