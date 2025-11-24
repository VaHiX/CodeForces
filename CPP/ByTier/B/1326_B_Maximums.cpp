// Problem: CF 1326 B - Maximums
// https://codeforces.com/contest/1326/problem/B

#include <cstdio>
typedef long long ll;
int main() {
  ll n;
  scanf("%lld", &n);
  ll mx(0); // mx stores the maximum value of a seen so far
  for (ll p = 0; p < n; p++) {
    ll b;
    scanf("%lld", &b);
    ll a = b + mx; // calculate a_i based on b_i and previous maximum
    printf("%lld ", a);
    mx = (mx > a) ? mx : a; // update maximum to be the larger of current max and new a_i
  }
  puts("");
  return 0;
}
/*
B. Maximums

Algorithm:
The problem involves reconstructing an array 'a' from another array 'b', where each b[i] is calculated as a[i] - x[i], and x[i] is the maximum value among all elements of array 'a' that come before index i (or 0 if i=1).

This can be solved efficiently by observing that:
- For i = 1: x[1] = 0, so a[1] = b[1] + 0 = b[1]
- For i > 1: Knowing the maximum of previous elements gives us an effective offset.

So, given b[i], we calculate a[i] by adding current b[i] with the running maximum of all previously computed values of 'a'. After computing a[i], update the running maximum to be the larger of the previous maximum and a[i].

Time Complexity: O(n), as the loop runs once through all n elements.
Space Complexity: O(1), since only constant extra space is used besides input/output buffers.

*/

// https://github.com/VaHiX/codeForces/