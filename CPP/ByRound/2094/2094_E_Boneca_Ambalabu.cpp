// Problem: CF 2094 E - Boneca Ambalabu
// https://codeforces.com/contest/2094/problem/E

/*
E. Boneca Ambalabu
Problem: Given a sequence of n integers, find the maximum value of sum of XORs (a_k ⊕ a_1) + (a_k ⊕ a_2) + ... + (a_k ⊕ a_n)
for all possible k from 1 to n.

Algorithm:
- For each bit position b from 0 to 34, count how many numbers in the array have that bit set to 1.
- For each number a_k, compute the sum of XORs by considering the contribution of each bit.
- To maximize the sum, for each bit, we want to choose between setting it to 1 or 0:
    - If current bit of a_k is 1: contribute (n - v[b]) to result
    - If current bit of a_k is 0: contribute v[b] to result

Time Complexity: O(n * B) where B = 35 (constant)
Space Complexity: O(B) = O(1) (v vector size is fixed at 35)

Approach:
- Precompute count of 1s at each bit position
- For each element, calculate best possible total by choosing optimal bits to maximize the sum of XORs
*/

#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  const int B = 35; // Maximum number of bits needed for nums up to 2^30
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> a(n);          // Input array
    std::vector<ll> v(B);          // Count of 1s at each bit position
    
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
      ll x(a[p]);                  // Copy of current number
      for (ll b = 0; x && b < B; b++) {
        v[b] += (x % 2);          // Count 1s at bit position b
        x /= 2;
      }
    }

    ll mx(0);                      // Maximum sum found so far
    
    for (ll p = 0; p < n; p++) {
      ll x(a[p]);                  // Copy of current number a_k
      ll total(0);
      for (ll b = 0; b < B; b++) {
        // If bit is set in a_k, then (a_k ^ a_i) contributes (n - v[b]) to the sum,
        // otherwise it contributes v[b], and we XOR with 1 << b
        total += (1 << b) * (x % 2 ? (n - v[b]) : v[b]);
        x /= 2;
      }
      mx = (mx > total ? mx : total); // Update maximum value
    }

    printf("%lld\n", mx);
  }
}


// https://github.com/VaHiX/codeForces/