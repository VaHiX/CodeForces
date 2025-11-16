// Problem: CF 1009 D - Relatively Prime Graph
// https://codeforces.com/contest/1009/problem/D

/*
 * Purpose: Construct a connected undirected graph with n vertices and m edges
 *          such that for every edge (u, v), GCD(u, v) = 1 (relatively prime).
 *
 * Algorithm: 
 *   - First, create a star graph centered at vertex 1, connecting all other nodes to 1.
 *   - Then, add more edges between pairs (a, b) where GCD(a, b) = 1.
 *   - If we cannot get exactly m edges, output "Impossible".
 *
 * Time Complexity: O(n^2 * log(min(a,b))) - due to checking GCD for all pairs up to n
 * Space Complexity: O(m) - to store the edges
 */

#include <cstdio>
#include <vector>
#include <utility>

typedef long long ll;

// Compute greatest common divisor using Euclidean algorithm
ll gcd(ll a, ll b) { return (b == 0) ? a : gcd(b, a % b); }

int main() {
  ll n, m;
  scanf("%lld %lld", &n, &m);
  
  // Check if it's possible to form a graph with m edges and n vertices
  // Minimum edges in a connected graph is n - 1
  // Maximum edges in a simple graph is n*(n-1)/2
  if (m < n - 1 || m > n * (n - 1) / 2) {
    puts("Impossible");
    return 0;
  }
  
  std::vector<std::pair<ll, ll>> v;
  
  // Add edges from vertex 1 to all other vertices
  // This creates a star graph which is connected
  for (ll p = 2; p <= n; p++) {
    v.push_back(std::make_pair(1, p));
  }
  
  // Try to add more edges that satisfy the relatively prime condition
  for (ll a = 2; a <= n && v.size() < m; a++) {
    for (ll b = a + 1; b <= n && v.size() < m; b++) {
      if (gcd(a, b) != 1) {
        continue;
      }
      v.push_back(std::make_pair(a, b));
    }
  }
  
  // If we did not get enough edges, it's impossible
  if (v.size() < m) {
    puts("Impossible");
  } else {
    puts("Possible");
    for (ll p = 0; p < v.size(); p++) {
      printf("%lld %lld\n", v[p].first, v[p].second);
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/