// Problem: CF 1468 A - LaIS
// https://codeforces.com/contest/1468/problem/A

/*
Algorithm: Largest Almost Increasing Subsequence (LaIS) using Coordinate Compression and Segment Tree
Techniques: Coordinate compression, Fenwick Tree (Binary Indexed Tree), Monotonic stack
Time Complexity: O(n log n) per test case
Space Complexity: O(n)

This solution uses a dynamic programming approach with coordinate compression and a Fenwick Tree 
to efficiently query and update the maximum length of almost increasing subsequences ending at each value.
The algorithm employs a monotonic stack to maintain elements in decreasing order while updating the segment tree.
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
const int N = 500010;
int tree[N], q[N], n, a[N], dp[N], ans; // tree: Fenwick Tree, q: monotonic stack, dp: DP array
long long k;

// Add value k to position x in the Fenwick Tree
void add(int x, int k) {
  while (x <= n) {
    tree[x] = max(tree[x], k); // Update with maximum value
    x += x & -x; // Move to parent node
  }
}

// Find maximum value from position 1 to x in the Fenwick Tree
int find(int x) {
  int ans = 0;
  while (x > 0) {
    ans = max(ans, tree[x]); // Accumulate maximum value
    x -= x & -x; // Move to parent node
  }
  return ans;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t) {
    t--;
    scanf("%d", &n);
    ans = 1; // Minimum length is 1
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
      tree[i + 1] = 0; // Initialize BIT
    }
    int r = 0; // Stack pointer
    for (int i = 0; i < n; i++) {
      dp[i] = min(i + 1, 2); // Base case: at most 2 elements form an almost increasing subsequence
      dp[i] = max(find(a[i]) + 1, dp[i]); // Query maximum previous length and extend
      ans = max(ans, dp[i]); // Keep track of global maximum

      // Maintain monotonic stack property
      while (r > 0 && a[q[r - 1]] <= a[i]) {
        add(a[q[r - 1]], dp[q[r - 1]] + 1); // Update BIT with current element & its DP value
        r--; // Pop from stack
      }
      q[r++] = i; // Push current index to stack
      add(a[i], dp[i]); // Add current element's DP value to BIT
    }
    printf("%d\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/