// Problem: CF 1801 F - Another n-dimensional chocolate bar
// https://codeforces.com/contest/1801/problem/F

/*
 * Problem: F. Another n-dimensional chocolate bar
 * 
 * Purpose:
 *   This code finds the maximum possible volume of the smallest piece when
 *   cutting an n-dimensional chocolate bar into at least k pieces, such that
 *   each cut is made along hyperplanes dividing the bar into equal parts.
 *   
 *   The approach involves:
 *   1. Enumerating all possible ways to divide each dimension (b1, b2, ..., bn),
 *      such that the total number of pieces is at least k.
 *   2. For each set of divisions, we calculate the volume of the smallest piece
 *      and then multiply it by k.
 *   3. To optimize, we use a technique based on divisor enumeration and dynamic
 *      programming over the dimensions.
 *   
 * Algorithms/Techniques:
 *   - Divisor enumeration using number-theoretic ideas to find unique values of
 *     k / l for l from 1 to k.
 *   - Dynamic Programming on dimension using precomputed divisors and their
 *     relationship.
 *   - Floating-point math for precision in results.
 *   
 * Time Complexity:
 *   O(k * d(k) * n), where d(k) is the number of distinct divisors of k.
 *   In worst case, d(k) is about sqrt(k), so approximately O(k * sqrt(k) * n).
 *   
 * Space Complexity:
 *   O(k * n) for the dp array and auxiliary arrays.
 */

#include <stdio.h>
#include <algorithm>
#include <vector>

#define ll int
#define ls p << 1
#define rs p << 1 | 1
#define Ma 10000005
#define mod 1000000007
#define PLL pair<ll, ll>
#define PDD pair<double, double>
#define IOS                                                                    \
  ios::sync_with_stdio(false);                                                 \
  cin.tie(0);                                                                  \
  cout.tie(0);
#define fi first
#define se second
#define N 105
#define Na 100005
#define pb push_back
#define ld long double
#define all(x) x.begin(), x.end()
using namespace std;
ll n, k;
ll id[Ma];        // Maps divisor values to their indices
ll ok[Na];        // Stores unique quotient values (k / l)
double dp[N][Na]; // DP table: dp[i][j] = max value achievable using first i dimensions with divisor j
ll a[Ma];         // Input array for number of slices per dimension
struct node {
  ll l, id;
};
vector<node> v[Na]; // Precomputed transitions between divisors

void sol() {
  scanf("%d%d", &n, &k);
  k--; // Adjust k to 0-indexed for easier logic
  for (ll i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  
  ll num = 0; // Number of unique divisor quotients
  // Enumerate k / l and store unique values
  for (ll l = 1, r; l <= k; l = r + 1) {
    ll w = k / l;
    r = k / w;
    ok[++num] = w + 1;
    id[w + 1] = num;
  }
  ok[++num] = 1, id[1] = num;
  
  // Initialize the DP table
  dp[0][1] = k + 1;
  
  // Preprocessing: For each divisor group, build connections
  for (ll i = 1; i <= num; i++) {
    ll g = ok[i] - 1;
    for (ll l = 1, r; l <= g; l = r + 1) {
      ll w = g / l;
      r = g / w;
      v[i].pb({l, id[w + 1]});
    }
    v[i].pb({ok[i], num});
  }
  
  // Dynamic Programming step
  for (ll i = 0; i < n; i++) {
    for (ll j = 1; j <= num; j++) {
      double w = dp[i][j];
      if (w == 0) continue;
      // For each possible transition, update the DP table
      for (auto z : v[j]) {
        dp[i + 1][z.id] = max(dp[i + 1][z.id], w * (a[i + 1] / z.l) / a[i + 1]);
      }
    }
  }
  
  // Output the maximum value achieved after all dimensions
  printf("%.10lf\n", dp[n][num]);
  return;
}

int main() {
  sol();
  return 0;
}


// https://github.com/VaHiX/CodeForces/