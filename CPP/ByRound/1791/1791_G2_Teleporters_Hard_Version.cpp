// Problem: CF 1791 G2 - Teleporters (Hard Version)
// https://codeforces.com/contest/1791/problem/G2

/*
Algorithm/Techniques: Greedy with Priority Queues
Time Complexity: O(n log n) per test case due to priority queue operations.
Space Complexity: O(n) for storing the teleporter costs and auxiliary data structures.

This solution uses two priority queues:
- 'used' (max heap): tracks the cost of teleporters already used.
- 'now' (min heap): tracks potential teleporters we might use.

The idea is to try using each teleporter from right to left (i = n down to 1), 
and determine the maximum number of teleporters we can use with the coins available.
We consider whether it's better to use a teleporter now or defer it, 
and track the minimum cost to use teleporters so far.
*/

#include <stdio.h>
#include <algorithm>
#include <functional>
#include <queue>
#include <vector>

using namespace std;
typedef long long ll;
int num[200010];
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
      scanf("%d", &num[i]);
    int ans = 0, res = 0;
    priority_queue<int> used; // max heap for costs of used teleporters
    priority_queue<int, vector<int>, greater<int>> now; // min heap for costs of potential teleporters
    for (int i = n; i; i--)
      if (k >= num[i] + i) { // if we can afford the teleporter at position i
        int mid = k - num[i] - i; // remaining coins after teleporting from i
        // Optimize: if we have a better option (lower cost) in 'used' we can swap
        while (now.size() && used.size()) {
          int x = now.top(), y = used.top();
          if (y <= x)
            break;
          now.pop();
          used.pop();
          res -= y - x; // Adjust total cost
          now.push(y);
          used.push(x);
        }
        // Remove unused teleporters if they don't improve the current solution
        while (res > mid && used.size() + 1 > ans) {
          res -= used.top();
          now.push(used.top());
          used.pop();
        }
        // Use more teleporters if beneficial
        while (now.size() && now.top() + res <= mid)
          res += now.top(), used.push(now.top()), now.pop();
        ans = max(ans, (int)used.size() + 1); // Update maximum teleporters used
        now.push(num[i] + min(i, n - i + 1)); // Push the cost to use the teleporter at position i
      } else
        now.push(num[i] + min(i, n - i + 1)); // Add this teleporter to potential list
    printf("%d\n", ans);
  }
}


// https://github.com/VaHiX/CodeForces/