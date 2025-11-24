// Problem: CF 1721 C - Min-Max Array Transformation
// https://codeforces.com/contest/1721/problem/C

/*
Algorithm/Techniques: 
- For each element in the array `a`, we determine the minimum and maximum possible values of `d[i]` such that when we add `d[i]` to `a[i]` and sort the result, we get the array `b`.
- Minimum `d[i]`: For the i-th element in `a`, we find the smallest element in `b` that is greater than or equal to `a[i]`, and the difference between them becomes the minimum `d[i]`.
- Maximum `d[i]`: We track an index `ind` that moves forward to determine the maximum `d[i]` such that `a[i] + d[i] <= b[ind]` and the resulting sorted array `b` is valid.

Time Complexity: O(n log n) per test case due to sorting and binary search.
Space Complexity: O(n) for storing the arrays `a` and `b`.
*/

#include <algorithm>
#include <iostream>

using namespace std;
int a[1000005], b[1000005], n;
int main() {
  int t;
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 0; i < n; i++)
      cin >> a[i];
    for (int i = 0; i < n; i++)
      cin >> b[i];
    
    // Calculate minimum d[i] values
    for (int i = 0; i < n; i++)
      cout << *lower_bound(b, b + n, a[i]) - a[i] << ' '; // Find the smallest b[j] >= a[i]
    cout << endl;
    
    // Calculate maximum d[i] values
    int ind = 0;
    for (int i = 0; i < n; i++) {
      ind = max(ind, i); // Make sure ind doesn't go backward
      // Move ind forward while a[ind + 1] <= b[ind]
      while (ind < n - 1 && a[ind + 1] <= b[ind])
        ind++;
      cout << b[ind] - a[i] << ' '; // Max d[i] is b[ind] - a[i]
    }
    cout << endl;
  }
}


// https://github.com/VaHiX/CodeForces/