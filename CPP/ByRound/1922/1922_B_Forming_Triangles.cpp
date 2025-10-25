// Problem: CF 1922 B - Forming Triangles
// https://codeforces.com/contest/1922/problem/B

/*
B. Forming Triangles

Algorithm:
- For each test case, count the number of ways to choose 3 sticks that can form a valid triangle.
- A triangle is valid if the sum of any two sides is greater than the third side.
- Since lengths are 2^a_i, we can sort them and use a two-pointer or combinatorial approach.
- This implementation uses frequency counting and precomputing sums for efficiency.

Time Complexity: O(n log n) per test case due to map operations (insertion and iteration).
Space Complexity: O(n) for storing frequencies in the map.
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
    std::map<ll, ll> m;  // Map to store frequency of each a_i
    for (ll p = 0; p < n; p++) {
      ll x;
      scanf("%lld", &x);
      ++m[x];  // Count occurrences of each value
    }
    ll prev(0);  // Keeps track of total count of elements processed so far
    ll cnt(0);   // Result counter
    for (std::map<ll, ll>::iterator it = m.begin(); it != m.end(); it++) {
      ll val = it->second;  // Frequency of current value
      // Add combinations of 3 sticks from same a_i values (if at least 3)
      cnt += (val >= 3) * val * (val - 1) * (val - 2) / 6;
      // Add combinations of 2 sticks from current a_i + 1 stick from previous values
      cnt += (val >= 2) * val * (val - 1) * prev / 2;
      prev += val;  // Update cumulative count
    }
    printf("%lld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/