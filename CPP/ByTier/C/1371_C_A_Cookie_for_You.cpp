// Problem: CF 1371 C - A Cookie for You
// https://codeforces.com/contest/1371/problem/C

/*
C. A Cookie for You
Algorithm: Greedy approach with constraint checking
Time Complexity: O(1) per test case
Space Complexity: O(1)

The problem involves determining if there exists an order of guests such that no guest gets angry.
Guests of type 1 prefer vanilla if v > c, otherwise chocolate.
Guests of type 2 prefer chocolate if v > c, otherwise vanilla.
We simulate the worst-case scenarios to check feasibility:
1. Total cookies must be sufficient for all guests (n + m <= a + b)
2. Maximum number of any guest type should not exceed minimum of cookie counts
   (since in worst case all guests of one type come first and need that many of their preferred cookie)
*/

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll a, b, n, m;
    scanf("%lld %lld %lld %lld", &a, &b, &n, &m);
    ll least = (a < b) ? a : b;  // Find the smaller count of cookies
    puts(((m + n <= a + b) && (m <= least)) ? "Yes" : "No");  // Check conditions for validity
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/