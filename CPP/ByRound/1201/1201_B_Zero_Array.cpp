// Problem: CF 1201 B - Zero Array
// https://codeforces.com/contest/1201/problem/B

/*
B. Zero Array
Algorithms/Techniques: Greedy approach with sum and maximum element analysis

Time Complexity: O(n)
Space Complexity: O(1)

The problem asks whether we can reduce all elements in the array to zero by repeatedly picking two elements and decreasing both by 1.
Key insight:
- Each operation reduces the total sum by 2.
- Hence, the total sum must be even for a solution to exist (since we subtract an even number of times).
- Also, if any single element is greater than half the total sum, it's impossible because we can't pair it with others to reduce it to zero.

The solution:
1. Read all elements and compute their sum (total) and maximum value (mx).
2. Check two conditions:
   - Total sum must be even.
   - Maximum element must not exceed half of the total sum.
3. If both conditions are satisfied, output "YES", otherwise "NO".
*/

#include <cstdio>
typedef long long ll;
int main() {
  ll n;
  scanf("%lld", &n);
  ll total(0), mx(0);  // Initialize total sum and maximum element
  for (ll p = 0; p < n; p++) {
    ll x;
    scanf("%lld", &x);
    total += x;         // Add current element to total sum
    mx = (mx > x) ? mx : x;  // Update maximum element
  }
  puts((total % 2) || (2 * mx > total) ? "NO" : "YES");  // Check conditions for YES/NO
  return 0;
}


// https://github.com/VaHiX/codeForces/