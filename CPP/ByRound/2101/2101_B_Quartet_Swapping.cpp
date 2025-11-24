// Problem: CF 2101 B - Quartet Swapping
// https://codeforces.com/contest/2101/problem/B

/*
B. Quartet Swapping
Algorithms/Techniques: Greedy with Priority Queue
Time Complexity: O(n log n) per test case
Space Complexity: O(n)

The problem allows swapping pairs of elements at indices (i, i+2) and (i+1, i+3) simultaneously.
This means we can rearrange elements independently in even and odd indexed groups.
We use a greedy approach:
- For each position from 1 to n-3, we greedily place the smallest available element
  that belongs in that position by using a priority queue to track minimums in even/odd positions.
- A swap operation effectively moves items within a 4-element window in a specific pattern.

The key idea is:
1. Separate elements into two groups: even indices and odd indices.
2. Use priority queues to quickly retrieve the smallest element from each group.
3. Process each index from left to right, and whenever we need to move an element,
   perform necessary swaps to bring it to the correct spot, leveraging 
   the allowed swapping pattern.

This allows for optimal lexicographical sorting with minimal number of operations.
*/

#include <stddef.h>
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
const int maxn = 2e5 + 10;
int a[maxn], wz[maxn];

void go(int x, int y) {
  swap(a[x], a[y]);           // Swap elements at positions x and y
  wz[a[x]] = x, wz[a[y]] = y; // Update their positions in wz array
}

priority_queue<int, vector<int>, greater<int>> q[2]; // Two queues: one for even indices, one for odd indices

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < 2; i++)   // Clear priority queues
    while (!q[i].empty())
      q[i].pop();
  for (int i = 1; i <= n; i++)
    cin >> a[i], wz[a[i]] = i; // Read array and store positions

  for (int i = 1; i <= n; i++)
    q[i % 2].push(a[i]);       // Assign elements to even/odd priority queues based on index parity

  for (int i = 1; i <= n - 3; i++) {   // Process up to n-3 positions
    int w = q[i % 2].top();            // Get the smallest value in the correct parity group
    q[i % 2].pop();
    int pos = wz[w];                   // Find current position of that element
    if (pos == n)                      // If at last index, do special handling for boundary
      go(pos - 2, pos), go(pos - 3, pos - 1), pos -= 2;
    go(i, pos), go(i + 1, pos + 1);    // Perform required swaps to bring element to correct place
  }

  for (int i = 1; i <= n; i++)
    cout << a[i] << " ";               // Output result
  cout << "\n";
}

signed main() {
  ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(0);
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/