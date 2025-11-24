// Problem: CF 1982 D - Beauty of the mountains
// https://codeforces.com/contest/1982/problem/D

/*
Purpose: 
This code determines whether it's possible to make the sum of heights of mountains with snowy caps equal to the sum of heights of mountains without snowy caps by performing k×k submatrix operations that add a constant value to all elements in the submatrix.

Approach:
1. For each test case, we read the mountain heights and their types (0 for snowy caps, 1 for no snowy caps).
2. We compute a prefix sum array 's' that helps determine the sum of a submatrix.
3. For each k×k submatrix, we calculate the sum of type indicators (1 for snowy, -1 for non-snowy).
4. We then compute the GCD of all these submatrix type sums.
5. If the total sum of the entire matrix is 0, or if the GCD is not zero and the total sum is divisible by the GCD, then we can balance the sums.

Time Complexity: O(n * m * (n/k) * (m/k)) = O(n * m * (n/k) * (m/k))
Space Complexity: O(n * m)

Algorithms/Techniques:
- Prefix Sum Technique
- GCD computation
- Submatrix operations

*/
#include <stdlib.h>
#include <iostream>

using namespace std;
const int MAXN = 505;
int T, n, m, k, a[MAXN][MAXN], s[MAXN][MAXN];
int gcd(int a, int b) { return (b ? gcd(b, a % b) : a); }
void Solve() {
  cin >> n >> m >> k;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
    }
  }
  long long sum = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      char u;
      cin >> u;
      int x = (u == '1' ? 1 : -1);  // 1 for no snow, -1 for snow
      sum += x * a[i][j],  // Accumulate total sum using type indicator
          s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + x;  // Build prefix sum
    }
  }
  int g = 0;
  for (int i = 0, x = k; x <= n; i++, x++) {
    for (int j = 0, y = k; y <= m; j++, y++) {
      int ss = s[x][y] - s[i][y] - s[x][j] + s[i][j];  // Calculate submatrix sum
      g = gcd(g, abs(ss));  // Update GCD of all submatrix type sums
    }
  }
  cout << (!sum || (g && sum % g == 0) ? "Yes\n" : "No\n");  // If sum is zero or divisible by GCD, return YES
}
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> T; T--;) {
    Solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/