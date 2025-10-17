// Problem: CF 2002 F2 - Court Blue (Hard Version)
// https://codeforces.com/contest/2002/problem/F2

/*
F2. Court Blue (Hard Version)
Time Complexity: O(n log log n + n * m * α(n)), where n ≈ 2×10^7 and α is the inverse Ackermann function.
Space Complexity: O(n)

Algorithms/Techniques:
- Sieve of Eratosthenes for prime generation
- Memoized DFS with pruning to determine valid (W_L, W_F) pairs such that gcd(W_L, W_F) = 1
- Brute-force search over all valid combinations up to n and m, bounded by early termination conditions

This problem involves dynamic programming with memoization combined with number theory concepts. 
We precompute primes using sieve and then use a recursive DFS with memoization to check whether 
a given pair (i,j) of wins is valid (gcd(i,j) == 1). The final score is maximized over all such valid pairs.
*/

#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#define int long long
using namespace std;

int n, m, l, f;
int ans;
bool notp[20000010]; // Boolean array to mark composite numbers
vector<int> pr;       // Vector to store primes
map<pair<int, int>, int> vis; // Memoization map for DFS results

// Sieve of Eratosthenes to precompute primes up to n
void ss(int n) {
  notp[1] = 1; // 1 is not a prime
  for (int i = 2; i <= n; i++) {
    if (!notp[i])
      pr.push_back(i); // Add prime number to vector
    for (int j = 0; j < pr.size() && pr[j] * i <= n; j++) {
      notp[pr[j] * i] = 1; // Mark product as composite
      if (i % pr[j] == 0)
        break; // Ensure unique factorization
    }
  }
}

// DFS to determine if a pair (x, y) is valid (gcd(x,y) == 1)
int dfs(int x, int y) {
  if (x < y)
    swap(x, y); // Ensure x >= y for optimization

  if (__gcd(x, y) > 1)
    return 0; // Not valid if not coprime

  if (!notp[x])
    return 1; // If x is prime and gcd(x,y)=1, then it's valid (since y < x)

  if (vis.count({x, y}))
    return vis[{x, y}]; // Return memoized result

  if (x != 1 && dfs(x - 1, y))
    return vis[{x, y}] = 1; // Try going one step back in x

  if (y != 1 && dfs(x, y - 1))
    return vis[{x, y}] = 1; // Try going one step back in y

  return vis[{x, y}] = 0; // Not valid
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  ss(20000000); // Precompute primes

  int T;
  cin >> T;
  while (T--) {
    cin >> n >> m >> l >> f;
    
    ans = max(l * n + f, l + m * f); // Initial boundary answer
    
    for (int i = n; i >= 2; i--) {
      if (i * l + m * f <= ans)
        break; // Early termination if current value cannot exceed best

      for (int j = m; j >= 2; j--) {
        if (i * l + j * f <= ans)
          break; // Early termination for inner loop too

        if (dfs(i, j))
          ans = i * l + j * f; // Update maximum if valid
      }
    }

    cout << ans << '\n';
  }

  return 0;
}


// https://github.com/VaHiX/codeForces/