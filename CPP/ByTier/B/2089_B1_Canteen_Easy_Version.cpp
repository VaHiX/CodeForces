// Problem: CF 2089 B1 - Canteen (Easy Version)
// https://codeforces.com/contest/2089/problem/B1

/*
B1. Canteen (Easy Version)
Algorithm: Monotonic Stack + Prefix Sum
Time Complexity: O(n) per test case
Space Complexity: O(n)

This problem involves simulating a process where two sequences 'a' and 'b' undergo rounds of operations.
Each round:
1. For each element, reduce both a[i] and b[i] by min(a[i], b[i]).
2. Shift elements in 'a' to the right (c[i] = a[(i-1) % n]).
3. Assign c back to 'a'.
We are to find the minimum number of rounds until all elements in 'a' become 0.

Since k=0, we do not change any value in 'a'. The problem simplifies to simulating this process and counting rounds.
We use a monotonic stack to efficiently compute how far right (in prefix sum terms) each element can "extend"
before a smaller prefix sum is encountered. This allows us to determine the optimal round count.

The key idea:
- Transform the difference array d[i] = a[i] - b[i].
- Compute prefix sums.
- Use monotonic stack to compute maximum distance between indices such that prefix sum decreases, which is crucial for determining rounds needed.
*/

#include <algorithm>
#include <iostream>
#include <stack>
#define int long long
#define endl '\n'
using namespace std;
int ar[400005];
stack<int> s;
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n, x, ans = 0, m;
    cin >> n >> m; // m not used in this version, but kept for interface consistency
    for (int i = 1; i <= n; i++)
      cin >> ar[i];            // Read array a
    for (int j = 1; j <= n; j++)
      cin >> x, ar[j] -= x;    // Subtract b[j] from a[j], storing difference in ar[j]
    for (int i = 1; i <= n; i++)
      ar[i + n] = ar[i];       // Duplicate the array to handle circularity
    for (int i = 1; i <= 2 * n; i++)
      ar[i] += ar[i - 1];      // Compute prefix sums
    for (int i = n * 2; i >= 1; i--) {
      while (!s.empty() && ar[s.top()] > ar[i]) // Maintain a decreasing stack
        s.pop();
      if (!s.empty() && i <= n)                 // If current index is within original array
        ans = max(s.top() - i, ans);            // Update answer with difference between indices
      s.push(i);                                // Push current index to stack
    }
    cout << ans << endl;
    while (!s.empty())                          // Clear the stack for next test case
      s.pop();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/