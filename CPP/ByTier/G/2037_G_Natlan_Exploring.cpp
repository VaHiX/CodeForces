// Problem: CF 2037 G - Natlan Exploring
// https://codeforces.com/contest/2037/problem/G

/*
G. Natlan Exploring
Purpose: Determine the number of distinct paths from City 1 to City n in a directed graph where there's an edge from i to j if gcd(a_i, a_j) != 1.
Algorithm: 
    - Precompute divisors and Möbius function for each number up to 10^6 using sieve.
    - Use dynamic programming with inclusion-exclusion principle on divisors.
Time Complexity: O(N * log(max_a))
Space Complexity: O(N)
*/

#include <cstdio>
#include <vector>
const int N = 1048576, mod = 998244353;
std::vector<int> d[N]; // Stores all divisors of each number
int pr[N / 5], u[N], pc; // pr: primes, u: mobius function values, pc: prime count
bool vis[N];
void sev() {
  for (int i = 2, nx; i < N; ++i) {
    if (!vis[i])
      pr[++pc] = i, u[i] = 1, d[i].push_back(i);
    for (int j = 1; j <= pc && (nx = i * pr[j]) < N; ++j) {
      vis[nx] = 1;
      d[nx] = d[i]; // Copy divisors of i to nx
      if (i % pr[j] == 0)
        break;
      u[nx] = -u[i]; // Möbius function: negate if divisible by square
      d[nx].push_back(pr[j]); // Add new prime divisor
      for (int f : d[i])
        d[nx].push_back(f * pr[j]); // Extend divisors with new prime
    }
  }
}
int f[N]; // f[x] = number of paths ending at a city whose attractiveness is divisible by x
int main() {
  sev();
  int n;
  scanf("%d", &n);
  bool fst = 1;
  while (n--) {
    int x, s = fst; // s: sum of paths through divisors; fst for initializing first node
    fst = 0;
    scanf("%d", &x);
    for (int y : d[x]) // Iterate over all divisors of current city's attractiveness
      s = ((s + u[y] * f[y]) % mod + mod) % mod; // Inclusion-exclusion with Möbius function
    for (int y : d[x]) // Update DP values for each divisor
      (f[y] += s) %= mod;
    if (!n)
      return printf("%d", s), 0; // Output final result when last city is processed
  }
}


// https://github.com/VaHiX/codeForces/