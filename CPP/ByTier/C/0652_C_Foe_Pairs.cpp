// Problem: CF 652 C - Foe Pairs
// https://codeforces.com/contest/652/problem/C

/*
 * Problem: Foe Pairs
 * 
 * Purpose: Given a permutation of numbers and a list of "foe pairs", 
 *          count the number of intervals [x, y] that do not contain any foe pair.
 *          A foe pair (a, b) is considered to be in an interval if both a and b 
 *          appear within that interval.
 * 
 * Algorithm:
 * 1. Convert the permutation into a position array 'a' such that a[i] = position of i in the permutation.
 * 2. For each foe pair (u, v), find their positions in the permutation and mark the leftmost position 
 *    where a foe pair could span from the smaller to larger position.
 * 3. Use a sliding window technique to calculate valid intervals efficiently.
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
  std::vector<ll> a(n + 1); // Position of each value in the permutation
  for (ll p = 1; p <= n; p++) {
    ll x;
    scanf("%lld", &x);
    a[x] = p; // Store position of value x
  }
  std::vector<ll> b(n + 1); // Mark invalid starting positions for intervals
  for (ll p = 0; p < m; p++) {
    ll x, y;
    scanf("%lld%lld", &x, &y);
    x = a[x]; // Get position of x
    y = a[y]; // Get position of y
    if (x > y) {
      ll tmp = x;
      x = y;
      y = tmp;
    }
    // Mark the earliest position that cannot be the start of a valid interval ending at y
    b[y] = (b[y] > x + 1) ? b[y] : (x + 1);
  }
  
  ll left(1), cnt(0); // left tracks the leftmost allowed start of an interval
  for (ll p = 1; p <= n; p++) {
    // Update the left boundary to ensure no foe pair is in current interval
    left = (left > b[p]) ? left : b[p];
    // Count valid intervals ending at position p
    cnt += p - left + 1;
  }
  
  printf("%lld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/CodeForces/