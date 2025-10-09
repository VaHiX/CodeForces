// Problem: CF 2045 I - Microwavable Subsequence
// https://codeforces.com/contest/2045/problem/I

/*
 * Problem: Microwavable Subsequence
 * Task: Compute sum of f(x,y) for all 1 <= x < y <= M where f(x,y) is the length
 *       of the longest microwavable subsequence consisting only of elements x and y.
 *
 * Algorithms/Techniques:
 * - Binary Indexed Tree (Fenwick Tree) for efficient range updates and queries
 * - Two-pass processing: right-to-left to build contributions, then final pass
 *   for remaining elements
 *
 * Time Complexity: O(N log N + M^2)
 * Space Complexity: O(N + M)
 */

#include <algorithm>
#include <iostream>

using namespace std;
#define MAX 1010101
typedef long long ll;

int A[MAX];       // Input array of integers
int pv[MAX];      // Last seen position of each value (1 to M)
int tree[MAX];    // Binary Indexed Tree for range queries/updates
int N, M;         // Size of array and maximum element

// Update BIT at index i by adding x
void upd(int i, int x) {
  while (i <= N) {
    tree[i] += x, i += i & -i;  // Propagate update using lowbit
  }
}

// Get prefix sum up to index i
int get(int i) {
  i = min(i, N);  // Clamp to valid range
  int ans = 0;
  while (i) {
    ans += tree[i], i -= i & -i;  // Traverse using lowbit
  }
  return ans;
}

signed main() {
  ios::sync_with_stdio(false), cin.tie(0);
  cin >> N >> M;

  int i;
  for (i = 1; i <= N; i++)
    cin >> A[i];  // Read input array

  // Initialize last seen positions to a value beyond array bounds
  for (i = 1; i <= M; i++)
    pv[i] = N + 1;

  ll sum = 0;

  // Process array from right to left
  for (i = N; i >= 1; i--) {
    if (pv[A[i]] <= N)
      upd(pv[A[i]], -1);  // Remove previous occurrence if exists

    upd(i, 1), pv[A[i]] = i;  // Add current position in BIT and update last seen

    if (i == 1) break;  // Don't process further for i=1

    int a = A[i - 1];     // Previous element
    int r = pv[a];        // Last occurrence of previous element

    sum += get(r - 1);   // Query how many valid ones exist before r
  }

  // Add contribution from each value's final position in BIT
  for (i = 1; i <= M; i++)
    sum += get(pv[i] - 1);

  cout << sum;
}


// https://github.com/VaHiX/codeForces/