// Problem: CF 2151 C - Incremental Stay
// https://codeforces.com/contest/2151/problem/C

/*
C. Incremental Stay
Algorithm: Greedy with prefix/suffix optimization
Time Complexity: O(n) per test case
Space Complexity: O(n)

This problem involves determining the maximum total stay time for visitors entering/exiting a museum,
given that at most k people can be inside simultaneously. For each k from 1 to n, we compute the 
maximum possible sum of stay times.

The approach:
- The sensor records 2*n events (entries and exits) in chronological order.
- For k=1, we simply pair up consecutive events optimally to maximize total stay time.
- For larger k, we use a sliding window technique with prefix/suffix sums to efficiently 
  compute the result for all values of k from 1 to n.
  
The solution works by first calculating an initial value (tot), then iteratively updating it 
while considering how many people can be inside the museum at any given time (k).
It precomputes optimal pairing strategies and uses dynamic updates based on changing k.

*/

#include <iostream>

using namespace std;
#define int long long
int n, a[400005];

void solve() {
  cin >> n;
  for (int i = 1; i <= 2 * n; i++)
    cin >> a[i];
  int tot = 0, tot1 = 0;
  // Compute initial total stay time for k=1 (sum of differences between consecutive pairs)
  for (int i = 1; i <= 2 * n; i += 2)
    tot += a[i + 1] - a[i];
  // Iterate through all possible k values from 1 to n
  for (int i = 1; i <= n; i++) {
    cout << tot + tot1 << " "; // Output the current maximum total stay time
    // Update tot and tot1 based on the current k
    tot += a[i], tot -= a[2 * n - i + 1]; 
    tot1 -= a[i], tot1 += a[2 * n - i + 1];
    tot = -tot; // Negate tot to simulate changing conditions for next iteration
  }
  cout << "\n";
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T = 1;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/