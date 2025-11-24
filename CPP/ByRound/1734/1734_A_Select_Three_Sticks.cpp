// Problem: CF 1734 A - Select Three Sticks
// https://codeforces.com/contest/1734/problem/A

/*
Problem: A. Select Three Sticks
Purpose: Given n sticks, find the minimum number of operations to make three sticks form an equilateral triangle.
Algorithm: Sort the array and check all possible triplets that can form a triangle with equal sides by minimizing operations needed to adjust the lengths.

Approach:
1. Sort the array of stick lengths.
2. For each valid triplet (i, i+1, i+2) in sorted order, calculate how many operations are required to make those three sticks have the same length.
3. The number of operations is equal to the difference between the largest and smallest value among the three, which can be computed as v[i+2] - v[i].
4. Return the minimum such operation count.

Time Complexity: O(n log n) due to sorting, where n <= 300.
Space Complexity: O(n) for storing the vector of stick lengths.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> v(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &v[p]); // Read each stick length
    }
    sort(v.begin(), v.end()); // Sort the sticks by length
    
    ll ans = v.back(); // Initialize answer with the largest stick
    for (ll p = 2; p < n; p++) {
      ll test = v[p] - v[p - 2]; // Difference between third and first in triplet
      ans = (ans < test) ? ans : test; // Update minimum operations needed
    }
    printf("%lld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/