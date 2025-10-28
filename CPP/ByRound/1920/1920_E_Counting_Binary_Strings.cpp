// Problem: CF 1920 E - Counting Binary Strings
// https://codeforces.com/contest/1920/problem/E

/*
 * Problem: Counting Binary Strings
 * 
 * Algorithm:
 * - Dynamic Programming approach to count valid binary strings.
 * - State definition: dp[i][j] represents the number of ways to form exactly i good substrings 
 *   with the last good substring having length j.
 * - The transition is based on how we can extend the string by appending 0s or 1s such that we 
 *   maintain the constraint that no good substring exceeds length k.
 * 
 * Time Complexity: O(n * k * n) where n is the number of good substrings and k is the max length,
 *                  which simplifies to O(n^2 * k) in worst case.
 * Space Complexity: O(n^2) due to the 2D DP table.
 */

#include <stddef.h>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vll;
typedef vector<pll> vpll;
#define PB push_back
#define PF push_front
#define PPB pop_back
#define PPF pop_front
#define X first
#define Y second
#define MP make_pair
#define all(x) (x).begin(), (x).end()
const int mod = 998244353;
const int inf = 1e9 + 7;
const ll INF = 1e18 + 7;
const int logo = 20;
const int MAXN = 2507;
const int off = 1 << logo;
const int trsz = off << 1;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, -1, 1};

void ad(int &a, int b) {
  a += b;
  if (a >= mod)
    a -= mod;
}

int dp[MAXN][MAXN];

void solve() {
  int n, k;
  cin >> n >> k;
  
  // Initialize base case: dp[0][j] = 1 for all j, meaning zero good substrings
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++)
      dp[i][j] = (i == 0);
  }

  int ans = 0;
  
  // Iterate over all possible lengths of the string s (from 1 to n)
  for (int s = 1; s <= n; s++) {
    // Iterate over all possible lengths of the last good substring (from 1 to k)
    for (int cr = 1; cr <= k; cr++) {
      // Iterate over all possible lengths of previous segments to form current segment
      for (int ls = 1; ls + cr - 1 <= k and ls * cr <= s; ls++) {
        // Add transitions: dp[s][cr] += dp[s - ls * cr][ls]
        ad(dp[s][cr], dp[s - ls * cr][ls]);
      }
      // If we've reached the total number of required goods substrings, add to answer
      if (s == n)
        ad(ans, dp[s][cr]);
    }
  }
  
  cout << ans << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int tt = 1;
  cin >> tt;
  while (tt--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/