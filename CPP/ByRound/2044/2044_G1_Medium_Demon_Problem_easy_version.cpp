// Problem: CF 2044 G1 - Medium Demon Problem (easy version)
// https://codeforces.com/contest/2044/problem/G1

/*
 * Problem: Medium Demon Problem (easy version)
 *
 * Purpose: Simulate a process where spiders exchange plushies according to a fixed rule,
 *          and determine the first year when the system becomes stable.
 *
 * Algorithm:
 *   - Model the exchange as a directed graph where each spider points to its recipient.
 *   - Use BFS-like simulation to propagate the effect of plushie transfers over time.
 *   - Track how many plushies each spider has at each step and detect cycles/stability.
 *
 * Time Complexity: O(n) per test case (amortized due to each node visited at most once)
 * Space Complexity: O(n) for storing in-degree, array, and queue-like vector
 */

#include <algorithm>
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

constexpr int N = 2e5 + 7;
int T, n, a[N], in[N];

void solve() {
  cin >> n;
  memset(in + 1, 0, sizeof(int) * n);  // Reset in-degree array
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];  // Read the recipient of spider i's plushie
    in[a[i]]++;   // Increment in-degree of the recipient
  }

  vector<int> v;  // Vector to store spiders with zero in-degree (no incoming plushies)
  for (int i = 1; i <= n; ++i)
    if (!in[i])
      v.emplace_back(i);  // Add spiders which initially have no plushies

  int ans = 2, front = 0, rear = v.size();  // Initialize answer to 2 (as year 1 can't be stable), pointer and size
  while (front < rear) {                    // Process all current nodes with in-degree 0
    ++ans;                                  // Increment the year count
    while (front < rear) {
      if (--in[a[v[front]]] == 0)  // Decrease in-degree of the recipient, if it becomes zero, add to queue
        v.emplace_back(a[v[front]]);
      ++front;  // Move to next node in current level
    }
    rear = v.size();  // Update rear to size of new level
  }
  cout << ans << '\n';  // Output the year when system stabilizes
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/