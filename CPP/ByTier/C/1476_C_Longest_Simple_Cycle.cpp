// Problem: CF 1476 C - Longest Simple Cycle
// https://codeforces.com/contest/1476/problem/C

/*
C. Longest Simple Cycle
Algorithm: Dynamic Programming on Chains
Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

The problem involves constructing a graph from n chains and finding the longest simple cycle.
Each chain is connected to the previous one via specific vertices (a_i and b_i).
We use dynamic programming to track the maximum possible cycle length up to each chain,
considering how connections affect the total cycle length.

Key insight:
- We process chains sequentially, maintaining state of the best cycle ending at current chain
- For each chain, we calculate contributions from:
  1. Direct connection (c[p] + 1 + diff)
  2. Previous chain's best result adjusted for vertex alignment (sofar - diff + c[p] + 1)
- The difference in vertex positions (diff) determines how much we gain or lose
  when connecting chains.
*/

#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> c(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &c[p]);
    }
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }
    std::vector<ll> b(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &b[p]);
    }
    
    ll sofar(0), res(0);
    for (ll p = 1; p < n; p++) {
      ll diff = a[p] - b[p]; // Difference in vertex positions between chains
      if (diff < 0) {
        diff = -diff;
      }
      
      ll cur = c[p] + 1 + diff; // Direct connection cost plus chain length
      
      if (diff > 0) { // If there's a misalignment
        ll tmp = (sofar - diff) + c[p] + 1; // Adjusted previous result
        cur = (cur > tmp) ? cur : tmp; // Take maximum of direct and adjusted path
      }
      
      res = (res > cur) ? res : cur; // Track global maximum
      sofar = cur; // Update for next iteration
    }
    
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/