// Problem: CF 1107 F - Vasya and Endless Credits
// https://codeforces.com/contest/1107/problem/F

/*
F. Vasya and Endless Credits
Algorithm: Dynamic Programming with Sorting
Time Complexity: O(n^2)
Space Complexity: O(n)

The problem is about choosing the optimal sequence of credit offers to maximize the money available at some point in time.
Each offer gives an initial amount 'a', then costs 'b' per month for 'k' months.
We sort the offers by 'b' in descending order to try better offers first.
For each offer, we compute how much money we can have after taking it, considering all possible starting points.
We use DP where dp[i] represents the maximum money we can have at any point in time when ending a sequence with exactly i active credits.
*/

#include <algorithm>
#include <iostream>

using namespace std;
#define int long long
struct node {
  int a, b, k;
} o[501];
int dp[501];
signed main() {
  int n;
  cin >> n;
  for (int x = 1; x <= n; x++)
    cin >> o[x].a >> o[x].b >> o[x].k;
  sort(o + 1, o + n + 1, [](node x, node y) { return x.b > y.b; }); // Sort by b in descending order
  for (int x = 1; x <= n; x++)
    for (int y = n - 1; y >= 0; y--)
      dp[y + 1] = max(dp[y + 1], dp[y] + o[x].a - o[x].b * y), // Update dp[y+1] if taking this offer at time y
             dp[y] = max(dp[y], dp[y] + o[x].a - o[x].k * o[x].b); // Update dp[y] for continuing current sequence
  int ans = 0;
  for (int x = 0; x <= n; x++)
    ans = max(ans, dp[x]); // Find the maximum money at any point in time
  cout << ans << endl;
}


// https://github.com/VaHiX/codeForces/