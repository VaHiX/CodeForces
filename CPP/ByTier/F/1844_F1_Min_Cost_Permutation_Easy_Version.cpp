// Problem: CF 1844 F1 - Min Cost Permutation (Easy Version)
// https://codeforces.com/contest/1844/problem/F1

/*
 * Problem: F1. Min Cost Permutation (Easy Version)
 * 
 * Purpose: 
 *   Given an array of integers and a constant c, find the lexicographically 
 *   smallest permutation of the array that minimizes the sum of absolute differences
 *   between consecutive elements minus c.
 * 
 * Algorithm:
 *   - Sort the array first.
 *   - If c >= 0, the best strategy is to place elements in ascending order 
 *     to minimize the sum of absolute differences.
 *   - If c < 0, we attempt to construct a permutation such that the differences 
 *     between consecutive elements are close to c. We split the sorted array into 
 *     segments where each segment respects the constraint between elements.
 *   - For each segment, a greedy approach is used to select elements to build the 
 *     permutation with minimal cost.
 * 
 * Time Complexity: O(n log n) due to sorting, with additional linear passes for 
 *   processing segments.
 * 
 * Space Complexity: O(n) for storing the arrays and auxiliary data structures.
 */
#include <stddef.h>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;
const ll INF = 1e17;
int a[500002];
int L[500002], R[500002], chk[500002];
int n, c;

// Function to process a segment from l to r and output the elements in 
// the correct order to minimize cost
void dothis(int l, int r) {
  if (l == r) {
    cout << a[l] << " ";
    return;
  }
  // Initialize left and right pointers for doubly linked list
  for (int i = l + 1; i < r; i++)
    L[i] = i - 1;
  for (int i = l + 1; i < r; i++)
    R[i] = i + 1;
  L[l + 1] = -1;
  R[r - 1] = r;
  // Initialize the check array to mark processed elements
  for (int i = l; i <= r; i++)
    chk[i] = 0;
  int now = a[l], cnt = 1;
  chk[l] = 1;
  cout << a[l] << " ";
  while (cnt < r - l) {
    // Iterate from right to left to find the appropriate next element
    for (int i = r - 1; i >= l + 1; i--) {
      if (a[i] - now >= c && chk[i] == 0 &&
          (L[i] == -1 || R[i] == -1 || a[R[i]] - a[L[i]] >= c)) {
        cnt++;
        chk[i] = 1;
        // Remove element from the linked list
        if (L[i] != -1)
          R[L[i]] = R[i];
        if (R[i] != -1)
          L[R[i]] = L[i];
        now = a[i];
        cout << a[i] << " ";
        break;
      }
    }
  }
  cout << a[r] << " ";
}

// Main solving function
void solve() {
  cin >> n >> c;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  // Sort the array in ascending order
  sort(a + 1, a + n + 1);
  // If c is non-negative, ascending order gives minimal cost
  if (c >= 0) {
    for (int i = 1; i <= n; i++) {
      cout << a[i] << " ";
    }
    cout << "\n";
    return;
  }
  // Reverse the array if c is negative
  reverse(a + 1, a + n + 1);
  int l = 1;
  for (int i = 2; i <= n; i++) {
    // If the difference is less than c, start a new segment
    if (a[i] - a[i - 1] < c) {
      dothis(l, i - 1);
      l = i;
    }
  }
  dothis(l, n);
  cout << "\n";
}

// Main driver
int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int T;
  cin >> T;
  while (T--)
    solve();
}


// https://github.com/VaHiX/CodeForces/