// Problem: CF 1996 G - Penacony
// https://codeforces.com/contest/1996/problem/G

/*
 * Code Purpose: 
 * This code solves a problem on Penacony, where we have a circular graph of n houses connected by n bidirectional roads,
 * and m friendship pairs between houses. The goal is to find the minimum number of roads that must be maintained so that
 * every pair of friends can reach each other through the maintained roads.
 *
 * Approach:
 * The problem is essentially finding the minimum number of edges to maintain in a cyclic graph such that all
 * friendship pairs are connected. This can be modeled using a technique based on XOR and prefix sums.
 * The idea is to use a hash map to track how many times each prefix XOR value occurs.
 * The maximum frequency of any such value gives us the largest connected component in the original graph.
 * The answer then becomes n - max_frequency, since all nodes in the same component can be connected with fewer edges.
 *
 * Time Complexity: O(n + m) average case due to hash map operations (assuming uniform distribution of hashes)
 * Space Complexity: O(n) for storing prefix XOR values and hash map
 */

#include <algorithm>
#include <iostream>
#include <random>
#include <unordered_map>
#include <utility>
#include <random>
#include <ctime>

using namespace std;

inline unsigned long long rnd() {
    static std::mt19937_64 rng(time(0));  // seed with current time
    return rng();
}

typedef long long ll;
typedef unsigned long long ull;
const int N = 4e5 + 10;
const ll mod = 1e9 + 7;
int t;
int n, m;
const ll base = 433;
ll a[N];
inline void solve() {
  unordered_map<ll, int> my_map; // Hash map to store frequency of prefix XOR values
  cin >> n >> m;
  for (int i = 0; i <= n; i++)
    a[i] = 0; // Initialize prefix sum array
  for (int i = 1, a1, b1; i <= m; i++) {
    cin >> a1 >> b1;
    ll r = rnd(); // Generate random number for XOR operation
    a[a1] ^= r, a[b1] ^= r; // XOR the random number at both ends of edge
  }
  for (int i = 1; i <= n; i++) {
    a[i] ^= a[i - 1]; // Compute prefix XOR
    my_map[a[i]]++; // Count frequency of prefix XOR
  }
  int ans = 0;
  for (auto tmp : my_map) {
    ans = max(ans, tmp.second); // Track maximum frequency
  }
  cout << n - ans << '\n'; // Minimum edges to maintain = total nodes - max component size
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/