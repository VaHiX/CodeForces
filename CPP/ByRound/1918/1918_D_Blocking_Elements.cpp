// Problem: CF 1918 D - Blocking Elements
// https://codeforces.com/contest/1918/problem/D

/*
 * Problem: Blocking Elements
 * 
 * Purpose: Given an array of numbers, we need to block some elements such that the cost of the array is minimized.
 * The cost is defined as the maximum of:
 *   1. Sum of blocked elements
 *   2. Maximum sum among the segments formed when blocked elements are removed
 * 
 * Algorithm:
 *   - Binary search on the answer (cost)
 *   - For a given cost threshold, check if it's possible to block elements to achieve that cost
 *   - Use dynamic programming with deque to maintain optimal subproblem solutions efficiently
 * 
 * Time Complexity: O(n * log(max_sum)) where n is the size of the array and max_sum is up to 1e15
 * Space Complexity: O(n)
 * 
 * Techniques:
 *   - Binary search on answer
 *   - Convex hull trick with deque
 *   - Prefix sums
 */

#include <iostream>

using namespace std;
#define ll long long
#define all(v) begin(v), end(v)
#define ff first
#define ss second
const char nl = '\n';
const int inf = 1e9 + 9;
const long long INF = 1e18 + 18;
const int N = 100010;
int a[N];
long long dp[N]{}, p[N]{};
int q[N]{};
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int tt = 1;
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      p[i + 1] = p[i] + a[i]; // Compute prefix sums for subarray sums
    }
    a[n] = 1; // Set last element to 1 to handle edge cases
    long long lo = 0, hi = 100000000000000LL; // Binary search bounds
    while (lo < hi) {
      long long mid = lo + hi >> 1; // Midpoint of the search space
      long long sum = 0;
      int l = 0, r = 0;
      for (int i = 0; i <= n; i++) {
        // Remove indices from front of deque if the difference in prefix sums exceeds mid
        while (l <= r && p[i] - p[q[l]] > mid) {
          l++;
        }
        // dp[i + 1] = dp[q[l]] + a[i] is the recurrence relation
        dp[i + 1] = dp[q[l]] + a[i];
        // Remove indices from back of deque if current dp value is not better
        while (l <= r && dp[i + 1] <= dp[q[r]]) {
          r--;
        }
        q[++r] = i + 1; // Add current index to deque
      }
      // Check if the computed minimum cost is within the threshold
      if (dp[n + 1] - 1 <= mid) {
        hi = mid; // Try to find a smaller cost
      } else {
        lo = mid + 1; // Increase the cost threshold
      }
    }
    cout << lo << '\n'; // Output the minimum possible cost
  }
}


// https://github.com/VaHiX/CodeForces/