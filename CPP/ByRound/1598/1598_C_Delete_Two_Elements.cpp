// Problem: CF 1598 C - Delete Two Elements
// https://codeforces.com/contest/1598/problem/C

/*
C. Delete Two Elements

Purpose:
This code solves the problem of counting the number of pairs of elements in an array such that removing them leaves the arithmetic mean unchanged.

Approach:
1. For each test case, calculate the total sum of the array and determine the required mean k.
2. Check if it's mathematically possible to remove two elements while maintaining the same mean.
   - This requires (n * k == 2 * sum) for integer division.
3. Count how many pairs of elements (a[i], a[j]) where i < j satisfy:
   - Their sum equals 2*k (to maintain mean)
   - If both elements are equal, use combination formula C(n,2) = n*(n-1)/2
   - Otherwise multiply counts of first and second element

Time Complexity: O(n log n) due to map operations, where n is the size of array.
Space Complexity: O(n) for storing frequency count in map.

Algorithms/Techniques:
- HashMap (std::map) to store element frequencies
- Mathematical formula for combinations to avoid nested loops
- Arithmetic mean calculation and validation
*/

#include <cstdio>
#include <map>
#include <utility>

typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::map<ll, ll> cnt; // Map to store frequency of each element
    ll sum(0); // Sum of all elements
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      ++cnt[x]; // Increment frequency of current element
      sum += x;
    }
    ll check = 2 * sum / n; // Required sum of two elements to maintain mean
    bool possible = (n * check == 2 * sum); // Check if division is exact
    ll res(0);
    if (!possible) {
      puts("0");
      continue;
    }
    for (std::map<ll, ll>::iterator it = cnt.begin(); it != cnt.end(); it++) {
      ll key = it->first; // Current element
      if (2 * key > check) {
        continue; // Skip if double of current exceeds required sum
      }
      ll left = it->second; // Frequency of current element
      ll right = cnt.count(check - key) ? cnt[check - key] : 0; // Frequency of complement
      res += (2 * key == check) ? (left * (left - 1) / 2) : (left * right); // Add valid pairs
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/