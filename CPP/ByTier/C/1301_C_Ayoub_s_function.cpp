// Problem: CF 1301 C - Ayoub's function
// https://codeforces.com/contest/1301/problem/C

/*
C. Ayoub's function
Algorithms/Techniques: Greedy approach to maximize the number of substrings containing at least one '1'
Time Complexity: O(1) per test case
Space Complexity: O(1)

The problem asks us to find the maximum value of f(s) over all binary strings s of length n with exactly m ones.
f(s) counts the number of contiguous substrings that contain at least one '1'.

To maximize f(s), we should distribute the m ones as evenly as possible among (m+1) segments:
- (n - m) positions are zeros
- We divide these (n - m) zeros into (m + 1) parts to separate the m ones
- This maximizes the number of substrings with at least one '1'
*/
#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, m;
    scanf("%lld %lld", &n, &m);
    
    // Calculate base number of ones per segment
    ll a = (n - m) / (m + 1);       // Number of zeros between ones in the optimal arrangement
    
    // Calculate leftover zeros to distribute
    ll b = (n - m) % (m + 1);        // Extra zeros that will get one more zero in some segments
    
    // Total possible substrings: n*(n+1)/2
    // Subtract invalid substrings with no ones
    // Invalid substrings are formed by blocks of zeros only
    // There are (m+1) such blocks, with a zeros in each block and b blocks with (a+1) zeros
    
    ll ans = n * (n + 1) / 2 - (m + 1) * a * (a + 1) / 2 - b * (a + 1);
    printf("%lld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/