// Problem: CF 1538 C - Number of Pairs
// https://codeforces.com/contest/1538/problem/C

/*
C. Number of Pairs
Algorithm: Two pointers technique
Time Complexity: O(n log n) per test case due to sorting, O(n) for two-pointer traversal
Space Complexity: O(1) additional space (not counting input storage)

Given an array of integers, find the number of pairs (i,j) such that l <= a[i] + a[j] <= r.
The solution uses sorting and two pointers to efficiently count valid pairs.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;

// Function to count pairs whose sum is <= s
ll f(std::vector<ll> &v, ll s) {
  ll left(0), right(v.size() - 1);  // Initialize two pointers
  ll res(0);
  while (left < right) {            // Loop until pointers meet
    if (v[left] + v[right] > s) {   // If sum exceeds s, move right pointer left
      --right;
    } else {                        // If sum is <= s, all elements from left+1 to right form valid pairs with left
      res += right - left;
      ++left;                       // Move left pointer right
    }
  }
  return res;
}

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, lower, upper;
    scanf("%lld %lld %lld", &n, &lower, &upper);  // Read input values
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);         // Read array elements
    }
    sort(a.begin(), a.end());       // Sort the array to enable two-pointer technique
    ll cnt = f(a, upper) - f(a, lower - 1);  // Count pairs in range [lower, upper]
    printf("%lld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/