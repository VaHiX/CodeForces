// Problem: CF 1248 A - Integer Points
// https://codeforces.com/contest/1248/problem/A

/*
 * Problem: Counting Integer Intersection Points of Two Sets of Lines
 *
 * Description:
 * DLS draws n lines of the form y = x + p_i, and JLS draws m lines of the form y = -x + q_i.
 * We need to count how many pairs of lines (one from each set) intersect at an integer point.
 *
 * Key Insight:
 * The intersection of line y = x + p_i and y = -x + q_j occurs when:
 *   x + p_i = -x + q_j
 *   2x = q_j - p_i
 *   x = (q_j - p_i) / 2
 * For x to be an integer, (q_j - p_i) must be even.
 * This happens if and only if p_i and q_j have the same parity (both odd or both even).
 *
 * Algorithm:
 * 1. Count how many p_i are odd and how many are even (stored in array a)
 * 2. Count how many q_j are odd and how many are even (stored in array b)
 * 3. The answer is a[0]*b[0] + a[1]*b[1]
 *    i.e., number of (even, even) pairs + number of (odd, odd) pairs.
 *
 * Time Complexity: O(n + m) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll a[2] = {0}; // a[0] counts even p_i, a[1] counts odd p_i
    while (n--) {
      ll x;
      scanf("%lld", &x);
      ++a[x & 1]; // Increment count based on parity (x & 1 gives 0 or 1)
    }
    ll m;
    scanf("%lld", &m);
    ll b[2] = {0}; // b[0] counts even q_j, b[1] counts odd q_j
    while (m--) {
      ll x;
      scanf("%lld", &x);
      ++b[x & 1]; // Increment count based on parity (x & 1 gives 0 or 1)
    }
    ll ans = a[0] * b[0] + a[1] * b[1]; // Count valid pairs
    printf("%lld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/