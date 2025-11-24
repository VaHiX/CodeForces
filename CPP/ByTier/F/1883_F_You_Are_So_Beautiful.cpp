// Problem: CF 1883 F - You Are So Beautiful
// https://codeforces.com/contest/1883/problem/F

/*
 * Problem: F. You Are So Beautiful
 * 
 * Purpose: Count the number of subarrays such that the subsequence formed by
 *          that subarray occurs exactly once in the original array.
 *
 * Algorithm:
 * - Use coordinate compression to map values to indices.
 * - Compute suffix array `suf[i]` which counts how many unique elements
 *   exist from position `i` to `n`.
 * - For each unique element in the compressed array, add 1 to answer if
 *   it appears only once in the full array.
 * - Then, for each position, if the current element is the first time seen,
 *   add the count of unique elements from next position onward.
 * 
 * Time Complexity: O(n log n) per test case due to sorting and binary search.
 * Space Complexity: O(n) for storing auxiliary arrays.
 */

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
const int N = 200010;
int a[N];
int b[N];           // auxiliary array for coordinate compression
int uq[N];          // marks if a value is unique at position i
int cnt[N];         // counts occurrences of compressed values
int suf[N];         // suffix sum of unique elements
int n, m;

// Function to get compressed index of a value
int get_id(int x) { return int(lower_bound(b + 1, b + m + 1, x) - b); }

void solve() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    b[i] = a[i];       // Copy original values for sorting
    cnt[i] = 0;        // Reset counter
  }

  // Sort the values for coordinate compression
  sort(b + 1, b + n + 1);
  m = int(unique(b + 1, b + n + 1) - b - 1);  // Remove duplicates

  // Build suffix array from right to left
  suf[n + 1] = 0;
  for (int i = n; i >= 1; --i) {
    a[i] = get_id(a[i]);         // Map to compressed index
    cnt[a[i]] += 1;              // Increment count of this value
    uq[i] = cnt[a[i]] == 1;      // Mark if it's the first occurrence at this position
    suf[i] = uq[i] + suf[i + 1]; // Suffix sum of unique elements from i to n
  }

  long long ans = 0;
  // Add subarrays having a unique value that occurs exactly once in the entire array
  for (int i = 1; i <= m; ++i)
    if (cnt[i] == 1) {
      ans += 1;
    }

  // Reset cnt array for next phase
  for (int i = 1; i <= n; ++i)
    cnt[i] = 0;

  // Process unique elements in order of appearance
  for (int i = 1; i <= n; ++i) {
    if (cnt[a[i]])      // If already processed this value
      continue;
    cnt[a[i]] = 1;      // Mark it as processed
    if (i < n) {
      ans += suf[i + 1]; // Add number of unique elements to the right
    }
  }
  cout << ans << "\n";
}

int main() {
  int T = 1;
  scanf("%d", &T);
  while (T--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/