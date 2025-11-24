// Problem: CF 1839 D - Ball Sorting
// https://codeforces.com/contest/1839/problem/D

/*
Purpose: This code solves the Ball Sorting problem where we need to sort balls of distinct colors into order 1 to n using at most k zero-color balls as placeholders and a cost of 1 coin per move operation.

Algorithm:
1. Preprocess: Compute 'pre' array to track decreasing sequences from right to left
2. Dynamic Programming: Use ite[i][k] to store maximum length of increasing subsequence ending at position i with k operations
3. Result Computation: For each k from 1 to n, calculate minimum coins needed for sorting

Time Complexity: O(n^3)
Space Complexity: O(n^2)

Approach:
- First, compute how many operations are 'free' based on precomputed decreasing sequences
- Then use dynamic programming to find maximum length of increasing subsequence for different numbers of operations
- Finally, for each k, determine the minimum number of coins (n - length) needed for k operations

*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
typedef long long int lli;
#define For(i, n) for (int i = 0; i < n; i++)
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;
    int a[n];
    For(i, n) cin >> a[i];
    int pre[n], flip = 0;
    pre[n - 1] = 0;
    // Precompute decreasing sequence from right to left
    for (int i = n - 2; i >= 0; i--) {
      if (a[i] > a[i + 1])
        flip = 1;
      pre[i] = flip;
    }
    // ite[i][k] = maximum length of increasing subsequence ending at i with k operations
    vector<vector<int>> ite(n + 1, vector<int>(n + 1, -1));
    ite[0][0] = 1;
    for (int i = 1; i < n; i++) {
      ite[i][1] = 1;
      For(k, i) {
        if (a[i] > a[k]) {
          For(l, k + 1) {
            if (ite[k][l] != -1) {
              // Update ite[i][l + (k == i-1 ? 0 : 1)] with maximum value
              ite[i][l + ((k == i - 1) ? 0 : 1)] =
                  max(ite[k][l] + 1, ite[i][l + ((k == i - 1) ? 0 : 1)]);
            }
          }
        }
      }
    }
    // ans[k] = minimum coins needed with k operations
    vector<int> ans(n + 1, n);
    For(i, n) {
      for (int k = 0; k <= i; k++) {
        if (ite[i][k] != -1) {
          // If we can maintain subsequence with k operations, update answer
          ans[k + pre[i]] = min(ans[k + pre[i]], n - ite[i][k]);
        }
      }
    }
    // Ensure minimum coins for all k from 1 to n
    For(i, n) ans[i + 1] = min(ans[i + 1], ans[i]);
    for (int k = 1; k <= n; k++)
      cout << ans[k] << ' ';
    cout << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/