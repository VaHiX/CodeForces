// Problem: CF 2116 E - Gellyfish and Eternal Violet
// https://codeforces.com/contest/2116/problem/E

/*
E. Gellyfish and Eternal Violet
Algorithms/Techniques:
- Dynamic Programming with probability calculation
- State management for attack choices under uncertain conditions
- Prefix sum optimization for probability transitions
Time Complexity: O(n * m^2)
Space Complexity: O(n * m)

This problem involves calculating the probability that Gellyfish can reduce all monster HPs to 1
after exactly m rounds of attacks, where each round has a probability p that her sword shines.
If the sword shines during an attack, she must reduce all monsters by 1; otherwise, she can choose one monster.
The solution uses two DP arrays:
- f[i][j]: probability that at round i, with j total HP lost, reaching the goal
- g[i][j]: probability that at round i, with j "non-shine" events, we're still alive

We compute probabilities via dynamic programming and use careful state transitions to handle
the optimal decision-making process in each step.
*/

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using namespace __gnu_pbds;
#define _                                                                      \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(0);
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define f first
#define s second
#define pb push_back
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
template <class T>
using Tree =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;
double f[4005][8005], g[4005][4005];
int n, m;
double p;
int a[405];
void solve() {
  cin >> n >> m >> p;
  p /= 100;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    a[i]--;
  }
  sort(a + 1, a + n + 1);
  int k = 0;
  for (int i = 1; i <= n; i++)
    k += a[i] - a[1];
  // Reset f
  for (int i = 0; i <= m; i++)
    for (int j = 0; j <= a[1] * n; j++)
      f[i][j] = 0;
  f[0][0] = 1;
  // Build up f: probability of achieving goal with given HP loss over time
  for (int i = 1; i <= m; i++) {
    f[i][0] = 1; // Base case: no HP lost means we're always in good state initially
    for (int j = 1; j <= a[1] * n; j++) {
      // If sword shines, attack all monsters but still can lose one more point
      f[i][j] = (1 - p) * max(f[i - 1][j], f[i - 1][j - 1]);
      if (j >= n)
        f[i][j] += p * max(f[i - 1][j], f[i - 1][j - n]); // Attack all
      else
        f[i][j] += p * f[i - 1][j]; // No enough to hit everyone, just one monster
    }
  }

  // Reset g
  for (int i = 0; i <= m; i++)
    for (int j = 0; j <= k; j++)
      g[i][j] = 0;
  g[0][0] = 1;
  // Build up g: probability of having exactly j non-shine events during m rounds
  for (int i = 1; i <= m; i++)
    for (int j = 0; j <= k; j++) {
      if (!j)
        g[i][j] = p * g[i - 1][j]; // Still no shines
      else
        g[i][j] = p * g[i - 1][j] + (1 - p) * g[i - 1][j - 1]; // Either shine or not
    }

  double ans = 0;
  for (int i = k; i <= m; i++) {
    double q = 0;
    if (!i)
      q = 1;
    else {
      if (!k)
        q = 0;
      else
        q = g[i - 1][k - 1] * (1 - p); // Transition from last step with k-1 non-shines
    }
    ans += q * f[m - i][max(a[1] - (i - k), 0) * n]; // Final state probability
  }
  cout << fixed << setprecision(10) << ans << "\n";
}
int main() {
  _ ll t;
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/codeForces/