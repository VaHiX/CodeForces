// Problem: CF 2115 C - Gellyfish and Eternal Violet
// https://codeforces.com/contest/2115/problem/C

/*
C. Gellyfish and Eternal Violet
Time Complexity: O(n * m^2) 
Space Complexity: O(n * m)

Algorithms/Techniques:
- Dynamic Programming (DP)
- Probability Calculation with transitions
- Optimization for attack decisions under different conditions
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <utility>

#define fi first
#define endl '\n'
#define il inline
#define se second
#define pb push_back
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif
const int N = 4e3 + 10;
int n, m, S, x, T;
double p, Q, f[N][N], g[N << 1];
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int mi = 1000; // minimum HP value among all monsters
    cin >> n >> m >> p, p *= 0.01, Q = 1 - p, S = 0; // convert p to probability and compute Q
    for (int i = 1; i <= n; i++)
      cin >> x, mi = min(mi, --x), S += x; // read HP, adjust by 1, find minimum, accumulate total
    if ((S -= x = mi * n) > m) { // subtracting total reduction needed from total hp to get excess
      cout << 0 << endl;
      continue;
    }
    f[0][0] = g[0] = 1, memset(g + 1, 0, x << 3); // initialize base case for DP and reset array g
    for (int i = 1, j; i <= m; i++)
      for (j = 1; j <= S && j <= i; j++)
        f[i][j] = p * f[i - 1][j] + Q * f[i - 1][j - 1]; // update transition probabilities
    double res = f[m][S] * (m - S >= mi); // calculate base result using f array
    for (int i = 1, j; i <= m - S; i++) {
      for (j = x; j >= 1; j--)
        g[j] = p * (j >= n ? g[j - n] : g[j]) + Q * max(g[j], g[j - 1]); // update g array for future rounds
      res += f[m - i][S] * g[max(mi - m + i + S, 0) * n]; // accumulate probability from current state
    }
    cout << fixed << setprecision(7) << res << endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/