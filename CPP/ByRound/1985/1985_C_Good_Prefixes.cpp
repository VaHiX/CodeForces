// Problem: CF 1985 C - Good Prefixes
// https://codeforces.com/contest/1985/problem/C

/*
C. Good Prefixes
Algorithms/Techniques: Prefix sum, single pass iteration
Time Complexity: O(n) per test case
Space Complexity: O(1)

Alex thinks some array is good if there exists some element that can be represented as the sum of all other elements.
We need to count how many prefixes of the given array are "good".
For each prefix, we check if any element equals the sum of all others in that prefix.
To optimize this, we use a running sum and track the maximum element seen so far.
If at any point the total sum is twice the maximum element, then that element is the sum of others,
hence making the prefix good.
*/

#include <cstdio>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll cs(0), mx(-1), cnt(0); // cs: current sum, mx: maximum element so far, cnt: count of good prefixes
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      mx = (mx > x ? mx : x); // Update the maximum element in prefix
      cs += x;                // Add current element to prefix sum
      cnt += (cs == 2 * mx);  // If sum equals twice max, this prefix is good
    }
    printf("%lld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/