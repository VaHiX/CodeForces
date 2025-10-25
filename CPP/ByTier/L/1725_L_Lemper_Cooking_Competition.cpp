// Problem: CF 1725 L - Lemper Cooking Competition
// https://codeforces.com/contest/1725/problem/L

/*
 * Problem: L. Lemper Cooking Competition
 * Task: Find minimum number of operations to make all stove temperatures non-negative.
 * Algorithm: Binary indexed tree (Fenwick tree) + coordinate compression + prefix sum technique.
 *
 * Time Complexity: O(N * log N)
 * Space Complexity: O(N)
 *
 * Techniques:
 * - Coordinate compression to reduce the range of values
 * - Prefix sum to track cumulative changes
 * - Binary Indexed Tree (BIT) for efficient range updates and queries
 * - Simulation with careful handling of negative values
 */

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
const int N = 1e5 + 5;
int n, m, tree[N];
long long s[N], v[N], Max, ans;

// Update BIT: increment value at position 's' by 1
void update(int s) {
  for (; s <= m; s += s & -s)
    tree[s]++;
}

// Query BIT: get sum of elements from 1 to 's'
int getsum(int s) {
  int t = 0;
  for (; s; s -= s & -s)
    t += tree[s];
  return t;
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &s[i]), v[i] = s[i] += s[i - 1]; // Compute prefix sum and store in v
    if (s[i] < 0) // If prefix sum becomes negative, impossible to achieve non-negative all stages
      return puts("-1"), 0;
    Max = max(Max, s[i]); // Track maximum prefix sum
  }
  if (s[n] ^ Max) // Check if total sum equals max prefix sum -> valid configuration
    return puts("-1"), 0;
  sort(v + 1, v + n + 1), m = unique(v + 1, v + n + 1) - v - 1; // Coordinate compression
  for (int i = 1; i <= n; i++) {
    int p = m - (lower_bound(v + 1, v + m + 1, s[i]) - v); // Map prefix sum to compressed index
    ans += getsum(p), update(p + 1); // Query and update BIT for counting inversions-like process
  }
  cout << ans;
}


// https://github.com/VaHiX/codeForces/