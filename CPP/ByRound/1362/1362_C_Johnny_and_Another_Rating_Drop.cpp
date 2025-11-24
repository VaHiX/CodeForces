// Problem: CF 1362 C - Johnny and Another Rating Drop
// https://codeforces.com/contest/1362/problem/C

/*
C. Johnny and Another Rating Drop
Algorithm: For each bit position, count how many times 1 appears across all numbers from 0 to n,
           then calculate contribution of that bit to total unfairness.
           The contribution is the number of 1s in a bit position multiplied by the number of 0s in that same bit position
           (since a 1 contributes to the difference when paired with a 0).
           Time Complexity: O(log n) per test case
           Space Complexity: O(1)
*/

#include <cstdio>
typedef long long ll;

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll cnt(0);
    ll denom(1);
    
    // Loop through each bit position
    for (ll p = 0; p < 64; p++) {
      // Count how many numbers in [0, n] have the current bit set to 1
      cnt += (n / denom); 
      
      // Move to next bit position
      denom *= 2;
      
      // Break if we've gone beyond the range of n
      if (denom > n) {
        break;
      }
    }
    
    printf("%lld\n", cnt);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/