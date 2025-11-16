// Problem: CF 1978 F - Large Graph
// https://codeforces.com/contest/1978/problem/F

/*
 * Purpose: This code calculates the number of connected components in a graph
 *          constructed from a cyclically shifted matrix. Each vertex in the graph
 *          corresponds to an element in the matrix, and edges exist between
 *          vertices if their Manhattan distance is at most k and their GCD is > 1.
 *
 * Algorithms/Techniques:
 *  - Sieve of Eratosthenes for precomputing smallest prime factors (SPF)
 *  - Union-Find (Disjoint Set Union) for efficiently grouping connected components
 *  - Preprocessing of matrix elements to group them by prime factors for fast edge
 *    detection based on GCD condition
 *
 * Time Complexity: O(N log log N + T * N), where N is up to 1e6, T is number of test cases
 * Space Complexity: O(N), for storing SPF, prime list, and union-find structures
 */
#include <stdlib.h>
#include <iostream>
#include <utility>

using namespace std;
const int N = 2e6 + 5, M = 1e6 + 5;
;
typedef long long ll;
int a[N], n, k, f[M], p[M], cnt, r[N], sz[N];
bool g[M];
ll ans;
pair<int, int> s[M];
int find(int x) { return r[x] == x ? x : r[x] = find(r[x]); }
void merge(int x, int y) {
  x = find(x), y = find(y);
  if (x == y)
    return;
  if (sz[x] > sz[y])
    swap(x, y);
  r[x] = y;
  sz[y] += sz[x];
  sz[x] = 0;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  // Preprocessing primes and smallest prime factors using sieve
  f[1] = g[1] = 1;
  for (int i = 2; i <= 1e6; i++) {
    if (!g[i]) {
      p[++cnt] = i;
      f[i] = i;
    }
    for (int j = 1; j <= cnt && i * p[j] <= 1e6; j++) {
      g[i * p[j]] = 1;
      f[i * p[j]] = p[j];
      if (i % p[j] == 0)
        break;
    }
  }
  int cases;
  cin >> cases;
  for (int t = 1; t <= cases; t++) {
    cin >> n >> k;
    // Load input data into array, with special handling for 1s
    for (int i = 1; i <= n; i++) {
      cin >> a[i + n - 1];
      if (a[i + n - 1] == 1)
        ans += n - 2 + (i == 1);
    }
    // Shift the array to prepare for two cycles
    for (int i = 1; i < n; i++)
      a[i] = a[i + n];
    n = 2 * n - 1;
    // Initialize Union-Find structures
    for (int i = 1; i <= n; i++)
      r[i] = i, sz[i] = 1;
    // For each element, decompose into prime factors and connect to previous similar prime
    for (int i = 1; i <= n; i++) {
      while (a[i] != 1) {
        // If the same prime factor has been seen before in current test case
        if (s[f[a[i]]].first == t && abs(i - s[f[a[i]]].second) <= k)
          merge(i, s[f[a[i]]].second);
        // Update the last seen position for this prime factor
        s[f[a[i]]] = {t, i};
        a[i] /= f[a[i]]; // Divide by the smallest prime factor
      }
    }
    // Count number of root nodes (connected components)
    for (int i = 1; i <= n; i++) {
      ans += (find(i) == i);
    }
    cout << ans << '\n';
    ans = 0;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/