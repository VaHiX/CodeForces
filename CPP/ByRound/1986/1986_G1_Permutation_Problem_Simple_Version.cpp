// Problem: CF 1986 G1 - Permutation Problem (Simple Version)
// https://codeforces.com/contest/1986/problem/G1

/*
 * Problem: G1. Permutation Problem (Simple Version)
 * 
 * Purpose: Count the number of index pairs (i, j) such that p[i] * p[j] is divisible by i * j.
 * 
 * Algorithm:
 * - For each element in the permutation, compute the reduced form of i and p[i] by dividing
 *   their GCD to simplify divisibility checking.
 * - Store these reduced values in a vector and sort them.
 * - For each sorted pair (x, y) where x = i / gcd(i, p[i]), y = p[i] / gcd(i, p[i]):
 *   iterate through multiples of y up to x, and for each multiple, check if any previous
 *   (x', y') in the map satisfies x % x' == 0.
 * - Increment the answer with the count of such valid pairs.
 * 
 * Time Complexity: O(n^2 * log(n)) in worst case, but optimized via sorting and map lookups.
 * Space Complexity: O(n)
 */
#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

using namespace std;
const int MOD = 1e9 + 7;
#define f first
#define s second
#define ll long long
#define pii pair<int, int>
#define plli pair<ll, int>
#define pb push_back
#define eb emplace_back
#define vctr vector
int a[500001];
int p[500001];
int x[500001];
map<int, int> v[500001]; // Map to count occurrences of (reduced_x, reduced_y)
vctr<pii> v2; // Vector to store (reduced_x, reduced_y) pairs for sorting

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int tt;
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
      p[a[i]] = i; // Store position of each value in permutation
    }
    for (int i = 1; i <= n; ++i) {
      int gcd = __gcd(i, p[i]); // Compute GCD of index and value
      p[i] /= gcd; // Reduce p[i] by GCD
      x[i] = i / gcd; // Reduce index by GCD
      v2.eb(x[i], p[i]); // Store reduced pair
    }
    sort(v2.begin(), v2.end()); // Sort pairs for efficient searching
    ll ans = 0;
    for (auto it : v2) {
      // Iterate over multiples of 'it.s' up to 'it.f'
      for (int j = it.s; j <= it.f; j += it.s) {
        // For each multiple, check all stored pairs with this denominator
        for (auto it2 : v[j]) {
          if (it.f % it2.f == 0) { // If numerator is divisible by stored numerator
            ans += it2.s; // Add count of valid pairs
          }
        }
      }
      ++v[it.f][it.s]; // Add current pair to map
    }
    cout << ans << '\n';
    for (int i = 1; i <= n; ++i)
      v[i].clear(); // Clear map for next test case
    v2.clear(); // Clear vector for next test case
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/