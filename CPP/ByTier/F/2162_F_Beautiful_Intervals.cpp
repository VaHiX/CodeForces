// Problem: CF 2162 F - Beautiful Intervals
// https://codeforces.com/contest/2162/problem/F

/*
Purpose: This code solves the problem of constructing a permutation of integers from 0 to n-1 such that the MEX (minimum excluded value) of all mex values computed over given intervals is minimized.

Algorithm:
- The solution attempts to construct a permutation that minimizes the MEX of the set of MEX values from all intervals.
- It uses a greedy approach to determine the best positions for elements 0, 1 to minimize the MEX.
- Special cases are handled for edge configurations like when an interval covers the full range [1,n].

Time Complexity: O(m log m + n^2) where m is the number of intervals and n is the size of permutation.
Space Complexity: O(n + m) for storing intervals and auxiliary arrays.

Techniques:
- Sorting and unique operations on intervals.
- Prefix sum technique to track interval coverage.
- Greedy placement of elements based on interval overlaps.
*/

#include <stdio.h>
#include <algorithm>
#include <utility>

const int maxn = 3e3 + 5;
using namespace std;
int T, n, m, cnt[maxn], ans[maxn], k;
pair<int, int> a[maxn];

// Function to build a permutation with specific elements at positions x and y
void build(int x, int y) {
  ans[x] = 0;
  ans[y] = 1;
  int tot = 2;
  for (int i = 1; i <= n; i++)
    if (i != x && i != y)
      ans[i] = tot++;
}

// Main solving logic
void solve() {
  // Initialize permutation as identity
  for (int i = 1; i <= n; i++)
    ans[i] = i - 1;
  
  // Try to find a position that is covered by all intervals
  for (int i = 1; i <= n; i++) {
    if (cnt[i] == k) {
      swap(ans[1], ans[i]);
      return;
    }
  }
  
  // Try to find a position not covered by any interval
  for (int i = 1; i <= n; i++) {
    if (!cnt[i]) {
      swap(ans[1], ans[i]);
      return;
    }
  }
  
  // Try to find two adjacent positions that are not covered by any interval
  for (int i = 1; i < n; i++) {
    int flag = 1;
    for (int j = 1; j <= k; j++) {
      if (i < a[j].first || a[j].second < i)
        continue;
      if (i + 1 < a[j].first || a[j].second < i + 1)
        flag = 0;
    }
    if (flag) {
      build(i, i + 1);
      return;
    }
  }
  
  // Try reverse adjacent check
  for (int i = 2; i <= n; i++) {
    int flag = 1;
    for (int j = 1; j <= k; j++) {
      if (i < a[j].first || a[j].second < i)
        continue;
      if (i - 1 < a[j].first || a[j].second < i - 1)
        flag = 0;
    }
    if (flag) {
      build(i, i - 1);
      return;
    }
  }
  
  // Fallback case where none of above conditions are met
  ans[1] = 0;
  ans[2] = 2;
  ans[3] = 1;
  for (int i = 4; i <= n; i++)
    ans[i] = i - 1;
}

int main() {
  scanf("%d", &T);
  for (; T; T--) {
    scanf("%d %d", &n, &m);
    k = 0;
    for (int i = 1; i <= n; i++)
      cnt[i] = 0;
    
    // Read intervals, skip full range [1,n] intervals
    for (int i = 1, l, r; i <= m; i++) {
      scanf("%d %d", &l, &r);
      if (l == 1 && r == n)
        continue;
      a[++k] = {l, r};
    }
    
    // Sort and remove duplicates
    sort(a + 1, a + k + 1);
    k = unique(a + 1, a + k + 1) - a - 1;
    
    // Compute prefix sum of interval coverage
    for (int i = 1; i <= k; i++)
      cnt[a[i].first]++, cnt[a[i].second + 1]--;
    for (int i = 1; i <= n; i++)
      cnt[i] += cnt[i - 1];
    
    solve();
    for (int i = 1; i <= n; i++)
      printf("%d ", ans[i]);
    puts("");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/