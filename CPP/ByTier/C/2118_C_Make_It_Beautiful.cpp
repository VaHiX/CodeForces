// Problem: CF 2118 C - Make It Beautiful
// https://codeforces.com/contest/2118/problem/C

/*
C. Make It Beautiful
Algorithm: Greedy bit manipulation approach
Time Complexity: O(n * B + B) where B = 63 (number of bits)
Space Complexity: O(B) for the auxiliary array zv

The problem asks to maximize the sum of beauty (number of set bits) in an array 
after at most k operations, each of which increases an element by 1.

Approach:
- For each bit position, calculate how many numbers in the array have that bit unset.
- Greedily use up to k operations to flip unset bits to set bits, prioritizing lower
  bit positions (more significant bits contribute more to beauty).
- We iterate through all possible bit positions, and for each, determine how many
  operations we can spend to turn unset bits into set ones without exceeding k.

*/

#include <cstdio>
typedef long long ll;

int main() {
  const ll B = 63;
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    ll zv[B] = {0}; // zv[p] stores count of numbers with p-th bit unset
    ll beauty(0);   // initial beauty sum
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      for (ll p = 0; p < B; p++) { // For each bit position
        if (x % 2) {               // If current bit is set
          ++beauty;
        } else {                   // If current bit is unset
          ++zv[p];
        }
        x /= 2; // Move to next bit
      }
    }
    for (ll p = 0; p < B; p++) {
      ll add = (1LL << p);         // Value of current bit position
      ll need = k / add;           // How many operations needed to flip all unset bits at this position
      need = (need < zv[p] ? need : zv[p]); // At most as many as available unset bits
      beauty += need;              // Add the increase in beauty
      k -= need * add;             // Reduce remaining operations
    }
    printf("%lld\n", beauty);
  }
}


// https://github.com/VaHiX/codeForces/