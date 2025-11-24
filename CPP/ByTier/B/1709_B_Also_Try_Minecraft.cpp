// Problem: CF 1709 B - Also Try Minecraft
// https://codeforces.com/contest/1709/problem/B

/*
 * Problem: B. Also Try Minecraft
 * 
 * Purpose: This code solves a pathfinding problem on a 1D terrain where movement between adjacent columns incurs fall damage.
 *          The goal is to find the minimum total fall damage for a set of queries moving from one column to another.
 *
 * Algorithm:
 *  - Preprocess two arrays:
 *    - left[p]: cumulative fall damage from column 0 to p when moving right (i.e., sum of upward moves).
 *    - right[p]: cumulative fall damage from column n-1 to p when moving left (i.e., sum of upward moves).
 *  - For each query, depending on direction (s to f), compute the difference in preprocessed values.
 *
 * Time Complexity: O(n + m)
 * Space Complexity: O(n)
 */

#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll n, m;
  scanf("%lld %lld", &n, &m);
  std::vector<ll> h(n); // Heights of columns
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &h[p]);
  }
  
  // left[p] stores cumulative fall damage when going right from index 0 to p
  std::vector<ll> left(n, 0);
  for (ll p = 1; p < n; p++) {
    left[p] = left[p - 1] + ((h[p] < h[p - 1]) ? (h[p - 1] - h[p]) : 0);
  }

  // right[p] stores cumulative fall damage when going left from index n-1 to p
  std::vector<ll> right(n, 0);
  for (ll p = n - 2; p >= 0; p--) {
    right[p] = right[p + 1] + ((h[p] < h[p + 1]) ? (h[p + 1] - h[p]) : 0);
  }

  while (m--) {
    ll res(0);
    ll s, f;
    scanf("%lld %lld", &s, &f);
    if (f > s) {
      // Moving right: use left array
      res = left[f - 1] - left[s - 1];
    } else {
      // Moving left: use right array
      res = right[f - 1] - right[s - 1];
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/