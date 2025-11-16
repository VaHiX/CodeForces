// Problem: CF 1733 D2 - Zero-One (Hard Version)
// https://codeforces.com/contest/1733/problem/D2

/*
Algorithm: Dynamic Programming
Time Complexity: O(n^2) where n is the length of the string
Space Complexity: O(n) for the arrays f and t

This problem involves transforming string 'a' to string 'b' using specific operations.
The key insight is to find the positions where 'a' and 'b' differ, and then use dynamic programming to calculate the minimum cost.

Operations:
- Select two indices l and r (l < r)
- Change a[l] and a[r] (flipping their bits)
- If l+1 = r, cost is x
- Otherwise, cost is y

Approach:
1. Identify all positions where a[i] != b[i]
2. If there's an odd number of differences, return -1 (impossible)
3. If there are exactly 2 differences and they are consecutive, we can do it in min(2*y, x) cost
4. Otherwise, use DP where f[i] represents the minimum cost to fix first i differences
   - f[i] = min(f[i-2] + 2*(t[i]-t[i-1])*x, f[i-1] + y)
   - We can think of this as either:
     - fixing last two differences with a cost related to their separation (x cost per unit gap), or
     - fixing all but last difference with a fixed cost y
5. Result is (f[m] + 1) / 2 to account for double counting
*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>

#define int long long
#define N 5005
using namespace std;
int n, m, t[N], x, y, f[N], T;
string a, b;
signed main() {
  cin >> T;
  while (T--) {
    cin >> n >> x >> y >> a >> b;
    f[1] = y, m = 0;
    for (int i = 1; i <= n; i++)
      if (a[i - 1] != b[i - 1])
        t[++m] = i;
    if (m % 2) {
      puts("-1");
      continue;
    }
    if (m == 2 && t[1] + 1 == t[2]) {
      cout << min(2 * y, x) << endl;
      continue;
    }
    for (int i = 2; i <= m; i++)
      f[i] = min(f[i - 2] + 2 * (t[i] - t[i - 1]) * x, f[i - 1] + y);
    cout << (f[m] + 1) / 2 << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/