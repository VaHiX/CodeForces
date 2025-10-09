// Problem: CF 2014 C - Robin Hood in Town
// https://codeforces.com/contest/2014/problem/C

/*
C. Robin Hood in Town
Algorithm: Sorting + Math
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the array

The problem is about finding the minimum value of x (extra gold) that needs to be added 
to the richest person's wealth so that more than half of the population becomes unhappy.
A person is unhappy if their wealth is strictly less than half of the average wealth.

Approach:
1. Sort the array to easily find the median and process elements in order.
2. Calculate total sum of wealth.
3. Use binary search or direct calculation to determine minimum x such that 
   more than n/2 people are unhappy after adding x to the richest person's wealth.
4. The key insight is to maximize the effect of adding x to one person's wealth 
   while minimizing how many people become unhappy.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> a(n);
    ll s(0);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
      s += a[p];
    }
    if (n <= 2) {
      puts("-1");
      continue;
    }
    sort(a.begin(), a.end()); // Sort to get the median easily
    ll res = 2 * n * a[n / 2] - s + 1; // Compute minimum x needed
    res = (res > 0 ? res : 0); // If negative, set to 0
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/