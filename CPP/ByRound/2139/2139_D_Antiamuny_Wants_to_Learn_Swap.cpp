// Problem: CF 2139 D - Antiamuny Wants to Learn Swap
// https://codeforces.com/contest/2139/problem/D

/*
 * Problem: D. Antiamuny Wants to Learn Swap
 * Purpose: Determine if a subarray is "perfect", meaning that using both adjacent swaps and
 *          swaps of elements two positions apart doesn't reduce the number of operations needed to sort.
 *
 * Algorithm:
 *   - For each query [l, r], check whether subarray a[l..r] is perfect.
 *   - Key idea: A subarray is perfect if it does not benefit from using operation 2 (swapping elements
 *               two positions apart), i.e., the number of operations needed using only adjacent swaps
 *               equals the number needed with both swap types.
 *
 *   - We precompute for each position i:
 *     * mxl[i]: leftmost index j such that a[j] < a[i] and j < i; helps detect "inversions" that would require more operations.
 *     * mir[i]: rightmost index j such that a[j] > a[i] and j > i; similar logic.
 *   - We use these to determine the maximum left boundary that "blocks" the optimal swap for a right element.
 *   - Then, we compute L[r], which is the maximal mxl value possible in subarray [1..r].
 *   - For each query [l, r], if l <= L[r], this means there exists an index whose "left inversion"
 *     crosses or touches the query left boundary, so the subarray is not perfect.
 *     
 * Time Complexity: O(n + q)
 * Space Complexity: O(n)
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void solve() {
  int n, q;
  cin >> n >> q;
  vector<int> a(n + 2); // 1-indexed array with padding
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  
  // mxl[i] stores the leftmost index j such that a[j] < a[i]
  vector<int> mxl(n + 1), mir(n + 1);
  for (int i = 1; i <= n; i++) {
    mxl[i] = i - 1;
    while (mxl[i] > 0 && a[mxl[i]] < a[i])
      mxl[i] = mxl[mxl[i]];
  }
  
  // mir[i] stores the rightmost index j such that a[j] > a[i]
  for (int i = n; i >= 1; i--) {
    mir[i] = i + 1;
    while (mir[i] <= n && a[mir[i]] > a[i])
      mir[i] = mir[mir[i]];
  }
  
  // L[r] represents the maximum value of mxl[i] for all i in [1, r]
  vector<int> L(n + 1, 0);
  for (int i = 2; i < n; i++) {
    if (mxl[i] > 0 && mir[i] <= n) {
      L[mir[i]] = max(L[mir[i]], mxl[i]);
    }
  }
  
  // Propagate the maximum from left to right
  for (int i = 1; i <= n; i++) {
    L[i] = max(L[i], L[i - 1]);
  }
  
  // Process queries
  for (int i = 0; i < q; i++) {
    int l, r;
    cin >> l >> r;
    if (l <= L[r])
      cout << "NO\n";
    else
      cout << "YES\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    solve();
  }
}


// https://github.com/VaHiX/codeForces/