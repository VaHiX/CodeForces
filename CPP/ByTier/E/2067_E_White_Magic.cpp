// Problem: CF 2067 E - White Magic
// https://codeforces.com/contest/2067/problem/E

/*
E. White Magic
Algorithms/Techniques: Greedy with MEX calculation and tracking of prefix minimums.
Time Complexity: O(n) amortized per test case, due to the use of a mex counter and careful updates.
Space Complexity: O(n), for storing arrays of size up to 2*10^5.

The task is to find the maximum length of a magical subsequence in a given array,
where a sequence is magical if for all prefixes, the minimum of that prefix
is greater than or equal to the mex of the suffix starting after that prefix.

Approach:
- Process the array from right to left.
- Keep track of how many zeros are encountered (c).
- For each element:
  - If it's not zero or we have only one zero remaining, increment its count in cnt array.
  - Update the mex value by advancing while there are elements in the range [0, mex].
- Compute final answer using a formula involving the total count of zeros and modified tk.

*/

#include <iostream>

using namespace std;
#define int long long
int a[200005], cnt[200005];

void DO() {
  int n;
  cin >> n;
  int tk = n, c = 0, cc; // tk: total count of elements to consider. c: number of zeros seen so far. cc: original count of zeros.
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    c += a[i] == 0; // Count zeros
    cc = c;         // Save initial zero count
  }
  for (int i = n, mex = 0; i >= 1; i--) {
    if (a[i] < mex)
      tk--; // If current element is less than mex, exclude it from result
    
    if (a[i] <= n and (a[i] != 0 or c == 1))
      cnt[a[i]]++; // Only count elements in [0, n], unless they are zeros with only one left
    
    c -= a[i] == 0; // Decrease zero counter as we move back
    
    while (cnt[mex]) // Increment mex if current mex is filled
      mex++;
  }
  cout << n - cc + (tk == n and cc) << '\n'; 
  for (int i = 0; i <= n; i++)
    cnt[i] = 0; // Reset counter array
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, i = 1;
  cin >> t;
  while (t--) {
    DO();
  }
}


// https://github.com/VaHiX/codeForces/