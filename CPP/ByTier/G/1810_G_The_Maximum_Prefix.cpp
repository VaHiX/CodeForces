// Problem: CF 1810 G - The Maximum Prefix
// https://codeforces.com/contest/1810/problem/G

/*
 * Problem: G. The Maximum Prefix
 * 
 * Algorithms/Techniques: Dynamic Programming, Probability, Modular Arithmetic
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(n^2)
 *
 * Description:
 * For each possible length k of the array (1 <= k <= n), we compute the expected score
 * of an array of that length. Each element of the array is 1 with probability p_i or -1 otherwise.
 * The score of an array is h_S where S is the maximum prefix sum.
 * We use dynamic programming to compute the expected score for all k.
 *
 * DP[i][j] represents the expected score when we have processed the first i elements and 
 * the current prefix sum is j (shifted to handle negative sums).
 * 
 * The recurrence relation involves:
 * DP[i][j] = p[i] * DP[i-1][j+1] + (1 - p[i]) * DP[i-1][max(0, j-1)]
 * This means the probability of choosing 1 (with value 1) and 1 (with value -1) and how they affect
 * the prefix sum.
 * 
 * Modular inverse is used to compute p[i] = x/y (mod MOD) as x * inverse(y) (mod MOD).
 * 
 * The result for each k is DP[k][0] which corresponds to the expected score of an array of length k.
 */
#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;
#define fi first
#define se second
#define rng(i, a, b) for (int i = int(a); i <= int(b); i++)
#define gnr(i, b, a) for (int i = int(b); i >= int(a); i--)
typedef long long ll;
using pii = pair<int, int>;
using ull = unsigned long long;
#define N 5005
#define INF 1000000007
#define MOD 1000000007
#define MAX_DIGIT 62
ll DP[N][N];
ll h[N];
ll p[N];

// Function to compute modular inverse using binary exponentiation
long long ari_inv(long long num) {
  long long res = 1, mult = num;
  for (int i = 0; i < MAX_DIGIT; i++) {
    if ((MOD - 2) & (1LL << i)) {
      res = (res * mult) % MOD;
    }
    mult = (mult * mult) % MOD;
  }
  return res;
}

__attribute__((optimize("Ofast,unroll-loops"), target("avx,avx2,fma"))) void
Solve() {
  int n;
  cin >> n;
  rng(i, 1, n) {
    ll x, y;
    cin >> x >> y;
    // Compute p[i] = x/y mod MOD using modular inverse
    p[i] = x * ari_inv(y) % MOD;
  }
  rng(i, 0, n) cin >> h[i];
  
  // Base case: for 0 elements, the expected score is h[j] where j is the maximum prefix sum
  rng(j, 0, n) DP[0][j] = h[j];
  
  // Dynamic programming: compute expected scores for arrays of length i
  rng(i, 1, n) {
    rng(j, 0, n - i) {
      // DP[i][j] = p[i] * DP[i-1][j+1] + (1 - p[i]) * DP[i-1][max(0, j-1)]
      // Probability of choosing 1 multiplied by expected value if sum increases by 1
      // Probability of choosing -1 multiplied by expected value if sum decreases by 1
      DP[i][j] =
          p[i] * DP[i - 1][j + 1] + (1 - p[i] + MOD) * DP[i - 1][max(0, j - 1)];
      DP[i][j] %= MOD;
    }
    // Output expected score for array length i
    cout << (DP[i][0] + MOD) % MOD << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  while (t--)
    Solve();
}


// https://github.com/VaHiX/CodeForces/