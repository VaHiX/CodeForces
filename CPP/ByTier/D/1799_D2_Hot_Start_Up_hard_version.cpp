// Problem: CF 1799 D2 - Hot Start Up (hard version)
// https://codeforces.com/contest/1799/problem/D2

/*
Algorithm/Techniques: Dynamic Programming with Preprocessing
Time Complexity: O(n + k) per test case, where n is the length of the program sequence and k is the number of programs
Space Complexity: O(n + k) for storing arrays f, s, pre, lst, and input arrays

This solution uses dynamic programming to find the minimum time required to run all programs in the given order. 
The key idea is to keep track of the last time each program was executed and use that to determine whether 
to use the cold or hot start time for each program. The DP state f[i] represents the minimum time to run the first i programs.

The preprocessing step calculates cumulative sums of costs (either cold or hot) and tracks the last occurrence of each program.
During DP computation, for each program, we check if it can benefit from a hot start (when it's repeated consecutively) 
and update the minimum time accordingly.
*/

#include <algorithm>
#include <iostream>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using db = double;
using ldb = long double;
const int N = 3e5 + 10;
const ll inf = (1ll << 60);
int t, n, k, a[N], c[N], h[N], lst[N], pre[N];
ll s[N], f[N];

// Function to calculate the sum of costs from index l to r
inline ll getdis(int l, int r) {
  if (l > r)
    return 0;
  return s[r] - s[l - 1];
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> t;
  while (t--) {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
      cin >> a[i];
    for (int i = 1; i <= k; ++i)
      cin >> c[i];
    for (int i = 1; i <= k; ++i)
      cin >> h[i];
    
    // Preprocessing step to compute cumulative costs and last occurrence markers
    for (int i = 1; i <= n; ++i) {
      if (a[i] == a[i - 1])
        s[i] = s[i - 1] + h[a[i]], pre[i] = pre[i - 1];  // Use hot start if same as previous program
      else
        s[i] = s[i - 1] + c[a[i]], pre[i] = i - 1;       // Use cold start otherwise
    }
    
    // Reset last occurrence array for each test case
    for (int i = 1; i <= k; ++i)
      lst[i] = 0;
    
    // Dynamic Programming step
    for (int i = 1; i <= n; ++i) {
      f[i] = inf;  // Initialize with infinity
      // Check for hot start from previous occurrence if valid
      if (lst[a[i]] && lst[a[i]] + 1 < i)
        f[i] = f[lst[a[i]] + 1] + getdis(lst[a[i]] + 2, i - 1) + h[a[i]];
      
      // Consider starting the current program (either with cold or hot start)
      f[i] = min(f[i - 1] + (a[i - 1] == a[i] ? h[a[i]] : c[a[i]]), f[i]);
      lst[a[i]] = i;  // Update last occurrence of program a[i]
    }
    
    cout << f[n] << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/