// Problem: CF 2138 B - Antiamuny Wants to Learn Swap
// https://codeforces.com/contest/2138/problem/B

/*
Problem: Antiamuny Wants to Learn Swap
Purpose:
  Given a permutation of integers and queries on subarrays,
  determine whether each subarray is "perfect". A subarray is perfect if
  the minimum number of operations (using both adjacent swaps and swaps with gap 2)
  required to sort it equals the minimum number of adjacent swaps needed.

Algorithms/Techniques:
  - Preprocessing using monotonic stacks to compute left and right boundaries
  - Dynamic programming approach to track maximum valid left index for each right index,
    indicating how much we can "cover" a range with one operation of type 2.
  - Efficient range query checking using precomputed prefix maximums.

Time Complexity: O(n + q)
Space Complexity: O(n)

*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void solve() {
  int n, q;
  cin >> n >> q;
  vector<int> a(n + 2); // 1-indexed array
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  
  // mxl[i] stores the leftmost index j such that a[j] >= a[i] and j < i
  vector<int> mxl(n + 1), mir(n + 1);
  
  // Precompute left boundaries using stack-like logic
  for (int i = 1; i <= n; i++) {
    mxl[i] = i - 1;
    while (mxl[i] > 0 && a[mxl[i]] < a[i])
      mxl[i] = mxl[mxl[i]]; // Jump to next valid index
  }

  // Precompute right boundaries using stack-like logic
  for (int i = n; i >= 1; i--) {
    mir[i] = i + 1;
    while (mir[i] <= n && a[mir[i]] > a[i])
      mir[i] = mir[mir[i]]; // Jump to next valid index
  }

  // L[r] stores the maximum left boundary for which we can "cover" up to r with one swap
  vector<int> L(n + 1, 0);
  for (int i = 2; i < n; i++) {
    if (mxl[i] > 0 && mir[i] <= n) {
      L[mir[i]] = max(L[mir[i]], mxl[i]); // Update maximum left boundary for right endpoint
    }
  }

  // Prefix max so that L[i] represents the furthest valid left index we can "cover" up to position i
  for (int i = 1; i <= n; i++) {
    L[i] = max(L[i], L[i - 1]);
  }

  for (int i = 0; i < q; i++) {
    int l, r;
    cin >> l >> r;
    // If l <= L[r], then the range [l,r] can be corrected by at most one swap of type 2,
    // meaning no need to reduce number of swaps compared to using only adjacent swaps.
    if (l <= L[r])
      cout << "NO\n";  // Not perfect
    else
      cout << "YES\n"; // Perfect
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