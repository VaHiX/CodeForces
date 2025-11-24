// Problem: CF 2103 F - Maximize Nor
// https://codeforces.com/contest/2103/problem/F

/*
F. Maximize Nor
Algorithms/Techniques: Divide and Conquer with Bit Manipulation
Time Complexity: O(n * k * log n)
Space Complexity: O(n * k)

The problem asks to find for each index i in the array, the maximum bitwise nor
of all subarrays containing that index. Bitwise nor is computed cumulatively from 
left to right.

This solution uses a divide and conquer approach:
1. Split the array into two halves.
2. For each half, compute the maximum nor value that can be achieved by extending
   from the left boundary or to the right boundary of the current segment.
3. Recursively solve for both halves.
4. Combine results using bit manipulation techniques to determine the optimal subarrays.

Key functions:
- dfs: Recursive function implementing divide and conquer logic.
- lowbit macro: Used in bit manipulation operations.
- flag array: Tracks which bits have already been set during computation.
- use array: Marks elements that are used in current computation path.
- maxx array: Stores intermediate maximum nor values for each position.

The core insight is building up subarrays from left and right boundaries to compute
optimal bitwise nor scores efficiently within O(n * k * log n) time.
*/

#include <algorithm>
#include <iostream>

using namespace std;
#define lowbit(x) (x & -x)
#define endl '\n'
const int Maxn = 17;
const int maxn = 1e5 + 10;
int t, n, k;
int a[maxn];
int ans[maxn];
bool flag[maxn], use[maxn];
int maxx[maxn];

void dfs(int l, int r) {
  if (l == r) {
    ans[l] = max(ans[l], a[l]); // Base case: single element subarray
    return;
  }
  int mid = l + r >> 1; // Midpoint of the current segment

  // Precompute left-to-right scan from mid to l, determine what bits are set
  for (int i = mid; i >= l; i--) {
    bool fflag = false;
    for (int j = 0; j < k; j++) {
      if ((a[i] >> j & 1) && !flag[j]) {
        flag[j] = true;
        fflag = true;
      }
    }
    if (i == mid || fflag) { // If there is a new bit set or its the midpoint
      use[i] = true;
    }
  }

  // Compute maximum nor values for current segment using precomputed data
  for (int i = mid; i >= l; i--) {
    if (!use[i] && !use[i + 1] && !use[i + 2]) { // Check if three consecutive elements not used
      maxx[i] = maxx[i + 2];
    } else {
      int p = a[i];
      for (int j = i + 1; j <= r; j++) {
        p = ((1 << k) - 1) ^ (p | a[j]); // Bitwise nor operation
        if (j > mid) {
          maxx[i] = max(maxx[i], p);
          maxx[j] = max(maxx[j], p);
        }
      }
    }
  }

  // Propagate maximum values to the right and left across current segment
  for (int i = r - 1; i > mid; i--) {
    maxx[i] = max(maxx[i], maxx[i + 1]);
  }
  for (int i = l + 1; i <= mid; i++) {
    maxx[i] = max(maxx[i], maxx[i - 1]);
  }

  // Update global answer and reset working arrays
  for (int i = l; i <= r; i++) {
    ans[i] = max(ans[i], maxx[i]);
    use[i] = false;
    maxx[i] = 0;
  }
  for (int i = 0; i < k; i++) {
    flag[i] = false;
  }

  dfs(l, mid);      // Process left half
  dfs(mid + 1, r);  // Process right half
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      ans[i] = 0;
    }
    dfs(1, n);
    for (int i = 1; i <= n; i++) {
      cout << ans[i] << " \n"[i == n]; // Output result with proper formatting
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/