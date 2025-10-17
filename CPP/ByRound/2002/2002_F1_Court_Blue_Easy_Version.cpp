// Problem: CF 2002 F1 - Court Blue (Easy Version)
// https://codeforces.com/contest/2002/problem/F1

/*
 * Problem: F1. Court Blue (Easy Version)
 * Algorithm/Techniques: Sieve of Eratosthenes, DFS with pruning, GCD checking,
 *                       Optimization using precomputed primes and symmetry.
 *
 * Time Complexity: O(n log log n + n^2) where n = max(n, m). Preprocessing sieve takes O(n log log n),
 *                  DFS explores at most O(n^2) states in worst case.
 * Space Complexity: O(n + n^2) for sieve array and visited state tracking.
 *
 * This solution uses a sieve to precompute primes up to 2e7, then performs a depth-first search
 * (DFS) to explore all valid paths of win counts that maintain gcd(W_L, W_F) <= 1. 
 * It avoids redundant states with a visited array and exploits symmetry by considering only 
 * (x,y) such that gcd(x,y) == 1 and ensuring x <= n, y <= m.
 */

#include <algorithm>
#include <stdio.h>
#include <utility>
#include <vector>
using namespace std;
typedef long long ll;

const int MAXN = 2e7 + 10; // Maximum size for sieve
const int MAXM = 2e3 + 10; // Safe limit based on problem constraints
int pr[MAXN], tot;         // Prime list and count
bool v[MAXN];              // Visited array for sieve

// Initialize sieve of Eratosthenes up to n
inline void init(int n) {
  v[0] = v[1] = 1;        // Mark 0 and 1 as not prime
  for (int i = 2; i <= n; i++) {
    if (!v[i])
      pr[++tot] = i;       // Add prime to list
    for (int j = 1; j <= tot && i * pr[j] <= n; j++) {
      v[i * pr[j]] = 1;    // Mark multiples as not prime
      if (i % pr[j] == 0)
        break;             // Optimization: avoid redundant checks
    }
  }
}

int n, m, p, q;             // Parameters for current test case

// Function to compute score based on wins x and y with p, q
inline ll f(int x, int y) {
  ll res = (ll)x * p + (ll)y * q;
  if (y <= n)
    res = max(res, (ll)x * q + (ll)y * p); // Alternative scoring order if applicable
  return res;
}

bool vis[MAXM][MAXM], res;   // Visited state for DFS and result flag
ll ans;                      // Maximum score found so far
vector<pair<int, int>> tmp;  // Temporary storage for visited states

// Depth-first search to explore path with gcd(x,y) = 1
void dfs(int x, int y) {
  if (__gcd(x, y) > 1)
    return;                 // Skip invalid paths (not coprime)

  ans = max(ans, f(x, y));  // Update maximum score
  vis[n - x][m - y] = 1, tmp.emplace_back(x, y); // Mark visited and store state

  if (x < n && !vis[n - x - 1][m - y])     // Move right (increase Lelle's wins)
    dfs(x + 1, y);
  if (res) return;

  if (y == m) return res = 1, void();       // Reached end condition

  if (y < m && !vis[n - x][m - y - 1])     // Move down (increase Flamm's wins)
    dfs(x, y + 1);
  if (res) return;
}

int T, x, y;

int main() {
  for (init(2e7), scanf("%d", &T); T--;) {   // Initialize sieve
    scanf("%d%d%d%d", &n, &m, &p, &q);      // Read input values

    ans = res = 0;                          // Reset global variables

    // Find smallest y >= m such that v[y] == 0 (i.e., y is prime)
    for (y = m; v[y]; y--)
      ;

    // Search from x = min(n, y-1) down to 1
    for (x = min(n, y - 1); !res; x--) {
      ans = max(ans, f(x, y));            // Compute initial score

      if (y < m)                         // Start DFS if not at last row
        dfs(x, y + 1);
      else break;                        // Break when reached last row
    }

    // Clear visited memoization table
    for (auto [i, j] : tmp)
      vis[n - i][m - j] = 0;
    tmp.clear();

    printf("%lld\n", ans);               // Output result
  }
}


// https://github.com/VaHiX/codeForces/