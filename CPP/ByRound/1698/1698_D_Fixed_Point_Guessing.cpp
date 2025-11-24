// Problem: CF 1698 D - Fixed Point Guessing
// https://codeforces.com/contest/1698/problem/D

/*
Algorithm: Binary Search on the answer
Purpose: Find the fixed point (element that did not change position) in an array that was created by swapping pairs of elements from the original sorted array [1,2,...,n].
The key insight is that we can determine if an element at position i is a fixed point by querying the prefix [1..i] and checking how many elements out of those are <= i. 
If the count of such elements is odd, then i is not a fixed point (because in a correctly swapped array with one element being fixed, if we fix an element at position i, 
then the prefix [1..i] should contain exactly i elements that are <= i from a fully sorted sequence. Any deviation from the expected pattern indicates a mismatch).
Time Complexity: O(log n) per test case due to binary search
Space Complexity: O(1) - only using a few variables for computation
*/
#include <iostream>
using namespace std;
int main() {
  int t, n;
  cin >> t;
  while (t--) {
    cin >> n;
    int l = 1, r = n, ans;
    while (l <= r) {
      int mid = (l + r) / 2, cnt = 0, a;
      cout << "? 1 " << mid << endl;  // Query prefix [1..mid]
      for (int i = 1; i <= mid; i++)
        cin >> a, cnt += a <= mid;  // Count elements in [1..mid] that are <= mid
      if (cnt % 2)  // If count is odd, the element at mid is not fixed (since it should be even in sorted order)
        r = mid - 1, ans = mid;  // Move left and store mid as potential answer
      else
        l = mid + 1;  // If even, move right
    }
    cout << "! " << ans << endl;  // Output the fixed point
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/