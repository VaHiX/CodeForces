// Problem: CF 2125 C - Count Good Numbers
// https://codeforces.com/contest/2125/problem/C

/*
C. Count Good Numbers
Algorithm: 
  - A "good" number has all prime factors with at least two digits (i.e., >= 10).
  - The approach uses precomputation and mathematical optimization to efficiently count good numbers in a range.
  - Key insight: We iterate through numbers modulo LCM(2,3,5,7) = 210, which represents a cycle where we can count good numbers.
    We compute the count of good numbers in one full cycle (from 1 to 209).
  - For large ranges, we use a recurrence function `getCount` that computes how many good numbers exist up to x,
    leveraging periodicity and precomputed sum per cycle.
  
Time Complexity: O(1) per test case after preprocessing
Space Complexity: O(1)

*/

#include <cstdio>
typedef long long ll;

// Function to calculate number of good integers from 1 to x
ll getCount(ll x, const ll LCM, const ll seg_cnt) {
  ll cnt = (x / LCM) * seg_cnt;  // Count full cycles
  x %= LCM;                      // Remaining part after dividing by LCM
  for (ll p = 1; p <= x; p++) {
    cnt += (p % 2 && p % 3 && p % 5 && p % 7);  // If none of 2,3,5,7 divide p, it's good
  }
  return cnt;
}

int main() {
  const ll L = 210;              // LCM of 2,3,5,7
  ll g(0);
  
  // Precompute count of good numbers in range [1, 209]
  for (ll p = 1; p < L; p++) {
    g += (p % 2 && p % 3 && p % 5 && p % 7);  // Increment if no prime factor from {2,3,5,7}
  }
  
  ll t;
  scanf("%lld", &t);
  
  while (t--) {
    ll a, b;
    scanf("%lld %lld", &a, &b);
    
    // Result = count(0..b) - count(0..a-1)
    ll res = getCount(b, L, g) - getCount(a - 1, L, g);
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/