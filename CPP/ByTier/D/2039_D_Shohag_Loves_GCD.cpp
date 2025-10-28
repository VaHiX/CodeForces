// Problem: CF 2039 D - Shohag Loves GCD
// https://codeforces.com/contest/2039/problem/D

/*
D. Shohag Loves GCD

Algorithms/Techniques: Sieve of Eratosthenes, Greedy, Preprocessing

Time Complexity: O(V log log V + n) where V = 1e5
Space Complexity: O(V + n)

This solution uses the concept that if we assign values to array elements such that 
the exponents of prime factors (i.e., f[i] function) determine the assignment, 
then we can guarantee that gcd(i,j) != gcd(a_i, a_j) for all pairs.

The key insight:
- For each number i, f[i] computes how many times it is divisible by primes.
- For any two indices i < j with gcd(i, j) = k, the condition implies that 
  a_k != gcd(a_i, a_j), which can be avoided if we carefully assign values based on f[i].
- We preprocess the sieve to calculate f[i] for each number and then compute g[i] = max(g[i - 1], f[i]).

The array is built by placing elements from S in decreasing order of f[i] so that 
each index i is assigned a value such that the condition gcd(i, j) != gcd(a_i, a_j) holds.
*/

#include <algorithm>
#include <iostream>

#define pb push_back
#define SZ(x) (int)(x).size()
using namespace std;
const int N = 1e5 + 5, V = 1e5;
int _, n, m, a[N], f[N], g[N];

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  // Sieve to compute the number of distinct prime factors for each number
  for (int i = 2; i <= V; i++)
    if (!f[i]) {
      f[i] = 1;
      for (int j = i * 2; j <= V; j += i)
        f[j] = f[j / i] + 1;
    }

  // Precompute max f[i] up to each point
  for (int i = 2; i <= V; i++)
    g[i] = max(g[i - 1], f[i]);

  cin >> _;
  while (_--) {
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
      cin >> a[i];

    // If maximum prime factor count >= number of elements, impossible
    if (g[n] >= m) {
      cout << "-1\n";
      continue;
    }

    // For each i from 1 to n, assign a value from S at position (m - f[i])
    for (int i = 1; i <= n; i++)
      cout << a[m - f[i]] << ' ';
    cout << '\n';
  }
}


// https://github.com/VaHiX/codeForces/