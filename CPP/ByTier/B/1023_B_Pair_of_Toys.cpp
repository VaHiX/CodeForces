// Problem: CF 1023 B - Pair of Toys
// https://codeforces.com/contest/1023/problem/B

/*
B. Pair of Toys
Algorithm: Mathematical approach to count valid pairs (a, b) such that a + b = k and 1 <= a < b <= n.
Techniques: Arithmetic and boundary checking.
Time Complexity: O(1)
Space Complexity: O(1)

The problem asks to find the number of ways to choose two different toys with prices summing to k.
We use mathematical logic:
- For a pair (a, b) where a < b and a + b = k, we have b = k - a.
- Both a and b must be in range [1, n].
- Since a < b and a + b = k, we get a < k/2.
- The minimum value of a is 1.
- For each valid a, there exists exactly one valid b = k - a.

Steps:
1. Calculate the lower bound 'a' for possible values of a using k-1.
2. Calculate the upper bound 'b' such that a < b and both are within [1,n].
3. Count valid pairs: max(0, b - a + 1)
*/

#include <cstdio>
typedef long long ll;

int main() {
  ll n, k;
  scanf("%lld %lld", &n, &k);
  
  // Calculate the starting value of 'a' such that a < b and a + b = k
  // If k - 1 < n, the maximum possible value for a is (k-1), else it's n
  ll a = k - ((k - 1 < n) ? (k - 1) : n);
  
  // Calculate the ending value of 'a' such that a < b and both are within [1,n]
  // If (k - 1)/2 < n, then the maximum valid a is (k-1)/2, else it's n
  ll b = ((k - 1) / 2 < n) ? ((k - 1) / 2) : n;
  
  // Compute the number of valid pairs; ensure non-negative result
  ll ans = b - a + 1;
  printf("%lld\n", ans > 0 ? ans : 0);
  return 0;
}


// https://github.com/VaHiX/codeForces/