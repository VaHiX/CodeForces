// Problem: CF 1668 B - Social Distance
// https://codeforces.com/contest/1668/problem/B

/*
B. Social Distance
time limit per test
1.5 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

Algorithms/Techniques: Greedy approach with prefix sum and optimization.

Time Complexity: O(n) per test case, where n is the number of people.
Space Complexity: O(1), only using a few variables for computation.

Problem Description:
We have m chairs arranged in a circle (numbered 0 to m-1). n people want to sit such that 
each person i requires at least a[i] empty chairs on both their left and right side. 
This means if a person sits at chair j, then chairs from 
(j - a[i]) mod m to (j + a[i]) mod m must be empty (inclusive).

We need to determine whether it's possible for all n people to sit down satisfying the constraints.
The key insight is to compute the minimum total space needed by considering:
1. Each person takes 1 chair.
2. Each person needs 'a[i]' empty chairs on both left and right = 2 * a[i] extra space.
3. The maximum gap between any two people must be considered to avoid overlapping constraints.

Approach:
For each person, we track:
- The minimum chair value (mn)
- The maximum chair value (mx)
- Total sum of all values (s)
We calculate the 'need' which is n + s + (mx - mn), and check if this <= m.

This calculation accounts for:
- n: number of people (each needs 1 chair).
- s: total "required empty space" needed on both sides across all people.
- (mx - mn): difference between max and min positions – gives us the actual seating interval.

If need <= m, then it's possible to arrange everyone; otherwise not.

*/

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, m;
    scanf("%lld %lld", &n, &m);
    ll mn(1e9 + 7), mx(-1e9 - 7); // Initialize min and max to extreme values
    ll s(0); // Total sum of a[i]
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      s += x; // Accumulate sum of a[i]
      mn = (mn < x ? mn : x); // Update minimum a[i]
      mx = (mx > x ? mx : x); // Update maximum a[i]
    }
    ll need = n + s + (mx - mn); // Compute minimal required chairs
    puts(need <= m ? "YES" : "NO"); // Output result
  }
}


// https://github.com/VaHiX/codeForces/