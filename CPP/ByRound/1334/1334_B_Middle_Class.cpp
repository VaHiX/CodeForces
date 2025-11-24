// Problem: CF 1334 B - Middle Class
// https://codeforces.com/contest/1334/problem/B

/*
B. Middle Class
Algorithm: Greedy approach with sorting
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the vector

The problem asks us to find the maximum number of people who can be made "wealthy" 
(where wealthy means having at least x burles). We can perform reforms that redistribute 
savings among any subset of people. The key insight is to sort the array in descending 
order and try to make as many people as possible have at least x burles by accumulating 
their savings and checking if we can distribute them equally among the first k people.

For each prefix of the sorted array, we calculate the total sum of the first p+1 elements,
and check if this total is enough so that each person in that prefix can have at least x.
If yes, we update our answer to p+1 (number of people who are wealthy).
*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n, x;
    scanf("%lld %lld", &n, &x);
    std::vector<ll> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }
    sort(a.rbegin(), a.rend()); // Sort in descending order
    ll s(0), ans(0);
    for (long p = 0; p < n; p++) {
      s += a[p]; // Accumulate sum of first p+1 elements
      if (s < (p + 1) * x) { // If average is less than x, break
        break;
      }
      ans = p + 1; // Update the number of wealthy people
    }
    printf("%lld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/