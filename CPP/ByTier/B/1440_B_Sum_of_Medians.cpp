// Problem: CF 1440 B - Sum of Medians
// https://codeforces.com/contest/1440/problem/B

/*
B. Sum of Medians
Algorithm: Greedy approach to maximize sum of medians.
- Since the array is already sorted, we can strategically assign elements to groups
  such that the median of each group is maximized.
- The key insight is that in a group of size n, the median is at position ⌈n/2⌉.
- To maximize the total sum of medians, we should try to place larger values as medians.
- We process elements from left to right and assign them to groups such that
  the best possible medians are achieved.

Time Complexity: O(n*k) per test case, where n is size of each group and k is number of groups.
Space Complexity: O(1) - only using a few variables for computation.
*/

#include <cstdio>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    ll a = k * ((n - 1) / 2);   // Starting index to take elements as medians
    ll b = 1 + n / 2;           // Step to take every 'b'-th element as median
    ll sm(0);                   // Sum of medians
    
    // Iterate over all nk elements in the array
    for (ll p = 0; p < n * k; p++) {
      ll x;
      scanf("%lld", &x);
      
      // Skip first 'a' elements, they are not used to form medians
      if (p < a) {
        continue;
      } else if ((p - a) % b == 0) {
        // Take every b-th element starting from position 'a'
        sm += x;
      }
    }
    
    printf("%lld\n", sm);
  }
}


// https://github.com/VaHiX/codeForces/