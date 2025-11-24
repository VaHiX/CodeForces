// Problem: CF 1775 C - Interesting Sequence
// https://codeforces.com/contest/1775/problem/C

/*
 * Problem: C. Interesting Sequence
 * 
 * Purpose: Given two integers n and x, find the smallest m >= n such that 
 *          n & (n+1) & ... & m = x, where & is bitwise AND.
 * 
 * Algorithm:
 * - The key insight is that as we increase m, the result of the AND operation 
 *   can only decrease or stay the same, never increase.
 * - For a valid solution to exist:
 *   1. All bits in x must be less than or equal to the corresponding bits in n.
 *   2. For the highest bit where n and x differ, the bit in x must be 1 and in n 0.
 *   3. All bits below that highest differing bit must be 0 in x.
 *   4. All bits beyond the highest differing bit must not cause x to be affected.
 * 
 * Time Complexity: O(1) - We process at most 60 bits (since numbers up to 1e18 are used).
 * Space Complexity: O(1) - Only using fixed size arrays and variables.
 */

#include <iostream>
#include <utility>

using namespace std;
using ll = long long;
using ld = long double;
ll mod = 1e9 + 7;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pil = pair<int, ll>;
ll INF = 1e18;
using pii = pair<pi, int>;
using pic = pair<int, char>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    ll n, x;
    cin >> n >> x;
    int b1[60], b2[60];  // b1 stores bits of n, b2 stores bits of x
    bool ok = true;
    int high = -1;  // highest bit where n and x differ
    
    // Extract bits of n and x into arrays
    for (int i = 0; i < 60; ++i) {
      b1[i] = (n >> i) & 1;
      b2[i] = (x >> i) & 1;
      // If bit in x is greater than in n, it's impossible
      if (b2[i] > b1[i]) {
        ok = false;
        break;
      }
      // Track where n and x differ, and the bit in n is 1
      if (b1[i] > b2[i]) {
        high = i;
      }
    }
    
    // Check if all bits below high are 0 in x
    for (int i = 0; i < high; ++i) {
      if (b2[i]) {
        ok = false;
      }
    }
    
    if (!ok) {
      cout << -1 << endl;
      continue;
    }
    
    // If no difference, x is already n
    if (high == -1) {
      cout << x << endl;
      continue;
    }
    
    // Check if bits beyond high in n are set
    for (int i = high + 1; i < 60; ++i) {
      if (!b1[i]) {
        break;  // Stop if we hit a 0 bit in n
      }
      if (b2[i]) {
        ok = false;  // If x has 1 in this position, it's invalid
        break;
      }
    }
    
    if (!ok) {
      cout << -1 << endl;
      continue;
    }
    
    // Calculate minimal value of m
    ll d = (1ll << high) - (n % (1ll << high));
    cout << n + d << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/